/**
 * File: AVRTab.h
 * @class AVRTab, inherits from QWidget
 * @author Ben Porter
 * @author Michael Spray (spraym@onid.orst.edu)
 *
 * To learn more about the Tekbots program: http://www.eecs.oregonstate.edu/tekbots.html
 *
 * @brief This file contains the appropriate definitions for variables and
 * functions that set up a widget for handling AVRDUDE options and setup for 
 * programming Atmel products.  The Avr Tab is added to the MainWindow
 */
 

#ifndef AVRTAB_H
#define AVRTAB_H

#include <QtCore/QVariant>
#include <QtGui/QWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QGroupBox>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QProcess>
#include <QProgressBar>
#include <QPushButton>
#include <QRadioButton>
#include <QTextEdit>
#include <QListWidget>
#include <sstream>
#include "Message.h"
#include "Config.h"

#define STATE_IDLE 1
#define STATE_IDENTIFY 2
#define STATE_ID_FOUND 3
#define STATE_PROGRAMMING 4
#define STATE_ERASE 5
#define STATE_VERIFY_ERASE 6
#define STATE_READING_LOCK 7
#define STATE_READING_FUSE 8

using namespace std;

//other classes we'll be using
class QCheckBox;
class QComboBox;
class QGroupBox;
class QLineEdit;
class QProgressBar;
class QPushButton;
class QRadioButton;
class QTextEdit;

//class definition
class AVRTab : public QWidget
{
	//set this as an object
	Q_OBJECT
	
public:

	AVRTab(Config *c);
	~AVRTab();
	
	// Returns the main widget
	QWidget *getWidget();
	
	// Set the temporary directory
	void setTempDir(QString);
	
	// Called externally on config change
	void updateOptions(); 
	
// Callbacks for Qt events
public slots:

	// Button Callbacks
	void browse4Flash();
	void browse4EEPROM();
	void avrIdentify();
	void resetAVRChip();
	
	void ScanFlashAVRChip();
	void ScanEEPROM();
	void ScanFuseBits();
	void ScanLockBits();
	
	void programFlashAVRChip();
	void programEEPROMAVRChip();
	void programFuseAVRChip();
	void programBootAVRChip();
	
	// Group Box Checked/Unchecked Callbacks
	void enableOrDisableFlash(bool state);
	void enableOrDisableEEPROM(bool state);
	void enableOrDisableFuseBits(bool state);
	void enableOrDisableLockBits(bool state);
	
	//updates the "EESAVE" fuse bit
	void updatePreserveEEPROM(bool);
	
	// Combo box selection changed callbacks
	void ProgrammerSelectionChanged(int);
	void changedDevice(int);
	
	//updates the LB1 and LB2 bits in the Boot Lock Bits section
	void flashLockBitsChange();
	
	// Called when the AvrDude process completes
	void programAVRStatus(int, QProcess::ExitStatus);
	
	// Called when there is STDOUT or STDERR from the AvrDude process
	void programAVROutput();

private:
	/*Methods*/
	//changes the layout of the fuse group
	void changeFuseGroup();
	//changes the layout of the lock group
	void changeLockGroup();
	//programs the avr chip given a command string (QString), returns a completion code
	int programAVRChip(QString);
	//checks that a chip erase finished correctly
	void checkEraseGood();
	
	// Reconstruct the programmer box based on the selected programmer
	void PopulateProgrammerBox();

	int GetProgrammerOptions(string &s);
	int GetPartOptions(string &s);

	// Helper function for processing avrdude output
	void ProcessOutputLine(QString currentOutput);
	
	// Read and load data from the temporary files created by AvrDude on fuse/lock read
	void ReadFuseByteFile();
	void ReadLockByteFile();
	
	// Helper function for fuse/lock bit verification
	int ReadByteFromFile(QString fileName, char &outChar);
	
	/* Variables */
	
	QWidget		*avr;
	QVBoxLayout * avr_master;
	QHBoxLayout * EEPROMandFlash;
	QHBoxLayout * Chip;
	QHBoxLayout * ProgrammerBox;

	// Currently selected avr part and programmer
	Part part;
	Programmer programmer;
	
	// Pointer to the configuration supplied by the main window
	Config *config;

	Message	*mess;
	
	//the process that runs avrdude
	QProcess *runAVRDUDE;
	QTextEdit	*avrdudeOutput;
	QProgressBar *avrdudeProgress;
	
	// Flash Group Box Items
	QGroupBox	*flashboxGroup;
	QLineEdit	*flashFileOutput;
	QPushButton	*flashFileBrowse;
	QPushButton *scanFlash;
	QPushButton *programFlash;
	
	// EEPROM Group Box Items
	QGroupBox * EEPROMboxGroup;
	QLineEdit	*EEPROMFileOutput;
	QPushButton	*EEPROMFileBrowse;
	QPushButton *scanEEPROM;
	QPushButton *programEEPROM;
	bool eepromCanSave;
	
	// Chip Group Box Items
	QGroupBox *programmerGroupBox;
	QComboBox   *AVRMods;
	QPushButton *AVRIdentify;
	QPushButton *eraseAVR;
	QComboBox	*AVRProgrammers;
	QComboBox	*AVRProgPorts;
	QCheckBox	*checkSig, *checkErase, *preserveEEP, *checkVerify; // More Options
	
	// Fuse Byte Group
	QGroupBox *fuseGroup;
	QPushButton *scanFuseBits;
	QListWidget * fuseListWidget;
	QPushButton *programFuseBits;
	
	// Lock Byte Group
	QGroupBox *bootlockbitsGroup;
	QListWidget * lockListWidget;
	QPushButton *scanLockBits;
	QPushButton *programBootBits;
	QRadioButton *noProtect, *progDisabled, *ProgANDVerDisabled;

	// Temporary directory for files
	QString	tempDir;
	
	// Folder for saving/loading files from
	QString folderRoot;
	
	// Variables for watching avrdude text output
	QString avrdudeOutputText;
	bool isProgressing;
	int state; // State of the programmer (used by process output watching methods)

};
#endif
