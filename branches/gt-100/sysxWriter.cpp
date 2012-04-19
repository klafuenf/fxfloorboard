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

#include <QFile>
#include <QDataStream>
#include <QByteArray>
#include <QMessageBox>
#include "sysxWriter.h"
#include "fileDialog.h"
#include "globalVariables.h"

sysxWriter::sysxWriter()
{

};

sysxWriter::~sysxWriter()
{

};

void sysxWriter::setFile(QString fileName)
{
    this->fileName = fileName;
    this->fileSource.address.clear();
    this->fileSource.hex.clear();
};

bool sysxWriter::readFile()
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly))
    {
        QByteArray data = file.readAll();     // read the pre-selected file,
        QByteArray default_data;
        QFile file(":default.syx");           // Read the default GT-100 sysx file .
        if (file.open(QIODevice::ReadOnly))
        {	default_data = file.readAll(); };
        QByteArray default_header = default_data.mid(0, 7);           // copy header from default.syx
        QByteArray file_header = data.mid(0, 7);                      // copy header from read file.syx
        bool isHeader = false;
        if (default_header == file_header) {isHeader = true;};

        if((data.size() == 1682) && isHeader == true){         // if GT-100 system file size is correct- load file.
            SysxIO *sysxIO = SysxIO::Instance();
            QString area = "System";
            sysxIO->setFileSource(area, data);
            //sysxIO->setFileName(this->fileName);
            this->systemSource = sysxIO->getSystemSource();
            return true;
        }
        else if(data.size() == 2152 && isHeader == true){         //2045 if GT-100 patch file size is correct- load file >>>  currently at 1763 bytes standard or 1904 with text.
            SysxIO *sysxIO = SysxIO::Instance();
            QString area = "Structure";
            sysxIO->setFileSource(area, data);
            sysxIO->setFileName(this->fileName);
            this->fileSource = sysxIO->getFileSource();
            return true;
        }
          else
        {
            QMessageBox *msgBox = new QMessageBox();
            msgBox->setWindowTitle(QObject::tr("Patch type Error!"));
            msgBox->setIcon(QMessageBox::Warning);
            msgBox->setTextFormat(Qt::RichText);
            QString msgText;
            msgText.append("<font size='+1'><b>");
            msgText.append(QObject::tr("This is not a ") + deviceType + QObject::tr(" patch!"));
            msgText.append("<b></font><br>");
            if (data.size() == 670){
                msgText.append(QObject::tr("but appears to be a GT-6 patch<br>"));};
            if (data.size() == 650){
                msgText.append(QObject::tr("but appears to be a GT-3 patch<br>"));};

            msgText.append(QObject::tr("Patch data size is ") + (QString::number(data.size(), 10)) + QObject::tr(" bytes, and does not meet GT-100FxFloorBoard requirements."));
            msgBox->setText(msgText);
            msgBox->setStandardButtons(QMessageBox::Ok);
            msgBox->exec();
            return false;
        };
    }
    else
    {
        QMessageBox *msgBox = new QMessageBox();
        msgBox->setWindowTitle(QObject::tr("Patch size Error!"));
        msgBox->setIcon(QMessageBox::Warning);
        msgBox->setTextFormat(Qt::RichText);
        QString msgText = "FILE ERROR";
        msgBox->setText(msgText);
        msgBox->setStandardButtons(QMessageBox::Ok);
        msgBox->exec();
        return false;
    };
};

void sysxWriter::patchIndex(int listIndex)
{
    SysxIO *sysxIO = SysxIO::Instance();
    this->index=sysxIO->patchListValue;
};

void sysxWriter::writeFile(QString fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly))
    {
        SysxIO *sysxIO = SysxIO::Instance();
        this->fileSource = sysxIO->getFileSource();

        QByteArray out;
        unsigned int count=0;
        for (QList< QList<QString> >::iterator dev = fileSource.hex.begin(); dev != fileSource.hex.end(); ++dev)
        {
            QList<QString> data(*dev);
            for (QList<QString>::iterator code = data.begin(); code != data.end(); ++code)
            {
                QString str(*code);
                bool ok;
                unsigned int n = str.toInt(&ok, 16);
                out[count] = (char)n;
                count++;
            };
        };
        file.write(out);
    };

};

void sysxWriter::writeSystemFile(QString fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly))
    {
        SysxIO *sysxIO = SysxIO::Instance();
        this->systemSource = sysxIO->getSystemSource();

        QByteArray out;
        unsigned int count=0;
        for (QList< QList<QString> >::iterator dev = systemSource.hex.begin(); dev != systemSource.hex.end(); ++dev)
        {
            QList<QString> data(*dev);
            for (QList<QString>::iterator code = data.begin(); code != data.end(); ++code)
            {
                QString str(*code);
                bool ok;
                unsigned int n = str.toInt(&ok, 16);
                out[count] = (char)n;
                count++;
            };
        };
        file.write(out);
    };

};

