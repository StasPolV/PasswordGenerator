#include "PasswordLengthWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QSignalBlocker>
#include <QSlider>
#include <QSpinBox>

PasswordLengthWidget::PasswordLengthWidget(QWidget* parent) : QWidget(parent)
{
	QLabel* label = new QLabel("Password Length: ", this);

	m_spin_box = new QSpinBox(this);
	m_spin_box->setKeyboardTracking(false);

	m_slider = new QSlider(Qt::Orientation::Horizontal, this);

	connect(m_spin_box, &QSpinBox::valueChanged, m_slider, &QSlider::setValue);
	connect(m_slider, &QSlider::valueChanged, m_spin_box, &QSpinBox::setValue);

	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);
	layout->addWidget(label, 1);
	layout->addWidget(m_spin_box, 1);
	layout->addWidget(m_slider, 3);

	connect(m_spin_box, &QSpinBox::valueChanged, this, &PasswordLengthWidget::LengthChanged);
}

void PasswordLengthWidget::SetRange(int min_value, int max_value)
{
	const QSignalBlocker spin_blocker(m_spin_box);
	const QSignalBlocker slider_blocker(m_slider);

	m_spin_box->setRange(min_value, max_value);
	m_slider->setRange(min_value, max_value);
	m_slider->setValue(m_spin_box->value());
}

void PasswordLengthWidget::SetValue(int value)
{
	const QSignalBlocker spin_blocker(m_spin_box);
	const QSignalBlocker slider_blocker(m_slider);

	m_spin_box->setValue(value);
	m_slider->setValue(m_spin_box->value());
}
