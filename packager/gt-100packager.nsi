; Script generated by the HM NIS Edit Script Wizard.

; HM NIS Edit Wizard helper defines
!define PRODUCT_NAME "GT-100FxFloorBoard"
!define PRODUCT_VERSION "20141028"
!define PRODUCT_PUBLISHER "Colin Willcocks (gumtown)"
!define PRODUCT_WEB_SITE "http://sourceforge.net/projects/fxfloorboard"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\GT-100FxFloorBoard.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

; MUI 1.67 compatible ------
!include "MUI.nsh"

; MUI Settings
!define MUI_ABORTWARNING
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

; Welcome page
!insertmacro MUI_PAGE_WELCOME
; License page
!insertmacro MUI_PAGE_LICENSE "license.txt"
; Directory page
!insertmacro MUI_PAGE_DIRECTORY
; Instfiles page
!insertmacro MUI_PAGE_INSTFILES
; Finish page
!define MUI_FINISHPAGE_RUN "$INSTDIR\GT-100FxFloorBoard.exe"
!define MUI_FINISHPAGE_SHOWREADME "$INSTDIR\readme.txt"
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_INSTFILES

; Language files
!insertmacro MUI_LANGUAGE "English"

; MUI end ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "GT-100FxFloorBoard_Setup.exe"
InstallDir "$PROGRAMFILES\GT-100FxFloorBoard"
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
ShowInstDetails show
ShowUnInstDetails show

Section "MainSection" SEC01
  SetOutPath "$INSTDIR"
  SetOverwrite ifnewer
  File "GT-100.tsl"
  File "test ver2.GT100_system_syx"
  File "temp-5.syx"
  File "temp-4.syx"
  File "temp-3.syx"
  File "temp-2.syx"
  File "temp-1.syx"
  File "readme.txt"
  File "Qt5Xml.dll"
  File "Qt5Widgets.dll"
  File "Qt5PrintSupport.dll"
  File "Qt5Gui.dll"
  File "Qt5Core.dll"
  File "preferences.xml"
  File "license.txt"
  File "libwinpthread-1.dll"
  File "libstdc++-6.dll"
  File "libgcc_s_dw2-1.dll"
  File "icuuc51.dll"
  File "icuin51.dll"
  File "icudt51.dll"
  File "GT-100FxFloorBoard.exe"
  CreateDirectory "$SMPROGRAMS\GT-100FxFloorBoard"
  CreateShortCut "$SMPROGRAMS\GT-100FxFloorBoard\GT-100FxFloorBoard.lnk" "$INSTDIR\GT-100FxFloorBoard.exe"
  CreateShortCut "$DESKTOP\GT-100FxFloorBoard.lnk" "$INSTDIR\GT-100FxFloorBoard.exe"
  SetOutPath "$INSTDIR\platforms"
  SetOverwrite try
  File "platforms\qwindows.dll"
  SetOutPath "$INSTDIR\Init Patches"
  File "Init Patches\000_INIT_Empty.syx"
  File "Init Patches\001_INIT_(JC_Clean)_Roland_JC120.syx"
  File "Init Patches\002_INIT_(JC_Clean)_Warm_Clean.syx"
  File "Init Patches\004_INIT_(JC_Clean)_Full_Range.syx"
  File "Init Patches\005_INIT_Two channels and effects.syx"
  File "Init Patches\006_INIT_(TW_Clean)_Fender_Twin_Reverb_Clean.syx"
  File "Init Patches\010_INIT_(Chrunch)_Crunch.syx"
  File "Init Patches\011_INIT_(Crunch)_.syx_Stack_Crunch.syx"
  File "Init Patches\020_INIT_(BG_Lead)_Messa_Boogie_Lead.syx"
  File "Init Patches\023_INIT_(BG_Lead)_Messa_Boogie_Mark_I_Smooth_Drive.syx"
  File "Init Patches\040_INIT_(HiGain)_Soldano_SLO-100.syx"
  File "Init Patches\042_INIT_(HiGain)_Lead_Stack.syx"
  File "Init Patches\047_INIT_(Custom)_Custom_1.syx"
  File "Init Patches\047_INIT_(Custom)_Custom_2.syx"
SectionEnd

