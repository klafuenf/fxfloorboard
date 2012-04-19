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
};

void menuPage_midi::updateSignal()
{

};

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
    /*editDetails()->page()->addMultiComboBox(0, 1, 1, 1, "02", "01", "02", "System"); //
    editDetails()->page()->addMultiComboBox(0, 2, 1, 1, "02", "01", "04", "System"); //
    editDetails()->page()->addMultiComboBox(0, 3, 1, 1, "02", "01", "06", "System"); //
    editDetails()->page()->addMultiComboBox(0, 4, 1, 1, "02", "01", "08", "System"); //
    editDetails()->page()->addMultiComboBox(0, 5, 1, 1, "02", "01", "0A", "System"); //
    editDetails()->page()->addMultiComboBox(0, 6, 1, 1, "02", "01", "0C", "System"); //
    editDetails()->page()->addMultiComboBox(0, 7, 1, 1, "02", "01", "0E", "System"); //
    editDetails()->page()->addMultiComboBox(0, 8, 1, 1, "02", "01", "10", "System"); //
    editDetails()->page()->addMultiComboBox(0, 9, 1, 1, "02", "01", "12", "System"); //
    editDetails()->page()->addMultiComboBox(0, 10, 1, 1, "02", "01", "14", "System"); //
    editDetails()->page()->addMultiComboBox(0, 11, 1, 1, "02", "01", "16", "System"); //
    editDetails()->page()->addMultiComboBox(0, 12, 1, 1, "02", "01", "18", "System"); //
    editDetails()->page()->addMultiComboBox(0, 13, 1, 1, "02", "01", "1A", "System"); //
    editDetails()->page()->addMultiComboBox(0, 14, 1, 1, "02", "01", "1C", "System"); //
    editDetails()->page()->addMultiComboBox(0, 15, 1, 1, "02", "01", "1E", "System"); // 16

    editDetails()->page()->addMultiComboBox(1, 0, 1, 1, "02", "01", "20", "System"); // 17
    editDetails()->page()->addMultiComboBox(1, 1, 1, 1, "02", "01", "22", "System"); //
    editDetails()->page()->addMultiComboBox(1, 2, 1, 1, "02", "01", "24", "System"); //
    editDetails()->page()->addMultiComboBox(1, 3, 1, 1, "02", "01", "26", "System"); //
    editDetails()->page()->addMultiComboBox(1, 4, 1, 1, "02", "01", "28", "System"); //
    editDetails()->page()->addMultiComboBox(1, 5, 1, 1, "02", "01", "2A", "System"); //
    editDetails()->page()->addMultiComboBox(1, 6, 1, 1, "02", "01", "2C", "System"); //
    editDetails()->page()->addMultiComboBox(1, 7, 1, 1, "02", "01", "2E", "System"); //
    editDetails()->page()->addMultiComboBox(1, 8, 1, 1, "02", "01", "30", "System"); //
    editDetails()->page()->addMultiComboBox(1, 9, 1, 1, "02", "01", "32", "System"); //
    editDetails()->page()->addMultiComboBox(1, 10, 1, 1, "02", "01", "34", "System"); //
    editDetails()->page()->addMultiComboBox(1, 11, 1, 1, "02", "01", "36", "System"); //
    editDetails()->page()->addMultiComboBox(1, 12, 1, 1, "02", "01", "38", "System"); //
    editDetails()->page()->addMultiComboBox(1, 13, 1, 1, "02", "01", "3A", "System"); //
    editDetails()->page()->addMultiComboBox(1, 14, 1, 1, "02", "01", "3C", "System"); //
    editDetails()->page()->addMultiComboBox(1, 15, 1, 1, "02", "01", "3E", "System"); // 32

    editDetails()->page()->addMultiComboBox(2, 0, 1, 1, "02", "01", "40", "System"); // 33
    editDetails()->page()->addMultiComboBox(2, 1, 1, 1, "02", "01", "42", "System"); //
    editDetails()->page()->addMultiComboBox(2, 2, 1, 1, "02", "01", "44", "System"); //
    editDetails()->page()->addMultiComboBox(2, 3, 1, 1, "02", "01", "46", "System"); //
    editDetails()->page()->addMultiComboBox(2, 4, 1, 1, "02", "01", "48", "System"); //
    editDetails()->page()->addMultiComboBox(2, 5, 1, 1, "02", "01", "4A", "System"); //
    editDetails()->page()->addMultiComboBox(2, 6, 1, 1, "02", "01", "4C", "System"); //
    editDetails()->page()->addMultiComboBox(2, 7, 1, 1, "02", "01", "4E", "System"); //
    editDetails()->page()->addMultiComboBox(2, 8, 1, 1, "02", "01", "50", "System"); //
    editDetails()->page()->addMultiComboBox(2, 9, 1, 1, "02", "01", "52", "System"); //
    editDetails()->page()->addMultiComboBox(2, 10, 1, 1, "02", "01", "54", "System"); //
    editDetails()->page()->addMultiComboBox(2, 11, 1, 1, "02", "01", "56", "System"); //
    editDetails()->page()->addMultiComboBox(2, 12, 1, 1, "02", "01", "58", "System"); //
    editDetails()->page()->addMultiComboBox(2, 13, 1, 1, "02", "01", "5A", "System"); //
    editDetails()->page()->addMultiComboBox(2, 14, 1, 1, "02", "01", "5C", "System"); //
    editDetails()->page()->addMultiComboBox(2, 15, 1, 1, "02", "01", "5E", "System"); // 48

    editDetails()->page()->addMultiComboBox(3, 0, 1, 1, "02", "01", "60", "System"); // 48
    editDetails()->page()->addMultiComboBox(3, 1, 1, 1, "02", "01", "62", "System"); //
    editDetails()->page()->addMultiComboBox(3, 2, 1, 1, "02", "01", "64", "System"); //
    editDetails()->page()->addMultiComboBox(3, 3, 1, 1, "02", "01", "66", "System"); //
    editDetails()->page()->addMultiComboBox(3, 4, 1, 1, "02", "01", "68", "System"); //
    editDetails()->page()->addMultiComboBox(3, 5, 1, 1, "02", "01", "6A", "System"); //
    editDetails()->page()->addMultiComboBox(3, 6, 1, 1, "02", "01", "6C", "System"); //
    editDetails()->page()->addMultiComboBox(3, 7, 1, 1, "02", "01", "6E", "System"); //
    editDetails()->page()->addMultiComboBox(3, 8, 1, 1, "02", "01", "70", "System"); //
    editDetails()->page()->addMultiComboBox(3, 9, 1, 1, "02", "01", "72", "System"); //
    editDetails()->page()->addMultiComboBox(3, 10, 1, 1, "02", "01", "74", "System"); //
    editDetails()->page()->addMultiComboBox(3, 11, 1, 1, "02", "01", "76", "System"); //
    editDetails()->page()->addMultiComboBox(3, 12, 1, 1, "02", "01", "78", "System"); //
    editDetails()->page()->addMultiComboBox(3, 13, 1, 1, "02", "01", "7A", "System"); //
    editDetails()->page()->addMultiComboBox(3, 14, 1, 1, "02", "01", "7C", "System"); //
    editDetails()->page()->addMultiComboBox(3, 15, 1, 1, "02", "01", "7E", "System"); // 64

    editDetails()->page()->addMultiComboBox(4, 0, 1, 1, "02", "02", "00", "System"); // 65
    editDetails()->page()->addMultiComboBox(4, 1, 1, 1, "02", "02", "02", "System"); //
    editDetails()->page()->addMultiComboBox(4, 2, 1, 1, "02", "02", "04", "System"); //
    editDetails()->page()->addMultiComboBox(4, 3, 1, 1, "02", "02", "06", "System"); //
    editDetails()->page()->addMultiComboBox(4, 4, 1, 1, "02", "02", "08", "System"); //
    editDetails()->page()->addMultiComboBox(4, 5, 1, 1, "02", "02", "0A", "System"); //
    editDetails()->page()->addMultiComboBox(4, 6, 1, 1, "02", "02", "0C", "System"); //
    editDetails()->page()->addMultiComboBox(4, 7, 1, 1, "02", "02", "0E", "System"); //
    editDetails()->page()->addMultiComboBox(4, 8, 1, 1, "02", "02", "10", "System"); //
    editDetails()->page()->addMultiComboBox(4, 9, 1, 1, "02", "02", "12", "System"); //
    editDetails()->page()->addMultiComboBox(4, 10, 1, 1, "02", "02", "14", "System"); //
    editDetails()->page()->addMultiComboBox(4, 11, 1, 1, "02", "02", "16", "System"); //
    editDetails()->page()->addMultiComboBox(4, 12, 1, 1, "02", "02", "18", "System"); //
    editDetails()->page()->addMultiComboBox(4, 13, 1, 1, "02", "02", "1A", "System"); //
    editDetails()->page()->addMultiComboBox(4, 14, 1, 1, "02", "02", "1C", "System"); //
    editDetails()->page()->addMultiComboBox(4, 15, 1, 1, "02", "02", "1E", "System"); // 80

    editDetails()->page()->addMultiComboBox(5, 0, 1, 1, "02", "02", "20", "System"); // 81
    editDetails()->page()->addMultiComboBox(5, 1, 1, 1, "02", "02", "22", "System"); //
    editDetails()->page()->addMultiComboBox(5, 2, 1, 1, "02", "02", "24", "System"); //
    editDetails()->page()->addMultiComboBox(5, 3, 1, 1, "02", "02", "26", "System"); //
    editDetails()->page()->addMultiComboBox(5, 4, 1, 1, "02", "02", "28", "System"); //
    editDetails()->page()->addMultiComboBox(5, 5, 1, 1, "02", "02", "2A", "System"); //
    editDetails()->page()->addMultiComboBox(5, 6, 1, 1, "02", "02", "2C", "System"); //
    editDetails()->page()->addMultiComboBox(5, 7, 1, 1, "02", "02", "2E", "System"); //
    editDetails()->page()->addMultiComboBox(5, 8, 1, 1, "02", "02", "30", "System"); //
    editDetails()->page()->addMultiComboBox(5, 9, 1, 1, "02", "02", "32", "System"); //
    editDetails()->page()->addMultiComboBox(5, 10, 1, 1, "02", "02", "34", "System"); //
    editDetails()->page()->addMultiComboBox(5, 11, 1, 1, "02", "02", "36", "System"); //
    editDetails()->page()->addMultiComboBox(5, 12, 1, 1, "02", "02", "38", "System"); //
    editDetails()->page()->addMultiComboBox(5, 13, 1, 1, "02", "02", "3A", "System"); //
    editDetails()->page()->addMultiComboBox(5, 14, 1, 1, "02", "02", "3C", "System"); //
    editDetails()->page()->addMultiComboBox(5, 15, 1, 1, "02", "02", "3E", "System"); // 96

    editDetails()->page()->addMultiComboBox(6, 0, 1, 1, "02", "02", "40", "System"); // 97
    editDetails()->page()->addMultiComboBox(6, 1, 1, 1, "02", "02", "42", "System"); //
    editDetails()->page()->addMultiComboBox(6, 2, 1, 1, "02", "02", "44", "System"); //
    editDetails()->page()->addMultiComboBox(6, 3, 1, 1, "02", "02", "46", "System"); //
    editDetails()->page()->addMultiComboBox(6, 4, 1, 1, "02", "02", "48", "System"); //
    editDetails()->page()->addMultiComboBox(6, 5, 1, 1, "02", "02", "4A", "System"); //
    editDetails()->page()->addMultiComboBox(6, 6, 1, 1, "02", "02", "4C", "System"); //
    editDetails()->page()->addMultiComboBox(6, 7, 1, 1, "02", "02", "4E", "System"); //
    editDetails()->page()->addMultiComboBox(6, 8, 1, 1, "02", "02", "50", "System"); //
    editDetails()->page()->addMultiComboBox(6, 9, 1, 1, "02", "02", "52", "System"); //
    editDetails()->page()->addMultiComboBox(6, 10, 1, 1, "02", "02", "54", "System"); //
    editDetails()->page()->addMultiComboBox(6, 11, 1, 1, "02", "02", "56", "System"); //
    editDetails()->page()->addMultiComboBox(6, 12, 1, 1, "02", "02", "58", "System"); //
    editDetails()->page()->addMultiComboBox(6, 13, 1, 1, "02", "02", "5A", "System"); //
    editDetails()->page()->addMultiComboBox(6, 14, 1, 1, "02", "02", "5C", "System"); //
    editDetails()->page()->addMultiComboBox(6, 15, 1, 1, "02", "02", "5E", "System"); // 112

    editDetails()->page()->addMultiComboBox(7, 0, 1, 1, "02", "02", "60", "System"); // 113
    editDetails()->page()->addMultiComboBox(7, 1, 1, 1, "02", "02", "62", "System"); //
    editDetails()->page()->addMultiComboBox(7, 2, 1, 1, "02", "02", "64", "System"); //
    editDetails()->page()->addMultiComboBox(7, 3, 1, 1, "02", "02", "66", "System"); //
    editDetails()->page()->addMultiComboBox(7, 4, 1, 1, "02", "02", "68", "System"); //
    editDetails()->page()->addMultiComboBox(7, 5, 1, 1, "02", "02", "6A", "System"); //
    editDetails()->page()->addMultiComboBox(7, 6, 1, 1, "02", "02", "6C", "System"); //
    editDetails()->page()->addMultiComboBox(7, 7, 1, 1, "02", "02", "6E", "System"); //
    editDetails()->page()->addMultiComboBox(7, 8, 1, 1, "02", "02", "70", "System"); //
    editDetails()->page()->addMultiComboBox(7, 9, 1, 1, "02", "02", "72", "System"); //
    editDetails()->page()->addMultiComboBox(7, 10, 1, 1, "02", "02", "74", "System"); //
    editDetails()->page()->addMultiComboBox(7, 11, 1, 1, "02", "02", "76", "System"); //
    editDetails()->page()->addMultiComboBox(7, 12, 1, 1, "02", "02", "78", "System"); //
    editDetails()->page()->addMultiComboBox(7, 13, 1, 1, "02", "02", "7A", "System"); //
    editDetails()->page()->addMultiComboBox(7, 14, 1, 1, "02", "02", "7C", "System"); //
    editDetails()->page()->addMultiComboBox(7, 15, 1, 1, "02", "02", "7E", "System"); // 128
*/
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->addPage("02", "00", "7F", "01", "System");

    editDetails()->page()->newGroupBox("MIDI PROGRAM TABLE - BANK 1.            Caution: Changes are automatically written to the GT-100.");
    editDetails()->page()->addMultiComboBox(0, 0, 1, 1, "02", "03", "00", "System"); // 1
  /*  editDetails()->page()->addMultiComboBox(0, 1, 1, 1, "02", "03", "02", "System"); //
    editDetails()->page()->addMultiComboBox(0, 2, 1, 1, "02", "03", "04", "System"); //
    editDetails()->page()->addMultiComboBox(0, 3, 1, 1, "02", "03", "06", "System"); //
    editDetails()->page()->addMultiComboBox(0, 4, 1, 1, "02", "03", "08", "System"); //
    editDetails()->page()->addMultiComboBox(0, 5, 1, 1, "02", "03", "0A", "System"); //
    editDetails()->page()->addMultiComboBox(0, 6, 1, 1, "02", "03", "0C", "System"); //
    editDetails()->page()->addMultiComboBox(0, 7, 1, 1, "02", "03", "0E", "System"); //
    editDetails()->page()->addMultiComboBox(0, 8, 1, 1, "02", "03", "10", "System"); //
    editDetails()->page()->addMultiComboBox(0, 9, 1, 1, "02", "03", "12", "System"); //
    editDetails()->page()->addMultiComboBox(0, 10, 1, 1, "02", "03", "14", "System"); //
    editDetails()->page()->addMultiComboBox(0, 11, 1, 1, "02", "03", "16", "System"); //
    editDetails()->page()->addMultiComboBox(0, 12, 1, 1, "02", "03", "18", "System"); //
    editDetails()->page()->addMultiComboBox(0, 13, 1, 1, "02", "03", "1A", "System"); //
    editDetails()->page()->addMultiComboBox(0, 14, 1, 1, "02", "03", "1C", "System"); //
    editDetails()->page()->addMultiComboBox(0, 15, 1, 1, "02", "03", "1E", "System"); // 16

    editDetails()->page()->addMultiComboBox(1, 0, 1, 1, "02", "03", "20", "System"); // 17
    editDetails()->page()->addMultiComboBox(1, 1, 1, 1, "02", "03", "22", "System"); //
    editDetails()->page()->addMultiComboBox(1, 2, 1, 1, "02", "03", "24", "System"); //
    editDetails()->page()->addMultiComboBox(1, 3, 1, 1, "02", "03", "26", "System"); //
    editDetails()->page()->addMultiComboBox(1, 4, 1, 1, "02", "03", "28", "System"); //
    editDetails()->page()->addMultiComboBox(1, 5, 1, 1, "02", "03", "2A", "System"); //
    editDetails()->page()->addMultiComboBox(1, 6, 1, 1, "02", "03", "2C", "System"); //
    editDetails()->page()->addMultiComboBox(1, 7, 1, 1, "02", "03", "2E", "System"); //
    editDetails()->page()->addMultiComboBox(1, 8, 1, 1, "02", "03", "30", "System"); //
    editDetails()->page()->addMultiComboBox(1, 9, 1, 1, "02", "03", "32", "System"); //
    editDetails()->page()->addMultiComboBox(1, 10, 1, 1, "02", "03", "34", "System"); //
    editDetails()->page()->addMultiComboBox(1, 11, 1, 1, "02", "03", "36", "System"); //
    editDetails()->page()->addMultiComboBox(1, 12, 1, 1, "02", "03", "38", "System"); //
    editDetails()->page()->addMultiComboBox(1, 13, 1, 1, "02", "03", "3A", "System"); //
    editDetails()->page()->addMultiComboBox(1, 14, 1, 1, "02", "03", "3C", "System"); //
    editDetails()->page()->addMultiComboBox(1, 15, 1, 1, "02", "03", "3E", "System"); // 32

    editDetails()->page()->addMultiComboBox(2, 0, 1, 1, "02", "03", "40", "System"); // 33
    editDetails()->page()->addMultiComboBox(2, 1, 1, 1, "02", "03", "42", "System"); //
    editDetails()->page()->addMultiComboBox(2, 2, 1, 1, "02", "03", "44", "System"); //
    editDetails()->page()->addMultiComboBox(2, 3, 1, 1, "02", "03", "46", "System"); //
    editDetails()->page()->addMultiComboBox(2, 4, 1, 1, "02", "03", "48", "System"); //
    editDetails()->page()->addMultiComboBox(2, 5, 1, 1, "02", "03", "4A", "System"); //
    editDetails()->page()->addMultiComboBox(2, 6, 1, 1, "02", "03", "4C", "System"); //
    editDetails()->page()->addMultiComboBox(2, 7, 1, 1, "02", "03", "4E", "System"); //
    editDetails()->page()->addMultiComboBox(2, 8, 1, 1, "02", "03", "50", "System"); //
    editDetails()->page()->addMultiComboBox(2, 9, 1, 1, "02", "03", "52", "System"); //
    editDetails()->page()->addMultiComboBox(2, 10, 1, 1, "02", "03", "54", "System"); //
    editDetails()->page()->addMultiComboBox(2, 11, 1, 1, "02", "03", "56", "System"); //
    editDetails()->page()->addMultiComboBox(2, 12, 1, 1, "02", "03", "58", "System"); //
    editDetails()->page()->addMultiComboBox(2, 13, 1, 1, "02", "03", "5A", "System"); //
    editDetails()->page()->addMultiComboBox(2, 14, 1, 1, "02", "03", "5C", "System"); //
    editDetails()->page()->addMultiComboBox(2, 15, 1, 1, "02", "03", "5E", "System"); // 48

    editDetails()->page()->addMultiComboBox(3, 0, 1, 1, "02", "03", "60", "System"); // 48
    editDetails()->page()->addMultiComboBox(3, 1, 1, 1, "02", "03", "62", "System"); //
    editDetails()->page()->addMultiComboBox(3, 2, 1, 1, "02", "03", "64", "System"); //
    editDetails()->page()->addMultiComboBox(3, 3, 1, 1, "02", "03", "66", "System"); //
    editDetails()->page()->addMultiComboBox(3, 4, 1, 1, "02", "03", "68", "System"); //
    editDetails()->page()->addMultiComboBox(3, 5, 1, 1, "02", "03", "6A", "System"); //
    editDetails()->page()->addMultiComboBox(3, 6, 1, 1, "02", "03", "6C", "System"); //
    editDetails()->page()->addMultiComboBox(3, 7, 1, 1, "02", "03", "6E", "System"); //
    editDetails()->page()->addMultiComboBox(3, 8, 1, 1, "02", "03", "70", "System"); //
    editDetails()->page()->addMultiComboBox(3, 9, 1, 1, "02", "03", "72", "System"); //
    editDetails()->page()->addMultiComboBox(3, 10, 1, 1, "02", "03", "74", "System"); //
    editDetails()->page()->addMultiComboBox(3, 11, 1, 1, "02", "03", "76", "System"); //
    editDetails()->page()->addMultiComboBox(3, 12, 1, 1, "02", "03", "78", "System"); //
    editDetails()->page()->addMultiComboBox(3, 13, 1, 1, "02", "03", "7A", "System"); //
    editDetails()->page()->addMultiComboBox(3, 14, 1, 1, "02", "03", "7C", "System"); //
    editDetails()->page()->addMultiComboBox(3, 15, 1, 1, "02", "03", "7E", "System"); // 64

    editDetails()->page()->addMultiComboBox(4, 0, 1, 1, "02", "04", "00", "System"); // 65
    editDetails()->page()->addMultiComboBox(4, 1, 1, 1, "02", "04", "02", "System"); //
    editDetails()->page()->addMultiComboBox(4, 2, 1, 1, "02", "04", "04", "System"); //
    editDetails()->page()->addMultiComboBox(4, 3, 1, 1, "02", "04", "06", "System"); //
    editDetails()->page()->addMultiComboBox(4, 4, 1, 1, "02", "04", "08", "System"); //
    editDetails()->page()->addMultiComboBox(4, 5, 1, 1, "02", "04", "0A", "System"); //
    editDetails()->page()->addMultiComboBox(4, 6, 1, 1, "02", "04", "0C", "System"); //
    editDetails()->page()->addMultiComboBox(4, 7, 1, 1, "02", "04", "0E", "System"); //
    editDetails()->page()->addMultiComboBox(4, 8, 1, 1, "02", "04", "10", "System"); //
    editDetails()->page()->addMultiComboBox(4, 9, 1, 1, "02", "04", "12", "System"); //
    editDetails()->page()->addMultiComboBox(4, 10, 1, 1, "02", "04", "14", "System"); //
    editDetails()->page()->addMultiComboBox(4, 11, 1, 1, "02", "04", "16", "System"); //
    editDetails()->page()->addMultiComboBox(4, 12, 1, 1, "02", "04", "18", "System"); //
    editDetails()->page()->addMultiComboBox(4, 13, 1, 1, "02", "04", "1A", "System"); //
    editDetails()->page()->addMultiComboBox(4, 14, 1, 1, "02", "04", "1C", "System"); //
    editDetails()->page()->addMultiComboBox(4, 15, 1, 1, "02", "04", "1E", "System"); // 80

    editDetails()->page()->addMultiComboBox(5, 0, 1, 1, "02", "04", "20", "System"); // 81
    editDetails()->page()->addMultiComboBox(5, 1, 1, 1, "02", "04", "22", "System"); //
    editDetails()->page()->addMultiComboBox(5, 2, 1, 1, "02", "04", "24", "System"); //
    editDetails()->page()->addMultiComboBox(5, 3, 1, 1, "02", "04", "26", "System"); //
    editDetails()->page()->addMultiComboBox(5, 4, 1, 1, "02", "04", "28", "System"); //
    editDetails()->page()->addMultiComboBox(5, 5, 1, 1, "02", "04", "2A", "System"); //
    editDetails()->page()->addMultiComboBox(5, 6, 1, 1, "02", "04", "2C", "System"); //
    editDetails()->page()->addMultiComboBox(5, 7, 1, 1, "02", "04", "2E", "System"); //
    editDetails()->page()->addMultiComboBox(5, 8, 1, 1, "02", "04", "30", "System"); //
    editDetails()->page()->addMultiComboBox(5, 9, 1, 1, "02", "04", "32", "System"); //
    editDetails()->page()->addMultiComboBox(5, 10, 1, 1, "02", "04", "34", "System"); //
    editDetails()->page()->addMultiComboBox(5, 11, 1, 1, "02", "04", "36", "System"); //
    editDetails()->page()->addMultiComboBox(5, 12, 1, 1, "02", "04", "38", "System"); //
    editDetails()->page()->addMultiComboBox(5, 13, 1, 1, "02", "04", "3A", "System"); //
    editDetails()->page()->addMultiComboBox(5, 14, 1, 1, "02", "04", "3C", "System"); //
    editDetails()->page()->addMultiComboBox(5, 15, 1, 1, "02", "04", "3E", "System"); // 96

    editDetails()->page()->addMultiComboBox(6, 0, 1, 1, "02", "04", "40", "System"); // 97
    editDetails()->page()->addMultiComboBox(6, 1, 1, 1, "02", "04", "42", "System"); //
    editDetails()->page()->addMultiComboBox(6, 2, 1, 1, "02", "04", "44", "System"); //
    editDetails()->page()->addMultiComboBox(6, 3, 1, 1, "02", "04", "46", "System"); //
    editDetails()->page()->addMultiComboBox(6, 4, 1, 1, "02", "04", "48", "System"); //
    editDetails()->page()->addMultiComboBox(6, 5, 1, 1, "02", "04", "4A", "System"); //
    editDetails()->page()->addMultiComboBox(6, 6, 1, 1, "02", "04", "4C", "System"); //
    editDetails()->page()->addMultiComboBox(6, 7, 1, 1, "02", "04", "4E", "System"); //
    editDetails()->page()->addMultiComboBox(6, 8, 1, 1, "02", "04", "50", "System"); //
    editDetails()->page()->addMultiComboBox(6, 9, 1, 1, "02", "04", "52", "System"); //
    editDetails()->page()->addMultiComboBox(6, 10, 1, 1, "02", "04", "54", "System"); //
    editDetails()->page()->addMultiComboBox(6, 11, 1, 1, "02", "04", "56", "System"); //
    editDetails()->page()->addMultiComboBox(6, 12, 1, 1, "02", "04", "58", "System"); //
    editDetails()->page()->addMultiComboBox(6, 13, 1, 1, "02", "04", "5A", "System"); //
    editDetails()->page()->addMultiComboBox(6, 14, 1, 1, "02", "04", "5C", "System"); //
    editDetails()->page()->addMultiComboBox(6, 15, 1, 1, "02", "04", "5E", "System"); // 112

    editDetails()->page()->addMultiComboBox(7, 0, 1, 1, "02", "04", "60", "System"); // 113
    editDetails()->page()->addMultiComboBox(7, 1, 1, 1, "02", "04", "62", "System"); //
    editDetails()->page()->addMultiComboBox(7, 2, 1, 1, "02", "04", "64", "System"); //
    editDetails()->page()->addMultiComboBox(7, 3, 1, 1, "02", "04", "66", "System"); //
    editDetails()->page()->addMultiComboBox(7, 4, 1, 1, "02", "04", "68", "System"); //
    editDetails()->page()->addMultiComboBox(7, 5, 1, 1, "02", "04", "6A", "System"); //
    editDetails()->page()->addMultiComboBox(7, 6, 1, 1, "02", "04", "6C", "System"); //
    editDetails()->page()->addMultiComboBox(7, 7, 1, 1, "02", "04", "6E", "System"); //
    editDetails()->page()->addMultiComboBox(7, 8, 1, 1, "02", "04", "70", "System"); //
    editDetails()->page()->addMultiComboBox(7, 9, 1, 1, "02", "04", "72", "System"); //
    editDetails()->page()->addMultiComboBox(7, 10, 1, 1, "02", "04", "74", "System"); //
    editDetails()->page()->addMultiComboBox(7, 11, 1, 1, "02", "04", "76", "System"); //
    editDetails()->page()->addMultiComboBox(7, 12, 1, 1, "02", "04", "78", "System"); //
    editDetails()->page()->addMultiComboBox(7, 13, 1, 1, "02", "04", "7A", "System"); //
    editDetails()->page()->addMultiComboBox(7, 14, 1, 1, "02", "04", "7C", "System"); //
    editDetails()->page()->addMultiComboBox(7, 15, 1, 1, "02", "04", "7E", "System"); // 128
*/
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->addPage("02", "00", "7F", "02", "System");

    editDetails()->page()->newGroupBox("MIDI PROGRAM TABLE - BANK 2.            Caution: Changes are automatically written to the GT-100.");
    editDetails()->page()->addMultiComboBox(0, 0, 1, 1, "02", "05", "00", "System"); // 1
    /*editDetails()->page()->addMultiComboBox(0, 1, 1, 1, "02", "05", "02", "System"); //
    editDetails()->page()->addMultiComboBox(0, 2, 1, 1, "02", "05", "04", "System"); //
    editDetails()->page()->addMultiComboBox(0, 3, 1, 1, "02", "05", "06", "System"); //
    editDetails()->page()->addMultiComboBox(0, 4, 1, 1, "02", "05", "08", "System"); //
    editDetails()->page()->addMultiComboBox(0, 5, 1, 1, "02", "05", "0A", "System"); //
    editDetails()->page()->addMultiComboBox(0, 6, 1, 1, "02", "05", "0C", "System"); //
    editDetails()->page()->addMultiComboBox(0, 7, 1, 1, "02", "05", "0E", "System"); //
    editDetails()->page()->addMultiComboBox(0, 8, 1, 1, "02", "05", "10", "System"); //
    editDetails()->page()->addMultiComboBox(0, 9, 1, 1, "02", "05", "12", "System"); //
    editDetails()->page()->addMultiComboBox(0, 10, 1, 1, "02", "05", "14", "System"); //
    editDetails()->page()->addMultiComboBox(0, 11, 1, 1, "02", "05", "16", "System"); //
    editDetails()->page()->addMultiComboBox(0, 12, 1, 1, "02", "05", "18", "System"); //
    editDetails()->page()->addMultiComboBox(0, 13, 1, 1, "02", "05", "1A", "System"); //
    editDetails()->page()->addMultiComboBox(0, 14, 1, 1, "02", "05", "1C", "System"); //
    editDetails()->page()->addMultiComboBox(0, 15, 1, 1, "02", "05", "1E", "System"); // 16

    editDetails()->page()->addMultiComboBox(1, 0, 1, 1, "02", "05", "20", "System"); // 17
    editDetails()->page()->addMultiComboBox(1, 1, 1, 1, "02", "05", "22", "System"); //
    editDetails()->page()->addMultiComboBox(1, 2, 1, 1, "02", "05", "24", "System"); //
    editDetails()->page()->addMultiComboBox(1, 3, 1, 1, "02", "05", "26", "System"); //
    editDetails()->page()->addMultiComboBox(1, 4, 1, 1, "02", "05", "28", "System"); //
    editDetails()->page()->addMultiComboBox(1, 5, 1, 1, "02", "05", "2A", "System"); //
    editDetails()->page()->addMultiComboBox(1, 6, 1, 1, "02", "05", "2C", "System"); //
    editDetails()->page()->addMultiComboBox(1, 7, 1, 1, "02", "05", "2E", "System"); //
    editDetails()->page()->addMultiComboBox(1, 8, 1, 1, "02", "05", "30", "System"); //
    editDetails()->page()->addMultiComboBox(1, 9, 1, 1, "02", "05", "32", "System"); //
    editDetails()->page()->addMultiComboBox(1, 10, 1, 1, "02", "05", "34", "System"); //
    editDetails()->page()->addMultiComboBox(1, 11, 1, 1, "02", "05", "36", "System"); //
    editDetails()->page()->addMultiComboBox(1, 12, 1, 1, "02", "05", "38", "System"); //
    editDetails()->page()->addMultiComboBox(1, 13, 1, 1, "02", "05", "3A", "System"); //
    editDetails()->page()->addMultiComboBox(1, 14, 1, 1, "02", "05", "3C", "System"); //
    editDetails()->page()->addMultiComboBox(1, 15, 1, 1, "02", "05", "3E", "System"); // 32

    editDetails()->page()->addMultiComboBox(2, 0, 1, 1, "02", "05", "40", "System"); // 33
    editDetails()->page()->addMultiComboBox(2, 1, 1, 1, "02", "05", "42", "System"); //
    editDetails()->page()->addMultiComboBox(2, 2, 1, 1, "02", "05", "44", "System"); //
    editDetails()->page()->addMultiComboBox(2, 3, 1, 1, "02", "05", "46", "System"); //
    editDetails()->page()->addMultiComboBox(2, 4, 1, 1, "02", "05", "48", "System"); //
    editDetails()->page()->addMultiComboBox(2, 5, 1, 1, "02", "05", "4A", "System"); //
    editDetails()->page()->addMultiComboBox(2, 6, 1, 1, "02", "05", "4C", "System"); //
    editDetails()->page()->addMultiComboBox(2, 7, 1, 1, "02", "05", "4E", "System"); //
    editDetails()->page()->addMultiComboBox(2, 8, 1, 1, "02", "05", "50", "System"); //
    editDetails()->page()->addMultiComboBox(2, 9, 1, 1, "02", "05", "52", "System"); //
    editDetails()->page()->addMultiComboBox(2, 10, 1, 1, "02", "05", "54", "System"); //
    editDetails()->page()->addMultiComboBox(2, 11, 1, 1, "02", "05", "56", "System"); //
    editDetails()->page()->addMultiComboBox(2, 12, 1, 1, "02", "05", "58", "System"); //
    editDetails()->page()->addMultiComboBox(2, 13, 1, 1, "02", "05", "5A", "System"); //
    editDetails()->page()->addMultiComboBox(2, 14, 1, 1, "02", "05", "5C", "System"); //
    editDetails()->page()->addMultiComboBox(2, 15, 1, 1, "02", "05", "5E", "System"); // 48

    editDetails()->page()->addMultiComboBox(3, 0, 1, 1, "02", "05", "60", "System"); // 48
    editDetails()->page()->addMultiComboBox(3, 1, 1, 1, "02", "05", "62", "System"); //
    editDetails()->page()->addMultiComboBox(3, 2, 1, 1, "02", "05", "64", "System"); //
    editDetails()->page()->addMultiComboBox(3, 3, 1, 1, "02", "05", "66", "System"); //
    editDetails()->page()->addMultiComboBox(3, 4, 1, 1, "02", "05", "68", "System"); //
    editDetails()->page()->addMultiComboBox(3, 5, 1, 1, "02", "05", "6A", "System"); //
    editDetails()->page()->addMultiComboBox(3, 6, 1, 1, "02", "05", "6C", "System"); //
    editDetails()->page()->addMultiComboBox(3, 7, 1, 1, "02", "05", "6E", "System"); //
    editDetails()->page()->addMultiComboBox(3, 8, 1, 1, "02", "05", "70", "System"); //
    editDetails()->page()->addMultiComboBox(3, 9, 1, 1, "02", "05", "72", "System"); //
    editDetails()->page()->addMultiComboBox(3, 10, 1, 1, "02", "05", "74", "System"); //
    editDetails()->page()->addMultiComboBox(3, 11, 1, 1, "02", "05", "76", "System"); //
    editDetails()->page()->addMultiComboBox(3, 12, 1, 1, "02", "05", "78", "System"); //
    editDetails()->page()->addMultiComboBox(3, 13, 1, 1, "02", "05", "7A", "System"); //
    editDetails()->page()->addMultiComboBox(3, 14, 1, 1, "02", "05", "7C", "System"); //
    editDetails()->page()->addMultiComboBox(3, 15, 1, 1, "02", "05", "7E", "System"); // 64

    editDetails()->page()->addMultiComboBox(4, 0, 1, 1, "02", "06", "00", "System"); // 65
    editDetails()->page()->addMultiComboBox(4, 1, 1, 1, "02", "06", "02", "System"); //
    editDetails()->page()->addMultiComboBox(4, 2, 1, 1, "02", "06", "04", "System"); //
    editDetails()->page()->addMultiComboBox(4, 3, 1, 1, "02", "06", "06", "System"); //
    editDetails()->page()->addMultiComboBox(4, 4, 1, 1, "02", "06", "08", "System"); //
    editDetails()->page()->addMultiComboBox(4, 5, 1, 1, "02", "06", "0A", "System"); //
    editDetails()->page()->addMultiComboBox(4, 6, 1, 1, "02", "06", "0C", "System"); //
    editDetails()->page()->addMultiComboBox(4, 7, 1, 1, "02", "06", "0E", "System"); //
    editDetails()->page()->addMultiComboBox(4, 8, 1, 1, "02", "06", "10", "System"); //
    editDetails()->page()->addMultiComboBox(4, 9, 1, 1, "02", "06", "12", "System"); //
    editDetails()->page()->addMultiComboBox(4, 10, 1, 1, "02", "06", "14", "System"); //
    editDetails()->page()->addMultiComboBox(4, 11, 1, 1, "02", "06", "16", "System"); //
    editDetails()->page()->addMultiComboBox(4, 12, 1, 1, "02", "06", "18", "System"); //
    editDetails()->page()->addMultiComboBox(4, 13, 1, 1, "02", "06", "1A", "System"); //
    editDetails()->page()->addMultiComboBox(4, 14, 1, 1, "02", "06", "1C", "System"); //
    editDetails()->page()->addMultiComboBox(4, 15, 1, 1, "02", "06", "1E", "System"); // 80

    editDetails()->page()->addMultiComboBox(5, 0, 1, 1, "02", "06", "20", "System"); // 81
    editDetails()->page()->addMultiComboBox(5, 1, 1, 1, "02", "06", "22", "System"); //
    editDetails()->page()->addMultiComboBox(5, 2, 1, 1, "02", "06", "24", "System"); //
    editDetails()->page()->addMultiComboBox(5, 3, 1, 1, "02", "06", "26", "System"); //
    editDetails()->page()->addMultiComboBox(5, 4, 1, 1, "02", "06", "28", "System"); //
    editDetails()->page()->addMultiComboBox(5, 5, 1, 1, "02", "06", "2A", "System"); //
    editDetails()->page()->addMultiComboBox(5, 6, 1, 1, "02", "06", "2C", "System"); //
    editDetails()->page()->addMultiComboBox(5, 7, 1, 1, "02", "06", "2E", "System"); //
    editDetails()->page()->addMultiComboBox(5, 8, 1, 1, "02", "06", "30", "System"); //
    editDetails()->page()->addMultiComboBox(5, 9, 1, 1, "02", "06", "32", "System"); //
    editDetails()->page()->addMultiComboBox(5, 10, 1, 1, "02", "06", "34", "System"); //
    editDetails()->page()->addMultiComboBox(5, 11, 1, 1, "02", "06", "36", "System"); //
    editDetails()->page()->addMultiComboBox(5, 12, 1, 1, "02", "06", "38", "System"); //
    editDetails()->page()->addMultiComboBox(5, 13, 1, 1, "02", "06", "3A", "System"); //
    editDetails()->page()->addMultiComboBox(5, 14, 1, 1, "02", "06", "3C", "System"); //
    editDetails()->page()->addMultiComboBox(5, 15, 1, 1, "02", "06", "3E", "System"); // 96

    editDetails()->page()->addMultiComboBox(6, 0, 1, 1, "02", "06", "40", "System"); // 97
    editDetails()->page()->addMultiComboBox(6, 1, 1, 1, "02", "06", "42", "System"); //
    editDetails()->page()->addMultiComboBox(6, 2, 1, 1, "02", "06", "44", "System"); //
    editDetails()->page()->addMultiComboBox(6, 3, 1, 1, "02", "06", "46", "System"); //
    editDetails()->page()->addMultiComboBox(6, 4, 1, 1, "02", "06", "48", "System"); //
    editDetails()->page()->addMultiComboBox(6, 5, 1, 1, "02", "06", "4A", "System"); //
    editDetails()->page()->addMultiComboBox(6, 6, 1, 1, "02", "06", "4C", "System"); //
    editDetails()->page()->addMultiComboBox(6, 7, 1, 1, "02", "06", "4E", "System"); //
    editDetails()->page()->addMultiComboBox(6, 8, 1, 1, "02", "06", "50", "System"); //
    editDetails()->page()->addMultiComboBox(6, 9, 1, 1, "02", "06", "52", "System"); //
    editDetails()->page()->addMultiComboBox(6, 10, 1, 1, "02", "06", "54", "System"); //
    editDetails()->page()->addMultiComboBox(6, 11, 1, 1, "02", "06", "56", "System"); //
    editDetails()->page()->addMultiComboBox(6, 12, 1, 1, "02", "06", "58", "System"); //
    editDetails()->page()->addMultiComboBox(6, 13, 1, 1, "02", "06", "5A", "System"); //
    editDetails()->page()->addMultiComboBox(6, 14, 1, 1, "02", "06", "5C", "System"); //
    editDetails()->page()->addMultiComboBox(6, 15, 1, 1, "02", "06", "5E", "System"); // 112

    editDetails()->page()->addMultiComboBox(7, 0, 1, 1, "02", "06", "60", "System"); // 113
    editDetails()->page()->addMultiComboBox(7, 1, 1, 1, "02", "06", "62", "System"); //
    editDetails()->page()->addMultiComboBox(7, 2, 1, 1, "02", "06", "64", "System"); //
    editDetails()->page()->addMultiComboBox(7, 3, 1, 1, "02", "06", "66", "System"); //
    editDetails()->page()->addMultiComboBox(7, 4, 1, 1, "02", "06", "68", "System"); //
    editDetails()->page()->addMultiComboBox(7, 5, 1, 1, "02", "06", "6A", "System"); //
    editDetails()->page()->addMultiComboBox(7, 6, 1, 1, "02", "06", "6C", "System"); //
    editDetails()->page()->addMultiComboBox(7, 7, 1, 1, "02", "06", "6E", "System"); //
    editDetails()->page()->addMultiComboBox(7, 8, 1, 1, "02", "06", "70", "System"); //
    editDetails()->page()->addMultiComboBox(7, 9, 1, 1, "02", "06", "72", "System"); //
    editDetails()->page()->addMultiComboBox(7, 10, 1, 1, "02", "06", "74", "System"); //
    editDetails()->page()->addMultiComboBox(7, 11, 1, 1, "02", "06", "76", "System"); //
    editDetails()->page()->addMultiComboBox(7, 12, 1, 1, "02", "06", "78", "System"); //
    editDetails()->page()->addMultiComboBox(7, 13, 1, 1, "02", "06", "7A", "System"); //
    editDetails()->page()->addMultiComboBox(7, 14, 1, 1, "02", "06", "7C", "System"); //
    editDetails()->page()->addMultiComboBox(7, 15, 1, 1, "02", "06", "7E", "System"); // 128
*/
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->addPage("02", "00", "7F", "03", "System");

    editDetails()->page()->newGroupBox("MIDI PROGRAM TABLE - BANK 3.            Caution: Changes are automatically written to the GT-100.");
    editDetails()->page()->addMultiComboBox(0, 0, 1, 1, "02", "07", "00", "System"); // 1
    /*editDetails()->page()->addMultiComboBox(0, 1, 1, 1, "02", "07", "02", "System"); //
    editDetails()->page()->addMultiComboBox(0, 2, 1, 1, "02", "07", "04", "System"); //
    editDetails()->page()->addMultiComboBox(0, 3, 1, 1, "02", "07", "06", "System"); //
    editDetails()->page()->addMultiComboBox(0, 4, 1, 1, "02", "07", "08", "System"); //
    editDetails()->page()->addMultiComboBox(0, 5, 1, 1, "02", "07", "0A", "System"); //
    editDetails()->page()->addMultiComboBox(0, 6, 1, 1, "02", "07", "0C", "System"); //
    editDetails()->page()->addMultiComboBox(0, 7, 1, 1, "02", "07", "0E", "System"); //
    editDetails()->page()->addMultiComboBox(0, 8, 1, 1, "02", "07", "10", "System"); //
    editDetails()->page()->addMultiComboBox(0, 9, 1, 1, "02", "07", "12", "System"); //
    editDetails()->page()->addMultiComboBox(0, 10, 1, 1, "02", "07", "14", "System"); //
    editDetails()->page()->addMultiComboBox(0, 11, 1, 1, "02", "07", "16", "System"); //
    editDetails()->page()->addMultiComboBox(0, 12, 1, 1, "02", "07", "18", "System"); //
    editDetails()->page()->addMultiComboBox(0, 13, 1, 1, "02", "07", "1A", "System"); //
    editDetails()->page()->addMultiComboBox(0, 14, 1, 1, "02", "07", "1C", "System"); //
    editDetails()->page()->addMultiComboBox(0, 15, 1, 1, "02", "07", "1E", "System"); // 16

    editDetails()->page()->addMultiComboBox(1, 0, 1, 1, "02", "07", "20", "System"); // 17
    editDetails()->page()->addMultiComboBox(1, 1, 1, 1, "02", "07", "22", "System"); //
    editDetails()->page()->addMultiComboBox(1, 2, 1, 1, "02", "07", "24", "System"); //
    editDetails()->page()->addMultiComboBox(1, 3, 1, 1, "02", "07", "26", "System"); //
    editDetails()->page()->addMultiComboBox(1, 4, 1, 1, "02", "07", "28", "System"); //
    editDetails()->page()->addMultiComboBox(1, 5, 1, 1, "02", "07", "2A", "System"); //
    editDetails()->page()->addMultiComboBox(1, 6, 1, 1, "02", "07", "2C", "System"); //
    editDetails()->page()->addMultiComboBox(1, 7, 1, 1, "02", "07", "2E", "System"); //
    editDetails()->page()->addMultiComboBox(1, 8, 1, 1, "02", "07", "30", "System"); //
    editDetails()->page()->addMultiComboBox(1, 9, 1, 1, "02", "07", "32", "System"); //
    editDetails()->page()->addMultiComboBox(1, 10, 1, 1, "02", "07", "34", "System"); //
    editDetails()->page()->addMultiComboBox(1, 11, 1, 1, "02", "07", "36", "System"); //
    editDetails()->page()->addMultiComboBox(1, 12, 1, 1, "02", "07", "38", "System"); //
    editDetails()->page()->addMultiComboBox(1, 13, 1, 1, "02", "07", "3A", "System"); //
    editDetails()->page()->addMultiComboBox(1, 14, 1, 1, "02", "07", "3C", "System"); //
    editDetails()->page()->addMultiComboBox(1, 15, 1, 1, "02", "07", "3E", "System"); // 32

    editDetails()->page()->addMultiComboBox(2, 0, 1, 1, "02", "07", "40", "System"); // 33
    editDetails()->page()->addMultiComboBox(2, 1, 1, 1, "02", "07", "42", "System"); //
    editDetails()->page()->addMultiComboBox(2, 2, 1, 1, "02", "07", "44", "System"); //
    editDetails()->page()->addMultiComboBox(2, 3, 1, 1, "02", "07", "46", "System"); //
    editDetails()->page()->addMultiComboBox(2, 4, 1, 1, "02", "07", "48", "System"); //
    editDetails()->page()->addMultiComboBox(2, 5, 1, 1, "02", "07", "4A", "System"); //
    editDetails()->page()->addMultiComboBox(2, 6, 1, 1, "02", "07", "4C", "System"); //
    editDetails()->page()->addMultiComboBox(2, 7, 1, 1, "02", "07", "4E", "System"); //
    editDetails()->page()->addMultiComboBox(2, 8, 1, 1, "02", "07", "50", "System"); //
    editDetails()->page()->addMultiComboBox(2, 9, 1, 1, "02", "07", "52", "System"); //
    editDetails()->page()->addMultiComboBox(2, 10, 1, 1, "02", "07", "54", "System"); //
    editDetails()->page()->addMultiComboBox(2, 11, 1, 1, "02", "07", "56", "System"); //
    editDetails()->page()->addMultiComboBox(2, 12, 1, 1, "02", "07", "58", "System"); //
    editDetails()->page()->addMultiComboBox(2, 13, 1, 1, "02", "07", "5A", "System"); //
    editDetails()->page()->addMultiComboBox(2, 14, 1, 1, "02", "07", "5C", "System"); //
    editDetails()->page()->addMultiComboBox(2, 15, 1, 1, "02", "07", "5E", "System"); // 48

    editDetails()->page()->addMultiComboBox(3, 0, 1, 1, "02", "07", "60", "System"); // 48
    editDetails()->page()->addMultiComboBox(3, 1, 1, 1, "02", "07", "62", "System"); //
    editDetails()->page()->addMultiComboBox(3, 2, 1, 1, "02", "07", "64", "System"); //
    editDetails()->page()->addMultiComboBox(3, 3, 1, 1, "02", "07", "66", "System"); //
    editDetails()->page()->addMultiComboBox(3, 4, 1, 1, "02", "07", "68", "System"); //
    editDetails()->page()->addMultiComboBox(3, 5, 1, 1, "02", "07", "6A", "System"); //
    editDetails()->page()->addMultiComboBox(3, 6, 1, 1, "02", "07", "6C", "System"); //
    editDetails()->page()->addMultiComboBox(3, 7, 1, 1, "02", "07", "6E", "System"); //
    editDetails()->page()->addMultiComboBox(3, 8, 1, 1, "02", "07", "70", "System"); //
    editDetails()->page()->addMultiComboBox(3, 9, 1, 1, "02", "07", "72", "System"); //
    editDetails()->page()->addMultiComboBox(3, 10, 1, 1, "02", "07", "74", "System"); //
    editDetails()->page()->addMultiComboBox(3, 11, 1, 1, "02", "07", "76", "System"); //
    editDetails()->page()->addMultiComboBox(3, 12, 1, 1, "02", "07", "78", "System"); //
    editDetails()->page()->addMultiComboBox(3, 13, 1, 1, "02", "07", "7A", "System"); //
    editDetails()->page()->addMultiComboBox(3, 14, 1, 1, "02", "07", "7C", "System"); //
    editDetails()->page()->addMultiComboBox(3, 15, 1, 1, "02", "07", "7E", "System"); // 64

    editDetails()->page()->addMultiComboBox(4, 0, 1, 1, "02", "08", "00", "System"); // 65
    editDetails()->page()->addMultiComboBox(4, 1, 1, 1, "02", "08", "02", "System"); //
    editDetails()->page()->addMultiComboBox(4, 2, 1, 1, "02", "08", "04", "System"); //
    editDetails()->page()->addMultiComboBox(4, 3, 1, 1, "02", "08", "06", "System"); //
    editDetails()->page()->addMultiComboBox(4, 4, 1, 1, "02", "08", "08", "System"); //
    editDetails()->page()->addMultiComboBox(4, 5, 1, 1, "02", "08", "0A", "System"); //
    editDetails()->page()->addMultiComboBox(4, 6, 1, 1, "02", "08", "0C", "System"); //
    editDetails()->page()->addMultiComboBox(4, 7, 1, 1, "02", "08", "0E", "System"); //
    editDetails()->page()->addMultiComboBox(4, 8, 1, 1, "02", "08", "10", "System"); //
    editDetails()->page()->addMultiComboBox(4, 9, 1, 1, "02", "08", "12", "System"); //
    editDetails()->page()->addMultiComboBox(4, 10, 1, 1, "02", "08", "14", "System"); //
    editDetails()->page()->addMultiComboBox(4, 11, 1, 1, "02", "08", "16", "System"); //
    editDetails()->page()->addMultiComboBox(4, 12, 1, 1, "02", "08", "18", "System"); //
    editDetails()->page()->addMultiComboBox(4, 13, 1, 1, "02", "08", "1A", "System"); //
    editDetails()->page()->addMultiComboBox(4, 14, 1, 1, "02", "08", "1C", "System"); //
    editDetails()->page()->addMultiComboBox(4, 15, 1, 1, "02", "08", "1E", "System"); // 80

    editDetails()->page()->addMultiComboBox(5, 0, 1, 1, "02", "08", "20", "System"); // 81
    editDetails()->page()->addMultiComboBox(5, 1, 1, 1, "02", "08", "22", "System"); //
    editDetails()->page()->addMultiComboBox(5, 2, 1, 1, "02", "08", "24", "System"); //
    editDetails()->page()->addMultiComboBox(5, 3, 1, 1, "02", "08", "26", "System"); //
    editDetails()->page()->addMultiComboBox(5, 4, 1, 1, "02", "08", "28", "System"); //
    editDetails()->page()->addMultiComboBox(5, 5, 1, 1, "02", "08", "2A", "System"); //
    editDetails()->page()->addMultiComboBox(5, 6, 1, 1, "02", "08", "2C", "System"); //
    editDetails()->page()->addMultiComboBox(5, 7, 1, 1, "02", "08", "2E", "System"); //
    editDetails()->page()->addMultiComboBox(5, 8, 1, 1, "02", "08", "30", "System"); //
    editDetails()->page()->addMultiComboBox(5, 9, 1, 1, "02", "08", "32", "System"); //
    editDetails()->page()->addMultiComboBox(5, 10, 1, 1, "02", "08", "34", "System"); //
    editDetails()->page()->addMultiComboBox(5, 11, 1, 1, "02", "08", "36", "System"); //
    editDetails()->page()->addMultiComboBox(5, 12, 1, 1, "02", "08", "38", "System"); //
    editDetails()->page()->addMultiComboBox(5, 13, 1, 1, "02", "08", "3A", "System"); //
    editDetails()->page()->addMultiComboBox(5, 14, 1, 1, "02", "08", "3C", "System"); //
    editDetails()->page()->addMultiComboBox(5, 15, 1, 1, "02", "08", "3E", "System"); // 96

    editDetails()->page()->addMultiComboBox(6, 0, 1, 1, "02", "08", "40", "System"); // 97
    editDetails()->page()->addMultiComboBox(6, 1, 1, 1, "02", "08", "42", "System"); //
    editDetails()->page()->addMultiComboBox(6, 2, 1, 1, "02", "08", "44", "System"); //
    editDetails()->page()->addMultiComboBox(6, 3, 1, 1, "02", "08", "46", "System"); //
    editDetails()->page()->addMultiComboBox(6, 4, 1, 1, "02", "08", "48", "System"); //
    editDetails()->page()->addMultiComboBox(6, 5, 1, 1, "02", "08", "4A", "System"); //
    editDetails()->page()->addMultiComboBox(6, 6, 1, 1, "02", "08", "4C", "System"); //
    editDetails()->page()->addMultiComboBox(6, 7, 1, 1, "02", "08", "4E", "System"); //
    editDetails()->page()->addMultiComboBox(6, 8, 1, 1, "02", "08", "50", "System"); //
    editDetails()->page()->addMultiComboBox(6, 9, 1, 1, "02", "08", "52", "System"); //
    editDetails()->page()->addMultiComboBox(6, 10, 1, 1, "02", "08", "54", "System"); //
    editDetails()->page()->addMultiComboBox(6, 11, 1, 1, "02", "08", "56", "System"); //
    editDetails()->page()->addMultiComboBox(6, 12, 1, 1, "02", "08", "58", "System"); //
    editDetails()->page()->addMultiComboBox(6, 13, 1, 1, "02", "08", "5A", "System"); //
    editDetails()->page()->addMultiComboBox(6, 14, 1, 1, "02", "08", "5C", "System"); //
    editDetails()->page()->addMultiComboBox(6, 15, 1, 1, "02", "08", "5E", "System"); // 112

    editDetails()->page()->addMultiComboBox(7, 0, 1, 1, "02", "08", "60", "System"); // 113
    editDetails()->page()->addMultiComboBox(7, 1, 1, 1, "02", "08", "62", "System"); //
    editDetails()->page()->addMultiComboBox(7, 2, 1, 1, "02", "08", "64", "System"); //
    editDetails()->page()->addMultiComboBox(7, 3, 1, 1, "02", "08", "66", "System"); //
    editDetails()->page()->addMultiComboBox(7, 4, 1, 1, "02", "08", "68", "System"); //
    editDetails()->page()->addMultiComboBox(7, 5, 1, 1, "02", "08", "6A", "System"); //
    editDetails()->page()->addMultiComboBox(7, 6, 1, 1, "02", "08", "6C", "System"); //
    editDetails()->page()->addMultiComboBox(7, 7, 1, 1, "02", "08", "6E", "System"); //
    editDetails()->page()->addMultiComboBox(7, 8, 1, 1, "02", "08", "70", "System"); //
    editDetails()->page()->addMultiComboBox(7, 9, 1, 1, "02", "08", "72", "System"); //
    editDetails()->page()->addMultiComboBox(7, 10, 1, 1, "02", "08", "74", "System"); //
    editDetails()->page()->addMultiComboBox(7, 11, 1, 1, "02", "08", "76", "System"); //
    editDetails()->page()->addMultiComboBox(7, 12, 1, 1, "02", "08", "78", "System"); //
    editDetails()->page()->addMultiComboBox(7, 13, 1, 1, "02", "08", "7A", "System"); //
    editDetails()->page()->addMultiComboBox(7, 14, 1, 1, "02", "08", "7C", "System"); //
    editDetails()->page()->addMultiComboBox(7, 15, 1, 1, "02", "08", "7E", "System"); // 128
*/
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->addPage("02", "00", "7F", "04", "System");
};
