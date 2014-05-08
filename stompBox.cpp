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

#include "stompBox.h"
#include "MidiTable.h"
#include "SysxIO.h"
#include "globalVariables.h"
#include "floorBoardDisplay.h"
#include "floorBoard.h"

stompBox::stompBox(QWidget *parent, unsigned int id, QString imagePath, QPoint stompPos)
    : QWidget(parent)
{
    this->id = id;
    this->imagePath = imagePath;
    this->stompSize = QPixmap(imagePath).size();
    this->stompPos = stompPos;
    this->setFixedSize(stompSize);
    this->editDialog = new editWindow();
    this->setWhatsThis(tr("StompBox effect<br>most can be dragged to a new chain position by holding down the mouse button while dragging the stompbox,<br>release the mouse button over the new location.<br>a double mouse click will open the effect edit page."));

    this->pathSwitch = new customButton(tr(""), false, QPoint(60, 60), this, ":/images/pathswitch.png");
    this->pathSwitch->hide();

    QObject::connect(this, SIGNAL( valueChanged(QString, QString, QString) ), this->parent(), SIGNAL( valueChanged(QString, QString, QString) ));

    QObject::connect(this->editDetails(), SIGNAL( valueUpdate(QString, QString, QString) ), this->parent(), SIGNAL( valueChanged(QString, QString, QString) ));

    QObject::connect(this->parent(), SIGNAL( updateStompOffset(signed int) ), this, SLOT( updatePos(signed int) ));

    QObject::connect(this->parent(), SIGNAL( updateSignal() ), this, SLOT( updateSignal() ));

    QObject::connect( this->editDetails()->swap_Button, SIGNAL(mouseReleased()),this->parent(), SIGNAL( updateSignal() ));

    QObject::connect(this->editDialog, SIGNAL( updateSignal() ), this, SLOT( updateSignal() ));

    QObject::connect(this, SIGNAL( dialogUpdateSignal() ), this->editDialog, SIGNAL( dialogUpdateSignal() ));

    QObject::connect(this->parent(), SIGNAL( updateSignal() ), this->editDialog, SIGNAL( dialogUpdateSignal() ));

    //QObject::connect(this->editDialog, SIGNAL( updateSignal() ), this, SLOT( setDisplayToFxName() ));

    QObject::connect(this, SIGNAL( setEditDialog( editWindow*) ), this->parent(), SLOT( setEditDialog(editWindow*) ));

    QObject::connect(this->pathSwitch, SIGNAL( valueChanged(bool)), this, SLOT( pathSwitchSignal(bool) ));

    QObject::connect(this->parent(), SIGNAL( pathUpdateSignal() ), this, SIGNAL( pathUpdateSignal() ));

    QObject::connect(this, SIGNAL( pathUpdateSignal() ), this, SLOT( updateStompPath() ));

    QObject::connect(this, SIGNAL( updateStompBoxes() ), this->parent(), SLOT( updateStompBoxes() ));

    QObject::connect(this, SIGNAL( switchSignal() ), this->parent(), SIGNAL( updateSignal() ));

    QObject::connect(this->parent(), SIGNAL(chain_buttonSignal(bool)), this, SLOT(chain_ButtonSignal(bool) ));
    QObject::connect(this->parent(), SIGNAL(chain_buttonSignal(bool)), this->parent(), SLOT(menuButtonSignal()));

    QObject::connect(this->parent(), SIGNAL(ch_mode_buttonSignal(bool)), this, SLOT(ch_mode_ButtonSignal(bool) ));
    QObject::connect(this, SIGNAL(ch_mode_statusSignal(bool)), this->parent(), SIGNAL(ch_mode_statusSignal(bool)));
    QObject::connect(this->parent(), SIGNAL(ch_mode_buttonSignal(bool)), this->parent(), SLOT(menuButtonSignal()));

    QObject::connect(this->parent(), SIGNAL(channel_Mix_buttonSignal(bool)), this, SLOT(channel_Mix_ButtonSignal(bool) ));
    QObject::connect(this, SIGNAL(channel_Mix_statusSignal(bool)), this->parent(), SIGNAL(channel_Mix_statusSignal(bool)));
    QObject::connect(this->parent(), SIGNAL(channel_Mix_buttonSignal(bool)), this->parent(), SLOT(menuButtonSignal()));

    QObject::connect(this, SIGNAL(channel_A_statusSignal(bool)), this->parent(), SIGNAL(channel_A_statusSignal(bool)));

    QObject::connect(this, SIGNAL(channel_B_statusSignal(bool)), this->parent(), SIGNAL(channel_B_statusSignal(bool)));

    QObject::connect(this->parent(), SIGNAL(preamp1_buttonSignal(bool)), this, SLOT(preamp1_ButtonSignal(bool) ));
    QObject::connect(this, SIGNAL(preamp1_statusSignal(bool)), this->parent(), SIGNAL(preamp1_statusSignal(bool)));
    QObject::connect(this->parent(), SIGNAL(preamp1_buttonSignal(bool)), this->parent(), SLOT(menuButtonSignal()));

    QObject::connect(this->parent(), SIGNAL(preamp2_buttonSignal(bool)), this, SLOT(preamp2_ButtonSignal(bool) ));
    QObject::connect(this, SIGNAL(preamp2_statusSignal(bool)), this->parent(), SIGNAL(preamp2_statusSignal(bool)));
    QObject::connect(this->parent(), SIGNAL(preamp2_buttonSignal(bool)), this->parent(), SLOT(menuButtonSignal()));
    QObject::connect(this, SIGNAL(solo1_statusSignal(bool)), this->parent(), SIGNAL(solo1_statusSignal(bool)));
    QObject::connect(this, SIGNAL(solo2_statusSignal(bool)), this->parent(), SIGNAL(solo2_statusSignal(bool)));

    QObject::connect(this->parent(), SIGNAL(distortion_buttonSignal(bool)), this, SLOT(distortion_ButtonSignal(bool) ));
    QObject::connect(this, SIGNAL(distortion_statusSignal(bool)), this->parent(), SIGNAL(distortion_statusSignal(bool)));
    QObject::connect(this->parent(), SIGNAL(distortion_buttonSignal(bool)), this->parent(), SLOT(menuButtonSignal()));

    QObject::connect(this->parent(), SIGNAL(compressor_buttonSignal(bool)), this, SLOT(compressor_ButtonSignal(bool) ));
    QObject::connect(this, SIGNAL(compressor_statusSignal(bool)), this->parent(), SIGNAL(compressor_statusSignal(bool)));
    QObject::connect(this->parent(), SIGNAL(compressor_buttonSignal(bool)), this->parent(), SLOT(menuButtonSignal()));

    QObject::connect(this->parent(), SIGNAL(ns1_buttonSignal(bool)), this, SLOT(ns1_ButtonSignal(bool) ));
    QObject::connect(this, SIGNAL(ns1_statusSignal(bool)), this->parent(), SIGNAL(ns1_statusSignal(bool)));
    QObject::connect(this->parent(), SIGNAL(ns1_buttonSignal(bool)), this->parent(), SLOT(menuButtonSignal()));

    QObject::connect(this->parent(), SIGNAL(ns2_buttonSignal(bool)), this, SLOT(ns2_ButtonSignal(bool) ));
    QObject::connect(this, SIGNAL(ns2_statusSignal(bool)), this->parent(), SIGNAL(ns2_statusSignal(bool)));
    QObject::connect(this->parent(), SIGNAL(ns2_buttonSignal(bool)), this->parent(), SLOT(menuButtonSignal()));

    QObject::connect(this->parent(), SIGNAL(fx1_buttonSignal(bool)), this, SLOT(fx1_ButtonSignal(bool) ));
    QObject::connect(this, SIGNAL(fx1_statusSignal(bool)), this->parent(), SIGNAL(fx1_statusSignal(bool)));
    QObject::connect(this->parent(), SIGNAL(fx1_buttonSignal(bool)), this->parent(), SLOT(menuButtonSignal()));

    QObject::connect(this->parent(), SIGNAL(fx2_buttonSignal(bool)), this, SLOT(fx2_ButtonSignal(bool) ));
    QObject::connect(this, SIGNAL(fx2_statusSignal(bool)), this->parent(), SIGNAL(fx2_statusSignal(bool)));
    QObject::connect(this->parent(), SIGNAL(fx2_buttonSignal(bool)), this->parent(), SLOT(menuButtonSignal()));

    QObject::connect(this->parent(), SIGNAL(fx3_buttonSignal(bool)), this, SLOT(fx3_ButtonSignal(bool) ));
    QObject::connect(this, SIGNAL(fx3_statusSignal(bool)), this->parent(), SIGNAL(fx3_statusSignal(bool)));
    QObject::connect(this->parent(), SIGNAL(fx3_buttonSignal(bool)), this->parent(), SLOT(menuButtonSignal()));

    QObject::connect(this->parent(), SIGNAL(reverb_buttonSignal(bool)), this, SLOT(reverb_ButtonSignal(bool) ));
    QObject::connect(this, SIGNAL(reverb_statusSignal(bool)), this->parent(), SIGNAL(reverb_statusSignal(bool)));
    QObject::connect(this->parent(), SIGNAL(reverb_buttonSignal(bool)), this->parent(), SLOT(menuButtonSignal()));

    QObject::connect(this->parent(), SIGNAL(delay_buttonSignal(bool)), this, SLOT(delay_ButtonSignal(bool) ));
    QObject::connect(this, SIGNAL(delay_statusSignal(bool)), this->parent(), SIGNAL(delay_statusSignal(bool)));
    QObject::connect(this->parent(), SIGNAL(delay_buttonSignal(bool)), this->parent(), SLOT(menuButtonSignal()));

    QObject::connect(this->parent(), SIGNAL(chorus_buttonSignal(bool)), this, SLOT(chorus_ButtonSignal(bool) ));
    QObject::connect(this, SIGNAL(chorus_statusSignal(bool)), this->parent(), SIGNAL(chorus_statusSignal(bool)));
    QObject::connect(this->parent(), SIGNAL(chorus_buttonSignal(bool)), this->parent(), SLOT(menuButtonSignal()));

    QObject::connect(this->parent(), SIGNAL(sendreturn_buttonSignal(bool)), this, SLOT(sendreturn_ButtonSignal(bool) ));
    QObject::connect(this, SIGNAL(sendreturn_statusSignal(bool)), this->parent(), SIGNAL(sendreturn_statusSignal(bool)));
    QObject::connect(this->parent(), SIGNAL(sendreturn_buttonSignal(bool)), this->parent(), SLOT(menuButtonSignal()));

    QObject::connect(this->parent(), SIGNAL(eq_buttonSignal(bool)), this, SLOT(eq_ButtonSignal(bool) ));
    QObject::connect(this, SIGNAL(eq_statusSignal(bool)), this->parent(), SIGNAL(eq_statusSignal(bool)));
    QObject::connect(this->parent(), SIGNAL(eq_buttonSignal(bool)), this->parent(), SLOT(menuButtonSignal()));

    QObject::connect(this->parent(), SIGNAL(pedal_buttonSignal(bool)), this, SLOT(pedal_ButtonSignal(bool) ));
    QObject::connect(this, SIGNAL(pedal_statusSignal(bool)), this->parent(), SIGNAL(pedal_statusSignal(bool)));
    QObject::connect(this->parent(), SIGNAL(pedal_buttonSignal(bool)), this->parent(), SLOT(menuButtonSignal()));

}

