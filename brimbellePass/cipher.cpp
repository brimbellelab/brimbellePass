#include "cipher.h"

#include <QtGlobal>

#include <cmath>
#include <iostream>
#include <string>
#include <memory>
#include <limits>
#include <stdexcept>

#include <openssl/evp.h>

#include <iomanip>


// Not fond of this zallocator thing but it's coming from openssl example here:
// https://wiki.openssl.org/index.php/EVP_Authenticated_Encryption_and_Decryption
template <typename T>
struct zallocator
{
public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    pointer address (reference v) const {return &v;}
    const_pointer address (const_reference v) const {return &v;}

    pointer allocate (size_type n) {
        if (n > std::numeric_limits<size_type>::max() / sizeof(T))
            throw std::bad_alloc();
        return static_cast<pointer> (::operator new (n * sizeof (value_type)));
    }

    void deallocate(pointer p, size_type n) {
        OPENSSL_cleanse(p, n*sizeof(T));
        ::operator delete(p);
    }

    size_type max_size() const {
        return std::numeric_limits<size_type>::max() / sizeof (T);
    }

    template<typename U>
    struct rebind
    {
        typedef zallocator<U> other;
    };

    void construct (pointer ptr, const T& val) {
        new (static_cast<T*>(ptr) ) T (val);
    }

    void destroy(pointer ptr) {
        static_cast<T*>(ptr)->~T();
    }

#if __cpluplus >= 201103L
    template<typename U, typename... Args>
    void construct (U* ptr, Args&&  ... args) {
        ::new (static_cast<void*> (ptr) ) U (std::forward<Args> (args)...);
    }

    template<typename U>
    void destroy(U* ptr) {
        ptr->~U();
    }
#endif
};

typedef std::basic_string<char, std::char_traits<char>, zallocator<char> > secure_string;

using EVP_CIPHER_CTX_free_ptr = std::unique_ptr<EVP_CIPHER_CTX, decltype(&::EVP_CIPHER_CTX_free)>;



Cipher::Cipher()
{
    // The key must have a fixed size of 32 bytes and is initially filled with '0'.
    // Later, its content will be replaced with the actual password for as many bytes as possible.
    std::memset(aesKey, '0', KEY_SIZE);
    key = "";
}



Cipher::Cipher(QString mainPassword)
{
    // The key must have a fixed size of 32 bytes and is initially filled with '0'.
    // Later, its content will be replaced with the actual password for as many bytes as possible.
    std::memset(aesKey, '0', KEY_SIZE);

    setPassword(mainPassword);
}



void
Cipher::setPassword(const QString &mainPassword)
{
    key = QString(mainPassword);

    // Load the necessary cipher.
    EVP_add_cipher(EVP_aes_256_cbc());

    std::cout << "KEY SIZE: " << int(KEY_SIZE) << ", password size: " << mainPassword.size() << std::endl;

    // aesKey memory has already been prepared, now injecting the password at the beginning for as many bytes as
    // possible.
    std::memcpy(aesKey, key.toStdString().c_str(), qMin(int(KEY_SIZE), mainPassword.size()));

    // Dump key for debug.
    for (size_t i = 0; i < KEY_SIZE; i++)
    {
        std::cout << aesKey[i];
    }
    std::cout << std::endl;

    // Dump IV for debug.
    for (size_t i = 0; i < BLOCK_SIZE; i++)
    {
        std::cout << iv[i];
    }
    std::cout << std::endl;
}



