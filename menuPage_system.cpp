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

#include "menuPage_system.h"

menuPage_system::menuPage_system(QWidget *parent)
    : menuPage(parent)
{ 
    setLSB("00", "00");
    setEditPages();
}

void menuPage_system::updateSignal()
{

}

void menuPage_system::setEditPages()
{ 
    QString text = tr("***CAUTION*** Settings changes are automatically written to GT-100 when changed");
    editDetails()->page()->addLabel(0, 0, 1, 3, text);
    editDetails()->page()->newGroupBox("User settings");
    editDetails()->page()->addKnob(0, 0, 1, 1, "00", "00", "00", "System"); // lcd contrast left
    editDetails()->page()->addKnob(0, 1, 1, 1, "00", "00", "01", "System"); // lcd contrast right
    editDetails()->page()->addLabel(0, 2, 1, 1, "     ");
    editDetails()->page()->addComboBox(0, 3, 1, 1, "00", "00", "41", "System"); // preamp mode
    editDetails()->page()->addLabel(0, 4, 1, 1, "     ");
    editDetails()->page()->addComboBox(0, 5, 1, 1, "00", "00", "11", "System"); //exp hold
    editDetails()->page()->addLabel(0, 6, 1, 1, "     ");
    editDetails()->page()->addComboBox(0, 7, 1, 1, "00", "00", "12", "System"); //knob lock
    editDetails()->page()->addLabel(0, 8, 1, 1, "     ");
    editDetails()->page()->addComboBox(0, 9, 1, 1, "00", "00", "13", "System"); //num pdl sw
    editDetails()->page()->addLabel(0, 10, 1, 1, "     ");
    editDetails()->page()->addComboBox(0, 11, 1, 1, "00", "00", "18", "System"); //pedal indication
    editDetails()->page()->addLabel(0, 12, 1, 1, "     ");
    editDetails()->page()->addComboBox(0, 13, 1, 1, "00", "00", "60", "System"); //auto off
    editDetails()->page()->addGroupBox(1, 0, 1, 3);

    editDetails()->page()->newGroupBox("USB settings");
    editDetails()->page()->addComboBox(0, 0, 1, 1, "00", "00", "50", "System"); //usb I/O mode
    editDetails()->page()->addLabel(0, 1, 1, 1, "     ");
    editDetails()->page()->addComboBox(0, 2, 1, 1, "00", "00", "55", "System"); //usb monitor cmd
    editDetails()->page()->addKnob(0, 3, 1, 1, "00", "00", "51", "System"); //usb input level
    editDetails()->page()->addKnob(0, 4, 1, 1, "00", "00", "52", "System"); //usb mix level
    editDetails()->page()->addKnob(0, 5, 1, 1, "00", "00", "53", "System"); //usb mix level
    editDetails()->page()->addGroupBox(2, 0, 1, 2);

    editDetails()->page()->newGroupBox("Tuner");
    editDetails()->page()->addComboBox(0, 0, 1, 1, "00", "00", "20", "System"); // tuner pitch
    editDetails()->page()->addLabel(0, 1, 1, 1, "               ");
    editDetails()->page()->addComboBox(0, 2, 1, 1, "00", "00", "21", "System"); //tuner output
    editDetails()->page()->addKnob(0, 3, 1, 1, "00", "00", "34", "System"); //metronome level
    editDetails()->page()->addGroupBox(2, 2, 1, 1);

    editDetails()->page()->newGroupBox("Patch Change");
    editDetails()->page()->addComboBox(0, 1, 1, 1, "00", "00", "10", "System"); // bank change mode
    editDetails()->page()->addKnob(0, 2, 1, 1, "00", "00", "14", "System"); // bank extent min
    editDetails()->page()->addKnob(0, 3, 1, 1, "00", "00", "16", "System"); // bank extent max
    editDetails()->page()->addGroupBox(3, 2, 1, 1);

    editDetails()->page()->newGroupBox("Input Level");
    editDetails()->page()->addKnob(0, 0, 1, 1, "00", "00", "71", "System"); // input level
    editDetails()->page()->addGroupBox(3, 0, 1, 1);
    editDetails()->page()->newGroupBox("Global NS/Reverb");
    editDetails()->page()->addKnob(0, 2, 1, 1, "00", "00", "77", "System"); // NS threshold
    editDetails()->page()->addKnob(0, 3, 1, 1, "00", "00", "78", "System"); // revberb level
    editDetails()->page()->addGroupBox(3, 1, 1, 1);

    editDetails()->addPage("00", "00", "2F", "00", "Tables");


    editDetails()->page()->newGroupBox("User Options " + text);
    editDetails()->page()->newGroupBox("Output");
    editDetails()->page()->addComboBox(0, 0, 1, 1, "00", "00", "79", "System"); // output level
    editDetails()->page()->addLabel(0, 1, 1, 1, "          ");
    editDetails()->page()->addComboBox(0, 2, 1, 1, "00", "00", "40", "System"); // select mode
    editDetails()->page()->addLabel(0, 3, 1, 1, "     ");
    editDetails()->page()->addComboBox(0, 4, 1, 1, "00", "00", "70", "System"); // output select
    editDetails()->page()->addGroupBox(0, 1, 1, 1);

    editDetails()->page()->newGroupBox("Phrase Looper");
    editDetails()->page()->addComboBox(0, 0, 1, 1, "00", "01", "00", "System"); // PH LOOP mode
    editDetails()->page()->addComboBox(0, 1, 1, 1, "00", "01", "02", "System"); // record mode
    editDetails()->page()->addComboBox(0, 2, 1, 1, "00", "01", "01", "System"); // pedal mode
    editDetails()->page()->addKnob(0, 3, 1, 1, "00", "01", "04", "System"); // play level
    editDetails()->page()->addGroupBox(1, 1, 1, 1);

    editDetails()->page()->newGroupBox("Knob Function");
    editDetails()->page()->addComboBox(0, 0, 1, 1, "00", "02", "50", "System"); // knob 1
    editDetails()->page()->addComboBox(0, 1, 1, 1, "00", "02", "52", "System"); // knob 2
    editDetails()->page()->addComboBox(0, 2, 1, 1, "00", "02", "54", "System"); // knob 3
    editDetails()->page()->addComboBox(0, 3, 1, 1, "00", "02", "56", "System"); // knob 4
    editDetails()->page()->addComboBox(1, 0, 1, 1, "00", "02", "58", "System"); // knob 5
    editDetails()->page()->addComboBox(1, 1, 1, 1, "00", "02", "5A", "System"); // knob 6
    editDetails()->page()->addComboBox(1, 2, 1, 1, "00", "02", "5C", "System"); // knob 7
    editDetails()->page()->addComboBox(1, 3, 1, 1, "00", "02", "5E", "System"); // knob 8
    editDetails()->page()->addGroupBox(2, 1, 1, 1);

    editDetails()->page()->newGroupBox("Global Equalizer");
    editDetails()->page()->addMasterEQ(0, 1, 2, 4, "00", "00", "71", "System");
    editDetails()->page()->addGroupBox(0, 0, 3, 1);
    editDetails()->page()->addGroupBox(0, 0, 1, 1);

    editDetails()->addPage("00", "00", "2F", "01", "Tables");


    editDetails()->page()->newGroupBox("Internal Pedals " + text);
    editDetails()->page()->newGroupBox("EXP PEDAL");
    editDetails()->page()->addComboBox(0, 0, 1, 1, "00", "00", "43", "System"); // exp pdl
    editDetails()->page()->addComboBox(0, 1, 1, 1, "00", "02", "70", "System"); // exp function
    editDetails()->page()->addKnob(0, 2, 1, 1, "00", "02", "71", "System"); // patch level min
    editDetails()->page()->addKnob(0, 3, 1, 1, "00", "02", "72", "System"); // patch level max
    editDetails()->page()->addGroupBox(0, 0, 1, 1);

    editDetails()->page()->newGroupBox("EXP PEDAL SWITCH");
    editDetails()->page()->addComboBox(1, 0, 1, 1, "00", "00", "44", "System"); // exp pdl sw
    editDetails()->page()->addComboBox(1, 1, 1, 1, "00", "02", "64", "System"); // exp sw function
    editDetails()->page()->addComboBox(1, 2, 1, 1, "00", "02", "65", "System"); // exp sw min
    editDetails()->page()->addComboBox(1, 3, 1, 1, "00", "02", "66", "System"); // exp sw max
    editDetails()->page()->addComboBox(1, 4, 1, 1, "00", "02", "67", "System"); // exp1 sw src mode
    editDetails()->page()->addGroupBox(1, 0, 1, 1);

    editDetails()->page()->newGroupBox("ACCEL/CTL PEDAL");
    editDetails()->page()->addComboBox(2, 0, 1, 1, "00", "00", "42", "System"); // Accel/ctrl
    editDetails()->page()->addComboBox(2, 1, 1, 1, "00", "02", "60", "System"); // Accel/ctrl function
    editDetails()->page()->addComboBox(2, 2, 1, 1, "00", "02", "61", "System"); // Accel/ctrl min
    editDetails()->page()->addComboBox(2, 3, 1, 1, "00", "02", "62", "System"); // Accel/ctrl max
    editDetails()->page()->addComboBox(2, 4, 1, 1, "00", "02", "63", "System"); // Accel/ctrl src mode
    editDetails()->page()->addGroupBox(2, 0, 1, 1);

    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->addPage("00", "00", "2F", "02", "Tables");

    editDetails()->page()->newGroupBox("External pedals " + text);
    editDetails()->page()->newGroupBox("SUB EXP PEDAL");
    editDetails()->page()->addComboBox(0, 0, 1, 1, "00", "00", "47", "System"); // sub exp pdl
    editDetails()->page()->addComboBox(0, 1, 1, 1, "00", "02", "73", "System"); // sub exp function
    editDetails()->page()->addGroupBox(0, 0, 1, 1);

    editDetails()->page()->newGroupBox("SUB CTL 1 PEDAL");
    editDetails()->page()->addComboBox(1, 0, 1, 1, "00", "00", "45", "System"); // sub ctrl 1
    editDetails()->page()->addComboBox(1, 1, 1, 1, "00", "02", "68", "System"); // sub ctl 1 function
    editDetails()->page()->addComboBox(1, 2, 1, 1, "00", "02", "69", "System"); // sub ctl 1 min
    editDetails()->page()->addComboBox(1, 3, 1, 1, "00", "02", "6A", "System"); // sub ctl 1 max
    editDetails()->page()->addComboBox(1, 4, 1, 1, "00", "02", "6B", "System"); // sub ctl 1 src mode
    editDetails()->page()->addGroupBox(1, 0, 1, 1);

    editDetails()->page()->newGroupBox("SUB CTL 2 PEDAL");
    editDetails()->page()->addComboBox(2, 0, 1, 1, "00", "00", "46", "System"); // sub ctrl 2
    editDetails()->page()->addComboBox(2, 1, 1, 1, "00", "02", "6C", "System"); // sub ctl 2 function
    editDetails()->page()->addComboBox(2, 2, 1, 1, "00", "02", "6D", "System"); // sub ctl 2 function
    editDetails()->page()->addComboBox(2, 3, 1, 1, "00", "02", "6E", "System"); // sub ctl 2 min
    editDetails()->page()->addComboBox(2, 4, 1, 1, "00", "02", "6F", "System"); // sub ctl 2 max
    editDetails()->page()->addGroupBox(2, 0, 1, 1);
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->addPage("00", "00", "2F", "03", "Tables");


    /////////////////////////////////// preamp A #1 ///////////////////////////////////////////

    editDetails()->page()->newGroupBox(tr("SYSTEM 1 Channel A"));
    editDetails()->page()->addLabel(0, 0, 1, 1, "System PreAmp " + text);

    editDetails()->page()->newGroupBox(tr("Pre Amp"));
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "10", "System");         // off/on effect
    editDetails()->page()->newStackControl(0);
    editDetails()->page()->addComboBox(0, 1, 1, 1, "00", "01", "11", "System");        //pre type
    editDetails()->page()->addStackControl();
    editDetails()->page()->addComboBox(0, 2, 1, 1, "00", "01", "1A", "System");        //gain sw
    editDetails()->page()->addKnob(0, 3, 1, 1, "00", "01", "12", "System");            // gain
    editDetails()->page()->addKnob(0, 4, 1, 1, "00", "01", "13", "System");            //T-Comp
    editDetails()->page()->addKnob(0, 5, 1, 1, "00", "01", "14", "System");            //bass
    editDetails()->page()->addKnob(0, 6, 1, 1, "00", "01", "15", "System");            // mid
    editDetails()->page()->addKnob(0, 7, 1, 1, "00", "01", "16", "System");            // treble
    editDetails()->page()->addKnob(0, 8, 1, 1, "00", "01", "17", "System");            // presence
    editDetails()->page()->addKnob(0, 9, 1, 1, "00", "01", "18", "System");            // effect level
    editDetails()->page()->addGroupBox(1, 0, 1, 1);

    editDetails()->page()->insertStackField(0, 2, 0, 1, 1);                // bright button

    editDetails()->page()->newGroupBox(tr("Speaker"));
    editDetails()->page()->newStackControl(1);
    editDetails()->page()->addComboBox(0, 0, 1, 1, "00", "01", "1D", "System");     //type
    editDetails()->page()->addStackControl();
    editDetails()->page()->addComboBox(0, 1, 1, 1, "00", "01", "1E", "System"); //mic type
    editDetails()->page()->addComboBox(0, 2, 1, 1, "00", "01", "1F", "System"); //mic dist
    editDetails()->page()->addKnob(0, 3, 1, 1, "00", "01", "20", "System");  //mic pos
    editDetails()->page()->addKnob(0, 4, 1, 1, "00", "01", "21", "System");   //mic level
    editDetails()->page()->addKnob(0, 5, 1, 1, "00", "01", "22", "System");   // direct mix
    editDetails()->page()->addGroupBox(3, 0, 1, 1);

    editDetails()->page()->newGroupBox(tr("Solo"));
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "1B", "System");
    editDetails()->page()->addKnob(1, 0, 1, 1, "00", "01", "1C", "System");  //solo level
    editDetails()->page()->addGroupBox(0, 1, 4, 1);

    editDetails()->page()->insertStackField(1, 0, 2, 4, 1);

    editDetails()->page()->addGroupBox(0, 0, 1, 1);


    // Bright Button stack fields
    editDetails()->page()->newStackField(0);  //boss clean
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "19", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // jc-120
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "19", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0);  //jazz combo
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "19", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // full range
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //clean twin
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "19", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // pro crunch
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "19", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // tweed
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "19", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //delux crunch
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //boss crunch
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "19", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0);  //blues
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "19", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //wild crunch
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //stack crunch
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "19", "System");
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
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "19", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // bg drive
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "19", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0);  // bg rhythm
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "19", "System");
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
    editDetails()->page()->addComboBox(0, 0, 1, 1, "00", "01", "23", "System");  //type
    editDetails()->page()->addStackControl();
    editDetails()->page()->insertStackField(2, 0, 1, 1, 1);
    editDetails()->page()->addKnob(0, 2, 1, 1, "00", "01", "24", "System");  //bottom
    editDetails()->page()->addKnob(0, 3, 1, 1, "00", "01", "25", "System");  //edge
    editDetails()->page()->addKnob(0, 4, 1, 1, "00", "01", "28", "System");  //pre-lo
    editDetails()->page()->addKnob(0, 5, 1, 1, "00", "01", "29", "System");  //pre-hi
    editDetails()->page()->addKnob(0, 6, 1, 1, "00", "01", "2A", "System");  //character
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
    editDetails()->page()->addKnob(0, 0, 1, 1, "00", "01", "2B", "System");
    editDetails()->page()->addKnob(1, 0, 1, 1, "00", "01", "2C", "System");
    editDetails()->page()->addKnob(2, 0, 1, 2, "00", "01", "2D", "System");
    editDetails()->page()->addComboBox(3, 0, 1, 1, "00", "01", "2E", "System");
    editDetails()->page()->addComboBox(4, 0, 1, 1, "00", "01", "2F", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(2);
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "19", "System");
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "19", "System");
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "19", "System");
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "19", "System");
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);editDetails()->page()->addStackField();

    editDetails()->addPage("00", "00", "2F", "04", "Tables");

    /////////////////////////////////////////////////// preamp B #1 //////////////////////////////////////////////
    editDetails()->page()->newGroupBox(tr("SYSTEM 1 Channel B"));
    editDetails()->page()->addLabel(0, 0, 1, 1, "System PreAmp " + text);

    editDetails()->page()->newGroupBox(tr("Pre Amp"));
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "30", "System");         // off/on effect
    editDetails()->page()->newStackControl(0);
    editDetails()->page()->addComboBox(0, 1, 1, 1, "00", "01", "31", "System");        //pre type
    editDetails()->page()->addStackControl();
    editDetails()->page()->addComboBox(0, 2, 1, 1, "00", "01", "3A", "System");        //gain sw
    editDetails()->page()->addKnob(0, 3, 1, 1, "00", "01", "32", "System");            // gain
    editDetails()->page()->addKnob(0, 4, 1, 1, "00", "01", "33", "System");            //T-Comp
    editDetails()->page()->addKnob(0, 5, 1, 1, "00", "01", "34", "System");            //bass
    editDetails()->page()->addKnob(0, 6, 1, 1, "00", "01", "35", "System");            // mid
    editDetails()->page()->addKnob(0, 7, 1, 1, "00", "01", "36", "System");            // treble
    editDetails()->page()->addKnob(0, 8, 1, 1, "00", "01", "37", "System");            // presence
    editDetails()->page()->addKnob(0, 9, 1, 1, "00", "01", "38", "System");            // effect level
    editDetails()->page()->addGroupBox(1, 0, 1, 1);

    editDetails()->page()->insertStackField(0, 2, 0, 1, 1);                // bright button

    editDetails()->page()->newGroupBox(tr("Speaker"));
    editDetails()->page()->newStackControl(1);
    editDetails()->page()->addComboBox(0, 0, 1, 1, "00", "01", "3D", "System");     //type
    editDetails()->page()->addStackControl();
    editDetails()->page()->addComboBox(0, 1, 1, 1, "00", "01", "3E", "System"); //mic type
    editDetails()->page()->addComboBox(0, 2, 1, 1, "00", "01", "3F", "System"); //mic dist
    editDetails()->page()->addKnob(0, 3, 1, 1, "00", "01", "40", "System");  //mic pos
    editDetails()->page()->addKnob(0, 4, 1, 1, "00", "01", "41", "System");   //mic level
    editDetails()->page()->addKnob(0, 5, 1, 1, "00", "01", "42", "System");   // direct mix
    editDetails()->page()->addGroupBox(3, 0, 1, 1);

    editDetails()->page()->newGroupBox(tr("Solo"));
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "3B", "System");
    editDetails()->page()->addKnob(1, 0, 1, 1, "00", "01", "3C", "System");  //solo level
    editDetails()->page()->addGroupBox(0, 1, 4, 1);

    editDetails()->page()->insertStackField(1, 0, 2, 4, 1);

    editDetails()->page()->addGroupBox(0, 0, 1, 1);


    // Bright Button stack fields
    editDetails()->page()->newStackField(0);  //boss clean
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "39", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // jc-120
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "39", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0);  //jazz combo
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "39", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // full range
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //clean twin
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "39", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // pro crunch
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "39", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // tweed
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "39", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //delux crunch
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //boss crunch
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "39", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0);  //blues
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "39", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //wild crunch
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //stack crunch
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "39", "System");
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
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "39", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // bg drive
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "39", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0);  // bg rhythm
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "39", "System");
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
    editDetails()->page()->addComboBox(0, 0, 1, 1, "00", "01", "43", "System");  //type
    editDetails()->page()->addStackControl();
    editDetails()->page()->insertStackField(2, 0, 1, 1, 1);
    editDetails()->page()->addKnob(0, 2, 1, 1, "00", "01", "44", "System");  //bottom
    editDetails()->page()->addKnob(0, 3, 1, 1, "00", "01", "45", "System");  //edge
    editDetails()->page()->addKnob(0, 4, 1, 1, "00", "01", "48", "System");  //pre-lo
    editDetails()->page()->addKnob(0, 5, 1, 1, "00", "01", "49", "System");  //pre-hi
    editDetails()->page()->addKnob(0, 6, 1, 1, "00", "01", "4A", "System");  //character
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
    editDetails()->page()->addKnob(0, 0, 1, 1, "00", "01", "4B", "System");
    editDetails()->page()->addKnob(1, 0, 1, 1, "00", "01", "4C", "System");
    editDetails()->page()->addKnob(2, 0, 1, 2, "00", "01", "4D", "System");
    editDetails()->page()->addComboBox(3, 0, 1, 1, "00", "01", "4E", "System");
    editDetails()->page()->addComboBox(4, 0, 1, 1, "00", "01", "4F", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(2);
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "39", "System");
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "39", "System");
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "39", "System");
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "39", "System");
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);editDetails()->page()->addStackField();

    editDetails()->addPage("00", "00", "2F", "05", "Tables");

    /////////////////////////////////// preamp A #2 ///////////////////////////////////////////

    editDetails()->page()->newGroupBox(tr("SYSTEM 2 Channel A"));
    editDetails()->page()->addLabel(0, 0, 1, 1, "System PreAmp " + text);

    editDetails()->page()->newGroupBox(tr("Pre Amp"));
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "50", "System");         // off/on effect
    editDetails()->page()->newStackControl(0);
    editDetails()->page()->addComboBox(0, 1, 1, 1, "00", "01", "51", "System");        //pre type
    editDetails()->page()->addStackControl();
    editDetails()->page()->addComboBox(0, 2, 1, 1, "00", "01", "5A", "System");        //gain sw
    editDetails()->page()->addKnob(0, 3, 1, 1, "00", "01", "52", "System");            // gain
    editDetails()->page()->addKnob(0, 4, 1, 1, "00", "01", "53", "System");            //T-Comp
    editDetails()->page()->addKnob(0, 5, 1, 1, "00", "01", "54", "System");            //bass
    editDetails()->page()->addKnob(0, 6, 1, 1, "00", "01", "55", "System");            // mid
    editDetails()->page()->addKnob(0, 7, 1, 1, "00", "01", "56", "System");            // treble
    editDetails()->page()->addKnob(0, 8, 1, 1, "00", "01", "57", "System");            // presence
    editDetails()->page()->addKnob(0, 9, 1, 1, "00", "01", "58", "System");            // effect level
    editDetails()->page()->addGroupBox(1, 0, 1, 1);

    editDetails()->page()->insertStackField(0, 2, 0, 1, 1);                // bright button

    editDetails()->page()->newGroupBox(tr("Speaker"));
    editDetails()->page()->newStackControl(1);
    editDetails()->page()->addComboBox(0, 0, 1, 1, "00", "01", "5D", "System");     //type
    editDetails()->page()->addStackControl();
    editDetails()->page()->addComboBox(0, 1, 1, 1, "00", "01", "5E", "System"); //mic type
    editDetails()->page()->addComboBox(0, 2, 1, 1, "00", "01", "5F", "System"); //mic dist
    editDetails()->page()->addKnob(0, 3, 1, 1, "00", "01", "60", "System");  //mic pos
    editDetails()->page()->addKnob(0, 4, 1, 1, "00", "01", "61", "System");   //mic level
    editDetails()->page()->addKnob(0, 5, 1, 1, "00", "01", "62", "System");   // direct mix
    editDetails()->page()->addGroupBox(3, 0, 1, 1);

    editDetails()->page()->newGroupBox(tr("Solo"));
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "5B", "System");
    editDetails()->page()->addKnob(1, 0, 1, 1, "00", "01", "5C", "System");  //solo level
    editDetails()->page()->addGroupBox(0, 1, 4, 1);

    editDetails()->page()->insertStackField(1, 0, 2, 4, 1);

    editDetails()->page()->addGroupBox(0, 0, 1, 1);


    // Bright Button stack fields
    editDetails()->page()->newStackField(0);  //boss clean
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "59", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // jc-120
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "59", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0);  //jazz combo
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "59", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // full range
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //clean twin
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "59", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // pro crunch
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "59", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // tweed
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "59", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //delux crunch
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //boss crunch
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "59", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0);  //blues
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "59", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //wild crunch
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //stack crunch
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "59", "System");
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
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "59", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // bg drive
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "59", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0);  // bg rhythm
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "59", "System");
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
    editDetails()->page()->addComboBox(0, 0, 1, 1, "00", "01", "63", "System");  //type
    editDetails()->page()->addStackControl();
    editDetails()->page()->insertStackField(2, 0, 1, 1, 1);
    editDetails()->page()->addKnob(0, 2, 1, 1, "00", "01", "64", "System");  //bottom
    editDetails()->page()->addKnob(0, 3, 1, 1, "00", "01", "65", "System");  //edge
    editDetails()->page()->addKnob(0, 4, 1, 1, "00", "01", "68", "System");  //pre-lo
    editDetails()->page()->addKnob(0, 5, 1, 1, "00", "01", "69", "System");  //pre-hi
    editDetails()->page()->addKnob(0, 6, 1, 1, "00", "01", "6A", "System");  //character
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
    editDetails()->page()->addKnob(0, 0, 1, 1, "00", "01", "6B", "System");
    editDetails()->page()->addKnob(1, 0, 1, 1, "00", "01", "6C", "System");
    editDetails()->page()->addKnob(2, 0, 1, 2, "00", "01", "6D", "System");
    editDetails()->page()->addComboBox(3, 0, 1, 1, "00", "01", "6E", "System");
    editDetails()->page()->addComboBox(4, 0, 1, 1, "00", "01", "6F", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(2);
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "59", "System");
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "59", "System");
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "59", "System");
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "59", "System");
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);editDetails()->page()->addStackField();

    editDetails()->addPage("00", "00", "2F", "06", "Tables");


    /////////////////////////////////////////////////// preamp B #2 //////////////////////////////////////////////
    editDetails()->page()->newGroupBox(tr("SYSTEM 2 Channel B"));
    editDetails()->page()->addLabel(0, 0, 1, 1, "System PreAmp " + text);

    editDetails()->page()->newGroupBox(tr("Pre Amp"));
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "70", "System");         // off/on effect
    editDetails()->page()->newStackControl(0);
    editDetails()->page()->addComboBox(0, 1, 1, 1, "00", "01", "71", "System");        //pre type
    editDetails()->page()->addStackControl();
    editDetails()->page()->addComboBox(0, 2, 1, 1, "00", "01", "7A", "System");        //gain sw
    editDetails()->page()->addKnob(0, 3, 1, 1, "00", "01", "72", "System");            // gain
    editDetails()->page()->addKnob(0, 4, 1, 1, "00", "01", "73", "System");            //T-Comp
    editDetails()->page()->addKnob(0, 5, 1, 1, "00", "01", "74", "System");            //bass
    editDetails()->page()->addKnob(0, 6, 1, 1, "00", "01", "75", "System");            // mid
    editDetails()->page()->addKnob(0, 7, 1, 1, "00", "01", "76", "System");            // treble
    editDetails()->page()->addKnob(0, 8, 1, 1, "00", "01", "77", "System");            // presence
    editDetails()->page()->addKnob(0, 9, 1, 1, "00", "01", "78", "System");            // effect level
    editDetails()->page()->addGroupBox(1, 0, 1, 1);

    editDetails()->page()->insertStackField(0, 2, 0, 1, 1);                // bright button

    editDetails()->page()->newGroupBox(tr("Speaker"));
    editDetails()->page()->newStackControl(1);
    editDetails()->page()->addComboBox(0, 0, 1, 1, "00", "01", "7D", "System");     //type
    editDetails()->page()->addStackControl();
    editDetails()->page()->addComboBox(0, 1, 1, 1, "00", "01", "7E", "System"); //mic type
    editDetails()->page()->addComboBox(0, 2, 1, 1, "00", "01", "7F", "System"); //mic dist
    editDetails()->page()->addKnob(0, 3, 1, 1, "00", "02", "00", "System");  //mic pos
    editDetails()->page()->addKnob(0, 4, 1, 1, "00", "02", "01", "System");   //mic level
    editDetails()->page()->addKnob(0, 5, 1, 1, "00", "02", "02", "System");   // direct mix
    editDetails()->page()->addGroupBox(3, 0, 1, 1);

    editDetails()->page()->newGroupBox(tr("Solo"));
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "7B", "System");
    editDetails()->page()->addKnob(1, 0, 1, 1, "00", "01", "7C", "System");  //solo level
    editDetails()->page()->addGroupBox(0, 1, 4, 1);

    editDetails()->page()->insertStackField(1, 0, 2, 4, 1);

    editDetails()->page()->addGroupBox(0, 0, 1, 1);


    // Bright Button stack fields
    editDetails()->page()->newStackField(0);  //boss clean
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "79", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // jc-120
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "79", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0);  //jazz combo
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "79", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // full range
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //clean twin
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "79", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // pro crunch
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "79", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // tweed
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "79", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //delux crunch
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //boss crunch
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "79", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0);  //blues
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "79", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //wild crunch
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //stack crunch
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "79", "System");
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
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "79", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // bg drive
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "79", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0);  // bg rhythm
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "79", "System");
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
    editDetails()->page()->addComboBox(0, 0, 1, 1, "00", "02", "03", "System");  //type
    editDetails()->page()->addStackControl();
    editDetails()->page()->insertStackField(2, 0, 1, 1, 1);
    editDetails()->page()->addKnob(0, 2, 1, 1, "00", "02", "04", "System");  //bottom
    editDetails()->page()->addKnob(0, 3, 1, 1, "00", "02", "05", "System");  //edge
    editDetails()->page()->addKnob(0, 4, 1, 1, "00", "02", "08", "System");  //pre-lo
    editDetails()->page()->addKnob(0, 5, 1, 1, "00", "02", "09", "System");  //pre-hi
    editDetails()->page()->addKnob(0, 6, 1, 1, "00", "02", "0A", "System");  //character
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
    editDetails()->page()->addKnob(0, 0, 1, 1, "00", "02", "0B", "System");
    editDetails()->page()->addKnob(1, 0, 1, 1, "00", "02", "0C", "System");
    editDetails()->page()->addKnob(2, 0, 1, 2, "00", "02", "0D", "System");
    editDetails()->page()->addComboBox(3, 0, 1, 1, "00", "02", "0E", "System");
    editDetails()->page()->addComboBox(4, 0, 1, 1, "00", "02", "0F", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(2);
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "79", "System");
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "79", "System");
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "79", "System");
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "01", "79", "System");
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);editDetails()->page()->addStackField();

    editDetails()->addPage("00", "00", "2F", "07", "Tables");

    /////////////////////////////////// preamp A #3 ///////////////////////////////////////////

    editDetails()->page()->newGroupBox(tr("SYSTEM 3 Channel A"));
    editDetails()->page()->addLabel(0, 0, 1, 1, "System PreAmp " + text);

    editDetails()->page()->newGroupBox(tr("Pre Amp"));
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "10", "System");         // off/on effect
    editDetails()->page()->newStackControl(0);
    editDetails()->page()->addComboBox(0, 1, 1, 1, "00", "02", "11", "System");        //pre type
    editDetails()->page()->addStackControl();
    editDetails()->page()->addComboBox(0, 2, 1, 1, "00", "02", "1A", "System");        //gain sw
    editDetails()->page()->addKnob(0, 3, 1, 1, "00", "02", "12", "System");            // gain
    editDetails()->page()->addKnob(0, 4, 1, 1, "00", "02", "13", "System");            //T-Comp
    editDetails()->page()->addKnob(0, 5, 1, 1, "00", "02", "14", "System");            //bass
    editDetails()->page()->addKnob(0, 6, 1, 1, "00", "02", "15", "System");            // mid
    editDetails()->page()->addKnob(0, 7, 1, 1, "00", "02", "16", "System");            // treble
    editDetails()->page()->addKnob(0, 8, 1, 1, "00", "02", "17", "System");            // presence
    editDetails()->page()->addKnob(0, 9, 1, 1, "00", "02", "18", "System");            // effect level
    editDetails()->page()->addGroupBox(1, 0, 1, 1);

    editDetails()->page()->insertStackField(0, 2, 0, 1, 1);                // bright button

    editDetails()->page()->newGroupBox(tr("Speaker"));
    editDetails()->page()->newStackControl(1);
    editDetails()->page()->addComboBox(0, 0, 1, 1, "00", "02", "1D", "System");     //type
    editDetails()->page()->addStackControl();
    editDetails()->page()->addComboBox(0, 1, 1, 1, "00", "02", "1E", "System"); //mic type
    editDetails()->page()->addComboBox(0, 2, 1, 1, "00", "02", "1F", "System"); //mic dist
    editDetails()->page()->addKnob(0, 3, 1, 1, "00", "02", "20", "System");  //mic pos
    editDetails()->page()->addKnob(0, 4, 1, 1, "00", "02", "21", "System");   //mic level
    editDetails()->page()->addKnob(0, 5, 1, 1, "00", "02", "22", "System");   // direct mix
    editDetails()->page()->addGroupBox(3, 0, 1, 1);

    editDetails()->page()->newGroupBox(tr("Solo"));
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "1B", "System");
    editDetails()->page()->addKnob(1, 0, 1, 1, "00", "02", "1C", "System");  //solo level
    editDetails()->page()->addGroupBox(0, 1, 4, 1);

    editDetails()->page()->insertStackField(1, 0, 2, 4, 1);

    editDetails()->page()->addGroupBox(0, 0, 1, 1);


    // Bright Button stack fields
    editDetails()->page()->newStackField(0);  //boss clean
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "19", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // jc-120
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "19", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0);  //jazz combo
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "19", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // full range
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //clean twin
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "19", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // pro crunch
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "19", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // tweed
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "19", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //delux crunch
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //boss crunch
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "19", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0);  //blues
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "19", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //wild crunch
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //stack crunch
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "19", "System");
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
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "19", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // bg drive
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "19", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0);  // bg rhythm
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "19", "System");
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
    editDetails()->page()->addComboBox(0, 0, 1, 1, "00", "02", "23", "System");  //type
    editDetails()->page()->addStackControl();
    editDetails()->page()->insertStackField(2, 0, 1, 1, 1);
    editDetails()->page()->addKnob(0, 2, 1, 1, "00", "02", "24", "System");  //bottom
    editDetails()->page()->addKnob(0, 3, 1, 1, "00", "02", "25", "System");  //edge
    editDetails()->page()->addKnob(0, 4, 1, 1, "00", "02", "28", "System");  //pre-lo
    editDetails()->page()->addKnob(0, 5, 1, 1, "00", "02", "29", "System");  //pre-hi
    editDetails()->page()->addKnob(0, 6, 1, 1, "00", "02", "2A", "System");  //character
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
    editDetails()->page()->addKnob(0, 0, 1, 1, "00", "02", "2B", "System");
    editDetails()->page()->addKnob(1, 0, 1, 1, "00", "02", "2C", "System");
    editDetails()->page()->addKnob(2, 0, 1, 2, "00", "02", "2D", "System");
    editDetails()->page()->addComboBox(3, 0, 1, 1, "00", "02", "2E", "System");
    editDetails()->page()->addComboBox(4, 0, 1, 1, "00", "02", "2F", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(2);
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "19", "System");
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "19", "System");
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "19", "System");
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "19", "System");
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);editDetails()->page()->addStackField();

    editDetails()->addPage("00", "00", "2F", "08", "Tables");

    /////////////////////////////////////////////////// preamp B #3 //////////////////////////////////////////////
    editDetails()->page()->newGroupBox(tr("SYSTEM 3 Channel B"));
    editDetails()->page()->addLabel(0, 0, 1, 1, "System PreAmp " + text);

    editDetails()->page()->newGroupBox(tr("Pre Amp"));
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "30", "System");         // off/on effect
    editDetails()->page()->newStackControl(0);
    editDetails()->page()->addComboBox(0, 1, 1, 1, "00", "02", "31", "System");        //pre type
    editDetails()->page()->addStackControl();
    editDetails()->page()->addComboBox(0, 2, 1, 1, "00", "02", "3A", "System");        //gain sw
    editDetails()->page()->addKnob(0, 3, 1, 1, "00", "02", "32", "System");            // gain
    editDetails()->page()->addKnob(0, 4, 1, 1, "00", "02", "33", "System");            //T-Comp
    editDetails()->page()->addKnob(0, 5, 1, 1, "00", "02", "34", "System");            //bass
    editDetails()->page()->addKnob(0, 6, 1, 1, "00", "02", "35", "System");            // mid
    editDetails()->page()->addKnob(0, 7, 1, 1, "00", "02", "36", "System");            // treble
    editDetails()->page()->addKnob(0, 8, 1, 1, "00", "02", "37", "System");            // presence
    editDetails()->page()->addKnob(0, 9, 1, 1, "00", "02", "38", "System");            // effect level
    editDetails()->page()->addGroupBox(1, 0, 1, 1);

    editDetails()->page()->insertStackField(0, 2, 0, 1, 1);                // bright button

    editDetails()->page()->newGroupBox(tr("Speaker"));
    editDetails()->page()->newStackControl(1);
    editDetails()->page()->addComboBox(0, 0, 1, 1, "00", "02", "3D", "System");     //type
    editDetails()->page()->addStackControl();
    editDetails()->page()->addComboBox(0, 1, 1, 1, "00", "02", "3E", "System"); //mic type
    editDetails()->page()->addComboBox(0, 2, 1, 1, "00", "02", "3F", "System"); //mic dist
    editDetails()->page()->addKnob(0, 3, 1, 1, "00", "02", "40", "System");  //mic pos
    editDetails()->page()->addKnob(0, 4, 1, 1, "00", "02", "41", "System");   //mic level
    editDetails()->page()->addKnob(0, 5, 1, 1, "00", "02", "42", "System");   // direct mix
    editDetails()->page()->addGroupBox(3, 0, 1, 1);

    editDetails()->page()->newGroupBox(tr("Solo"));
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "3B", "System");
    editDetails()->page()->addKnob(1, 0, 1, 1, "00", "02", "3C", "System");  //solo level
    editDetails()->page()->addGroupBox(0, 1, 4, 1);

    editDetails()->page()->insertStackField(1, 0, 2, 4, 1);

    editDetails()->page()->addGroupBox(0, 0, 1, 1);


    // Bright Button stack fields
    editDetails()->page()->newStackField(0);  //boss clean
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "39", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // jc-120
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "39", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0);  //jazz combo
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "39", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // full range
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //clean twin
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "39", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // pro crunch
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "39", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // tweed
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "39", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //delux crunch
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //boss crunch
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "39", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0);  //blues
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "39", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //wild crunch
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); //stack crunch
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "39", "System");
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
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "39", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0); // bg drive
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "39", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(0);  // bg rhythm
    editDetails()->page()->newGroupBox("");
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "39", "System");
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
    editDetails()->page()->addComboBox(0, 0, 1, 1, "00", "02", "43", "System");  //type
    editDetails()->page()->addStackControl();
    editDetails()->page()->insertStackField(2, 0, 1, 1, 1);
    editDetails()->page()->addKnob(0, 2, 1, 1, "00", "02", "44", "System");  //bottom
    editDetails()->page()->addKnob(0, 3, 1, 1, "00", "02", "45", "System");  //edge
    editDetails()->page()->addKnob(0, 4, 1, 1, "00", "02", "48", "System");  //pre-lo
    editDetails()->page()->addKnob(0, 5, 1, 1, "00", "02", "49", "System");  //pre-hi
    editDetails()->page()->addKnob(0, 6, 1, 1, "00", "02", "4A", "System");  //character
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
    editDetails()->page()->addKnob(0, 0, 1, 1, "00", "02", "4B", "System");
    editDetails()->page()->addKnob(1, 0, 1, 1, "00", "02", "4C", "System");
    editDetails()->page()->addKnob(2, 0, 1, 2, "00", "02", "2D", "System");
    editDetails()->page()->addComboBox(3, 0, 1, 1, "00", "02", "4E", "System");
    editDetails()->page()->addComboBox(4, 0, 1, 1, "00", "02", "4F", "System");
    editDetails()->page()->addGroupBox(0, 0, 1, 1);
    editDetails()->page()->addStackField();

    editDetails()->page()->newStackField(2);
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "39", "System");
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "39", "System");
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "39", "System");
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);
    editDetails()->page()->addSwitch(0, 0, 1, 1, "00", "02", "39", "System");
    editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);editDetails()->page()->addStackField();
    editDetails()->page()->newStackField(2);editDetails()->page()->addStackField();

    editDetails()->addPage("00", "00", "2F", "09", "Tables");
}
