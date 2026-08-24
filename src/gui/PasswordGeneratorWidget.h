#pragma once

#include <QObject>
#include <QWidget>

class QLineEdit;

class PasswordGeneratorWidget : public QWidget
{
	Q_OBJECT

signals:
	void GenerateRequested();
	void UpperChanged(int state);
	void LowerChanged(int state);
	void DigitsChanged(int state);
	void SymbolsChanged(int state);
	void LengthChanged(int length);

public slots:
	void SetPassword(QString password);

public:
	explicit PasswordGeneratorWidget(QWidget* parent = nullptr);

private:
	QLineEdit* m_password_enter;
};
