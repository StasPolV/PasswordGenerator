#pragma once

#include <QWidget>

class QButtonGroup;
class QCheckBox;
class QLineEdit;

class PasswordLengthWidget;

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

	void SetLengthRange(int min_length, int max_length);
	void SetLength(int length);
	void SetUpperCase(bool upper_case);
	void SetLowerCase(bool lower_case);
	void SetDigits(bool digits);
	void SetSymbols(bool symbols);

private:
	void UpdateCheckboxAvailability();
	void SetCheckboxSilently(QCheckBox* checkbox, bool checked);

	QLineEdit* m_password_enter;
	PasswordLengthWidget* m_length_widget;
	QButtonGroup* m_checkbox_group;
	QCheckBox* m_check_upper;
	QCheckBox* m_check_lower;
	QCheckBox* m_check_digits;
	QCheckBox* m_check_symbols;
};
