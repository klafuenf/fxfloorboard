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

#include "menuPage_assign1.h"

menuPage_assign1::menuPage_assign1(QWidget *parent)
    : menuPage(parent)
{
    setLSB("08", "30");
    editDetails()->patchPos(2374, 32, "08", "30");
    setEditPages();
}

void menuPage_assign1::updateSignal()
{
   updateSwitch("08", "00", "30");
}

void menuPage_assign1::setEditPages()
{
    editDetails()->page()->newGroupBox(tr("Assign 1"));
    editDetails()->page()->newGroupBox(tr(""));
    editDetails()->page()->addSwitch(0, 0, 1, 1, "08", "00", "30", "middle", Qt::AlignCenter);
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->newGroupBox("Assign 1 Target");
    editDetails()->page()->addTarget(0, 0, 1, 3, "08", "00", "31", "target","target", 120); // Target
    editDetails()->page()->addGroupBox(0, 1, 1, 1);
    editDetails()->page()->newGroupBox("Assign 1 Source");
    editDetails()->page()->newStackControl(0);
    editDetails()->page()->addComboBox(0, 0, 1, 1, "08", "00", "37");                    // Source
    editDetails()->page()->addStackControl();
    editDetails()->page()->addComboBox(0, 1, 1, 1, "08", "00", "38");                    // Source Mode
    editDetails()->page()->addRange(0, 2, 1, 2, "08", "00", "39", "Structure");         // min/max range widget
    editDetails()->page()->addGroupBox(0, 2, 1, 1);
    editDetails()->page()->insertStackField(0, 1, 1, 1, 2);
    editDetails()->page()->addGroupBox(0, 0, 2, 1);

    editDetails()->addPage();



    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);
    editDetails()->page()->newGroupBox("Assign 1 Internal Pedal");
    editDetails()->page()->addComboBox(0, 0, 1, 1, "08", "00", "3B");                    // Internal Pedal Trigger
    editDetails()->page()->addKnob(0, 1, 1, 1, "08", "00", "3C");                        // Internal Pedal Time
    editDetails()->page()->addComboBox(0, 2, 1, 1, "08", "00", "3D");                    // Internal Pedal Curve
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);
    editDetails()->page()->newGroupBox("Assign 1 Wave Pedal");
    editDetails()->page()->addKnob(1, 0, 1, 1, "08", "00", "3E", "normal","right", 120);// Wave Form Rate
    editDetails()->page()->addComboBox(1, 1, 1, 1, "08", "00", "3F");                    // Wave Form
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);
    editDetails()->page()->newGroupBox("Input");
    editDetails()->page()->addKnob(0, 0, 1, 1, "0A", "00", "30", "normal","right", 85);
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();

}
