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
CONFIG += static
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
android{
        message(Including Android specific headers and sources...)
DEPENDPATH += .
QT += androidextras
        message("Special Android build messages !!")
   ## OTHER_FILES += \
   ## android/AndroidManifest.xml \
   ## android/res/layout/splash.xml \
   ## android/res/values/libs.xml \
   ## android/res/values/strings.xml \
   ## android/res/values-de/strings.xml \
   ## android/res/values-el/strings.xml \
   ## android/res/values-es/strings.xml \
   ## android/res/values-et/strings.xml \
   ## android/res/values-fa/strings.xml \
   ## android/res/values-fr/strings.xml \
   ## android/res/values-id/strings.xml \
   ## android/res/values-it/strings.xml \
   ## android/res/values-ja/strings.xml \
   ## android/res/values-ms/strings.xml \
   ## android/res/values-nb/strings.xml \
   ## android/res/values-nl/strings.xml \
   ## android/res/values-pl/strings.xml \
   ## android/res/values-pt-rBR/strings.xml \
   ## android/res/values-ro/strings.xml \
   ## android/res/values-rs/strings.xml \
   ## android/res/values-ru/strings.xml \
   ## android/res/values-zh-rCN/strings.xml \
   ## android/res/values-zh-rTW/strings.xml \
   ## android/src/org/kde/necessitas/ministro/IMinistro.aidl \
   ## android/src/org/kde/necessitas/ministro/IMinistroCallback.aidl \
   ## android/src/org/qtproject/qt5/android/bindings/QtActivity.java \
   ## android/src/org/qtproject/qt5/android/bindings/QtApplication.java \
   ## android/version.xml \
   ## android/midi-driver.apklib
}


#Include file(s)
include(GT-100FxFloorBoard.pri)

#Windows resource file
win32:RC_FILE = GT-100FxFloorBoard.rc

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    android/AndroidManifest.xml

DISTFILES += \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat

