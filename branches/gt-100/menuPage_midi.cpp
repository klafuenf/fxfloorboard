/****************************************************************************
**
** Copyright (C) 2007~2012 Colin Willcocks.
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

#include "menuPage_midi.h"

menuPage_midi::menuPage_midi(QWidget *parent)
    : menuPage(parent)
{
  //setImage(":/images/midi_pushbutton.png");
  setLSB("0B", "00");
	setEditPages();
}

void menuPage_midi::updateSignal()
{

}

void menuPage_midi::setEditPages()
{
               
	editDetails()->page()->newGroupBox("SYSTEM MIDI.  Caution: Changes are automatically written to the GT-100.");
    editDetails()->page()->addComboBox(0, 0, 1, 1, "02", "00", "00", "System"); // rx channel
    editDetails()->page()->addComboBox(0, 1, 1, 1, "02", "00", "01", "System"); // omni mode
	editDetails()->page()->addComboBox(0, 2, 1, 1, "02", "00", "02", "System"); // tx channel
    editDetails()->page()->addComboBox(0, 3, 1, 1, "02", "00", "03", "System"); // sync clock
    editDetails()->page()->addComboBox(0, 4, 1, 1, "02", "00", "04", "System"); // midi port
    editDetails()->page()->addComboBox(0, 5, 1, 1, "02", "00", "05", "System"); // pc out
	
	
    editDetails()->page()->addComboBox(1, 0, 1, 1, "02", "00", "06", "System"); // PH loop out
    editDetails()->page()->addComboBox(1, 1, 1, 1, "02", "00", "07", "System"); // Accel/CTL out
    editDetails()->page()->addComboBox(1, 2, 1, 1, "02", "00", "08", "System"); // EXP out
    editDetails()->page()->addComboBox(1, 3, 1, 1, "02", "00", "09", "System"); // EXP sw out
    editDetails()->page()->addComboBox(2, 0, 1, 1, "02", "00", "0A", "System"); // sub ctl 1 out
    editDetails()->page()->addComboBox(2, 1, 1, 1, "02", "00", "0B", "System"); // sub ctl 2 out
    editDetails()->page()->addComboBox(2, 2, 1, 1, "02", "00", "0C", "System"); // sub EXP out
	editDetails()->page()->addComboBox(2, 3, 1, 1, "02", "00", "0D", "System"); // map select
	
	editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->addPage("02", "00", "7F", "00", "System");

    editDetails()->page()->newGroupBox("MIDI PROGRAM TABLE - BANK 0.            Caution: Changes are automatically written to the GT-100.");
    editDetails()->page()->addMultiComboBox(0, 0, 1, 1, "02", "01", "00", "System"); // 1
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->addPage("02", "00", "7F", "01", "System");

    editDetails()->page()->newGroupBox("MIDI PROGRAM TABLE - BANK 1.            Caution: Changes are automatically written to the GT-100.");
    editDetails()->page()->addMultiComboBox(0, 0, 1, 1, "02", "03", "00", "System"); // 1
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->addPage("02", "00", "7F", "02", "System");

    editDetails()->page()->newGroupBox("MIDI PROGRAM TABLE - BANK 2.            Caution: Changes are automatically written to the GT-100.");
    editDetails()->page()->addMultiComboBox(0, 0, 1, 1, "02", "05", "00", "System"); // 1
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->addPage("02", "00", "7F", "03", "System");

    editDetails()->page()->newGroupBox("MIDI PROGRAM TABLE - BANK 3.            Caution: Changes are automatically written to the GT-100.");
    editDetails()->page()->addMultiComboBox(0, 0, 1, 1, "02", "07", "00", "System"); // 1
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->addPage("02", "00", "7F", "04", "System");
}
