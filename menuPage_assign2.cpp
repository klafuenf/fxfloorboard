/****************************************************************************
**
** Copyright (C) 2007~2012 Colin Willcocks.
** Copyright (C) 2005~2007 Uco Mesdag.
** All rights reserved.
** This file is part of "GT-100B Fx FloorBoard".
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

#include "menuPage_assign2.h"

menuPage_assign2::menuPage_assign2(QWidget *parent)
    : menuPage(parent)
{
    setLSB("08", "50");
    editDetails()->patchPos(2438, 32, "08", "50");    //192 sysx file offset and data length of chorus parameters x2,
    setEditPages();
};

void menuPage_assign2::updateSignal()
{
   updateSwitch("08", "00", "50");
};

void menuPage_assign2::setEditPages()
{
    editDetails()->page()->newGroupBox(tr("Assign 2"));
    editDetails()->page()->newGroupBox(tr(""));
    editDetails()->page()->newStackControl(0);
    editDetails()->page()->addSwitch(0, 0, 1, 1, "08", "00", "50", "middle", Qt::AlignCenter);
    editDetails()->page()->addStackControl();
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->insertStackField(0, 0, 1, 2, 1);
    editDetails()->page()->addGroupBox(0, 0, 1, 1);

    editDetails()->addPage();

    //editDetails()->page()->newStackField(0);
    //editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0);
    editDetails()->page()->newGroupBox("Assign 2 Target");
    editDetails()->page()->addTarget(0, 0, 1, 3, "08", "00", "51", "target","target", 120); // Target
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->newGroupBox("Assign 2 Source");
    editDetails()->page()->newStackControl(1);
    editDetails()->page()->addComboBox(0, 0, 1, 1, "08", "00", "57");                    // Source
    editDetails()->page()->addStackControl();
    editDetails()->page()->addComboBox(0, 1, 1, 1, "08", "00", "58");                    // Source Mode
    editDetails()->page()->addRange(0, 2, 1, 2, "08", "00", "59", "Structure");         // min/max range widget
    editDetails()->page()->addGroupBox(0, 1, 1, 1);
    editDetails()->page()->insertStackField(1, 1, 0, 1, 2);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(1);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(1);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(1);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(1);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(1);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(1);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(1);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(1);
    editDetails()->page()->newGroupBox("Assign 2 Internal Pedal");
    editDetails()->page()->addComboBox(0, 0, 1, 1, "08", "00", "5B");                    // Internal Pedal Trigger
    editDetails()->page()->addKnob(0, 1, 1, 1, "08", "00", "5C");                        // Internal Pedal Time
    editDetails()->page()->addComboBox(0, 2, 1, 1, "08", "00", "5D");                    // Internal Pedal Curve
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(1);
    editDetails()->page()->newGroupBox("Assign 2 Wave Pedal");
    editDetails()->page()->addKnob(1, 0, 1, 1, "08", "00", "5E", "normal","right", 105);// Wave Form Rate
    editDetails()->page()->addComboBox(1, 1, 1, 1, "08", "00", "5F");                    // Wave Form
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(1);
    editDetails()->page()->newGroupBox("Input");
    editDetails()->page()->addKnob(0, 0, 1, 1, "0A", "00", "30", "normal","right", 85);
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();

};
