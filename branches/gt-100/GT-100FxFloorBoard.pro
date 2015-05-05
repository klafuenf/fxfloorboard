#############################################################################
##
## Copyright (C) 2007~2015 Colin Willcocks.
## Copyright (C) 2005~2007 Uco Mesdag. 
## All rights reserved.
##
## This file is part of "GT-100 Fx FloorBoard".
##
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License along
## with this program; if not, write to the Free Software Foundation, Inc.,
## 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
##
#############################################################################

cache()
TEMPLATE = app
##CONFIG += static
CONFIG += embed_manifest_exe
CONFIG += release
TARGET = "GT-100FxFloorBoard"
DESTDIR = ./packager
	OBJECTS_DIR += release
	UI_DIR += ./generatedfiles
	MOC_DIR += ./generatedfiles/release
INCLUDEPATH += ./generatedfiles \
    ./generatedfiles/release \
    .
    
TRANSLATIONS = language_fr.ts \
               language_ge.ts \
               language_ch.ts
               
CODECFORTR = UTF-8

DEPENDPATH += .
QT += xml
QT += widgets
QT += printsupport

#Platform dependent file(s)
win32{
        exists("C:/SDK/Lib/WinMM.Lib")
                {	# <-- Change the path to WinMM.Lib here!
                    LIBS += C:/SDK/Lib/WinMM.Lib	# <-- Change the path here also!
                   # LIBS += C:/SDK/Lib/setupapi.Lib
                   # LIBS += C:/SDK/Lib/ksuser.Lib
                }
        message(Including Windows specific headers and sources...)
}
linux-g++{
        LIBS += -lasound
        LIBS += -ljack
        message("ALSA LIBRARIES SHOULD BE INSTALLED or ERROR will Occur")
        message("Please install the ALSA Audio System packages if not present")
        message(Including Linux specific headers and sources...)
}
linux-g++-64{
        LIBS += -lasound
        LIBS += -ljack
        message("ALSA LIBRARIES SHOULD BE INSTALLED or ERROR will Occur")
        message("Please install the ALSA Audio System packages if not present")
        message(Including Linux specific headers and sources...)
}
macx{
        LIBS += -framework CoreMidi -framework CoreAudio -framework CoreFoundation
        LIBS += -ljack
        message("X-Code LIBRARIES SHOULD BE INSTALLED or ERROR will Occur")
        message("Please install the X-Code Audio System packages if not present")
        ICON = GT-100FxFloorBoard.icns
        message(Including Mac OS X specific headers and sources...)
}



#Include file(s)
include(GT-100FxFloorBoard.pri)

#Windows resource file
win32:RC_FILE = GT-100FxFloorBoard.rc

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    android/AndroidManifest.xml

