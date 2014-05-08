/****************************************************************************
**
** Copyright (C) 2007~2014 Colin Willcocks.
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

#include "stompbox_ce.h"

stompbox_ce::stompbox_ce(QWidget *parent)
    : stompBox(parent)
{
	/* Chorus */
	setImage(":/images/ce.png");
    setLSB("06", "00");
    setKnob1("06", "00", "02");
    setKnob2("06", "00", "03");
    setComboBox("06", "00", "01");
    setButton("06", "00", "00");
    editDetails()->patchPos(1714, 16, "06", "00");
	setEditPages();
}

void stompbox_ce::updateSignal()
{
    updateKnob1("06", "00", "02");
    updateKnob2("06", "00", "03");
    updateComboBox("06", "00", "01");
    updateButton("06", "00", "00");
    updateSwitch("06", "00", "00");
}

void stompbox_ce::setEditPages()
{
    editDetails()->page()->newGroupBox(tr("Effect"));
    editDetails()->page()->addSwitch(0, 0, 1, 1, "06", "00", "00", "middle", Qt::AlignCenter);
    editDetails()->page()->addComboBox(1, 0, 1, 1, "06", "00", "01", "large");
	editDetails()->page()->addGroupBox(0, 0, 2, 1);

	editDetails()->page()->newGroupBox(tr("Chorus"));
    editDetails()->page()->addKnob(0, 0, 1, 3, "06", "00", "02", "normal","right", 120);
    editDetails()->page()->addKnob(1, 0, 1, 1, "06", "00", "04", "normal","bottom", 80);
    editDetails()->page()->addKnob(1, 1, 1, 1, "06", "00", "03");

	editDetails()->page()->addGroupBox(0, 1, 2, 1);

	editDetails()->page()->newGroupBox(tr("Filter"));
    editDetails()->page()->addKnob(0, 0, 1, 1, "06", "00", "05");
    editDetails()->page()->addKnob(0, 1, 1, 1, "06", "00", "06");
	editDetails()->page()->addGroupBox(0, 2, 2, 1);

	editDetails()->page()->newGroupBox(tr("Level"));
    editDetails()->page()->addKnob(0, 0, 1, 1, "06", "00", "07");
    editDetails()->page()->addGroupBox(0, 3, 2, 1);

	editDetails()->addPage();
  	
}
