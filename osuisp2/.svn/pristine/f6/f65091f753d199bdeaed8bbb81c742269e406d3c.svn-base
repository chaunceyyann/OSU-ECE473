/**
 * File: Message.h
 * @class Message, extends QDialog
 * @author Michael Spray (contact @ (503) 457-6351, spraym@onid.orst.edu)
 * NOTE: For a description of how the class operates, please see the corresponding
 * cpp file.
 *
 * Description: This file contains the appropriate definitions for variables and
 * functions that drive the Message class.
 */
//make sure we only include this once
#ifndef MESSAGEH
#define MESSAGEH

#include <QDialog>

//other classes we'll be using
class QLabel;
class QPushButton;

class Message : public QDialog{
public:
	//constructor
	Message(QWidget *parent = 0);
	//used to update the message
	void changeMessage(QString newMessage);	
private:
	//label that holds the current message that will be displayed by the dialog
	QLabel *label;
	//button used to close the Message dialog
	QPushButton *okay;
};
#endif

