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

#ifndef FLOORBOARDDISPLAY_H
#define FLOORBOARDDISPLAY_H

#include <QtGui>
#include <QWidget>
#include <QTimer>
#include "customButton.h"
#include "customPanelButton.h"
#include "customControlListMenu.h"
#include "customDisplay.h"
#include "customLabelDisplay.h"
#include "initPatchListMenu.h"

class floorBoardDisplay : public QWidget
{
    Q_OBJECT

public:
    floorBoardDisplay(QWidget *parent = 0,
                      QPoint pos = QPoint(0, 0));
    QPoint getPos();

public slots:
    void setValueDisplay(QString fxName, QString valueName, QString value);
    void setPatchDisplay(QString patchName);
    void setPatchNumDisplay(int bank, int patch);
    void setPos(QPoint newPos);
    void updateDisplay();
    void set_temp();
    void temp1_copy(bool value);
    void temp1_paste(bool value);
    void temp2_copy(bool value);
    void temp2_paste(bool value);
    void temp3_copy(bool value);
    void temp3_paste(bool value);
    void temp4_copy(bool value);
    void temp4_paste(bool value);
    void temp5_copy(bool value);
    void temp5_paste(bool value);
    void save_temp(QString fileName, QString sysxMsg);
    void autoconnect();
    void autoConnectionResult(QString);
    void connectSignal(bool value);
    void connectionResult(QString);
    void autosyncSignal(bool value);
    void autosyncResult(QString);
    void writeSignal(bool value);
    void resetDevice(QString replyMsg);
    void patchSelectSignal(int bank, int patch);
    void blinkSellectedPatch(bool active = true);
    void patchLoadSignal(int bank, int patch);
    void notConnected();
    void patchChangeFailed();
    void writeToBuffer();
    void writeToMemory();
    void valueChanged(bool value, QString hex1, QString hex2, QString hex3); // Not used.
    void autosync();


signals:
    void updateSignal();
    void dialogUpdateSignal();
    void connectedSignal();
    void notConnectedSignal();

    void setStatusSymbol(int value);
    void setStatusProgress(int value);
    void setStatusMessage(QString message);

private:
    QPoint pos;
    customDisplay *valueDisplay;
    customDisplay *patchDisplay;
    customDisplay *patchNumDisplay;
    customLabelDisplay *temp1Display;
    customLabelDisplay *temp2Display;
    customLabelDisplay *temp3Display;
    customLabelDisplay *temp4Display;
    customLabelDisplay *temp5Display;
    customControlListMenu *output;
    customControlListMenu *catagory;
    customButton *autoButton;
    customButton *connectButton;
    customButton *writeButton;
    customPanelButton *midi_Button;
    customPanelButton *system_Button;
    customPanelButton *master_Button;
    customPanelButton *chain_Button;
    customPanelButton *ez_edit_Button;

    customPanelButton *ch_mode_Button;
    customPanelButton *channel_Mix_Button;
    customPanelButton *channel_A_Button;
    customPanelButton *channel_B_Button;
    customPanelButton *preamp1_Button;
    customPanelButton *preamp2_Button;
    customPanelButton *solo1_Button;
    customPanelButton *solo2_Button;
    customPanelButton *distortion_Button;
    customPanelButton *compressor_Button;
    customPanelButton *ns1_Button;
    customPanelButton *ns2_Button;
    customPanelButton *fx1_Button;
    customPanelButton *fx2_Button;
    customPanelButton *fx3_Button;
    customPanelButton *reverb_Button;
    customPanelButton *delay_Button;
    customPanelButton *chorus_Button;
    customPanelButton *sendreturn_Button;
    customPanelButton *eq_Button;
    customPanelButton *pedal_Button;
    customPanelButton *assign1_Button;
    customPanelButton *assign2_Button;
    customPanelButton *assign3_Button;
    customPanelButton *assign4_Button;
    customPanelButton *assign5_Button;
    customPanelButton *assign6_Button;
    customPanelButton *assign7_Button;
    customPanelButton *assign8_Button;
    customButton *temp1_copy_Button;
    customButton *temp1_paste_Button;
    customButton *temp2_copy_Button;
    customButton *temp2_paste_Button;
    customButton *temp3_copy_Button;
    customButton *temp3_paste_Button;
    customButton *temp4_copy_Button;
    customButton *temp4_paste_Button;
    customButton *temp5_copy_Button;
    customButton *temp5_paste_Button;
    customButton *temp6_copy_Button;
    customButton *temp6_paste_Button;

    bool connectButtonActive;
    bool autosyncButtonActive;
    bool patchLoadError;
    QTimer* timer;
    QTimer* autosyncTimer;
    int blinkCount;
    bool currentSyncStatus;
    initPatchListMenu *initPatch;
    QString patchName;
    QString temp1_sysxMsg;
    QString temp2_sysxMsg;
    QString temp3_sysxMsg;
    QString temp4_sysxMsg;
    QString temp5_sysxMsg;
    int set_bank;
    int set_patch;
};

#endif // FLOORBOARDDISPLAY_H