void sysxWriter::writeSMF(QString fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly))
    {
        SysxIO *sysxIO = SysxIO::Instance();
        this->fileSource = sysxIO->getFileSource();

        QByteArray out;
        unsigned int count=0;
        for (QList< QList<QString> >::iterator dev = fileSource.hex.begin(); dev != fileSource.hex.end(); ++dev)
        {
            QList<QString> data(*dev);
            for (QList<QString>::iterator code = data.begin(); code != data.end(); ++code)
            {
                QString str(*code);
                bool ok;
                unsigned int n = str.toInt(&ok, 16);
                out[count] = (char)n;
                count++;
            };
        };

        QByteArray temp;                        // TRANSLATION of GT-100 PATCHES, data read from syx patch **************
        QByteArray Qhex;                        // and replace syx headers with mid data and new addresses**************
        QFile hexfile(":HexLookupTable.hex");   // use a QByteArray of hex numbers from a lookup table.
        if (hexfile.open(QIODevice::ReadOnly))
        {	Qhex = hexfile.readAll(); };

        temp = Qhex.mid((288), 30);
        out.remove(1763, 282);       //remove user text from end
        out.prepend(temp);          // insert midi timing header
        out.remove(30, 11);         // remove address "00 00" header
        temp = Qhex.mid((320), 13);
        out.insert(30, temp);       // insert new address "00 00" header
        out.remove(171, 13);        // remove address "01 00" header
        temp = Qhex.mid((336), 16);
        out.insert(285, temp);      // insert new address "01 72" header
        out.remove(315, 13);        // remove address "02 00" header
        out.remove(443, 13);        // remove address "03 00" header
        temp = Qhex.mid((352), 16);
        out.insert(543, temp);      // insert new address "03 64" header
        out.remove(587, 13);        // remove address "04 00" header
        out.remove(715, 13);        // remove address "05 00" header
        temp = Qhex.mid((368), 16);
        out.insert(801, temp);      // insert new address "05 56" header
        out.remove(817, 13);        // remove address "06 00" header
        out.remove(945, 13);        // remove address "07 00" header
        temp = Qhex.mid((438), 42);  // copy 42 x extra "00"
        out.insert(817, temp);      // insert 42 x extra "00"
        temp = Qhex.mid((384), 16);
        out.insert(1059, temp);      // insert new address "07 48" header
        out.remove(1131, 13);        // remove address "08 00" header
        out.remove(1259, 13);        // remove address "09 00" header
        temp = Qhex.mid((400), 16);
        out.insert(1317, temp);      // insert new address "09 3A" header
        out.remove(1375, 13);        // remove address "0A 00" header
        out.remove(1503, 13);        // remove address "0B 00" header
        out.remove(1631, 13);        // remove address "0C 00" header
        temp = Qhex.mid((438), 28);  // copy 28 x extra "00"
        out.insert(1375, temp);      // insert 28 x extra "00"
        temp = Qhex.mid((416), 16);
        out.insert(1575, temp);      // insert new address "0B 2C" header
        out.remove(1803, 2);        // remove file footer
        temp = Qhex.mid((438), 29);  // copy 29 x extra "00"
        out.insert(1803, temp);      // insert 28 x extra "00"
        temp = Qhex.mid((432), 3);
        out.insert(1832, temp);      // insert new file footer (part of)
        out.remove(0, 29);           // remove header again for checksum calcs
        out.remove(1835, 70);

        this->fileSource.address.clear();
        this->fileSource.hex.clear();

        QList<QString> sysxBuffer;
        int dataSize = 0; int offset = 0;
        for(int i=0;i<out.size();i++)
        {
            unsigned char byte = (char)out[i];
            unsigned int n = (int)byte;
            QString hex = QString::number(n, 16).toUpper();
            if (hex.length() < 2) hex.prepend("0");
            sysxBuffer.append(hex);

            unsigned char nextbyte = (char)out[i+1];
            unsigned int nextn = (int)nextbyte;
            QString nexthex = QString::number(nextn, 16).toUpper();
            if (nexthex.length() < 2) nexthex.prepend("0");
            if(offset >= checksumOffset+3 && nexthex != "F7")   // smf offset is 8 bytes + previous byte
            {
                dataSize += n;
            };
            if(nexthex == "F7")
            {
                QString checksum;
                bool ok;
                int dataSize = 0;
                for(int i=checksumOffset+3;i<sysxBuffer.size()-1;++i)
                { dataSize += sysxBuffer.at(i).toInt(&ok, 16); };
                QString base = "80";
                int sum = dataSize % base.toInt(&ok, 16);
                if(sum!=0) sum = base.toInt(&ok, 16) - sum;
                checksum = QString::number(sum, 16).toUpper();
                if(checksum.length()<2) checksum.prepend("0");
                sysxBuffer.replace(sysxBuffer.size() - 1, checksum);

            };
            offset++;

            if(hex == "F7")
            {
                this->fileSource.address.append( sysxBuffer.at(sysxAddressOffset + 5) + sysxBuffer.at(sysxAddressOffset + 6) );
                this->fileSource.hex.append(sysxBuffer);
                sysxBuffer.clear();
                dataSize = 0;
                offset = 0;
            };
        };


        out.clear();
        count=0;
        for (QList< QList<QString> >::iterator dev = fileSource.hex.begin(); dev != fileSource.hex.end(); ++dev)
        {
            QList<QString> data(*dev);
            for (QList<QString>::iterator code = data.begin(); code != data.end(); ++code)
            {
                QString str(*code);
                bool ok;
                unsigned int n = str.toInt(&ok, 16);
                out[count] = (char)n;
                count++;
            };
        };
        temp = Qhex.mid((288), 29);           // place smf header after checksum is added
        out.prepend(temp);
        temp = Qhex.mid((435), 4);             // place smf footer after "F7" EOF
        out.append(temp);
        file.write(out);
    };
};

