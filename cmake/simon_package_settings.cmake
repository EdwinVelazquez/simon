# Copyright (c) 2008, Peter Grasch <grasch@simon-listens.org>
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without modification, 
# are permitted provided that the following conditions are met:
# 
#     Redistributions of source code must retain the above copyright notice, 
#     this list of conditions and the following disclaimer.
#     Redistributions in binary form must reproduce the above copyright notice, 
#     this list of conditions and the following disclaimer in the documentation 
#     and/or other materials provided with the distribution.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE 
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

if(WIN32)
SET(CPACK_GENERATOR "NSIS")
endif(WIN32)
if(UNIX)
SET(DESTDIR "/usr")
SET(CPACK_SET_DESTDIR "ON") 
SET(CPACK_GENERATOR "DEB;STGZ")
#SET(CPACK_GENERATOR "RPM")
endif(UNIX)

INCLUDE(InstallRequiredSystemLibraries)

IF(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
	SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE amd64)
	SET(CPACK_RPM_PACKAGE_ARCHITECTURE "x86_64")
ELSEIF(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "i686")
	SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE i386)
	SET(CPACK_RPM_PACKAGE_ARCHITECTURE "i386")
ENDIF(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")

SET(CPACK_DEBIAN_PACKAGE_DEPENDS  "kdelibs5 (>=4.3.98-0ubuntu3),
kdebase-runtime, libqtcore4, libqtgui4, libqt4-multimedia, libqt4-script, libstdc++6, libasound2, zlib1g, libc6, libportaudio2, libqt4-sql-sqlite, flex, libattica0")
SET(CPACK_DEBIAN_PACKAGE_CONFLICTS  "julius julius-simon")
SET(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA 
	"${CMAKE_CURRENT_SOURCE_DIR}/package/deb/postinst;${CMAKE_CURRENT_SOURCE_DIR}/package/deb/postrm")

SET(CPACK_PACKAGE_CONTACT "SIMON listens <support@simon-listens.org>")
SET(CPACK_DEBIAN_PACKAGE_SECTION "utils")
SET(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")

SET(CPACK_RPM_PACKAGE_LICENCE "GNU General Public License (GPL)")
SET(CPACK_RPM_PACKAGE_GROUP " Productivity/Multimedia/Sound/Utilities")
SET(CPACK_RPM_PACKAGE_REQUIRES "kdelibs4 >= 4.3.95, libattica0,
kdebase4-runtime, libasound2, zlib, portaudio, libqt4-sql, qt4-qtscript, libqt4-multimedia, libqt4-sql-sqlite, libqt4-x11, libqt4")

SET(CPACK_PACKAGE_NAME "Simon")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Open-Source Speech Recognition")
SET(CPACK_PACKAGE_DESCRIPTION "Simon provides an easy to use interface to the open-source speech recognizer julius (this package ships its own modified version of julius) and the HTK (has to be installed separately).\n\nsimon does not include a speech model but provides the means to create its own.\n\nWith the recognition results simon can type, open programs and places and more.")
SET(CPACK_PACKAGE_VENDOR "SIMON listens e.V.")
#SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/ReadMe.txt")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENCE.txt")
set(CPACK_PACKAGE_VERSION "0.4")
SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "3")
SET(CPACK_PACKAGE_VERSION_PATCH "60")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "simon ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}")
SET(CPACK_STRIP_FILES TRUE)
SET(CPACK_SOURCE_STRIP_FILES TRUE)

set(CPACK_SOURCE_IGNORE_FILES
"~$"
"/.svn/"
"/build/"
"\\\\.svn\\\\"
"\\\\build\\\\"
)

# Devel
# simoncommandinputnumberplugin 
set(CPACK_COMPONENTS_ALL  kdecore julius juliusdevel ksimond simondoc translations simoncommandaipluginaimlsalice
		simoncommandaipluginaimlsgerman simoncommandaiplugin simoncommandcompositeplugin simoncommandlistplugin 
		simoncommanddesktopgridplugin simoncommanddictationplugin simoncommandinputnumberplugin  
		simoncommandfilterplugin simoncommandpronunciationtrainingplugin  ssc sscd
		simoncommandexecutableplugin simoncommandplaceplugin simoncommandshortcutplugin simoncommandtextmacroplugin
		simon simond simoncore simoncoredevel simondevel simonddevel
    		simonmodelmanagement sam afaras simonstatus speechcal
		simoncommandkeyboardplugin simoncommandcalculatorplugin
                simonprocessopenedconditionplugin simonorconditionassociationplugin
                simonactivewindowplugin)

#SET(CPACK_COMPONENT_DEVEL_DISPLAY_NAME "Simon System Files")
SET(CPACK_COMPONENT_KDECORE_DISPLAY_NAME "KDE System Files")
SET(CPACK_COMPONENT_JULIUS_DISPLAY_NAME "Julius")
SET(CPACK_COMPONENT_JULIUSDEVEL_DISPLAY_NAME "Julius Development Files")
SET(CPACK_COMPONENT_KSIMOND_DISPLAY_NAME "KSimond")

SET(CPACK_COMPONENT_AFARAS_DISPLAY_NAME "Afaras")
SET(CPACK_COMPONENT_SAM_DISPLAY_NAME "Sam")
SET(CPACK_COMPONENT_SSC_DISPLAY_NAME "SSC")
SET(CPACK_COMPONENT_SSCD_DISPLAY_NAME "SSCd")
SET(CPACK_COMPONENT_SPEECHCAL_DISPLAY_NAME "Speechcal")
SET(CPACK_COMPONENT_SIMONSTATUS_DISPLAY_NAME "Simonstatus")

SET(CPACK_COMPONENT_SIMONDOC_DISPLAY_NAME "Simon Documentation")
SET(CPACK_COMPONENT_SIMONCOMMANDAIPLUGINAIMLSALICE_DISPLAY_NAME "AI: Alice AIMLS")
SET(CPACK_COMPONENT_SIMONCOMMANDAIPLUGINAIMLSGERMAN_DISPLAY_NAME "AI: German AIMLS")
SET(CPACK_COMPONENT_SIMONCOMMANDAIPLUGIN_DISPLAY_NAME "AI")
SET(CPACK_COMPONENT_SIMONCOMMANDCALCULATORPLUGIN_DISPLAY_NAME "Calculator")
SET(CPACK_COMPONENT_SIMONCOMMANDKEYBOARDPLUGIN_DISPLAY_NAME "Keyboard")
SET(CPACK_COMPONENT_SIMONCOMMANDCOMPOSITEPLUGIN_DISPLAY_NAME "Composite")
SET(CPACK_COMPONENT_SIMONCOMMANDDESKTOPGRIDPLUGIN_DISPLAY_NAME "Desktop Grid")
SET(CPACK_COMPONENT_SIMONCOMMANDDICTATIONPLUGIN_DISPLAY_NAME "Dictation")
SET(CPACK_COMPONENT_SIMONCOMMANDEXECUTABLEPLUGIN_DISPLAY_NAME "Executables")
SET(CPACK_COMPONENT_SIMONCOMMANDINPUTNUMBERPLUGIN_DISPLAY_NAME "Input Number")
SET(CPACK_COMPONENT_SIMONCOMMANDPRONUNCIATIONTRAININGPLUGIN_DISPLAY_NAME "Pronunciation Training")
SET(CPACK_COMPONENT_SIMONCOMMANDFILTERPLUGIN_DISPLAY_NAME "Filter")
SET(CPACK_COMPONENT_SIMONCOMMANDLISTPLUGIN_DISPLAY_NAME "List")
SET(CPACK_COMPONENT_SIMONCOMMANDSHORTCUTPLUGIN_DISPLAY_NAME "Shortcut")
SET(CPACK_COMPONENT_SIMONCOMMANDTEXTMACROPLUGIN_DISPLAY_NAME "Text-Macro")
SET(CPACK_COMPONENT_SIMON_DISPLAY_NAME "Simon")
SET(CPACK_COMPONENT_SIMONDEVEL_DISPLAY_NAME "Simon Development Files")
SET(CPACK_COMPONENT_SIMOND_DISPLAY_NAME "Simond")
SET(CPACK_COMPONENT_SIMONDDEVEL_DISPLAY_NAME "Simond Development Files")
SET(CPACK_COMPONENT_SIMONCORE_DISPLAY_NAME "Shared Components")
SET(CPACK_COMPONENT_SIMONCOREDEVEL_DISPLAY_NAME "Shared Components Development Files")
SET(CPACK_COMPONENT_TRANSLATIONS_DISPLAY_NAME "Translations")

SET(CPACK_COMPONENT_SIMONORCONDITIONASSOCIATIONPLUGIN_DISPLAY_NAME "'Or' Condition Association")
SET(CPACK_COMPONENT_SIMONPROCESSOPENEDCONDITIONPLUGIN_DISPLAY_NAME "Process Opened Condition")
SET(CPACK_COMPONENT_SIMONACTIVEWINDOWPLUGIN_DISPLAY_NAME "Active Window Condition")



#SET(CPACK_COMPONENT_DEVEL_DISPLAY_DESCRIPTION "Contains a needed set of libraries.")
SET(CPACK_COMPONENT_KDECORE_DISPLAY_DESCRIPTION "This contains a subset of the kde system files needed to run Simon / Simond / KSimond.")
SET(CPACK_COMPONENT_JULIUS_DISPLAY_DESCRIPTION "The Julius Recognition Engine")
SET(CPACK_COMPONENT_JULIUSDEVEL_DISPLAY_DESCRIPTION "The Julius Recognition Engine Development Files")
SET(CPACK_COMPONENT_KSIMOND_DISPLAY_DESCRIPTION "A KDE4 Front-End to Simond")

SET(CPACK_COMPONENT_SAM_DISPLAY_DESCRIPTION "Simon acoustic modeller")
SET(CPACK_COMPONENT_AFARAS_DISPLAY_DESCRIPTION "Automatically find and remove amiss samples")
SET(CPACK_COMPONENT_SSC_DISPLAY_DESCRIPTION "Simon sample collector")
SET(CPACK_COMPONENT_SSCD_DISPLAY_DESCRIPTION "Simon sample collector daemon")
SET(CPACK_COMPONENT_SIMONCOMMANDPLUGINBASE_DISPLAY_DESCRIPTION "Core library shared by all command plugins")

SET(CPACK_COMPONENT_SPEECHCAL_DISPLAY_DESCRIPTION "Speech controlled calendar")
SET(CPACK_COMPONENT_SIMONSTATUS_DISPLAY_DESCRIPTION "Simon status widget")

SET(CPACK_COMPONENT_SIMONCOMMANDAIPLUGINAIMLSALICE_DISPLAY_DESCRIPTION "The Alice-Personality for the AI Command Plug-In")
SET(CPACK_COMPONENT_SIMONCOMMANDAIPLUGINAIMLSGERMAN_DISPLAY_DESCRIPTION "A German Personality for the AI Command Plug-In")
SET(CPACK_COMPONENT_SIMONCOMMANDAIPLUGIN_DISPLAY_DESCRIPTION "The AI Command Plug-In")
SET(CPACK_COMPONENT_SIMONCOMMANDCALCULATORPLUGIN_DISPLAY_DESCRIPTION "The Calculator Command Plug-In")
SET(CPACK_COMPONENT_SIMONCOMMANDKEYBOARDPLUGIN_DISPLAY_DESCRIPTION "The Keyboard Command Plug-In")
SET(CPACK_COMPONENT_SIMONCOMMANDCOMPOSITEPLUGIN_DISPLAY_DESCRIPTION "The Composite Command Plug-In")
SET(CPACK_COMPONENT_SIMONCOMMANDDESKTOPGRIDPLUGIN_DISPLAY_DESCRIPTION "The Desktop Grid Command Plug-In")
SET(CPACK_COMPONENT_SIMONCOMMANDDICTATIONPLUGIN_DISPLAY_DESCRIPTION "The Dictation Command Plug-In")
SET(CPACK_COMPONENT_SIMONCOMMANDEXECUTABLEPLUGIN_DISPLAY_DESCRIPTION "The Executables Command Plug-In")
SET(CPACK_COMPONENT_SIMONCOMMANDLISTPLUGIN_DISPLAY_DESCRIPTION "The List Command Plug-In")
SET(CPACK_COMPONENT_SIMONCOMMANDINPUTNUMBERPLUGIN_DISPLAY_DESCRIPTION "The Input Number Command Plug-In")
SET(CPACK_COMPONENT_SIMONCOMMANDPRONUNCIATIONTRAININGPLUGIN_DISPLAY_DESCRIPTION "The Pronunciation Training Command Plug-In")
SET(CPACK_COMPONENT_SIMONCOMMANDFILTERPLUGIN_DISPLAY_DESCRIPTION "The Filter Command Plug-In")
SET(CPACK_COMPONENT_SIMONCOMMANDPLACEPLUGIN_DISPLAY_DESCRIPTION "The Place Command Plug-In")
SET(CPACK_COMPONENT_SIMONCOMMANDSHORTCUTPLUGIN_DISPLAY_DESCRIPTION "The Shortcut Command Plug-In")
SET(CPACK_COMPONENT_SIMONCOMMANDTEXTMACROPLUGIN_DISPLAY_DESCRIPTION "The Text-Macro Command Plug-In")
SET(CPACK_COMPONENT_SIMON_DISPLAY_DESCRIPTION "The Simon application; Acts as a client to the Simond recognition server and provides means to manage the speech- and acoustic model.")
SET(CPACK_COMPONENT_SIMONDEVEL_DISPLAY_DESCRIPTION "The Simon Development Files")
SET(CPACK_COMPONENT_SIMONDOC_DISPLAY_DESCRIPTION "The Simon Documentation")
SET(CPACK_COMPONENT_SIMOND_DISPLAY_DESCRIPTION "The Simond recognition server; Stores and compiles the models of the Simon clients. Uses Julius for the recognition.")
SET(CPACK_COMPONENT_SIMONDDEVEL_DISPLAY_DESCRIPTION "Development Files for the Simond recognition server")
SET(CPACK_COMPONENT_SIMONCORE_DISPLAY_DESCRIPTION "Required shared components.")
SET(CPACK_COMPONENT_SIMONCOREDEVEL_DISPLAY_DESCRIPTION "Development Files of the shared components")
SET(CPACK_COMPONENT_TRANSLATIONS_DISPLAY_DESCRIPTION "Translations of all the components.")

SET(CPACK_COMPONENT_SIMONORCONDITIONASSOCIATIONPLUGIN_DISPLAY_NAME "The 'Or' Condition Association Plug-In for context detection")
SET(CPACK_COMPONENT_SIMONPROCESSOPENEDCONDITIONPLUGIN_DISPLAY_NAME "The Process Opened Condition Plug-In for context detection")
SET(CPACK_COMPONENT_SIMONACTIVEWINDOWPLUGIN_DISPLAY_NAME "The Active Window Condition Plug-In for context detection")


set(CPACK_COMPONENT_KSIMOND_DEPENDS simond )
set(CPACK_COMPONENT_AFARAS_DEPENDS simoncore )
set(CPACK_COMPONENT_SIMONCOMMANDAIPLUGINAIMLSALICE_DEPENDS simoncommandaiplugin )
set(CPACK_COMPONENT_SIMONCOMMANDAIPLUGINAIMLSGERMAN_DEPENDS simoncommandaiplugin )
set(CPACK_COMPONENT_SIMONCOMMANDAIPLUGIN_DEPENDS simon)
set(CPACK_COMPONENT_SIMONCOMMANDKEYBOARDPLUGIN_DEPENDS simon)
set(CPACK_COMPONENT_SIMONCOMMANDCALCULATORPLUGIN_DEPENDS simon)
set(CPACK_COMPONENT_SIMONCOMMANDCOMPOSITEPLUGIN_DEPENDS simon)
set(CPACK_COMPONENT_SIMONCOMMANDDESKTOPGRIDPLUGIN_DEPENDS simon)
set(CPACK_COMPONENT_SIMONCOMMANDDICTATIONPLUGIN_DEPENDS simon)
set(CPACK_COMPONENT_SIMONCOMMANDEXECUTABLEPLUGIN_DEPENDS simon)
set(CPACK_COMPONENT_SIMONCOMMANDLISTPLUGIN_DEPENDS simon)
set(CPACK_COMPONENT_SIMONCOMMANDINPUTNUMBERPLUGIN_DEPENDS simon)
set(CPACK_COMPONENT_SIMONCOMMANDFILTERPLUGIN_DEPENDS simon)
set(CPACK_COMPONENT_SIMONCOMMANDPRONUNCIATIONTRAININGPLUGIN_DEPENDS simon)
set(CPACK_COMPONENT_SIMONCOMMANDPLACEPLUGIN_DEPENDS simon)
set(CPACK_COMPONENT_SIMONCOMMANDSHORTCUTPLUGIN_DEPENDS simon)
set(CPACK_COMPONENT_SIMONCOMMANDTEXTMACROPLUGIN_DEPENDS simon)
set(CPACK_COMPONENT_SIMON_DEPENDS simoncore)
set(CPACK_COMPONENT_SIMOND_DEPENDS simoncore)
set(CPACK_COMPONENT_KSIMOND_DEPENDS simoncore)
set(CPACK_COMPONENT_SIMONCORE_DEPENDS kdecore )#Devel
SET(CPACK_COMPONENT_SAM_DEPENDS julius kdecore)
SET(CPACK_COMPONENT_SSC_DEPENDS simoncore)
SET(CPACK_COMPONENT_SSCD_DEPENDS simoncore)

SET(CPACK_COMPONENT_SIMONORCONDITIONASSOCIATIONPLUGIN_DEPENDS simon)
SET(CPACK_COMPONENT_SIMONPROCESSOPENEDCONDITIONPLUGIN_DEPENDS simon)
SET(CPACK_COMPONENT_SIMONACTIVEWINDOWPLUGIN_DEPENDS simon)


#set(CPACK_COMPONENT_DEVEL_GROUP "Applications")
set(CPACK_COMPONENT_KDECORE_GROUP "Applications")
SET(CPACK_COMPONENT_JULIUS_GROUP "Applications")
SET(CPACK_COMPONENT_JULIUSDEVEL_GROUP "Development")
SET(CPACK_COMPONENT_KSIMOND_GROUP "Applications")
SET(CPACK_COMPONENT_SAM_GROUP "Applications")
SET(CPACK_COMPONENT_SSC_GROUP "Applications")
SET(CPACK_COMPONENT_SSCD_GROUP "Applications")
SET(CPACK_COMPONENT_AFARAS_GROUP "Applications")
SET(CPACK_COMPONENT_SPEECHCAL_GROUP "Applications")
SET(CPACK_COMPONENT_SIMONSTATUS_GROUP "Applications")
SET(CPACK_COMPONENT_SIMONCOMMANDCALCULATORPLUGIN_GROUP "Commands")
SET(CPACK_COMPONENT_SIMONCOMMANDKEYBOARDPLUGIN_GROUP "Commands")
SET(CPACK_COMPONENT_SIMONCOMMANDCOMPOSITEPLUGIN_GROUP "Commands")
SET(CPACK_COMPONENT_SIMONCOMMANDAIPLUGINAIMLSALICE_GROUP "Commands")
SET(CPACK_COMPONENT_SIMONCOMMANDAIPLUGINAIMLSGERMAN_GROUP "Commands")
SET(CPACK_COMPONENT_SIMONCOMMANDAIPLUGIN_GROUP "Commands")
SET(CPACK_COMPONENT_SIMONCOMMANDLISTPLUGIN_GROUP "Commands")
SET(CPACK_COMPONENT_SIMONCOMMANDDESKTOPGRIDPLUGIN_GROUP "Commands")
SET(CPACK_COMPONENT_SIMONCOMMANDDICTATIONPLUGIN_GROUP "Commands")
SET(CPACK_COMPONENT_SIMONCOMMANDEXECUTABLEPLUGIN_GROUP "Commands")
SET(CPACK_COMPONENT_SIMONCOMMANDLISTPLUGIN_GROUP "Commands")
SET(CPACK_COMPONENT_SIMONCOMMANDINPUTNUMBERPLUGIN_GROUP "Commands")
SET(CPACK_COMPONENT_SIMONCOMMANDFILTERPLUGIN_GROUP "Commands")
SET(CPACK_COMPONENT_SIMONCOMMANDPRONUNCIATIONTRAININGPLUGIN_GROUP "Commands")
SET(CPACK_COMPONENT_SIMONCOMMANDPLACEPLUGIN_GROUP "Commands")
SET(CPACK_COMPONENT_SIMONCOMMANDSHORTCUTPLUGIN_GROUP "Commands")
SET(CPACK_COMPONENT_SIMONCOMMANDTEXTMACROPLUGIN_GROUP "Commands")
SET(CPACK_COMPONENT_SIMON_GROUP "Applications")
SET(CPACK_COMPONENT_SIMONDEVEL_GROUP "Development")
SET(CPACK_COMPONENT_SIMONDOC_GROUP "Documentation")
SET(CPACK_COMPONENT_SIMOND_GROUP "Applications")
SET(CPACK_COMPONENT_SIMONDDEVEL_GROUP "Development")
SET(CPACK_COMPONENT_SIMONCORE_GROUP "Applications")
SET(CPACK_COMPONENT_SIMONCOREDEVEL_GROUP "Development")
SET(CPACK_COMPONENT_TRANSLATIONS_GROUP "Localization")

SET(CPACK_COMPONENT_SIMONORCONDITIONASSOCIATIONPLUGIN_GROUP "Conditions")
SET(CPACK_COMPONENT_SIMONPROCESSOPENEDCONDITIONPLUGIN_GROUP "Conditions")
SET(CPACK_COMPONENT_SIMONACTIVEWINDOWPLUGIN_GROUP "Conditions")


set(CPACK_COMPONENT_GROUP_DEVELOPMENT_DESCRIPTION
   "Development Files (Headers,...)")
set(CPACK_COMPONENT_GROUP_APPLICATIONS_DESCRIPTION
   "Runtime files. You will definitely want those if you want to use Simon / Simond or KSimond.")
set(CPACK_COMPONENT_GROUP_COMMANDS_DESCRIPTION
   "Command Plug-Ins. Those add actions to Simon.")
set(CPACK_COMPONENT_GROUP_DOCUMENTATION_DESCRIPTION
   "Manuals and other documentation.")
set(CPACK_COMPONENT_GROUP_LOCALIZATION_DESCRIPTION
   "Translations and other localization files.")
set(CPACK_COMPONENT_GROUP_CONDITIONS_DESCRIPTION
   "Condition Plug-Ins.  These add context gathering to Simon.")

   
set(CPACK_ALL_INSTALL_TYPES Full User Developer)


#SET(CPACK_COMPONENT_DEVEL_INSTALL_TYPES Full User Devel
SET(CPACK_COMPONENT_KDECORE_INSTALL_TYPES Full User Developer) 	 
SET(CPACK_COMPONENT_JULIUS_INSTALL_TYPES Full User Developer) 	 
SET(CPACK_COMPONENT_JULIUSDEVEL_INSTALL_TYPES Developer) 	 
SET(CPACK_COMPONENT_KSIMOND_INSTALL_TYPES Full User Developer) 	 
SET(CPACK_COMPONENT_SAM_INSTALL_TYPES Full User Developer) 	 
SET(CPACK_COMPONENT_SSC_INSTALL_TYPES Full User Developer) 	 
SET(CPACK_COMPONENT_AFARAS_INSTALL_TYPES Full User Developer) 	 
SET(CPACK_COMPONENT_SSCD_INSTALL_TYPES Full User Developer) 	 
SET(CPACK_COMPONENT_SIMONCOMMANDAIPLUGINAIMLSALICE_INSTALL_TYPES Full User) 	 
SET(CPACK_COMPONENT_SIMONCOMMANDAIPLUGINAIMLSGERMAN_INSTALL_TYPES Full User) 	 
SET(CPACK_COMPONENT_SIMONCOMMANDAIPLUGIN_INSTALL_TYPES Full User) 	 
SET(CPACK_COMPONENT_SIMONCOMMANDCALCULATORPLUGIN_INSTALL_TYPES Full User) 	 

SET(CPACK_COMPONENT_SIMONCOMMANDFILTERPLUGIN_INSTALL_TYPES Full User)
SET(CPACK_COMPONENT_SIMONCOMMANDPRONUNCIATIONTRAININGPLUGIN_INSTALL_TYPES Full User)

SET(CPACK_COMPONENT_SIMONCOMMANDKEYBOARDPLUGIN_INSTALL_TYPES Full User) 	 
SET(CPACK_COMPONENT_SIMONCOMMANDCOMPOSITEPLUGIN_INSTALL_TYPES Full User) 	 
SET(CPACK_COMPONENT_SIMONCOMMANDDESKTOPGRIDPLUGIN_INSTALL_TYPES Full User) 	 
SET(CPACK_COMPONENT_SIMONCOMMANDDICTATIONPLUGIN_INSTALL_TYPES Full User) 	 
SET(CPACK_COMPONENT_SIMONCOMMANDEXECUTABLEPLUGIN_INSTALL_TYPES Full User) 	 
SET(CPACK_COMPONENT_SIMONCOMMANDLISTPLUGIN_INSTALL_TYPES Full User) 	 
SET(CPACK_COMPONENT_SIMONCOMMANDINPUTNUMBERPLUGIN_INSTALL_TYPES Full User) 	 
SET(CPACK_COMPONENT_SIMONCOMMANDPLACEPLUGIN_INSTALL_TYPES Full User) 	 
SET(CPACK_COMPONENT_SIMONCOMMANDSHORTCUTPLUGIN_INSTALL_TYPES Full User) 	 
SET(CPACK_COMPONENT_SIMONCOMMANDTEXTMACROPLUGIN_INSTALL_TYPES Full User) 	 
SET(CPACK_COMPONENT_SIMON_INSTALL_TYPES Full User Developer) 	 
SET(CPACK_COMPONENT_SIMONDEVEL_INSTALL_TYPES Developer) 	 
SET(CPACK_COMPONENT_SIMONDOC_INSTALL_TYPES Full User) 	 
SET(CPACK_COMPONENT_SIMOND_INSTALL_TYPES Full User Developer) 	 
SET(CPACK_COMPONENT_SIMONDDEVEL_INSTALL_TYPES Developer) 	 
SET(CPACK_COMPONENT_SIMONCORE_INSTALL_TYPES Full User Developer) 	 
SET(CPACK_COMPONENT_SIMONCOREDEVEL_INSTALL_TYPES Developer) 	 
SET(CPACK_COMPONENT_TRANSLATIONS_INSTALL_TYPES Full User) 	 
SET(CPACK_COMPONENT_SPEECHCAL_INSTALL_TYPES Full) 	 
SET(CPACK_COMPONENT_SIMONSTATUS_INSTALL_TYPES Full) 	 

SET(CPACK_COMPONENT_SIMONORCONDITIONASSOCIATIONPLUGIN_GROUP Full User)
SET(CPACK_COMPONENT_SIMONPROCESSOPENEDCONDITIONPLUGIN_GROUP Full User)
SET(CPACK_COMPONENT_SIMONACTIVEWINDOWPLUGIN_GROUP Full User)
 
#SET(CPACK_COMPONENT_DEVEL_REQUIRED) 	 
SET(CPACK_COMPONENT_KDECORE_REQUIRED) 	 
SET(CPACK_COMPONENT_SIMONCORE_REQUIRED) 	 
SET(CPACK_COMPONENT_SIMONCOMMANDAIPLUGIN_DISABLED) 	 
SET(CPACK_COMPONENT_SIMONCOMMANDAIPLUGINAIMLSALICE_DISABLED) 	 
SET(CPACK_COMPONENT_SIMONCOMMANDAIPLUGINAIMLSGERMAN_DISABLED) 	 
 
 
SET(CPACK_NSIS_MUI_ICON "${CMAKE_CURRENT_SOURCE_DIR}\\\\simon.ico") 	 
 
IF(WIN32 AND NOT UNIX) 	 
	# There is a bug in NSI that does not handle full unix paths properly. Make 	 
	# sure there is at least one set of four (4) backlasshes. 	 
	SET(CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}\\\\installbanner.bmp") 	 
	#SET(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\simon.exe") 	 
	SET(CPACK_NSIS_INSTALLER_ICON "${CMAKE_CURRENT_SOURCE_DIR}\\\\simon.ico") 	 
	SET(CPACK_NSIS_MUI_ICON "${CMAKE_CURRENT_SOURCE_DIR}\\\\simon.ico") 	 
	SET(CPACK_NSIS_MUI_UNIICON "${CMAKE_CURRENT_SOURCE_DIR}\\\\simon.ico") 	 
	SET(CPACK_NSIS_COMPRESSOR "/SOLID lzma") 	 
	 
	SET(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY}") 	 
	SET(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.simon-listens.org/wiki") 	 
	SET(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.simon-listens.org") 	 
	SET(CPACK_NSIS_CONTACT "support@simon-listens.org") 	 
	SET(CPACK_NSIS_MODIFY_PATH ON) 	 
	 
	SET(CPACK_NSIS_CREATE_ICONS_EXTRA "CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\simon.lnk\\\" \\\"$INSTDIR\\\\bin\\\\simon.exe\\\" \\\"\\\" \\\"$INSTDIR\\\\bin\\\\simon.exe\\\" 0 	 
	CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\simond.lnk\\\" \\\"$INSTDIR\\\\bin\\\\simond.exe\\\" \\\"\\\" \\\"$INSTDIR\\\\bin\\\\simond.exe\\\" 0 	 
	CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\ksimond.lnk\\\" \\\"$INSTDIR\\\\bin\\\\ksimond.exe\\\" \\\"\\\" \\\"$INSTDIR\\\\bin\\\\ksimond.exe\\\" 0
	
	CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\sam.lnk\\\" \\\"$INSTDIR\\\\bin\\\\sam.exe\\\" \\\"\\\" \\\"$INSTDIR\\\\bin\\\\sam.exe\\\" 0 	 
	CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\ssc.lnk\\\" \\\"$INSTDIR\\\\bin\\\\ssc.exe\\\" \\\"\\\" \\\"$INSTDIR\\\\bin\\\\ssc.exe\\\" 0 	 
	CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\sscd.lnk\\\" \\\"$INSTDIR\\\\bin\\\\sscd.exe\\\" \\\"\\\" \\\"$INSTDIR\\\\bin\\\\sscd.exe\\\" 0 	 
	CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\afaras.lnk\\\" \\\"$INSTDIR\\\\bin\\\\afaras.exe\\\" \\\"\\\" \\\"$INSTDIR\\\\bin\\\\afaras.exe\\\" 0 	 
	") 	 
	 
	 
	 
   SET(CPACK_NSIS_DELETE_ICONS_EXTRA " 	 
	 !insertmacro MUI_STARTMENU_GETFOLDER Application $MUI_TEMP 	 
	 Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\simon.lnk\\\" 	 
	 Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\simond.lnk\\\" 	 
	 Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\ksimond.lnk\\\" 	 
	 Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\sam.lnk\\\" 	 
	 Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\ssc.lnk\\\" 	 
	 Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\sscd.lnk\\\" 	 
	 Delete \\\"$SMPROGRAMS\\\\$MUI_TEMP\\\\afaras.lnk\\\" 	 
	 ") 	 
ENDIF(WIN32 AND NOT UNIX) 	 
 
SET(CPACK_PACKAGE_EXECUTABLES "simon" "simon")

include(CPack)
