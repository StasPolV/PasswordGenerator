#pragma once

#include <QWidget>

class QSlider;
class QSpinBox;

class PasswordLengthWidget : public QWidget
{
	Q_OBJECT

signals:
	void LengthChanged(int value);

public:
	explicit PasswordLengthWidget(QWidget* parent = nullptr);

	void SetRange(int min_value, int max_value);
	void SetValue(int value);

private:
	QSpinBox* m_spin_box;
	QSlider* m_slider;
};
