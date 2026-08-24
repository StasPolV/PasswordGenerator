#include "PasswordGeneratorController.h"
#include "PasswordGeneratorModel.h"
#include "PasswordGeneratorWidget.h"

#include <QApplication>

#include <iostream>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	PasswordGeneratorWidget widget;
	widget.show();
	PasswordGeneratorModel model;
	PasswordGeneratorController controller(model, widget);

	return app.exec();
}
