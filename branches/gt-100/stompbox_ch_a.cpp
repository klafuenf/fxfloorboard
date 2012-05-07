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

#include "stompbox_ch_a.h"

stompbox_ch_a::stompbox_ch_a(QWidget *parent)
    : stompBox(parent)
{
    /* CHANNEL_A PREAMP*/
    setImage(":/images/ch_a.png");
    setLSB("00", "50");
    setButton("00", "00", "50");
    setComboBox("00", "00", "51");
    setKnob1("00", "00", "52");
    setKnob2("00", "00", "58");
    editDetails()->patchPos(182, 64, "00", "50");
    setEditPages();
};

void stompbox_ch_a::updateSignal()
{
    updateButton("00", "00", "50");
    updateComboBox("00", "00", "51");
    updateKnob1("00", "00", "52");
    updateKnob2("00", "00", "58");
    updateSwitch("00", "00", "50");
    updateSwitch("00", "00", "5B");
};

void stompbox_ch_a::setEditPages()
{
    editDetails()->page()->newGroupBox("Effect");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "00", "50");   // off/on effect
    editDetails()->page()->addGroupBox(0, 0, 1, 1);

    // CHANNEL A


    editDetails()->page()->newGroupBox(tr("Channel A"));

    editDetails()->page()->newGroupBox(tr("Pre Amp"));
    editDetails()->page()->newStackControl(0);
    editDetails()->page()->addComboBox(0, 0, 1, 1, "00", "00", "51");        //pre type
    editDetails()->page()->addStackControl();
    editDetails()->page()->addComboBox(0, 1, 1, 1, "00", "00", "5A", "bottom", Qt::AlignLeft); //gain sw
    editDetails()->page()->addKnob(0, 2, 1, 1, "00", "00", "52", "turbo");   // gain
    editDetails()->page()->addKnob(0, 3, 1, 1, "00", "00", "53");            //T-Comp
    editDetails()->page()->addKnob(0, 4, 1, 1, "00", "00", "54");            //bass
    editDetails()->page()->addKnob(0, 5, 1, 1, "00", "00", "55");            // mid
    editDetails()->page()->addKnob(0, 6, 1, 1, "00", "00", "56");            // treble
    editDetails()->page()->addKnob(0, 7, 1, 1, "00", "00", "57");            // presence
    editDetails()->page()->addKnob(0, 8, 1, 1, "00", "00", "58");            // effect level
    editDetails()->page()->addGroupBox(0, 0, 1, 1);

    editDetails()->page()->insertStackField(0, 1, 0, 1, 1);                // bright button

    editDetails()->page()->newGroupBox(tr("Speaker"));
    editDetails()->page()->newStackControl(1);
    editDetails()->page()->addComboBox(0, 0, 1, 1, "00", "00", "5D");     //type
    editDetails()->page()->addStackControl();
    editDetails()->page()->addComboBox(0, 1, 1, 1, "00", "00", "5E", "bottom", Qt::AlignRight); //mic type
    editDetails()->page()->addComboBox(0, 2, 1, 1, "00", "00", "5F"); //mic dist
    editDetails()->page()->addKnob(0, 3, 1, 1, "00", "00", "60");  //mic pos
    editDetails()->page()->addKnob(0, 4, 1, 1, "00", "00", "61");   //mic level
    editDetails()->page()->addKnob(0, 5, 1, 1, "00", "00", "62");   // direct mix
    editDetails()->page()->addGroupBox(2, 0, 1, 1);

    editDetails()->page()->newGroupBox(tr("Solo"));
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "00", "5B", "middle", Qt::AlignLeft | Qt::AlignTop);
    editDetails()->page()->addKnob(1, 0, 1, 1, "00", "00", "5C");  //solo level
    editDetails()->page()->addGroupBox(0, 1, 3, 1);

    editDetails()->page()->insertStackField(1, 0, 2, 4, 1);

    editDetails()->page()->addGroupBox(0, 1, 1, 1);




    // Bright Button stack fields
    editDetails()->page()->newStackField(0);  //boss clean
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "00", "59", "middle", Qt::AlignCenter);
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // jc-120
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "00", "59", "middle", Qt::AlignCenter);
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0);  //jazz combo
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "00", "59", "middle", Qt::AlignCenter);
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // full range
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //clean twin
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "00", "59", "middle", Qt::AlignCenter);
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // pro crunch
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "00", "59", "middle", Qt::AlignCenter);
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // tweed
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "00", "59", "middle", Qt::AlignCenter);
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //delux crunch
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //boss crunch
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "00", "59", "middle", Qt::AlignCenter);
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0);  //blues
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "00", "59", "middle", Qt::AlignCenter);
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //wild crunch
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //stack crunch
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "00", "59", "middle", Qt::AlignCenter);
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
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "00", "59", "middle", Qt::AlignCenter);
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // bg drive
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "00", "59", "middle", Qt::AlignCenter);
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0);  // bg rhythm
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "00", "59", "middle", Qt::AlignCenter);
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
    editDetails()->page()->addComboBox(0, 0, 1, 1, "00", "00", "63");  //type
    editDetails()->page()->addStackControl();
    editDetails()->page()->insertStackField(2, 0, 1, 1, 1);
    editDetails()->page()->addKnob(0, 2, 1, 1, "00", "00", "64");  //bottom
    editDetails()->page()->addKnob(0, 3, 1, 1, "00", "00", "65");  //edge
    editDetails()->page()->addKnob(0, 4, 1, 1, "00", "00", "68");  //pre-lo
    editDetails()->page()->addKnob(0, 5, 1, 1, "00", "00", "69");  //pre-hi
    editDetails()->page()->addKnob(0, 6, 1, 1, "00", "00", "6A");  //character
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
    editDetails()->page()->addKnob(0, 0, 1, 1, "00", "00", "6B", "normal","right", 40);  //
    editDetails()->page()->addKnob(1, 0, 1, 1, "00", "00", "6C", "normal","right", 40);
    editDetails()->page()->addKnob(2, 0, 1, 2, "00", "00", "6D", "normal","right", 40);
    editDetails()->page()->addComboBox(3, 0, 1, 1, "00", "00", "6E", "bottom", Qt::AlignHCenter);
    editDetails()->page()->addComboBox(4, 0, 1, 1, "00", "00", "6F", "bottom", Qt::AlignHCenter);
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(2);
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "00", "59", "middle", Qt::AlignCenter);
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "00", "59", "middle", Qt::AlignCenter);
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "00", "59", "middle", Qt::AlignCenter);
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "00", "59", "middle", Qt::AlignCenter);
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);editDetails()->page()->addStackField();


    editDetails()->addPage();
};
