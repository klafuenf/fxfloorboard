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

#include <QtWidgets>
#include <QFile>
#include <QDataStream>
#include <QByteArray>
#include <QMessageBox>
#include "bulkSaveDialog.h"
#include "Preferences.h"
#include "globalVariables.h"


// Platform-dependent sleep routines.
#ifdef Q_OS_WIN
#include <windows.h>
#define SLEEP( milliseconds ) Sleep( (DWORD) milliseconds )
#else // Unix variants & Mac
#include <unistd.h>
#define SLEEP( milliseconds ) usleep( (unsigned long) (milliseconds * 1000.0) )
#endif

bulkSaveDialog::bulkSaveDialog()
{ 
    QLabel *startRangeLabel = new QLabel(tr("Start Bank."));
    QLabel *finishRangeLabel = new QLabel(tr("Finish Bank."));

    this->gclButton = new QRadioButton(tr("*.gcl Librarian file"), this );
    this->syxButton = new QRadioButton(tr("*.syx System Exclusive file"), this );
    this->midButton = new QRadioButton(tr("*.mid Standard Midi (SMF) file"), this );
    this->gclButton->setChecked(true);
    
    QCheckBox *systemCheckBox = new QCheckBox(tr("Save System Data"));
    QSpinBox *startRangeSpinBox = new QSpinBox;
    QSpinBox *finishRangeSpinBox = new QSpinBox;

    this->systemCheckBox = systemCheckBox;

    this->startRangeSpinBox = startRangeSpinBox;
    startRangeSpinBox->setValue(1);
    startRangeSpinBox->setRange(1, 50);
    startRangeSpinBox->setPrefix(tr("Start at U"));
    startRangeSpinBox->setSuffix("-1");

    this->finishRangeSpinBox = finishRangeSpinBox;
    finishRangeSpinBox->setValue(50);
    finishRangeSpinBox->setRange(1, 50);
    finishRangeSpinBox->setPrefix(tr("Finish at U"));
    finishRangeSpinBox->setSuffix("-4");

    QVBoxLayout *rangeLabelLayout = new QVBoxLayout;
    rangeLabelLayout->addSpacing(12);
    rangeLabelLayout->addWidget(startRangeLabel);
    rangeLabelLayout->addWidget(finishRangeLabel);

    QVBoxLayout *rangeBoxLayout = new QVBoxLayout;
    //rangeBoxLayout->addWidget(systemCheckBox);
    rangeBoxLayout->addSpacing(12);
    rangeBoxLayout->addWidget(startRangeSpinBox);
    rangeBoxLayout->addSpacing(12);
    rangeBoxLayout->addWidget(finishRangeSpinBox);

    QHBoxLayout *dataRangeLayout = new QHBoxLayout;
    dataRangeLayout->addSpacing(20);
    dataRangeLayout->addLayout(rangeLabelLayout);
    //dataRangeLayout->addSpacing(12);
    dataRangeLayout->addLayout(rangeBoxLayout);
    dataRangeLayout->addSpacing(20);

    QGroupBox *patchRangeGroup = new QGroupBox(tr("Set range of Patch data to save"));
    patchRangeGroup->setLayout(dataRangeLayout);

    this->startButton = new QPushButton(this);
    this->startButton->setText(tr("Start"));
    connect(startButton, SIGNAL(clicked()), this, SLOT(backup()));

    this->completedButton = new QPushButton(this);
    this->completedButton->setText(tr("DATA TRANSFER COMPLETED"));
    this->completedButton->hide();
    connect(completedButton, SIGNAL(clicked()), this, SLOT(DialogClose()));

    this->cancelButton = new QPushButton(this);
    this->cancelButton->setText(tr("Cancel"));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(DialogClose()));

    this->progressLabel = new QLabel(this);
    this->progressLabel->setText(tr("Full Backup may take up to 2 minutes"));
    this->bytesLabel = new QLabel(this);
    this->bytesLabel->setText("");

    this->progressBar = new QProgressBar(this);
    this->progressBar->setTextVisible(false);
    this->progressBar->setRange(0, 100);
    this->progressBar->setValue(0);

    QVBoxLayout *fileFormatLayout = new QVBoxLayout;
    fileFormatLayout->addStretch(1);
    fileFormatLayout->addSpacing(6);
    fileFormatLayout->addWidget(gclButton);
    fileFormatLayout->addStretch(1);
    fileFormatLayout->addSpacing(6);
    fileFormatLayout->addWidget(syxButton);
    fileFormatLayout->addStretch(1);
    fileFormatLayout->addSpacing(6);
    fileFormatLayout->addWidget(midButton);
    fileFormatLayout->addSpacing(6);
    QGroupBox *fileFormatGroup = new QGroupBox(tr("Select File format to save"));
    fileFormatGroup->setLayout(fileFormatLayout);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addSpacing(40);
    buttonsLayout->addWidget(startButton);
    buttonsLayout->addStretch(1);
    buttonsLayout->addSpacing(20);
    buttonsLayout->addWidget(cancelButton);
    buttonsLayout->addSpacing(40);

    QHBoxLayout *progressBarLayout = new QHBoxLayout;
    progressBarLayout->addWidget(progressBar);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(fileFormatGroup);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(buttonsLayout, Qt::AlignCenter);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addWidget(patchRangeGroup, Qt::AlignCenter);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addWidget(progressLabel, Qt::AlignCenter);

    mainLayout->addWidget(bytesLabel, Qt::AlignCenter);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addWidget(completedButton);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(progressBarLayout, Qt::AlignCenter);
    setLayout(mainLayout);

    setWindowTitle(tr("Bulk File Backup"));

    //QObject::connect(this, SIGNAL( startRangeSpinBox->valueChanged(int) ), this, SLOT( bankStart(int) ));
    //QObject::connect(this, SIGNAL( finishRangeSpinBox->valueChanged(int) ), this, SLOT( bankFinish(int) ));
    SysxIO *sysxIO = SysxIO::Instance();
    QObject::connect(this, SIGNAL(setStatusSymbol(int)), sysxIO, SIGNAL(setStatusSymbol(int)));
    QObject::connect(this, SIGNAL(setStatusProgress(int)), sysxIO, SIGNAL(setStatusProgress(int)));
    QObject::connect(this, SIGNAL(setStatusMessage(QString)), sysxIO, SIGNAL(setStatusMessage(QString)));

}

