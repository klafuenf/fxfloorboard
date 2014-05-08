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
#include <QWhatsThis>
#include "mainWindow.h"
#include "Preferences.h"
#include "preferencesDialog.h"
#include "statusBarWidget.h"
#include "SysxIO.h"
#include "bulkSaveDialog.h"
#include "bulkLoadDialog.h"
#include "summaryDialog.h"
#include "summaryDialogPatchList.h"
#include "summaryDialogSystem.h"
#include "globalVariables.h"


mainWindow::mainWindow()
{
  /*  reg = false;
    if(QFile("registare.bin").exists())
    {
        QFile file("registare.bin");
        file.open(QFile::ReadOnly);
        QString registry = QLatin1String(file.readAll());
        if(registry.contains("registered"))
        {*/
            reg = true;
        //};
    //};
    createActions();
    createMenus();

    floorBoard *fxsBoard = new floorBoard(this);
    Preferences *preferences = Preferences::Instance();
    QString setting = preferences->getPreferences("Scheme", "Style", "select");
    bool ok;
    int choice = setting.toInt(&ok, 16);
    QString style;
    if(choice == 3) {style = "motif"; }
    else if(choice == 2) {style = "cde"; }
    else if(choice == 1) {style = "plastique"; }
    else style = "";

    setting = preferences->getPreferences("Scheme", "Colour", "select");
    choice = setting.toInt(&ok, 16);
    QString colour;
    if(choice == 4) {colour = ":qss/system.qss"; }
    else if(choice == 3) {colour = ":qss/green.qss"; }
    else if(choice == 2) {colour = ":qss/blue.qss"; }
    else if(choice == 1) {colour = ":qss/white.qss"; }
    else colour = ":qss/black.qss";
    /* Loads the stylesheet for the current platform if present */
    QApplication::setStyle(QStyleFactory::create(style));
    if(QFile(colour).exists())
    {
        QFile file(colour);
        file.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(file.readAll());
        fxsBoard->setStyleSheet(styleSheet);
    };
    setWindowTitle(deviceType + tr(" Fx FloorBoard"));
    createStatusBar();
    setCentralWidget(fxsBoard);
    statusBar()->setWhatsThis("StatusBar<br>midi activity is displayed here<br>and some status messages are displayed.");

    QObject::connect(fxsBoard, SIGNAL( sizeChanged(QSize, QSize) ),
                     this, SLOT( updateSize(QSize, QSize) ) );
                     
    int count = (preferences->getPreferences("General", "Start", "count").toInt(&ok, 10));
    if(count == 0 && preferences->getPreferences("General", "Donate", "url")!="true")
    { donate(); };
    count++;
    if(count >= 8) {count = 0; };
    QString index = QString::number(count, 10).toUpper();
    preferences->setPreferences("General", "Start", "count", index);
}

mainWindow::~mainWindow()
{
    Preferences *preferences = Preferences::Instance();
    if(preferences->getPreferences("Window", "Restore", "window")=="true")
    {
        QString posx, width;
        if(preferences->getPreferences("Window", "Restore", "sidepanel")=="true" &&
                preferences->getPreferences("Window", "Collapsed", "bool")=="true")
        {
            width = QString::number(this->geometry().width(), 10);
            posx = QString::number(this->geometry().x()-8, 10);
        }
        else
        {
            bool ok;
            width = preferences->getPreferences("Window", "Size", "minwidth");
            posx = QString::number(this->geometry().x()+((this->geometry().width()-width.toInt(&ok,10))/2), 10);
        };
        preferences->setPreferences("Window", "Position", "x", posx);
        preferences->setPreferences("Window", "Position", "y", QString::number(this->geometry().y()-30, 10));
        preferences->setPreferences("Window", "Size", "width", width);
        preferences->setPreferences("Window", "Size", "height", QString::number(this->geometry().height(), 10));
    }
    else
    {
        preferences->setPreferences("Window", "Position", "x", "");
        preferences->setPreferences("Window", "Position", "y", "");
        preferences->setPreferences("Window", "Size", "width", "");
        preferences->setPreferences("Window", "Size", "height", "");
    };
    preferences->savePreferences();
}

void mainWindow::updateSize(QSize floorSize, QSize oldFloorSize)
{
    this->setFixedWidth(floorSize.width());
    int x = this->geometry().x() - ((floorSize.width() - oldFloorSize.width()) / 2);
    int y = this->geometry().y();
    this->setGeometry(x, y, floorSize.width(), this->geometry().height());
}

