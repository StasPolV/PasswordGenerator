#include "PasswordGeneratorModel.h"

#include <QDebug>
#include <QRandomGenerator>

#include <algorithm>
#include <string>

namespace
{
	static constexpr int kMinLength = 6;
}  // namespace

PasswordGeneratorModel::PasswordGeneratorModel(QObject* parent)
    : QObject(parent), m_length(kMinLength), m_upper_case(true), m_lower_case(true), m_digits(true),
      m_symbols(true)
{}

PasswordGeneratorModel::PasswordGeneratorModel(int length, bool upper_case, bool lower_case,
                                               bool digits, bool symbols, QObject* parent)
    : QObject(parent), m_length(std::max(length, kMinLength)), m_upper_case(upper_case),
      m_lower_case(lower_case), m_digits(digits), m_symbols(symbols)
{}

void PasswordGeneratorModel::ValidateString(QString& s, const Alphabets& alphabets) const
{
	QRandomGenerator* rng = QRandomGenerator::system();

	enum class Category
	{
		Digit,
		Upper,
		Lower,
		Symbol,
		None
	};

	auto classify = [&](QChar c) -> Category
	{
		if (c.isDigit())
			return Category::Digit;
		if (c.isUpper())
			return Category::Upper;
		if (c.isLower())
			return Category::Lower;
		if (alphabets.symbols.contains(c))
			return Category::Symbol;
		return Category::None;
	};

	std::array<std::vector<int>, 4> positions_by_category;
	for (int i = 0; i < s.length(); ++i)
	{
		Category cat = classify(s[i]);
		if (cat != Category::None)
			positions_by_category[static_cast<int>(cat)].push_back(i);
	}

	struct CategoryInfo
	{
		bool enabled;
		Category cat;
		const QString* alphabet;
	};
	const std::array<CategoryInfo, 4> categories = {
	        {
             {m_digits, Category::Digit, &alphabets.digits},
             {m_upper_case, Category::Upper, &alphabets.upper},
             {m_lower_case, Category::Lower, &alphabets.lower},
             {m_symbols, Category::Symbol, &alphabets.symbols},
	         }
    };

	std::vector<const QString*> missing_alphabets;
	std::vector<bool> is_protected(s.length(), false);

	for (const auto& info : categories)
	{
		if (!info.enabled)
			continue;

		auto& positions = positions_by_category[static_cast<int>(info.cat)];
		if (positions.empty())
		{
			missing_alphabets.push_back(info.alphabet);
		}
		else
		{
			int idx = rng->bounded(static_cast<int>(positions.size()));
			is_protected[positions[idx]] = true;
		}
	}

	if (missing_alphabets.empty())
		return;

	std::vector<int> free_positions;
	free_positions.reserve(s.length());
	for (int i = 0; i < s.length(); ++i)
	{
		if (!is_protected[i])
			free_positions.push_back(i);
	}

	if (missing_alphabets.size() > free_positions.size())
	{
		qWarning() << "Password length too small to satisfy all categories safely";
		missing_alphabets.resize(free_positions.size());
	}

	std::shuffle(free_positions.begin(), free_positions.end(), *rng);

	for (size_t i = 0; i < missing_alphabets.size(); ++i)
	{
		const QString& alphabet = *missing_alphabets[i];
		int pos = free_positions[i];
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
