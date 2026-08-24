#include "PasswordGeneratorController.h"
#include "PasswordGeneratorModel.h"
#include "PasswordGeneratorWidget.h"

#include <QApplication>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	PasswordGeneratorModel model;
	PasswordGeneratorWidget widget;
	PasswordGeneratorController controller(model, widget);

	widget.show();

	return app.exec();
}
