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
#include "MidiTable.h"

sysxWriter::sysxWriter()
{

}

sysxWriter::~sysxWriter()
{

}

void sysxWriter::setFile(QString fileName)
{
    this->fileName = fileName;
    this->fileSource.address.clear();
    this->fileSource.hex.clear();
}

bool sysxWriter::readFile()
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly))
    {
        data = file.readAll();     // read the pre-selected file,
        QByteArray GT10_default;
        QByteArray GCL_default;
        QByteArray SMF_default;

        QFile file(":default.syx");           // Read the default GT-100 sysx file .
        if (file.open(QIODevice::ReadOnly))
        {GT10_default = file.readAll(); };

        QFile GCLfile(":default.gcl");           // Read the default GT-10 GCL file .
        if (GCLfile.open(QIODevice::ReadOnly))
        {GCL_default = GCLfile.readAll(); };

        QFile smffile(":default.mid");           // Read the HexLookupTable for the SMF header file .
        if (smffile.open(QIODevice::ReadOnly))
        {SMF_default = smffile.readAll(); };

        QByteArray SYX_header = GT10_default.mid(0, 7);             // copy header from default.syx
        QByteArray other_SYX_header = GT10_default.mid(0, 3);
        QByteArray GCL_header = GCL_default.mid(3, 20);            // copy header from default.gcl
        QByteArray SMF_header = SMF_default.mid(0, 18);            // copy header from default.mid
        QByteArray SYX_file = data.mid(0, 7);                      // copy *.syx identifiable info from loaded patch
        QByteArray other_SYX_file = data.mid(0, 3);
        QByteArray GCL_file = data.mid(3, 20);
        QByteArray SMF_file = data.mid(0, 18);

        headerType = "false";
        if (SYX_file == SYX_header) {headerType = "GT100_SYX";}
        else if (GCL_file == GCL_header && data.mid(2, 1) == "G"){headerType = "GT10_GXG"; }
        else if (GCL_file == GCL_header){headerType = "GT100_GCL"; }
        else if (SMF_file == SMF_header) {headerType = "GT100_SMF"; }
        else if (other_SYX_file == other_SYX_header) {headerType = "other_SYX"; };


        /***** TEST IF SYSTEM FILE *****************************************/
        if(data.size() == 1682 && headerType == "GT100_SYX"){    // if GT-100 system file size is correct- load file.
            SysxIO *sysxIO = SysxIO::Instance();
            QString area = "System";
            sysxIO->setFileSource(area, data);
            this->systemSource = sysxIO->getSystemSource();
            return true;
        }
        /***** TEST IF GT-100 SYX PATCH FILE *****************************************/
        else if(data.size() == 2152 && headerType == "GT100_SYX"){  //if GT-100 patch file size is correct- load file >>>  currently at 1763 bytes standard or 1904 with text.
            SysxIO *sysxIO = SysxIO::Instance();
            QString area = "Structure";
            sysxIO->setFileSource(area, data);
            sysxIO->setFileName(this->fileName);
            this->fileSource = sysxIO->getFileSource();
            return true;
        }
        /***** TEST IF GT-100 SMF PATCH FILE *****************************************/
        else if (headerType == "GT100_SMF")
        {                                        // file contains a .mid type SMF patch file header from Boss Librarian
            QByteArray GT100_default;
            QFile file(":default.syx");              // Read the default GT-100 sysx file so we don't start empty handed.
            if (file.open(QIODevice::ReadOnly))
            {	GT100_default = file.readAll(); };
            QByteArray temp;                         // TRANSLATION of GT-100 SMF PATCHES, data read from smf patch **************

            if ( data.at(37) != GT100_default.at(5) ){    // check if a valid GT-100 file
               /* QMessageBox *msgBox = new QMessageBox();
                msgBox->setWindowTitle(QObject::tr("SMF file import"));
                msgBox->setIcon(QMessageBox::Warning);
                msgBox->setTextFormat(Qt::RichText);
                QString msgText;
                msgText.append("<font size='+1'><b>");
                msgText.append(QObject::tr("This is not a GT-100 patch!"));
                msgText.append("<b></font><br>");
                msgText.append(QObject::tr("this file is a GT-10B Bass version<br>"));
                msgText.append(QObject::tr("*Loading this file may have unpredictable results*."));
                msgBox->setText(msgText);
                msgBox->setStandardButtons(QMessageBox::Ok);
                msgBox->exec();*/
                headerType = "GT10_SMF";
                convertFromGT10();
                return true;
            };

            index = 1;
            int patchCount = (data.size()-32)/2322;
            if (patchCount>1)
            {
                QString msgText;
                QString patchText;
                QString patchNumber;
                unsigned char r;
                this->patchList.clear();
                this->patchList.append(QObject::tr("Select Patch"));
                unsigned int a = 43; // locate patch text start position from the start of the file
                for (int h=0;h<patchCount;h++)
                {
                    for (int b=0;b<16;b++)
                    {
                        r = (char)data[a+b];
                        patchText.append(r);
                    };
                    patchNumber = QString::number(h+1, 10).toUpper();
                    msgText.append(patchNumber + " : ");
                    msgText.append(patchText + "   ");
                    this->patchList.append(msgText);
                    patchText.clear();
                    msgText.clear();
                    a=a+2322;                      // offset is set in front of marker
                };

                QString type = "smf";
                fileDialog *dialog = new fileDialog(fileName, patchList, data, GT10_default, type);
                dialog->exec();
                patchIndex(this->index);
            };

            int a=0;
            if (patchCount>1)
            {
                int q=index-1;      // find start of required patch
                a = q*2322;
            };
            temp = data.mid(a+43, 128);            // copy SMF 128 bytes#
            GT100_default.replace(11, 128, temp);             // replace gt100 address "00"#
            temp = data.mid(a+171, 114);           // copy SMF part1#
            temp.append(data.mid(a+301,14));       // copy SMF part2#
            GT100_default.replace(152, 128, temp);            // replace gt100 address "01"#
            temp = data.mid(a+315, 128);           // copy SMF part1#
            GT100_default.replace(293, 128, temp);            // replace gt100 address "02"#
            temp = data.mid(a+443, 100);           // copy SMF part1#
            temp.append(data.mid(a+559,28));       // copy SMF part2#
            GT100_default.replace(434, 128, temp);            // replace gt100 address "03"#
            temp = data.mid(a+587, 128);           // copy SMF part1#
            GT100_default.replace(575, 128, temp);            // replace gt100 address "04"#
            temp = data.mid(a+715, 86);            // copy SMF part1#
            temp.append(data.mid(a+817,42));      // copy SMF part2#
            GT100_default.replace(716, 128, temp);             // replace gt100 address "05"#
            temp = data.mid(a+859, 128);           // copy SMF part1#
            GT100_default.replace(857,128, temp);             // replace gt100 address "06"#
            temp = data.mid(a+987, 72);            // copy SMF part1#
            temp.append(data.mid(a+1075,56));      // copy SMF part2#
            GT100_default.replace(998, 128, temp);            // replace gt100 address "07"#
            temp = data.mid(a+1131, 128);          // copy SMF part1#
            GT100_default.replace(1139,128, temp);            // replace gt100 address "08"#
            temp = data.mid(a+1259, 58);           // copy SMF part1#
            temp.append(data.mid(a+1333,70));      // copy SMF part2#
            GT100_default.replace(1280, 128, temp);           // replace gt100 address "09"#
            temp = data.mid(a+1403, 128);          // copy SMF part1#
            GT100_default.replace(1421,128, temp);            // replace gt100 address "0A"#
            temp = data.mid(a+1531, 44);           // copy SMF part1#
            temp.append(data.mid(a+1591,84));      // copy SMF part2#
            GT100_default.replace(1562, 128, temp);           // replace gt100 address "0B"#
            temp = data.mid(a+1675, 128);          // copy SMF part1#
            GT100_default.replace(1703,128, temp);            // replace gt100 address "0C"#
            temp = data.mid(a+1803, 30);           // copy SMF part1#
            temp.append(data.mid(a+1849,98));      // copy SMF part2#
            GT100_default.replace(1844, 128, temp);           // replace gt100 address "0D"#
            temp = data.mid(a+1947, 128);           // copy SMF part1#
            GT100_default.replace(1985, 128, temp);           // replace gt100 address "0E"#
            temp = data.mid(a+2075, 16);           // copy SMF part1#
            temp.append(data.mid(a+2107,8));      // copy SMF part2
            GT100_default.replace(2126, 24, temp);           // replace gt100 address "0F"
            if (index>0)
            {
                SysxIO *sysxIO = SysxIO::Instance();
                QString area = "Structure";
                sysxIO->setFileSource(area, GT100_default);
                sysxIO->setFileName(this->fileName);
                this->fileSource = sysxIO->getFileSource();
                return true;
            } else {return false; }
        }
        /***** TEST IF GT-100 GCL PATCH FILE *****************************************/
        else if (headerType == "GT100_GCL")
        {
            index=1;
            unsigned char msb = (char)data[34];     // find patch count msb bit in GCL file at byte 34
            unsigned char lsb = (char)data[35];     // find patch count lsb bit in GCL file at byte 35
            bool ok;
            int patchCount;
            patchCount = (256*QString::number(msb, 16).toUpper().toInt(&ok, 16)) + (QString::number(lsb, 16).toUpper().toInt(&ok, 16));
            QByteArray marker;
            if (patchCount>1)
            {
                QString msgText;
                marker = data.mid(170, 2);      //copy marker key to find "0882" which marks the start of each patch block
                QString patchText;
                QString patchNumber;
                this->patchList.clear();
                this->patchList.append(QObject::tr("Select Patch"));
                unsigned int a = data.indexOf(marker, 0); // locate patch start position from the start of the file
                a=a+2;                             // offset is set in front of marker
                for (int h=0;h<patchCount;h++)
                {
                    for (int b=0;b<16;b++)
                    {
                        unsigned char r = (char)data[a+b];
                        patchText.append(r);
                    };
                    patchNumber = QString::number(h+1, 10).toUpper();
                    msgText.append(patchNumber + " : ");
                    msgText.append(patchText + "   ");
                    this->patchList.append(msgText);
                    patchText.clear();
                    msgText.clear();
                    a = data.indexOf(marker, a); // locate patch start position from the start of the file
                    a=a+2;                      // offset is set in front of marker
                };

                QString type = "gcl";
                fileDialog *dialog = new fileDialog(fileName, patchList, data, GT10_default, type);
                dialog->exec();
                patchIndex(this->index);
            };

            marker = data.mid(170, 2);                 //copy marker key to find "0882" which marks the start of each patch block
            unsigned int a = data.indexOf(marker, 0);  // locate patch start position from the start of the file
            a=a+2;                                     // offset is set in front of marker
            if (patchCount>1)
            {
                int q=index-1;
                for (int h=0;h<q;h++)
                {
                    a = data.indexOf(marker, a);          // locate patch start position from the start of the file
                    a=a+2;
                };                                     // offset is set in front of marker
            };
            QByteArray temp;
            temp = data.mid(a, 128);
            GT10_default.replace(11, 128, temp);       //address "00" +
            temp = data.mid(a+128, 128);
            GT10_default.replace(152, 128, temp);      //address "01" +
            temp = data.mid(a+256, 128);
            GT10_default.replace(293, 128, temp);      //address "02" +
            temp = data.mid(a+384, 128);
            GT10_default.replace(434, 128, temp);      //address "03" +
            temp = data.mid(a+512, 128);
            GT10_default.replace(575, 128, temp);      //address "04" +
            temp = data.mid(a+640, 128);
            GT10_default.replace(716, 128, temp);       //address "05" +
            temp = data.mid(a+768, 128);
            GT10_default.replace(857, 128, temp);      //address "06" +
            temp = data.mid(a+896, 128);
            GT10_default.replace(998, 128, temp);      //address "07" +
            temp = data.mid(a+1024, 128);
            GT10_default.replace(1139, 128, temp);     //address "08" +
            temp = data.mid(a+1152, 128);
            GT10_default.replace(1280, 128, temp);     //address "09" +
            temp = data.mid(a+1280, 128);
            GT10_default.replace(1421, 128, temp);     //address "0A" +
            temp = data.mid(a+1408, 128);
            GT10_default.replace(1562, 128, temp);     //address "0B" +
            temp = data.mid(a+1536, 128);
            GT10_default.replace(1703, 128, temp);     //address "0C" +
            temp = data.mid(a+1664, 128);
            GT10_default.replace(1844, 128, temp);     //address "0D" +
            temp = data.mid(a+1792, 128);
            GT10_default.replace(1985, 128, temp);     //address "0E" +
            temp = data.mid(a+1920, 24);
            GT10_default.replace(2126, 24, temp);     //address "0F" +
            /*
            // copy user text, first two sections only, sections seperated/terminated by "00"
            temp = data.mid(32, 1);                    //copy "00"
            int z = a+2178;                            //start position of first text dialog.
            int y = data.indexOf( temp, (a+2178));     //end position of first text dialog.
            int x = data.indexOf( temp, (a+2178)) + 1; //start position of second text dialog.
            int w = data.indexOf( temp, (x+1));        //end position of second text dialog.
            temp = data.mid(z, (y-z) );                //copy first text dialog.
            marker = data.mid(31, 1);                  //copy "20"
            if ((y-z)>2 )
            {
                for (int u = (128-(y-z));u>0; u--)
                { temp.append(marker); };
                if (temp.size()>128) {temp=temp.mid(0, 128); };
                GT10_default.replace(1774, 128, temp);   // paste text 1
            };
            temp = data.mid(x, (w-x) );
            if ((w-x)>2 )
            {
                for (int u = (32-(w-x));u>0; u--)
                { temp.append(marker); };
                if (temp.size()>32) {temp=temp.mid(0, 32); };
                GT10_default.replace(1915, 32, temp);    // paste text 2
            };*/

            if (index>0)
            {
                SysxIO *sysxIO = SysxIO::Instance();
                QString area = "Structure";
                sysxIO->setFileSource(area, GT10_default);
                sysxIO->setFileName(this->fileName);
                this->fileSource = sysxIO->getFileSource();
                return true;
            }
        }
        else if (headerType == "GT10_GXG"){
            convertFromGT10();
            return true;
        }
        else if(headerType == "other_SYX")
        {
          other_SYX_file = data.mid(0, 11);
          QString header;
          for(int x=0; x<10; ++x)
          {
              char r = other_SYX_file.at(x+1);
              QString val = QString::number(r, 16).toUpper();
              if(val.size()<2){val.prepend("0"); };
              header.append(val);
          };
          bool ok;
          int address = header.mid(12, 2).toInt(&ok, 16);
          bool isPatch = false;
          if(address > 9)isPatch = true;
          if(isPatch && header.contains("00002F") )
          { headerType = "GT10_SYX";
             convertFromGT10();
             return true; };
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
            if (data.size() == 1010){
                msgText.append(QObject::tr("but appears to be a GT-8 patch<br>"));};
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
}

void sysxWriter::patchIndex(int listIndex)
{
    SysxIO *sysxIO = SysxIO::Instance();
    this->index=sysxIO->patchListValue;
}

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

}

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

}

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
}

