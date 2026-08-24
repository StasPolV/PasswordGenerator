#pragma once

#include <QObject>
#include <QString>

class PasswordGeneratorModel : public QObject
{
	Q_OBJECT
signals:
	void PasswordGenerated(QString password);
public slots:
	void SetLength(int length);
	void SetUpperCase(bool upper_case);
	void SetLowerCase(bool lower_case);
	void SetDigits(bool digits);
	void SetSymbols(bool symbols);

	void GeneratePassword();

public:
	explicit PasswordGeneratorModel(QObject* parent = nullptr);
	PasswordGeneratorModel(int length, bool upper_case, bool lower_case, bool digits, bool symbols,
	                       QObject* parent = nullptr);

	static int MinLength();
	static int MaxLength();

	int Length() const { return m_length; }
	bool UpperCase() const { return m_upper_case; }
	bool LowerCase() const { return m_lower_case; }
	bool Digits() const { return m_digits; }
	bool Symbols() const { return m_symbols; }

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
