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

#include <QtWidgets>
#include <QFile>
#include <QDataStream>
#include <QByteArray>
#include <QMessageBox>
#include "bulkSaveDialog.h"
#include "Preferences.h"
#include "globalVariables.h"
#include "MidiTable.h"
#include "SysxIO.h"


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

    this->tslButton = new QRadioButton(tr("*.tsl Tone Studio file"), this );
    this->gclButton = new QRadioButton(tr("*.gcl Librarian file"), this );
    this->syxButton = new QRadioButton(tr("*.syx System Exclusive file"), this );
    this->midButton = new QRadioButton(tr("*.mid Standard Midi (SMF) file"), this );
    this->tslButton->setChecked(true);
    
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
    fileFormatLayout->addWidget(tslButton);
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
        QString part16 = replyMsg.mid(4000, 76); //y was 48
        QString part16B = replyMsg.mid(4106, 180) + footer;
        part16.prepend("0F00").prepend(addressMsb).prepend(header);
        QString part17 = replyMsg.mid(4282, 120);
        part17.prepend("1000").prepend(addressMsb).prepend(header).append(footer);


        replyMsg.clear();
        replyMsg.append(part1).append(part2).append(part3).append(part4).append(part5).append(part6)
                .append(part7).append(part8).append(part9).append(part10).append(part11).append(part12)
                .append(part13).append(part14).append(part15).append(part16).append(part16B).append(part17);

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
        if (this->tslButton->isChecked() ) { writeTSL(); };
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
                temp = out.mid(b+2126, 128);
                GCL_default.replace(a+1920, 128, temp);    //address "0F"
                temp = out.mid(b+2267, 60);
                GCL_default.replace(a+2048, 60, temp);     //address "10"
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

                temp = patches.mid(a+2142,112);
                temp.append(patches.mid(a+2267,60));
                GT100_default.replace(2107, 172, temp);         // replace SMF address "0F10"#

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

