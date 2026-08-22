#include "PasswordGeneratorModel.h"

#include <QRandomGenerator>

#include <algorithm>
#include <string>

namespace
{
	static constexpr int kMinLength = 6;
	static constexpr int kStandartLength = 8;
}  // namespace

PasswordGeneratorModel::PasswordGeneratorModel(QObject* parent)
    : QObject(parent), m_length(std::max(kStandartLength, kMinLength)), m_upper_case(true),
      m_lower_case(true), m_digits(true), m_symbols(true)
{}

PasswordGeneratorModel::PasswordGeneratorModel(int length, bool upper_case, bool lower_case,
                                               bool digits, bool symbols, QObject* parent)
    : QObject(parent), m_length(std::max(length, kMinLength)), m_upper_case(upper_case),
      m_lower_case(lower_case), m_digits(digits), m_symbols(symbols)
{}

void PasswordGeneratorModel::ValidateString(QString& s, const Alphabets& alphabets) const
{
	QRandomGenerator* rng = QRandomGenerator::system();

	struct Category
	{
		bool enabled;
		bool (*predicate)(QChar, const QString&);
		const QString* alphabet;
	};

	auto has_digit = [](QChar c)
	{
		return c.isDigit();
	};
	auto has_upper = [](QChar c)
	{
		return c.isUpper();
	};
	auto has_lower = [](QChar c)
	{
		return c.isLower();
	};
	auto has_symbol = [&](QChar c)
	{
		return alphabets.symbols.contains(c);
	};

	std::vector<const QString*> missing_alphabets;

	if (m_digits && !std::any_of(s.begin(), s.end(), has_digit))
		missing_alphabets.push_back(&alphabets.digits);
	if (m_upper_case && !std::any_of(s.begin(), s.end(), has_upper))
		missing_alphabets.push_back(&alphabets.upper);
	if (m_lower_case && !std::any_of(s.begin(), s.end(), has_lower))
		missing_alphabets.push_back(&alphabets.lower);
	if (m_symbols && !std::any_of(s.begin(), s.end(), has_symbol))
		missing_alphabets.push_back(&alphabets.symbols);

	if (missing_alphabets.empty())
		return;

	std::vector<int> positions(s.length());
	std::iota(positions.begin(), positions.end(), 0);
	std::shuffle(positions.begin(), positions.end(), *rng);

	for (size_t i = 0; i < missing_alphabets.size(); ++i)
	{
		const QString& alphabet = *missing_alphabets[i];
		int pos = positions[i];
		s[pos] = alphabet[rng->bounded(alphabet.length())];
	}
}

void PasswordGeneratorModel::GeneratePassword()
{
	QRandomGenerator* rng = QRandomGenerator::system();
	const Alphabets alphabets = BuildAlphabets();

	QString password;
	password.resize(m_length);

	const int alphabet_size = alphabets.combined.length();
	for (int i = 0; i < m_length; ++i)
	{
		password[i] = alphabets.combined[rng->bounded(alphabet_size)];
	}

	ValidateString(password, alphabets);

	emit PasswordGenerated(password);
}

PasswordGeneratorModel::Alphabets PasswordGeneratorModel::BuildAlphabets() const
{
	Alphabets a;
	a.digits = "0123456789";
	a.upper = "QWERTYUIOPASDFGHJKLZXCVBNM";
	a.lower = "qwertyuiopasdfghjklzxcvbnm";
	a.symbols = "!#$%&'()*+,-./:;<=>?@[\\]^_{|}~`";

	if (m_digits)
		a.combined += a.digits;
	if (m_upper_case)
		a.combined += a.upper;
	if (m_lower_case)
		a.combined += a.lower;
	if (m_symbols)
		a.combined += a.symbols;

	return a;
}
