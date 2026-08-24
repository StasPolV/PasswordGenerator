#include "PasswordGeneratorWidget.h"

#include "PasswordLengthWidget.h"

#include <QAbstractButton>
#include <QButtonGroup>
#include <QCheckBox>
#include <QClipboard>
#include <QGuiApplication>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QSignalBlocker>
#include <QToolButton>
#include <QVBoxLayout>

#include <algorithm>

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
	m_password_enter->setReadOnly(true);
	QToolButton* create_button = new QToolButton(this);
	create_button->setMaximumHeight(100);
	create_button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QToolButton* copy_button = new QToolButton(this);
	copy_button->setMaximumHeight(100);

	connect(create_button, &QToolButton::clicked, this,
	        &PasswordGeneratorWidget::GenerateRequested);

	copy_button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	copy_button->setText("Copy");
	connect(copy_button, &QToolButton::clicked, this,
	        [this]()
	        {
		        QClipboard* clipboard = QGuiApplication::clipboard();
		        clipboard->setText(m_password_enter->text());
	        });

	password_layout->addWidget(m_password_enter, 3);
	password_layout->addWidget(create_button, 1);
	password_layout->addWidget(copy_button, 1);

	m_length_widget = new PasswordLengthWidget(this);
	connect(m_length_widget, &PasswordLengthWidget::LengthChanged, this,
	        &PasswordGeneratorWidget::LengthChanged);

	main_layout->addLayout(password_layout);
	main_layout->addWidget(m_length_widget);

	m_checkbox_group = new QButtonGroup(this);
	m_checkbox_group->setExclusive(false);
	m_check_upper = new QCheckBox("Uppercase", this);
	m_check_lower = new QCheckBox("Lower Case", this);
	m_check_digits = new QCheckBox("Digits", this);
	m_check_symbols = new QCheckBox("Symbols", this);
	m_checkbox_group->addButton(m_check_upper);
	m_checkbox_group->addButton(m_check_lower);
	m_checkbox_group->addButton(m_check_digits);
	m_checkbox_group->addButton(m_check_symbols);
	for (auto* button : m_checkbox_group->buttons())
	{
		button->setChecked(true);
	}

	connect(m_check_upper, &QCheckBox::checkStateChanged, this,
	        &PasswordGeneratorWidget::UpperChanged);
	connect(m_check_lower, &QCheckBox::checkStateChanged, this,
	        &PasswordGeneratorWidget::LowerChanged);
	connect(m_check_digits, &QCheckBox::checkStateChanged, this,
	        &PasswordGeneratorWidget::DigitsChanged);
	connect(m_check_symbols, &QCheckBox::checkStateChanged, this,
	        &PasswordGeneratorWidget::SymbolsChanged);

	QHBoxLayout* checkboxes_layout = new QHBoxLayout;
	checkboxes_layout->setContentsMargins(0, 0, 0, 0);
	checkboxes_layout->setSpacing(0);
	checkboxes_layout->addWidget(m_check_upper);
	checkboxes_layout->addWidget(m_check_lower);
	checkboxes_layout->addWidget(m_check_digits);
	checkboxes_layout->addWidget(m_check_symbols);

	main_layout->addLayout(checkboxes_layout);

	const auto buttons = m_checkbox_group->buttons();
	for (auto* button : buttons)
	{
		connect(button, &QAbstractButton::toggled, this,
		        [this]() { UpdateCheckboxAvailability(); });
	}

	UpdateCheckboxAvailability();
}

void PasswordGeneratorWidget::SetPassword(QString password)
{
	m_password_enter->setText(password);
}

void PasswordGeneratorWidget::SetLengthRange(int min_length, int max_length)
{
	m_length_widget->SetRange(min_length, max_length);
}

void PasswordGeneratorWidget::SetLength(int length)
{
	m_length_widget->SetValue(length);
}

void PasswordGeneratorWidget::SetUpperCase(bool upper_case)
{
	SetCheckboxSilently(m_check_upper, upper_case);
}

void PasswordGeneratorWidget::SetLowerCase(bool lower_case)
{
	SetCheckboxSilently(m_check_lower, lower_case);
}

void PasswordGeneratorWidget::SetDigits(bool digits)
{
	SetCheckboxSilently(m_check_digits, digits);
}

void PasswordGeneratorWidget::SetSymbols(bool symbols)
{
	SetCheckboxSilently(m_check_symbols, symbols);
}

void PasswordGeneratorWidget::SetCheckboxSilently(QCheckBox* checkbox, bool checked)
{
	{
		const QSignalBlocker blocker(checkbox);
		checkbox->setChecked(checked);
	}

	UpdateCheckboxAvailability();
}

void PasswordGeneratorWidget::UpdateCheckboxAvailability()
{
	const auto buttons = m_checkbox_group->buttons();
	const auto checked_count =
	        std::count_if(buttons.cbegin(), buttons.cend(),
	                      [](const QAbstractButton* button) { return button->isChecked(); });

	for (auto* button : buttons)
	{
		const bool is_last_checked = (checked_count == 1) && button->isChecked();

		button->setEnabled(!is_last_checked);
		button->setToolTip(is_last_checked ? tr("At least one character set must remain enabled")
		                                   : QString());
	}
}
