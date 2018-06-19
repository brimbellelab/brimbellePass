# BrimbellePass

A split-database password manager, by [Landry COLLET](https://www.github.com/landrycollet) for [BrimbelleLab](https://www.github.com/brimbellelab).

BrimbellePass is a free software, licensed under GNU GPLv3.

![BrimbellePass, main screen](http://www.brimbellelab.com/brimbellepass/Screenshots/v1.0.0/mainScreen.png)


## Disclaimer

BrimbellePass is still a work in progress and clearly lacks A LOT of necessary features before claiming to be the
perfect password manager. Refer to the road map for more details before using.

This software is distributed AS IS, with no warranty expressed or implied.


## Introduction

BrimbellePass is born from my frustration of dealing with hundreds of password on a daily basis. And a light paranoia
about computer security.

There are plenty of solutions available, but none seems to match my requirements, which are:
- AES256 encryption of passwords and "safety answers".
- No storage of password on untrusted remote servers.
- No plugins embedded in web browser.
- Possibility to copy a password without never displaying it on the screen (useful in public areas).
- Possibility to simply display the password (useful when at home, the app running on a different device than the one
where you want to enter the password).
- Easy to track your password/login database with versioning tools such as SVN or Git.
- *Multiplateform, including smartphones (granted that one's not for tomorrow, although the use of Qt should make it
easier).*

- **and the main feature of BrimbellePass: the ability to store (encrypted) passwords list and logins list in two
different, separate XML files.**

The last point tremendously improves the safety and possibilities of password manager:
- you can store your passwords in a private cloud / git repo or a NAS, and of the logins in a generic cloud like
Dropbox.
- you can store the passwords on a cold storage like a USB key, and the logins on your computer.
- if one of the service you use is compromised, you're still safe as there's no use of a single file : you need the
pair. It's then easy to shuffle the entries on your files to make the leaked file completely obsolete.

Features in *italic* are not yet implemented, but I'm working hard on it!

For now this software has been developed on MacOS X 10.13 but it should build fine on Windows and Linux as well as long
as the dependancies are installed on your computer.

**For your safety, as the software is not in a stable version yet, I would strongly advise you to keep track of your
passwords on another medium as well.**

Knowing the current limitations of BrimbellePass, if you don't feel wild enough to use this software, feel free to have
a look to [KeePass](http://keepass.info), it's my second favorite!

## License

BrimbellePass is licensed under the GNU General Public License version 3. http://www.gnu.org/licenses/gpl-3.0.html
```
BrimbellePass, a split-database password manager.

Copyright (C) 2018, by Landry COLLET for BrimbelleLab.

BrimbellePass is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or any
later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see https://www.gnu.org/licenses/.
```


## Getting started

Make sure you have the dependancies installed, i.e. Qt and OpenSSL.

Open the file `BrimbellePass.pro` with QtCreator

or

Build the software with the following commands:

*TODO*

To start, go to the configuration tab and point to `loginList.xml` and `pwdList.xml` stored in `XML_samples`. Then,
restart the software.

The default password associated with these files is `GUEST`.


## Road map

Here are the next features to be developed. Feel free to help and contribute if you're interested!

- friendly wizard to get set when the software is opened for the first time.
- user should be able to change the main password.
- the accounts should appear in alphabetical order in the comboBox list AND
- accounts shouldn't be stored by alphabetical order in the XML files.
- translation to French, and other languages.
- add a checksum attribute to the "entry" tag in both XML files to make sure the 2 files match?
- shuffle entries id, for when one of the database files has been compromised.
- export the database to a csv file (or even xml file), without encryption, human readable.
- modify the main password, which implies to decipher all encrypted data and re-encrypt everything with the new key.
- import CSV files.
- import other password manager file format.
- make it possible to access xml files through SSH on a remote machine.
- optional encryption of logins as well.
- port software on iOS.
- port software on Android.


## Issues

- Input fields are parsed in an incorrect order when hitting TAB key.

If you find an unknown issue, fell free to mention it [here](https://github.com/brimbellelab/brimbellePass/issues).


## Author

Landry COLLET [www.landrycollet.fr](http://www.landrycollet.fr/blog)
[Offer me a beer here!](https://www.paypal.me/LandryCOLLET)


## Credits

BrimbellePass is written using the following libraries and frameworks:
- [Qt](https://www.qt.io), version 5.7, but should be compatible with any Qt version > 4.0
- [OpenSSL](https://www.openssl.org)
