/**
 * File: MainWindow.h
 * @class MainWindow, extends QMainWindow
 * @author Michael Spray (spraym@onid.orst.edu)
 * @author Ben Porter
 * NOTE: For a description of how the class operates, please see the corresponding
 * cpp file.
 *
 * To learn more about the Tekbots program: http://www.eecs.oregonstate.edu/tekbots.html
 *
 * Description: This file contains the appropriate definitions for variables and
 * functions that drive the MainWindow class.
 */
//make sure we only include this once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include <QtGui/QWidget>
#include <QAction>
#include <QTabWidget>
#include <fstream>
#include <iostream>
#include "AVRTab.h"
#include "JTAGTab.h"
#include "Message.h"
#include "config.h"

using namespace std;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	//constructor
	MainWindow();
	//destructor
	~MainWindow();
	//called when the window is about to be closed (this is where you will want to destruct tabs)
	void closeEvent(QCloseEvent *);
	//returns the temporary folder [depreciated]
	QString getTempDir();
protected:
private slots:
	void tabChanged(int index);
	//opens up a change directory dialog that allows the user to select a different temporary directory
	void changeTempDir();
	void changeOptionsItemClicked();
private:
	/*Methods*/
	//set up the menu actions in this method
	void createActions();
	//set up the top menu and add the above actions to the menu
	void createMenu();
	
	/*Variables*/
	Config config;
	//the location of our temporary folder
	QString tempDir;
	//points to each screen via the tab (see MainWindow.cpp)
	QTabWidget	*programTabs;
	//our AVR_ISP screen
	AVRTab *avr;
	//our JTAG Screen
	JTAGTab *jtag;
	//a general dialog box
	Message *mess;
	//the file menu at the top of the window
	QMenu	*fileMenu;
	QMenu	*optionsMenu;
	Options originalOptions;
	//menu action that allows the user to change the temporary directory
	QAction *newTempDir;
	
	QAction *changeOptionsItem;
};
#endif
