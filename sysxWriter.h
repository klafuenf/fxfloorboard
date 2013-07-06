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

#ifndef SYSXWRITER_H
#define SYSXWRITER_H

#include <QString>
#include <QList>
#include "SysxIO.h"	

class sysxWriter
{

public:
    sysxWriter();
    ~sysxWriter();
    void setFile(QString fileName);
    bool readFile();
    SysxData getFileSource();
    SysxData getSystemSource();
    void writeFile(QString fileName);
    void writeSystemFile(QString fileName);
    void writeSMF(QString fileName);
    void writeGCL(QString fileName);
    QString getFileName();
    QList<QString> patchList;
    int index;

public slots:
    void patchIndex(int listIndex);

private:
    QString fileName;
    SysxData fileSource;
    SysxData systemSource;
    QByteArray data;
    void convertFromGT10();
    void convertFromGT10B();
    void convertFromGT8();
    void translate10to100();
    void translate10Bto100();
    void convertFromGT6B();
    QString headerType;
    int ArrayToInt(QByteArray Array);
    QByteArray IntToArray(int value);
};

#endif // SYSXWRITER_H
