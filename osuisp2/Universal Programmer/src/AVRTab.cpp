/**
 * File: AVRTab.cpp
 * @class AVRTab
 * @author Ben Porter
 * @author Michael Spray (spraym@onid.orst.edu)
 * @author Jace Akerlund (akerlunj@onid.orst.edu)
 *
 * To learn more about the Tekbots program: http://www.eecs.oregonstate.edu/tekbots.html
 *
 * @brief
 * The AVR tab provides an intuitive interface to the command line Avrdude program.  The
 * GUI elements (layout, arrangement) and GUI logic (button presses, etc) are included in
 * this file.
 */
 
#include <QtGui>
#include "AVRTab.h"
#include <windows.h>

AVRTab::AVRTab(Config * c)
{
	runAVRDUDE = NULL;
	
	if (c!=NULL)
	{
		config = c;
	}
		
	//set up the AVR_ISP screen, don't set a parent, that gets set later
	avr = new QWidget();

	//create this so we can relay messages to the user through a dialog
	mess = new Message();
		
	//make sure we have at least one avr chip model and programmer defined
	if(config->parts.size() == 0){
		mess->changeMessage(*(new QString("No AVR Parts Defined! Cannot Create AVR Tab")));
		mess->show();
		return;
	}
	if(config->programmers.size() == 0){
		mess->changeMessage(*(new QString("No AVR Programmers Defined! Cannot Create AVR Tab")));
		mess->show();
		return;
	}
	
	part = config->parts[0];

	tempDir = QDir::tempPath();
	folderRoot = QDir::homePath();
	
	//master AVRISP layout box
	avr_master = new QVBoxLayout(avr);
	
	//get the EEPROM and flash together horizontally
	EEPROMandFlash = new QHBoxLayout(avr);
	
	//set up the Chip section
	Chip = new QHBoxLayout(avr);
	
	//set up the programmer section
	ProgrammerBox = new QHBoxLayout(avr);
	

	
	/*
	 *CREATE "Programmer" GROUP
	 */
	//{ <-Folding!
	// set up the bindingh box for the programmer section
	programmerGroupBox = new QGroupBox("&Programmer",avr);
	programmerGroupBox->setCheckable(false); // do not let it be checkable
	QVBoxLayout * programmerLabelOptionPair = new QVBoxLayout(avr);
	
	
	// set up the programmer selection combo box
	int commonCount = 0;
	AVRProgrammers = new QComboBox(programmerGroupBox);
	for(size_t i = 0; i<config->programmers.size(); i++)
	{
		if (config->programmers[i].isCommon.compare("yes")==0)
		{
			AVRProgrammers->addItem(*(new QString(config->programmers[i].name.c_str())));
			commonCount++;
		}
		else
		{
			AVRProgrammers->insertItem(AVRProgrammers->count(), *(new QString(config->programmers[i].name.c_str())));
		}
	}
	
	AVRProgrammers->insertSeparator(commonCount);
	AVRProgrammers->setEditable(false); // do not let the user modify the list
	
	programmerLabelOptionPair->addWidget(new QLabel("Programmer",programmerGroupBox)); // Add the label
	programmerLabelOptionPair->addWidget(AVRProgrammers); // Add the selection

	// Update the programmer params when a new programmer is selected
	connect(AVRProgrammers,SIGNAL(currentIndexChanged(int)),this,SLOT(ProgrammerSelectionChanged(int)));

	ProgrammerBox->addLayout(programmerLabelOptionPair);
	
	// Populate the remainder of the box with param options for the selected programmer (defined in configuration file)
	PopulateProgrammerBox();

	//update the group box
	programmerGroupBox->setLayout(ProgrammerBox);
	programmerGroupBox->show();
	//add the Programmer layout to the master layout
	avr_master->addWidget(programmerGroupBox);
	//}
	
	
	/*
	 *CREATE "Chip" GROUP
	 */
	//{ <-Folding!
	//create a binding box for chip section
	QGroupBox *chipboxGroup	= new QGroupBox("&Chip",avr);
	//do not let it be checkable
	chipboxGroup->setCheckable(false);
	//set up the combo box that lists each model item
	AVRMods = new QComboBox(chipboxGroup);
	
	for(size_t i = 0; i<config->parts.size(); i++)
	{
		AVRMods->addItem(config->parts[i].name.c_str());
		
	}
	
	// Option check boxes
	checkSig = new QCheckBox("Skip Signature Check",avr);
	checkErase = new QCheckBox("Check Erasure",avr);
	checkVerify = new QCheckBox("Skip Verify",avr);
//	verbosity = new QCheckBox("Verbose",avr);
	QLabel * optionsLabel = new QLabel("Options:", avr);
	QHBoxLayout * optionCheckBoxes = new QHBoxLayout(avr);
	
	optionCheckBoxes->addWidget(optionsLabel);
	
optionCheckBoxes->addSpacing(50);
	optionCheckBoxes->addWidget(checkSig);
//	optionCheckBoxes->addWidget(verbosity);
	optionCheckBoxes->addWidget(checkVerify);
	optionCheckBoxes->addWidget(checkErase);	
	
	optionCheckBoxes->addStretch();
	
	
	
	//do not let the user modify the list
	AVRMods->setEditable(false);
	//set up the signals/slots when the user selects another device, the screen is updated
	connect(AVRMods,SIGNAL(currentIndexChanged(int)),this,SLOT(changedDevice(int)));
	//Add the Model box to the chip section
	Chip->addWidget(AVRMods);
	//put some space between chip select and next widget(s)
	Chip->addSpacing(50);
	//set up the button that allows for identifying the chip
	AVRIdentify = new QPushButton(*(new QString("Identify")),chipboxGroup);
	AVRIdentify->setEnabled(true);
	connect(AVRIdentify,SIGNAL(clicked()),this,SLOT(avrIdentify()));
	Chip->addWidget(AVRIdentify);
	//add button that allows for scanning the chip
//	scanAVR = new QPushButton(*(new QString("Scan Chip")),chipboxGroup);
//	scanAVR->setEnabled(true);
//	connect(scanAVR,SIGNAL(clicked()),this,SLOT(scanAVRChip()));
//	Chip->addWidget(scanAVR);
	//add button that allows for reseting (erasing) the chip
	eraseAVR = new QPushButton(*(new QString("Erase Chip")),chipboxGroup);
	eraseAVR->setEnabled(true);
	connect(eraseAVR,SIGNAL(clicked()),this,SLOT(resetAVRChip()));
	Chip->addWidget(eraseAVR);
	
	QVBoxLayout * chipVerticalLayout = new QVBoxLayout(avr);
	chipVerticalLayout->addLayout(Chip);
	chipVerticalLayout->addLayout(optionCheckBoxes);
	//update the group box
	chipboxGroup->setLayout(chipVerticalLayout);
	chipboxGroup->show();
	//Add the chip section to the overall layout
	avr_master->addWidget(chipboxGroup);
	//}
	

	// Columns for programming options
	QVBoxLayout * columnOne = new QVBoxLayout(avr);
	QVBoxLayout * columnTwo = new QVBoxLayout(avr);
	QVBoxLayout * columnThree = new QVBoxLayout(avr);
	QHBoxLayout * holdsColumnedItems = new QHBoxLayout(avr);
	avr_master->addLayout(holdsColumnedItems);
	holdsColumnedItems->addLayout(columnOne);
	holdsColumnedItems->addLayout(columnTwo);
	holdsColumnedItems->addLayout(columnThree);
	
	/*
	 *CREATE "Flash" GROUP
	 */
	//{ <-Folding!
	//create a layout box for hoizontally holding button and text field together for both flash and EEPROM


	// Create the file path viewer
	flashFileOutput = new QLineEdit(avr);
	flashFileOutput->setReadOnly(true);
	flashFileOutput->insert(*(new QString("")));
	flashFileOutput->setEnabled(false);
	
	// Create the browse button
	flashFileBrowse = new QPushButton(QString("Browse"),avr);
	flashFileBrowse->setMaximumSize(100, 30);
	flashFileBrowse->setEnabled(false);
	connect(flashFileBrowse,SIGNAL(clicked()),this,SLOT(browse4Flash()));//connect the signal to the parent
	
	// Create the flash write button
	programFlash = new QPushButton("Write Flash",avr);
	programFlash->setMaximumSize(100, 30);
	programFlash->setEnabled(false);
	connect(programFlash,SIGNAL(clicked()),this,SLOT(programFlashAVRChip()));
	
	// Create the scan flash button
	scanFlash = new QPushButton("Scan",avr);
	scanFlash->setMaximumSize(100, 30);
	scanFlash->setEnabled(false);
	connect(scanFlash,SIGNAL(clicked()),this,SLOT(ScanFlashAVRChip()));
	
	// Horizontal box layout for the browse and scan buttons
	QHBoxLayout * flashButtonsBox = new QHBoxLayout(avr);
	flashButtonsBox->addWidget(flashFileBrowse);
	flashButtonsBox->addWidget(scanFlash);
	flashButtonsBox->addStretch(); // And push them to the side
	
	// Vertical layout from browse box and buttons
	QVBoxLayout * flashVerticalBox = new QVBoxLayout(avr);
	flashVerticalBox->addWidget(flashFileOutput);
	flashVerticalBox->addLayout(flashButtonsBox);
	flashVerticalBox->addStretch();
	flashVerticalBox->addWidget(programFlash);
	
	// Create the group box to hold all the flash related elements created above
	flashboxGroup = new QGroupBox("&Flash",avr);
	flashboxGroup->setCheckable(true); // make it checkable (for enabling/disabling)
	flashboxGroup->setChecked(false);
	flashboxGroup->setLayout(flashVerticalBox);
	
	if (config->options.flash)
		flashboxGroup->show();
	else
		flashboxGroup->hide();
	
	columnOne->addWidget(flashboxGroup);
	//}
	
	/*
	 *CREATE "EEPROM" GROUP
	 */
	//{ <-Folding!
	//create a new binding box group

	
	// EEPROM Text Field
	EEPROMFileOutput = new QLineEdit(avr);
	EEPROMFileOutput->setReadOnly(true); // set it to read only and clear the contents
	EEPROMFileOutput->insert(*(new QString("")));
	EEPROMFileOutput->setEnabled(false);
	
	// EEPROM Browse Button
	EEPROMFileBrowse = new QPushButton(*(new QString("Browse")),avr);
	EEPROMFileBrowse->setMaximumSize(100, 30);
	connect(EEPROMFileBrowse,SIGNAL(clicked()),this,SLOT(browse4EEPROM()));
	EEPROMFileBrowse->setEnabled(false);
	
	// Program EEPROM Button
	programEEPROM = new QPushButton("Write EEPROM",avr);
	programEEPROM->setMaximumSize(100, 30);
	connect(programEEPROM,SIGNAL(clicked()),this,SLOT(programEEPROMAVRChip()));
	programEEPROM->setEnabled(false);
	
	// scan EEPROM Button
	scanEEPROM = new QPushButton(*(new QString("Scan")),avr);
	scanEEPROM->setMaximumSize(100, 30);
	connect(scanEEPROM,SIGNAL(clicked()),this,SLOT(ScanEEPROM()));
	scanEEPROM->setEnabled(false);
	
	QHBoxLayout * eepromButtonsBox = new QHBoxLayout(avr);
	eepromButtonsBox->addWidget(EEPROMFileBrowse);
	eepromButtonsBox->addWidget(scanEEPROM);
	eepromButtonsBox->addStretch();
	
	QVBoxLayout * eepromVerticalBox = new QVBoxLayout(avr);
	eepromVerticalBox->addWidget(EEPROMFileOutput); // Browse and show on top
	eepromVerticalBox->addLayout(eepromButtonsBox);
	eepromVerticalBox->addStretch(); // Push the program button to the bottom
	eepromVerticalBox->addWidget(programEEPROM);
	
	EEPROMboxGroup = new QGroupBox("&EEPROM",avr);
	EEPROMboxGroup->setLayout(eepromVerticalBox);
	EEPROMboxGroup->setCheckable(true);
	EEPROMboxGroup->setChecked(false);
	
	if (config->options.eeprom)
		EEPROMboxGroup->show();
	else
		EEPROMboxGroup->hide();
	
	columnOne->addWidget(EEPROMboxGroup);
	avr_master->addLayout(EEPROMandFlash);
	//}
	
	/*
	 *CREATE "Options" GROUP and rest of the Bottom half of the AVR Screen
	 */
	
	QHBoxLayout *optionsANDfuse = new QHBoxLayout(avr);
	QHBoxLayout *options = new QHBoxLayout(avr);
	QHBoxLayout *checkANDboot = new QHBoxLayout(avr);

	/*
	 *CREATE "Boot Lock Bits" GROUP
	 */
	//{ <-Folding!
	
	// List to hold the lock bit checkbox/item pairs
	lockListWidget = new QListWidget();
	lockListWidget->setEnabled(false);
	
	// Program Lock Bits Button
	programBootBits = new QPushButton("Write Lock Bits",avr);
	connect(programBootBits,SIGNAL(clicked()),this,SLOT(programBootAVRChip()));
	programBootBits->setEnabled(false);
	
	scanLockBits = new QPushButton("Scan",avr);
	connect(scanLockBits,SIGNAL(clicked()),this,SLOT(ScanLockBits()));
	scanLockBits->setEnabled(false);
	
	// Radio buttons for easier control of the reprogrammable lock bits
	noProtect = new QRadioButton("Keep device programmable",this);
	noProtect->toggle(); // Select noProtect by default
	progDisabled = new QRadioButton("Disable future programming",this);
	ProgANDVerDisabled = new QRadioButton("Disable future programming and verification",this);
	connect(noProtect,SIGNAL(clicked()),this,SLOT(flashLockBitsChange()));
	connect(progDisabled,SIGNAL(clicked()),this,SLOT(flashLockBitsChange()));
	connect(ProgANDVerDisabled,SIGNAL(clicked()),this,SLOT(flashLockBitsChange()));
	
	// Layout for list and button
	QVBoxLayout * lockGroupLayout = new QVBoxLayout(avr);
	lockGroupLayout->addWidget(lockListWidget);
	lockGroupLayout->addWidget(noProtect);
	lockGroupLayout->addWidget(progDisabled);
	lockGroupLayout->addWidget(ProgANDVerDisabled);
	QHBoxLayout * lockButtonGroup = new QHBoxLayout(avr);
	lockButtonGroup->addWidget(programBootBits);
	lockButtonGroup->addWidget(scanLockBits);
	lockGroupLayout->addLayout(lockButtonGroup);
	
	//set up the boot bits section, first the binding box
	bootlockbitsGroup = new QGroupBox("Program &Lock Bits",avr);
	bootlockbitsGroup->setCheckable(true);
	bootlockbitsGroup->setChecked(false);
	bootlockbitsGroup->setLayout(lockGroupLayout);
	connect(bootlockbitsGroup,SIGNAL(toggled(bool)),this,SLOT(enableOrDisableLockBits(bool)));
	if (config->options.lockBits)
		bootlockbitsGroup->show();
	else
		bootlockbitsGroup->hide();

	//set up the check boxes
	changeLockGroup();
	checkANDboot->addSpacing(20);
	columnThree->addWidget(bootlockbitsGroup);
	options->addLayout(checkANDboot);
	//}
	
	/*
	 *CREATE "Fuse" GROUP
	 */
	//{ <-Folding!
	
	fuseListWidget = new QListWidget(avr);
	fuseListWidget->setEnabled(false);
	
	// Program Fuse Bits Button
	programFuseBits = new QPushButton("Write Fuse Bits",avr);
	connect(programFuseBits,SIGNAL(clicked()),this,SLOT(programFuseAVRChip()));
	programFuseBits->setEnabled(false);
	
	// Program Fuse Bits Button
	scanFuseBits = new QPushButton("Scan",avr);
	connect(scanFuseBits,SIGNAL(clicked()),this,SLOT(ScanFuseBits()));
	scanFuseBits->setEnabled(false);
	
	// Preserve EEPROM check box
	preserveEEP = new QCheckBox("Preserve EEPROM (fuse bit)",avr);
	connect(preserveEEP,SIGNAL(toggled(bool)),this,SLOT(updatePreserveEEPROM(bool)));
	
	// Layout for list and button
	QVBoxLayout * fuseGroupLayout = new QVBoxLayout(avr);
	fuseGroupLayout->addWidget(fuseListWidget);
	fuseGroupLayout->addWidget(preserveEEP);
	//QHBoxLayout * fuseButtonBox = new QHBoxLayout(avr);
	fuseGroupLayout->addWidget(scanFuseBits);
	//fuseButtonBox->addWidget(programFuseBits);
	fuseGroupLayout->addWidget(programFuseBits);
	//fuseGroupLayout->addLayout(fuseButtonBox);
	
	// The group box which holds the list, button, and layout
	fuseGroup = new QGroupBox("Program F&use Bits",avr);
	fuseGroup->setCheckable(true);
	fuseGroup->setChecked(false);
	fuseGroup->setLayout(fuseGroupLayout);
	connect(fuseGroup,SIGNAL(toggled(bool)),this,SLOT(enableOrDisableFuseBits(bool)));
	if (config->options.fuseBits)
		fuseGroup->show();
	else
		fuseGroup->hide();

columnTwo->addWidget(fuseGroup);
	
	// Calling this function will set up the checkboxes (normally called on part selection change)
	changeFuseGroup();
	
	//update the options and fuses area
	optionsANDfuse->addLayout(options);
	

//	optionsANDfuse->addWidget(fuseGroup);
//	optionsboxGroup->setLayout(optionsANDfuse);

	//}
	
	/*
	 *CREATE "Output" GROUP
	 */
	//{ <-Folding!
	//create the output area, first creating the binding box
	QHBoxLayout *VeryBottom = new QHBoxLayout(avr);
	QGroupBox *outputGroup = new QGroupBox("Output",avr);
	outputGroup->setCheckable(false);
	//create a temporary layout
	QVBoxLayout *output  = new QVBoxLayout(outputGroup);
	//initialize our AVRDUDE output box
	avrdudeOutput = new QTextEdit("",outputGroup);
	avrdudeOutput->setReadOnly(true);
	//initialize our AVRDUDE progress bar
	avrdudeProgress = new QProgressBar(outputGroup);
	avrdudeProgress->setEnabled(true);
	//set the range from 0->100 (percent)
	avrdudeProgress->setRange(0,100);
	//shows the text for the progress bar
	avrdudeProgress->setTextVisible(true);
	//clear the value to 0
	avrdudeProgress->reset();
	//update our layout
	output->addWidget(avrdudeOutput);
	output->addWidget(avrdudeProgress);
	//update our binding box
	outputGroup->setLayout(output);
	outputGroup->show();
	
	//update the rest of the bottom group (options and output)

//columnOne->addWidget(optionsboxGroup);
//Bottom->addWidget(optionsboxGroup);
	VeryBottom->addWidget(outputGroup);


	connect(flashboxGroup,SIGNAL(toggled(bool)),this,SLOT(enableOrDisableFlash(bool)));
	connect(EEPROMboxGroup,SIGNAL(toggled(bool)),this,SLOT(enableOrDisableEEPROM(bool)));


	
	
	//add the bottom to the overal layout
//	avr_master->addLayout(Bottom);
	avr_master->addLayout(VeryBottom);
	
	//set the master layout
	avr->setLayout(avr_master);

	//}

}