void mainWindow::createActions()
{
    openAct = new QAction(QIcon(":/images/fileopen.png"), tr("&Load Patch File... (*.syx, *.mid, *.gcl *.gxg *.gxb)"), this);
    openAct->setShortcut(tr("Ctrl+O"));
    openAct->setStatusTip(tr("Open an existing file, any GT-100, GT-10, GT-8, GT-10B, GT-6B patch file"));
    openAct->setWhatsThis(tr("Open an existing file, any GT-100, GT-10, GT-8, GT-10B, GT-6B patch file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(QIcon(":/images/filesave.png"), tr("&Save currently open Patch file...       (*.gcl *.mid *.syx)"), this);
    saveAct->setShortcut(tr("Ctrl+S"));
    saveAct->setStatusTip(tr("Save the current patch to the last opened file to disk"));
    saveAct->setWhatsThis(tr("Save the current patch to the last opened file to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    saveGCLAct = new QAction(QIcon(":/images/filesave.png"), tr("Save As Librarian compatable GCL Patch... (*.gcl)"), this);
    saveGCLAct->setShortcut(tr("Ctrl+Shift+G"));
    saveGCLAct->setStatusTip(tr("Save to disk as a Boss Librarian File"));
    saveGCLAct->setWhatsThis(tr("Save to disk as a Boss Librarian File"));
    connect(saveGCLAct, SIGNAL(triggered()), this, SLOT(saveGCL()));

    saveAsAct = new QAction(QIcon(":/images/filesave.png"), tr("Export System Exclusive Patch...  (*.syx)"), this);
    saveAsAct->setShortcut(tr("Ctrl+Shift+S"));
    saveAsAct->setStatusTip(tr("Export as a System Exclusive File"));
    saveAsAct->setWhatsThis(tr("Export as a System Exclusive File"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    exportSMFAct = new QAction(QIcon(":/images/filesave.png"), tr("Export Standard Midi Format Patch... (*.mid)"), this);
    exportSMFAct->setShortcut(tr("Ctrl+Shift+E"));
    exportSMFAct->setStatusTip(tr("Export as a Standard Midi File"));
    exportSMFAct->setWhatsThis(tr("Export as a Standard Midi File"));
    connect(exportSMFAct, SIGNAL(triggered()), this, SLOT(exportSMF()));

    systemLoadAct = new QAction(QIcon(":/images/fileopen.png"), tr("&Load System and Global Data..."), this);
    systemLoadAct->setShortcut(tr("Ctrl+L"));
    systemLoadAct->setStatusTip(tr("Load System Data to GT-100"));
    systemLoadAct->setWhatsThis(tr("Load System Data to GT-100"));
    connect(systemLoadAct, SIGNAL(triggered()), this, SLOT(systemLoad()));

    systemSaveAct = new QAction(QIcon(":/images/filesave.png"), tr("Save System and Global Data to File..."), this);
    systemSaveAct->setShortcut(tr("Ctrl+D"));
    systemSaveAct->setStatusTip(tr("Save System Data to File"));
    systemSaveAct->setWhatsThis(tr("Save System Data to File"));
    connect(systemSaveAct, SIGNAL(triggered()), this, SLOT(systemSave()));

    bulkLoadAct = new QAction(QIcon(":/images/fileopen.png"), tr("&Load Bulk Patch File to GT-100..."), this);
    bulkLoadAct->setShortcut(tr("Ctrl+B"));
    bulkLoadAct->setStatusTip(tr("Load Bulk Data to GT-100"));
    bulkLoadAct->setWhatsThis(tr("Load Bulk Data to GT-100"));
    connect(bulkLoadAct, SIGNAL(triggered()), this, SLOT(bulkLoad()));

    bulkSaveAct = new QAction(QIcon(":/images/filesave.png"), tr("Save Bulk GT-100 Patches to File..."), this);
    bulkSaveAct->setShortcut(tr("Ctrl+G"));
    bulkSaveAct->setStatusTip(tr("Save Bulk Data to File"));
    bulkSaveAct->setWhatsThis(tr("Save Bulk Data to File"));
    connect(bulkSaveAct, SIGNAL(triggered()), this, SLOT(bulkSave()));

    exitAct = new QAction(QIcon(":/images/exit.png"),tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    exitAct->setStatusTip(tr("Exit the application"));
    exitAct->setWhatsThis(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    settingsAct = new QAction(QIcon(":/images/preferences.png"), tr("&Preferences"), this);
    settingsAct->setShortcut(tr("Ctrl+P"));
    settingsAct->setStatusTip(tr("FxFloorBoard Preferences\n Select midi device, language,splash, directories"));
    settingsAct->setWhatsThis(tr("FxFloorBoard Preferences\n Select midi device, language,splash, directories"));
    connect(settingsAct, SIGNAL(triggered()), this, SLOT(settings()));

    uploadAct = new QAction(QIcon(":/images/upload.png"), tr("Upload patch to GT-Central"), this);
    uploadAct->setStatusTip(tr("Upload any saved patch file to a shared patch library\n via the internet."));
    uploadAct->setWhatsThis(tr("Upload any saved patch file to a shared patch library\n via the internet."));
    connect(uploadAct, SIGNAL(triggered()), this, SLOT(upload()));

    summaryAct = new QAction(QIcon(":/images/copy.png"), tr("Patch Text Summary"), this);
    summaryAct->setStatusTip(tr("Display the current patch parameters\n in a readable text format, which\n can be printed or saved to file."));
    summaryAct->setWhatsThis(tr("Display the current patch parameters\n in a readable text format, which\n can be printed or saved to file."));
    connect(summaryAct, SIGNAL(triggered()), this, SLOT(summaryPage()));

    summarySystemAct = new QAction(QIcon(":/images/copy.png"), tr("System/Global Text Summary"), this);
    summarySystemAct->setStatusTip(tr("Display the current System and Global parameters\n in a readable text format, which\n can be printed or saved to file."));
    summarySystemAct->setWhatsThis(tr("Display the current System and Global parameters\n in a readable text format, which\n can be printed or saved to file."));
    connect(summarySystemAct, SIGNAL(triggered()), this, SLOT(summarySystemPage()));

    summaryPatchListAct = new QAction(QIcon(":/images/copy.png"), tr("GT-100 Patch List Summary"), this);
    summaryPatchListAct->setStatusTip(tr("Display the GT-100 patch listing names\n in a readable text format, which\n can be printed or saved to file."));
    summaryPatchListAct->setWhatsThis(tr("Display the GT-100 patch listing names\n in a readable text format, which\n can be printed or saved to file."));
    connect(summaryPatchListAct, SIGNAL(triggered()), this, SLOT(summaryPatchList()));

    helpAct = new QAction(QIcon(":/images/help.png"), tr("GT-100 Fx FloorBoard &Help"), this);
    helpAct->setShortcut(tr("Ctrl+F1"));
    helpAct->setStatusTip(tr("Help page to assist with FxFloorBoard functions."));
    helpAct->setWhatsThis(tr("Help page to assist with FxFloorBoard functions."));
    connect(helpAct, SIGNAL(triggered()), this, SLOT(help()));

    whatsThisAct = new QAction(QIcon(":/images/help.png"), tr("Whats This? description of items under the mouse cursor"), this);
    whatsThisAct->setShortcut(tr("F1"));
    whatsThisAct->setStatusTip(tr("ha..ha..ha..!!"));
    whatsThisAct->setWhatsThis(tr("ha..ha..ha..!!"));
    connect(whatsThisAct, SIGNAL(triggered()), this, SLOT(whatsThis()));

    homepageAct = new QAction(QIcon(":/images/GT-100FxFloorBoard.png"), tr("GT-100 Fx FloorBoard &Webpage"), this);
    homepageAct->setStatusTip(tr("download Webpage for FxFloorBoard\n find if the latest version is available."));
    homepageAct->setWhatsThis(tr("download Webpage for FxFloorBoard\n find if the latest version is available."));
    connect(homepageAct, SIGNAL(triggered()), this, SLOT(homepage()));

    donationAct = new QAction(QIcon(":/images/donate.png"), tr("Donate if you appreciate this software"), this);
    donationAct->setStatusTip(tr("Even though the software is free,\n an occassional donation is very much appreciated\n as i am not paid for this work."));
    donationAct->setWhatsThis(tr("Even though the software is free,\n an occassional donation is very much appreciated\n as i am not paid for this work."));
    connect(donationAct, SIGNAL(triggered()), this, SLOT(donate()));

    manualAct = new QAction(QIcon(":/images/manual.png"), tr("GT-100 Manuals and Drivers"), this);
    manualAct->setStatusTip(tr("........"));
    manualAct->setWhatsThis(tr("........"));
    connect(manualAct, SIGNAL(triggered()), this, SLOT(manual()));

    licenseAct = new QAction(QIcon(":/images/licence.png"), tr("&License"), this);
    licenseAct->setStatusTip(tr("licence agreement which you\n have accepted by installing this software."));
    licenseAct->setWhatsThis(tr("licence agreement which you\n have accepted by installing this software."));
    connect(licenseAct, SIGNAL(triggered()), this, SLOT(license()));

    aboutAct = new QAction(QIcon(":/images/GT-100FxFloorBoard.png"), tr("&About FxFloorBoard"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    aboutAct->setWhatsThis(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(QIcon(":/images/qt-logo.png"),tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    aboutQtAct->setWhatsThis(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void mainWindow::createMenus()
{
    //menuBar = new QMenuBar();
    fileMenu = menuBar()->addMenu(tr("&File"));
    //QMenu *fileMenu = new QMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveGCLAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addAction(exportSMFAct);
    fileMenu->addSeparator();
    fileMenu->addAction(bulkLoadAct);
    fileMenu->addAction(bulkSaveAct);
    fileMenu->addSeparator();
    fileMenu->addAction(systemLoadAct);
    fileMenu->addAction(systemSaveAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);
    fileMenu->setWhatsThis(tr("File Saving and Loading,<br> and application Exit."));

    toolsMenu = menuBar()->addMenu(tr("&Tools"));
    toolsMenu->addAction(uploadAct);
    fileMenu->addSeparator();
    toolsMenu->addAction(summaryAct);
    toolsMenu->addAction(summarySystemAct);
    toolsMenu->addAction(summaryPatchListAct);
    
    settingsMenu = menuBar()->addMenu(tr("&Settings"));
    settingsMenu->addAction(settingsAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(helpAct);
    helpMenu->addAction(whatsThisAct);
    helpMenu->addAction(homepageAct);
    helpMenu->addSeparator();
    helpMenu->addAction(donationAct);
    helpMenu->addSeparator();
    helpMenu->addAction(manualAct);
    helpMenu->addAction(licenseAct);
    helpMenu->addSeparator();
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void mainWindow::createStatusBar()
{
    SysxIO *sysxIO = SysxIO::Instance();

    statusBarWidget *statusInfo = new statusBarWidget(this);
    statusInfo->setStatusSymbol(0);
    statusInfo->setStatusMessage(tr("Not connected"));

    QObject::connect(sysxIO, SIGNAL(setStatusSymbol(int)), statusInfo, SLOT(setStatusSymbol(int)));
    QObject::connect(sysxIO, SIGNAL(setStatusProgress(int)), statusInfo, SLOT(setStatusProgress(int)));
    QObject::connect(sysxIO, SIGNAL(setStatusMessage(QString)), statusInfo, SLOT(setStatusMessage(QString)));
    QObject::connect(sysxIO, SIGNAL(setStatusdBugMessage(QString)), statusInfo, SLOT(setStatusdBugMessage(QString)));

    //statusBar = new QStatusBar;
    statusBar()->addWidget(statusInfo);
    statusBar()->setSizeGripEnabled(false);
}

/* FILE MENU */
void mainWindow::open()
{
    Preferences *preferences = Preferences::Instance();
    QString dir = preferences->getPreferences("General", "Files", "dir");

    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Choose a file"),
                dir,
                tr("for GT-100, 10, 8, 10B, 6B (*.syx *.mid *.gcl *.gxg *.gxb)"));
    if (!fileName.isEmpty())
    {
        file.setFile(fileName);
        if(file.readFile())
        {
            // DO SOMETHING AFTER READING THE FILE (UPDATE THE GUI)
            SysxIO *sysxIO = SysxIO::Instance();
            QString area = "Structure";
            sysxIO->setFileSource(area, file.getFileSource());
            sysxIO->setFileName(fileName);
            sysxIO->setSyncStatus(false);
            sysxIO->setDevice(false);
            emit updateSignal();
            if(sysxIO->isConnected())
            {sysxIO->writeToBuffer();};
        };
    };
}

void mainWindow::save()
{
    if(reg == true)
    {
        Preferences *preferences = Preferences::Instance();
        QString dir = preferences->getPreferences("General", "Files", "dir");

        SysxIO *sysxIO = SysxIO::Instance();
        file.setFile(sysxIO->getFileName());

        if(file.getFileName().isEmpty() || file.getFileName().contains("system_syx"))
        {
            QString fileName = QFileDialog::getSaveFileName(
                        this,
                        tr("Save As"),
                        dir,
                        tr(" (*.gcl *.mid *.syx)"));
            if (!fileName.isEmpty())
            {
                if(!fileName.contains(".syx") && !fileName.contains(".mid") && !fileName.contains(".gcl"))
                {
                    fileName.append(".gcl");
                };

            };
            if(fileName.contains(".syx"))      { file.writeFile(fileName); }
            else if(fileName.contains(".mid")) { file.writeSMF(fileName); }
            else if(fileName.contains(".gcl")) {file.writeGCL(fileName); };

            file.setFile(fileName);
            if(file.readFile())
            {
                // DO SOMETHING AFTER READING THE FILE (UPDATE THE GUI)
                SysxIO *sysxIO = SysxIO::Instance();
                QString area = "Structure";
                sysxIO->setFileSource(area, file.getFileSource());
                emit updateSignal();
            };
        }
        else
        {
            if(file.getFileName().contains(".syx"))      { file.writeFile(file.getFileName()); }
            else if(file.getFileName().contains(".mid")) { file.writeSMF(file.getFileName()); }
            else if(file.getFileName().contains(".gcl")) {file.writeGCL(file.getFileName()); };
        };
    };
}

void mainWindow::saveAs()
{
    if(reg == true)
    {
        Preferences *preferences = Preferences::Instance();
        QString dir = preferences->getPreferences("General", "Files", "dir");

        QString fileName = QFileDialog::getSaveFileName(
                    this,
                    tr("Save As"),
                    dir,
                    tr("System Exclusive (*.syx)"));
        if (!fileName.isEmpty())
        {
            if(!fileName.contains(".syx"))
            {
                fileName.append(".gcl");
            };
            file.writeFile(fileName);

            file.setFile(fileName);
            if(file.readFile())
            {
                // DO SOMETHING AFTER READING THE FILE (UPDATE THE GUI)
                SysxIO *sysxIO = SysxIO::Instance();
                QString area = "Structure";
                sysxIO->setFileSource(area, file.getFileSource());


                emit updateSignal();
            };
        };
    };
}

void mainWindow::importSMF()
{
    Preferences *preferences = Preferences::Instance();
    QString dir = preferences->getPreferences("General", "Files", "dir");

    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Choose a file"),
                dir,
                tr("Standard Midi File (*.mid)"));
    if (!fileName.isEmpty())
    {
        file.setFile(fileName);
        if(file.readFile())
        {
            // DO SOMETHING AFTER READING THE FILE (UPDATE THE GUI)
            SysxIO *sysxIO = SysxIO::Instance();
            QString area = "Structure";
            sysxIO->setFileSource(area, file.getFileSource());
            sysxIO->setFileName(fileName);
            sysxIO->setSyncStatus(false);
            sysxIO->setDevice(false);
            emit updateSignal();
            if(sysxIO->isConnected())
            {sysxIO->writeToBuffer(); };
        };
    };
}

void mainWindow::exportSMF()
{
    if(reg == true)
    {
        Preferences *preferences = Preferences::Instance();
        QString dir = preferences->getPreferences("General", "Files", "dir");

        QString fileName = QFileDialog::getSaveFileName(
                    this,
                    tr("Export SMF"),
                    dir,
                    tr("Standard Midi File (*.mid)"));
        if (!fileName.isEmpty())
        {
            if(!fileName.contains(".mid"))
            {
                fileName.append(".mid");
            };
            file.writeSMF(fileName);

            file.setFile(fileName);
            if(file.readFile())
            {
                // DO SOMETHING AFTER READING THE FILE (UPDATE THE GUI)
                SysxIO *sysxIO = SysxIO::Instance();
                QString area = "Structure";
                sysxIO->setFileSource(area, file.getFileSource());

                emit updateSignal();
            };
        };
    };
}

void mainWindow::openGCL()
{
    Preferences *preferences = Preferences::Instance();
    QString dir = preferences->getPreferences("General", "Files", "dir");

    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Choose a file"),
                dir,
                tr("Boss Librarian File (*.gcl *.gxg *.gxb)"));
    if (!fileName.isEmpty())
    {
        file.setFile(fileName);
        if(file.readFile())
        {
            // DO SOMETHING AFTER READING THE FILE (UPDATE THE GUI)
            SysxIO *sysxIO = SysxIO::Instance();
            QString area = "Structure";
            sysxIO->setFileSource(area, file.getFileSource());
            sysxIO->setFileName(fileName);
            sysxIO->setSyncStatus(false);
            sysxIO->setDevice(false);

            emit updateSignal();
            if(sysxIO->isConnected())
            {sysxIO->writeToBuffer(); };
        };
    };
}

void mainWindow::saveGCL()
{

    if(reg == true)
    {

        Preferences *preferences = Preferences::Instance();
        QString dir = preferences->getPreferences("General", "Files", "dir");

        QString fileName = QFileDialog::getSaveFileName(
                    this,
                    tr("Export GCL"),
                    dir,
                    tr("Boss Librarian File (*.gcl)"));
        if (!fileName.isEmpty())
        {
            if(!fileName.contains(".gcl"))
            {
                fileName.append(".gcl");
            };
            file.writeGCL(fileName);

            file.setFile(fileName);
            if(file.readFile())
            {
                // DO SOMETHING AFTER READING THE FILE (UPDATE THE GUI)
                SysxIO *sysxIO = SysxIO::Instance();
                QString area = "Structure";
                sysxIO->setFileSource(area, file.getFileSource());

                emit updateSignal();
            };
        };
    };
}

void mainWindow::systemLoad()
{
    SysxIO *sysxIO = SysxIO::Instance();
    if (sysxIO->isConnected())
    {
        Preferences *preferences = Preferences::Instance();
        QString dir = preferences->getPreferences("General", "Files", "dir");

        QString fileName = QFileDialog::getOpenFileName(
                    this,
                    tr("Choose a file"),
                    dir,
                    deviceType + tr(" System Data File (*.GT100_system_syx)"));
        if (!fileName.isEmpty())
        {
            file.setFile(fileName);
            if(file.readFile())
            {
                // DO SOMETHING AFTER READING THE FILE (UPDATE THE GUI)
                SysxIO *sysxIO = SysxIO::Instance();
                QString area = "System";
                sysxIO->setFileSource(area, file.getSystemSource());
                sysxIO->setFileName(fileName);
                //sysxIO->setSyncStatus(false);
                //sysxIO->setDevice(false);
                emit updateSignal();
                QMessageBox *msgBox = new QMessageBox();
                msgBox->setWindowTitle(deviceType + tr(" Fx FloorBoard"));
                msgBox->setIcon(QMessageBox::Warning);
                msgBox->setTextFormat(Qt::RichText);
                QString msgText;
                msgText.append("<font size='+1'><b>");
                msgText.append(tr("You have chosen to load a SYSTEM DATA file."));
                msgText.append("<b></font><br>");
                msgText.append(tr("This will overwrite the SYSTEM DATA currently stored in the ")+ deviceType);
                msgText.append(tr ("<br> and can't be undone.<br>"));
                msgText.append(tr("Select 'NO' to only update the Editor - Select 'YES' to update the GT System<br>"));


                msgBox->setInformativeText(tr("Are you sure you want to write to the ")+ deviceType);
                msgBox->setText(msgText);
                msgBox->setStandardButtons(QMessageBox::Yes | QMessageBox::No);

                if(msgBox->exec() == QMessageBox::Yes)
                {	// Accepted to overwrite system data.
                    sysxIO->systemWrite();
                };
            };
        };
    }
    else
    {
        QString snork = tr("Ensure connection is active and retry");
        QMessageBox *msgBox = new QMessageBox();
        msgBox->setWindowTitle(deviceType + tr(" not connected !!"));
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setText(snork);
        msgBox->setStandardButtons(QMessageBox::Ok);
        msgBox->exec();
    };
}

void mainWindow::systemSave()
{
    if(reg == true)
    {
        SysxIO *sysxIO = SysxIO::Instance();
        if (sysxIO->isConnected())
        {
            sysxIO->systemDataRequest();

            Preferences *preferences = Preferences::Instance();
            QString dir = preferences->getPreferences("General", "Files", "dir");

            QString fileName = QFileDialog::getSaveFileName(
                        this,
                        tr("Save System Data"),
                        dir,
                        tr("System Exclusive File (*.GT100_system_syx)"));
            if (!fileName.isEmpty())
            {
                if(!fileName.contains(".GT100_system_syx"))
                {
                    fileName.append(".GT100_system_syx");
                };

                file.writeSystemFile(fileName);

                file.setFile(fileName);
                if(file.readFile())
                {
                    SysxIO *sysxIO = SysxIO::Instance();
                    QString area = "System";
                    sysxIO->setFileSource(area, file.getSystemSource());
                    emit updateSignal();
                };
            };
        }
        else
        {
            QString snork = tr("Ensure connection is active and retry<br>");
            QMessageBox *msgBox = new QMessageBox();
            msgBox->setWindowTitle(deviceType + tr(" not connected !!"));
            msgBox->setIcon(QMessageBox::Information);
            msgBox->setText(snork);
            msgBox->setStandardButtons(QMessageBox::Ok);
            msgBox->exec();
        };
    };
}

void mainWindow::bulkLoad()
{
    SysxIO *sysxIO = SysxIO::Instance();
    if (sysxIO->isConnected())
    {
        bulkLoadDialog *loadDialog = new bulkLoadDialog();
        loadDialog->exec();
    }
    else
    {
        QString snork = tr("Ensure connection is active and retry");
        QMessageBox *msgBox = new QMessageBox();
        msgBox->setWindowTitle(deviceType + tr(" not connected !!"));
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setText(snork);
        msgBox->setStandardButtons(QMessageBox::Ok);
        msgBox->exec();
    };
}

void mainWindow::bulkSave()
{

    SysxIO *sysxIO = SysxIO::Instance();
    if (sysxIO->isConnected())
    {
        bulkSaveDialog *bulkDialog = new bulkSaveDialog();
        bulkDialog->exec();
    }
    else
    {
        QString snork = tr("Ensure connection is active and retry");
        QMessageBox *msgBox = new QMessageBox();
        msgBox->setWindowTitle(deviceType + tr(" not connected !!"));
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setText(snork);
        msgBox->setStandardButtons(QMessageBox::Ok);
        msgBox->exec();
    };
}

/* TOOLS MENU */
void mainWindow::settings()
{
    preferencesDialog *dialog = new preferencesDialog();
    if (dialog->exec())
    {
        Preferences *preferences = Preferences::Instance();

        QString dir = dialog->generalSettings->dirEdit->text();
        QString sidepanel = (dialog->windowSettings->sidepanelCheckBox->checkState())?QString("true"):QString("false");
        QString window = (dialog->windowSettings->windowCheckBox->checkState())?QString("true"):QString("false");
        QString singleWindow = (dialog->windowSettings->singleWindowCheckBox->checkState())?QString("true"):QString("false");
        QString widgetHelp = (dialog->windowSettings->widgetsCheckBox->checkState())?QString("true"):QString("false");
        QString splash = (dialog->windowSettings->splashCheckBox->checkState())?QString("true"):QString("false");
        QString dBug = (dialog->midiSettings->dBugCheckBox->checkState())?QString("true"):QString("false");
        QString midiIn = QString::number(dialog->midiSettings->midiInCombo->currentIndex() - 1, 10); // -1 because there is a default entry at index 0
        QString midiOut = QString::number(dialog->midiSettings->midiOutCombo->currentIndex() - 1, 10);
        QString midiTimeSet =QString::number(dialog->midiSettings->midiTimeSpinBox->value());
        QString receiveTimeout =QString::number(dialog->midiSettings->midiDelaySpinBox->value());
        QString lang;
        if (dialog->languageSettings->chineseButton->isChecked() ) {lang="6"; }
        else if (dialog->languageSettings->japaneseButton->isChecked() ) {lang="5"; }
        else if (dialog->languageSettings->spanishButton->isChecked() ) {lang="4"; }
        else if (dialog->languageSettings->portugueseButton->isChecked() ) {lang="3"; }
        else if (dialog->languageSettings->germanButton->isChecked() ) {lang="2"; }
        else if (dialog->languageSettings->frenchButton->isChecked() ) {lang="1"; }
        else {lang="0"; };
        preferences->setPreferences("Language", "Locale", "select", lang);
        QString choice;
        if (dialog->styleSettings->motifButton->isChecked() ) {choice="3"; }
        else if (dialog->styleSettings->cdeButton->isChecked() ) {choice="2"; }
        else if (dialog->styleSettings->plastiqueButton->isChecked() ) {choice="1"; }
        else {choice="0"; };
        preferences->setPreferences("Scheme", "Style", "select", choice);
        if (dialog->styleSettings->systemButton->isChecked() ) {choice="4"; }
        else if (dialog->styleSettings->greenButton->isChecked() ) {choice="3"; }
        else if (dialog->styleSettings->blueButton->isChecked() ) {choice="2"; }
        else if (dialog->styleSettings->whiteButton->isChecked() ) {choice="1"; }
        else {choice="0"; };
        preferences->setPreferences("Scheme", "Colour", "select", choice);

        if(midiIn=="-1") { midiIn = ""; };
        if(midiOut=="-1") {	midiOut = ""; };

        preferences->setPreferences("General", "Files", "dir", dir);
        preferences->setPreferences("Midi", "MidiIn", "device", midiIn);
        preferences->setPreferences("Midi", "MidiOut", "device", midiOut);
        preferences->setPreferences("Midi", "DBug", "bool", dBug);
        preferences->setPreferences("Midi", "Time", "set", midiTimeSet);
        preferences->setPreferences("Midi", "Delay", "set", receiveTimeout);
        preferences->setPreferences("Window", "Restore", "sidepanel", sidepanel);
        preferences->setPreferences("Window", "Restore", "window", window);
        preferences->setPreferences("Window", "Single", "bool", singleWindow);
        preferences->setPreferences("Window", "Widgets", "bool", widgetHelp);
        preferences->setPreferences("Window", "Splash", "bool", splash);
        preferences->savePreferences();
    };
}

/* HELP MENU */
void mainWindow::help()
{
    Preferences *preferences = Preferences::Instance();
    QDesktopServices::openUrl(QUrl( preferences->getPreferences("General", "Help", "url") ));
}

void mainWindow::whatsThis()
{
    QWhatsThis::enterWhatsThisMode();
}


void mainWindow::upload()
{
    //Preferences *preferences = Preferences::Instance();
    QDesktopServices::openUrl(QUrl( "http://www.bossgtcentral.com/dm/" ));
}

void mainWindow::summaryPage()
{
    summaryDialog *summary = new summaryDialog();
    summary->setMinimumWidth(800);
    summary->setMinimumHeight(650);
    summary->show();
}

void mainWindow::summarySystemPage()
{
    summaryDialogSystem *summarySystem = new summaryDialogSystem();
    summarySystem->setMinimumWidth(800);
    summarySystem->setMinimumHeight(650);
    summarySystem->show();
}

void mainWindow::summaryPatchList()
{
    summaryDialogPatchList *summaryPatchList = new summaryDialogPatchList();
    summaryPatchList->setMinimumWidth(800);
    summaryPatchList->setMinimumHeight(650);
    summaryPatchList->show();
}

void mainWindow::homepage()
{
    //Preferences *preferences = Preferences::Instance();
    QDesktopServices::openUrl(QUrl( "http://sourceforge.net/projects/fxfloorboard/" ));
}

void mainWindow::donate()
{
    //Preferences *preferences = Preferences::Instance();
    QDesktopServices::openUrl(QUrl("https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=9B7Z6AQLF86WW" ));
}

void mainWindow::manual()
{
    //Preferences *preferences = Preferences::Instance();
    QDesktopServices::openUrl(QUrl( "http://www.roland.com/products/en/GT-100/" ));
}

void mainWindow::license()
{
    QDesktopServices::openUrl(QUrl(":license.txt"));
}

void mainWindow::about()
{
    Preferences *preferences = Preferences::Instance();
    QString version = preferences->getPreferences("General", "Application", "version");

    QFile file(":about");
    if(file.open(QIODevice::ReadOnly))
    {
        QMessageBox::about(this, deviceType + tr(" Fx FloorBoard - About"),
                           deviceType + tr(" Fx FloorBoard - ") + tr("version") + " " + version + "<br>" + file.readAll());
    };
}

void mainWindow::closeEvent(QCloseEvent* ce)
{
    Preferences *preferences = Preferences::Instance();
    preferences->savePreferences();
    ce->accept();
    emit closed();
}
