#include "MainWindow.h"
#include <QApplication>

#include <iostream>

using namespace std;

int main(int argc, char *argv[]){
	QApplication app(argc, argv);
	MainWindow *gui = new MainWindow();
	
	gui->show();
	
	return app.exec();



}