void sysxWriter::writeGCL(QString fileName)
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
        QByteArray GCL_default;
        QByteArray temp;
        int a = 172;
        QFile GCLfile(":default.gcl");           // Read the default GT-100 GCL file .
        if (GCLfile.open(QIODevice::ReadOnly))
        { GCL_default = GCLfile.readAll(); };
        temp = out.mid(11, 128);
        GCL_default.replace(a, 128, temp);         //address "00"
        temp = out.mid(152, 128);
        GCL_default.replace(a+128, 128, temp);     //address "01"
        temp = out.mid(293, 128);
        GCL_default.replace(a+256, 128, temp);     //address "02"
        temp = out.mid(434, 128);
        GCL_default.replace(a+384, 128, temp);     //address "03"
        temp = out.mid(575, 128);
        GCL_default.replace(a+512, 128, temp);     //address "04"
        temp = out.mid(716, 86);
        GCL_default.replace(a+640, 86, temp);      //address "05"
        temp = out.mid(815, 128);
        GCL_default.replace(a+768, 128, temp);     //address "06"
        temp = out.mid(956, 128);
        GCL_default.replace(a+896, 128, temp);     //address "07"
        temp = out.mid(1097, 128);
        GCL_default.replace(a+1024, 128, temp);    //address "08"
        temp = out.mid(1238, 100);
        GCL_default.replace(a+1152, 100, temp);    //address "09"
        temp = out.mid(1351, 128);
        GCL_default.replace(a+1280, 128, temp);    //address "0A"
        temp = out.mid(1492, 128);
        GCL_default.replace(a+1408, 128, temp);    //address "0B"
        temp = out.mid(1633, 128);
        GCL_default.replace(a+1536, 128, temp);    //address "0C"
        // copy user text, first two sections only, section terminated by "00"
        QByteArray marker = GCL_default.mid(32, 1);     //copy "00" for position marker.
        //int z = a+1701;
        //int y = GCL_default.indexOf( marker, (a+1701));

        temp = out.mid(1774, 128 );   // copy first text section from patch
        //GCL_default.replace(a+1701, (y-z), temp);       // paste text 1
        GCL_default.replace(a+1701, 128, temp);       // paste text 1

        //int x = GCL_default.indexOf( marker, (y+1));
        //int w = GCL_default.indexOf( marker, (x+1));

        temp = out.mid(1915, 32 );     // copy second text section from patch
        //GCL_default.replace(x+1, (w-x), temp);          // paste text 2
        GCL_default.replace(a+1830, 32, temp);          // paste text 2

        file.write(GCL_default);
    };
}