void bulkSaveDialog::writeTSL()        //********************************* TSL File Format *****************************
{
    Preferences *preferences = Preferences::Instance();
    QString dir = preferences->getPreferences("General", "Files", "dir");
    QString fileName = QFileDialog::getSaveFileName(
                this,
                tr("Save Bulk Data"),
                dir,
                tr("Tone Studio Backup File (*.tsl)"));
    if (!fileName.isEmpty())
    {
        if(!fileName.contains(".tsl"))
        {
            fileName.append(".tsl");
        };

        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly))
        {
            bool ok;
            QByteArray bulk_syx;
            int size = this->bulk.size()/2;
            int patchCount = size/(patchSize);
            for (int x=0;x<size*2;x++)
            {
                QString hexStr = bulk.mid(x, 2);
                bulk_syx.append( (char)(hexStr.toInt(&ok, 16)) );          // convert the bulk QString to a QByteArray.
                ++x;
            };
            QByteArray TSL_FILE;                       // TRANSLATION of GT-100 PATCHES, data read from syx patch **************
            QFile TSLfile(":default.tsl");           // Read the default GT-100 GCL file .
            if (TSLfile.open(QIODevice::ReadOnly))
            { TSL_FILE = TSLfile.readAll(); };
            QByteArray TSL_header(TSL_FILE.mid(0, 46));
            QByteArray TSL_footer(TSL_FILE.mid(TSL_FILE.lastIndexOf("],"), TSL_FILE.lastIndexOf("}}")+2));
            QByteArray rebuild;
            TSL_FILE.remove(0, 46);
            TSL_FILE.remove(TSL_FILE.lastIndexOf("],"), 94);
            for(int x=0; x<patchCount; ++x)
            {
                QByteArray temp(bulk_syx.mid(x*(patchSize), (patchSize)));
                TSL_default = TSL_FILE;//.mid(TSL_FILE.indexOf("[")+1, TSL_FILE.lastIndexOf("],"));
                AppendTSL(temp.mid(11, 1), "patch_name1");  //copy patch name
                AppendTSL(temp.mid(12, 1), "patch_name2");  //copy patch name
                AppendTSL(temp.mid(13, 1), "patch_name3");  //copy patch name
                AppendTSL(temp.mid(14, 1), "patch_name4");  //copy patch name
                AppendTSL(temp.mid(15, 1), "patch_name5");  //copy patch name
                AppendTSL(temp.mid(16, 1), "patch_name6");  //copy patch name
                AppendTSL(temp.mid(17, 1), "patch_name7");  //copy patch name
                AppendTSL(temp.mid(18, 1), "patch_name8");  //copy patch name
                AppendTSL(temp.mid(19, 1), "patch_name9");  //copy patch name
                AppendTSL(temp.mid(20, 1), "patch_name10"); //copy patch name
                AppendTSL(temp.mid(21, 1), "patch_name11"); //copy patch name
                AppendTSL(temp.mid(22, 1), "patch_name12"); //copy patch name
                AppendTSL(temp.mid(23, 1), "patch_name13"); //copy patch name
                AppendTSL(temp.mid(24, 1), "patch_name14"); //copy patch name
                AppendTSL(temp.mid(25, 1), "patch_name15"); //copy patch name
                AppendTSL(temp.mid(26, 1), "patch_name16"); //copy patch name
                AppendTSL(temp.mid(27, 1), "output_select");   //copy output select

                AppendTSL(temp.mid(43, 1), "comp_on_off");     //copy comp
                AppendTSL(temp.mid(44, 1), "comp_type");       //copy comp
                AppendTSL(temp.mid(45, 1), "comp_sustain");    //copy comp
                AppendTSL(temp.mid(46, 1), "comp_attack");     //copy comp
                AppendTSL(temp.mid(47, 1), "comp_tone");       //copy comp
                AppendTSL(temp.mid(48, 1), "comp_level");      //copy comp
                AppendTSL(temp.mid(59, 1), "od_ds_on_off");              //copy dist
                AppendTSL(temp.mid(60, 1), "od_ds_type");                //copy dist
                AppendTSL(temp.mid(61, 1), "od_ds_drive");               //copy dist
                AppendTSL(temp.mid(62, 1), "od_ds_bottom");              //copy dist
                AppendTSL(temp.mid(63, 1), "od_ds_tone");                //copy dist
                AppendTSL(temp.mid(64, 1), "od_ds_solo_sw");             //copy dist
                AppendTSL(temp.mid(65, 1), "od_ds_solo_level");          //copy dist
                AppendTSL(temp.mid(66, 1), "od_ds_effect_level");        //copy dist
                AppendTSL(temp.mid(67, 1), "od_ds_direct_mix");          //copy dist
                AppendTSL(temp.mid(68, 1), "od_ds_custom_type");         //copy dist
                AppendTSL(temp.mid(69, 1), "od_ds_custom_bottom");       //copy dist
                AppendTSL(temp.mid(70, 1), "od_ds_custom_top");          //copy dist
                AppendTSL(temp.mid(71, 1), "od_ds_custom_low");          //copy dist
                AppendTSL(temp.mid(72, 1), "od_ds_custom_high");         //copy dist
                AppendTSL(temp.mid(73, 1), "od_ds_custom_character");    //copy dist
                AppendTSL(temp.mid(91, 1), "preamp_a_on_off");                 //copy pre A
                AppendTSL(temp.mid(92, 1), "preamp_a_type");                   //copy pre A
                AppendTSL(temp.mid(93, 1), "preamp_a_gain");                   //copy pre A
                AppendTSL(temp.mid(94, 1), "preamp_a_t_comp");                 //copy pre A
                AppendTSL(temp.mid(95, 1), "preamp_a_bass");                   //copy pre A
                AppendTSL(temp.mid(96, 1), "preamp_a_middle");                 //copy pre A
                AppendTSL(temp.mid(97, 1), "preamp_a_treble");                 //copy pre A
                AppendTSL(temp.mid(98, 1), "preamp_a_presence");               //copy pre A
                AppendTSL(temp.mid(99, 1), "preamp_a_level");                  //copy pre A
                AppendTSL(temp.mid(100, 1), "preamp_a_bright");                //copy pre A
                AppendTSL(temp.mid(101, 1), "preamp_a_gain_sw");               //copy pre A
                AppendTSL(temp.mid(102, 1), "preamp_a_solo_sw");               //copy pre A
                AppendTSL(temp.mid(103, 1), "preamp_a_solo_level");            //copy pre A
                AppendTSL(temp.mid(104, 1), "preamp_a_sp_type");               //copy pre A
                AppendTSL(temp.mid(105, 1), "preamp_a_mic_type");              //copy pre A
                AppendTSL(temp.mid(106, 1), "preamp_a_mic_dis");               //copy pre A
                AppendTSL(temp.mid(107, 1), "preamp_a_mic_pos");               //copy pre A
                AppendTSL(temp.mid(108, 1), "preamp_a_mic_level");             //copy pre A
                AppendTSL(temp.mid(109, 1), "preamp_a_direct_mix");            //copy pre A
                AppendTSL(temp.mid(110, 1), "preamp_a_custom_type");           //copy pre A
                AppendTSL(temp.mid(111, 1), "preamp_a_custom_bottom");         //copy pre A
                AppendTSL(temp.mid(112, 1), "preamp_a_custom_edge");           //copy pre A
                AppendTSL(temp.mid(115, 1), "preamp_a_custom_preamp_low");     //copy pre A
                AppendTSL(temp.mid(116, 1), "preamp_a_custom_preamp_high");    //copy pre A
                AppendTSL(temp.mid(117, 1), "preamp_a_custom_char");           //copy pre A
                AppendTSL(temp.mid(118, 1), "preamp_a_custom_sp_size");        //copy pre A
                AppendTSL(temp.mid(119, 1), "preamp_a_custom_sp_color_low");   //copy pre A
                AppendTSL(temp.mid(120, 1), "preamp_a_custom_sp_color_high");  //copy pre A
                AppendTSL(temp.mid(121, 1), "preamp_a_custom_sp_num");         //copy pre A
                AppendTSL(temp.mid(122, 1), "preamp_a_custom_sp_cabinet");     //copy pre A
                AppendTSL(temp.mid(152, 1), "preamp_b_on_off");              //copy pre B
                AppendTSL(temp.mid(153, 1), "preamp_b_type");                //copy pre B
                AppendTSL(temp.mid(154, 1), "preamp_b_gain");                //copy pre B
                AppendTSL(temp.mid(155, 1), "preamp_b_t_comp");              //copy pre B
                AppendTSL(temp.mid(156, 1), "preamp_b_bass");                //copy pre B
                AppendTSL(temp.mid(157, 1), "preamp_b_middle");              //copy pre B
                AppendTSL(temp.mid(158, 1), "preamp_b_treble");              //copy pre B
                AppendTSL(temp.mid(159, 1), "preamp_b_presence");            //copy pre B
                AppendTSL(temp.mid(160, 1), "preamp_b_level");               //copy pre B
                AppendTSL(temp.mid(161, 1), "preamp_b_bright");              //copy pre B
                AppendTSL(temp.mid(162, 1), "preamp_b_gain_sw");             //copy pre B
                AppendTSL(temp.mid(163, 1), "preamp_b_solo_sw");             //copy pre B
                AppendTSL(temp.mid(164, 1), "preamp_b_solo_level");          //copy pre B
                AppendTSL(temp.mid(165, 1), "preamp_b_sp_type");             //copy pre B
                AppendTSL(temp.mid(166, 1), "preamp_b_mic_type");            //copy pre B
                AppendTSL(temp.mid(167, 1), "preamp_b_mic_dis");             //copy pre B
                AppendTSL(temp.mid(168, 1), "preamp_b_mic_pos");             //copy pre B
                AppendTSL(temp.mid(169, 1), "preamp_b_mic_level");           //copy pre B
                AppendTSL(temp.mid(170, 1), "preamp_b_direct_mix");          //copy pre B
                AppendTSL(temp.mid(171, 1), "preamp_b_custom_type");         //copy pre B
                AppendTSL(temp.mid(172, 1), "preamp_b_custom_bottom");       //copy pre B
                AppendTSL(temp.mid(173, 1), "preamp_b_custom_edge");         //copy pre B
                AppendTSL(temp.mid(176, 1), "preamp_b_custom_preamp_low");   //copy pre B
                AppendTSL(temp.mid(177, 1), "preamp_b_custom_preamp_high");  //copy pre B
                AppendTSL(temp.mid(178, 1), "preamp_b_custom_char");         //copy pre B
                AppendTSL(temp.mid(179, 1), "preamp_b_custom_sp_size");      //copy pre B
                AppendTSL(temp.mid(180, 1), "preamp_b_custom_sp_color_low"); //copy pre B
                AppendTSL(temp.mid(181, 1), "preamp_b_custom_sp_color_high");//copy pre B
                AppendTSL(temp.mid(182, 1), "preamp_b_custom_sp_num");       //copy pre B
                AppendTSL(temp.mid(183, 1), "preamp_b_custom_sp_cabinet");   //copy pre B
                AppendTSL(temp.mid(200, 1), "eq_on_off");                 //copy EQ
                AppendTSL(temp.mid(201, 1), "eq_low_cut");                //copy EQ
                AppendTSL(temp.mid(202, 1), "eq_low_gain");               //copy EQ
                AppendTSL(temp.mid(203, 1), "eq_low_mid_freq");           //copy EQ
                AppendTSL(temp.mid(204, 1), "eq_low_mid_q");              //copy EQ
                AppendTSL(temp.mid(205, 1), "eq_low_mid_gain");           //copy EQ
                AppendTSL(temp.mid(206, 1), "eq_high_mid_freq");          //copy EQ
                AppendTSL(temp.mid(207, 1), "eq_high_mid_q");             //copy EQ
                AppendTSL(temp.mid(208, 1), "eq_high_mid_gain");          //copy EQ
                AppendTSL(temp.mid(209, 1), "eq_high_gain");              //copy EQ
                AppendTSL(temp.mid(210, 1), "eq_high_cut");               //copy EQ
                AppendTSL(temp.mid(211, 1), "eq_level");                  //copy EQ
                AppendTSL(temp.mid(216, 1), "fx1_on_off");                  //copy FX1
                AppendTSL(temp.mid(217, 1), "fx1_fx_type");                  //copy FX1
                AppendTSL(temp.mid(218, 1), "fx1_sub_od_ds_type");                  //copy FX1
                AppendTSL(temp.mid(219, 1), "fx1_sub_od_ds_drive");                  //copy FX1
                AppendTSL(temp.mid(220, 1), "fx1_sub_od_ds_bottom");                  //copy FX1
                AppendTSL(temp.mid(221, 1), "fx1_sub_od_ds_tone");                  //copy FX1
                AppendTSL(temp.mid(222, 1), "fx1_sub_od_ds_solo_sw");                  //copy FX1
                AppendTSL(temp.mid(223, 1), "fx1_sub_od_ds_solo_level");                  //copy FX1
                AppendTSL(temp.mid(224, 1), "fx1_sub_od_ds_effect_level");                  //copy FX1
                AppendTSL(temp.mid(225, 1), "fx1_sub_od_ds_direct_mix");                  //copy FX1
                AppendTSL(temp.mid(228, 1), "fx1_t_wah_mode");                  //copy FX1
                AppendTSL(temp.mid(229, 1), "fx1_t_wah_polar");                  //copy FX1
                AppendTSL(temp.mid(230, 1), "fx1_t_wah_sens");                  //copy FX1
                AppendTSL(temp.mid(231, 1), "fx1_t_wah_freq");                  //copy FX1
                AppendTSL(temp.mid(232, 1), "fx1_t_wah_peak");                  //copy FX1
                AppendTSL(temp.mid(233, 1), "fx1_t_wah_direct_mix");                  //copy FX1
                AppendTSL(temp.mid(234, 1), "fx1_t_wah_effect_level");                  //copy FX1
                AppendTSL(temp.mid(236, 1), "fx1_auto_wah_mode");                  //copy FX1
                AppendTSL(temp.mid(237, 1), "fx1_auto_wah_freq");                  //copy FX1
                AppendTSL(temp.mid(238, 1), "fx1_auto_wah_peak");                  //copy FX1
                AppendTSL(temp.mid(239, 1), "fx1_auto_wah_rate");                  //copy FX1
                AppendTSL(temp.mid(240, 1), "fx1_auto_wah_depth");                  //copy FX1
                AppendTSL(temp.mid(241, 1), "fx1_auto_wah_direct_mix");                  //copy FX1
                AppendTSL(temp.mid(242, 1), "fx1_auto_wah_effect_level");                  //copy FX1
                AppendTSL(temp.mid(245, 1), "fx1_sub_wah_type");                  //copy FX1
                AppendTSL(temp.mid(246, 1), "fx1_sub_wah_pedal_pos");                  //copy FX1
                AppendTSL(temp.mid(247, 1), "fx1_sub_wah_pedal_min");                  //copy FX1
                AppendTSL(temp.mid(248, 1), "fx1_sub_wah_pedal_max");                  //copy FX1
                AppendTSL(temp.mid(249, 1), "fx1_sub_wah_effect_level");                  //copy FX1
                AppendTSL(temp.mid(250, 1), "fx1_sub_wah_direct_mix");                  //copy FX1
                AppendTSL(temp.mid(251, 1), "fx1_adv_comp_type");                  //copy FX1
                AppendTSL(temp.mid(252, 1), "fx1_adv_comp_sustain");                  //copy FX1
                AppendTSL(temp.mid(253, 1), "fx1_adv_comp_attack");                  //copy FX1
                AppendTSL(temp.mid(254, 1), "fx1_adv_comp_tone");                  //copy FX1
                AppendTSL(temp.mid(255, 1), "fx1_adv_comp_level");                  //copy FX1
                AppendTSL(temp.mid(257, 1), "fx1_limiter_type");                  //copy FX1
                AppendTSL(temp.mid(258, 1), "fx1_limiter_attack");                  //copy FX1
                AppendTSL(temp.mid(259, 1), "fx1_limiter_thresh");                  //copy FX1
                AppendTSL(temp.mid(260, 1), "fx1_limiter_ratio");                  //copy FX1
                AppendTSL(temp.mid(261, 1), "fx1_limiter_release");                  //copy FX1
                AppendTSL(temp.mid(262, 1), "fx1_limiter_level");                  //copy FX1
                AppendTSL(temp.mid(264, 1), "fx1_graphic_eq_31hz");                  //copy FX1
                AppendTSL(temp.mid(265, 1), "fx1_graphic_eq_62hz");                  //copy FX1
                AppendTSL(temp.mid(266, 1), "fx1_graphic_eq_125hz");                  //copy FX1
                AppendTSL(temp.mid(267, 1), "fx1_graphic_eq_250hz");                  //copy FX1
                AppendTSL(temp.mid(268, 1), "fx1_graphic_eq_500hz");                  //copy FX1
                AppendTSL(temp.mid(269, 1), "fx1_graphic_eq_1khz");                  //copy FX1
                AppendTSL(temp.mid(270, 1), "fx1_graphic_eq_2khz");                  //copy FX1
                AppendTSL(temp.mid(271, 1), "fx1_graphic_eq_4khz");                  //copy FX1
                AppendTSL(temp.mid(272, 1), "fx1_graphic_eq_8khz");                  //copy FX1
                AppendTSL(temp.mid(273, 1), "fx1_graphic_eq_16khz");                  //copy FX1
                AppendTSL(temp.mid(274, 1), "fx1_graphic_eq_level");                  //copy FX1
                AppendTSL(temp.mid(276, 1), "fx1_parametric_eq_low_cut");                  //copy FX1
                AppendTSL(temp.mid(277, 1), "fx1_parametric_eq_low_gain");                  //copy FX1
                AppendTSL(temp.mid(278, 1), "fx1_parametric_eq_low_mid_freq");                  //copy FX1
                AppendTSL(temp.mid(279, 1), "fx1_parametric_eq_low_mid_q");                  //copy FX1
                AppendTSL(temp.mid(293, 1), "fx1_parametric_eq_low_mid_gain");                  //copy FX1
                AppendTSL(temp.mid(294, 1), "fx1_parametric_eq_high_mid_freq");                  //copy FX1
                AppendTSL(temp.mid(295, 1), "fx1_parametric_eq_high_mid_q");                  //copy FX1
                AppendTSL(temp.mid(296, 1), "fx1_parametric_eq_high_mid_gain");                  //copy FX1
                AppendTSL(temp.mid(297, 1), "fx1_parametric_eq_high_gain");                  //copy FX1
                AppendTSL(temp.mid(298, 1), "fx1_parametric_eq_high_cut");                  //copy FX1
                AppendTSL(temp.mid(299, 1), "fx1_parametric_eq_level");                  //copy FX1
                AppendTSL(temp.mid(301, 1), "fx1_tone_modify_type");                  //copy FX1
                AppendTSL(temp.mid(302, 1), "fx1_tone_modify_reso");                  //copy FX1
                AppendTSL(temp.mid(303, 1), "fx1_tone_modify_low");                  //copy FX1
                AppendTSL(temp.mid(304, 1), "fx1_tone_modify_high");                  //copy FX1
                AppendTSL(temp.mid(305, 1), "fx1_tone_modify_level");                  //copy FX1
                AppendTSL(temp.mid(307, 1), "fx1_guitar_sim_type");                  //copy FX1
                AppendTSL(temp.mid(308, 1), "fx1_guitar_sim_low");                  //copy FX1
                AppendTSL(temp.mid(309, 1), "fx1_guitar_sim_high");                  //copy FX1
                AppendTSL(temp.mid(310, 1), "fx1_guitar_sim_level");                  //copy FX1
                AppendTSL(temp.mid(311, 1), "fx1_guitar_sim_body");                  //copy FX1
                AppendTSL(temp.mid(313, 1), "fx1_slow_gear_sens");                  //copy FX1
                AppendTSL(temp.mid(314, 1), "fx1_slow_gear_rise_time");                  //copy FX1
                AppendTSL(temp.mid(315, 1), "fx1_slow_gear_level");                  //copy FX1
                AppendTSL(temp.mid(317, 1), "fx1_defretter_tone");                  //copy FX1
                AppendTSL(temp.mid(318, 1), "fx1_defretter_sens");                  //copy FX1
                AppendTSL(temp.mid(319, 1), "fx1_defretter_attack");                  //copy FX1
                AppendTSL(temp.mid(320, 1), "fx1_defretter_depth");                  //copy FX1
                AppendTSL(temp.mid(321, 1), "fx1_defretter_reso");                  //copy FX1
                AppendTSL(temp.mid(322, 1), "fx1_defretter_effect_level");                  //copy FX1
                AppendTSL(temp.mid(323, 1), "fx1_defretter_direct_mix");                  //copy FX1
                AppendTSL(temp.mid(325, 1), "fx1_wave_synth_wave");                  //copy FX1
                AppendTSL(temp.mid(326, 1), "fx1_wave_synth_cutoff");                  //copy FX1
                AppendTSL(temp.mid(327, 1), "fx1_wave_synth_reso");                  //copy FX1
                AppendTSL(temp.mid(328, 1), "fx1_wave_synth_filter_sens");                  //copy FX1
                AppendTSL(temp.mid(329, 1), "fx1_wave_synth_filter_decay");                  //copy FX1
                AppendTSL(temp.mid(330, 1), "fx1_wave_synth_filter_depth");                  //copy FX1
                AppendTSL(temp.mid(331, 1), "fx1_wave_synth_synth_level");                  //copy FX1
                AppendTSL(temp.mid(332, 1), "fx1_wave_synth_direct_mix");                  //copy FX1
                AppendTSL(temp.mid(334, 1), "fx1_sitar_sim_tone");                  //copy FX1
                AppendTSL(temp.mid(335, 1), "fx1_sitar_sim_sens");                  //copy FX1
                AppendTSL(temp.mid(336, 1), "fx1_sitar_sim_depth");                  //copy FX1
                AppendTSL(temp.mid(337, 1), "fx1_sitar_sim_reso");                  //copy FX1
                AppendTSL(temp.mid(338, 1), "fx1_sitar_sim_buzz");                  //copy FX1
                AppendTSL(temp.mid(339, 1), "fx1_sitar_sim_effect_level");                  //copy FX1
                AppendTSL(temp.mid(340, 1), "fx1_sitar_sim_direct_mix");                  //copy FX1
                AppendTSL(temp.mid(342, 1), "fx1_octave_range");                  //copy FX1
                AppendTSL(temp.mid(343, 1), "fx1_octave_level");                  //copy FX1
                AppendTSL(temp.mid(344, 1), "fx1_octave_direct_mix");                  //copy FX1
                AppendTSL(temp.mid(346, 1), "fx1_pitch_shifter_voice");                  //copy FX1
                AppendTSL(temp.mid(347, 1), "fx1_pitch_shifter_ps1mode");                  //copy FX1
                AppendTSL(temp.mid(348, 1), "fx1_pitch_shifter_ps1pitch");                  //copy FX1
                AppendTSL(temp.mid(349, 1), "fx1_pitch_shifter_ps1fine");                  //copy FX1
                AppendTSL(temp.mid(350, 2), "fx1_pitch_shifter_ps1pre_dly");                  //copy FX1
                AppendTSL(temp.mid(350, 1), "fx1_pitch_shifter_ps1pre_dly_h");                  //copy FX1
                AppendTSL(temp.mid(351, 1), "fx1_pitch_shifter_ps1pre_dly_l");                  //copy FX1
                AppendTSL(temp.mid(352, 1), "fx1_pitch_shifter_ps1level");                  //copy FX1
                AppendTSL(temp.mid(353, 1), "fx1_pitch_shifter_ps2mode");                  //copy FX1
                AppendTSL(temp.mid(354, 1), "fx1_pitch_shifter_ps2pitch");                  //copy FX1
                AppendTSL(temp.mid(355, 1), "fx1_pitch_shifter_ps2fine");                  //copy FX1
                AppendTSL(temp.mid(356, 2), "fx1_pitch_shifter_ps2pre_dly");                  //copy FX1
                AppendTSL(temp.mid(356, 1), "fx1_pitch_shifter_ps2pre_dly_h");                  //copy FX1
                AppendTSL(temp.mid(357, 1), "fx1_pitch_shifter_ps2pre_dly_l");                  //copy FX1
                AppendTSL(temp.mid(358, 1), "fx1_pitch_shifter_ps2level");                  //copy FX1
                AppendTSL(temp.mid(359, 1), "fx1_pitch_shifter_ps1f_back");                  //copy FX1
                AppendTSL(temp.mid(360, 1), "fx1_pitch_shifter_direct_mix");                  //copy FX1
                AppendTSL(temp.mid(362, 1), "fx1_harmonist_voice");                  //copy FX1
                AppendTSL(temp.mid(363, 1), "fx1_harmonist_hr1harm");                  //copy FX1
                AppendTSL(temp.mid(364, 2), "fx1_harmonist_hr1pre_dly");                  //copy FX1
                AppendTSL(temp.mid(364, 1), "fx1_harmonist_hr1pre_dly_h");                  //copy FX1
                AppendTSL(temp.mid(365, 1), "fx1_harmonist_hr1pre_dly_l");                  //copy FX1
                AppendTSL(temp.mid(366, 1), "fx1_harmonist_hr1level");                  //copy FX1
                AppendTSL(temp.mid(367, 1), "fx1_harmonist_hr2harm");                  //copy FX1
                AppendTSL(temp.mid(368, 2), "fx1_harmonist_hr2pre_dly");                  //copy FX1
                AppendTSL(temp.mid(368, 1), "fx1_harmonist_hr2pre_dly_h");                  //copy FX1
                AppendTSL(temp.mid(369, 1), "fx1_harmonist_hr2pre_dly_l");                  //copy FX1
                AppendTSL(temp.mid(370, 1), "fx1_harmonist_hr2level");                  //copy FX1
                AppendTSL(temp.mid(372, 1), "fx1_harmonist_direct_mix");                  //copy FX1
                AppendTSL(temp.mid(373, 1), "fx1_harmonist_hr1c");                  //copy FX1
                AppendTSL(temp.mid(375, 1), "fx1_harmonist_hr1d");                  //copy FX1
                AppendTSL(temp.mid(274, 1), "fx1_harmonist_hr1db");                  //copy FX1
                AppendTSL(temp.mid(377, 1), "fx1_harmonist_hr1e");                  //copy FX1
                AppendTSL(temp.mid(376, 1), "fx1_harmonist_hr1eb");                  //copy FX1
                AppendTSL(temp.mid(378, 1), "fx1_harmonist_hr1f");                  //copy FX1
                AppendTSL(temp.mid(379, 1), "fx1_harmonist_hr1f_s");                  //copy FX1
                AppendTSL(temp.mid(371, 1), "fx1_harmonist_hr1f_back");                  //copy FX1
                AppendTSL(temp.mid(380, 1), "fx1_harmonist_hr1g");                  //copy FX1
                AppendTSL(temp.mid(382, 1), "fx1_harmonist_hr1a");                  //copy FX1
                AppendTSL(temp.mid(381, 1), "fx1_harmonist_hr1ab");                  //copy FX1
                AppendTSL(temp.mid(384, 1), "fx1_harmonist_hr1b");                  //copy FX1
                AppendTSL(temp.mid(383, 1), "fx1_harmonist_hr1bb");                  //copy FX1
                AppendTSL(temp.mid(385, 1), "fx1_harmonist_hr2c");                  //copy FX1
                AppendTSL(temp.mid(387, 1), "fx1_harmonist_hr2d");                  //copy FX1
                AppendTSL(temp.mid(386, 1), "fx1_harmonist_hr2db");                  //copy FX1
                AppendTSL(temp.mid(389, 1), "fx1_harmonist_hr2e");                  //copy FX1
                AppendTSL(temp.mid(388, 1), "fx1_harmonist_hr2eb");                  //copy FX1
                AppendTSL(temp.mid(390, 1), "fx1_harmonist_hr2f");                  //copy FX1
                AppendTSL(temp.mid(391, 1), "fx1_harmonist_hr2f_s");                  //copy FX1
                AppendTSL(temp.mid(392, 1), "fx1_harmonist_hr2g");                  //copy FX1
                AppendTSL(temp.mid(394, 1), "fx1_harmonist_hr2a");                  //copy FX1
                AppendTSL(temp.mid(393, 1), "fx1_harmonist_hr2ab");                  //copy FX1
                AppendTSL(temp.mid(396, 1), "fx1_harmonist_hr2b");                  //copy FX1
                AppendTSL(temp.mid(395, 1), "fx1_harmonist_hr2bb");                  //copy FX1
                AppendTSL(temp.mid(398, 1), "fx1_sound_hold_hold");                  //copy FX1
                AppendTSL(temp.mid(399, 1), "fx1_sound_hold_rise_time");                  //copy FX1
                AppendTSL(temp.mid(400, 1), "fx1_sound_hold_effect_level");                  //copy FX1
                AppendTSL(temp.mid(402, 1), "fx1_ac_processor_type");                  //copy FX1
                AppendTSL(temp.mid(403, 1), "fx1_ac_processor_bass");                  //copy FX1
                AppendTSL(temp.mid(404, 1), "fx1_ac_processor_middle");                  //copy FX1
                AppendTSL(temp.mid(405, 1), "fx1_ac_processor_middle_freq");                  //copy FX1
                AppendTSL(temp.mid(406, 1), "fx1_ac_processor_treble");                  //copy FX1
                AppendTSL(temp.mid(407, 1), "fx1_ac_processor_presence");                  //copy FX1
                AppendTSL(temp.mid(408, 1), "fx1_ac_processor_level");                  //copy FX1
                AppendTSL(temp.mid(410, 1), "fx1_phaser_type");                  //copy FX1
                AppendTSL(temp.mid(411, 1), "fx1_phaser_rate");                  //copy FX1
                AppendTSL(temp.mid(412, 1), "fx1_phaser_depth");                  //copy FX1
                AppendTSL(temp.mid(413, 1), "fx1_phaser_manual");                  //copy FX1
                AppendTSL(temp.mid(414, 1), "fx1_phaser_reso");                  //copy FX1
                AppendTSL(temp.mid(415, 1), "fx1_phaser_step_rate");                  //copy FX1
                AppendTSL(temp.mid(416, 1), "fx1_phaser_effect_level");                  //copy FX1
                AppendTSL(temp.mid(417, 1), "fx1_phaser_direct_mix");                  //copy FX1
                AppendTSL(temp.mid(419, 1), "fx1_flanger_rate");                  //copy FX1
                AppendTSL(temp.mid(420, 1), "fx1_flanger_depth");                  //copy FX1
                AppendTSL(temp.mid(434, 1), "fx1_flanger_manual");                  //copy FX1
                AppendTSL(temp.mid(435, 1), "fx1_flanger_reso");                  //copy FX1
                AppendTSL(temp.mid(436, 1), "fx1_flanger_separation");                  //copy FX1
                AppendTSL(temp.mid(437, 1), "fx1_flanger_low_cut");                  //copy FX1
                AppendTSL(temp.mid(438, 1), "fx1_flanger_effect_level");                  //copy FX1
                AppendTSL(temp.mid(439, 1), "fx1_flanger_direct_mix");                  //copy FX1
                AppendTSL(temp.mid(441, 1), "fx1_tremolo_wave_shape");                  //copy FX1
                AppendTSL(temp.mid(442, 1), "fx1_tremolo_rate");                  //copy FX1
                AppendTSL(temp.mid(443, 1), "fx1_tremolo_depth");                  //copy FX1
                AppendTSL(temp.mid(444, 1), "fx1_tremolo_level");                  //copy FX1
                AppendTSL(temp.mid(446, 1), "fx1_rotary_speed_select");                  //copy FX1
                AppendTSL(temp.mid(447, 1), "fx1_rotary_rate_slow");                  //copy FX1
                AppendTSL(temp.mid(448, 1), "fx1_rotary_rate_fast");                  //copy FX1
                AppendTSL(temp.mid(449, 1), "fx1_rotary_rise_time");                  //copy FX1
                AppendTSL(temp.mid(450, 1), "fx1_rotary_fall_time");                  //copy FX1
                AppendTSL(temp.mid(451, 1), "fx1_rotary_depth");                  //copy FX1
                AppendTSL(temp.mid(452, 1), "fx1_rotary_level");                  //copy FX1
                AppendTSL(temp.mid(454, 1), "fx1_uni_v_rate");                  //copy FX1
                AppendTSL(temp.mid(455, 1), "fx1_uni_v_depth");                  //copy FX1
                AppendTSL(temp.mid(456, 1), "fx1_uni_v_level");                  //copy FX1
                AppendTSL(temp.mid(458, 1), "fx1_pan_type");                  //copy FX1
                AppendTSL(temp.mid(459, 1), "fx1_pan_pos");                  //copy FX1
                AppendTSL(temp.mid(460, 1), "fx1_pan_wave_shape");                  //copy FX1
                AppendTSL(temp.mid(461, 1), "fx1_pan_rate");                  //copy FX1
                AppendTSL(temp.mid(462, 1), "fx1_pan_depth");                  //copy FX1
                AppendTSL(temp.mid(463, 1), "fx1_pan_level");                  //copy FX1
                AppendTSL(temp.mid(465, 1), "fx1_slicer_pattern");                  //copy FX1
                AppendTSL(temp.mid(466, 1), "fx1_slicer_rate");                  //copy FX1
                AppendTSL(temp.mid(467, 1), "fx1_slicer_trigger_sens");                  //copy FX1
                AppendTSL(temp.mid(468, 1), "fx1_slicer_effect_level");                  //copy FX1
                AppendTSL(temp.mid(469, 1), "fx1_slicer_direct_mix");                  //copy FX1
                AppendTSL(temp.mid(471, 1), "fx1_vibrato_rate");                  //copy FX1
                AppendTSL(temp.mid(472, 1), "fx1_vibrato_depth");                  //copy FX1
                AppendTSL(temp.mid(473, 1), "fx1_vibrato_trigger");                  //copy FX1
                AppendTSL(temp.mid(474, 1), "fx1_vibrato_rise_time");                  //copy FX1
                AppendTSL(temp.mid(475, 1), "fx1_vibrato_level");                  //copy FX1
                AppendTSL(temp.mid(477, 1), "fx1_ring_mod_mode");                  //copy FX1
                AppendTSL(temp.mid(478, 1), "fx1_ring_mod_freq");                  //copy FX1
                AppendTSL(temp.mid(479, 1), "fx1_ring_mod_effect_level");                  //copy FX1
                AppendTSL(temp.mid(480, 1), "fx1_ring_mod_direct_mix");                  //copy FX1
                AppendTSL(temp.mid(482, 1), "fx1_humanizer_mode");                  //copy FX1
                AppendTSL(temp.mid(483, 1), "fx1_humanizer_vowel1");                  //copy FX1
                AppendTSL(temp.mid(484, 1), "fx1_humanizer_vowel2");                  //copy FX1
                AppendTSL(temp.mid(485, 1), "fx1_humanizer_sens");                  //copy FX1
                AppendTSL(temp.mid(486, 1), "fx1_humanizer_rate");                  //copy FX1
                AppendTSL(temp.mid(487, 1), "fx1_humanizer_depth");                  //copy FX1
                AppendTSL(temp.mid(488, 1), "fx1_humanizer_manual");                  //copy FX1
                AppendTSL(temp.mid(489, 1), "fx1_humanizer_level");                  //copy FX1
                AppendTSL(temp.mid(491, 1), "fx1_2x2_chorus_xover_freq");                  //copy FX1
                AppendTSL(temp.mid(492, 1), "fx1_2x2_chorus_low_rate");                  //copy FX1
                AppendTSL(temp.mid(493, 1), "fx1_2x2_chorus_low_depth");                  //copy FX1
                AppendTSL(temp.mid(494, 1), "fx1_2x2_chorus_low_pre_delay");                  //copy FX1
                AppendTSL(temp.mid(495, 1), "fx1_2x2_chorus_low_level");                  //copy FX1
                AppendTSL(temp.mid(496, 1), "fx1_2x2_chorus_high_rate");                  //copy FX1
                AppendTSL(temp.mid(497, 1), "fx1_2x2_chorus_high_depth");                  //copy FX1
                AppendTSL(temp.mid(498, 1), "fx1_2x2_chorus_high_pre_delay");                  //copy FX1
                AppendTSL(temp.mid(499, 1), "fx1_2x2_chorus_high_level");                  //copy FX1
                AppendTSL(temp.mid(500, 1), "fx1_2x2_chorus_direct_level");                  //copy FX1
                AppendTSL(temp.mid(501, 1), "fx1_sub_delay_type");                  //copy FX1
                AppendTSL(temp.mid(502, 2), "fx1_sub_delay_time");                  //copy FX1
                AppendTSL(temp.mid(502, 1), "fx1_sub_delay_time_h");                  //copy FX1
                AppendTSL(temp.mid(503, 1), "fx1_sub_delay_time_l");                  //copy FX1
                AppendTSL(temp.mid(504, 1), "fx1_sub_delay_f_back");                  //copy FX1
                AppendTSL(temp.mid(505, 1), "fx1_sub_delay_high_cut");                  //copy FX1
                AppendTSL(temp.mid(506, 1), "fx1_sub_delay_effect_level");                  //copy FX1
                AppendTSL(temp.mid(507, 1), "fx1_sub_delay_direct_mix");                  //copy FX1
                AppendTSL(temp.mid(508, 1), "fx1_sub_delay_tap_time");                  //copy FX1
                AppendTSL(temp.mid(510, 1), "fx2_on_off");                  //copy FX2
                AppendTSL(temp.mid(511, 1), "fx2_fx_type");                  //copy FX2
                AppendTSL(temp.mid(512, 1), "fx2_sub_od_ds_type");                  //copy FX2
                AppendTSL(temp.mid(513, 1), "fx2_sub_od_ds_drive");                  //copy FX2
                AppendTSL(temp.mid(514, 1), "fx2_sub_od_ds_bottom");                  //copy FX2
                AppendTSL(temp.mid(515, 1), "fx2_sub_od_ds_tone");                  //copy FX2
                AppendTSL(temp.mid(516, 1), "fx2_sub_od_ds_solo_sw");                  //copy FX2
                AppendTSL(temp.mid(517, 1), "fx2_sub_od_ds_solo_level");                  //copy FX2
                AppendTSL(temp.mid(518, 1), "fx2_sub_od_ds_effect_level");                  //copy FX2
                AppendTSL(temp.mid(519, 1), "fx2_sub_od_ds_direct_mix");                  //copy FX2
                AppendTSL(temp.mid(522, 1), "fx2_t_wah_mode");                  //copy FX2
                AppendTSL(temp.mid(523, 1), "fx2_t_wah_polar");                  //copy FX2
                AppendTSL(temp.mid(524, 1), "fx2_t_wah_sens");                  //copy FX2
                AppendTSL(temp.mid(525, 1), "fx2_t_wah_freq");                  //copy FX2
                AppendTSL(temp.mid(526, 1), "fx2_t_wah_peak");                  //copy FX2
                AppendTSL(temp.mid(527, 1), "fx2_t_wah_direct_mix");                  //copy FX2
                AppendTSL(temp.mid(528, 1), "fx2_t_wah_effect_level");                  //copy FX2
                AppendTSL(temp.mid(530, 1), "fx2_auto_wah_mode");                  //copy FX2
                AppendTSL(temp.mid(531, 1), "fx2_auto_wah_freq");                  //copy FX2
                AppendTSL(temp.mid(532, 1), "fx2_auto_wah_peak");                  //copy FX2
                AppendTSL(temp.mid(533, 1), "fx2_auto_wah_rate");                  //copy FX2
                AppendTSL(temp.mid(534, 1), "fx2_auto_wah_depth");                  //copy FX2
                AppendTSL(temp.mid(535, 1), "fx2_auto_wah_direct_mix");                  //copy FX2
                AppendTSL(temp.mid(536, 1), "fx2_auto_wah_effect_level");                  //copy FX2
                AppendTSL(temp.mid(538, 1), "fx2_sub_wah_type");                  //copy FX2
                AppendTSL(temp.mid(539, 1), "fx2_sub_wah_pedal_pos");                  //copy FX2
                AppendTSL(temp.mid(540, 1), "fx2_sub_wah_pedal_min");                  //copy FX2
                AppendTSL(temp.mid(541, 1), "fx2_sub_wah_pedal_max");                  //copy FX2
                AppendTSL(temp.mid(542, 1), "fx2_sub_wah_effect_level");                  //copy FX2
                AppendTSL(temp.mid(543, 1), "fx2_sub_wah_direct_mix");                  //copy FX2
                AppendTSL(temp.mid(545, 1), "fx2_adv_comp_type");                  //copy FX2
                AppendTSL(temp.mid(546, 1), "fx2_adv_comp_sustain");                  //copy FX2
                AppendTSL(temp.mid(547, 1), "fx2_adv_comp_attack");                  //copy FX2
                AppendTSL(temp.mid(548, 1), "fx2_adv_comp_tone");                  //copy FX2
                AppendTSL(temp.mid(549, 1), "fx2_adv_comp_level");                  //copy FX2
                AppendTSL(temp.mid(551, 1), "fx2_limiter_type");                  //copy FX2
                AppendTSL(temp.mid(552, 1), "fx2_limiter_attack");                  //copy FX2
                AppendTSL(temp.mid(553, 1), "fx2_limiter_thresh");                  //copy FX2
                AppendTSL(temp.mid(554, 1), "fx2_limiter_ratio");                  //copy FX2
                AppendTSL(temp.mid(555, 1), "fx2_limiter_release");                  //copy FX2
                AppendTSL(temp.mid(556, 1), "fx2_limiter_level");                  //copy FX2
                AppendTSL(temp.mid(558, 1), "fx2_graphic_eq_31hz");                  //copy FX2
                AppendTSL(temp.mid(559, 1), "fx2_graphic_eq_62hz");                  //copy FX2
                AppendTSL(temp.mid(560, 1), "fx2_graphic_eq_125hz");                  //copy FX2
                AppendTSL(temp.mid(561, 1), "fx2_graphic_eq_250hz");                  //copy FX2
                AppendTSL(temp.mid(575, 1), "fx2_graphic_eq_500hz");                  //copy FX2
                AppendTSL(temp.mid(576, 1), "fx2_graphic_eq_1khz");                  //copy FX2
                AppendTSL(temp.mid(577, 1), "fx2_graphic_eq_2khz");                  //copy FX2
                AppendTSL(temp.mid(578, 1), "fx2_graphic_eq_4khz");                  //copy FX2
                AppendTSL(temp.mid(579, 1), "fx2_graphic_eq_8khz");                  //copy FX2
                AppendTSL(temp.mid(580, 1), "fx2_graphic_eq_16khz");                  //copy FX2
                AppendTSL(temp.mid(581, 1), "fx2_graphic_eq_level");                  //copy FX2
                AppendTSL(temp.mid(583, 1), "fx2_parametric_eq_low_cut");                  //copy FX2
                AppendTSL(temp.mid(584, 1), "fx2_parametric_eq_low_gain");                  //copy FX2
                AppendTSL(temp.mid(585, 1), "fx2_parametric_eq_low_mid_freq");                  //copy FX2
                AppendTSL(temp.mid(586, 1), "fx2_parametric_eq_low_mid_q");                  //copy FX2
                AppendTSL(temp.mid(587, 1), "fx2_parametric_eq_low_mid_gain");                  //copy FX2
                AppendTSL(temp.mid(588, 1), "fx2_parametric_eq_high_mid_freq");                  //copy FX2
                AppendTSL(temp.mid(589, 1), "fx2_parametric_eq_high_mid_q");                  //copy FX2
                AppendTSL(temp.mid(590, 1), "fx2_parametric_eq_high_mid_gain");                  //copy FX2
                AppendTSL(temp.mid(591, 1), "fx2_parametric_eq_high_gain");                  //copy FX2
                AppendTSL(temp.mid(592, 1), "fx2_parametric_eq_high_cut");                  //copy FX2
                AppendTSL(temp.mid(593, 1), "fx2_parametric_eq_level");                  //copy FX2
                AppendTSL(temp.mid(595, 1), "fx2_tone_modify_type");                  //copy FX2
                AppendTSL(temp.mid(596, 1), "fx2_tone_modify_reso");                  //copy FX2
                AppendTSL(temp.mid(597, 1), "fx2_tone_modify_low");                  //copy FX2
                AppendTSL(temp.mid(598, 1), "fx2_tone_modify_high");                  //copy FX2
                AppendTSL(temp.mid(599, 1), "fx2_tone_modify_level");                  //copy FX2
                AppendTSL(temp.mid(601, 1), "fx2_guitar_sim_type");                  //copy FX2
                AppendTSL(temp.mid(602, 1), "fx2_guitar_sim_low");                  //copy FX2
                AppendTSL(temp.mid(603, 1), "fx2_guitar_sim_high");                  //copy FX2
                AppendTSL(temp.mid(604, 1), "fx2_guitar_sim_level");                  //copy FX2
                AppendTSL(temp.mid(605, 1), "fx2_guitar_sim_body");                  //copy FX2
                AppendTSL(temp.mid(607, 1), "fx2_slow_gear_sens");                  //copy FX2
                AppendTSL(temp.mid(608, 1), "fx2_slow_gear_rise_time");                  //copy FX2
                AppendTSL(temp.mid(609, 1), "fx2_slow_gear_level");                  //copy FX2
                AppendTSL(temp.mid(611, 1), "fx2_defretter_tone");                  //copy FX2
                AppendTSL(temp.mid(612, 1), "fx2_defretter_sens");                  //copy FX2
                AppendTSL(temp.mid(613, 1), "fx2_defretter_attack");                  //copy FX2
                AppendTSL(temp.mid(614, 1), "fx2_defretter_depth");                  //copy FX2
                AppendTSL(temp.mid(615, 1), "fx2_defretter_reso");                  //copy FX2
                AppendTSL(temp.mid(616, 1), "fx2_defretter_effect_level");                  //copy FX2
                AppendTSL(temp.mid(617, 1), "fx2_defretter_direct_mix");                  //copy FX2
                AppendTSL(temp.mid(619, 1), "fx2_wave_synth_wave");                  //copy FX2
                AppendTSL(temp.mid(620, 1), "fx2_wave_synth_cutoff");                  //copy FX2
                AppendTSL(temp.mid(621, 1), "fx2_wave_synth_reso");                  //copy FX2
                AppendTSL(temp.mid(622, 1), "fx2_wave_synth_filter_sens");                  //copy FX2
                AppendTSL(temp.mid(623, 1), "fx2_wave_synth_filter_decay");                  //copy FX2
                AppendTSL(temp.mid(624, 1), "fx2_wave_synth_filter_depth");                  //copy FX2
                AppendTSL(temp.mid(625, 1), "fx2_wave_synth_synth_level");                  //copy FX2
                AppendTSL(temp.mid(626, 1), "fx2_wave_synth_direct_mix");                  //copy FX2
                AppendTSL(temp.mid(628, 1), "fx2_sitar_sim_tone");                  //copy FX2
                AppendTSL(temp.mid(629, 1), "fx2_sitar_sim_sens");                  //copy FX2
                AppendTSL(temp.mid(630, 1), "fx2_sitar_sim_depth");                  //copy FX2
                AppendTSL(temp.mid(631, 1), "fx2_sitar_sim_reso");                  //copy FX2
                AppendTSL(temp.mid(632, 1), "fx2_sitar_sim_buzz");                  //copy FX2
                AppendTSL(temp.mid(633, 1), "fx2_sitar_sim_effect_level");                  //copy FX2
                AppendTSL(temp.mid(634, 1), "fx2_sitar_sim_direct_mix");                  //copy FX2
                AppendTSL(temp.mid(636, 1), "fx2_octave_range");                  //copy FX2
                AppendTSL(temp.mid(637, 1), "fx2_octave_level");                  //copy FX2
                AppendTSL(temp.mid(638, 1), "fx2_octave_direct_mix");                  //copy FX2
                AppendTSL(temp.mid(640, 1), "fx2_pitch_shifter_voice");                  //copy FX2
                AppendTSL(temp.mid(641, 1), "fx2_pitch_shifter_ps1mode");                  //copy FX2
                AppendTSL(temp.mid(642, 1), "fx2_pitch_shifter_ps1pitch");                  //copy FX2
                AppendTSL(temp.mid(643, 1), "fx2_pitch_shifter_ps1fine");                  //copy FX2
                AppendTSL(temp.mid(644, 2), "fx2_pitch_shifter_ps1pre_dly");                  //copy FX2
                AppendTSL(temp.mid(644, 1), "fx2_pitch_shifter_ps1pre_dly_h");                  //copy FX2
                AppendTSL(temp.mid(645, 1), "fx2_pitch_shifter_ps1pre_dly_l");                  //copy FX2
                AppendTSL(temp.mid(646, 1), "fx2_pitch_shifter_ps1level");                  //copy FX2
                AppendTSL(temp.mid(647, 1), "fx2_pitch_shifter_ps2mode");                  //copy FX2
                AppendTSL(temp.mid(648, 1), "fx2_pitch_shifter_ps2pitch");                  //copy FX2
                AppendTSL(temp.mid(649, 1), "fx2_pitch_shifter_ps2fine");                  //copy FX2
                AppendTSL(temp.mid(650, 2), "fx2_pitch_shifter_ps2pre_dly");                  //copy FX2
                AppendTSL(temp.mid(650, 1), "fx2_pitch_shifter_ps2pre_dly_h");                  //copy FX2
                AppendTSL(temp.mid(650, 1), "fx2_pitch_shifter_ps2pre_dly_l");                  //copy FX2
                AppendTSL(temp.mid(652, 1), "fx2_pitch_shifter_ps2level");                  //copy FX2
                AppendTSL(temp.mid(653, 1), "fx2_pitch_shifter_ps1f_back");                  //copy FX2
                AppendTSL(temp.mid(654, 1), "fx2_pitch_shifter_direct_mix");                  //copy FX2
                AppendTSL(temp.mid(656, 1), "fx2_harmonist_voice");                  //copy FX2
                AppendTSL(temp.mid(657, 1), "fx2_harmonist_hr1harm");                  //copy FX2
                AppendTSL(temp.mid(658, 2), "fx2_harmonist_hr1pre_dly");                  //copy FX2
                AppendTSL(temp.mid(658, 1), "fx2_harmonist_hr1pre_dly_h");                  //copy FX2
                AppendTSL(temp.mid(659, 1), "fx2_harmonist_hr1pre_dly_l");                  //copy FX2
                AppendTSL(temp.mid(660, 1), "fx2_harmonist_hr1level");                  //copy FX2
                AppendTSL(temp.mid(661, 1), "fx2_harmonist_hr2harm");                  //copy FX2
                AppendTSL(temp.mid(662, 2), "fx2_harmonist_hr2pre_dly");                  //copy FX2
                AppendTSL(temp.mid(662, 1), "fx2_harmonist_hr2pre_dly_h");                  //copy FX2
                AppendTSL(temp.mid(662, 1), "fx2_harmonist_hr2pre_dly_l");                  //copy FX2
                AppendTSL(temp.mid(664, 1), "fx2_harmonist_hr2level");                  //copy FX2
                AppendTSL(temp.mid(665, 1), "fx2_harmonist_hr1f_back");                  //copy FX2
                AppendTSL(temp.mid(666, 1), "fx2_harmonist_direct_mix");                  //copy FX2
                AppendTSL(temp.mid(667, 1), "fx2_harmonist_hr1c");                  //copy FX2
                AppendTSL(temp.mid(668, 1), "fx2_harmonist_hr1db");                  //copy FX2
                AppendTSL(temp.mid(669, 1), "fx2_harmonist_hr1d");                  //copy FX2
                AppendTSL(temp.mid(670, 1), "fx2_harmonist_hr1eb");                  //copy FX2
                AppendTSL(temp.mid(671, 1), "fx2_harmonist_hr1e");                  //copy FX2
                AppendTSL(temp.mid(672, 1), "fx2_harmonist_hr1f");                  //copy FX2
                AppendTSL(temp.mid(673, 1), "fx2_harmonist_hr1f_s");                  //copy FX2
                AppendTSL(temp.mid(674, 1), "fx2_harmonist_hr1g");                  //copy FX2
                AppendTSL(temp.mid(675, 1), "fx2_harmonist_hr1ab");                  //copy FX2
                AppendTSL(temp.mid(676, 1), "fx2_harmonist_hr1a");                  //copy FX2
                AppendTSL(temp.mid(677, 1), "fx2_harmonist_hr1bb");                  //copy FX2
                AppendTSL(temp.mid(678, 1), "fx2_harmonist_hr1b");                  //copy FX2
                AppendTSL(temp.mid(679, 1), "fx2_harmonist_hr2c");                  //copy FX2
                AppendTSL(temp.mid(680, 1), "fx2_harmonist_hr2db");                  //copy FX2
                AppendTSL(temp.mid(681, 1), "fx2_harmonist_hr2d");                  //copy FX2
                AppendTSL(temp.mid(682, 1), "fx2_harmonist_hr2eb");                  //copy FX2
                AppendTSL(temp.mid(683, 1), "fx2_harmonist_hr2e");                  //copy FX2
                AppendTSL(temp.mid(684, 1), "fx2_harmonist_hr2f");                  //copy FX2
                AppendTSL(temp.mid(685, 1), "fx2_harmonist_hr2f_s");                  //copy FX2
                AppendTSL(temp.mid(686, 1), "fx2_harmonist_hr2g");                  //copy FX2
                AppendTSL(temp.mid(687, 1), "fx2_harmonist_hr2ab");                  //copy FX2
                AppendTSL(temp.mid(688, 1), "fx2_harmonist_hr2a");                  //copy FX2
                AppendTSL(temp.mid(689, 1), "fx2_harmonist_hr2bb");                  //copy FX2
                AppendTSL(temp.mid(690, 1), "fx2_harmonist_hr2b");                  //copy FX2
                AppendTSL(temp.mid(692, 1), "fx2_sound_hold_hold");                  //copy FX2
                AppendTSL(temp.mid(693, 1), "fx2_sound_hold_rise_time");                  //copy FX2
                AppendTSL(temp.mid(694, 1), "fx2_sound_hold_effect_level");                  //copy FX2
                AppendTSL(temp.mid(696, 1), "fx2_ac_processor_type");                  //copy FX2
                AppendTSL(temp.mid(697, 1), "fx2_ac_processor_bass");                  //copy FX2
                AppendTSL(temp.mid(698, 1), "fx2_ac_processor_middle");                  //copy FX2
                AppendTSL(temp.mid(699, 1), "fx2_ac_processor_middle_freq");                  //copy FX2
                AppendTSL(temp.mid(700, 1), "fx2_ac_processor_treble");                  //copy FX2
                AppendTSL(temp.mid(701, 1), "fx2_ac_processor_presence");                  //copy FX2
                AppendTSL(temp.mid(702, 1), "fx2_ac_processor_level");                  //copy FX2
                AppendTSL(temp.mid(716, 1), "fx2_phaser_type");                  //copy FX2
                AppendTSL(temp.mid(717, 1), "fx2_phaser_rate");                  //copy FX2
                AppendTSL(temp.mid(718, 1), "fx2_phaser_depth");                  //copy FX2
                AppendTSL(temp.mid(719, 1), "fx2_phaser_manual");                  //copy FX2
                AppendTSL(temp.mid(720, 1), "fx2_phaser_reso");                  //copy FX2
                AppendTSL(temp.mid(721, 1), "fx2_phaser_step_rate");                  //copy FX2
                AppendTSL(temp.mid(722, 1), "fx2_phaser_effect_level");                  //copy FX2
                AppendTSL(temp.mid(723, 1), "fx2_phaser_direct_mix");                  //copy FX2
                AppendTSL(temp.mid(726, 1), "fx2_flanger_rate");                  //copy FX2
                AppendTSL(temp.mid(727, 1), "fx2_flanger_depth");                  //copy FX2
                AppendTSL(temp.mid(728, 1), "fx2_flanger_manual");                  //copy FX2
                AppendTSL(temp.mid(729, 1), "fx2_flanger_reso");                  //copy FX2
                AppendTSL(temp.mid(730, 1), "fx2_flanger_separation");                  //copy FX2
                AppendTSL(temp.mid(731, 1), "fx2_flanger_low_cut");                  //copy FX2
                AppendTSL(temp.mid(732, 1), "fx2_flanger_effect_level");                  //copy FX2
                AppendTSL(temp.mid(733, 1), "fx2_flanger_direct_mix");                  //copy FX2
                AppendTSL(temp.mid(735, 1), "fx2_tremolo_wave_shape");                  //copy FX2
                AppendTSL(temp.mid(736, 1), "fx2_tremolo_rate");                  //copy FX2
                AppendTSL(temp.mid(737, 1), "fx2_tremolo_depth");                  //copy FX2
                AppendTSL(temp.mid(738, 1), "fx2_tremolo_level");                  //copy FX2
                AppendTSL(temp.mid(740, 1), "fx2_rotary_speed_select");                  //copy FX2
                AppendTSL(temp.mid(741, 1), "fx2_rotary_rate_slow");                  //copy FX2
                AppendTSL(temp.mid(742, 1), "fx2_rotary_rate_fast");                  //copy FX2
                AppendTSL(temp.mid(743, 1), "fx2_rotary_rise_time");                  //copy FX2
                AppendTSL(temp.mid(744, 1), "fx2_rotary_fall_time");                  //copy FX2
                AppendTSL(temp.mid(745, 1), "fx2_rotary_depth");                  //copy FX2
                AppendTSL(temp.mid(746, 1), "fx2_rotary_level");                  //copy FX2
                AppendTSL(temp.mid(748, 1), "fx2_uni_v_rate");                  //copy FX2
                AppendTSL(temp.mid(749, 1), "fx2_uni_v_depth");                  //copy FX2
                AppendTSL(temp.mid(750, 1), "fx2_uni_v_level");                  //copy FX2
                AppendTSL(temp.mid(752, 1), "fx2_pan_type");                  //copy FX2
                AppendTSL(temp.mid(753, 1), "fx2_pan_pos");                  //copy FX2
                AppendTSL(temp.mid(754, 1), "fx2_pan_wave_shape");                  //copy FX2
                AppendTSL(temp.mid(755, 1), "fx2_pan_rate");                  //copy FX2
                AppendTSL(temp.mid(756, 1), "fx2_pan_depth");                  //copy FX2
                AppendTSL(temp.mid(757, 1), "fx2_pan_level");                  //copy FX2
                AppendTSL(temp.mid(759, 1), "fx2_slicer_pattern");                  //copy FX2
                AppendTSL(temp.mid(760, 1), "fx2_slicer_rate");                  //copy FX2
                AppendTSL(temp.mid(761, 1), "fx2_slicer_trigger_sens");                  //copy FX2
                AppendTSL(temp.mid(762, 1), "fx2_slicer_effect_level");                  //copy FX2
                AppendTSL(temp.mid(763, 1), "fx2_slicer_direct_mix");                  //copy FX2
                AppendTSL(temp.mid(765, 1), "fx2_vibrato_rate");                  //copy FX2
                AppendTSL(temp.mid(766, 1), "fx2_vibrato_depth");                  //copy FX2
                AppendTSL(temp.mid(767, 1), "fx2_vibrato_trigger");                  //copy FX2
                AppendTSL(temp.mid(768, 1), "fx2_vibrato_rise_time");                  //copy FX2
                AppendTSL(temp.mid(769, 1), "fx2_vibrato_level");                  //copy FX2
                AppendTSL(temp.mid(771, 1), "fx2_ring_mod_mode");                  //copy FX2
                AppendTSL(temp.mid(772, 1), "fx2_ring_mod_freq");                  //copy FX2
                AppendTSL(temp.mid(773, 1), "fx2_ring_mod_effect_level");                  //copy FX2
                AppendTSL(temp.mid(774, 1), "fx2_ring_mod_direct_mix");                  //copy FX2
                AppendTSL(temp.mid(776, 1), "fx2_humanizer_mode");                  //copy FX2
                AppendTSL(temp.mid(777, 1), "fx2_humanizer_vowel1");                  //copy FX2
                AppendTSL(temp.mid(778, 1), "fx2_humanizer_vowel2");                  //copy FX2
                AppendTSL(temp.mid(779, 1), "fx2_humanizer_sens");                  //copy FX2
                AppendTSL(temp.mid(780, 1), "fx2_humanizer_rate");                  //copy FX2
                AppendTSL(temp.mid(781, 1), "fx2_humanizer_depth");                  //copy FX2
                AppendTSL(temp.mid(782, 1), "fx2_humanizer_manual");                  //copy FX2
                AppendTSL(temp.mid(783, 1), "fx2_humanizer_level");                  //copy FX2
                AppendTSL(temp.mid(785, 1), "fx2_2x2_chorus_xover_freq");                  //copy FX2
                AppendTSL(temp.mid(786, 1), "fx2_2x2_chorus_low_rate");                  //copy FX2
                AppendTSL(temp.mid(787, 1), "fx2_2x2_chorus_low_depth");                  //copy FX2
                AppendTSL(temp.mid(788, 1), "fx2_2x2_chorus_low_pre_delay");                  //copy FX2
                AppendTSL(temp.mid(789, 1), "fx2_2x2_chorus_low_level");                  //copy FX2
                AppendTSL(temp.mid(790, 1), "fx2_2x2_chorus_high_rate");                  //copy FX2
                AppendTSL(temp.mid(791, 1), "fx2_2x2_chorus_high_depth");                  //copy FX2
                AppendTSL(temp.mid(792, 1), "fx2_2x2_chorus_high_pre_delay");                  //copy FX2
                AppendTSL(temp.mid(793, 1), "fx2_2x2_chorus_high_level");                  //copy FX2
                AppendTSL(temp.mid(794, 1), "fx2_2x2_chorus_direct_level");                  //copy FX2
                AppendTSL(temp.mid(795, 1), "fx2_sub_delay_type");                  //copy FX2
                AppendTSL(temp.mid(796, 2), "fx2_sub_delay_time");                  //copy FX2
                AppendTSL(temp.mid(796, 1), "fx2_sub_delay_time_h");                  //copy FX2
                AppendTSL(temp.mid(797, 1), "fx2_sub_delay_time_l");                  //copy FX2
                AppendTSL(temp.mid(798, 1), "fx2_sub_delay_f_back");                  //copy FX2
                AppendTSL(temp.mid(799, 1), "fx2_sub_delay_high_cut");                  //copy FX2
                AppendTSL(temp.mid(800, 1), "fx2_sub_delay_effect_level");                  //copy FX2
                AppendTSL(temp.mid(801, 1), "fx2_sub_delay_direct_mix");                  //copy FX2
                AppendTSL(temp.mid(802, 1), "fx2_sub_delay_tap_time");                  //copy FX2
                AppendTSL(temp.mid(812, 1), "delay_on_off");                  //copy DD
                AppendTSL(temp.mid(813, 1), "delay_type");                  //copy DD
                AppendTSL(temp.mid(814, 2), "delay_delay_time");                  //copy DD
                AppendTSL(temp.mid(814, 1), "delay_delay_time_h");                  //copy DD
                AppendTSL(temp.mid(815, 1), "delay_delay_time_l");                  //copy DD
                AppendTSL(temp.mid(816, 1), "delay_f_back");                  //copy DD
                AppendTSL(temp.mid(817, 1), "delay_high_cut");                  //copy DD
                AppendTSL(temp.mid(818, 1), "delay_effect_level");                  //copy DD
                AppendTSL(temp.mid(819, 1), "delay_direct_mix");                  //copy DD
                AppendTSL(temp.mid(820, 1), "delay_tap_time");                  //copy DD
                AppendTSL(temp.mid(821, 2), "delay_d1_time");                  //copy DD
                AppendTSL(temp.mid(821, 1), "delay_d1_time_h");                  //copy DD
                AppendTSL(temp.mid(822, 1), "delay_d1_time_l");                  //copy DD
                AppendTSL(temp.mid(823, 1), "delay_d1_f_back");                  //copy DD
                AppendTSL(temp.mid(824, 1), "delay_d1_hi_cut");                  //copy DD
                AppendTSL(temp.mid(825, 1), "delay_d1_level");                  //copy DD
                AppendTSL(temp.mid(826, 2), "delay_d2_time");                  //copy DD
                AppendTSL(temp.mid(826, 1), "delay_d2_time_h");                  //copy DD
                AppendTSL(temp.mid(827, 1), "delay_d2_time_l");                  //copy DD
                AppendTSL(temp.mid(828, 1), "delay_d2_f_back");                  //copy DD
                AppendTSL(temp.mid(829, 1), "delay_d2_hi_cut");                  //copy DD
                AppendTSL(temp.mid(830, 1), "delay_d2_level");                  //copy DD
                AppendTSL(temp.mid(831, 1), "delay_mod_rate");                  //copy DD
                AppendTSL(temp.mid(832, 1), "delay_mod_depth");                  //copy DD
                AppendTSL(temp.mid(857, 1), "chorus_on_off");                  //copy CE
                AppendTSL(temp.mid(858, 1), "chorus_mode");                  //copy CE
                AppendTSL(temp.mid(859, 1), "chorus_rate");                  //copy CE
                AppendTSL(temp.mid(860, 1), "chorus_depth");                  //copy CE
                AppendTSL(temp.mid(861, 1), "chorus_pre_delay");                  //copy CE
                AppendTSL(temp.mid(862, 1), "chorus_low_cut");                  //copy CE
                AppendTSL(temp.mid(863, 1), "chorus_high_cut");                  //copy CE
                AppendTSL(temp.mid(864, 1), "chorus_effect_level");                  //copy CE
                AppendTSL(temp.mid(865, 1), "chorus_direct_level");                  //copy CE
                AppendTSL(temp.mid(873, 1), "reverb_on_off");                  //copy RV
                AppendTSL(temp.mid(874, 1), "reverb_type");                  //copy RV
                AppendTSL(temp.mid(875, 1), "reverb_time");                  //copy RV
                AppendTSL(temp.mid(876, 2), "reverb_pre_delay");                  //copy RV
                AppendTSL(temp.mid(876, 1), "reverb_pre_delay_h");                  //copy RV
                AppendTSL(temp.mid(877, 1), "reverb_pre_delay_l");                  //copy RV
                AppendTSL(temp.mid(878, 1), "reverb_low_cut");                  //copy RV
                AppendTSL(temp.mid(879, 1), "reverb_high_cut");                  //copy RV
                AppendTSL(temp.mid(880, 1), "reverb_density");                  //copy RV
                AppendTSL(temp.mid(881, 1), "reverb_effect_level");                  //copy RV
                AppendTSL(temp.mid(882, 1), "reverb_direct_mix");                  //copy RV
                AppendTSL(temp.mid(883, 1), "reverb_spring_sens");                  //copy RV
                AppendTSL(temp.mid(889, 1), "pedal_fx_on_off");                  //copy PedalFX
                AppendTSL(temp.mid(891, 1), "pedal_fx_pedal_bend_pitch");                  //copy PedalFX
                AppendTSL(temp.mid(892, 1), "pedal_fx_pedal_bend_position");                  //copy PedalFX
                AppendTSL(temp.mid(893, 1), "pedal_fx_pedal_bend_effect_level");                  //copy PedalFX
                AppendTSL(temp.mid(894, 1), "pedal_fx_pedal_bend_direct_mix");                  //copy PedalFX
                AppendTSL(temp.mid(895, 1), "pedal_fx_wah_type");                  //copy PedalFX
                AppendTSL(temp.mid(896, 1), "pedal_fx_wah_position");                  //copy PedalFX
                AppendTSL(temp.mid(897, 1), "pedal_fx_wah_pedal_min");                  //copy PedalFX
                AppendTSL(temp.mid(898, 1), "pedal_fx_wah_pedal_max");                  //copy PedalFX
                AppendTSL(temp.mid(899, 1), "pedal_fx_wah_effect_level");                  //copy PedalFX
                AppendTSL(temp.mid(900, 1), "pedal_fx_wah_direct_mix");                  //copy PedalFX
                AppendTSL(temp.mid(908, 1), "foot_volume_volume_curve");                  //copy FV
                AppendTSL(temp.mid(909, 1), "foot_volume_volume_min");                  //copy FV
                AppendTSL(temp.mid(910, 1), "foot_volume_volume_max");                  //copy FV
                AppendTSL(temp.mid(911, 1), "foot_volume_level");                  //copy FV
                AppendTSL(temp.mid(921, 1), "divider_mode");                  //copy Divide/Mix
                AppendTSL(temp.mid(922, 1), "divider_ch_select");                  //copy Divide/Mix
                AppendTSL(temp.mid(923, 1), "divider_ch_a_dynamic");                  //copy Divide/Mix
                AppendTSL(temp.mid(924, 1), "divider_ch_a_dynamic_sens");                  //copy Divide/Mix
                AppendTSL(temp.mid(925, 1), "divider_ch_a_filter");                  //copy Divide/Mix
                AppendTSL(temp.mid(926, 1), "divider_ch_a_cutoff_freq");                  //copy Divide/Mix
                AppendTSL(temp.mid(927, 1), "divider_ch_b_dynamic");                  //copy Divide/Mix
                AppendTSL(temp.mid(928, 1), "divider_ch_b_dynamic_sens");                  //copy Divide/Mix
                AppendTSL(temp.mid(929, 1), "divider_ch_b_filter");                  //copy Divide/Mix
                AppendTSL(temp.mid(930, 1), "divider_ch_b_cutoff_freq");                  //copy Divide/Mix
                AppendTSL(temp.mid(937, 1), "mixer_mode");                  //copy Divide/Mix
                AppendTSL(temp.mid(938, 1), "mixer_ch_a_b_balance");                  //copy Divide/Mix
                AppendTSL(temp.mid(939, 1), "mixer_spread");                  //copy Divide/Mix
                AppendTSL(temp.mid(942, 1), "send_return_on_off");                  //copy S/R
                AppendTSL(temp.mid(943, 1), "send_return_mode");                  //copy S/R
                AppendTSL(temp.mid(944, 1), "send_return_send_level");                  //copy S/R
                AppendTSL(temp.mid(945, 1), "send_return_return_level");                  //copy S/R
                AppendTSL(temp.mid(946, 1), "send_return_adjust");                  //copy S/R
                AppendTSL(temp.mid(953, 1), "amp_control");                  //copy Amp ctrl
                AppendTSL(temp.mid(956, 1), "ns1_on_off");                  //copy NS
                AppendTSL(temp.mid(957, 1), "ns1_threshold");                  //copy NS
                AppendTSL(temp.mid(958, 1), "ns1_release");                  //copy NS
                AppendTSL(temp.mid(959, 1), "ns1_detect");                  //copy NS
                AppendTSL(temp.mid(961, 1), "ns2_on_off");                  //copy NS
                AppendTSL(temp.mid(962, 1), "ns2_threshold");                  //copy NS
                AppendTSL(temp.mid(963, 1), "ns2_release");                  //copy NS
                AppendTSL(temp.mid(964, 1), "ns2_detect");                  //copy NS
                AppendTSL(temp.mid(969, 1), "accel_fx_type");                  //copy Accel
                AppendTSL(temp.mid(970, 1), "accel_fx_s_bend_pitch");                  //copy Accel
                AppendTSL(temp.mid(971, 1), "accel_fx_s_bend_rise_time");                  //copy Accel
                AppendTSL(temp.mid(972, 1), "accel_fx_s_bend_fall_time");                  //copy Accel
                AppendTSL(temp.mid(973, 1), "accel_fx_laser_beam_rate");                  //copy Accel
                AppendTSL(temp.mid(974, 1), "accel_fx_laser_beam_depth");                  //copy Accel
                AppendTSL(temp.mid(975, 1), "accel_fx_laser_beam_rise_time");                  //copy Accel
                AppendTSL(temp.mid(976, 1), "accel_fx_laser_beam_fall_time");                  //copy Accel
                AppendTSL(temp.mid(977, 1), "accel_fx_ring_mod_freq");                  //copy Accel
                AppendTSL(temp.mid(978, 1), "accel_fx_ring_mod_rise_time");                  //copy Accel
                AppendTSL(temp.mid(979, 1), "accel_fx_ring_mod_fall_time");                  //copy Accel
                AppendTSL(temp.mid(980, 1), "accel_fx_ring_mod_ring_level");                  //copy Accel
                AppendTSL(temp.mid(981, 1), "accel_fx_ring_mod_octave_level");                  //copy Accel
                AppendTSL(temp.mid(982, 1), "accel_fx_ring_mod_direct_mix");                  //copy Accel
                AppendTSL(temp.mid(983, 1), "accel_fx_twist_level");                  //copy Accel
                AppendTSL(temp.mid(984, 1), "accel_fx_twist_rise_time");                  //copy Accel
                AppendTSL(temp.mid(998, 1), "accel_fx_twist_fall_time");                  //copy Accel
                AppendTSL(temp.mid(999, 1), "accel_fx_warp_level");                  //copy Accel
                AppendTSL(temp.mid(1000, 1), "accel_fx_warp_rise_time");                  //copy Accel
                AppendTSL(temp.mid(1001, 1), "accel_fx_warp_fall_time");                  //copy Accel
                AppendTSL(temp.mid(1002, 1), "accel_fx_feedbacker_mode");                  //copy Accel
                AppendTSL(temp.mid(1003, 1), "accel_fx_feedbacker_depth");                  //copy Accel
                AppendTSL(temp.mid(1004, 1), "accel_fx_feedbacker_rise_time");                  //copy Accel
                AppendTSL(temp.mid(1005, 1), "accel_fx_feedbacker_octave_rise_time");                  //copy Accel
                AppendTSL(temp.mid(1006, 1), "accel_fx_feedbacker_f_back_level");                  //copy Accel
                AppendTSL(temp.mid(1007, 1), "accel_fx_feedbacker_octave_f_back_level");                  //copy Accel
                AppendTSL(temp.mid(1008, 1), "accel_fx_feedbacker_vib_rate");                  //copy Accel
                AppendTSL(temp.mid(1009, 1), "accel_fx_feedbacker_vib_depth");                  //copy Accel
                AppendTSL(temp.mid(1013, 1), "patch_category");               //copy Master
                AppendTSL(temp.mid(1014, 1), "patch_level");                  //copy Master
                AppendTSL(temp.mid(1015, 1), "master_eq_low_gain");           //copy Master
                AppendTSL(temp.mid(1016, 1), "master_eq_mid_freq");           //copy Master
                AppendTSL(temp.mid(1017, 1), "master_eq_mid_q");              //copy Master
                AppendTSL(temp.mid(1018, 1), "master_eq_mid_gain");           //copy Master
                AppendTSL(temp.mid(1019, 1), "master_eq_high_gain");          //copy Master
                AppendTSL(temp.mid(1020, 2), "master_bpm");                 //copy Master
                AppendTSL(temp.mid(1020, 1), "master_bpm_h");                 //copy Master
                AppendTSL(temp.mid(1021, 1), "master_bpm_l");                 //copy Master
                AppendTSL(temp.mid(1022, 1), "master_key");                   //copy Master
                AppendTSL(temp.mid(1023, 1), "master_beat");                  //copy Master
                AppendTSL(temp.mid(1024, 1), "pitch_detection");              //copy Master
                AppendTSL(temp.mid(1030, 1), "fx_chain_position1");                   //copy Chain position
                AppendTSL(temp.mid(1031, 1), "fx_chain_position2");                   //copy Chain position
                AppendTSL(temp.mid(1032, 1), "fx_chain_position3");                   //copy Chain position
                AppendTSL(temp.mid(1033, 1), "fx_chain_position4");                   //copy Chain position
                AppendTSL(temp.mid(1034, 1), "fx_chain_position5");                   //copy Chain position
                AppendTSL(temp.mid(1035, 1), "fx_chain_position6");                   //copy Chain position
                AppendTSL(temp.mid(1036, 1), "fx_chain_position7");                   //copy Chain position
                AppendTSL(temp.mid(1037, 1), "fx_chain_position8");                   //copy Chain position
                AppendTSL(temp.mid(1038, 1), "fx_chain_position9");                   //copy Chain position
                AppendTSL(temp.mid(1039, 1), "fx_chain_position10");                  //copy Chain position
                AppendTSL(temp.mid(1040, 1), "fx_chain_position11");                  //copy Chain position
                AppendTSL(temp.mid(1041, 1), "fx_chain_position12");                  //copy Chain position
                AppendTSL(temp.mid(1042, 1), "fx_chain_position13");                  //copy Chain position
                AppendTSL(temp.mid(1043, 1), "fx_chain_position14");                  //copy Chain position
                AppendTSL(temp.mid(1044, 1), "fx_chain_position15");                  //copy Chain position
                AppendTSL(temp.mid(1045, 1), "fx_chain_position16");                  //copy Chain position
                AppendTSL(temp.mid(1046, 1), "fx_chain_position17");                  //copy Chain position
                AppendTSL(temp.mid(1047, 1), "fx_chain_position18");                  //copy Chain position
                AppendTSL(temp.mid(1048, 1), "fx_chain_position19");                  //copy Chain position
                AppendTSL(temp.mid(1049, 1), "fx_chain_position20");                  //copy Chain position
                AppendTSL(temp.mid(1062, 1), "manual_mode_bank_down");                      //copy Manual Mode
                AppendTSL(temp.mid(1063, 1), "manual_mode_bank_up");                        //copy Manual Mode
                AppendTSL(temp.mid(1064, 1), "manual_mode_number_pedal1");                  //copy Manual Mode
                AppendTSL(temp.mid(1065, 1), "manual_mode_number_pedal2");                  //copy Manual Mode
                AppendTSL(temp.mid(1066, 1), "manual_mode_number_pedal3");                  //copy Manual Mode
                AppendTSL(temp.mid(1067, 1), "manual_mode_number_pedal4");                  //copy Manual Mode
                AppendTSL(temp.mid(1068, 1), "manual_mode_phrase_loop");                    //copy Manual Mode
                AppendTSL(temp.mid(1069, 1), "manual_mode_accel_ctrl");                     //copy Manual Mode
                AppendTSL(temp.mid(1078, 1), "ctl_exp_accel_ctl_func");                 //copy CTL/EXP
                AppendTSL(temp.mid(1079, 1), "ctl_exp_accel_ctl_min");                  //copy CTL/EXP
                AppendTSL(temp.mid(1080, 1), "ctl_exp_accel_ctl_max");                  //copy CTL/EXP
                AppendTSL(temp.mid(1081, 1), "ctl_exp_accel_ctl_src_mode");             //copy CTL/EXP
                AppendTSL(temp.mid(1094, 1), "ctl_exp_exp_sw_func");                    //copy CTL/EXP
                AppendTSL(temp.mid(1095, 1), "ctl_exp_exp_sw_min");                     //copy CTL/EXP
                AppendTSL(temp.mid(1096, 1), "ctl_exp_exp_sw_max");                     //copy CTL/EXP
                AppendTSL(temp.mid(1097, 1), "ctl_exp_exp_sw_src_mode");                //copy CTL/EXP
                AppendTSL(temp.mid(1110, 1), "ctl_exp_sub_ctl1_func");                  //copy CTL/EXP
                AppendTSL(temp.mid(1111, 1), "ctl_exp_sub_ctl1_min");                   //copy CTL/EXP
                AppendTSL(temp.mid(1112, 1), "ctl_exp_sub_ctl1_max");                   //copy CTL/EXP
                AppendTSL(temp.mid(1113, 1), "ctl_exp_sub_ctl1_src_mode");              //copy CTL/EXP
                AppendTSL(temp.mid(1139, 1), "ctl_exp_sub_ctl2_func");                  //copy CTL/EXP
                AppendTSL(temp.mid(1140, 1), "ctl_exp_sub_ctl2_min");                   //copy CTL/EXP
                AppendTSL(temp.mid(1141, 1), "ctl_exp_sub_ctl2_max");                   //copy CTL/EXP
                AppendTSL(temp.mid(1142, 1), "ctl_exp_sub_ctl2_src_mode");              //copy CTL/EXP
                AppendTSL(temp.mid(1155, 1), "ctl_exp_exp_func");                       //copy CTL/EXP
                AppendTSL(temp.mid(1156, 1), "ctl_exp_sub_exp_patch_level_min");        //copy CTL/EXP
                AppendTSL(temp.mid(1157, 1), "ctl_exp_sub_exp_patch_level_max");        //copy CTL/EXP
                AppendTSL(temp.mid(1171, 1), "ctl_exp_sub_exp_func");                   //copy CTL/EXP
                AppendTSL(temp.mid(1172, 1), "ctl_exp_exp_patch_level_min");            //copy CTL/EXP
                AppendTSL(temp.mid(1173, 1), "ctl_exp_exp_patch_level_max");            //copy CTL/EXP
                AppendTSL(temp.mid(1187, 1), "assign1_on_off");                  //copy Assigns
                AppendTSL(temp.mid(1188, 2), "assign1_target");                  //copy Assigns
                AppendTSL(temp.mid(1188, 1), "assign1_target_h");                //copy Assigns
                AppendTSL(temp.mid(1189, 1), "assign1_target_l");                //copy Assigns
                AppendTSL(temp.mid(1190, 2), "assign1_target_min");              //copy Assigns
                AppendTSL(temp.mid(1190, 1), "assign1_target_min_h");            //copy Assigns
                AppendTSL(temp.mid(1191, 1), "assign1_target_min_l");            //copy Assigns
                AppendTSL(temp.mid(1192, 2), "assign1_target_max");              //copy Assigns
                AppendTSL(temp.mid(1192, 1), "assign1_target_max_h");            //copy Assigns
                AppendTSL(temp.mid(1193, 1), "assign1_target_max_l");            //copy Assigns
                AppendTSL(temp.mid(1194, 1), "assign1_source");                  //copy Assigns
                AppendTSL(temp.mid(1195, 1), "assign1_source_mode");             //copy Assigns
                AppendTSL(temp.mid(1196, 1), "assign1_act_range_lo");            //copy Assigns
                AppendTSL(temp.mid(1197, 1), "assign1_act_range_hi");            //copy Assigns
                AppendTSL(temp.mid(1198, 1), "assign1_int_pdl_trigger");         //copy Assigns
                AppendTSL(temp.mid(1199, 1), "assign1_int_pdl_time");            //copy Assigns
                AppendTSL(temp.mid(1200, 1), "assign1_int_pdl_curve");           //copy Assigns
                AppendTSL(temp.mid(1201, 1), "assign1_wave_rate");               //copy Assigns
                AppendTSL(temp.mid(1202, 1), "assign1_waveform");                //copy Assigns
                AppendTSL(temp.mid(1219, 1), "assign2_on_off");                  //copy Assigns
                AppendTSL(temp.mid(1220, 2), "assign2_target");                  //copy Assigns
                AppendTSL(temp.mid(1220, 1), "assign2_target_h");                //copy Assigns
                AppendTSL(temp.mid(1221, 1), "assign2_target_l");                //copy Assigns
                AppendTSL(temp.mid(1222, 2), "assign2_target_min");              //copy Assigns
                AppendTSL(temp.mid(1222, 1), "assign2_target_min_h");            //copy Assigns
                AppendTSL(temp.mid(1223, 1), "assign2_target_min_l");            //copy Assigns
                AppendTSL(temp.mid(1224, 2), "assign2_target_max");              //copy Assigns
                AppendTSL(temp.mid(1224, 1), "assign2_target_max_h");            //copy Assigns
                AppendTSL(temp.mid(1225, 1), "assign2_target_max_l");            //copy Assigns
                AppendTSL(temp.mid(1226, 1), "assign2_source");                  //copy Assigns
                AppendTSL(temp.mid(1227, 1), "assign2_source_mode");             //copy Assigns
                AppendTSL(temp.mid(1228, 1), "assign2_act_range_lo");            //copy Assigns
                AppendTSL(temp.mid(1229, 1), "assign2_act_range_hi");            //copy Assigns
                AppendTSL(temp.mid(1230, 1), "assign2_int_pdl_trigger");         //copy Assigns
                AppendTSL(temp.mid(1231, 1), "assign2_int_pdl_time");            //copy Assigns
                AppendTSL(temp.mid(1232, 1), "assign2_int_pdl_curve");           //copy Assigns
                AppendTSL(temp.mid(1233, 1), "assign2_wave_rate");               //copy Assigns
                AppendTSL(temp.mid(1234, 1), "assign2_waveform");                //copy Assigns
                AppendTSL(temp.mid(1251, 1), "assign3_on_off");                  //copy Assigns
                AppendTSL(temp.mid(1252, 2), "assign3_target");                  //copy Assigns
                AppendTSL(temp.mid(1252, 1), "assign3_target_h");                //copy Assigns
                AppendTSL(temp.mid(1253, 1), "assign3_target_l");                //copy Assigns
                AppendTSL(temp.mid(1254, 2), "assign3_target_min");              //copy Assigns
                AppendTSL(temp.mid(1254, 1), "assign3_target_min_h");            //copy Assigns
                AppendTSL(temp.mid(1255, 1), "assign3_target_min_l");            //copy Assigns
                AppendTSL(temp.mid(1256, 2), "assign3_target_max");              //copy Assigns
                AppendTSL(temp.mid(1256, 1), "assign3_target_max_h");            //copy Assigns
                AppendTSL(temp.mid(1257, 1), "assign3_target_max_l");            //copy Assigns
                AppendTSL(temp.mid(1258, 1), "assign3_source");                  //copy Assigns
                AppendTSL(temp.mid(1259, 1), "assign3_source_mode");             //copy Assigns
                AppendTSL(temp.mid(1260, 1), "assign3_act_range_lo");            //copy Assigns
                AppendTSL(temp.mid(1261, 1), "assign3_act_range_hi");            //copy Assigns
                AppendTSL(temp.mid(1262, 1), "assign3_int_pdl_trigger");         //copy Assigns
                AppendTSL(temp.mid(1263, 1), "assign3_int_pdl_time");            //copy Assigns
                AppendTSL(temp.mid(1264, 1), "assign3_int_pdl_curve");           //copy Assigns
                AppendTSL(temp.mid(1265, 1), "assign3_wave_rate");               //copy Assigns
                AppendTSL(temp.mid(1266, 1), "assign3_waveform");                //copy Assigns
                AppendTSL(temp.mid(1296, 1), "assign4_on_off");                  //copy Assigns
                AppendTSL(temp.mid(1297, 2), "assign4_target");                  //copy Assigns
                AppendTSL(temp.mid(1297, 1), "assign4_target_h");                //copy Assigns
                AppendTSL(temp.mid(1298, 1), "assign4_target_l");                //copy Assigns
                AppendTSL(temp.mid(1299, 2), "assign4_target_min");              //copy Assigns
                AppendTSL(temp.mid(1299, 1), "assign4_target_min_h");            //copy Assigns
                AppendTSL(temp.mid(1300, 1), "assign4_target_min_l");            //copy Assigns
                AppendTSL(temp.mid(1301, 2), "assign4_target_max");              //copy Assigns
                AppendTSL(temp.mid(1301, 1), "assign4_target_max_h");            //copy Assigns
                AppendTSL(temp.mid(1302, 1), "assign4_target_max_l");            //copy Assigns
                AppendTSL(temp.mid(1303, 1), "assign4_source");                  //copy Assigns
                AppendTSL(temp.mid(1304, 1), "assign4_source_mode");             //copy Assigns
                AppendTSL(temp.mid(1305, 1), "assign4_act_range_lo");            //copy Assigns
                AppendTSL(temp.mid(1306, 1), "assign4_act_range_hi");            //copy Assigns
                AppendTSL(temp.mid(1307, 1), "assign4_int_pdl_trigger");         //copy Assigns
                AppendTSL(temp.mid(1308, 1), "assign4_int_pdl_time");            //copy Assigns
                AppendTSL(temp.mid(1309, 1), "assign4_int_pdl_curve");           //copy Assigns
                AppendTSL(temp.mid(1310, 1), "assign4_wave_rate");               //copy Assigns
                AppendTSL(temp.mid(1311, 1), "assign4_waveform");                //copy Assigns
                AppendTSL(temp.mid(1328, 1), "assign5_on_off");                  //copy Assigns
                AppendTSL(temp.mid(1329, 2), "assign5_target");                  //copy Assigns
                AppendTSL(temp.mid(1329, 1), "assign5_target_h");                //copy Assigns
                AppendTSL(temp.mid(1330, 1), "assign5_target_l");                //copy Assigns
           //     AppendTSL(temp.mid(1331, 2), "assign5_target_min");              //copy Assigns
                AppendTSL(temp.mid(1331, 1), "assign5_target_min_h");            //copy Assigns
                AppendTSL(temp.mid(1332, 1), "assign5_target_min_l");            //copy Assigns
                AppendTSL(temp.mid(1333, 2), "assign5_target_max");              //copy Assigns
                AppendTSL(temp.mid(1333, 1), "assign5_target_max_h");            //copy Assigns
                AppendTSL(temp.mid(1334, 1), "assign5_target_max_l");            //copy Assigns
                AppendTSL(temp.mid(1335, 1), "assign5_source");                  //copy Assigns
                AppendTSL(temp.mid(1336, 1), "assign5_source_mode");             //copy Assigns
                AppendTSL(temp.mid(1337, 1), "assign5_act_range_lo");            //copy Assigns
                AppendTSL(temp.mid(1338, 1), "assign5_act_range_hi");            //copy Assigns
                AppendTSL(temp.mid(1339, 1), "assign5_int_pdl_trigger");         //copy Assigns
                AppendTSL(temp.mid(1340, 1), "assign5_int_pdl_time");            //copy Assigns
                AppendTSL(temp.mid(1341, 1), "assign5_int_pdl_curve");           //copy Assigns
                AppendTSL(temp.mid(1342, 1), "assign5_wave_rate");               //copy Assigns
                AppendTSL(temp.mid(1343, 1), "assign5_waveform");                //copy Assigns
                AppendTSL(temp.mid(1360, 1), "assign6_on_off");                  //copy Assigns
                AppendTSL(temp.mid(1361, 2), "assign6_target");                  //copy Assigns
                AppendTSL(temp.mid(1361, 1), "assign6_target_h");                //copy Assigns
                AppendTSL(temp.mid(1362, 1), "assign6_target_l");                //copy Assigns
                AppendTSL(temp.mid(1363, 2), "assign6_target_min");              //copy Assigns
                AppendTSL(temp.mid(1363, 1), "assign6_target_min_h");            //copy Assigns
                AppendTSL(temp.mid(1364, 1), "assign6_target_min_l");            //copy Assigns
                AppendTSL(temp.mid(1365, 2), "assign6_target_max");              //copy Assigns
                AppendTSL(temp.mid(1365, 1), "assign6_target_max_h");            //copy Assigns
                AppendTSL(temp.mid(1366, 1), "assign6_target_max_l");            //copy Assigns
                AppendTSL(temp.mid(1367, 1), "assign6_source");                  //copy Assigns
                AppendTSL(temp.mid(1368, 1), "assign6_source_mode");             //copy Assigns
                AppendTSL(temp.mid(1369, 1), "assign6_act_range_lo");            //copy Assigns
                AppendTSL(temp.mid(1370, 1), "assign6_act_range_hi");            //copy Assigns
                AppendTSL(temp.mid(1371, 1), "assign6_int_pdl_trigger");         //copy Assigns
                AppendTSL(temp.mid(1372, 1), "assign6_int_pdl_time");            //copy Assigns
                AppendTSL(temp.mid(1373, 1), "assign6_int_pdl_curve");           //copy Assigns
                AppendTSL(temp.mid(1374, 1), "assign6_wave_rate");               //copy Assigns
                AppendTSL(temp.mid(1375, 1), "assign6_waveform");                //copy Assigns
                AppendTSL(temp.mid(1392, 1), "assign7_on_off");                  //copy Assigns
                AppendTSL(temp.mid(1393, 2), "assign7_target");                  //copy Assigns
                AppendTSL(temp.mid(1393, 1), "assign7_target_h");                //copy Assigns
                AppendTSL(temp.mid(1394, 1), "assign7_target_l");                //copy Assigns
                AppendTSL(temp.mid(1395, 2), "assign7_target_min");              //copy Assigns
                AppendTSL(temp.mid(1395, 1), "assign7_target_min_h");            //copy Assigns
                AppendTSL(temp.mid(1396, 1), "assign7_target_min_l");            //copy Assigns
                AppendTSL(temp.mid(1397, 2), "assign7_target_max");              //copy Assigns
                AppendTSL(temp.mid(1397, 1), "assign7_target_max_h");            //copy Assigns
                AppendTSL(temp.mid(1398, 1), "assign7_target_max_l");            //copy Assigns
                AppendTSL(temp.mid(1399, 1), "assign7_source");                  //copy Assigns
                AppendTSL(temp.mid(1400, 1), "assign7_source_mode");             //copy Assigns
                AppendTSL(temp.mid(1401, 1), "assign7_act_range_lo");            //copy Assigns
                AppendTSL(temp.mid(1402, 1), "assign7_act_range_hi");            //copy Assigns
                AppendTSL(temp.mid(1403, 1), "assign7_int_pdl_trigger");         //copy Assigns
                AppendTSL(temp.mid(1404, 1), "assign7_int_pdl_time");            //copy Assigns
                AppendTSL(temp.mid(1405, 1), "assign7_int_pdl_curve");           //copy Assigns
                AppendTSL(temp.mid(1406, 1), "assign7_wave_rate");               //copy Assigns
                AppendTSL(temp.mid(1407, 1), "assign7_waveform");                //copy Assigns
                AppendTSL(temp.mid(1437, 1), "assign8_on_off");                  //copy Assigns
                AppendTSL(temp.mid(1438, 2), "assign8_target");                  //copy Assigns
                AppendTSL(temp.mid(1438, 1), "assign8_target_h");                //copy Assigns
                AppendTSL(temp.mid(1439, 1), "assign8_target_l");                //copy Assigns
                AppendTSL(temp.mid(1440, 2), "assign8_target_min");              //copy Assigns
                AppendTSL(temp.mid(1440, 1), "assign8_target_min_h");            //copy Assigns
                AppendTSL(temp.mid(1441, 1), "assign8_target_min_l");            //copy Assigns
                AppendTSL(temp.mid(1442, 2), "assign8_target_max");              //copy Assigns
                AppendTSL(temp.mid(1442, 1), "assign8_target_max_h");            //copy Assigns
                AppendTSL(temp.mid(1443, 1), "assign8_target_max_l");            //copy Assigns
                AppendTSL(temp.mid(1444, 1), "assign8_source");                  //copy Assigns
                AppendTSL(temp.mid(1445, 1), "assign8_source_mode");             //copy Assigns
                AppendTSL(temp.mid(1446, 1), "assign8_act_range_lo");            //copy Assigns
                AppendTSL(temp.mid(1447, 1), "assign8_act_range_hi");            //copy Assigns
                AppendTSL(temp.mid(1448, 1), "assign8_int_pdl_trigger");         //copy Assigns
                AppendTSL(temp.mid(1449, 1), "assign8_int_pdl_time");            //copy Assigns
                AppendTSL(temp.mid(1450, 1), "assign8_int_pdl_curve");           //copy Assigns
                AppendTSL(temp.mid(1451, 1), "assign8_wave_rate");               //copy Assigns
                AppendTSL(temp.mid(1452, 1), "assign8_waveform");                //copy Assigns
                AppendTSL(temp.mid(1469, 1), "assign_common_input_sens");        //copy Assign common Input sense

                AppendTSL(temp.mid(2283, 1), "fx1_acsim_high");              //copy FX1
                AppendTSL(temp.mid(2284, 1), "fx1_acsim_body");              //copy FX1
                AppendTSL(temp.mid(2285, 1), "fx1_acsim_low");               //copy FX1
                AppendTSL(temp.mid(2287, 1), "fx1_acsim_level");             //copy FX1
                AppendTSL(temp.mid(2289, 1), "fx1_rotary2_balance");         //copy FX1
                AppendTSL(temp.mid(2290, 1), "fx1_rotary2_speed_sel");       //copy FX1
                AppendTSL(temp.mid(2291, 1), "fx1_rotary2_rate_slow");       //copy FX1
                AppendTSL(temp.mid(2292, 1), "fx1_rotary2_rate_fast");       //copy FX1
                AppendTSL(temp.mid(2293, 1), "fx1_rotary2_risetime");        //copy FX1
                AppendTSL(temp.mid(2294, 1), "fx1_rotary2_falltime");        //copy FX1
                AppendTSL(temp.mid(2295, 1), "fx1_rotary2_depth");           //copy FX1
                AppendTSL(temp.mid(2296, 1), "fx1_rotary2_level");           //copy FX1
                AppendTSL(temp.mid(2297, 1), "fx1_rotary2_direct_mix");      //copy FX1
                AppendTSL(temp.mid(2298, 1), "fx2_acsim_high");                 //copy FX2
                AppendTSL(temp.mid(2299, 1), "fx2_acsim_body");                 //copy FX2
                AppendTSL(temp.mid(2300, 1), "fx2_acsim_low");                  //copy FX2
                AppendTSL(temp.mid(2302, 1), "fx2_acsim_level");                //copy FX2
                AppendTSL(temp.mid(2304, 1), "fx2_rotary2_balance");            //copy FX2
                AppendTSL(temp.mid(2305, 1), "fx2_rotary2_speed_sel");          //copy FX2
                AppendTSL(temp.mid(2306, 1), "fx2_rotary2_rate_slow");          //copy FX2
                AppendTSL(temp.mid(2307, 1), "fx2_rotary2_rate_fast");          //copy FX2
                AppendTSL(temp.mid(2308, 1), "fx2_rotary2_risetime");           //copy FX2
                AppendTSL(temp.mid(2309, 1), "fx2_rotary2_falltime");           //copy FX2
                AppendTSL(temp.mid(2310, 1), "fx2_rotary2_depth");              //copy FX2
                AppendTSL(temp.mid(2311, 1), "fx2_rotary2_level");              //copy FX2
                AppendTSL(temp.mid(2312, 1), "fx2_rotary2_direct_mix");         //copy FX2
                AppendTSL(temp.mid(2314, 1), "prm_fx2_teraecho_mode");          //copy FX2
                AppendTSL(temp.mid(2315, 1), "prm_fx2_teraecho_time");          //copy FX2
                AppendTSL(temp.mid(2316, 1), "prm_fx2_teraecho_feedback");      //copy FX2
                AppendTSL(temp.mid(2317, 1), "prm_fx2_teraecho_tone");          //copy FX2
                AppendTSL(temp.mid(2318, 1), "prm_fx2_teraecho_effect_level");  //copy FX2
                AppendTSL(temp.mid(2319, 1), "prm_fx2_teraecho_direct_mix");    //copy FX2
                AppendTSL(temp.mid(2320, 1), "prm_fx2_teraecho_hold");          //copy FX2
                AppendTSL(temp.mid(2322, 1), "prm_fx2_overtone_detune");        //copy FX2
                AppendTSL(temp.mid(2323, 1), "prm_fx2_overtone_tone");          //copy FX2
                AppendTSL(temp.mid(2324, 1), "prm_fx2_overtone_upper_level");   //copy FX2
                AppendTSL(temp.mid(2325, 1), "prm_fx2_overtone_lower_level");   //copy FX2
                AppendTSL(temp.mid(2326, 1), "prm_fx2_overtone_direct_level");  //copy FX2

                AppendTSL(temp.mid(1030, 1), "position1");
                AppendTSL(temp.mid(1031, 1), "position2");
                AppendTSL(temp.mid(1032, 1), "position3");
                AppendTSL(temp.mid(1033, 1), "position4");
                AppendTSL(temp.mid(1034, 1), "position5");
                AppendTSL(temp.mid(1035, 1), "position6");
                AppendTSL(temp.mid(1036, 1), "position7");
                AppendTSL(temp.mid(1037, 1), "position8");
                AppendTSL(temp.mid(1038, 1), "position9");
                AppendTSL(temp.mid(1039, 1), "position10");
                AppendTSL(temp.mid(1040, 1), "position11");
                AppendTSL(temp.mid(1041, 1), "position12");
                AppendTSL(temp.mid(1042, 1), "position13");
                AppendTSL(temp.mid(1043, 1), "position14");
                AppendTSL(temp.mid(1044, 1), "position15");
                AppendTSL(temp.mid(1045, 1), "position16");
                AppendTSL(temp.mid(1046, 1), "position17");
                AppendTSL(temp.mid(1047, 1), "position18");
                AppendTSL(temp.mid(1048, 1), "position19");
                AppendTSL(temp.mid(1049, 1), "position20");

               TextTSL(temp.mid(11, 8), "gt100Name1");  //copy patch name
               TextTSL(temp.mid(19, 8), "gt100Name2");  //copy patch name
               TextTSL(temp.mid(11, 16), "patchname");  //copy patch name
               TextTSL(temp.mid(11, 16), "name");  //copy patch name

               QByteArray name("positionList");
               int start_index = TSL_default.indexOf(name)+(name.size()+3); //find pointer to start of Json value.
               QByteArray list;
               QByteArray posList;
               list.append(temp.mid(1030, 20));  // copy 20 bytes of chain data
               for(int xt=0; xt<list.size(); ++xt)
               {
                   bool ok;
                   char a = list.at(xt);
                   QString val = QString::number(a, 16).toUpper();
                   int value = val.toInt(&ok, 16);
                   QByteArray v;
                   v.setNum(value);
                   posList.append(v);
                   if(xt<list.size()-1) {posList.append(","); };

                   MidiTable *midiTable = MidiTable::Instance();
                   SysxIO *sysxIO = SysxIO::Instance();
                   QString hex = QString::number(sysxIO->getSourceValue("Structure", "07", "00", "0F"), 16).toUpper();
                   Midi items = midiTable->getMidiMap("Structure", "07", "00", "0F", "0"+hex);
                   QByteArray txt;
                   for(int x=0; x<items.desc.size(); x++ )
                   { txt.append(items.desc.at(x));   };
                   TextTSL(txt, "category");

               };
               TSL_default.replace(start_index, 49, posList);

               QByteArray note1(temp.mid(1485, 32));
               QByteArray note2(temp.mid(1562, 128).simplified());
               QByteArray note;
               if(!note1.contains("enter your name or details here")) {note.append(note1); };
               if(!note2.contains("enter your patch comment text here to describe the effects and settings used - text is saved into GT-100 patch data and files")){note.append(note2); };
               if(!note.isEmpty()) { TextTSL(note, "note"); };  //copy text notes.

               /* AppendTSL(temp.mid(27, 1), "output_select");   //copy output select
                "orderNumber"
                "patchNo":"U01-1",
                "patchID":null,
                "logPatchName":null,
                "tcPatch":false,
                "liveSetId":"5657668243",
                "category":"USER1",
                "patchCategoryName":null,
                "currentPatchNo":0,
                "prevCurrentPatchNo":0,*/
                QByteArray coma(",");
                if(x<patchCount-1) {TSL_default.append(coma); };
                rebuild.append(TSL_default);
            };
            rebuild.append(TSL_footer);
            rebuild.prepend(TSL_header);
            file.write(rebuild);
        };
        DialogClose();
    };

}

