#include "PasswordGeneratorWidget.h"

#include <QHBoxLayout>
#include <QLineEdit>
#include <QToolButton>
#include <QVBoxLayout>

PasswordGeneratorWidget::PasswordGeneratorWidget(QWidget* parent) : QWidget(parent)
{
	QHBoxLayout* password_layout = new QHBoxLayout(this);
	password_layout->setContentsMargins(0, 0, 0, 0);
	password_layout->setSpacing(0);

	QLineEdit* password_enter = new QLineEdit(this);
	password_enter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QToolButton* create_button = new QToolButton(this);
	create_button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QToolButton* push_button = new QToolButton(this);
	push_button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	push_button->setText("Copy");

	password_layout->addWidget(password_enter, 3);
	password_layout->addWidget(create_button, 1);
	password_layout->addWidget(push_button, 1);
}
