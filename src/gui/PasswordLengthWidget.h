#pragma once

#include <QObject>
#include <QWidget>

class PasswordLengthWidget : public QWidget
{
	Q_OBJECT

signals:
	void LengthChanged(int value);

public:
	explicit PasswordLengthWidget(QWidget* parent = nullptr);

private:
};
