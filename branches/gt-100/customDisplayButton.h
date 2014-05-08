/****************************************************************************
**
** Copyright (C) 2007~2014 Colin Willcocks.
** Copyright (C) 2005~2007 Uco Mesdag. 
** All rights reserved.
** This file is part of "GR-55 FloorBoard".
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

#ifndef CUSTOMDISPLAYBUTTON_H
#define CUSTOMDISPLAYBUTTON_H

#include <QWidget>
#include "customPanelButton.h"

class customDisplayButton : public QWidget
{
    Q_OBJECT

public:
    customDisplayButton(
            QString text,
            bool active = false,
            QPoint buttonPos = QPoint(0, 0),
            QWidget *parent = 0,
            QString imagePath = ":/images/button.png");

public slots:
    void setValue(bool value);

signals:
    void valueChanged(bool value);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    customPanelButton *button;
    void emitValue(bool value);
    QString text;
    bool active;
    bool on;
    QString imagePath;
    QSize buttonSize;
    QPoint buttonPos;
    QPoint dragStartPosition;
};

#endif // CUSTOMPANELBUTTON_H