void AVRTab::updateOptions()
{
	if (config == NULL)
		return;
	
	if (config->options.flash)
		flashboxGroup->show();
	else
		flashboxGroup->hide();

	if (config->options.eeprom)
		EEPROMboxGroup->show();
	else
		EEPROMboxGroup->hide();

	if (config->options.lockBits)
		bootlockbitsGroup->show();
	else
		bootlockbitsGroup->hide();

	if (config->options.fuseBits)
		fuseGroup->show();
	else
		fuseGroup->hide();
}

/*
 *@destructor
 */
AVRTab::~AVRTab()
{
	if (runAVRDUDE != NULL)
	{
		delete runAVRDUDE;
		runAVRDUDE = NULL;
	}
}

void AVRTab::PopulateProgrammerBox ()
{

	// Hide all but the first item in the programmer box
	for (int i = 1; i<ProgrammerBox->count(); i++)
	{
		QLayout * l = ProgrammerBox->itemAt(i)->layout();
		
		// Is the layout formed as expected?
		if (l==0 || l->itemAt(0) == 0 || l->itemAt(1) == 0)
			break; // Should give an error here!
		
		QWidget * label = l->itemAt(0)->widget();
		QWidget * combo = l->itemAt(1)->widget();
		
		if (label) label->setVisible(false);
		if (combo) combo->setVisible(false);
	}

	
	// Get the selected programmer
	string name = AVRProgrammers->currentText().toStdString();
	Programmer programmer;
	if (config->GetProgrammerByName(name, &programmer)!=0) 
	{
		// Failed to find programmer, cannot add any extra data to the programmers box
		return;
	}
	
	for (int i = 0; i < (int)programmer.params.size(); i++)
	{
		// Check if we need to add a new layout item and widgets to the programmer box
		if ((i+1) >= ProgrammerBox->count())
		{
			QVBoxLayout * l = new QVBoxLayout;  // Layout which holds label and combo box...
			l->addWidget(new QLabel("", this)); // Empty Label...
			l->addWidget(new QComboBox(this));  // Empty Combo box...
			ProgrammerBox->addLayout(l);		// Add it all to the end of the programmer box
		}
		
		QLayout * l = ProgrammerBox->itemAt(i+1)->layout();
		
		// Is the layout formed as expected?
		if (l==0 || l->itemAt(0) == 0 || l->itemAt(1) == 0)
			break; // Should give an error here!
		
		QLabel 	  * label 		   = (QLabel*)l->itemAt(0)->widget();
		QComboBox * paramValuesBox = (QComboBox*)l->itemAt(1)->widget();
		
		// Are they widgets?
		if (label == 0 || paramValuesBox == 0)
			break; // Error here too!
		
		
		// Should be fine from now on - all widgets are as expected (hurray!)
		label->setText(programmer.params[i].name.c_str());
		label->setVisible(true);
		
		paramValuesBox->clear();
		paramValuesBox->setVisible(true);
		
		// Should the box be editable?
		bool editable = programmer.params[i].canEdit.compare("true")==0;
		paramValuesBox->setEditable(editable);
		
		// Add items to the combo box
		for (size_t j = 0; j<programmer.params[i].values.size(); j++)
			paramValuesBox->addItem(QString(programmer.params[i].values[j].c_str()));
		
		// Select the default index (if it's valid)
		if (programmer.params[i].defaultIndex < paramValuesBox->count())
			paramValuesBox->setCurrentIndex(programmer.params[i].defaultIndex);
	
	}
	ProgrammerBox->update();
	return;
}