bulkSaveDialog::~bulkSaveDialog()
{
}

void bulkSaveDialog::backup()
{
    this->startButton->hide();
    //this->cancelButton->hide();
    this->bankStart = this->startRangeSpinBox->value();
    this->bankFinish = this->finishRangeSpinBox->value();
    if (bankFinish<bankStart) {bankFinish = bankStart; this->finishRangeSpinBox->setValue(bankStart); };
    this->bank=bankStart*4;
    bulk.clear();
    this->progress = 0;
    this->patch = 1;
    range = 200/(bankFinish-bankStart+1);
    requestPatch(bank/4, patch);
}

void bulkSaveDialog::requestPatch(int bank, int patch) 
{	
    SysxIO *sysxIO = SysxIO::Instance();
    if(sysxIO->isConnected() && sysxIO->deviceReady() )
    {
        SysxIO *sysxIO = SysxIO::Instance();
        QObject::connect(sysxIO, SIGNAL(sysxReply(QString)), this, SLOT(updatePatch(QString)));
        sysxIO->requestPatch(bank, patch);
    };
}

void bulkSaveDialog::updatePatch(QString replyMsg)
{
    SysxIO *sysxIO = SysxIO::Instance();
    QObject::disconnect(sysxIO, SIGNAL(sysxReply(QString)), this, SLOT(updatePatch(QString)));
    sysxIO->setDeviceReady(true); // Free the device after finishing interaction.

    replyMsg = replyMsg.remove(" ").toUpper();       /* TRANSLATE SYSX MESSAGE FORMAT to 128 byte data blocks */
    if (replyMsg.size()/2 == patchReplySize){
        QString header = "F0410000006012";
        QString footer ="00F7";
        QString addressMsb = replyMsg.mid(14,4);
        QString part1 = replyMsg.mid(22, 256); //y
        part1.prepend("0000").prepend(addressMsb).prepend(header).append(footer);
        QString part2 = replyMsg.mid(278, 228); //y
        QString part2B = replyMsg.mid(532, 28); //y
        part2.prepend("0100").prepend(addressMsb).prepend(header).append(part2B).append(footer);
        QString part3 = replyMsg.mid(560, 256); //y
        part3.prepend("0200").prepend(addressMsb).prepend(header).append(footer);
        QString part4 = replyMsg.mid(816, 200); //y
        QString part4B = replyMsg.mid(1042, 56); //y
        part4.prepend("0300").prepend(addressMsb).prepend(header).append(part4B).append(footer);
        QString part5 = replyMsg.mid(1098, 256); //y
        part5.prepend("0400").prepend(addressMsb).prepend(header).append(footer);
        QString part6 = replyMsg.mid(1354, 172); //y
        QString part6B = replyMsg.mid(1552, 84); //y
        part6.prepend("0500").prepend(addressMsb).prepend(header).append(part6B).append(footer);
        QString part7 = replyMsg.mid(1636, 256); //y
        part7.prepend("0600").prepend(addressMsb).prepend(header).append(footer);
        QString part8 = replyMsg.mid(1892, 144);  //y
        QString part8B = replyMsg.mid(2072, 16); //spacer
        QString part8C = replyMsg.mid(2062, 96); //y
        part8.prepend("0700").prepend(addressMsb).prepend(header).append(part8B).append(part8C).append(footer);
        QString part9 = replyMsg.mid(2158, 256); //y
        part9.prepend("0800").prepend(addressMsb).prepend(header).append(footer);
        QString part10 = replyMsg.mid(2414,132); //y
        QString part10B = replyMsg.mid(2072, 14); //spacer added twice
        QString part10C = replyMsg.mid(2572,96); //y
        part10.prepend("0900").prepend(addressMsb).prepend(header).append(part10B).append(part10B).append(part10C).append(footer);
        QString part11 = replyMsg.mid(2668, 256); //y
        part11.prepend("0A00").prepend(addressMsb).prepend(header).append(footer);
        QString part12 = replyMsg.mid(2924, 132); //y
        QString part12B = replyMsg.mid(3082, 124);//y
        part12.prepend("0B00").prepend(addressMsb).prepend(header).append(part12B).append(footer);
        QString part13 = replyMsg.mid(3206, 256); //y
        part13.prepend("0C00").prepend(addressMsb).prepend(header).append(footer);
        QString part14 = replyMsg.mid(3462, 104); //y
        QString part14B = replyMsg.mid(3592, 152);//y
        part14.prepend("0D00").prepend(addressMsb).prepend(header).append(part14B).append(footer);
        QString part15 = replyMsg.mid(3744, 256); //y
        part15.prepend("0E00").prepend(addressMsb).prepend(header).append(footer);
        QString part16 = replyMsg.mid(4000, 48); //y
        part16.prepend("0F00").prepend(addressMsb).prepend(header).append(footer);

        replyMsg.clear();
        replyMsg.append(part1).append(part2).append(part3).append(part4).append(part5).append(part6)
                .append(part7).append(part8).append(part9).append(part10).append(part11).append(part12)
                .append(part13).append(part14).append(part15).append(part16);

        QString reBuild;       // Add correct checksum to patch strings
        QString sysxEOF;
        QString hex;
        int msgLength = replyMsg.length()/2;
        for(int i=0;i<msgLength*2;++i)
        {
            hex.append(replyMsg.mid(i*2, 2));
            sysxEOF = (replyMsg.mid((i*2)+4, 2));
            if (sysxEOF == "F7")
            {
                int dataSize = 0; bool ok;
                for(int h=checksumOffset;h<hex.size()-1;++h)
                { dataSize += hex.mid(h*2, 2).toInt(&ok, 16); };
                QString base = "80";                       // checksum calculate.
                unsigned int sum = dataSize % base.toInt(&ok, 16);
                if(sum!=0) { sum = base.toInt(&ok, 16) - sum; };
                QString checksum = QString::number(sum, 16).toUpper();
                if(checksum.length()<2) {checksum.prepend("0");};
                hex.append(checksum);
                hex.append("F7");
                reBuild.append(hex);

                hex = "";
                sysxEOF = "";
                i=i+2;
            };
        };
        replyMsg = reBuild.simplified().toUpper();
        bulk.append(replyMsg); 	                                           // add patch to the bulk string.
    ++patch;
    };

    if(patch>4) {patch=1; bank=bank+4;};	                      // increment patch.
    progress=progress+range;
    bulkStatusProgress(this->progress);                         // advance the progressbar.
    int bf = (bankFinish+1)*4 -2;
    if (bank >= bf)
    {                                                            // check if nearly finished.
        this->completedButton->show();
        this->progressLabel->setText(tr("Bulk data transfer completed!!"));
    };
    if (bank<(bankFinish+1)*4 )
    {
        bool ok;
        QString patchText;
        QString name = replyMsg.mid(22, 32);                       // get name from loaded patch.
        QList<QString> x;
        for (int b=0;b<16;b++)
        {
            x.append(name.mid(b*2, 2));
        };
        for (int b=0;b<16;b++)
        {
            QString hexStr = x.at(b);
            patchText.append( (char)(hexStr.toInt(&ok, 16)) );      // convert name to readable text characters.
        };
        
        QString patchNumber = QString::number(bank/4, 10).toUpper();
        if (patchNumber.size()<2) { patchNumber.prepend("0"); };
        patchNumber.prepend(tr("User Patch U"));
        patchNumber.append("-");
        patchNumber.append( QString::number(patch, 10).toUpper() );
        patchNumber.append("     ");
        patchNumber.append(patchText);
        patchText=patchNumber;
        this->progressLabel->setText(patchText);                        //display the patch number and name.

        patchNumber = tr("File build size = ");
        int size = (bulk.size()/2)+fullPatchSize;
        patchNumber.append(QString::number(size, 10).toUpper() );
        patchNumber.append(tr(" bytes"));
        this->bytesLabel->setText(patchNumber);                         //display the bulk data size.

        setStatusMessage(tr("Bulk Download"));
        requestPatch(bank/4, patch);                                   //request the next patch.
    } else {
        setStatusMessage(tr("Ready"));
        sysxIO->bulk = this->bulk;
        if (this->gclButton->isChecked() ) { writeGCL(); };                      // format and write bulk patches.
        if (this->syxButton->isChecked() ) { writeSYX(); };
        if (this->midButton->isChecked() ) { writeSMF(); };
    };
}

