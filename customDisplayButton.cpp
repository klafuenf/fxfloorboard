/****************************************************************************
**
** Copyright (C) 2007~2012 Colin Willcocks.
** All rights reserved.
** This file is part of "GT-100 FloorBoard".
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

#include <QtGui>
#include "customDisplayButton.h"
#include "globalVariables.h"


customDisplayButton::customDisplayButton(QString text, bool active, QPoint buttonPos, QWidget *parent,
                                         QString imagePath) : QWidget(parent)
{
    QSize imageSize = QPixmap(imagePath).size();
    QSize buttonSize =  QSize(imageSize.width(), imageSize.height()/2);
    QLabel *textLabel = new QLabel(this->parentWidget());
    textLabel->setObjectName("panelButton");
    textLabel->setText(text);
    textLabel->setAlignment(Qt::AlignCenter);
    textLabel->setGeometry(buttonPos.x()-buttonSize.width()+3, buttonPos.y()+buttonSize.height()/2, textLabel->width(), textLabel->height());
    this->button = new customPanelButton(0, active, buttonPos, this, imagePath);
}

void customDisplayButton::mousePressEvent(QMouseEvent *event)
{
    if ( event->button() == Qt::LeftButton )
    {
        this->dragStartPosition = event->pos();
        setFocus();
        emitValue(true);
    };
}

void customDisplayButton::mouseReleaseEvent(QMouseEvent *event)
{
    if ( event->button() == Qt::LeftButton )
    {
        clearFocus();
    };
}

void customDisplayButton::emitValue(bool value)
{
    this->active = value;
    emit valueChanged((bool)value);
}

void customDisplayButton::mouseMoveEvent(QMouseEvent *event)
{
    if (!(event->buttons() == Qt::LeftButton) && (event->pos() - dragStartPosition).manhattanLength() < QApplication::startDragDistance())
    {
        return;
    };
}

void customDisplayButton::setValue(bool value)
{
    this->button->setValue(value);
}

