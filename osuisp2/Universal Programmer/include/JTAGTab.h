/**
 * File: JTAGTab.cpp
 * @class JTAGTab
 * @author Ben Porter
 * @author Jace Akerlund (akerlunj@onid.orst.edu)
 * @author Michael Spray (spraym@onid.orst.edu)
 * NOTE: For comments about the meaning of the variables, please see
 * the corresponding header file.
 *
 * To learn more about the Tekbots program: http://www.eecs.oregonstate.edu/tekbots.html
 *
 * @brief This file contains persistant objects and function definition for 
 * the JTAG tab. 
 */
 
#ifndef JTAGTAB_H
#define JTAGTAB_H

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
#include <QTemporaryFile>
#include <QFile>
#include "Message.h"

using namespace std;

//class definition
class JTAGTab : public QWidget
{
	//set this as an object
	Q_OBJECT

public:

	JTAGTab();
	~JTAGTab();

	QWidget *getWidget();

	void tabChanged(int index);
	
// Qt uses these methods for event callbacks (button presses, etc)
public slots:

	//opens up a file browser so user can select a .hex file for SVF
	void OpenXSVFBrowse();
	void RunXSVFPlayer();

	void programjtagExitStatus(int exitCode, QProcess::ExitStatus exit_status);
	void programjtagOutput();
	void SetTempDir(QString newDir);

private:

	QWidget	*jtag;
	QProcess *svfProcess;
	
	// XSVF/SVF Runner Items
	QGroupBox *SVFboxGroup;
	QLineEdit *SVFFileOutput;
	QPushButton	*SVFFileBrowse;

	QPushButton *runSVF;
	QTextEdit *svfConsoleOutput;
	QProgressBar *svfProgress;
	QString	SVFFilePath;
	QString tempDir;
};
#endif