void stompBox::paintEvent(QPaintEvent *)
{
    QRectF target(0.0, 0.0, stompSize.width(), stompSize.height());
    QRectF source(0.0, 0.0, stompSize.width(), stompSize.height());
    QPixmap image(imagePath);

    this->image = image;

    QPainter painter(this);
    painter.drawPixmap(target, image, source);
}

editWindow* stompBox::editDetails()
{
    return this->editDialog;
}

void stompBox::mousePressEvent(QMouseEvent *event)
{
    emitValueChanged(this->hex1, this->hex2, "00", "void");

    if (event->button() == Qt::LeftButton)
    {
        this->dragStartPosition = event->pos();
    }
    else if (event->button() == Qt::RightButton)
    {
        emit switchSignal();
        this->editDialog->setWindow(this->fxName);
        emit setEditDialog(this->editDialog);
    };
}

void stompBox::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit switchSignal();
    this->editDialog->setWindow(this->fxName);
    emit setEditDialog(this->editDialog);
}

void stompBox::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        QPoint mousePoint = event->pos();
        QRect stompRect = this->rect();

        if ( /*(event->pos() - dragStartPosition).manhattanLength() > QApplication::startDragDistance() &&*/
             stompRect.contains(mousePoint) )
        {

            QByteArray itemData;
            QDataStream dataStream(&itemData, QIODevice::WriteOnly);
            dataStream << id << stompPos << stompSize << event->pos() - rect().topLeft();

            QMimeData *mimeData = new QMimeData;
            mimeData->setData("application/x-stompbox", itemData);
            mimeData->setText(this->objectName());

            QDrag *drag = new QDrag(this);
            drag->setMimeData(mimeData);
            drag->setHotSpot(event->pos() - rect().topLeft());

            QPixmap screen = QPixmap::grabWidget(this);
            screen.setMask(image.mask());

            QRectF source(4, 4, stompSize.width()-8, stompSize.height()-8);
            QRectF target(4, 4, stompSize.width()-8, stompSize.height()-8);

            QPixmap buffer = image;
            QPainter painter(&buffer);
            painter.drawPixmap(target, screen, source);
            painter.end();

            drag->setPixmap(buffer);

            hide();

            if (drag->start(Qt::MoveAction) != Qt::MoveAction)
            {
                event->ignore();
                show();
            };

            if(drag->source() != drag->target())
            {
                event->ignore();
                show();
            };
            if (this->id < 20) updateStompPath();
        };
    };
}