void bulkSaveDialog::AppendTSL(QByteArray hex, const char* Json_name)
{
    bool ok;
    char a = hex.at(0);
    QString val = QString::number(a, 16).toUpper();
    int value = val.toInt(&ok, 16);
    QByteArray name(Json_name);
    QByteArray spare_TSL(TSL_default); spare_TSL.truncate(spare_TSL.lastIndexOf(name)); // copy default and trim last "name" off
    QByteArray n("name");
    int start_index = TSL_default.indexOf(name)+(name.size()+2); //find pointer to start of Json value.//removed +2 from end
    if(name==n){ start_index = spare_TSL.lastIndexOf(name)+name.size()+3; };   //look for last index of "name"
    QByteArray b(":");
    unsigned int incr = 5;
LOOP:
    incr--;
    if((TSL_default.mid(start_index-1, 1).contains(b)) && (TSL_default.mid(start_index-name.size()-3, 1 ).contains((char)34)))
    {
        int end_index = TSL_default.indexOf(",", start_index)-start_index;                  //find pointer to end of value to get the size of the value.
        if(name==n) {end_index = TSL_default.indexOf("}", start_index)-start_index-2; };
        QByteArray v;
        v.setNum(value);
        TSL_default.replace(start_index, end_index, v);
        incr=0;
    }else if (incr>0) {start_index = TSL_default.indexOf(name, start_index)+(name.size()+2); goto LOOP; };
}

