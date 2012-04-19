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

#include "stompbox_eq.h"

stompbox_eq::stompbox_eq(QWidget *parent)
    : stompBox(parent)
{
    /* EQ */
    setImage(":/images/eq.png");
    setLSB("01", "00");
    setSlider1("01", "00", "32");
    setSlider2("01", "00", "35");
    setSlider3("01", "00", "38");
    setSlider4("01", "00", "39");
    setSlider5("01", "00", "3B");
    setButton("01", "00", "30");
    editDetails()->patchPos(530, 24, "01", "30");
    setEditPages();
};

void stompbox_eq::updateSignal()
{
    updateSlider1("01", "00", "32");
    updateSlider2("01", "00", "35");
    updateSlider3("01", "00", "38");
    updateSlider4("01", "00", "39");
    updateSlider5("01", "00", "3B");
    updateButton("01", "00", "30");
    updateSwitch("01", "00", "30");
};

void stompbox_eq::setEditPages()
{
    editDetails()->page()->newGroupBox("Effect", Qt::AlignTop | Qt::AlignHCenter);
    //editDetails()->page()->addSwitch(0, 0, 1, 1, "01", "00", "70", "middle", Qt::AlignCenter);
    //editDetails()->page()->addParaEQ(0, 1, 2, 4, "01", "00", "71");
    //editDetails()->page()->addGroupBox(0, 0, 2, 4);


    editDetails()->page()->addSwitch(0, 0, 1, 1, "01", "00", "30", "middle", Qt::AlignCenter);
	editDetails()->page()->addGroupBox(0, 0, 2, 1);

	editDetails()->page()->newGroupBox("Equalizer");
	editDetails()->page()->newGroupBox("Low");
    editDetails()->page()->addKnob(0, 0, 1, 1, "01", "00", "31");
    editDetails()->page()->addKnob(0, 1, 1, 1, "01", "00", "32");
	editDetails()->page()->addGroupBox(0, 0, 1, 1);

	editDetails()->page()->newGroupBox("Low-Middle");
    editDetails()->page()->addKnob(1, 0, 1, 1, "01", "00", "33");
    editDetails()->page()->addKnob(2, 0, 1, 1, "01", "00", "34");
    editDetails()->page()->addKnob(0, 0, 1, 1, "01", "00", "35");
	editDetails()->page()->addGroupBox(0, 1, 1, 1);

	editDetails()->page()->newGroupBox("High-Middle");
    editDetails()->page()->addKnob(1, 0, 1, 1, "01", "00", "36");
    editDetails()->page()->addKnob(2, 0, 1, 1, "01", "00", "37");
    editDetails()->page()->addKnob(0, 0, 1, 1, "01", "00", "38");
	editDetails()->page()->addGroupBox(0, 2, 1, 1);

	editDetails()->page()->newGroupBox("High");
    editDetails()->page()->addKnob(0, 0, 1, 1, "01", "00", "39");
    editDetails()->page()->addKnob(0, 1, 1, 1, "01", "00", "3A");
	editDetails()->page()->addGroupBox(0, 3, 1, 1);
	editDetails()->page()->addGroupBox(0, 1, 2, 1);

	editDetails()->page()->newGroupBox("Level");
    editDetails()->page()->addKnob(0, 0, 1, 1, "01", "00", "3B");
	editDetails()->page()->addGroupBox(0, 2, 2, 1);

	editDetails()->addPage();

};