void bulkSaveDialog::bulkStatusProgress(int value)
{
    value=value/8;
    if (value >100) {value = 100;};
    if (value<0) {value = 0; };
    this->progressBar->setValue(value);
}

void bulkSaveDialog::writeGCL()         // ************************************ GCL File Format***************************
{	
    Preferences *preferences = Preferences::Instance();
    QString dir = preferences->getPreferences("General", "Files", "dir");

    QString fileName = QFileDialog::getSaveFileName(
                this,
                tr("Save Bulk Data"),
                dir,
                tr("Librarian Backup File (*.gcl)"));
    if (!fileName.isEmpty())
    {
        if(!fileName.contains(".gcl"))
        {
            fileName.append(".gcl");
        };

        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly))
        {
            bool ok;
            QByteArray out;
            int size = this->bulk.size()/2;
            int patchCount = size/patchSize;
            for (int x=0;x<size*2;x++)
            {
                QString hexStr = bulk.mid(x, 2);
                out.append( (char)(hexStr.toInt(&ok, 16)) );          // convert the bulk QString to a QByteArray.
                ++x;
            };
            QByteArray bulkFile;
            QByteArray GCL_default;
            QByteArray temp;
            QFile GCLfile(":default.gcl");           // Read the default GT-100 GCL file .
            if (GCLfile.open(QIODevice::ReadOnly))
            {	GCL_default = GCLfile.readAll(); };
            bulkFile.append(GCL_default.mid(0, 160));
            int b = 0;
            for (int x=0;x<patchCount;x++)
            {
                int a = 172;
                temp = out.mid(b+11, 128);
                GCL_default.replace(a, 128, temp);         //address "00"
                temp = out.mid(b+152, 128);
                GCL_default.replace(a+128, 128, temp);     //address "01"
                temp = out.mid(b+293, 128);
                GCL_default.replace(a+256, 128, temp);     //address "02"
                temp = out.mid(b+434, 128);
                GCL_default.replace(a+384, 128, temp);     //address "03"
                temp = out.mid(b+575, 128);
                GCL_default.replace(a+512, 128, temp);     //address "04"
                temp = out.mid(b+716, 128);
                GCL_default.replace(a+640, 128, temp);      //address "05"
                temp = out.mid(b+857, 128);
                GCL_default.replace(a+768, 128, temp);     //address "06"
                temp = out.mid(b+998, 128);
                GCL_default.replace(a+896, 128, temp);     //address "07"
                temp = out.mid(b+1139, 128);
                GCL_default.replace(a+1024, 128, temp);    //address "08"
                temp = out.mid(b+1280, 128);
                GCL_default.replace(a+1152, 128, temp);    //address "09"
                temp = out.mid(b+1421, 128);
                GCL_default.replace(a+1280, 128, temp);    //address "0A"
                temp = out.mid(b+1562, 128);
                GCL_default.replace(a+1408, 128, temp);    //address "0B"
                temp = out.mid(b+1703, 128);
                GCL_default.replace(a+1536, 128, temp);    //address "0C"
                temp = out.mid(b+1844, 128);
                GCL_default.replace(a+1664, 128, temp);    //address "0D"
                temp = out.mid(b+1985, 128);
                GCL_default.replace(a+1792, 128, temp);    //address "0E"
                temp = out.mid(b+2126, 24);
                GCL_default.replace(a+1920, 24, temp);    //address "0F"
                temp.clear();

                b=b+patchSize;
                bulkFile.append(GCL_default.mid(160, 2194));
            };
            QString hex = QString::number(patchCount, 16).toUpper();     // convert integer to QString.
            if (hex.length() < 2) hex.prepend("0");
            QByteArray count;
            count.append( (char)(hex.toInt(&ok, 16)) );
            bulkFile.replace(35, 1, count);     //   insert the correct patch count into the GCL file.
            file.write(bulkFile);
        };
    };
    DialogClose();      // close the dialog page after the file has been saved or cancelled.
}

