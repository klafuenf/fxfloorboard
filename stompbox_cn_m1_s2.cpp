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

#include "stompbox_cn_m1_s2.h"

stompbox_cn_m1_s2::stompbox_cn_m1_s2(QWidget *parent)
    : stompBox(parent)
{
    /* CHAIN MERGE */
    this->setImage(":/images/cn_m1_s2.png");
    setLSB("07", "20");
    editDetails()->patchPos(2060, 40, "07", "20");
    setEditPages();
}

void stompbox_cn_m1_s2::updateSignal()
{
    emit updateStompBoxes();
}

void stompbox_cn_m1_s2::setEditPages()
{

    QString text = tr("USE FOR PASTING CHAIN CONFIGURATIONS - For Chain editing, close and drag stompboxes");
    editDetails()->page()->addLabel(0, 0, 1, 3, text);
    editDetails()->addPage();
}