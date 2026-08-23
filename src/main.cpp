#include "PasswordGeneratorWidget.h"

#include <QApplication>

#include <iostream>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	PasswordGeneratorWidget widget;
	widget.show();

	return app.exec();
}
