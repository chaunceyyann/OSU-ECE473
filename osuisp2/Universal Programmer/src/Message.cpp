/**
 * File: Message.cpp
 * @class Message
 * @author Michael Spray (contact @ (503) 457-6351, spraym@onid.orst.edu)
 * NOTE: For comments about the meaning of the variables, please see
 * the corresponding header file.
 *
 * Description: This file contains the code for the dialog box is probably the most
 * "useless" and at the same time the most used.  This merely prints a message, assigned
 * by changeMessage.  It is good for letting the user know the status of certain operations.
 */

#include <QtGui>
#include "Message.h"

/**
 *@constructor
 */
Message::Message(QWidget *parent) : QDialog(parent){
	//layout variables, V = vertical
	QVBoxLayout *Whole			= new QVBoxLayout;
		
	//get components initialized
	//default message is... no message
	label = new QLabel(tr("No Message"));
	
	//button to close the window after the user has read the message (hopefully)
	okay = new QPushButton(tr("Okay"));
	okay->setEnabled(true);
	okay->setDefault(true);
	
	//set up signal and socket connections
	//closes the dialog box
	connect(okay,SIGNAL(clicked()),this,SLOT(close()));

	//start making layout
	//put the label above the button
	Whole->addWidget(label);
	Whole->addWidget(okay);
	
	//set the layout
	setLayout(Whole);
	return;

}

/**
 *@method changeMessage
 *
 *Updates what the message dialog should say when shown
 */
void Message::changeMessage(QString newMessage){
	label->setText(newMessage);
	return;
}

