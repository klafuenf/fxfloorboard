cmake_minimum_required(VERSION 3.9.4)

project(gt100)

set(CMAKE_VERBOSE_MAKEFILE on)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Widgets)
find_package(Qt5Xml)
find_package(Qt5PrintSupport)

find_package(ALSA)
find_package(Threads)


set(HEADERS
    editPage.h 
    editWindow.h 
    globalVariables.h 
    mainWindow.h 
    bankTreeList.h 
    bulkEditDialog.h 
    bulkLoadDialog.h 
    bulkSaveDialog.h 
    customButton.h 
    customComboBox.h 
    customControlParaEQ.h 
    customControlEZ_amp.h 
    customControlEZ_Patch.h 
    customControlGraphicEQ.h 
    customControlKnob.h 
    customControlRange.h 
    customControlLabel.h 
    customControlMasterEQ.h 
    customControlListMenu.h 
    customControlMidiTable.h 
    customControlSwitch.h 
    customControlTarget.h 
    customDial.h 
    customDisplay.h 
    customParaEQGraph.h 
    customEZ_amp.h 
    customEZ_Patch.h 
    customGraphicEQGraph.h 
    customKnob.h 
    customKnobTarget.h 
    customKnobRange.h 
    customLabelDisplay.h 
    customLed.h 
    customMasterEQGraph.h 
    customMultiComboBox.h 
    customPanelButton.h 
    customRangeDial.h 
    customRenameDialog.h 
    customRenameWidget.h 
    customSlider.h 
    customSplashScreen.h 
    customSwitch.h 
    customSystemOverride.h 
    customTargetDial.h 
    customTargetListMenu.h 
    dragBar.h 
    fileDialog.h 
    floorBoard.h 
    floorBoardDisplay.h 
    floorPanelBar.h 
    floorPanelBarButton.h 
    initPatchListMenu.h 
    menuPage.h 
    menuPage_assign1.h 
    menuPage_assign2.h 
    menuPage_assign3.h 
    menuPage_assign4.h 
    menuPage_assign5.h 
    menuPage_assign6.h 
    menuPage_assign7.h 
    menuPage_assign8.h 
    menuPage_ez_edit.h 
    menuPage_midi.h 
    menuPage_master.h 
    menuPage_system.h 
    renameDialog.h 
    renameWidget.h 
    statusBarSymbol.h 
    statusBarWidget.h 
    stompBox.h 
    stompbox_ce.h 
    stompbox_ch_a.h 
    stompbox_ch_b.h 
    stompbox_cn_s.h 
    stompbox_cn_m.h 
    stompbox_cn_m1_s2.h 
    stompbox_cs.h 
    stompbox_dd.h 
    stompbox_fx3.h 
    stompbox_eq.h 
    stompbox_fv.h 
    stompbox_fx1.h 
    stompbox_fx2.h 
    stompbox_lp.h 
    stompbox_ns_1.h 
    stompbox_ns_2.h 
    stompbox_od.h 
    stompbox_pdl.h 
    stompbox_rv.h 
    stompbox_usb.h 
    midiIO.h 
    midiIODestroyer.h 
    MidiTable.h 
    MidiTableDestroyer.h 
    RtMidi.h 
    summaryDialog.h 
    summaryDialogPatchList.h 
    summaryDialogSystem.h 
    SysxIO.h 
    SysxIODestroyer.h 
    sysxWriter.h 
    Preferences.h 
    PreferencesDestroyer.h 
    preferencesDialog.h 
    preferencesPages.h 
    xmlwriter/xmlwriter.h 
    xmlwriter/xmlwriter_p.h )

#Source files
set(SOURCES
    editPage.cpp 
    editWindow.cpp 
    main.cpp 
    mainWindow.cpp 
    bankTreeList.cpp 
    bulkEditDialog.cpp 
    bulkLoadDialog.cpp 
    bulkSaveDialog.cpp 
    customButton.cpp 
    customComboBox.cpp 
    customControlParaEQ.cpp 
    customControlEZ_amp.cpp 
    customControlEZ_Patch.cpp 
    customControlGraphicEQ.cpp 
    customControlKnob.cpp 
    customControlLabel.cpp 
    customControlListMenu.cpp 
    customControlMidiTable.cpp 
    customControlMasterEQ.cpp 
    customControlRange.cpp 
    customControlSwitch.cpp 
    customControlTarget.cpp 
    customDial.cpp 
    customDisplay.cpp 
    customParaEQGraph.cpp 
    customEZ_amp.cpp 
    customEZ_Patch.cpp 
    customGraphicEQGraph.cpp 
    customKnob.cpp 
    customKnobTarget.cpp 
    customKnobRange.cpp 
    customLabelDisplay.cpp 
    customLed.cpp 
    customMasterEQGraph.cpp 
    customMultiComboBox.cpp 
    customPanelButton.cpp 
    customRangeDial.cpp 
    customRenameDialog.cpp 
    customRenameWidget.cpp 
    customSlider.cpp 
    customSplashScreen.cpp 
    customSwitch.cpp 
    customSystemOverride.cpp 
    customTargetDial.cpp 
    customTargetListMenu.cpp 
    dragBar.cpp 
    fileDialog.cpp 
    floorBoard.cpp 
    floorBoardDisplay.cpp 
    floorPanelBar.cpp 
    floorPanelBarButton.cpp 
    initPatchListMenu.cpp 
    menuPage.cpp 
    menuPage_assign1.cpp 
    menuPage_assign2.cpp 
    menuPage_assign3.cpp 
    menuPage_assign4.cpp 
    menuPage_assign5.cpp 
    menuPage_assign6.cpp 
    menuPage_assign7.cpp 
    menuPage_assign8.cpp 
    menuPage_ez_edit.cpp 
    menuPage_midi.cpp 
    menuPage_master.cpp 
    menuPage_system.cpp 
    renameDialog.cpp 
    renameWidget.cpp 
    RtMidi.cpp 
    statusBarSymbol.cpp 
    statusBarWidget.cpp 
    stompBox.cpp 
    stompbox_ce.cpp 
    stompbox_ch_a.cpp 
    stompbox_ch_b.cpp 
    stompbox_cn_s.cpp 
    stompbox_cn_m.cpp 
    stompbox_cn_m1_s2.cpp 
    stompbox_cs.cpp 
    stompbox_dd.cpp 
    stompbox_fx3.cpp 
    stompbox_eq.cpp 
    stompbox_fv.cpp 
    stompbox_fx1.cpp 
    stompbox_fx2.cpp 
    stompbox_lp.cpp 
    stompbox_ns_1.cpp 
    stompbox_ns_2.cpp 
    stompbox_od.cpp 
    stompbox_pdl.cpp 
    stompbox_rv.cpp 
    stompbox_usb.cpp 
    summaryDialog.cpp 
    summaryDialogPatchList.cpp 
    summaryDialogSystem.cpp 
    midiIO.cpp 
    midiIODestroyer.cpp 
    MidiTable.cpp 
    MidiTableDestroyer.cpp 
    Preferences.cpp 
    PreferencesDestroyer.cpp 
    preferencesDialog.cpp 
    preferencesPages.cpp 
    SysxIO.cpp 
    SysxIODestroyer.cpp 
    sysxWriter.cpp 
    xmlwriter/xmlwriter.cpp)

set(RESOURCES GT-100FxFloorBoard.qrc)
    
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} ${RESOURCES})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Xml Qt5::PrintSupport)
target_link_libraries(${PROJECT_NAME} ${ALSA_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${THREADS_LIBRARIES})
target_link_libraries (${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})


