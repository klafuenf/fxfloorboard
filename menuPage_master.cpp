/****************************************************************************
**
** Copyright (C) 2007~2015 Colin Willcocks.
** Copyright (C) 2005~2007 Uco Mesdag. 
** All rights reserved.
** This file is part of "GT-100 Fx FloorBoard".
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License along
** with this program; if not, write to the Free Software Foundation, Inc.,
** 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
**
****************************************************************************/

#include "menuPage_master.h"

menuPage_master::menuPage_master(QWidget *parent)
    : menuPage(parent)
{
    setLSB("07", "00");
    editDetails()->patchPos(2028, 20, "07", "10");
    //editDetails()->patchPos(2124, 16, "07", "40");
    setEditPages();
}

void menuPage_master::updateSignal()
{

}

void menuPage_master::setEditPages()
{

    editDetails()->page()->newGroupBox("Master EQ");
    editDetails()->page()->addMasterEQ(0, 1, 2, 4, "07", "00", "10");
    editDetails()->page()->addGroupBox(0, 0, 2, 1);

    editDetails()->page()->newGroupBox("Amp CTRL");
    editDetails()->page()->addComboBox(0, 0, 1, 1, "06", "00", "60");                     // amp control
    editDetails()->page()->addGroupBox(1, 1, 1, 1);

    editDetails()->page()->newGroupBox("Master");
    editDetails()->page()->addKnob(0, 0, 1, 1, "07", "00", "16");                         // master BPM
    editDetails()->page()->addComboBox(1, 0, 1, 1, "07", "00", "18");                     // master key
    editDetails()->page()->addComboBox(2, 0, 1, 1, "07", "00", "19");                     // master beat
    editDetails()->page()->addComboBox(3, 0, 1, 1, "07", "00", "1A");                     // midi pitch detect
    editDetails()->page()->addGroupBox(0, 2, 2, 1);

    editDetails()->page()->newGroupBox("Manual Mode");
    editDetails()->page()->addComboBox(0, 1, 1, 1, "07", "00", "40");                     //
    editDetails()->page()->addComboBox(0, 2, 1, 1, "07", "00", "41");                     //
    editDetails()->page()->addComboBox(1, 0, 1, 1, "07", "00", "42");                     //
    editDetails()->page()->addComboBox(2, 0, 1, 1, "07", "00", "43");                     //
    editDetails()->page()->addComboBox(3, 0, 1, 1, "07", "00", "44");                     //
    editDetails()->page()->addComboBox(4, 0, 1, 1, "07", "00", "45");                     //
    editDetails()->page()->addComboBox(6, 1, 1, 1, "07", "00", "46");                     //
    editDetails()->page()->addComboBox(6, 2, 1, 1, "07", "00", "47");                     //
    editDetails()->page()->addGroupBox(0, 3, 2, 1);

    editDetails()->addPage();
}