void bulkSaveDialog::writeSYX()        //********************************* SYX File Format *****************************
{	
    Preferences *preferences = Preferences::Instance();
    QString dir = preferences->getPreferences("General", "Files", "dir");

    QString fileName = QFileDialog::getSaveFileName(
                this,
                tr("Save Bulk Data"),
                dir,
                tr("System Exclusive Backup File (*.syx)"));
    if (!fileName.isEmpty())
    {
        if(!fileName.contains(".syx"))
        {
            fileName.append(".syx");
        };

        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly))
        {
            bool ok;
            QByteArray out;
            int size = this->bulk.size()/2;
            //int patchCount = size/fullPatchSize;
            for (int x=0;x<size*2;x++)
            {
                QString hexStr = bulk.mid(x, 2);
                out.append( (char)(hexStr.toInt(&ok, 16)) );
                ++x;
            };
            file.write(out);
        };
    };
    DialogClose();
}

void bulkSaveDialog::writeSMF()    // **************************** SMF FILE FORMAT ***************************
{	
    Preferences *preferences = Preferences::Instance();
    QString dir = preferences->getPreferences("General", "Files", "dir");
    QByteArray bulkFile;
    int a = 0;
    QString fileName = QFileDialog::getSaveFileName(
                this,
                tr("Save Bulk Data"),
                dir,
                tr("Standard Midi Backup File (*.mid)"));
    if (!fileName.isEmpty())
    {
        if(!fileName.contains(".mid"))
        {
            fileName.append(".mid");
        };

        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly))
        {
            bool ok;
            QByteArray patches;
            QByteArray patch_address;
            int size = this->bulk.size()/2;
            int patchCount = size/patchSize;
            for (int x=0;x<size*2;x++)
            {
                QString hexStr = bulk.mid(x, 2);
                patches.append( (char)(hexStr.toInt(&ok, 16)) );          // convert the bulk QString to a QByteArray.
                ++x;
            };
            QByteArray temp;                        // TRANSLATION of GT-100 PATCHES, data read from syx patch **************
            QByteArray GT100_default;                        // and replace syx headers with mid data and new addresses**************
            QFile hexfile(":default.mid");   // use a QByteArray of hex numbers from a lookup table.
            if (hexfile.open(QIODevice::ReadOnly))
            { GT100_default = hexfile.readAll(); };
            QByteArray header(GT100_default.mid(0,29));
            QByteArray footer(GT100_default.mid(2351,4));
            for(int x=0; x<patchCount; ++x)
            {
                patch_address = patches.mid(a+7, 2);
                temp = patches.mid(a+11, 128);
                temp.append(patches.mid(a+152, 114));
                GT100_default.replace(43, 242, temp);         // replace SMF address "0000"#

                temp = patches.mid(a+266, 14);
                temp.append(patches.mid(a+293,128));
                temp.append(patches.mid(a+434,100));
                GT100_default.replace(301, 242, temp);        // replace SMF address "0172"#

                temp = patches.mid(a+534, 28);
                temp.append(patches.mid(a+575,128));
                temp.append(patches.mid(a+716,86));
                GT100_default.replace(559, 242, temp);        // replace SMF address "0346"#

                temp = patches.mid(a+802, 42);
                temp.append(patches.mid(a+857, 128));
                temp.append(patches.mid(a+998, 72));
                GT100_default.replace(817, 242, temp);        // replace SMF address "0542"#

                temp = patches.mid(a+1070, 56);
                temp.append(patches.mid(a+1139, 128));
                temp.append(patches.mid(a+1280, 58));
                GT100_default.replace(1075, 242, temp);       // replace SMF address "0748"#

                temp = patches.mid(a+1338, 70);
                temp.append(patches.mid(a+1421,128));
                temp.append(patches.mid(a+1562,44));
                GT100_default.replace(1333, 242, temp);       // replace SMF address "093A"#

                temp = patches.mid(a+1606,84);
                temp.append(patches.mid(a+1703,128));
                temp.append(patches.mid(a+1844,30));
                GT100_default.replace(1591, 242, temp);       // replace SMF address "0B2C"#

                temp = patches.mid(a+1874, 98);
                temp.append(patches.mid(a+1985,128));
                temp.append(patches.mid(a+2126,16));
                GT100_default.replace(1849, 242, temp);       // replace SMF address "0D1E"#

                temp = patches.mid(a+2142,8);
                GT100_default.replace(2107, 8, temp);         // replace SMF address "0F10"#

                GT100_default.replace(39, 2, patch_address); // replace patch addresses
                GT100_default.replace(297, 2, patch_address);
                GT100_default.replace(555, 2, patch_address);
                GT100_default.replace(813, 2, patch_address);
                GT100_default.replace(1071, 2, patch_address);
                GT100_default.replace(1329, 2, patch_address);
                GT100_default.replace(1587, 2, patch_address);
                GT100_default.replace(1845, 2, patch_address);
                GT100_default.replace(2103, 2, patch_address);

                GT100_default.remove(2351,4);   // remove footer
                GT100_default.remove(0,29);     // remove header
                QByteArray Q;
                Q.append((char)20);
                if(a>0) {GT100_default.replace(0, 1, Q); };

                QByteArray sysxBuffer;
                int dataSize = 0;
                int offset = 0;
                for(int i=0;i<GT100_default.size();i++)
                {
                    unsigned char byte = (char)GT100_default[i];
                    unsigned int n = (int)byte;
                    QString hex = QString::number(n, 16).toUpper();
                    if (hex.length() < 2) hex.prepend("0");
                    sysxBuffer.append(hex);

                    unsigned char nextbyte = (char)GT100_default[i+1];
                    unsigned int nextn = (int)nextbyte;
                    QString nexthex = QString::number(nextn, 16).toUpper();
                    if (nexthex.length() < 2) nexthex.prepend("0");
                    if((offset >= checksumOffset+3) && (nexthex != "F7"))   // smf offset is 8 bytes + previous byte
                    {
                        dataSize += n;
                    };
                    if(nexthex == "F7")
                    {
                        bool ok;
                        QString base = "80";
                        int sum = dataSize % base.toInt(&ok, 16);
                        if(sum!=0) {sum = base.toInt(&ok, 16) - sum; };
                        QByteArray cs;
                        cs.append((char)sum);
                        GT100_default.replace(i, 1, cs);
                    };
                    offset++;
                    if(hex == "F7")
                    {
                        sysxBuffer.clear();
                        dataSize = 0;
                        offset = 0;
                    };
                };
                a=a+patchSize;

                bulkFile.append(GT100_default);      // append the bulk file.
                GT100_default.prepend(header);
                GT100_default.append(footer);
            };
            bulkFile.prepend(header);
            bulkFile.append(footer);                // add file footer.
            size = bulkFile.size()-22;
            QByteArray fileSize;
            int xsb = size/16384;
            int msb = size/128;
            int lsb = size-((msb*128)+(xsb*16384));
            fileSize.append((char)xsb/4);
            fileSize.append((char)msb/2);
            fileSize.append((char)lsb);
            bulkFile.replace(19, 3, fileSize);     // correct filesize attributes
            file.write(bulkFile);
        };
        DialogClose();
    };
}


void bulkSaveDialog::DialogClose()
{
    bank = 100;
    SysxIO *sysxIO = SysxIO::Instance();
    QObject::disconnect(sysxIO, SIGNAL(sysxReply(QString)), this, SLOT(updatePatch(QString)));
    this->deleteLater();
    this->close();
}
