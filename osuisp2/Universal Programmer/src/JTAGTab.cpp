/**
 * File: JTAGTab.cpp
 * @class JTAGTab
 * @author Ben Porter
 * @author Jace Akerlund (akerlunj@onid.orst.edu)
 * @author Michael Spray (spraym@onid.orst.edu)
 *
 * To learn more about the Tekbots program: http://www.eecs.oregonstate.edu/tekbots.html
 *
 * @brief The JTAG tab provides a GUI for loading a .svf or .xsvf file and programming
 * the file to a xilinx or other device using a .xsvf runner.  If a .svf file is chosen,
 * the program automatically converts the .svf to a .xsvf format (.xsvf is a compressed
 * binary version of the .svf file)
 */
#include <QtGui>
#include "JTAGTab.h"

/**
 * The constructor lays out components in the JTAG tab
 */
JTAGTab::JTAGTab()
{
	jtag = new QWidget();
	
	svfProcess = NULL;
	
	SVFFilePath = QDir::homePath();

	QVBoxLayout *jtag_master = new QVBoxLayout(jtag);
	QHBoxLayout *svfMainBoxLayout = new QHBoxLayout(jtag);
	QHBoxLayout *ChainandOutput = new QHBoxLayout(jtag);
	
	/**
	 * Create XSVF Player options box
	 */
	SVFboxGroup = new QGroupBox("XSVF/SVF File Player",jtag);
	SVFboxGroup->show();
	SVFboxGroup->setEnabled(true);

	// Run button
	runSVF = new QPushButton(*(new QString("Run xsvf/svf Player")),SVFboxGroup);
	runSVF->setEnabled(false);
	connect(runSVF,SIGNAL(clicked()),this,SLOT(RunXSVFPlayer()));
	
	//set up our text field that outputs the location of the flash file
	SVFFileOutput = new QLineEdit(SVFboxGroup);
	SVFFileOutput->setReadOnly(true);
	SVFFileOutput->insert(*(new QString("")));
	SVFFileOutput->setEnabled(true);
	SVFFileOutput->show();
	
	SVFFileBrowse = new QPushButton(*(new QString("Browse")),SVFboxGroup);
	SVFFileBrowse->setEnabled(true);
	SVFFileBrowse->show();
	connect(SVFFileBrowse,SIGNAL(clicked()),this,SLOT(OpenXSVFBrowse()));
	
	QHBoxLayout *xsvfPlayerHLayout   = new QHBoxLayout(jtag);
	xsvfPlayerHLayout->addWidget(SVFFileOutput);
	xsvfPlayerHLayout->addWidget(SVFFileBrowse);
	
	QVBoxLayout *xsvfVerticalBox = new QVBoxLayout(jtag);
	xsvfVerticalBox->addLayout(xsvfPlayerHLayout);
	xsvfVerticalBox->addWidget(runSVF); // TODO: RENAME
	SVFboxGroup->setLayout(xsvfVerticalBox);

	svfMainBoxLayout->addWidget(SVFboxGroup);
	
	fflush(stdout); // Why is this here?
	
	jtag_master->addLayout(svfMainBoxLayout);
	
	/**
	 * CREATE "Output" GROUP
	 */
	//create the output area, first creating the binding box
	QGroupBox *outputGroup = new QGroupBox("Output",jtag);
	outputGroup->setCheckable(false);

	// Setup the console output window
	svfConsoleOutput = new QTextEdit("",outputGroup);
	svfConsoleOutput->setReadOnly(true);
	
	// Setup the progress bar
	svfProgress = new QProgressBar(outputGroup);
	svfProgress->setTextVisible(true);
	svfProgress->setRange(0,100);
	svfProgress->reset();
	
	QVBoxLayout *output  = new QVBoxLayout(outputGroup);
	output->addWidget(svfConsoleOutput);
	output->addWidget(svfProgress);

	outputGroup->setLayout(output);
	outputGroup->show();
	
	ChainandOutput->addWidget(outputGroup);
	
	jtag_master->addLayout(ChainandOutput);
	jtag->setLayout(jtag_master);
}


