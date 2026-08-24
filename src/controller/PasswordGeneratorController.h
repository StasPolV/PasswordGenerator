#pragma once

#include "PasswordGeneratorModel.h"
#include "PasswordGeneratorWidget.h"

#include <QObject>

class PasswordGeneratorController : public QObject
{
	Q_OBJECT

public:
	PasswordGeneratorController(PasswordGeneratorModel& model, PasswordGeneratorWidget& widget,
	                            QObject* parent = nullptr);

private:
	void SyncWidgetWithModel();

	PasswordGeneratorModel& m_model;
	PasswordGeneratorWidget& m_widget;
};