void stompBox::chain_ButtonSignal(bool value)
{
    if (this->id == 18)
    {
        setDisplayToFxName();
        this->editDialog->setWindow(tr("Signal Chain"));
        emit setEditDialog(this->editDialog);
    };
}

void stompBox::ch_mode_ButtonSignal(bool value)
{
    if (this->id == 17)
    {
        setDisplayToFxName();
        this->editDialog->setWindow(tr("Channel Divide"));
        emit setEditDialog(this->editDialog);
    };
}

void stompBox::channel_Mix_ButtonSignal(bool value)
{
    if (this->id == 19)
    {
        setDisplayToFxName();
        this->editDialog->setWindow(tr("Channel Mixer"));
        emit setEditDialog(this->editDialog);
    };
}

void stompBox::preamp1_ButtonSignal(bool value)
{
    if (this->id == 2)
    {
        setDisplayToFxName();
        this->editDialog->setWindow(this->fxName);
        emit setEditDialog(this->editDialog);
    };
}

void stompBox::preamp2_ButtonSignal(bool value)
{
    if (this->id == 3)
    {
        setDisplayToFxName();
        this->editDialog->setWindow(this->fxName);
        emit setEditDialog(this->editDialog);
    };
}

void stompBox::distortion_ButtonSignal(bool value)
{
    if (this->id == 15)
    {
        setDisplayToFxName();
        this->editDialog->setWindow(this->fxName);
        emit setEditDialog(this->editDialog);
    };
}

