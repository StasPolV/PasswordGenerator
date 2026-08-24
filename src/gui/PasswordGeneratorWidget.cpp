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

	QLineEdit* password_enter = new QLineEdit(this);
	password_enter->setMaximumHeight(100);
	password_enter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QToolButton* create_button = new QToolButton(this);
	create_button->setMaximumHeight(100);
	create_button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QToolButton* copy_button = new QToolButton(this);
	copy_button->setMaximumHeight(100);

	copy_button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	copy_button->setText("Copy");

	password_layout->addWidget(password_enter, 3);
	password_layout->addWidget(create_button, 1);
	password_layout->addWidget(copy_button, 1);

	PasswordLengthWidget* length_widget = new PasswordLengthWidget(this);

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

	QHBoxLayout* checkboxes_layout = new QHBoxLayout;
	checkboxes_layout->setContentsMargins(0, 0, 0, 0);
	checkboxes_layout->setSpacing(0);
	checkboxes_layout->addWidget(check_upper);
	checkboxes_layout->addWidget(check_lower);
	checkboxes_layout->addWidget(check_digits);
	checkboxes_layout->addWidget(check_symbols);

	main_layout->addLayout(checkboxes_layout);
}