void bulkSaveDialog::TextTSL(QByteArray hex, const char* Json_name)
{
    QByteArray name(Json_name);   // name of function to be searched for
    QByteArray spare_TSL(TSL_default); spare_TSL.truncate(spare_TSL.lastIndexOf(name)); // copy default and trim last "name" off
    int start_index = TSL_default.indexOf(name)+name.size()+3;   //find pointer to start of Json value after :".
    if(name=="category") { start_index = TSL_default.lastIndexOf(name)+name.size()+3; };
    if(name=="name"){ start_index = spare_TSL.lastIndexOf(name)+name.size()+3; };   //look for last index of "name"
    QByteArray b(":");
    int incr = 20;
    QByteArray null("null");
LOOP2:
    incr--;
    if(TSL_default.mid(start_index-2, 1) != b)  // check if correct name is found - a ": should be after the name.
    {
        start_index = TSL_default.indexOf(name, start_index+name.size())+3;   // if not correct, move to the next name instance
    };
    if(TSL_default.mid(start_index-2, 1) == b)    // if name": is a match - find end of string field ",
    {
        int end_index = TSL_default.indexOf(",", start_index)-start_index-2; //find pointer to end of value to get the size of the value.
        if(name=="name") {end_index = TSL_default.indexOf("}", start_index)-start_index-2; };
        if(TSL_default.mid(start_index-1, 4).contains(null) && !hex.isEmpty())
        {
            TSL_default.replace(start_index-1, end_index+3, ((char)34+hex+(char)34));   //replace the old string with the new string
        } else
        {
            if(name=="category" || name=="name" || name.contains("gt100Name")) { TSL_default.replace(start_index, end_index+1, hex); } else
            { TSL_default.replace(start_index, end_index, hex); };  //replace the old string with the new string
        };
        incr=0;
    };
    if (incr>0) {goto LOOP2; };
}


void bulkSaveDialog::DialogClose()
{
    bank = 100;
    SysxIO *sysxIO = SysxIO::Instance();
    QObject::disconnect(sysxIO, SIGNAL(sysxReply(QString)), this, SLOT(updatePatch(QString)));
    this->deleteLater();
    this->close();
}
