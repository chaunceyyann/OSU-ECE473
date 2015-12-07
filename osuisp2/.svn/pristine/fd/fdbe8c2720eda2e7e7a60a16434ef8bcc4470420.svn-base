#
#  Copyright (C) 2009 TekBots
# 
#   This program is free software; you can redistribute it and/or modify it under the 
#   terms of the GNU General Public License as published by the Free Software Foundation;
# 	either version 2 of the License, or (at your option) any later version.
# 
#   This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
# 	without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
# 	See the GNU General Public License for more details.
# 
#   You should have received a copy of the GNU General Public License along with this program;
# 	if not, write to the 
# 	Free Software Foundation, Inc., 
# 	59 Temple Place, Suite 330, 
# 	Boston, MA 02111-1307 USA
# 
#   Written by Jace Akerlund (akerlunj@onid.orst.edu)
#   Distributed by: TekBots  (TekBots@eecs.oregonstate.edu)
# 


TEMPLATE = app
TARGET = Universal_GUI
DEPENDPATH += . include src
INCLUDEPATH += . include
RC_FILE = icon.rc
CONFIG += release

win32 {

dllLocation = $$(QTDIR)\bin

dll.files += $$dllLocation\mingwm10.dll 
dll.files += $$dllLocation\QtCore4.dll 
dll.files += $$dllLocation\QtGui4.dll

#to make testing and packaging easier in windows
target.path = .\win_Installer\UniversalGUI
dll.path = .\win_Installer\UniversalGUI
INSTALLS += target dll

#Developers only, provides terminal output
#CONFIG += console
}

!win32 {
target.path = /usr/bin/
icons.files = ./icons/*.png
icons.path = /usr/share/universal_gui
shortcut.files = universal_gui.desktop
shortcut.path = /usr/share/applications
INSTALLS += target icons shortcut
}

# Input
HEADERS += include/AVRTab.h \
           include/MainWindow.h \
           include/Message.h \
		   include/JTAGTab.h \
		   include/Config.h
SOURCES += main.cpp \
           src/AVRTab.cpp \
           src/MainWindow.cpp \
           src/Message.cpp \
		   src/JTAGTab.cpp \
		   rapidXml/rapidxml.hpp \
		   src/Config.cpp
		   
