/****************************************************************************
**
** Copyright (C) 2007~2013 Colin Willcocks.
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

#include "stompbox_lp.h"

stompbox_lp::stompbox_lp(QWidget *parent)
    : stompBox(parent)
{
    /* LOOP */
    setImage(":/images/lp.png");
    setLSB("06", "00");
    setKnob1("06", "00", "57");
    setKnob2("06", "00", "58");
    setComboBox("06", "00", "56");
    setButton("06", "00", "55");
    editDetails()->patchPos(1884, 8, "06", "55");
    setEditPages();
}

void stompbox_lp::updateSignal()
{
    updateKnob1("06", "00", "57");
    updateKnob2("06", "00", "58");
    updateComboBox("06", "00", "56");
    updateButton("06", "00", "55");
    updateSwitch("06", "00", "55");
}

void stompbox_lp::setEditPages()
{
    editDetails()->page()->newGroupBox("Effect");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "06", "00", "55", "middle", Qt::AlignCenter);
    editDetails()->page()->addComboBox(1, 0, 1, 1, "06", "00", "56", "large");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);

    editDetails()->page()->newGroupBox("Level");
    editDetails()->page()->addKnob(0, 0, 1, 1, "06", "00", "57");
    editDetails()->page()->addKnob(0, 1, 1, 1, "06", "00", "58");
    editDetails()->page()->addGroupBox(0, 1, 1, 1);

    editDetails()->addPage();
}
