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

#include "menuPage_assign7.h"

menuPage_assign7::menuPage_assign7(QWidget *parent)
    : menuPage(parent)
{
    setLSB("09", "70");
    editDetails()->patchPos(3266, 32, "09", "70");    //192 sysx file offset and data length of chorus parameters x2,
    setEditPages();
};

void menuPage_assign7::updateSignal()
{
   updateSwitch("09", "00", "70");
};

void menuPage_assign7::setEditPages()
{
    editDetails()->page()->newGroupBox(tr("Assign 7"));
    editDetails()->page()->newGroupBox(tr(""));
    editDetails()->page()->newStackControl(0);
    editDetails()->page()->addSwitch(0, 0, 1, 1, "09", "00", "70", "middle", Qt::AlignCenter);
    editDetails()->page()->addStackControl();
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->insertStackField(0, 0, 1, 2, 1);
    editDetails()->page()->addGroupBox(0, 0, 2, 1);

    editDetails()->addPage();

    editDetails()->page()->newStackField(0);
    editDetails()->page()->newGroupBox("Assign 7 Target");
    editDetails()->page()->addTarget(0, 0, 1, 3, "09", "00", "71", "target","target", 120); // Target
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->newGroupBox("Assign 7 Source");
    editDetails()->page()->newStackControl(1);
    editDetails()->page()->addComboBox(1, 0, 1, 1, "09", "00", "77");                    // Source
    editDetails()->page()->addStackControl();
    editDetails()->page()->addComboBox(1, 1, 1, 1, "09", "00", "78");                    // Source Mode
    editDetails()->page()->addRange(1, 2, 1, 2, "09", "00", "79", "Structure");         // min/max range widget
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
    editDetails()->page()->newGroupBox("Assign 7 Internal Pedal");
    editDetails()->page()->addComboBox(0, 0, 1, 1, "09", "00", "7B");                    // Internal Pedal Trigger
    editDetails()->page()->addKnob(0, 1, 1, 1, "09", "00", "79");                        // Internal Pedal Time
    editDetails()->page()->addComboBox(0, 2, 1, 1, "09", "00", "7D");                    // Internal Pedal Curve
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(1);
    editDetails()->page()->newGroupBox("Assign 7 Wave Pedal");
    editDetails()->page()->addKnob(1, 0, 1, 1, "09", "00", "7E", "normal","right", 105);// Wave Form Rate
    editDetails()->page()->addComboBox(1, 1, 1, 1, "09", "00", "7F");                    // Wave Form
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(1);
    editDetails()->page()->newGroupBox("Input");
    editDetails()->page()->addKnob(0, 0, 1, 1, "0A", "00", "30", "normal","right", 85);
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(0);editDetails()->page()->addStackField();
};
