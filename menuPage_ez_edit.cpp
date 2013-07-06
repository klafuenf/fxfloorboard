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

#include "menuPage_ez_edit.h"

menuPage_ez_edit::menuPage_ez_edit(QWidget *parent)
    : menuPage(parent)
{
    setLSB("00", "00");
    setEditPages();
}

void menuPage_ez_edit::updateSignal()
{

}

void menuPage_ez_edit::setEditPages()
{
    //editDetails()->page()->newGroupBox("Patch Creator");
    editDetails()->page()->newGroupBox("Style");
    editDetails()->page()->addEZ_Patch(0, 0, 1, 1, "00", "00", "31", "middle", Qt::AlignCenter);
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->newGroupBox("Preamp");
    editDetails()->page()->addEZ_amp(0, 0, 1, 1, "00", "00", "52", "Preamp");
     editDetails()->page()->addGroupBox(0, 1, 1, 1);
    editDetails()->page()->newGroupBox("Speaker & Cabinet");
    //editDetails()->page()->addComboBox(0, 0, 1, 1, "00", "00", "6F", "large");   // custom spkr A type
    editDetails()->page()->addEZ_amp(0, 0, 1, 1, "00", "00", "60", "Speaker");
    editDetails()->page()->addGroupBox(0, 2, 1, 1);
   // editDetails()->page()->addGroupBox(0, 0, 1, 3);
    editDetails()->addPage("00", "00", "30", "00", "Tables");

    editDetails()->page()->newGroupBox(tr("Amp Select"));
    editDetails()->page()->addComboBox(0, 0, 1, 1, "06", "00", "40", "large");   //mode
    editDetails()->page()->newStackControl(0);
    editDetails()->page()->addComboBox(1, 0, 1, 1, "06", "00", "41", "large");   // channel select
    editDetails()->page()->addStackControl();
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->insertStackField(0, 0, 1, 1, 1);

    editDetails()->page()->newStackField(0);
    editDetails()->page()->newGroupBox("Amp A Customiser");
    editDetails()->page()->addComboBox(0, 0, 1, 1, "00", "00", "63", "large");   // custom amp A type
    editDetails()->page()->addEZ_amp(1, 0, 1, 1, "00", "00", "65", "Preamp_A");
    editDetails()->page()->addGroupBox(1, 0, 1, 1);
    editDetails()->page()->newGroupBox("Speaker A Customiser");
    editDetails()->page()->addComboBox(0, 0, 1, 1, "00", "00", "6F", "large");   // custom spkr A type
    editDetails()->page()->addEZ_amp(1, 0, 1, 1, "00", "00", "61", "Speaker_A");
    editDetails()->page()->addGroupBox(1, 1, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0);
    editDetails()->page()->newGroupBox("Amp B Customiser");
    editDetails()->page()->addComboBox(0, 0, 1, 1, "01", "00", "13", "large");   // custom amp B type
    editDetails()->page()->addEZ_amp(1, 0, 1, 1, "01", "00", "15", "Preamp_B");
    editDetails()->page()->addGroupBox(1, 0, 1, 1);
    editDetails()->page()->newGroupBox("Speaker B Customiser");
    editDetails()->page()->addComboBox(0, 0, 1, 1, "01", "00", "1F", "large");   // custom spkr B type
    editDetails()->page()->addEZ_amp(1, 0, 1, 1, "01", "00", "11", "Speaker_B");
    editDetails()->page()->addGroupBox(1, 1, 1, 1);
    editDetails()->page()->addStackField();
    editDetails()->addPage("00", "00", "30", "01", "Tables");

    editDetails()->page()->newGroupBox("OD/DS Customiser");
    editDetails()->page()->addComboBox(0, 0, 1, 1, "00", "00", "39", "large");   // custom
    editDetails()->page()->addEZ_amp(1, 0, 1, 1, "00", "00", "3B", "Distortion");
    editDetails()->page()->addGroupBox(0, 1, 1, 1);
    editDetails()->addPage("00", "00", "30", "02", "Tables");

    editDetails()->page()->newGroupBox("Ambience");
    //editDetails()->page()->addComboBox(0, 0, 1, 1, "00", "00", "39", "large");   // custom
    editDetails()->page()->addEZ_amp(1, 0, 1, 1, "06", "00", "02", "Ambience");
    editDetails()->page()->addGroupBox(0, 1, 1, 1);
    editDetails()->addPage("00", "00", "30", "03", "Tables");
}