void stompBox::compressor_ButtonSignal(bool value)
{
    if (this->id == 0)
    {
        setDisplayToFxName();
        this->editDialog->setWindow(this->fxName);
        emit setEditDialog(this->editDialog);
    };
}

void stompBox::ns1_ButtonSignal(bool value)
{
    if (this->id == 13)
    {
        setDisplayToFxName();
        this->editDialog->setWindow(this->fxName);
        emit setEditDialog(this->editDialog);
    };
}

void stompBox::ns2_ButtonSignal(bool value)
{
    if (this->id == 14)
    {
        setDisplayToFxName();
        this->editDialog->setWindow(this->fxName);
        emit setEditDialog(this->editDialog);
    };
}

void stompBox::fx1_ButtonSignal(bool value)
{
    if (this->id == 5)
    {
        setDisplayToFxName();
        this->editDialog->setWindow(this->fxName);
        emit setEditDialog(this->editDialog);
    };
}

void stompBox::fx2_ButtonSignal(bool value)
{
    if (this->id == 6)
    {
        setDisplayToFxName();
        this->editDialog->setWindow(this->fxName);
        emit setEditDialog(this->editDialog);
    };
}

void stompBox::fx3_ButtonSignal(bool value)
{
    if (this->id == 10)
    {
        setDisplayToFxName();
        this->editDialog->setWindow(this->fxName);
        emit setEditDialog(this->editDialog);
    };
}

void stompBox::reverb_ButtonSignal(bool value)
{
    if (this->id == 9)
    {
        setDisplayToFxName();
        this->editDialog->setWindow(this->fxName);
        emit setEditDialog(this->editDialog);
    };
}

void stompBox::delay_ButtonSignal(bool value)
{
    if (this->id == 7)
    {
        setDisplayToFxName();
        this->editDialog->setWindow(this->fxName);
        emit setEditDialog(this->editDialog);
    };
}

void stompBox::chorus_ButtonSignal(bool value)
{
    if (this->id == 8)
    {
        setDisplayToFxName();
        this->editDialog->setWindow(this->fxName);
        emit setEditDialog(this->editDialog);
    };
}

void stompBox::sendreturn_ButtonSignal(bool value)
{
    if (this->id == 1)
    {
        setDisplayToFxName();
        this->editDialog->setWindow(this->fxName);
        emit setEditDialog(this->editDialog);
    };
}

void stompBox::eq_ButtonSignal(bool value)
{
    if (this->id == 4)
    {
        setDisplayToFxName();
        this->editDialog->setWindow(this->fxName);
        emit setEditDialog(this->editDialog);
    };
}

void stompBox::pedal_ButtonSignal(bool value)
{
    if (this->id == 11)
    {
        setDisplayToFxName();
        this->editDialog->setWindow(this->fxName);
        emit setEditDialog(this->editDialog);
    };
}

void stompBox::pathSwitchSignal(bool value)
{
    int hex_A = stompOrderName.indexOf("CN_S");
    int hex_B = stompOrderName.indexOf("CN_M1_S2");
    int hex_C = stompOrderName.indexOf("CN_M");
    int hex_Pos = stompOrderName.indexOf(this->namedata);
    if (hex_Pos > hex_A && hex_Pos < hex_C && this->id != 18){this->pathSwitch->show(); }else{this->pathSwitch->hide();};
    if (hex_Pos > hex_A && hex_Pos < hex_B){this->pathSwitch->setValue(false);}else{this->pathSwitch->setValue(true);};

    emit updateSignal();
    emit updateStompBoxes();
}