/**
 * Destructor
 * Delete any undeleted items allocated in this class
 */
JTAGTab::~JTAGTab()
{
	if (this->svfProcess != NULL)
	{
		delete this->svfProcess;
		svfProcess = NULL;
	}
}

/**
 * Get the main widget of the jtag tab
 * @return the main widget (the thing everything is drawn to)
 */
QWidget *JTAGTab::getWidget()
{
	return jtag;
}

// TODO: Disable tab change while process is running
void JTAGTab::tabChanged(int index)
{
	static int prev=0;
	if(prev==1 && svfProcess != NULL)
	{
		switch(svfProcess->state())
		{
			case QProcess::NotRunning:
				break;
			case QProcess::Starting:
				svfProcess->kill();
			case QProcess::Running:
				//for(i=0;i<5;i++)
				//{
				//	runurJTAG->write("quit\x0C");
				//	if(runurJTAG->waitForFinished(500))
				//		break;
				//}
				//if(runurJTAG->state()!=QProcess::NotRunning)
				svfProcess->kill();
				break;
			default:
				break;
		}
	}
	prev=index;
}

/**
 * Watch output from external processes.
 * This is used to update the GUI progress bar
 * and output box.
 */
void JTAGTab::programjtagOutput()
{
	// Get standard out and error from process
	QString currentOutput = 
		svfProcess->readAllStandardOutput() +
		svfProcess->readAllStandardError();

	// See if it's a percentage type thing:
	int index = currentOutput.indexOf("Programming...");
	if (index > 0)
	{
		QString percentage = currentOutput.mid(index + 14);
		int percentSign = percentage.indexOf("%");
		if (percentSign > 0)
		{
			percentage = percentage.mid (0, percentSign);
			QVariant converter (percentage);
			bool worked;
			int p = converter.toInt (&worked);
			if (worked)
			{
				svfProgress->setValue (p);
			}
		}
	}
	else
	{
		svfConsoleOutput->append(currentOutput);
	}
}

// TODO: Make this work right (test)
void JTAGTab::programjtagExitStatus(int exitCode, QProcess::ExitStatus exit_status)
{
	if(exit_status == QProcess::NormalExit && exitCode == 0)
	{
		svfConsoleOutput->append("------------------------------------------");
		svfConsoleOutput->append("----------Operation Successful!----------");
		svfConsoleOutput->append("------------------------------------------");
	} 
	else // let the user know there was a problem
	{
		svfConsoleOutput->append("------------------------------------------");
		svfConsoleOutput->append("The process did not complete successfully");
		svfConsoleOutput->append("------------------------------------------");
	}
//	runSVF->setEnabled(true);
	jtag->setEnabled (true);
	svfProgress->setValue(0);
}


void JTAGTab::OpenXSVFBrowse()
{
	runSVF->setEnabled(false);
	QString myFile = QFileDialog::getOpenFileName(this,tr("Open SVF/XSVF File"),SVFFilePath,tr("SVF/XSVF Files (*.svf; *.xsvf)"));

	if (myFile.isNull() || myFile.isEmpty())
	{
		return; // File is no good, do nothing
	}

	// Verify extension
	if (myFile.contains(".svf",Qt::CaseInsensitive) ||
		myFile.contains(".xsvf", Qt::CaseInsensitive))
	{
		//update our label
		SVFFileOutput->selectAll();
		SVFFileOutput->insert(myFile);
		runSVF->setEnabled(true);
		SVFFilePath=QDir::root().filePath(myFile);
		
		// Valid file, enable button here
		runSVF->setEnabled(true);
	}
	
	return;
}

/**
 * Called when there is a valid filepath in the xsvf/svf player
 * filepath box and the Run button is pressed.
 * This method will start the xsvf player.  If the file is a
 * .svf file (not the compressed binary .xsvf), a conversion
 * tool will be run.
 */
