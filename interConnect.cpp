/****************************************************************************
**
** Copyright (C) 2007~2015 Colin Willcocks.
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

#include <QChar>
#include "interConnect.h"
#include "Preferences.h"
#include "MidiTable.h"
#include "SysxIO.h"
#include "midiIO.h"
#include "globalVariables.h"


interConnect::interConnect(QWidget *parent)
    : QWidget(parent)
{  

}

void interConnect::setValueDisplay(QString fxName, QString valueName, QString value)
{
    //this->valueDisplay->setMainText(fxName);
   // this->valueDisplay->setSubText(valueName, value);
}

void interConnect::valueChanged(bool value, QString hex1, QString hex2, QString hex3)
{

}

void interConnect::test()
{
   //QApplication::beep();
}