void stompBox::setPos(QPoint newPos)
{
    this->move(newPos);
    this->stompPos = newPos;
    updateStompPath();
}

void stompBox::updatePos(signed int offsetDif)
{
    this->stompPos = this->pos();
    QPoint newPos = stompPos + QPoint(offsetDif, 0);
    this->move(newPos);
    this->stompPos = newPos;
}

void stompBox::setImage(QString imagePath)
{
    this->imagePath = imagePath;
    this->update();
}

void stompBox::setSize(QSize newSize)
{
    this->stompSize = newSize;
    this->setFixedSize(stompSize);
}

void stompBox::setId(unsigned int id)
{
    this->id = id;
}

unsigned int stompBox::getId()
{
    return this->id;
}

void stompBox::setLSB(QString hex1, QString hex2)
{
    this->editDialog->setLSB(hex1, hex2);
}

void stompBox::setComboBox(QString hex1, QString hex2, QString hex3, QRect geometry)
{
    this->combo_hex1 = hex1;
    this->combo_hex2 = hex2;
    this->combo_hex3 = hex3;

    MidiTable *midiTable = MidiTable::Instance();
    Midi items = midiTable->getMidiMap("Structure", this->combo_hex1, this->combo_hex2, this->combo_hex3);

    this->stompComboBox = new customComboBox(this);
    this->stompComboBox->setObjectName("smallcombo");

    int itemcount = 0;
    for(itemcount=0;itemcount<items.level.size();itemcount++ )
    {
        QString item;
        QString desc = items.level.at(itemcount).desc;
        QString customdesc = items.level.at(itemcount).customdesc;
        if(!customdesc.isEmpty())
        {
            item = customdesc;
        }
        else
        {
            item = desc;
        };
        this->stompComboBox->addItem(item);
    };

    this->stompComboBox->setGeometry(geometry);
    this->stompComboBox->setEditable(false);
    this->stompComboBox->setFrame(false);
    this->stompComboBox->setMaxVisibleItems(itemcount);

    QObject::connect(this->stompComboBox, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(valueChanged(int)));

    QObject::connect(this->stompComboBox, SIGNAL(highlighted(int)),
                     this, SLOT(valueChanged(int)));
}

void stompBox::setComboBoxCurrentIndex(int index)
{
    this->stompComboBox->setCurrentIndex(index);
}

void stompBox::setKnob1(QString hex1, QString hex2, QString hex3)
{
    MidiTable *midiTable = MidiTable::Instance();
    int range = midiTable->getRange("Structure", hex1, hex2, hex3);
    knob1 = new customDial(0, 0, range, 1, 10, QPoint(6, 9), this, hex1, hex2, hex3);
    this->knob1->setWhatsThis(tr("hold down mouse button and drag up/down for quick adjustment")
                              + "<br>" + tr("use scroll wheel or up/down arrow keys for fine adjustment"));

}

void stompBox::setKnob2(QString hex1, QString hex2, QString hex3)
{
    MidiTable *midiTable = MidiTable::Instance();
    int range = midiTable->getRange("Structure", hex1, hex2, hex3);
    knob2 = new customDial(0, 0, range, 1, 10, QPoint(53, 9), this, hex1, hex2, hex3);
    this->knob2->setWhatsThis(tr("hold down mouse button and drag up/down for quick adjustment")
                              + "<br>" + tr("use scroll wheel or up/down arrow keys for fine adjustment"));

}

void stompBox::setSlider1(QString hex1, QString hex2, QString hex3)
{
    MidiTable *midiTable = MidiTable::Instance();
    int range = midiTable->getRange("Structure", hex1, hex2, hex3);
    slider1 = new customSlider(0, 0, range, 1, 10, QPoint(8, 17), this, hex1, hex2, hex3);
}

void stompBox::setSlider2(QString hex1, QString hex2, QString hex3)
{
    MidiTable *midiTable = MidiTable::Instance();
    int range = midiTable->getRange("Structure", hex1, hex2, hex3);
    slider2 = new customSlider(0, 0, range, 1, 10, QPoint(24, 17), this, hex1, hex2, hex3);
}

void stompBox::setSlider3(QString hex1, QString hex2, QString hex3)
{
    MidiTable *midiTable = MidiTable::Instance();
    int range = midiTable->getRange("Structure", hex1, hex2, hex3);
    slider3 = new customSlider(0, 0, range, 1, 10, QPoint(40, 17), this, hex1, hex2, hex3);
}

void stompBox::setSlider4(QString hex1, QString hex2, QString hex3)
{
    MidiTable *midiTable = MidiTable::Instance();
    int range = midiTable->getRange("Structure", hex1, hex2, hex3);
    slider4 = new customSlider(0, 0, range, 1, 10, QPoint(56, 17), this, hex1, hex2, hex3);
}

