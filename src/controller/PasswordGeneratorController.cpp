#include "PasswordGeneratorController.h"

PasswordGeneratorController::PasswordGeneratorController(PasswordGeneratorModel& model,
                                                         PasswordGeneratorWidget& widget,
                                                         QObject* parent)
    : QObject(parent), m_model(model), m_widget(widget)
{
	connect(&m_model, &PasswordGeneratorModel::PasswordGenerated, &m_widget,
	        &PasswordGeneratorWidget::SetPassword);

	connect(&m_widget, &PasswordGeneratorWidget::GenerateRequested, &m_model,
	        &PasswordGeneratorModel::GeneratePassword);
	connect(&m_widget, &PasswordGeneratorWidget::UpperChanged, &m_model,
	        &PasswordGeneratorModel::SetUpperCase);
	connect(&m_widget, &PasswordGeneratorWidget::LowerChanged, &m_model,
	        &PasswordGeneratorModel::SetLowerCase);
	connect(&m_widget, &PasswordGeneratorWidget::DigitsChanged, &m_model,
	        &PasswordGeneratorModel::SetDigits);
	connect(&m_widget, &PasswordGeneratorWidget::SymbolsChanged, &m_model,
	        &PasswordGeneratorModel::SetSymbols);
	connect(&m_widget, &PasswordGeneratorWidget::LengthChanged, &m_model,
	        &PasswordGeneratorModel::SetLength);
}
