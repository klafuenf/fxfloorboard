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

#include "stompbox_ch_b.h"

stompbox_ch_b::stompbox_ch_b(QWidget *parent)
    : stompBox(parent)
{
    /* CHANNEL B PREAMP */
    setImage(":/images/ch_b.png");
    setLSB("01", "00");
    setButton("01", "00", "00");
    setComboBox("01", "00", "01");
    setKnob1("01", "00", "02");
    setKnob2("01", "00", "08");
    editDetails()->patchPos(304, 62, "01", "00");
    setEditPages();

};

void stompbox_ch_b::updateSignal()
{
    updateButton("01", "00", "00");
    updateComboBox("01", "00", "01");
    updateKnob1("01", "00", "02");
    updateKnob2("01", "00", "08");
    updateSwitch("01", "00", "00");
    updateSwitch("01", "00", "0B");
};

void stompbox_ch_b::setEditPages()
{
    editDetails()->page()->newGroupBox("Effect");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "01", "00", "00");   // off/on effect
    editDetails()->page()->addGroupBox(0, 0, 1, 1);


    // CHANNEL B

    editDetails()->page()->newGroupBox(tr("Channel B"));

    editDetails()->page()->newGroupBox(tr("Pre Amp"));
    editDetails()->page()->newStackControl(0);
    editDetails()->page()->addComboBox(0, 0, 1, 1, "01", "00", "01");  // pre type
    editDetails()->page()->addStackControl();
    editDetails()->page()->addComboBox(0, 1, 1, 1, "01", "00", "0A", "bottom", Qt::AlignLeft); // gain sw
    editDetails()->page()->addKnob(0, 2, 1, 1, "01", "00", "02", "turbo");  //gain
    editDetails()->page()->addKnob(0, 3, 1, 1, "01", "00", "03");            // t-comp
    editDetails()->page()->addKnob(0, 4, 1, 1, "01", "00", "04");            // bass
    editDetails()->page()->addKnob(0, 5, 1, 1, "01", "00", "05");           // mid
    editDetails()->page()->addKnob(0, 6, 1, 1, "01", "00", "06");           // treble
    editDetails()->page()->addKnob(0, 7, 1, 1, "01", "00", "07");           //presence
    editDetails()->page()->addKnob(0, 8, 1, 1, "01", "00", "08");          //effect level
    editDetails()->page()->addGroupBox(0, 0, 1, 1);

    editDetails()->page()->insertStackField(0, 1, 0, 1, 1);                 // bright switch

    editDetails()->page()->newGroupBox(tr("Speaker"));
    editDetails()->page()->newStackControl(1);
    editDetails()->page()->addComboBox(0, 0, 1, 1, "01", "00", "0D");   // speaker type
    editDetails()->page()->addStackControl();
    editDetails()->page()->addComboBox(0, 1, 1, 1, "01", "00", "0E", "bottom", Qt::AlignRight);  // mic type
    editDetails()->page()->addComboBox(0, 2, 1, 1, "01", "00", "0F");  // mic dis
    editDetails()->page()->addKnob(0, 3, 1, 1, "01", "00", "10");   // mic pos
    editDetails()->page()->addKnob(0, 4, 1, 1, "01", "00", "11");    // mic level
    editDetails()->page()->addKnob(0, 5, 1, 1, "01", "00", "12");   // direct level
    editDetails()->page()->addGroupBox(2, 0, 1, 1);

    editDetails()->page()->newGroupBox(tr("Solo"));
    editDetails()->page()->addSwitch(0, 0, 1, 1, "01", "00", "0B", "middle", Qt::AlignLeft | Qt::AlignTop);
    editDetails()->page()->addKnob(1, 0, 1, 1, "01", "00", "0C");
    editDetails()->page()->addGroupBox(0, 1, 3, 1);


    editDetails()->page()->insertStackField(1, 0, 2, 4, 1);
    


    editDetails()->page()->addGroupBox(0, 1, 1, 1);




    // Bright Button stack fields
    editDetails()->page()->newStackField(0);  //boss clean
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "01", "00", "09", "middle", Qt::AlignCenter);
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // jc-120
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "01", "00", "09", "middle", Qt::AlignCenter);
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0);  //jazz combo
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "01", "00", "09", "middle", Qt::AlignCenter);
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // full range
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //clean twin
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "01", "00", "09", "middle", Qt::AlignCenter);
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // pro crunch
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "01", "00", "09", "middle", Qt::AlignCenter);
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // tweed
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "01", "00", "09", "middle", Qt::AlignCenter);
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //delux crunch
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //boss crunch
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "01", "00", "09", "middle", Qt::AlignCenter);
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0);  //blues
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "01", "00", "09", "middle", Qt::AlignCenter);
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //wild crunch
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //stack crunch
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "01", "00", "09", "middle", Qt::AlignCenter);
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //VO drive
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //VO lead
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // VO clean
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0);  // match drive
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0);  //fat match
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0);  // match lead
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // bg lead
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "01", "00", "09", "middle", Qt::AlignCenter);
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // bg drive
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "01", "00", "09", "middle", Qt::AlignCenter);
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0);  // bg rhythm
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "01", "00", "09", "middle", Qt::AlignCenter);
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // ms1959 I
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // ms1959 II
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // MS hi gain
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0);  // ms scoop
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // custom
    editDetails()->page()->newGroupBox(tr("Custom PreAmp"));
    editDetails()->page()->newStackControl(2);
    editDetails()->page()->addComboBox(0, 0, 1, 1, "01", "00", "13");
    editDetails()->page()->addStackControl();
    editDetails()->page()->insertStackField(2, 0, 1, 1, 1);
    editDetails()->page()->addKnob(0, 2, 1, 1, "01", "00", "14");
    editDetails()->page()->addKnob(0, 3, 1, 1, "01", "00", "15");
    editDetails()->page()->addKnob(0, 4, 1, 1, "01", "00", "18");
    editDetails()->page()->addKnob(0, 5, 1, 1, "01", "00", "19");
    editDetails()->page()->addKnob(0, 6, 1, 1, "01", "00", "1A");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();


    editDetails()->page()->newStackField(1);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(1);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(1);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(1);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(1);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(1);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(1);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(1);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(1);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(1);
    editDetails()->page()->newGroupBox(tr("Custom Speaker"));
    editDetails()->page()->addKnob(0, 0, 1, 1, "01", "00", "1B", "normal","right", 40);
    editDetails()->page()->addKnob(1, 0, 1, 1, "01", "00", "1C", "normal","right", 40);
    editDetails()->page()->addKnob(2, 0, 1, 2, "01", "00", "1D", "normal","right", 40);
    editDetails()->page()->addComboBox(3, 0, 1, 1, "01", "00", "1E", "bottom", Qt::AlignHCenter);
    editDetails()->page()->addComboBox(4, 0, 1, 1, "01", "00", "1F", "bottom", Qt::AlignHCenter);
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(2);
    editDetails()->page()->addSwitch(0, 0, 1, 1, "01", "00", "09", "middle", Qt::AlignCenter);
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);
    editDetails()->page()->addSwitch(0, 0, 1, 1, "01", "00", "09", "middle", Qt::AlignCenter);
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);
    editDetails()->page()->addSwitch(0, 0, 1, 1, "01", "00", "09", "middle", Qt::AlignCenter);
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);
    editDetails()->page()->addSwitch(0, 0, 1, 1, "01", "00", "09", "middle", Qt::AlignCenter);
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);editDetails()->page()->addStackField();


    editDetails()->addPage();
};