void stompBox::setSlider5(QString hex1, QString hex2, QString hex3)
{
    MidiTable *midiTable = MidiTable::Instance();
    int range = midiTable->getRange("Structure", hex1, hex2, hex3);
    slider5 = new customSlider(0, 0, range, 1, 10, QPoint(79, 17), this, hex1, hex2, hex3);
}

void stompBox::setButton(QString hex1, QString hex2, QString hex3)
{
    button = new customButton(false, QPoint(4, 110), this, hex1, hex2, hex3);
    led = new customLed(false, QPoint(41, 4), this);

    QObject::connect(button, SIGNAL(valueChanged(bool, QString, QString, QString)),
                     led, SLOT(changeValue(bool)));
}

void stompBox::setButton(QString hex1, QString hex2, QString hex3, QPoint pos, QString imagePath)
{
    button = new customButton(false, pos, this, hex1, hex2, hex3, imagePath);
    led = new customLed(false, QPoint(41, 4), this);

    QObject::connect(button, SIGNAL(valueChanged(bool, QString, QString, QString)),
                     led, SLOT(changeValue(bool)));
}

void stompBox::setSwitch(QString hex1, QString hex2, QString hex3)
{
    switchbutton = new customSwitch(false, this, hex1, hex2, hex3);
    switchbutton->move(QPoint(15, 45));
}

void stompBox::updateComboBox(QString hex1, QString hex2, QString hex3)
{
    QObject::disconnect(this->stompComboBox, SIGNAL(currentIndexChanged(int)), // To prevent sending a signal when loading a patch.
                        this, SLOT(valueChanged(int)));

    SysxIO *sysxIO = SysxIO::Instance();
    setComboBoxCurrentIndex(sysxIO->getSourceValue("Structure", this->combo_hex1, this->combo_hex2, this->combo_hex3));

    QObject::connect(this->stompComboBox, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(valueChanged(int)));
}

void stompBox::updateKnob1(QString hex1, QString hex2, QString hex3)
{
    SysxIO *sysxIO = SysxIO::Instance();
    knob1->setValue(sysxIO->getSourceValue("Structure", hex1, hex2, hex3));
}

void stompBox::updateKnob2(QString hex1, QString hex2, QString hex3)
{
    SysxIO *sysxIO = SysxIO::Instance();
    knob2->setValue(sysxIO->getSourceValue("Structure", hex1, hex2, hex3));
}

void stompBox::updateSlider1(QString hex1, QString hex2, QString hex3)
{
    SysxIO *sysxIO = SysxIO::Instance();
    slider1->setValue(sysxIO->getSourceValue("Structure", hex1, hex2, hex3));
}

void stompBox::updateSlider2(QString hex1, QString hex2, QString hex3)
{
    SysxIO *sysxIO = SysxIO::Instance();
    slider2->setValue(sysxIO->getSourceValue("Structure", hex1, hex2, hex3));
}

void stompBox::updateSlider3(QString hex1, QString hex2, QString hex3)
{
    SysxIO *sysxIO = SysxIO::Instance();
    slider3->setValue(sysxIO->getSourceValue("Structure", hex1, hex2, hex3));
}

void stompBox::updateSlider4(QString hex1, QString hex2, QString hex3)
{
    SysxIO *sysxIO = SysxIO::Instance();
    slider4->setValue(sysxIO->getSourceValue("Structure", hex1, hex2, hex3));
}

void stompBox::updateSlider5(QString hex1, QString hex2, QString hex3)
{
    SysxIO *sysxIO = SysxIO::Instance();
    slider5->setValue(sysxIO->getSourceValue("Structure", hex1, hex2, hex3));
}

void stompBox::updateButton(QString hex1, QString hex2, QString hex3)
{
    SysxIO *sysxIO = SysxIO::Instance();
    int value = sysxIO->getSourceValue("Structure", hex1, hex2, hex3);
    led->setValue((value==1)?true:false);
    button->setValue((value==1)?true:false);
}