SysxData sysxWriter::getFileSource()
{
    return fileSource;
}

SysxData sysxWriter::getSystemSource()
{
    return systemSource;
}

QString sysxWriter::getFileName()
{
    return fileName;
}

void sysxWriter::convertFromGT10()
{
    QByteArray GT10_default;
    QFile file(":gt10_default.syx");           // Read the default GT-10 sysx file .
    if (file.open(QIODevice::ReadOnly))
    {	GT10_default = file.readAll(); };

    if(/*data.size() == 1862 && */headerType == "GT10_SYX"){         // if GT-10 patch file size is an old format <<<<<<<<<<<<<<<<<.

        QByteArray temp;
        data.remove(1618, 50);
        temp = data.mid(1605, 13);
        data.remove(1605, 13);
        data.insert(1620, temp);
        data.remove(1761, 49);

        QByteArray standard_data = data;
        QFile file(":default.syx");   // Read the default GT-10 sysx file so we don't start empty handed.
        if (file.open(QIODevice::ReadOnly))
        {	data = file.readAll(); };

        temp = data.mid(1763, 282);           // copy patch description from default.syx
        standard_data.append(temp);
        data = standard_data;

        translate10to100();
    }
    else if (headerType == "GT10_SMF")                      // SMF ******************************************************************
    {                                        // file contains a .mid type SMF patch file header from Boss Librarian
        QByteArray GT10_default;
        QFile file(":gt10_default.syx");              // Read the default GT-10 sysx file so we don't start empty handed.
        if (file.open(QIODevice::ReadOnly))
        {	GT10_default = file.readAll(); };
        QByteArray temp;                         // TRANSLATION of GT-10 SMF PATCHES, data read from smf patch **************

       /* if ( data.at(37) != GT10_default.at(5) ){    // check if a valid GT-10 file
            QMessageBox *msgBox = new QMessageBox();
            msgBox->setWindowTitle(QObject::tr("SMF file import"));
            msgBox->setIcon(QMessageBox::Warning);
            msgBox->setTextFormat(Qt::RichText);
            QString msgText;
            msgText.append("<font size='+1'><b>");
            msgText.append(QObject::tr("This is not a GT-10 patch!"));
            msgText.append("<b></font><br>");
            msgText.append(QObject::tr("this file is a GT-10 Bass version<br>"));
            msgText.append(QObject::tr("*Loading this file may have unpredictable results*."));
            msgBox->setText(msgText);
            msgBox->setStandardButtons(QMessageBox::Ok);
            msgBox->exec();
        };*/

        index = 1;
        int patchCount = (data.size()-32)/1806;
        if (patchCount>1)
        {
            QString msgText;
            QString patchText;
            QString patchNumber;
            unsigned char r;
            this->patchList.clear();
            this->patchList.append(QObject::tr("Select Patch"));
            unsigned int a = 43; // locate patch text start position from the start of the file
            for (int h=0;h<patchCount;h++)
            {
                for (int b=0;b<16;b++)
                {
                    r = (char)data[a+b];
                    patchText.append(r);
                };
                patchNumber = QString::number(h+1, 10).toUpper();
                msgText.append(patchNumber + " : ");
                msgText.append(patchText + "   ");
                this->patchList.append(msgText);
                patchText.clear();
                msgText.clear();
                a=a+1806;                      // offset is set in front of marker
            };

            QString type = "smf";
            fileDialog *dialog = new fileDialog(fileName, patchList, data, GT10_default, type);
            dialog->exec();
            patchIndex(this->index);
        };

        int a=0;
        if (patchCount>1)
        {
            int q=index-1;      // find start of required patch
            a = q*1806;
        };
        //temp = data.mid(a+43, 128);            // copy SMF 128 bytes
        GT10_default.replace(11, 16, data.mid(a+43, 16));             // replace gt10 address "00"
        temp = data.mid(a+171, 114);           // copy SMF part1
        temp.append(data.mid(a+301,14));       // copy SMF part2
        GT10_default.replace(152, 128, temp);            // replace gt10 address "01"
        temp = data.mid(a+315, 128);           // copy SMF part1
        GT10_default.replace(293, 128, temp);            // replace gt10 address "02"
        temp = data.mid(a+443, 100);           // copy SMF part1
        temp.append(data.mid(a+559,28));       // copy SMF part2
        GT10_default.replace(434, 128, temp);            // replace gt10 address "03"
        temp = data.mid(a+587, 128);           // copy SMF part1
        GT10_default.replace(575, 128, temp);            // replace gt10 address "04"
        temp = data.mid(a+715, 86);            // copy SMF part1
        GT10_default.replace(716, 86, temp);             // replace gt10 address "05"
        temp = data.mid(a+859, 128);           // copy SMF part1
        GT10_default.replace(815,128, temp);             // replace gt10 address "06"
        temp = data.mid(a+987, 72);            // copy SMF part1
        temp.append(data.mid(a+1075,56));      // copy SMF part2
        GT10_default.replace(956, 128, temp);            // replace gt10 address "07"
        temp = data.mid(a+1131, 128);          // copy SMF part1
        GT10_default.replace(1097,128, temp);            // replace gt10 address "08"
        temp = data.mid(a+1259, 58);           // copy SMF part1
        temp.append(data.mid(a+1333,42));      // copy SMF part2
        GT10_default.replace(1238, 100, temp);           // replace gt10 address "09"
        temp = data.mid(a+1403, 128);          // copy SMF part1
        GT10_default.replace(1351,128, temp);            // replace gt10 address "0A"
        temp = data.mid(a+1531, 44);           // copy SMF part1
        temp.append(data.mid(a+1591,84));      // copy SMF part2
        GT10_default.replace(1492, 128, temp);           // replace gt10 address "0B"
        temp = data.mid(a+1675, 128);          // copy SMF part1
        GT10_default.replace(1633,128, temp);            // replace gt10 address "0C"
        if (index>0)
        {
            data = GT10_default;
            translate10to100();
        }
    }
    else if (headerType == "GT10_GXG")      // if the read file is a Boss Librarian type. ***************************************
    {
        index=1;
        unsigned char msb = (char)data[34];     // find patch count msb bit in GXG file at byte 34
        unsigned char lsb = (char)data[35];     // find patch count lsb bit in GXG file at byte 35
        bool ok;
        int patchCount;
        patchCount = (256*QString::number(msb, 16).toUpper().toInt(&ok, 16)) + (QString::number(lsb, 16).toUpper().toInt(&ok, 16));
        QByteArray marker;
        if (patchCount>1)
        {
            QString msgText;
            marker = data.mid(170, 2);      //copy marker key to find "06A5" which marks the start of each patch block
            QString patchText;
            QString patchNumber;
            this->patchList.clear();
            this->patchList.append(QObject::tr("Select Patch"));
            unsigned int a = data.indexOf(marker, 0); // locate patch start position from the start of the file
            a=a+2;                             // offset is set in front of marker
            for (int h=0;h<patchCount;h++)
            {
                for (int b=0;b<16;b++)
                {
                    unsigned char r = (char)data[a+b];
                    patchText.append(r);
                };
                patchNumber = QString::number(h+1, 10).toUpper();
                msgText.append(patchNumber + " : ");
                msgText.append(patchText + "   ");
                this->patchList.append(msgText);
                patchText.clear();
                msgText.clear();
                a = data.indexOf(marker, a); // locate patch start position from the start of the file
                a=a+2;                      // offset is set in front of marker
            };

            QString type = "gxg";
            fileDialog *dialog = new fileDialog(fileName, patchList, data, GT10_default, type);
            dialog->exec();
            patchIndex(this->index);
        };

        marker = data.mid(170, 2);                 //copy marker key to find "06A5" which marks the start of each patch block
        unsigned int a = data.indexOf(marker, 0);  // locate patch start position from the start of the file
        a=a+2;                                     // offset is set in front of marker
        if (patchCount>1)
        {
            int q=index-1;
            for (int h=0;h<q;h++)
            {
                a = data.indexOf(marker, a);          // locate patch start position from the start of the file
                a=a+2;
            };                                     // offset is set in front of marker
        };
        QByteArray temp;
        temp = data.mid(a, 128);
        GT10_default.replace(11, 128, temp);       //address "00" +
        temp = data.mid(a+128, 128);
        GT10_default.replace(152, 128, temp);      //address "01" +
        temp = data.mid(a+256, 128);
        GT10_default.replace(293, 128, temp);      //address "02" +
        temp = data.mid(a+384, 128);
        GT10_default.replace(434, 128, temp);      //address "03" +
        temp = data.mid(a+512, 128);
        GT10_default.replace(575, 128, temp);      //address "04" +
        temp = data.mid(a+640, 86);
        GT10_default.replace(716, 86, temp);       //address "05" +
        temp = data.mid(a+768, 128);
        GT10_default.replace(815, 128, temp);      //address "06" +
        temp = data.mid(a+896, 128);
        GT10_default.replace(956, 128, temp);      //address "07" +
        temp = data.mid(a+1024, 128);
        GT10_default.replace(1097, 128, temp);     //address "08" +
        temp = data.mid(a+1152, 100);
        GT10_default.replace(1238, 100, temp);     //address "09" +
        temp = data.mid(a+1280, 128);
        GT10_default.replace(1351, 128, temp);     //address "0A" +
        temp = data.mid(a+1408, 128);
        GT10_default.replace(1492, 128, temp);     //address "0B" +
        temp = data.mid(a+1536, 128);
        GT10_default.replace(1633, 128, temp);     //address "0C" +
        data = GT10_default;
/*
        // copy user text, first two sections only, sections seperated/terminated by "00"
        temp = data.mid(32, 1);                    //copy "00"
        int z = a+1701;                            //start position of first text dialog.
        int y = data.indexOf( temp, (a+1701));     //end position of first text dialog.
        int x = data.indexOf( temp, (a+1701)) + 1; //start position of second text dialog.
        int w = data.indexOf( temp, (x+1));        //end position of second text dialog.
        temp = data.mid(z, (y-z) );                //copy first text dialog.
        marker = data.mid(31, 1);                  //copy "20"
        if ((y-z)>2 )
        {
            for (int u = (128-(y-z));u>0; u--)
            { temp.append(marker); };
            if (temp.size()>128) {temp=temp.mid(0, 128); };
            GT10_default.replace(1774, 128, temp);   // paste text 1
        };
        temp = data.mid(x, (w-x) );
        if ((w-x)>2 )
        {
            for (int u = (32-(w-x));u>0; u--)
            { temp.append(marker); };
            if (temp.size()>32) {temp=temp.mid(0, 32); };
            GT10_default.replace(1915, 32, temp);    // paste text 2
        };
*/
        if (index>0)
        {
           translate10to100();
        };
    }
}

