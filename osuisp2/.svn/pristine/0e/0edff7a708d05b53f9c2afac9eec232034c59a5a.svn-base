/**
 * File: MainWindow.cpp
 * @class MainWindow
 * @author Ben Porter
 * @author Michael Spray (spraym@onid.orst.edu)
 *
 * To learn more about the Tekbots program: http://www.eecs.oregonstate.edu/tekbots.html
 *
 * Description: The general theory behind this program is that you write your own
 * Qt widget in another file (see AVRTab.h and AVRTab.cpp for an example) and merely
 * add that widget to the programTabs QTabWidget object.  This allows for ease of
 * extending the program and makes the code considerably less cluttered.  
 */
#include <QtGui>
#include "MainWindow.h"

/**
 * @brief Construct the main window, load the configuration, and create tabs.
 *
 */
MainWindow::MainWindow()
{
	this->resize(QSize(640, 620).expandedTo(this->minimumSizeHint()));
	this->setMinimumSize(640, 620);
	this->setWindowTitle(QString("Tekbots Universal Programmer v3.1"));
	this->setWindowIcon(QIcon(QString("./icons/tekbot.png")));
	
	// Make it so you can call MainWindow->update()
	this->setUpdatesEnabled(true);
	
	// Set the temporary directory (used for storing temp files)
	// User must have read/write permission to this location
	tempDir = QDir::tempPath();
	
	//set up our master widget, which holds each Window
	programTabs = new QTabWidget(this);
	
	// config.load(); // TODO: Make a load method in the config class! Right now, it's all in the constructor...
	
	// Setup AVR tab
	avr = new AVRTab(&config);
	avr->setTempDir(tempDir);
	programTabs->addTab(avr->getWidget(),QString("AVR"));
	
	jtag = new JTAGTab();
	jtag->SetTempDir(tempDir);
	programTabs->addTab(jtag->getWidget(),QString("JTAG"));
	
	connect(programTabs,SIGNAL(currentChanged(int)),this,SLOT(tabChanged(int)));	
	programTabs->setCurrentWidget(avr);
	this->setCentralWidget(programTabs);

	//create the actions for the menu for the Main Window
	createActions();
	
	//create the menu for the Main Window
	createMenu();

	return;
}

/**
 * Destructor
 */
MainWindow::~MainWindow()
{
}	

/**
 * Called when a tab changes.
 * Used by the tabs to stop any running processes
 * (however, the user shouldn't be allowed to change tabs when there is a process running...)
 */
void MainWindow::tabChanged(int index)
{
	// Todo: allow tabs to disable tab change
	jtag->tabChanged(index);
}


/**
 * @brief Called on window close.  Be sure to destroy all
 * allocated objects here.
 */
void MainWindow::closeEvent(QCloseEvent *event)
{
	avr->~AVRTab();
	jtag->~JTAGTab();
	programTabs->~QTabWidget();
	QApplication::exit();
}

/**
 * @brief Creates the menu items for the main window (file, options, etc)
 */
void MainWindow::createActions()
{
	//create an action that allows the user to change the temporary directory
	newTempDir = new QAction(QIcon("./icons/folder.png"), tr("Change &Temp Dir"), this);
	
	//set keyboard shortcut for changing the temporary directory
	newTempDir->setShortcut(tr("Ctrl+T"));
    //set the status tip to show the below
	newTempDir->setStatusTip(tr("Change the temporary directory"));
    //actually connect this to a method
	connect(newTempDir, SIGNAL(triggered()), this, SLOT(changeTempDir()));
	
	changeOptionsItem = new QAction(tr("Enable Advanced Options"), this);
	changeOptionsItem->setStatusTip(tr("Enable advanced programming options"));
	connect(changeOptionsItem, SIGNAL(triggered()), this, SLOT(changeOptionsItemClicked()));
	return;
}

/**
 * Used to notify tabs of a configuration change
 */
void MainWindow::changeOptionsItemClicked()
{
	if (changeOptionsItem->text().contains("Enable"))
	{
		originalOptions = config.options;
		config.options.flash = true;
		config.options.eeprom = true;
		config.options.lockBits = true;
		config.options.fuseBits = true;
		changeOptionsItem->setText("Disable Advanced Options");
		changeOptionsItem->setStatusTip(tr("Disable advanced programming options"));
	}
	else
	{
		config.options = originalOptions;
		changeOptionsItem->setText("Enable Advanced Options");
		changeOptionsItem->setStatusTip(tr("Enable advanced programming options"));
	}
	avr->updateOptions();
}

/**
 * @brief Creates the menus for the Main Window
 */
void MainWindow::createMenu()
{
	//create the menu
	//creates a "File Menu"
	fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newTempDir);
	
	optionsMenu = menuBar()->addMenu(tr("Options"));
	optionsMenu->addAction(changeOptionsItem);
	//show the statu menu at the bottom
	statusBar()->show();
}
	
/**
 * @brief Allows the user to change the current temporary directory
 */
void MainWindow::changeTempDir()
{
	//create a new file dialog box and get the user's selection
	QString curTemp = QFileDialog::getExistingDirectory(this,"Select a temporary folder to use...",tempDir,QFileDialog::ShowDirsOnly);
	//make sure we actually got something useful back
	if(!(curTemp.isEmpty() || curTemp.isNull())){
		//update the temporary folder
		tempDir = curTemp;
		//set the temporary directory for the avr tab
		avr->setTempDir(tempDir);
		jtag->SetTempDir(tempDir);
		//ADD ANY OTHER SET TEMP DIRECTORIES HERE
	}
	return;
}

/**
 * @brief Accessor method for the temp directory
 * @return The currently selected temporary directory
 */
QString MainWindow::getTempDir()
{
	return tempDir;	
}
