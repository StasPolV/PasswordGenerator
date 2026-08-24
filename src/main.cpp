#include "PasswordGeneratorController.h"
#include "PasswordGeneratorModel.h"
#include "PasswordGeneratorWidget.h"

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QStyleFactory>

namespace
{
	void ApplyApplicationStyle(QApplication& app)
	{
		QApplication::setStyle(QStyleFactory::create("Fusion"));

		QFile style_file(":/style.qss");
		if (!style_file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			qWarning() << "Failed to load the application style sheet";
			return;
		}

		app.setStyleSheet(QString::fromUtf8(style_file.readAll()));
	}
}  // namespace

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	ApplyApplicationStyle(app);

	PasswordGeneratorModel model;
	PasswordGeneratorWidget widget;
	PasswordGeneratorController controller(model, widget);

	widget.show();

	return app.exec();
}
