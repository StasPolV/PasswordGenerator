#include "PasswordLengthWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QSpinBox>

PasswordLengthWidget::PasswordLengthWidget(QWidget* parent) : QWidget(parent)
{
	QLabel* label = new QLabel("Password Length: ", this);
	QSpinBox* spin_box = new QSpinBox(this);
	spin_box->setRange(6, 32);
	QSlider* slider = new QSlider(Qt::Orientation::Horizontal, this);
	slider->setRange(6, 32);

	connect(spin_box, &QSpinBox::valueChanged, slider, &QSlider::setValue);
	connect(slider, &QSlider::valueChanged, spin_box, &QSpinBox::setValue);

	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);
	layout->addWidget(label, 1);
	layout->addWidget(spin_box, 1);
	layout->addWidget(slider, 3);
}
