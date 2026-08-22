#pragma once

#include <QObject>

class PasswordGeneratorModel : public QObject
{
	Q_OBJECT

public slots:
	void SetLength(int length) { m_length = length; }
	void SetUpperCase(bool upper_case) { m_upper_case = upper_case; }
	void SetLowerCase(bool lower_case) { m_lower_case = lower_case; }
	void SetDigits(bool digits) { m_digits = digits; }
	void SetSymbols(bool symbols) { m_symbols = symbols; }

public:
	explicit PasswordGeneratorModel(QObject* parent = nullptr);
	PasswordGeneratorModel(int length, bool upper_case, bool lower_case, bool digits, bool symbols,
	                       QObject* parent = nullptr);

private:
	int m_length;
	bool m_upper_case;
	bool m_lower_case;
	bool m_digits;
	bool m_symbols;
};
