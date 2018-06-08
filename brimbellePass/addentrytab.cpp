// AddEntryTab.cpp - BrimbellePass, a split-database password manager. github.com/brimbellelab/brimbellepass
// Copyright (C) 2018, by Landry COLLET for BrimbelleLab.
// Released under the GNU General Public License v3, see https://www.gnu.org/licenses.

#include "addentrytab.h"

AddEntryTab::AddEntryTab(QWidget *parent) : QWidget(parent)
{
    label = new QLabel("Add entry", this);
}