void sysxWriter::convertFromGT8()
{
    if (data.size() == 1010){      // if the file size = gt-8 patch

        QByteArray gt8_data = data;
        QFile file(":gt10_default.syx");   // Read the default GT-10 sysx file so we don't start empty handed.
        if (file.open(QIODevice::ReadOnly))
        {	data = file.readAll(); };
        char r;
        QByteArray temp;                         // TRANSLATION of GT-8 PATCHES, data read from gt8 patch **************
        QByteArray Qhex;                            // and used to replace gt10 patch data*********************************
        QFile hexfile(":HexLookupTable.hex");   // use a QByteArray of hex numbers from a lookup table.
        if (hexfile.open(QIODevice::ReadOnly))
        {	Qhex = hexfile.readAll(); };
        temp = gt8_data.mid(692, 16);           // copy gt8 name
        data.replace(11, 16, temp);              // replace gt10 name
        temp = gt8_data.mid(154, 1);             // copy gt8 compressor part1
        temp.append(gt8_data.mid(156,7));        // copy gt8 compressor part2
        data.replace(75, 8, temp);               // replace gt10 compressor
        temp = gt8_data.mid(212, 1);             // copy gt8 dist/od part1
        data.replace(123, 1, temp);              // replace gt10 distortion part1
        r = gt8_data.at(214);
        temp = Qhex.mid((180+r), 1);             // convert DISTORTION types from HexLookupTable address 180->
        temp.append(gt8_data.mid(215,5));        // copy gt8 dist/od part2
        data.replace(124, 6, temp);              // replace gt10 distortion


        temp = gt8_data.mid(233, 1);             // copy gt8 preAmp control part1
        temp.append(gt8_data.mid(235,2));        // copy gt8 preAmp control part2
        temp.append(gt8_data.mid(238,1));        // copy gt8 preAmp control part3
        temp.append(gt8_data.mid(237,1));        // copy gt8 preAmp control part4
        data.replace(152, 5, temp);              // replace gt10 preAmp control
        r = gt8_data.at(239);
        temp = Qhex.mid((224+r), 1);             // convert PRE_AMP types from HexLookupTable 224->
        temp.append(gt8_data.mid(240, 16));      // copy gt8 preAmp channel A
        data.replace(168, 17, temp);             // replace gt10 preAmp channel A
        r = gt8_data.at(256);
        temp = Qhex.mid((224+r), 1);             // convert PRE_AMP types from HexLookupTable 224->
        temp.append(gt8_data.mid(257, 16));      // copy gt8 preAmp channel B
        data.replace(200, 17, temp);             // replace gt10 preAmp channel B
        temp = gt8_data.mid(286, 1);             // copy gt8 EQ part1
        temp.append(gt8_data.mid(288,11));       // copy gt8 EQ part2
        data.replace(264, 12, temp);             // replace gt10 EQ


        temp = gt8_data.mid(545, 1);            // copy gt8 delay part1
        temp.append(gt8_data.mid(547,16));      // copy gt8 delay part2
        temp.append(gt8_data.mid(565,4));       // copy gt8 delay part3
        temp.append(gt8_data.mid(563,2));       // copy gt8 delay part4
        temp.append(gt8_data.mid(569,2));       // copy gt8 delay part5
        if (temp.mid(2,1)=="11"){temp.replace(2, 1, "00"); }; // gt10 don't have hold function in delay
        data.replace(1351, 25, temp);           // replace gt10 delay
        temp = gt8_data.mid(584, 1);            // copy gt8 chorus part1
        temp.append(gt8_data.mid(586,7));       // copy gt8 chorus part2
        data.replace(1383, 8, temp);            // replace gt10 chorus
        temp = gt8_data.mid(606, 1);            // copy gt8 reverb part1
        temp.append(gt8_data.mid(608,3));       // copy gt8 reverb part2
        temp.append(gt8_data.mid(611,5));       // copy gt8 reverb part3
        data.replace(1399, 9, temp);            // replace gt10 reverb
        temp = (gt8_data.mid(610,1));           // copy gt8 reverb part4
        data.replace(1410, 1, temp);            // replace gt10 reverb


        temp.clear();                            // Convert GT8 Chain items to GT10 format
        r = gt8_data.at(665);
        temp.append(Qhex.mid(r+164, 1));
        r = gt8_data.at(666);
        temp.append(Qhex.mid(r+164, 1));
        r = gt8_data.at(667);
        temp.append(Qhex.mid(r+164, 1));
        r = gt8_data.at(668);
        temp.append(Qhex.mid(r+164, 1));
        r = gt8_data.at(669);
        temp.append(Qhex.mid(r+164, 1));
        r = gt8_data.at(670);
        temp.append(Qhex.mid(r+164, 1));
        r = gt8_data.at(671);
        temp.append(Qhex.mid(r+164, 1));
        r = gt8_data.at(672);
        temp.append(Qhex.mid(r+164, 1));
        r = gt8_data.at(673);
        temp.append(Qhex.mid(r+164, 1));
        r = gt8_data.at(674);
        temp.append(Qhex.mid(r+164, 1));
        r = gt8_data.at(675);
        temp.append(Qhex.mid(r+164, 1));
        r = gt8_data.at(676);
        temp.append(Qhex.mid(r+164, 1));
        r = gt8_data.at(677);
        temp.append(Qhex.mid(r+164, 1));
        r = gt8_data.at(678);
        temp.append(Qhex.mid(r+164, 1));

        unsigned int a = temp.indexOf(Qhex.mid(4,1)); // locate gt10_preamp 1 **** find "04"
        temp.insert(a-1, Qhex.mid(16, 1));       //insert gt10_split before preamp 1 "10"
        temp.insert(a+1, Qhex.mid(17, 1));       // insert gt10_merge after preamp 1  "11"
        temp.insert(a+1, Qhex.mid(77, 1));     // insert NS_2 "4D"  77
        temp.insert(a+1, Qhex.mid(67, 1));       // insert channel B "43" 67
        data.replace(1492, 18, temp);            // replace gt10 chain


        temp = gt8_data.mid(194, 1);             // copy gt8 Loop part1
        temp.append(gt8_data.mid(196,3));        // copy gt8 Loop part2
        data.replace(1472, 4, temp);             // replace gt10 Loop (Send/Return))

        temp = gt8_data.mid(629, 4);             // copy gt8 NS
        data.replace(1464, 4, temp);             // replace gt10 NS_1
        data.replace(1468, 4, temp);             // replace gt10 NS_2

        temp = gt8_data.mid(176, 1);             // copy gt8 wah on/off
        data.replace(1415, 1, temp);             // replace gt10 pedal fx on/off
        r = gt8_data.at(737);
        temp = Qhex.mid((r+1), 1);               // copy gt8 ExSw Func
        data.replace(1421, 1, temp);             // replace gt10 ExSw 1 Func + 1
        r = gt8_data.at(722);
        temp = Qhex.mid((r+1), 1);               // copy gt8 CTL Func
        data.replace(1422, 1, temp);             // replace gt10 CTL 1 Func + 1
        temp = gt8_data.mid(178, 2);             // copy gt8 wah
        data.replace(1424, 2, temp);             // replace gt10 wah
        temp = gt8_data.mid(180, 1);             // copy gt8 wah level
        data.replace(1428, 1, temp);             // replace gt10 wah
        // todo replace direct level with effect inverted (optional).

        temp = gt8_data.mid(469, 5);             // copy gt8 pedal bend (fx2)
        data.replace(1435, 5, temp);             // replace gt10 pedal bend

        temp = gt8_data.mid(636, 1);             // copy gt8 FV level
        data.replace(1441, 1, temp);             // replace gt10 FV level
        temp = gt8_data.mid(637, 1);             // copy gt8 FV vol curve
        data.replace(1444, 1, temp);             // replace gt10 FV vol curve
        temp = gt8_data.mid(752, 2);             // copy gt8 FV vol min/max
        data.replace(1442, 2, temp);             // replace gt10 FV vol min/max

        temp = gt8_data.mid(651, 1);             // copy gt8 Amp control
        data.replace(1456, 1, temp);             // replace gt10 Amp control

        temp = gt8_data.mid(633, 1);             // copy gt8 Master patch level
        data.replace(1447, 1, temp);             // replace gt10 Master patch level
        temp = gt8_data.mid(634, 2);             // copy gt8 Master BPM
        data.replace(1454, 2, temp);             // replace gt10 Master BPM

        temp = gt8_data.mid(11, 1);              // copy gt8 FX1 on/off
        data.replace(293, 1, temp);              // replace gt10 FX1 on/off
        r = gt8_data.at(13);
        temp = Qhex.mid((128+r), 1);       // convert FX1 Type: selection items from lookup table Qhex (HexLookupTable.hex file) from 128 to 144
        temp.append(gt8_data.mid(14, 25));       // copy gt8 FX1 part2
        data.replace(294, 26, temp);             // replace gt10 FX1 part2
        temp = gt8_data.mid(49, 19);              // copy gt8 FX1 part3
        data.replace(320, 19, temp);             // replace gt10 FX1 part3
        temp = gt8_data.mid(68, 16);              // copy gt8 FX1 part4
        data.replace(341, 16, temp);             // replace gt10 FX1 part4
        temp = gt8_data.mid(98, 24);              // copy gt8 FX1 part5
        data.replace(357, 24, temp);             // replace gt10 FX1 part5
        temp = gt8_data.mid(130, 11);              // copy gt8 FX1 part6
        data.replace(381, 11, temp);              // replace gt10 FX1 part6
        temp = gt8_data.mid(84, 14);              // copy gt8 FX1 part7
        data.replace(479, 14, temp);             // replace gt10 FX1 part7
        temp = gt8_data.mid(122, 8);              // copy gt8 FX1 part8
        data.replace(493, 8, temp);              // replace gt10 FX1 part8
        temp = gt8_data.mid(39, 10);              // copy gt8 FX1 part9
        data.replace(747, 10, temp);               // replace gt10 FX1 part9


        temp = gt8_data.mid(312, 1);              // copy gt8 FX2 on/off
        data.replace(815, 1, temp);              // replace gt10 FX2 on/off
        r = gt8_data.at(314);
        temp = Qhex.mid((128+r), 1);       // convert FX2 Type: selection items from lookup table Qhex (HexLookupTable.hex file) from 128 to 144
        temp.append(gt8_data.mid(315, 25));       // copy gt8 FX2 part2
        data.replace(816, 26, temp);             // replace gt10 FX2 part2
        temp = gt8_data.mid(350, 19);              // copy gt8 FX2 part3
        data.replace(842, 19, temp);             // replace gt10 FX2 part3
        temp = gt8_data.mid(369, 16);              // copy gt8 FX2 part4
        data.replace(863, 16, temp);             // replace gt10 FX2 part4
        temp = gt8_data.mid(399, 24);              // copy gt8 FX2 part5
        data.replace(879, 24, temp);             // replace gt10 FX2 part5
        temp = gt8_data.mid(431, 11);              // copy gt8 FX2 part6
        data.replace(903, 11, temp);              // replace gt10 FX2 part6
        temp = gt8_data.mid(385, 14);              // copy gt8 FX2 part7
        data.replace(1001, 14, temp);             // replace gt10 FX2 part7
        temp = gt8_data.mid(423, 8);              // copy gt8 FX2 part8
        data.replace(1015, 8, temp);              // replace gt10 FX2 part8
        temp = gt8_data.mid(340, 10);              // copy gt8 FX2 part9
        data.replace(1269, 10, temp);               // replace gt10 FX2 part9
        temp = gt8_data.mid(442, 4);              // copy gt8 FX2 part10  HR
        temp.append(gt8_data.mid(447,5));
        temp.append(gt8_data.mid(446,1));
        temp.append(gt8_data.mid(453,1));
        data.replace(914, 11, temp);               // replace gt10 FX2 part10  HR
        temp = gt8_data.mid(454, 6);              // copy gt8 FX2 part11  PS
        temp.append(gt8_data.mid(461,7));
        temp.append(gt8_data.mid(460,1));
        temp.append(gt8_data.mid(468,1));
        data.replace(962, 15, temp);               // replace gt10 FX2 part11  PS
        temp = gt8_data.mid(474, 18);              // copy gt8 FX2 part12  OC, RT, 2CE
        data.replace(977, 18, temp);               // replace gt10 FX2 part12  OC, RT, 2CE
        temp = gt8_data.mid(492, 4);              // copy gt8 FX2 part13  AR
        temp.append(gt8_data.mid(497,4));
        data.replace(1040, 8, temp);               // replace gt10 FX2 part13  AR
        temp = gt8_data.mid(502, 1);              // copy gt8 FX2 part14  SYN
        temp.append(gt8_data.mid(501,1));
        temp.append(gt8_data.mid(503,15));
        data.replace(1023, 17, temp);               // replace gt10 FX2 part14 SYN
        temp = gt8_data.mid(518, 7);              // copy gt8 FX2 part15  AC
        data.replace(1279, 7, temp);               // replace gt10 FX2 part15 AC
        temp = gt8_data.mid(525, 3);              // copy gt8 FX2 part16  SH
        data.replace(1266, 3, temp);               // replace gt10 FX2 part16 SH
        temp = gt8_data.mid(528, 3);              // copy gt8 FX2 part17  SDD
        data.replace(995, 3, temp);               // replace gt10 FX2 part17 SDD
        temp = gt8_data.mid(531, 1);              // copy gt8 FX2 part18  SDD
        data.replace(999, 1, temp);               // replace gt10 FX2 part18 SDD

    };
}