void JTAGTab::RunXSVFPlayer()
{
	jtag->setEnabled(false);
	
	svfProgress->setValue(0);
	svfConsoleOutput->append("------------------------------------------");
	svfConsoleOutput->append("---------XSVF/SVF Player Started----------");
	svfConsoleOutput->append("------------------------------------------");
	
	QString fileName = SVFFileOutput->text();
	
	// Verify filename is valid
	if (fileName == "")
	{
		svfConsoleOutput->append("Could not run player: input file is blank!");
		runSVF->setEnabled(false);
		jtag->setEnabled(true);
		return;
	}
	
	// Looks like we need to convert the .svf to a .xsvf file...
	if (fileName.endsWith(".svf", Qt::CaseInsensitive))
	{
		QString temporaryFilePath = tempDir + "output.xsvf";
		QString program = "svf2xsvf502.exe -i \"" + fileName + "\" -d -o \"" + temporaryFilePath + "\"";
		fileName = temporaryFilePath;//"output.xsvf";
		svfConsoleOutput->append("Running Command: " + program);
	
		if (svfProcess != NULL)
		{
			delete svfProcess;	
		}
		svfProcess = new QProcess(jtag);
		svfProcess->setProcessChannelMode(QProcess::MergedChannels);

		connect(svfProcess,SIGNAL(readyReadStandardOutput()),this,SLOT(programjtagOutput()));
			
		svfProcess->start(program, QIODevice::ReadOnly);

		if (svfProcess->waitForStarted())
		{
			svfConsoleOutput->append("SVF to XSVF Conversion Started...");
		}
		else
		{
			svfConsoleOutput->append("The converter could not be started");
			svfConsoleOutput->append("Ensure svf2xsvf502.exe is in the same folder as this .exe");
			
			svfProcess->kill();
			jtag->setEnabled(true);
			return;
		}
	
		// Wait 3 seconds for the conversion to complete (should be ample time...)
		if (!svfProcess->waitForFinished(3000))
		{
			if (svfProcess->error() == QProcess::Timedout)
			{
				svfConsoleOutput->append("The converter timed out: try converting manually with the command above");
			}
			svfProcess->kill();
		}

		if (svfProcess->exitCode() == 0)
		{
			svfConsoleOutput->append("SVF to XSVF Conversion Completed");
		}
	}
	
	// Here fileName should be a valid .xsvf file (but better do a quick check to be sure...)
	if (!fileName.endsWith(".xsvf", Qt::CaseInsensitive))
	{
		svfConsoleOutput->append("ERROR: The file '" + fileName + "' is not a valid .xsvf file!");
	}
	
	QString program = "XSVF_Sender.exe \"" + fileName + "\"";
	svfConsoleOutput->append("Running Command: " + program);
	
	if (svfProcess != NULL)
	{
		delete svfProcess;	
	}
	svfProcess = new QProcess(jtag);
	svfProcess->setProcessChannelMode(QProcess::MergedChannels);
	connect(svfProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(programjtagExitStatus(int, QProcess::ExitStatus)));
	connect(svfProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(programjtagOutput()));
	svfProcess->start(program, QIODevice::ReadOnly);

	if(svfProcess->waitForStarted())
	{
		svfConsoleOutput->append("XSVF Player Started...");
	}
	else
	{
		svfConsoleOutput->append("The XSVF Player could not be started.");
		svfConsoleOutput->append("Ensure XSVF_Sender.exe is in the same folder as this .exe");
		svfProcess->kill();
		jtag->setEnabled(true);
		return;
	}

	return;
}

/**
 * Called by the main window, tells the AVR tab what the temporary directory is
 */
void JTAGTab::SetTempDir(QString newDir)
{
	tempDir = newDir;
	//add a trailing "/" so folder construction is easier later on
	if (tempDir.at(tempDir.size()-1) != '/')
	{
		tempDir.append("/");
	}
	return;
}