/*
 *@method getWidget()
 *
 *return the main widget (the thing everything is drawn to)
 */
QWidget *AVRTab::getWidget()
{
	return avr;
}

/**
 * Clears the current program, eeprom, and lock bits
 */
void AVRTab::resetAVRChip()
{
	this->state = STATE_ERASE;
	QString command = " -e";
	
	if (checkErase->isChecked())
	{
		command += " -U flash:r:\"" + tempDir + "erase_temp.hex\":r"; // Read in flash, binary style
	}
	if (programAVRChip(command) != 0)
	{
		avrdudeOutput->append("Error erasing chip!");
		this->state = STATE_IDLE;
		return;
	}
}

/**
 * Verifies that a previous erase took by reading in a temp read file and
 * ensuring that every byte is 0
 */
void AVRTab::checkEraseGood()
{
	int i = 0;
	//open the temporary file
	QFile tempRead(tempDir + "erase_temp.hex");
	//make sure the file exists
	if(!tempRead.exists())
	{
		avrdudeOutput->append("Could not verify erase: temporary file not found");
		return;
	}
	//make sure we can open the file
	if(!tempRead.open(QIODevice::ReadOnly))
	{
		avrdudeOutput->append("Could not verify erase: temporary file cannot be read");
		return;
	}
	//create an array large enough to hold every byte of temp file
	char *myData = new char[tempRead.size()];
	//read all the bytes
	int totalRead = tempRead.read(myData,tempRead.size());
	
	if(totalRead == -1 || totalRead != tempRead.size())
	{
		avrdudeOutput->append("Could not verify erase: temporary file read error");
		return;
	} 
	else // The read was good
	{ 
		//iterate through every byte and ensure that it is equal to zero
		for(i = 0; i<totalRead; i++)
		{
			if(myData[i] != 0)
			{
				avrdudeOutput->append("The erase failed!");
				break;
			}
		}
	}
	
	//only happens on a good erase
	if(i==tempRead.size())
	{
		avrdudeOutput->append("Erase was Good");
	}
	
	delete [] myData;
	
	// Close and remove the temp file
	tempRead.close();
	if (!tempRead.remove())
	{
		avrdudeOutput->append("Couldn't delete temp file: erase_temp.hex in " + tempDir);
	}
	return;
}

/**
 * Programs the flash memory of avr chip with the current choosen file
 */
void AVRTab::programFlashAVRChip()
{
	this->state = STATE_PROGRAMMING;
	QString flashFile = flashFileOutput->displayText();
	
	if(flashFile.isNull() || flashFile.isEmpty())
	{
		avrdudeOutput->append("Cannot program Flash: The selected file is invalid");
		return;
	}
	
	QString command = QString("-U flash:w:\"" + flashFile + "\":a");
	
	programAVRChip(command);
	return;
}

/**
 * Programs the EEPROM memory of avr chip with the current choosen file
 */
void AVRTab::programEEPROMAVRChip()
{
	this->state = STATE_PROGRAMMING;
	QString EEPROMFile = EEPROMFileOutput->displayText();
	
	if(EEPROMFile.isNull() || EEPROMFile.isEmpty())
	{
		avrdudeOutput->append("Cannot program EEPROM: The selected file is invalid");
		return;
	}
	
	QString command = QString("-U eeprom:w:\"" + EEPROMFile + "\":a");
	programAVRChip(command);
	return;
}

/**
 * Programs the fuse bits of avr chip with the current settings
 */
void AVRTab::programFuseAVRChip()
{
	this->state = STATE_PROGRAMMING;
	avrdudeOutput->clear();
	
	// Let's make sure we're not getting ahead of ourselves...
	if (fuseListWidget->count() == 0)
	{
		avrdudeOutput->append("Cannot program fuse bits: there are none!");
		return;
	}
		
	// An empty string will indicate the fuse doesn't exist.
	QString fuseHexValue = "";
	QString lowFuseHexValue = "";
	QString highFuseHexValue = "";
	QString extFuseHexValue = "";
		
	uint32_t bitHolder = 0; // 32 bit unsigned integer (although we only need 24 bits...)
		
	for (int i = 0; i < 24; i++)
	{
		// Only leave it a zero (programmed) if the checkbox is checked
		if (i < fuseListWidget->count() && fuseListWidget->item(i)->checkState() != Qt::Checked)
		{
			bitHolder += (1<<i);
		}
	}
		
	// The bits are all in the bitHolder, we just have to figure out where they go...
	
	// Check if the lower eight go into the fuse variable:
	if (part.fuse.size() > 0)
	{
		fuseHexValue = QString::number((bitHolder & 0xff), 16);
	}
	else
	{
		// Have a lfuse and hfuse
		lowFuseHexValue = QString::number((bitHolder & 0xff), 16);
		highFuseHexValue = QString::number((bitHolder >> 8) & 0xff, 16);
		
		// Ahh, but do we have an efuse?
		if (part.efuse.size() > 0)
		{
			// Yep, sure do!
			extFuseHexValue = QString::number((bitHolder >> 16) & 0xff, 16);
		}
	}
		
	// Pad with zero if needed (is this needed? I'm sure avrdude can parse a 0x3 as 3, not 24...)
	// Whatever, it looks prettier...
	if (fuseHexValue.size()     == 1) fuseHexValue     = "0" + fuseHexValue;
	if (lowFuseHexValue.size()  == 1) lowFuseHexValue  = "0" + lowFuseHexValue;
	if (highFuseHexValue.size() == 1) highFuseHexValue = "0" + highFuseHexValue;
	if (extFuseHexValue.size()  == 1) extFuseHexValue  = "0" + extFuseHexValue;

	// Construct and execute the command
	QString command = "";
	if (!fuseHexValue.isEmpty()) // we're programming the single fuse byte
	{
		command += " -U fuse:w:0x" + fuseHexValue + ":m";
	}
	else // We're programming at least lfuse and hfuse
	{ 
		command += " -U lfuse:w:0x"+lowFuseHexValue+":m";
		command += " -U hfuse:w:0x" + highFuseHexValue + ":m";
		
		// Program efuse (if needed)
		if(!(extFuseHexValue.isEmpty()))
		{
			command += " -U efuse:w:0x" + extFuseHexValue + ":m";
		}
	}
	programAVRChip(command);
	return;
}

/**
 * Programs the lock bits of avr chip with the current settings
 */
void AVRTab::programBootAVRChip()
{
	this->state = STATE_PROGRAMMING;
	if (lockListWidget->count() <= 0)
	{
		avrdudeOutput->append("Cannot write lock bits: there are none!");
		return;
	}

	QString lockHexValue = QString("");
	int lockByteValue = 0;

	for(int i = 0; i < lockListWidget->count(); i++)
	{
		if(lockListWidget->item(i)->checkState() != Qt::Checked)
		{
			lockByteValue += (1<<i);
		}
	}
	lockHexValue = QString::number(lockByteValue,16);
	
	// Force the hex to be length 2, (unless it's an empty string, which indicates no lock bits at all)
	if (lockHexValue.size() == 1) lockHexValue = QString("0") + lockHexValue;

	QString command = QString("-u -U lock:w:0x"+lockHexValue+":m");
	
	// program the chip
	programAVRChip(command);
	
	return;
}

/**
 * @brief Compute the part options string for the avrdude command line (-p [part])
 * @param OUT string s std::string in which the result will be stored
 * @return 0 on success, non-zero if there is an error
 */
int AVRTab::GetPartOptions(string &s)
{
	stringstream options;
	options << " -p " << part.abbreviation;
	s = options.str();
	return 0;
}

/**
 * @brief Compute the programmer options from the current programmer selection
 * @param OUT string s std::string in which the result will be stored
 * @return 0 on success, non-zero if there is an error.
 */
int AVRTab::GetProgrammerOptions(string & s)
{
	stringstream options;
	
	// Find and add programmer command line param (-c):
	Programmer pgm;
	if (config->GetProgrammerByName(AVRProgrammers->currentText().toStdString(), &pgm)!=0)
	{
		// Failed to find programmer, cannot add any extra data to the programmers box
		return 1;
	}
	options << " -c " << pgm.name;

	// Load in parameters
	for (size_t i = 0; i < pgm.params.size(); i++)
	{
		// Ensure the programmer box has enough elements.
		// This only fails if somebody forgot to call PopulateProgrammerBox() (was it you???)
		if ((i+1) >= (size_t)ProgrammerBox->count()) 
			break;
			
		QLayout * l = ProgrammerBox->itemAt(i+1)->layout();
		
		if (l==0 || l->itemAt(1) == 0) // Should never happen, but just in case...
			break;
			
		QComboBox * paramValueWidget = (QComboBox*)l->itemAt(1)->widget();
		
		if (paramValueWidget == 0) // Again, just a safety check...
			break;

		options << " " << pgm.params[i].flag << " " << paramValueWidget->currentText().toStdString();
	}
	s = options.str();
	return 0;
}

/**
 * Given a command (in the form of a QString) creates a process to run AVRDUDE
 * with the given command string.  Connects the appropriate signals in order to determine
 * progress
 * @param commands AVRDUDE command excluding programmer and options.
 * @return an integer representing the exit status of AVRDUDE (0 = good, not 0 = bad)
 */
int AVRTab::programAVRChip(QString commands)
{
	avrdudeProgress->setValue(0);
	avrdudeOutput->clear();
	
	//get a parent object that QProcess can reference as the calling widget
	QObject *parent = this;
	avr->setEnabled (false);
	
#ifdef WIN32
	QString program = QString("avrdude/avrdude.exe ");
#else
	QString program = QString("avrdude ");
#endif
	
	string progOptions;
	if (this->GetProgrammerOptions(progOptions)!=0)
	{
		avrdudeOutput->append("Problem getting programmer options");
		return 1;
	}
	
	string partOptions;
	if (this->GetPartOptions(partOptions)!=0)
	{
		avrdudeOutput->append("Problem getting part options");
		return 1;
	}
	
	program += QString(progOptions.c_str()) + QString(partOptions.c_str());

	if(checkSig->isChecked()) // Skip signature check
	{
		program += QString(" -F");
	}
	
	if(checkVerify->isChecked()) // Skip verify check
	{
		program += QString(" -V");
	}

	//initialize our QProcess
	if (runAVRDUDE != NULL)
	{
		delete runAVRDUDE;
		runAVRDUDE = NULL;
	}
	runAVRDUDE = new QProcess(parent);
	
	runAVRDUDE->setProcessChannelMode(QProcess::MergedChannels);
	
	
	program += QString (" ") + commands;
	
	connect(runAVRDUDE, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(programAVRStatus(int, QProcess::ExitStatus)));
	connect(runAVRDUDE, SIGNAL(readyReadStandardOutput()), this, SLOT(programAVROutput()));
	
	avrdudeOutput->append("Running Command: " + program);
	isProgressing = false;
	
	//run the program and make the process read only
	runAVRDUDE->start(program, QIODevice::ReadOnly);
	
	//make sure the process started
	if(!runAVRDUDE->waitForStarted())
	{
		avrdudeOutput->append("AVRDUDE Could Not Be Started!  Is the avrdude folder still there?");
		runAVRDUDE->kill();
		return 1;
	}

	return 0;
}

/**
 * Watch the stderr and stdout from the running AvrDude process
 * Text comes in as unpredictably sized chunks.  This method
 * will split the text up line by line for more convenient
 * processing in the ProcessOutputLine method.
 */
void AVRTab::programAVROutput()
{
	avrdudeOutputText += runAVRDUDE->readAllStandardError() + runAVRDUDE->readAllStandardOutput();
	int endOfLine = avrdudeOutputText.indexOf("\n");
	while (endOfLine > 0)
	{
		isProgressing = false; // State variable for logic below
		QString line = avrdudeOutputText.mid(0, endOfLine - 1);
		avrdudeOutputText.remove(0, endOfLine + 1); // Remove all the first line including the \n
		
		// Process the line if it's not blank
		if (!line.trimmed().isEmpty())
		{
			ProcessOutputLine(line);
		}
		
		endOfLine = avrdudeOutputText.indexOf("\n");
	}
	
	// If the line isn't complete (no new line), it may be a progress bar made of ### signs.
	// This line will look like the following:
	// Reading | ################################################## | 100%
	// The text may be Reading or Writing
	bool reading = avrdudeOutputText.contains("Reading | ");
	bool writing = avrdudeOutputText.contains("Writing | ");
	
	if (reading || writing)
	{
		if (!isProgressing)
		{
			avrdudeProgress->setValue(0);
			isProgressing = true;
		}
		int progress = avrdudeOutputText.count("#") * 2; // * 2 since each # means 2 percent (50 total)
		avrdudeProgress->setValue(progress);
	}
}

/**
 * Process a single output line
 * @param line The current AvrDude Output line, with no newline characters.
 */
void AVRTab::ProcessOutputLine(QString line)
{
	// Output avrdude outputs to terminal
	const char * stringoutput = QString(line).toAscii();
	printf("%s", stringoutput);

	// Print out lines starting with avrdude.exe: 
	if (line.contains("avrdude.exe: "))
	{
		bool ignore = 
			(this->state == STATE_IDENTIFY || this->state == STATE_ID_FOUND) && 
			(line.contains("Expected signature") || line.contains("Device signature"));
		if (!ignore)
		{
			avrdudeOutput->append(line);
		}
	}

	if (this->state == STATE_IDENTIFY)
	{
		if(line.contains("Device signature", Qt::CaseInsensitive))
		{
			// [Parse this line] avrdude: Device signature = 0x1e9109
			int sigStart = line.indexOf("0x");

			QString signature = line.mid(sigStart).trimmed();
			avrdudeOutput->append("Signature = '" + signature + "'");

			bool match_found = false;
			for (size_t i = 0; i < config->parts.size(); i++) 
			{
				if(signature.compare(QString("0x") + QString(config->parts[i].id.c_str()), Qt::CaseInsensitive) == 0)
				{
					part = config->parts[i];
					match_found = true;
				}
			}
			
			if (!match_found)
			{
				mess->changeMessage("No matching part for signature '"+signature + "'");
				mess->show();
				return;
			}
			
			QString model_name = QString(part.name.c_str());
			
			// Returns the index that our model is at, or -1 if it doesn't exist
			int combo_box_index = AVRMods->findText(model_name, Qt::MatchExactly);
			
			//let the user know it doesn't exist
			if (combo_box_index == -1) 
			{
				mess->changeMessage("Part name '" + model_name + "' not found in list");
				mess->show();
				return;
			}
			AVRMods->setCurrentIndex(combo_box_index);
			avrdudeOutput->append("Model = '" + model_name + "'");
			avrdudeOutput->append("\nOperation Successful!");
			this->state = STATE_ID_FOUND; // Set to ID found to ignore errors on process end
		}
	}
	
	return;
}

/**
 * Determine what to do when the Avrdude command completes
 */
void AVRTab::programAVRStatus(int exitCode, QProcess::ExitStatus exit_status)
{
	// Process all remaining output
	if (!avrdudeOutputText.isEmpty())
	{
		ProcessOutputLine(avrdudeOutputText);
		avrdudeOutputText.clear();
	}
	
	if (this->state == STATE_ID_FOUND)
	{
		// Ignore error codes in the identify state (as long as the id is found).
		// We expect this to return a non-zero exit code
	}
	else
	{
		// OK if normal exit, exit code == 0, and we're not in the identify state
		if(exit_status == QProcess::NormalExit && exitCode == 0 && this->state != STATE_IDENTIFY)
		{
			switch(this->state)
			{
				case STATE_VERIFY_ERASE:
					checkEraseGood();
					break;
				
				case STATE_READING_LOCK:
					ReadLockByteFile();
					break;
				
				case STATE_READING_FUSE:
					ReadFuseByteFile();
					break;
				
				default:
					avrdudeOutput->append("\nOperation Successful!\n");
					break;
			}
		}
		else // let the user know there was a problem
		{
			avrdudeOutput->append("\nAn Error Occurred: Exit code " + QString::number(exitCode) + "\n");
		}
	}
	
	this->state = STATE_IDLE;
	avr->setEnabled(true);
	avrdudeProgress->setValue(100); // Whatever we were doing, it's done now!
	
	return;
}



/**
 * Called on scan flash click
 */
void AVRTab::ScanFlashAVRChip()
{
	// Write Flash To File
	QString command = "-U flash:r:\"" + tempDir + "flash_temp.hex\":i"; // Write as intel hex (i)
	
	if(programAVRChip(command))
	{
		mess->changeMessage("There was an error getting flash information, aborting scan");
		mess->show();
		return;
	}
	
	flashFileOutput->clear();
	flashFileOutput->setText(QString(tempDir + "flash_temp.hex"));
	flashFileOutput->setModified(true);
	programFlash->setEnabled(true);
}

/**
 * Read the EEPROM from the chip into a temporary file
 */
void AVRTab::ScanEEPROM()
{
	// Read EEPROM To File
	QString command = "-U eeprom:r:\"" + tempDir + "eeprom_temp.eep.hex\":r";
	
	if (programAVRChip(command))
	{
		mess->changeMessage("There was an error getting EEPROM information, aborting scan");
		mess->show();
		return;
	}
	
	EEPROMFileOutput->clear();
	EEPROMFileOutput->setText(QString(tempDir+"eeprom_temp.eep.hex"));
	EEPROMFileOutput->setModified(true);
	programEEPROM->setEnabled(true);
}

/**
 * Read the fuse bits into the GUI:
 * This method starts the chain of events:
 * 1. This method starts AvrDude
 * 2. Avrdude completes, and the process complete callback calls the ReadFuseByteFile function
 * 3. The ReadFuseByteFile function reads the files produced by AvrDude and updates the checkboxes accordingly
 */
void AVRTab::ScanFuseBits()
{
	this->state = STATE_READING_FUSE;

	QString command;

	// Just one fuse
	if(part.fuse.size () > 0)
	{
		command = "-U fuse:r:\"" + tempDir + "fuse_temp.hex" + "\":r";
	}
	else //there is at least low and high fuse
	{ 
		command = " -U lfuse:r:\"" + tempDir + "lfuse_temp.hex\":r";
		command+= " -U hfuse:r:\"" + tempDir + "hfuse_temp.hex\":r";
		
		if (part.efuse.size() > 0)
		{
			command+= " -U efuse:r:\"" + tempDir + "efuse_temp.hex\":r";
		}
	}
	
	if (programAVRChip(command))
	{
		mess->changeMessage("There was an error getting fuse information, aborting scan");
		mess->show();
	}
}

/**
 * Reads the fuse byte file produced by AvrDude
 * Sets the checkboxes accordingly
 */
void AVRTab::ReadFuseByteFile()
{
	char fuse = 0;
	char lfuse = 0;
	char hfuse = 0;
	char efuse = 0;
	
	if (part.fuse.size() > 0)
	{
		if (ReadByteFromFile (tempDir + "fuse_temp.hex", fuse) != 0)
		{
			avrdudeOutput->append("Failed to read fuse byte");
			return;
		}
	}
	else // Otherwise, read lfuse, hfuse, and maybe efuse
	{
		if (ReadByteFromFile (tempDir + "lfuse_temp.hex", lfuse) != 0)
		{
			avrdudeOutput->append("Failed to read lfuse byte");
			return;
		}
		if (ReadByteFromFile (tempDir + "hfuse_temp.hex", hfuse) != 0)
		{
			avrdudeOutput->append("Failed to read hfuse byte");
			return;
		}
		if (part.efuse.size() > 0 && ReadByteFromFile (tempDir + "efuse_temp.hex", efuse) != 0)
		{
			avrdudeOutput->append("Failed to read efuse byte");
			return;
		}
	}
	
	uint32_t allFuseBytes = ((uint32_t)fuse & 0x000000FF) | 
							((uint32_t)lfuse & 0x000000FF) | 
							(((uint32_t)hfuse << 8) & 0x0000FF00) | 
							(((uint32_t)efuse << 16) & 0x00FF0000);

	// Update the lock check boxes
	for (int i = 0; i < fuseListWidget->count(); i++)
	{
		if (allFuseBytes & (1 << i))
		{
			fuseListWidget->item(i)->setCheckState(Qt::Unchecked); // Ones mean unchecked (unprogrammed)
		}
		else
		{
			fuseListWidget->item(i)->setCheckState(Qt::Checked); // Zero's mean checked (programmed)
		}
	}
	
	avrdudeOutput->append("Fuse Bit Scan Completed Successfully!");
}

/**
 * Starts the scan lock bits chain:
 * 1. Call Avrdude, write lock bits to file
 * 2. Process complete callback calls ReadLockByteFile
 * 3. ReadLockByteFile reads the files produced, and sets the checkboxes
 */
void AVRTab::ScanLockBits()
{
	this->state = STATE_READING_LOCK;
	QString command = "-U lock:r:\"" + tempDir + "lock_temp.hex" + "\":r";
	
	if (programAVRChip(command))
	{
		mess->changeMessage("There was an error getting Lock Bit information, aborting scan");
		mess->show();
		return;
	}
}

/**
 * Read the lock byte file produced by AvrDude
 */
void AVRTab::ReadLockByteFile()
{
	// Get the lock byte saved by avrdude
	char lockByte;
	
	if (ReadByteFromFile(tempDir + "lock_temp.hex", lockByte) != 0)
	{
		avrdudeOutput->append("Failed to read lock byte, File IO Error");
		return;
	}
	
	// Update the lock check boxes
	for (int i = 0; i < lockListWidget->count(); i++)
	{
		if (lockByte & (1<<i))
		{
			lockListWidget->item(i)->setCheckState(Qt::Unchecked); // Ones mean unchecked (unprogrammed)
		}
		else
		{
			lockListWidget->item(i)->setCheckState(Qt::Checked); // Zero's mean checked (programmed)
		}
	}
	avrdudeOutput->append("Lock Bit Scan Completed Successfully!");
}

int AVRTab::ReadByteFromFile(QString fileName, char &outChar)
{
	outChar = 0;
	
	QFile file(fileName);
	
	if(!file.exists())
	{
		mess->changeMessage("Temporary File Does Not Exist!");
		mess->show();
		return -1;
	}
	
	//make sure it can opened
	if(!file.open(QIODevice::ReadOnly))
	{
		mess->changeMessage("Couldn't open temp file.\nMake sure you have read permissions.");
		mess->show();
		return -1;
	}
	
	char lockByte = 0;
	int read = file.read(&lockByte,1);
	
	if (read == -1) // Read Error
	{
		mess->changeMessage("Couldn't Read temp file.\nMake sure you have read permissions.");
		mess->show();
		return -1;
	}
	
	if (read != 1) // Read wrong number of bytes
	{
		mess->changeMessage("Bad Read of temp file.");
		mess->show();
		return -1;
	}
	
	outChar = lockByte;
	return 0;
}

/**
 * Identifies chip that is current connected to the programmer and sets
 * it in the drop down box for chip model, if it exists
 */
void AVRTab::avrIdentify(void)
{
	avr->setEnabled(false);
	this->state = STATE_IDENTIFY;
	avrdudeOutput->clear();
	
	//get a new process
	if (runAVRDUDE != NULL)
	{
		delete runAVRDUDE;
		runAVRDUDE = NULL;
	}
	runAVRDUDE = new QProcess(this);

	string progOptions;
	if (this->GetProgrammerOptions(progOptions) != 0)
	{
		avrdudeOutput->append("Could not determine programmer options...");
		return;
	}
	
	//avrdude path for windows
	#ifdef WIN32
	QString readSig = QString("avrdude/avrdude.exe");
	//avrdude path for linux
	#else
	QString readSig = QString("avrdude");
	#endif
	
	readSig += " -p m128 " + QString(progOptions.c_str());
	
	avrdudeOutput->append(readSig);
	connect(runAVRDUDE, SIGNAL(readyReadStandardError()), this, SLOT(programAVROutput()));
	connect(runAVRDUDE, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(programAVRStatus(int, QProcess::ExitStatus)));
	QStringList environment = QProcess::systemEnvironment();
	
	// Start the process
	runAVRDUDE->start(readSig,QIODevice::ReadOnly);
	//make sure the process started
	if(runAVRDUDE->waitForStarted())
	{
		avrdudeOutput->append("AVRDUDE Started\n");
	}
	else
	{
		avrdudeOutput->append("AVRDUDE could not be started, check that the avrdude folder exists.");
		runAVRDUDE->kill();
		avr->setEnabled(true);
		this->state = STATE_IDLE;
		return;
	}
}

/**
 * Called when the index of the programmer selection is changed.
 */
void AVRTab::ProgrammerSelectionChanged(int curChoice)
{
	this->PopulateProgrammerBox();
	return;
}

/**
 * Called on lock bits group box check change
 * Used to enable or disable elements inside the box
 */
void AVRTab::enableOrDisableLockBits(bool state)
{
	programBootBits->setEnabled(state);
	scanLockBits->setEnabled(state);
	lockListWidget->setEnabled(state);
}

/**
 * Called on fuse bits group box check change
 * Used to enable or disable elements inside the box
 */
void AVRTab::enableOrDisableFuseBits(bool state)
{
	programFuseBits->setEnabled(state);
	scanFuseBits->setEnabled(state);
	preserveEEP->setEnabled(state && eepromCanSave);
	fuseListWidget->setEnabled(state);
}

/**
 * Called on flash group box check change
 * Used to enable or disable elements inside the box
 */
void AVRTab::enableOrDisableFlash(bool state){
	flashFileOutput->setEnabled(state);
	flashFileBrowse->setEnabled(state);
	scanFlash->setEnabled(state);
	programFlash->setEnabled(state&&flashFileOutput->isModified());
	return;
}

/**
 * Opens a browse dialog for the flash .hex file
 */
void AVRTab::browse4Flash()
{
	//let the user browse to find the file
	QString myFile = QFileDialog::getOpenFileName(this,tr("Open Flash Hex File"),folderRoot,tr("Hex Files (*.hex)"));
	
	//ensure we didn't get junk back
	if(!myFile.isNull() && myFile.contains(".hex",Qt::CaseInsensitive))
	{
		flashFileOutput->selectAll();
		flashFileOutput->insert(myFile);
		enableOrDisableFlash(true);
		folderRoot=QDir::root().filePath(myFile);
	}
	return;
}

/**
 * Checkbox for EEPROM programming
 * Used to enable or disable EEPROM items
 */
void AVRTab::enableOrDisableEEPROM(bool state)
{
	EEPROMFileOutput->setEnabled(state);
	EEPROMFileBrowse->setEnabled(state);
	scanEEPROM->setEnabled(state);
	programEEPROM->setEnabled(state&&EEPROMFileOutput->isModified());
}

/** 
 * Open a browse dialog for an eeprom .hex file
 */
void AVRTab::browse4EEPROM()
{
	// Let the user browse to find the file
	QString myFile = QFileDialog::getOpenFileName(this,tr("Open EEPROM Hex File"),folderRoot,tr("Hex Files (*.hex)"));
	
	// Ensure we didn't get junk back
	if(!(myFile.isNull())  && myFile.contains(".hex",Qt::CaseInsensitive))
	{
		EEPROMFileOutput->selectAll();
		EEPROMFileOutput->insert(myFile);
		enableOrDisableEEPROM(true);
		folderRoot=QDir::root().filePath(myFile);
	}
	return;
}

/**
 * Changes whether LB1 and LB2 (if present in the current Boot Lock Bits section)
 * are checked or not depending on what the user has chosen:
 * ________________________________
 * |STATE         |LB1    |LB2    |
 * --------------------------------
 * |No Protection |uncheck|uncheck| 
 * --------------------------------
 * |Program       |check  |uncheck|
 * --------------------------------
 * |Program+Verify|check  |check  |
 * --------------------------------
 */
