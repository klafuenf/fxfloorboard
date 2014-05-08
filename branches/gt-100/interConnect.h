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

#ifndef INTERCONNECT_H
#define INTERCONNECT_H

#include <QtGui>
#include <QWidget>

class interConnect : public QWidget
{
    Q_OBJECT

public:
    interConnect(QWidget *parent = 0);

public slots:
    void setValueDisplay(QString fxName, QString valueName, QString value);
    void valueChanged(bool value, QString hex1, QString hex2, QString hex3); // Not used.
    void test();

protected:
    interConnect();

signals:
    void updateSignal();

};

#endif // INTERCONNECT_H