Section -AdditionalIcons
  SetOutPath $INSTDIR
  WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
  CreateShortCut "$SMPROGRAMS\GT-100FxFloorBoard\Website.lnk" "$INSTDIR\${PRODUCT_NAME}.url"
  CreateShortCut "$SMPROGRAMS\GT-100FxFloorBoard\Uninstall.lnk" "$INSTDIR\uninst.exe"
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\GT-100FxFloorBoard.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\GT-100FxFloorBoard.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd


Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) was successfully removed from your computer."
FunctionEnd

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Are you sure you want to completely remove $(^Name) and all of its components?" IDYES +2
  Abort
FunctionEnd

Section Uninstall
  Delete "$INSTDIR\${PRODUCT_NAME}.url"
  Delete "$INSTDIR\uninst.exe"
  Delete "$INSTDIR\Init Patches\047_INIT_(Custom)_Custom_2.syx"
  Delete "$INSTDIR\Init Patches\047_INIT_(Custom)_Custom_1.syx"
  Delete "$INSTDIR\Init Patches\042_INIT_(HiGain)_Lead_Stack.syx"
  Delete "$INSTDIR\Init Patches\040_INIT_(HiGain)_Soldano_SLO-100.syx"
  Delete "$INSTDIR\Init Patches\023_INIT_(BG_Lead)_Messa_Boogie_Mark_I_Smooth_Drive.syx"
  Delete "$INSTDIR\Init Patches\020_INIT_(BG_Lead)_Messa_Boogie_Lead.syx"
  Delete "$INSTDIR\Init Patches\011_INIT_(Crunch)_.syx_Stack_Crunch.syx"
  Delete "$INSTDIR\Init Patches\010_INIT_(Chrunch)_Crunch.syx"
  Delete "$INSTDIR\Init Patches\006_INIT_(TW_Clean)_Fender_Twin_Reverb_Clean.syx"
  Delete "$INSTDIR\Init Patches\005_INIT_Two channels and effects.syx"
  Delete "$INSTDIR\Init Patches\004_INIT_(JC_Clean)_Full_Range.syx"
  Delete "$INSTDIR\Init Patches\002_INIT_(JC_Clean)_Warm_Clean.syx"
  Delete "$INSTDIR\Init Patches\001_INIT_(JC_Clean)_Roland_JC120.syx"
  Delete "$INSTDIR\Init Patches\000_INIT_Empty.syx"
  Delete "$INSTDIR\platforms\qwindows.dll"
  Delete "$INSTDIR\GT-100FxFloorBoard.exe"
  Delete "$INSTDIR\icudt51.dll"
  Delete "$INSTDIR\icuin51.dll"
  Delete "$INSTDIR\icuuc51.dll"
  Delete "$INSTDIR\ksuser.dll"
  Delete "$INSTDIR\libgcc_s_dw2-1.dll"
  Delete "$INSTDIR\libstdc++-6.dll"
  Delete "$INSTDIR\libwinpthread-1.dll"
  Delete "$INSTDIR\license.txt"
  Delete "$INSTDIR\preferences.xml"
  Delete "$INSTDIR\Qt5Core.dll"
  Delete "$INSTDIR\Qt5Gui.dll"
  Delete "$INSTDIR\Qt5PrintSupport.dll"
  Delete "$INSTDIR\Qt5Widgets.dll"
  Delete "$INSTDIR\Qt5Xml.dll"
  Delete "$INSTDIR\readme.txt"
  Delete "$INSTDIR\temp-1.syx"
  Delete "$INSTDIR\temp-2.syx"
  Delete "$INSTDIR\temp-3.syx"
  Delete "$INSTDIR\temp-4.syx"
  Delete "$INSTDIR\temp-5.syx"
  Delete "$INSTDIR\test ver2.GT100_system_syx"
  Delete "$INSTDIR\GT-100.tsl"

  Delete "$SMPROGRAMS\GT-100FxFloorBoard\Uninstall.lnk"
  Delete "$SMPROGRAMS\GT-100FxFloorBoard\Website.lnk"
  Delete "$DESKTOP\GT-100FxFloorBoard.lnk"
  Delete "$SMPROGRAMS\GT-100FxFloorBoard\GT-100FxFloorBoard.lnk"

  RMDir "$SMPROGRAMS\GT-100FxFloorBoard"
  RMDir "$INSTDIR\platforms"
  RMDir "$INSTDIR\Init Patches"
  RMDir "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd