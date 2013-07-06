#############################################################################
##
## Copyright (C) 2007~2013 Colin Willcocks.
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
 
#Header files
HEADERS += ./editPage.h \
    ./editWindow.h \
    ./globalVariables.h \
    ./mainWindow.h \
    ./bankTreeList.h \
    ./bulkEditDialog.h \
    ./bulkLoadDialog.h \
    ./bulkSaveDialog.h \
    ./customButton.h \
    ./customComboBox.h \
    ./customControlParaEQ.h \
    ./customControlEZ_amp.h \
    ./customControlEZ_Patch.h \
    ./customControlGraphicEQ.h \
    ./customControlKnob.h \
    ./customControlRange.h \
    ./customControlLabel.h \
    ./customControlMasterEQ.h \
    ./customControlListMenu.h \
    ./customControlMidiTable.h \
    ./customControlSwitch.h \
    ./customControlTarget.h \
    ./customDial.h \
    ./customDisplay.h \
    ./customDisplayButton.h \
    ./customParaEQGraph.h \
    ./customEZ_amp.h \
    ./customEZ_Patch.h \
    ./customGraphicEQGraph.h \
    ./customKnob.h \
    ./customKnobTarget.h \
    ./customKnobRange.h \
    ./customLabelDisplay.h \
    ./customLed.h \
    ./customMasterEQGraph.h \
    ./customMultiComboBox.h \
    ./customPanelButton.h \
    ./customRangeDial.h \
    ./customRenameDialog.h \
    ./customRenameWidget.h \
    ./customSlider.h \
    ./customSplashScreen.h \
    ./customSwitch.h \ 
    ./customTargetDial.h \
    ./customTargetListMenu.h \
    ./dragBar.h \
    ./fileDialog.h \
    ./floorBoard.h \
    ./floorBoardDisplay.h \
    ./floorPanelBar.h \
    ./floorPanelBarButton.h \
    ./initPatchListMenu.h \
    ./menuPage.h \
    ./menuPage_assign1.h \
    ./menuPage_assign2.h \
    ./menuPage_assign3.h \
    ./menuPage_assign4.h \
    ./menuPage_assign5.h \
    ./menuPage_assign6.h \
    ./menuPage_assign7.h \
    ./menuPage_assign8.h \
    ./menuPage_ez_edit.h \
    ./menuPage_midi.h \
    ./menuPage_master.h \
    ./menuPage_system.h \
    ./renameDialog.h \
    ./renameWidget.h \
    ./statusBarSymbol.h \
    ./statusBarWidget.h \
    ./stompBox.h \
    ./stompbox_ce.h \
    ./stompbox_ch_a.h \
    ./stompbox_ch_b.h \
    ./stompbox_cn_s.h \
    ./stompbox_cn_m.h \
    ./stompbox_cn_m1_s2.h \
    ./stompbox_cs.h \
    ./stompbox_dd.h \
    ./stompbox_fx3.h \
    ./stompbox_eq.h \
    ./stompbox_fv.h \
    ./stompbox_fx1.h \
    ./stompbox_fx2.h \
    ./stompbox_lp.h \
    ./stompbox_ns_1.h \
    ./stompbox_ns_2.h \
    ./stompbox_od.h \
    ./stompbox_pdl.h \
    ./stompbox_rv.h \
    ./stompbox_usb.h \
    ./midiIO.h \
    ./MidiTable.h \
    ./MidiTableDestroyer.h \
    ./RtError.h \
    ./RtMidi.h \
    ./summaryDialog.h \
    ./summaryDialogPatchList.h \
    ./summaryDialogSystem.h \
    ./SysxIO.h \
    ./SysxIODestroyer.h \
    ./sysxWriter.h \
    ./Preferences.h \
    ./PreferencesDestroyer.h \
    ./preferencesDialog.h \
    ./preferencesPages.h \
    ./xmlwriter/xmlwriter.h \
    ./xmlwriter/xmlwriter_p.h 

#Source files
SOURCES += ./editPage.cpp \
    ./editWindow.cpp \
    ./main.cpp \
    ./mainWindow.cpp \
    ./bankTreeList.cpp \
    ./bulkEditDialog.cpp \
    ./bulkLoadDialog.cpp \
    ./bulkSaveDialog.cpp \
    ./customButton.cpp \
    ./customComboBox.cpp \
    ./customControlParaEQ.cpp \
    ./customControlEZ_amp.cpp \
    ./customControlEZ_Patch.cpp \
    ./customControlGraphicEQ.cpp \
    ./customControlKnob.cpp \
    ./customControlLabel.cpp \
    ./customControlListMenu.cpp \
    ./customControlMidiTable.cpp \
    ./customControlMasterEQ.cpp \
    ./customControlRange.cpp \
    ./customControlSwitch.cpp \
    ./customControlTarget.cpp \
    ./customDial.cpp \
    ./customDisplay.cpp \
    ./customDisplayButton.cpp \
    ./customParaEQGraph.cpp \
    ./customEZ_amp.cpp \
    ./customEZ_Patch.cpp \
    ./customGraphicEQGraph.cpp \
    ./customKnob.cpp \
    ./customKnobTarget.cpp \
    ./customKnobRange.cpp \
    ./customLabelDisplay.cpp \
    ./customLed.cpp \
    ./customMasterEQGraph.cpp \
    ./customMultiComboBox.cpp \
    ./customPanelButton.cpp \
    ./customRangeDial.cpp \
    ./customRenameDialog.cpp \
    ./customRenameWidget.cpp \
    ./customSlider.cpp \
    ./customSplashScreen.cpp \
    ./customSwitch.cpp \
    ./customTargetDial.cpp \
    ./customTargetListMenu.cpp \
    ./dragBar.cpp \
    ./fileDialog.cpp \
    ./floorBoard.cpp \
    ./floorBoardDisplay.cpp \
    ./floorPanelBar.cpp \
    ./floorPanelBarButton.cpp \
    ./initPatchListMenu.cpp \
    ./menuPage.cpp \
    ./menuPage_assign1.cpp \
    ./menuPage_assign2.cpp \
    ./menuPage_assign3.cpp \
    ./menuPage_assign4.cpp \
    ./menuPage_assign5.cpp \
    ./menuPage_assign6.cpp \
    ./menuPage_assign7.cpp \
    ./menuPage_assign8.cpp \
    ./menuPage_ez_edit.cpp \
    ./menuPage_midi.cpp \
    ./menuPage_master.cpp \
    ./menuPage_system.cpp \
    ./renameDialog.cpp \
    ./renameWidget.cpp \
    ./statusBarSymbol.cpp \
    ./statusBarWidget.cpp \
    ./stompBox.cpp \
    ./stompbox_ce.cpp \
    ./stompbox_ch_a.cpp \
    ./stompbox_ch_b.cpp \
    ./stompbox_cn_s.cpp \
    ./stompbox_cn_m.cpp \
    ./stompbox_cn_m1_s2.cpp \
    ./stompbox_cs.cpp \
    ./stompbox_dd.cpp \
    ./stompbox_fx3.cpp \
    ./stompbox_eq.cpp \
    ./stompbox_fv.cpp \
    ./stompbox_fx1.cpp \
    ./stompbox_fx2.cpp \
    ./stompbox_lp.cpp \
    ./stompbox_ns_1.cpp \
    ./stompbox_ns_2.cpp \
    ./stompbox_od.cpp \
    ./stompbox_pdl.cpp \
    ./stompbox_rv.cpp \ 
    ./stompbox_usb.cpp \
    ./summaryDialog.cpp \
    ./summaryDialogPatchList.cpp \
    ./summaryDialogSystem.cpp \
    ./midiIO.cpp \
    ./MidiTable.cpp \
    ./MidiTableDestroyer.cpp \
    ./Preferences.cpp \
    ./PreferencesDestroyer.cpp \
    ./preferencesDialog.cpp \
    ./preferencesPages.cpp \
    ./SysxIO.cpp \
    ./SysxIODestroyer.cpp \
    ./sysxWriter.cpp \
    ./xmlwriter/xmlwriter.cpp    
    
#Resource file(s)
RESOURCES += GT-100FxFloorBoard.qrc