void stompBox::updateSwitch(QString hex1, QString hex2, QString hex3)
{
    SysxIO *sysxIO = SysxIO::Instance();
    int value = sysxIO->getSourceValue("Structure", hex1, hex2, hex3);
    //     switchbutton->setValue((value==1)?true:false);
    bool set = false;
    bool _set = true;
    if (value > 0) {set = true; _set = false; };
    if (this->id == 0 && hex3 == "20") { emit compressor_statusSignal(set); };
    if (this->id == 1 && hex3 == "55") { emit sendreturn_statusSignal(set); };
    if (this->id == 2 && hex3 == "50") { emit preamp1_statusSignal(set); };
    if (this->id == 2 && hex3 == "5B") { emit solo1_statusSignal(set); };
    if (this->id == 3 && hex3 == "00") { emit preamp2_statusSignal(set); };
    if (this->id == 3 && hex3 == "0B") { emit solo2_statusSignal(set); };
    if (this->id == 4 && hex3 == "30") { emit eq_statusSignal(set); };
    if (this->id == 5 && hex3 == "40") { emit fx1_statusSignal(set); };
    if (this->id == 6 && hex3 == "4C") { emit fx2_statusSignal(set); };
    if (this->id == 7 && hex3 == "60") { emit delay_statusSignal(set); };
    if (this->id == 8 && hex3 == "00") { emit chorus_statusSignal(set); };
    if (this->id == 9 && hex3 == "10") { emit reverb_statusSignal(set); };
    if (this->id == 10){ emit fx3_statusSignal(set); };
    if (this->id == 11 && hex3 == "20"){ emit pedal_statusSignal(set); };
    if (this->id == 13 && hex3 == "63"){ emit ns1_statusSignal(set); };
    if (this->id == 14 && hex3 == "68"){ emit ns2_statusSignal(set); };
    if (this->id == 15 && hex3 == "30"){ emit distortion_statusSignal(set); };
    if (this->id == 17){
        int value2 = sysxIO->getSourceValue("Structure", "06", "00", "40");
        int value3 = sysxIO->getSourceValue("Structure", "06", "00", "41");
        if (value2 > 0){ emit channel_A_statusSignal(value2);
            emit channel_B_statusSignal(value2);
        } else {
            emit channel_B_statusSignal(value3);
            emit channel_A_statusSignal(!value3);
        };
    }; //toggle the Channel buttons
}

void stompBox::valueChanged(int value, QString hex1, QString hex2, QString hex3)
{
    QString valueHex = QString::number(value, 16).toUpper();
    if(valueHex.length() < 2) valueHex.prepend("0");
    emitValueChanged(hex1, hex2, hex3, valueHex);
}

void stompBox::valueChanged(bool value, QString hex1, QString hex2, QString hex3)
{
    int valueInt;
    (value)? valueInt=1: valueInt=0;
    QString valueHex = QString::number(valueInt, 16).toUpper();
    if(valueHex.length() < 2) valueHex.prepend("0");
    emitValueChanged(hex1, hex2, hex3, valueHex);
}

void stompBox::valueChanged(int index)
{
    QString valueHex = QString::number(index, 16).toUpper();
    if(valueHex.length() < 2) valueHex.prepend("0");
    emitValueChanged(this->combo_hex1, this->combo_hex2, this->combo_hex3, valueHex);
    MidiTable *midiTable = MidiTable::Instance();
    Midi items = midiTable->getMidiMap("Structure", this->combo_hex1, this->combo_hex2, this->combo_hex3);

    QString desc = items.level.at(index).desc;
    QString customdesc = items.level.at(index).customdesc;
    if(customdesc.isEmpty())
    {
        customdesc = desc;
    };

    this->stompComboBox->setCurrentIndex(index);
    this->stompComboBox->setEditText(desc);
}

void stompBox::emitValueChanged(QString hex1, QString hex2, QString hex3, QString valueHex)
{
    QString valueName, valueStr;
    if(hex1 != "void" && hex2 != "void")
    {
        MidiTable *midiTable = MidiTable::Instance();
        if(valueHex != "void")

        {
            SysxIO *sysxIO = SysxIO::Instance(); bool ok;
            if(midiTable->isData("Structure", hex1, hex2, hex3))
            {
                int maxRange = QString("7F").toInt(&ok, 16) + 1;
                int value = valueHex.toInt(&ok, 16);
                int dif = value/maxRange;
                QString valueHex1 = QString::number(dif, 16).toUpper();
                if(valueHex1.length() < 2) valueHex1.prepend("0");
                QString valueHex2 = QString::number(value - (dif * maxRange), 16).toUpper();
                if(valueHex2.length() < 2) valueHex2.prepend("0");
                sysxIO->setFileSource("Structure", hex1, hex2, hex3, valueHex1, valueHex2);
            }
            else
            {
                sysxIO->setFileSource("Structure", hex1, hex2, hex3, valueHex);
                emit dialogUpdateSignal();
                sysxIO->setFileSource("Structure", hex1, hex2, hex3, valueHex);
            };
            Midi items = midiTable->getMidiMap("Structure", hex1, hex2, hex3);
            valueName = items.customdesc;
            valueStr = midiTable->getValue("Structure", hex1, hex2, hex3, valueHex);
            emit valueChanged(this->fxName, valueName, valueStr);
            updateSwitch(hex1, hex2, hex3);
        };
    };
}

void stompBox::setDisplayToFxName()
{
    emit valueChanged(this->fxName, "", "");
}

