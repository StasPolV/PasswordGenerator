#pragma once

#include <QObject>
#include <QString>

class PasswordGeneratorModel : public QObject
{
	Q_OBJECT
signals:
	void PasswordGenerated(QString password);
public slots:
	void SetLength(int length) { m_length = length; }
	void SetUpperCase(bool upper_case) { m_upper_case = upper_case; }
	void SetLowerCase(bool lower_case) { m_lower_case = lower_case; }
	void SetDigits(bool digits) { m_digits = digits; }
	void SetSymbols(bool symbols) { m_symbols = symbols; }
	void GeneratePassword();

public:
	explicit PasswordGeneratorModel(QObject* parent = nullptr);
	PasswordGeneratorModel(int length, bool upper_case, bool lower_case, bool digits, bool symbols,
	                       QObject* parent = nullptr);

private:
	struct Alphabets
	{
		QString digits;
		QString upper;
		QString lower;
		QString symbols;
		QString combined;
	};

	void ValidateString(QString& s, const Alphabets& alphabets) const;
	Alphabets BuildAlphabets() const;

	int m_length;
	bool m_upper_case;
	bool m_lower_case;
	bool m_digits;
	bool m_symbols;
};