QByteArray
Cipher::encrypt(QByteArray input)
{
    std::cout << "ENCRYPTING" << std::endl;
    secure_string ctext;
    // secure_string ptext = input.toStdString().c_str();
    secure_string ptext = input.data();

    // Dump original plain string.
    std::cout << "ptext initialized with " << ptext.size() << " bytes string: " << std::endl;
    for (size_t i = 0; i < ptext.size(); i++)
    {
        std::cout << ptext[i];
    }
    std::cout << std::endl;

    std::cout << "size of plain char*: " << (int)ptext.size() << std::endl;

    std::unique_ptr<EVP_CIPHER_CTX, decltype(&::EVP_CIPHER_CTX_free)> ctx(EVP_CIPHER_CTX_new(), EVP_CIPHER_CTX_free);
    int returnCode = EVP_EncryptInit_ex(ctx.get(), EVP_aes_256_cbc(), NULL, aesKey, iv);
    if (returnCode != 1)
      throw std::runtime_error("EVP_EncryptInit_ex failed");

    // Cipher text expands upto BLOCK_SIZE.
    ctext.resize(ptext.size() + BLOCK_SIZE);
    int out_len1 = (int)ctext.size();

    returnCode = EVP_EncryptUpdate(ctx.get(),
                           (unsigned char*)&ctext[0],
                            &out_len1,
                            (const unsigned char*)&ptext[0],
                            (int)ptext.size());
    if (returnCode != 1)
    {
        throw std::runtime_error("EVP_EncryptUpdate failed");
    }

    int out_len2 = (int)ctext.size() - out_len1;
    returnCode = EVP_EncryptFinal_ex(ctx.get(), (unsigned char*)&ctext[0] + out_len1, &out_len2);
    if (returnCode != 1)
    {
        throw std::runtime_error("EVP_EncryptFinal_ex failed");
    }

    // Set cipher text size now that we know it.
    ctext.resize(out_len1 + out_len2);

    // Dump ciphered string and assign result.
    QByteArray result;
    std::cout << "resulting Ciphered text of " << out_len1 + out_len2 << " bytes: " <<  std::endl;
    std::cout << std::hex <<  std::setw(2);
    for (int i = 0; i < out_len1 + out_len2; i++)
    {
        std::cout  << std::setfill('0') << "0x" << (static_cast<unsigned short>(ctext[i]) & 0xFF) << " ";
        result.append(ctext[i]);
    }
    std::cout << std::dec << std::endl;

    EVP_CIPHER_CTX_cleanup(ctx.get()); // Should be call when done to remove sensitive information from memory.

    return result;
}



QByteArray
Cipher::decrypt(QByteArray input)
{
    std::cout << "DECRYPTING" << std::endl;
    secure_string ptext;
    secure_string ctext;
    ctext.resize(input.size());
    ctext = input.data();
    // It's necessary to resize one more time ctext in case input ends with a \0 or the size will be wrong.
    ctext.resize(input.size());
    std::cout << "input qbyte array is " << input.size() << " bytes" << std::endl;
    // Dump ciphered string.
    std::cout << "ctext initialized with " << ctext.size() << " bytes string: " << std::endl;
    std::cout << std::hex;
    for (size_t i = 0; i < ctext.size(); i++)
    {
        std::cout << "0x"<< (static_cast<unsigned short>(ctext[i]) & 0xFF) << " ";
    }
    std::cout << std::dec << std::endl;

    std::unique_ptr<EVP_CIPHER_CTX, decltype(&::EVP_CIPHER_CTX_free)> ctx(EVP_CIPHER_CTX_new(), EVP_CIPHER_CTX_free);
    int returnCode = EVP_DecryptInit_ex(ctx.get(), EVP_aes_256_cbc(), NULL, aesKey, iv);
    if (returnCode != 1)
    {
        throw std::runtime_error("EVP_DecryptInit_ex failed");
    }

    // Plain text buffer must be the length of the ciphered string + BLOCK_SIZE.
    ptext.resize(ctext.size() + BLOCK_SIZE);

    int out_len1 = (int)ptext.size();

    std::cout << "ptext.size = " << out_len1 << ", ctext.size = " << ctext.size() << std::endl;

    returnCode = EVP_DecryptUpdate(ctx.get(),
                           (unsigned char*)&ptext[0],
                           &out_len1,
                           (const unsigned char*)&ctext[0],
                           (int)ctext.size());
    if (returnCode != 1)
    {
        throw std::runtime_error("EVP_DecryptUpdate failed");
    }

    int out_len2 = (int)ptext.size() - out_len1;
    std::cout  << "Size of ptext: " << ptext.size() << ", outlen1 is " << out_len1 << "; outlen2 is " << out_len2 << std::endl;

    returnCode = EVP_DecryptFinal_ex(ctx.get(),
                             (unsigned char*)&ptext[0] + out_len1,
                             &out_len2); // Just here to receive the result, it's not read within EVP_DecryptFinal.
    if (returnCode != 1)
    {
        ERR_print_errors_fp(stderr);
        throw std::runtime_error("EVP_DecryptFinal_ex failed");
    }

    // Set plain text size now that we know it.
    ptext.resize(out_len1 + out_len2);

    // Dump plain string and assign it to result.
    QByteArray result;
    std::cout << " Decyphered to " << out_len1 + out_len2 << "bytes:" << std::endl;
    for (size_t i = 0; i < ptext.size(); i++)
    {
        std::cout << ptext[i];
        result.append(ptext[i]);
    }
    std::cout << std::endl;

    EVP_CIPHER_CTX_cleanup(ctx.get()); // Should be call when done to remove sensitive information from memory.

    return result;
}