void sysxWriter::translate10to100()
{
    MidiTable *midiTable = MidiTable::Instance();
    QByteArray GT100_default;
    QFile file(":default.syx");           // Read the default GT-100 sysx file .
    if (file.open(QIODevice::ReadOnly))
    {GT100_default = file.readAll(); };

    GT100_default.replace(11, 16, data.mid(11, 16));   //copy name
    GT100_default.replace(27, 1, data.mid(28, 1));     //copy output select
    GT100_default.replace(43, 4, data.mid(75, 4));     //copy comp
    GT100_default.replace(47, 2, data.mid(81, 2));     //copy comp
    GT100_default.replace(59, 1, data.mid(123, 1));    //copy dist
    GT100_default.replace(60, 1, midiTable->getArrayValue("Tables", "00", "00", "00", data.mid(124, 1))); // convert type
    GT100_default.replace(61, 3, data.mid(125, 3));    //copy dist
    GT100_default.replace(64, 2, data.mid(130, 2));    //copy dist
    GT100_default.replace(66, 2, data.mid(128, 2));    //copy dist
    GT100_default.replace(68, 1, data.mid(132, 1));    //copy dist
    GT100_default.replace(69, 1, midiTable->getArrayValue("Tables", "00", "00", "01", data.mid(133, 1))); //convert custom dist
    GT100_default.replace(70, 1, midiTable->getArrayValue("Tables", "00", "00", "01", data.mid(134, 1))); //convert custom dist
    GT100_default.replace(71, 1, midiTable->getArrayValue("Tables", "00", "00", "01", data.mid(135, 1))); //convert custom dist
    GT100_default.replace(72, 1, midiTable->getArrayValue("Tables", "00", "00", "01", data.mid(136, 1))); //convert custom dist
    GT100_default.replace(91, 1, data.mid(152, 1));  //copy Preamp A sw
    GT100_default.replace(92, 1, midiTable->getArrayValue("Tables", "00", "00", "02", data.mid(168, 1))); //convert pre type
    GT100_default.replace(93, 1, data.mid(169, 1));    //copy pre A gain
    GT100_default.replace(96, 16, data.mid(171, 16));  //copy pre A
    GT100_default.replace(111, 1, midiTable->getArrayValue("Tables", "00", "00", "01", data.mid(186, 1))); //convert custom pre
    GT100_default.replace(112, 1, midiTable->getArrayValue("Tables", "00", "00", "01", data.mid(187, 1))); //convert custom pre
    GT100_default.replace(115, 1, midiTable->getArrayValue("Tables", "00", "00", "01", data.mid(190, 1))); //convert custom pre
    GT100_default.replace(116, 1, midiTable->getArrayValue("Tables", "00", "00", "01", data.mid(191, 1))); //convert custom pre
    GT100_default.replace(118, 5, data.mid(192, 5));  //copy custom spkr A
    GT100_default.replace(152, 1, data.mid(152, 1));  //copy Preamp B sw
    GT100_default.replace(153, 1, midiTable->getArrayValue("Tables", "00", "00", "02", data.mid(200, 1))); //convert pre type
    GT100_default.replace(154, 1, data.mid(201, 1));    //copy pre B gain
    GT100_default.replace(157, 16, data.mid(203, 16));  //copy pre B
    GT100_default.replace(172, 1, midiTable->getArrayValue("Tables", "00", "00", "01", data.mid(218, 1))); //convert custom pre
    GT100_default.replace(173, 1, midiTable->getArrayValue("Tables", "00", "00", "01", data.mid(219, 1))); //convert custom pre
    GT100_default.replace(176, 1, midiTable->getArrayValue("Tables", "00", "00", "01", data.mid(222, 1))); //convert custom pre
    GT100_default.replace(177, 1, midiTable->getArrayValue("Tables", "00", "00", "01", data.mid(223, 1))); //convert custom pre
    GT100_default.replace(179, 5, data.mid(224, 5));  //copy custom spkr B
    GT100_default.replace(200, 12, data.mid(264, 12));  //copy EQ
    GT100_default.replace(201, 1, midiTable->getArrayValue("Tables", "00", "00", "03", data.mid(265, 1))); //convert lo cut
    GT100_default.replace(210, 1, midiTable->getArrayValue("Tables", "00", "00", "04", data.mid(274, 1))); //convert hi cut
    GT100_default.replace(216, 1, data.mid(293, 1));  //copy FX1 sw
    GT100_default.replace(217, 1, midiTable->getArrayValue("Tables", "00", "00", "05", data.mid(294, 1))); //convert FX type
    GT100_default.replace(251, 5, data.mid(295, 5));  //copy ACS
    GT100_default.replace(257, 6, data.mid(300, 6));  //copy ALM
    GT100_default.replace(228, 7, data.mid(306, 7));  //copy TW
    GT100_default.replace(236, 7, data.mid(313, 7));  //copy AW
    GT100_default.replace(441, 3, data.mid(320, 3));  //copy TR
    GT100_default.replace(410, 8, data.mid(323, 8));  //copy PH
    GT100_default.replace(419, 2, data.mid(331, 2));  //copy FL
    GT100_default.replace(434, 6, data.mid(333, 6));  //copy FL
    GT100_default.replace(458, 5, data.mid(339, 5));  //copy PAN
    GT100_default.replace(471, 4, data.mid(344, 4));  //copy VB
    GT100_default.replace(454, 3, data.mid(348, 3));  //copy UV
    GT100_default.replace(477, 4, data.mid(351, 4));  //copy RM
    GT100_default.replace(313, 2, data.mid(355, 2));  //copy SG
    GT100_default.replace(482, 8, data.mid(370, 8));  //copy HU
    GT100_default.replace(465, 3, data.mid(378, 3));  //copy SL
    GT100_default.replace(276, 1, midiTable->getArrayValue("Tables", "00", "00", "03", data.mid(381, 1))); //convert lo cut
    GT100_default.replace(277, 3, data.mid(382, 3));  //copy SEQ
    GT100_default.replace(293, 5, data.mid(385, 5));  //copy SEQ
    GT100_default.replace(298, 1, midiTable->getArrayValue("Tables", "00", "00", "04", data.mid(390, 1))); //convert hi cut
    GT100_default.replace(299, 1, data.mid(391, 1));  //copy SEQ
    GT100_default.replace(362, 29, data.mid(392, 29));//copy HR
    GT100_default.replace(391, 6, data.mid(434, 6));  //copy HR
    GT100_default.replace(346, 15, data.mid(440, 15));//copy PS
    GT100_default.replace(342, 3, data.mid(455, 3));  //copy OC
    GT100_default.replace(446, 6, data.mid(458, 6));  //copy RT
    GT100_default.replace(491, 9, data.mid(464, 9));  //copy 2CE
    GT100_default.replace(504, 4, data.mid(475, 4));  //copy SDD
    GT100_default.replace(502, 2, data.mid(473, 2));  //copy SDD
    GT100_default.replace(505, 1, midiTable->getArrayValue("Tables", "00", "00", "04", data.mid(476, 1))); //convert hi cut
    GT100_default.replace(317, 7, data.mid(479, 7));  //copy DF
    GT100_default.replace(334, 7, data.mid(486, 7));  //copy SITAR
    GT100_default.replace(325, 8, data.mid(493, 8));  //copy WSY
    GT100_default.replace(398, 3, data.mid(744, 3));  //copy SH
    GT100_default.replace(301, 5, data.mid(747, 5));  //copy TM
    GT100_default.replace(307, 5, data.mid(752, 5));  //copy GS
    GT100_default.replace(402, 7, data.mid(757, 7));  //copy AC
    GT100_default.replace(244, 6, data.mid(764, 6));  //copy SWAH
    GT100_default.replace(264, 1, midiTable->getArrayValue("Tables", "00", "00", "06", data.mid(771, 1))); //convert GEQ
    GT100_default.replace(265, 1, midiTable->getArrayValue("Tables", "00", "00", "06", data.mid(772, 1))); //convert GEQ
    GT100_default.replace(266, 1, midiTable->getArrayValue("Tables", "00", "00", "06", data.mid(773, 1))); //convert GEQ
    GT100_default.replace(267, 1, midiTable->getArrayValue("Tables", "00", "00", "06", data.mid(774, 1))); //convert GEQ
    GT100_default.replace(268, 1, midiTable->getArrayValue("Tables", "00", "00", "06", data.mid(775, 1))); //convert GEQ
    GT100_default.replace(269, 1, midiTable->getArrayValue("Tables", "00", "00", "06", data.mid(776, 1))); //convert GEQ
    GT100_default.replace(270, 1, midiTable->getArrayValue("Tables", "00", "00", "06", data.mid(777, 1))); //convert GEQ
    GT100_default.replace(271, 1, midiTable->getArrayValue("Tables", "00", "00", "06", data.mid(778, 1))); //convert GEQ
    GT100_default.replace(272, 1, midiTable->getArrayValue("Tables", "00", "00", "06", data.mid(779, 1))); //convert GEQ
    GT100_default.replace(273, 1, midiTable->getArrayValue("Tables", "00", "00", "06", data.mid(780, 1))); //convert GEQ
    GT100_default.replace(274, 1, midiTable->getArrayValue("Tables", "00", "00", "06", data.mid(770, 1))); //convert GEQ
    GT100_default.replace(510, 1, data.mid(815, 1));  //copy FX2 sw
    GT100_default.replace(511, 1, midiTable->getArrayValue("Tables", "00", "00", "05", data.mid(816, 1))); //convert FX type
    GT100_default.replace(545, 5, data.mid(817, 5));  //copy ACS
    GT100_default.replace(551, 6, data.mid(822, 6));  //copy ALM
    GT100_default.replace(522, 7, data.mid(828, 7));  //copy TW
    GT100_default.replace(530, 7, data.mid(835, 7));  //copy AW
    GT100_default.replace(735, 3, data.mid(842, 3));  //copy TR
    GT100_default.replace(716, 8, data.mid(845, 8));  //copy PH
    GT100_default.replace(726, 8, data.mid(853, 8));  //copy FL
    GT100_default.replace(752, 5, data.mid(861, 5));  //copy PAN
    GT100_default.replace(765, 4, data.mid(866, 4));  //copy VB
    GT100_default.replace(748, 3, data.mid(870, 3));  //copy UV
    GT100_default.replace(771, 4, data.mid(873, 4));  //copy RM
    GT100_default.replace(607, 2, data.mid(877, 2));  //copy SG
    GT100_default.replace(776, 8, data.mid(892, 8));  //copy HU
    GT100_default.replace(759, 3, data.mid(900, 3));  //copy SL
    GT100_default.replace(583, 1, midiTable->getArrayValue("Tables", "00", "00", "03", data.mid(903, 1))); //convert lo cut
    GT100_default.replace(584, 8, data.mid(904, 8));  //copy SEQ
    GT100_default.replace(592, 1, midiTable->getArrayValue("Tables", "00", "00", "04", data.mid(912, 1))); //convert hi cut
    GT100_default.replace(593, 1, data.mid(913, 1));  //copy SEQ
    GT100_default.replace(656, 29, data.mid(914, 29));//copy HR
    GT100_default.replace(685, 6, data.mid(956, 6));  //copy HR
    GT100_default.replace(640, 15, data.mid(962, 15));//copy PS
    GT100_default.replace(636, 3, data.mid(977, 3));  //copy OC
    GT100_default.replace(740, 6, data.mid(980, 6));  //copy RT
    GT100_default.replace(785, 9, data.mid(986, 9));  //copy 2CE
    GT100_default.replace(796, 6, data.mid(995, 6));  //copy SDD
    GT100_default.replace(799, 1, midiTable->getArrayValue("Tables", "00", "00", "04", data.mid(998, 1))); //convert hi cut
    GT100_default.replace(611, 7, data.mid(1001, 7));  //copy DF
    GT100_default.replace(628, 7, data.mid(1008, 7));  //copy SITAR
    GT100_default.replace(619, 8, data.mid(1015, 8));  //copy WSY
    GT100_default.replace(692, 3, data.mid(1266, 3));  //copy SH
    GT100_default.replace(595, 5, data.mid(1269, 5));  //copy TM
    GT100_default.replace(601, 5, data.mid(1274, 5));  //copy GS
    GT100_default.replace(696, 7, data.mid(1279, 7));  //copy AC
    GT100_default.replace(538, 6, data.mid(1286, 6));  //copy SWAH
    GT100_default.replace(558, 1, midiTable->getArrayValue("Tables", "00", "00", "06", data.mid(1293, 1))); //convert GEQ
    GT100_default.replace(559, 1, midiTable->getArrayValue("Tables", "00", "00", "06", data.mid(1294, 1))); //convert GEQ
    GT100_default.replace(560, 1, midiTable->getArrayValue("Tables", "00", "00", "06", data.mid(1295, 1))); //convert GEQ
    GT100_default.replace(561, 1, midiTable->getArrayValue("Tables", "00", "00", "06", data.mid(1296, 1))); //convert GEQ
    GT100_default.replace(575, 1, midiTable->getArrayValue("Tables", "00", "00", "06", data.mid(1297, 1))); //convert GEQ
    GT100_default.replace(576, 1, midiTable->getArrayValue("Tables", "00", "00", "06", data.mid(1298, 1))); //convert GEQ
    GT100_default.replace(577, 1, midiTable->getArrayValue("Tables", "00", "00", "06", data.mid(1299, 1))); //convert GEQ
    GT100_default.replace(578, 1, midiTable->getArrayValue("Tables", "00", "00", "06", data.mid(1300, 1))); //convert GEQ
    GT100_default.replace(579, 1, midiTable->getArrayValue("Tables", "00", "00", "06", data.mid(1301, 1))); //convert GEQ
    GT100_default.replace(580, 1, midiTable->getArrayValue("Tables", "00", "00", "06", data.mid(1302, 1))); //convert GEQ
    GT100_default.replace(581, 1, midiTable->getArrayValue("Tables", "00", "00", "06", data.mid(1292, 1))); //convert GEQ
    GT100_default.replace(812, 1, data.mid(1351, 1));  //copy DD sw
    GT100_default.replace(813, 1, midiTable->getArrayValue("Tables", "00", "00", "07", data.mid(1352, 1))); //convert DD type
    GT100_default.replace(814, 2, data.mid(1353, 2));  //copy DD time
    GT100_default.replace(820, 1, data.mid(1355, 1));  //copy DD tap
    GT100_default.replace(816, 1, data.mid(1356, 1));  //copy DD fb
    GT100_default.replace(817, 1, midiTable->getArrayValue("Tables", "00", "00", "04", data.mid(1357, 1))); //convert hi cut
    GT100_default.replace(821, 10, data.mid(1358, 10));  //copy DD
    GT100_default.replace(824, 1, midiTable->getArrayValue("Tables", "00", "00", "03", data.mid(1361, 1))); //convert lo cut
    GT100_default.replace(829, 1, midiTable->getArrayValue("Tables", "00", "00", "04", data.mid(1366, 1))); //convert hi cut
    GT100_default.replace(831, 2, data.mid(1372, 2));  //copy DD mod
    GT100_default.replace(818, 2, data.mid(1374, 2));  //copy DD level
    GT100_default.replace(857, 5, data.mid(1383, 5));  //copy CE
    GT100_default.replace(862, 1, midiTable->getArrayValue("Tables", "00", "00", "03", data.mid(1388, 1))); //convert lo cut
    GT100_default.replace(863, 1, midiTable->getArrayValue("Tables", "00", "00", "04", data.mid(1389, 1))); //convert hi cut
    GT100_default.replace(864, 1, data.mid(1390, 1));  //copy CE
    GT100_default.replace(873, 3, data.mid(1399, 3));  //copy RV
    GT100_default.replace(878, 1, midiTable->getArrayValue("Tables", "00", "00", "03", data.mid(1403, 1))); //convert lo cut
    GT100_default.replace(879, 1, midiTable->getArrayValue("Tables", "00", "00", "04", data.mid(1404, 1))); //convert hi cut
    GT100_default.replace(880, 4, data.mid(1405, 4));  //copy RV
    GT100_default.replace(876, 2, data.mid(1409, 2));  //copy RV pre delay
    GT100_default.replace(889, 1, data.mid(1415, 1));  //copy PFX sw
    GT100_default.replace(1155, 1, data.mid(1420, 1));  //copy PFX mode
    GT100_default.replace(1094, 1, midiTable->getArrayValue("Tables", "00", "00", "08", data.mid(1421, 1))); //convert EXP sw func
    GT100_default.replace(1078, 1, midiTable->getArrayValue("Tables", "00", "00", "09", data.mid(1422, 1))); //convert ctl 1 func
    GT100_default.replace(1110, 1, midiTable->getArrayValue("Tables", "00", "00", "09", data.mid(1423, 1))); //convert ctl 2 func
    GT100_default.replace(895, 6, data.mid(1424, 6));  //copy PFX WAH
    GT100_default.replace(891, 4, data.mid(1436, 4));  //copy PFX PB
    GT100_default.replace(908, 1, data.mid(1441, 1));  //copy PFX FV
    GT100_default.replace(906, 2, data.mid(1442, 2));  //copy PFX FV
    GT100_default.replace(905, 1, data.mid(1444, 1));  //copy PFX FV
    GT100_default.replace(1014, 1, data.mid(1447, 1));  //copy MST
    GT100_default.replace(1015, 1, midiTable->getArrayValue("Tables", "00", "00", "06", data.mid(1448, 1))); //convert MEQ
    GT100_default.replace(1018, 1, midiTable->getArrayValue("Tables", "00", "00", "06", data.mid(1449, 1))); //convert MEQ
    GT100_default.replace(1017, 1, data.mid(1450, 1));  //copy MST
    GT100_default.replace(1016, 1, data.mid(1451, 1));  //copy MST
    GT100_default.replace(1019, 1, midiTable->getArrayValue("Tables", "00", "00", "06", data.mid(1452, 1))); //convert MEQ
    GT100_default.replace(1020, 3, data.mid(1453, 3));  //copy MST bpm
    GT100_default.replace(953, 1, data.mid(1456, 1));  //copy AMP sw
    GT100_default.replace(956, 4, data.mid(1464, 4));  //copy NS1
    GT100_default.replace(961, 4, data.mid(1468, 4));  //copy NS2
    GT100_default.replace(942, 4, data.mid(1472, 4));  //copy SR loop

    QByteArray chain(data.mid(1492, 18)); //copy gt10 chain
    QString chn;
    QString list;
    for(int x=0; x<18; ++x)
    {
        char r = chain.at(x);
        QString val = QString::number(r, 16).toUpper();
        if(val.size()<2){val.prepend("0"); };
        chn.append(val);
        list.append(chn.mid(x*2, 1)); // make list of 10's units of chain items, channel b are prepended with 4
    };
    int pos = list.indexOf("4"); //find position of channel b start

    chain.replace(0, 1, midiTable->getArrayValue("Tables", "00", "00", "0A", chain.mid(0, 1))); //convert chain
    chain.replace(1, 1, midiTable->getArrayValue("Tables", "00", "00", "0A", chain.mid(1, 1))); //convert chain
    chain.replace(2, 1, midiTable->getArrayValue("Tables", "00", "00", "0A", chain.mid(2, 1))); //convert chain
    chain.replace(3, 1, midiTable->getArrayValue("Tables", "00", "00", "0A", chain.mid(3, 1))); //convert chain
    chain.replace(4, 1, midiTable->getArrayValue("Tables", "00", "00", "0A", chain.mid(4, 1))); //convert chain
    chain.replace(5, 1, midiTable->getArrayValue("Tables", "00", "00", "0A", chain.mid(5, 1))); //convert chain
    chain.replace(6, 1, midiTable->getArrayValue("Tables", "00", "00", "0A", chain.mid(6, 1))); //convert chain
    chain.replace(7, 1, midiTable->getArrayValue("Tables", "00", "00", "0A", chain.mid(7, 1))); //convert chain
    chain.replace(8, 1, midiTable->getArrayValue("Tables", "00", "00", "0A", chain.mid(8, 1))); //convert chain
    chain.replace(9, 1, midiTable->getArrayValue("Tables", "00", "00", "0A", chain.mid(9, 1))); //convert chain
    chain.replace(10, 1, midiTable->getArrayValue("Tables", "00", "00", "0A", chain.mid(10, 1))); //convert chain
    chain.replace(11, 1, midiTable->getArrayValue("Tables", "00", "00", "0A", chain.mid(11, 1))); //convert chain
    chain.replace(12, 1, midiTable->getArrayValue("Tables", "00", "00", "0A", chain.mid(12, 1))); //convert chain
    chain.replace(13, 1, midiTable->getArrayValue("Tables", "00", "00", "0A", chain.mid(13, 1))); //convert chain
    chain.replace(14, 1, midiTable->getArrayValue("Tables", "00", "00", "0A", chain.mid(14, 1))); //convert chain
    chain.replace(15, 1, midiTable->getArrayValue("Tables", "00", "00", "0A", chain.mid(15, 1))); //convert chain
    chain.replace(16, 1, midiTable->getArrayValue("Tables", "00", "00", "0A", chain.mid(16, 1))); //convert chain
    chain.replace(17, 1, midiTable->getArrayValue("Tables", "00", "00", "0A", chain.mid(17, 1))); //convert chain
    chain.insert(17, (char)10);
    chain.insert(pos, (char)18);
    GT100_default.replace(1030, 20, chain);

    GT100_default.replace(1187, 1, data.mid(1524, 1));  //copy Assign 1
    GT100_default.replace(1188, 2, midiTable->getArrayValue("Tables", "00", "00", "0B", data.mid(1525, 2))); //convert target
    GT100_default.replace(1190, 4, data.mid(1527, 4));  //copy min/max
    GT100_default.replace(1194, 1, midiTable->getArrayValue("Tables", "00", "00", "0C", data.mid(1531, 1))); //convert source
    GT100_default.replace(1195, 3, data.mid(1532, 3));  //copy Assign
    GT100_default.replace(1198, 1, midiTable->getArrayValue("Tables", "00", "00", "0D", data.mid(1535, 1))); //convert int pedal
    GT100_default.replace(1199, 4, data.mid(1536, 4));  //copy Assign
    GT100_default.replace(1219, 1, data.mid(1540, 1));  //copy Assign 2
    GT100_default.replace(1220, 2, midiTable->getArrayValue("Tables", "00", "00", "0B", data.mid(1541, 2))); //convert target
    GT100_default.replace(1222, 4, data.mid(1543, 4));  //copy min/max
    GT100_default.replace(1226, 1, midiTable->getArrayValue("Tables", "00", "00", "0C", data.mid(1547, 1))); //convert source
    GT100_default.replace(1227, 3, data.mid(1548, 3));  //copy Assign
    GT100_default.replace(1230, 1, midiTable->getArrayValue("Tables", "00", "00", "0D", data.mid(1551, 1))); //convert int pedal
    GT100_default.replace(1231, 4, data.mid(1552, 4));  //copy Assign
    GT100_default.replace(1251, 1, data.mid(1556, 1));  //copy Assign 3
    GT100_default.replace(1252, 2, midiTable->getArrayValue("Tables", "00", "00", "0B", data.mid(1557, 2))); //convert target
    GT100_default.replace(1254, 4, data.mid(1559, 4));  //copy min/max
    GT100_default.replace(1258, 1, midiTable->getArrayValue("Tables", "00", "00", "0C", data.mid(1563, 1))); //convert source
    GT100_default.replace(1259, 3, data.mid(1564, 3));  //copy Assign
    GT100_default.replace(1262, 1, midiTable->getArrayValue("Tables", "00", "00", "0D", data.mid(1567, 1))); //convert int pedal
    GT100_default.replace(1263, 4, data.mid(1568, 4));  //copy Assign
    GT100_default.replace(1296, 1, data.mid(1572, 1));  //copy Assign 4
    GT100_default.replace(1297, 2, midiTable->getArrayValue("Tables", "00", "00", "0B", data.mid(1573, 2))); //convert target
    GT100_default.replace(1299, 4, data.mid(1575, 4));  //copy min/max
    GT100_default.replace(1303, 1, midiTable->getArrayValue("Tables", "00", "00", "0C", data.mid(1579, 1))); //convert source
    GT100_default.replace(1304, 3, data.mid(1580, 3));  //copy Assign
    GT100_default.replace(1307, 1, midiTable->getArrayValue("Tables", "00", "00", "0D", data.mid(1583, 1))); //convert int pedal
    GT100_default.replace(1308, 4, data.mid(1584, 4));  //copy Assign
    GT100_default.replace(1328, 1, data.mid(1588, 1));  //copy Assign 5
    GT100_default.replace(1329, 2, midiTable->getArrayValue("Tables", "00", "00", "0B", data.mid(1589, 2))); //convert target
    GT100_default.replace(1331, 4, data.mid(1591, 4));  //copy min/max
    GT100_default.replace(1335, 1, midiTable->getArrayValue("Tables", "00", "00", "0C", data.mid(1595, 1))); //convert source
    GT100_default.replace(1336, 3, data.mid(1596, 3));  //copy Assign
    GT100_default.replace(1339, 1, midiTable->getArrayValue("Tables", "00", "00", "0D", data.mid(1599, 1))); //convert int pedal
    GT100_default.replace(1340, 4, data.mid(1600, 4));  //copy Assign
    GT100_default.replace(1360, 1, data.mid(1604, 1));  //copy Assign 6
    GT100_default.replace(1361, 2, midiTable->getArrayValue("Tables", "00", "00", "0B", data.mid(1605, 2))); //convert target
    GT100_default.replace(1363, 4, data.mid(1607, 4));  //copy min/max
    GT100_default.replace(1367, 1, midiTable->getArrayValue("Tables", "00", "00", "0C", data.mid(1611, 1))); //convert source
    GT100_default.replace(1368, 3, data.mid(1612, 3));  //copy Assign
    GT100_default.replace(1371, 1, midiTable->getArrayValue("Tables", "00", "00", "0D", data.mid(1615, 1))); //convert int pedal
    GT100_default.replace(1372, 4, data.mid(1616, 4));  //copy Assign
    GT100_default.replace(1392, 1, data.mid(1633, 1));  //copy Assign 7
    GT100_default.replace(1393, 2, midiTable->getArrayValue("Tables", "00", "00", "0B", data.mid(1634, 2))); //convert target
    GT100_default.replace(1395, 4, data.mid(1636, 4));  //copy min/max
    GT100_default.replace(1399, 1, midiTable->getArrayValue("Tables", "00", "00", "0C", data.mid(1640, 1))); //convert source
    GT100_default.replace(1400, 3, data.mid(1641, 3));  //copy Assign
    GT100_default.replace(1403, 1, midiTable->getArrayValue("Tables", "00", "00", "0D", data.mid(1644, 1))); //convert int pedal
    GT100_default.replace(1404, 4, data.mid(1645, 4));  //copy Assign
    GT100_default.replace(1437, 1, data.mid(1649, 1));  //copy Assign 8
    GT100_default.replace(1438, 2, midiTable->getArrayValue("Tables", "00", "00", "0B", data.mid(1650, 2))); //convert target
    GT100_default.replace(1440, 4, data.mid(1652, 4));  //copy min/max
    GT100_default.replace(1444, 1, midiTable->getArrayValue("Tables", "00", "00", "0C", data.mid(1656, 1))); //convert source
    GT100_default.replace(1445, 3, data.mid(1657, 3));  //copy Assign
    GT100_default.replace(1448, 1, midiTable->getArrayValue("Tables", "00", "00", "0D", data.mid(1660, 1))); //convert int pedal
    GT100_default.replace(1449, 4, data.mid(1661, 4));  //copy Assign
    GT100_default.replace(1469, 1, data.mid(1665, 1));  //copy input sensitivity
    GT100_default.replace(922, 1, data.mid(154, 1));  //copy Channel A/B select
    GT100_default.replace(939, 1, data.mid(155, 1));  //copy Channel Delay
    GT100_default.replace(924, 1, data.mid(156, 1));  //copy Channel A dynamic
    GT100_default.replace(928, 1, data.mid(156, 1));  //copy Channel B dynamic
    GT100_default.replace(921, 1, midiTable->getArrayValue("Tables", "00", "00", "0E", data.mid(153, 1))); //convert CH mode
    GT100_default.replace(923, 1, midiTable->getArrayValue("Tables", "00", "00", "0F", data.mid(153, 1))); //convert dynamic A
    GT100_default.replace(927, 1, midiTable->getArrayValue("Tables", "00", "00", "10", data.mid(153, 1))); //convert dynamic B

    SysxIO *sysxIO = SysxIO::Instance();
    sysxIO->setFileSource("Structure", GT100_default);
    sysxIO->setFileName(this->fileName);
    this->fileSource = sysxIO->getFileSource();
}