void stompBox::updateStompPath()
{
    getStompOrder();

    if (this->id == 0) {this->hexdata_A = "00"; this->hexdata_B = "00"; this->namedata = "CS";   this->fxName = tr("Compressor");};
    if (this->id == 1) {this->hexdata_A = "01"; this->hexdata_B = "01"; this->namedata = "LP";   this->fxName = tr("Send/Return");};
    if (this->id == 2) {this->hexdata_A = "02"; this->hexdata_B = "02"; this->namedata = "CH_A"; this->fxName = tr("PreAmp/Speaker A");};
    if (this->id == 3) {this->hexdata_A = "03"; this->hexdata_B = "03"; this->namedata = "CH_B"; this->fxName = tr("PreAmp/Speaker B");};
    if (this->id == 4) {this->hexdata_A = "04"; this->hexdata_B = "04"; this->namedata = "EQ";   this->fxName = tr("Equalizer");};
    if (this->id == 5) {this->hexdata_A = "05"; this->hexdata_B = "05"; this->namedata = "FX1";  this->fxName = tr("FX-1");};
    if (this->id == 6) {this->hexdata_A = "06"; this->hexdata_B = "06"; this->namedata = "FX2";  this->fxName = tr("FX-2");};
    if (this->id == 7) {this->hexdata_A = "07"; this->hexdata_B = "07"; this->namedata = "DD";   this->fxName = tr("Delay");};
    if (this->id == 8) {this->hexdata_A = "08"; this->hexdata_B = "08"; this->namedata = "CE";   this->fxName = tr("Chorus");};
    if (this->id == 9) {this->hexdata_A = "09"; this->hexdata_B = "09"; this->namedata = "RV";   this->fxName = tr("Reverb");};
    if (this->id == 10){this->hexdata_A = "0A"; this->hexdata_B = "0A"; this->namedata = "FX3";  this->fxName = tr("Accel");};
    if (this->id == 11){this->hexdata_A = "0B"; this->hexdata_B = "0B"; this->namedata = "PDL";  this->fxName = tr("Pedal FX");};
    if (this->id == 12){this->hexdata_A = "0C"; this->hexdata_B = "0C"; this->namedata = "FV";   this->fxName = tr("Volume");};
    if (this->id == 13){this->hexdata_A = "0D"; this->hexdata_B = "0D"; this->namedata = "NS_1"; this->fxName = tr("Noise Suppressor 1");};
    if (this->id == 14){this->hexdata_A = "0E"; this->hexdata_B = "0E"; this->namedata = "NS_2"; this->fxName = tr("Noise Suppressor 2");};
    if (this->id == 15){this->hexdata_A = "0F"; this->hexdata_B = "0F"; this->namedata = "OD";   this->fxName = tr("Distortion");};
    if (this->id == 16){this->hexdata_A = "10"; this->hexdata_B = "10"; this->namedata = "USB"; this->fxName = tr("USB");};
    if (this->id == 17){this->hexdata_A = "11"; this->hexdata_B = "11"; this->namedata = "CN_S"; this->fxName = tr("Channel Divide");};
    if (this->id == 18){this->hexdata_A = "12"; this->hexdata_B = "12"; this->namedata = "CN_M1_S2"; this->fxName = tr("Chain");};
    if (this->id == 19){this->hexdata_A = "13"; this->hexdata_B = "13"; this->namedata = "CN_M"; this->fxName = tr("Channel Mixer");};

    int hex_A = stompOrderName.indexOf("CN_S");
    int hex_B = stompOrderName.indexOf("CN_M1_S2");
    int hex_C = stompOrderName.indexOf("CN_M");
    int hex_Pos = stompOrderName.indexOf(this->namedata);
    if (hex_Pos > hex_A && hex_Pos < hex_C && this->id != 2 && this->id != 3 && this->id != 18){this->pathSwitch->show(); }else{this->pathSwitch->hide();};
    if (hex_Pos > hex_A && hex_Pos < hex_B){this->pathSwitch->setValue(false);}else{this->pathSwitch->setValue(true);};

}

void stompBox::getStompOrder()
{
    SysxIO *sysxIO = SysxIO::Instance();
    QList<QString> fxChain = sysxIO->getFileSource("Structure", "07", "00");

    MidiTable *midiTable = MidiTable::Instance();
    QList<QString> stompOrderName;
    QString stompOrderHex;
    for(int i= sysxDataOffset+32;i< (sysxDataOffset+32 + 20);i++ )
    {
        stompOrderName.append( midiTable->getMidiMap("Structure", "07", "00", "20", fxChain.at(i)).name );
        stompOrderHex.append( midiTable->getMidiMap("Structure", "07", "00", "20", fxChain.at(i)).value );
        stompOrderHex.append(" ");
    };
    this->stompOrderName = stompOrderName;
    this->stompOrderHex = stompOrderHex;
}