void sysxWriter::writeGXG(QString fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly))
    {
        SysxIO *sysxIO = SysxIO::Instance();
        this->fileSource = sysxIO->getFileSource();

        QByteArray out;
        unsigned int count=0;
        for (QList< QList<QString> >::iterator dev = fileSource.hex.begin(); dev != fileSource.hex.end(); ++dev)
        {
            QList<QString> data(*dev);
            for (QList<QString>::iterator code = data.begin(); code != data.end(); ++code)
            {
                QString str(*code);
                bool ok;
                unsigned int n = str.toInt(&ok, 16);
                out[count] = (char)n;
                count++;
            };
        };
        QByteArray GXG_default;
        QByteArray temp;
        int a = 172;
        QFile GXGfile(":default.gxg");           // Read the default GT-100 GXG file .
        if (GXGfile.open(QIODevice::ReadOnly))
        { GXG_default = GXGfile.readAll(); };
        temp = out.mid(11, 128);
        GXG_default.replace(a, 128, temp);         //address "00"
        temp = out.mid(152, 128);
        GXG_default.replace(a+128, 128, temp);     //address "01"
        temp = out.mid(293, 128);
        GXG_default.replace(a+256, 128, temp);     //address "02"
        temp = out.mid(434, 128);
        GXG_default.replace(a+384, 128, temp);     //address "03"
        temp = out.mid(575, 128);
        GXG_default.replace(a+512, 128, temp);     //address "04"
        temp = out.mid(716, 86);
        GXG_default.replace(a+640, 86, temp);      //address "05"
        temp = out.mid(815, 128);
        GXG_default.replace(a+768, 128, temp);     //address "06"
        temp = out.mid(956, 128);
        GXG_default.replace(a+896, 128, temp);     //address "07"
        temp = out.mid(1097, 128);
        GXG_default.replace(a+1024, 128, temp);    //address "08"
        temp = out.mid(1238, 100);
        GXG_default.replace(a+1152, 100, temp);    //address "09"
        temp = out.mid(1351, 128);
        GXG_default.replace(a+1280, 128, temp);    //address "0A"
        temp = out.mid(1492, 128);
        GXG_default.replace(a+1408, 128, temp);    //address "0B"
        temp = out.mid(1633, 128);
        GXG_default.replace(a+1536, 128, temp);    //address "0C"
        // copy user text, first two sections only, section terminated by "00"
        QByteArray marker = GXG_default.mid(32, 1);     //copy "00" for position marker.
        //int z = a+1701;
        //int y = GXG_default.indexOf( marker, (a+1701));

        temp = out.mid(1774, 128 );   // copy first text section from patch
        //GXG_default.replace(a+1701, (y-z), temp);       // paste text 1
        GXG_default.replace(a+1701, 128, temp);       // paste text 1

        //int x = GXG_default.indexOf( marker, (y+1));
        //int w = GXG_default.indexOf( marker, (x+1));

        temp = out.mid(1915, 32 );     // copy second text section from patch
        //GXG_default.replace(x+1, (w-x), temp);          // paste text 2
        GXG_default.replace(a+1830, 32, temp);          // paste text 2

        file.write(GXG_default);
    };
};

SysxData sysxWriter::getFileSource()
{
    return fileSource;
};

SysxData sysxWriter::getSystemSource()
{
    return systemSource;
};

QString sysxWriter::getFileName()
{
    return fileName;
};