void AVRTab::flashLockBitsChange()
{
	//integer representation of what radio button is checked
	int toChange = 0;
	
	//see which one of the radio buttons was selected
	if (noProtect->isChecked()) 
	{
		toChange = 0;
	} 
	else if (progDisabled->isChecked()) 
	{
		toChange = 2;
	}
	else //user must have chosen Program and Verify Disable
	{
		toChange = 3;
	}
	//update our LB1 and LB2 in the Boot Lock Bits section
	for (int i = 0; i < lockListWidget->count(); i++)
	{
		// Found LB1
		if (lockListWidget->item(i)->text() == "LB1=0")
		{
			//if we are doing anything other than no protection, check it
			if (toChange)
			{
				lockListWidget->item(i)->setCheckState(Qt::Checked);
			}
			else //otherwise, uncheck it
			{
				lockListWidget->item(i)->setCheckState(Qt::Unchecked);
			}
		}
		// Found LB2
		if (lockListWidget->item(i)->text() == "LB2=0")
		{
			if (toChange == 3) // only if doing Program & Verify disabling, check LB2
			{
				lockListWidget->item(i)->setCheckState(Qt::Checked);
			}
			else // otherwise, uncheck it
			{
				lockListWidget->item(i)->setCheckState(Qt::Unchecked);
			}
		}
	}
	
	//update the widget
	bootlockbitsGroup->update();
	return;
}

/**
 * This is called when the user changes the index of the Model drop down box
 * (i.e. changes the current model).  The screen is updated with the proper
 * flash and lock bits for the new model and defaults are set again.
 */
void AVRTab::changedDevice(int device)
{
	string name = AVRMods->currentText().toStdString();
	
	if (config->GetPartByName (name, &part)!=0)
	{
		stringstream out;
		out << "Part Name " << name << " Not Found!";
		mess->changeMessage (out.str().c_str());
		mess->show();
	}
	else
	{
		changeFuseGroup();
		changeLockGroup();
		noProtect->toggle();
		this->update();
	}
	
	return;
}

/**
 * Called from changedDevice, deletes any current layout and check boxes under the 
 * Boot Lock Bits section and sets up the new check boxes based on those set in the 
 * configuration file
 */
void AVRTab::changeLockGroup()
{
	// Remove all old lock bits from the list
	lockListWidget->clear();
	
	if (part.lock.size() == 0)
	{
		// since we don't go ahead and don't allow users to do anything inside
		bootlockbitsGroup->setEnabled(false);
	}
	else // Lets add the checkboxes
	{
		bootlockbitsGroup->setEnabled(true);
		for(size_t i = 0; i < part.lock.size(); i++)
		{
			QString name = QString(part.lock[i].c_str()) + QString("=0");
				
			QListWidgetItem * item = new QListWidgetItem (name, lockListWidget);
			item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled); // Initially enabled and checkable
			item->setCheckState(Qt::Unchecked); // Initially unchecked
			
			if((name.compare("LB1=0", Qt::CaseInsensitive) == 0) || (name.compare("LB2=0", Qt::CaseInsensitive) == 0))
			{
				item->setFlags(Qt::ItemIsUserCheckable); // No more enabled flag
			}
		}
	}

	bootlockbitsGroup->update();
	return;
}

/**
 * Called from changedDevice, deletes any current layout and check boxes under the 
 * Fuse section and sets up the new check boxes based on those set in the 
 * configuration file
 * There are two special cases here, if a fuse bit is called "EESAVE" it is toggled with
 * the "Preserve EEPROM" check box and if it is called "RESERVED" it is disabled, period.
 */
void AVRTab::changeFuseGroup()
{	
	// Remove all other fuse items from the list
	fuseListWidget->clear();

	//checks if we can allow the EEPROM to be preserved
	eepromCanSave = false;

	//see if we have any fuse bits
	if((part.fuse.size() + part.lfuse.size() + part.hfuse.size() + part.efuse.size()) == 0)
	{
	}
	else
	{
		//we're just doing one fuse
		if(part.fuse.size() > 0)
		{
			//go through each fuse and create a check box
			for(size_t i = 0; i < part.fuse.size(); i++)
			{
				QString name = QString(part.fuse[i].c_str()) + QString("=0");
				
				QListWidgetItem * item = new QListWidgetItem (name, fuseListWidget);
				item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled); // Initially enabled and checkable
				item->setCheckState(Qt::Unchecked); // Initially unchecked
				
				if(name.contains("RESERVED", Qt::CaseInsensitive))
				{
					item->setFlags(Qt::ItemIsUserCheckable); // No more enabled flag
				}
				
				if(name.contains("EESAVE", Qt::CaseInsensitive))
				{
					item->setFlags(Qt::ItemIsUserCheckable); // No more enabled flag
					eepromCanSave = true;
				}
			}
			
		}
		else
		{ 
			//we're doing multiples, at least low and high fuses

			//update our size variable
			size_t totalFuseBits = part.lfuse.size() + part.hfuse.size() + part.efuse.size();
			
			for(size_t i = 0; i < totalFuseBits; i++)
			{
				//create a new fuse, 0->7 are lfuse; 8-15 are hfuse and 16+ is efuse
				QString name = "?";
				
				if(i <= 7) // lfuse
				{
					if (i < part.lfuse.size())
						name = QString(part.lfuse[i].c_str()) + QString("=0");
				} 
				else if(i <= 15) // hfuse
				{
					if ((i-8) < part.hfuse.size())
						name = QString(part.hfuse[i-8].c_str()) + QString("=0");
				} 
				else // efuse
				{
					if ((i-16) < part.efuse.size())
						name = QString(part.efuse[i-16].c_str()) + QString("=0");
				}

				QListWidgetItem * item = new QListWidgetItem (name, fuseListWidget);
				item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled); // Initially enabled and checkable
				item->setCheckState(Qt::Unchecked); // Initially unchecked
				
				item->setText(name);
				if(name.contains("RESERVED", Qt::CaseInsensitive))
				{
					item->setFlags(Qt::ItemIsUserCheckable); // No more enabled flag
				}
				
				if(name.contains("EESAVE", Qt::CaseInsensitive))
				{
					item->setFlags(Qt::ItemIsUserCheckable); // No more enabled flag
					eepromCanSave = true;
				}
			}
		}
	}
	//set whether or not we can save the eeprom on the gui
	preserveEEP->setEnabled(fuseGroup->isChecked() && eepromCanSave);

	return;
}

/**
 * Updates the 'EESAVE' fuse bit, if it exists, to reflect the user's choice of the
 * "Preserve EEPROM" check box
 */
void AVRTab::updatePreserveEEPROM(bool update)
{
	QList<QListWidgetItem*> items = fuseListWidget->findItems("EESAVE", Qt::MatchContains);
	
	for (int i = 0; i<items.size (); i++)
	{
		items[i]->setCheckState(update ?  Qt::Checked : Qt::Unchecked);
	}

	return;
}

/**
 * Called by the main window, tells the AVR tab what the temporary directory is
 */
void AVRTab::setTempDir(QString newDir)
{
	tempDir = newDir;
	//add a trailing "/" so folder construction is easier later on
	if (tempDir.at(tempDir.size()-1) != '/')
	{
		tempDir.append("/");
	}
	return;
}
