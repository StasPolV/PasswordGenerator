#include "PasswordGeneratorWidget.h"

#include "PasswordLengthWidget.h"

#include <QButtonGroup>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QToolButton>
#include <QVBoxLayout>

PasswordGeneratorWidget::PasswordGeneratorWidget(QWidget* parent) : QWidget(parent)
{
	QVBoxLayout* main_layout = new QVBoxLayout(this);
	main_layout->setSpacing(5);

	QHBoxLayout* password_layout = new QHBoxLayout;
	password_layout->setContentsMargins(0, 0, 0, 0);
	password_layout->setSpacing(0);

	m_password_enter = new QLineEdit(this);
	m_password_enter->setMaximumHeight(100);
	m_password_enter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QToolButton* create_button = new QToolButton(this);
	create_button->setMaximumHeight(100);
	create_button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QToolButton* copy_button = new QToolButton(this);
	copy_button->setMaximumHeight(100);

	copy_button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	copy_button->setText("Copy");

	password_layout->addWidget(m_password_enter, 3);
	password_layout->addWidget(create_button, 1);
	password_layout->addWidget(copy_button, 1);

	PasswordLengthWidget* length_widget = new PasswordLengthWidget(this);
	connect(length_widget, &PasswordLengthWidget::LengthChanged, this,
	        &PasswordGeneratorWidget::LengthChanged);

	main_layout->addLayout(password_layout);
	main_layout->addWidget(length_widget);

	QButtonGroup* checkbox_group = new QButtonGroup(this);
	checkbox_group->setExclusive(false);
	QCheckBox* check_upper = new QCheckBox("Uppercase", this);
	QCheckBox* check_lower = new QCheckBox("Lower Case", this);
	QCheckBox* check_digits = new QCheckBox("Digits", this);
	QCheckBox* check_symbols = new QCheckBox("Symbols", this);
	checkbox_group->addButton(check_upper);
	checkbox_group->addButton(check_lower);
	checkbox_group->addButton(check_digits);
	checkbox_group->addButton(check_symbols);
	for (auto button : checkbox_group->buttons())
	{
		button->setChecked(true);
	}

	connect(check_upper, &QCheckBox::checkStateChanged, this,
	        &PasswordGeneratorWidget::UpperChanged);
	connect(check_lower, &QCheckBox::checkStateChanged, this,
	        &PasswordGeneratorWidget::LowerChanged);
	connect(check_digits, &QCheckBox::checkStateChanged, this,
	        &PasswordGeneratorWidget::DigitsChanged);
	connect(check_symbols, &QCheckBox::checkStateChanged, this,
	        &PasswordGeneratorWidget::SymbolsChanged);

	QHBoxLayout* checkboxes_layout = new QHBoxLayout;
	checkboxes_layout->setContentsMargins(0, 0, 0, 0);
	checkboxes_layout->setSpacing(0);
	checkboxes_layout->addWidget(check_upper);
	checkboxes_layout->addWidget(check_lower);
	checkboxes_layout->addWidget(check_digits);
	checkboxes_layout->addWidget(check_symbols);

	main_layout->addLayout(checkboxes_layout);

	const auto buttons = checkbox_group->buttons();
	for (auto* btn : buttons)
	{
		connect(btn, &QAbstractButton::toggled, this,
		        [this, btn, checkbox_group](bool checked)
		        {
			        if (!checked)
			        {
				        bool any_checked = false;
				        for (auto* b : checkbox_group->buttons())
				        {
					        if (b->isChecked())
					        {
						        any_checked = true;
						        emit GenerateRequested();
						        break;
					        }
				        }
				        if (!any_checked)
				        {
					        btn->blockSignals(true);
					        btn->setChecked(true);
					        btn->blockSignals(false);
				        }
			        }
			        else
			        {
				        emit GenerateRequested();
			        }
		        });
	}
}

void PasswordGeneratorWidget::SetPassword(QString password) {}
