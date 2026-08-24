#include "PasswordGeneratorModel.h"

#include <QObject>
#include <QString>

#include <gtest/gtest.h>

namespace
{
	const QString kDigits = QStringLiteral("0123456789");
	const QString kUpper = QStringLiteral("QWERTYUIOPASDFGHJKLZXCVBNM");
	const QString kLower = QStringLiteral("qwertyuiopasdfghjklzxcvbnm");
	const QString kSymbols = QStringLiteral("!#$%&'()*+,-./:;<=>?@[\\]^_{|}~`");

	constexpr int kRepeatCount = 200;

	class PasswordCapture
	{
	public:
		explicit PasswordCapture(PasswordGeneratorModel& model)
		{
			QObject::connect(&model, &PasswordGeneratorModel::PasswordGenerated, &m_context,
			                 [this](const QString& password)
			                 {
				                 m_last = password;
				                 ++m_count;
			                 });
		}

		QString Last() const { return m_last; }
		int Count() const { return m_count; }

		void Reset()
		{
			m_last.clear();
			m_count = 0;
		}

	private:
		QObject m_context;
		QString m_last;
		int m_count = 0;
	};

	bool ConsistsOnlyOf(const QString& password, const QString& alphabet)
	{
		for (const QChar symbol : password)
		{
			if (!alphabet.contains(symbol))
				return false;
		}

		return true;
	}

	bool ContainsAnyOf(const QString& password, const QString& alphabet)
	{
		for (const QChar symbol : password)
		{
			if (alphabet.contains(symbol))
				return true;
		}

		return false;
	}
}  // namespace

TEST(PasswordGeneratorModelTest, LengthBoundsAreOrdered)
{
	EXPECT_LT(PasswordGeneratorModel::MinLength(), PasswordGeneratorModel::MaxLength());
	EXPECT_GT(PasswordGeneratorModel::MinLength(), 0);
}

TEST(PasswordGeneratorModelTest, DefaultConstructedModelEnablesEveryCategory)
{
	const PasswordGeneratorModel model;

	EXPECT_EQ(model.Length(), PasswordGeneratorModel::MinLength());
	EXPECT_TRUE(model.UpperCase());
	EXPECT_TRUE(model.LowerCase());
	EXPECT_TRUE(model.Digits());
	EXPECT_TRUE(model.Symbols());
}

TEST(PasswordGeneratorModelTest, ConstructorStoresFlagsAsGiven)
{
	const PasswordGeneratorModel model(10, true, false, true, false);

	EXPECT_EQ(model.Length(), 10);
	EXPECT_TRUE(model.UpperCase());
	EXPECT_FALSE(model.LowerCase());
	EXPECT_TRUE(model.Digits());
	EXPECT_FALSE(model.Symbols());
}

TEST(PasswordGeneratorModelTest, ConstructorClampsLengthBelowMinimum)
{
	const PasswordGeneratorModel model(PasswordGeneratorModel::MinLength() - 1, true, true, true,
	                                   true);

	EXPECT_EQ(model.Length(), PasswordGeneratorModel::MinLength());
}

TEST(PasswordGeneratorModelTest, ConstructorClampsLengthAboveMaximum)
{
	const PasswordGeneratorModel model(PasswordGeneratorModel::MaxLength() + 1, true, true, true,
	                                   true);

	EXPECT_EQ(model.Length(), PasswordGeneratorModel::MaxLength());
}

TEST(PasswordGeneratorModelTest, SetLengthClampsBelowMinimum)
{
	PasswordGeneratorModel model;
	model.SetLength(-100);

	EXPECT_EQ(model.Length(), PasswordGeneratorModel::MinLength());
}

TEST(PasswordGeneratorModelTest, SetLengthClampsAboveMaximum)
{
	PasswordGeneratorModel model;
	model.SetLength(PasswordGeneratorModel::MaxLength() + 100);

	EXPECT_EQ(model.Length(), PasswordGeneratorModel::MaxLength());
}

TEST(PasswordGeneratorModelTest, SettersStoreFlags)
{
	PasswordGeneratorModel model;

	model.SetUpperCase(false);
	EXPECT_FALSE(model.UpperCase());

	model.SetLowerCase(false);
	EXPECT_FALSE(model.LowerCase());

	model.SetDigits(false);
	EXPECT_FALSE(model.Digits());

	model.SetSymbols(false);
	EXPECT_FALSE(model.Symbols());

	model.SetUpperCase(true);
	EXPECT_TRUE(model.UpperCase());
}

TEST(PasswordGeneratorModelTest, GeneratePasswordEmitsExactlyOnce)
{
	PasswordGeneratorModel model;
	PasswordCapture capture(model);

	model.GeneratePassword();

	EXPECT_EQ(capture.Count(), 1);
}

TEST(PasswordGeneratorModelTest, EverySetterTriggersGeneration)
{
	PasswordGeneratorModel model;
	PasswordCapture capture(model);

	model.SetLength(12);
	EXPECT_EQ(capture.Count(), 1);

	model.SetUpperCase(false);
	EXPECT_EQ(capture.Count(), 2);

	model.SetLowerCase(true);
	EXPECT_EQ(capture.Count(), 3);

	model.SetDigits(false);
	EXPECT_EQ(capture.Count(), 4);

	model.SetSymbols(true);
	EXPECT_EQ(capture.Count(), 5);
}

TEST(PasswordGeneratorModelTest, GeneratedPasswordMatchesRequestedLength)
{
	PasswordGeneratorModel model;
	PasswordCapture capture(model);

	for (int length = PasswordGeneratorModel::MinLength();
	     length <= PasswordGeneratorModel::MaxLength(); ++length)
	{
		model.SetLength(length);
		EXPECT_EQ(capture.Last().length(), length);
	}
}

TEST(PasswordGeneratorModelTest, DigitsOnlyPasswordConsistsOfDigits)
{
	PasswordGeneratorModel model(16, false, false, true, false);
	PasswordCapture capture(model);

	model.GeneratePassword();

	EXPECT_TRUE(ConsistsOnlyOf(capture.Last(), kDigits));
}

TEST(PasswordGeneratorModelTest, UpperOnlyPasswordConsistsOfUpperCaseLetters)
{
	PasswordGeneratorModel model(16, true, false, false, false);
	PasswordCapture capture(model);

	model.GeneratePassword();

	EXPECT_TRUE(ConsistsOnlyOf(capture.Last(), kUpper));
}

TEST(PasswordGeneratorModelTest, LowerOnlyPasswordConsistsOfLowerCaseLetters)
{
	PasswordGeneratorModel model(16, false, true, false, false);
	PasswordCapture capture(model);

	model.GeneratePassword();

	EXPECT_TRUE(ConsistsOnlyOf(capture.Last(), kLower));
}

TEST(PasswordGeneratorModelTest, SymbolsOnlyPasswordConsistsOfSymbols)
{
	PasswordGeneratorModel model(16, false, false, false, true);
	PasswordCapture capture(model);

	model.GeneratePassword();

	EXPECT_TRUE(ConsistsOnlyOf(capture.Last(), kSymbols));
}

TEST(PasswordGeneratorModelTest, SymbolAlphabetExcludesDoubleQuoteAndSpace)
{
	PasswordGeneratorModel model(PasswordGeneratorModel::MaxLength(), false, false, false, true);
	PasswordCapture capture(model);

	for (int i = 0; i < kRepeatCount; ++i)
	{
		model.GeneratePassword();

		ASSERT_FALSE(capture.Last().contains(QChar('"')));
		ASSERT_FALSE(capture.Last().contains(QChar(' ')));
	}
}

TEST(PasswordGeneratorModelTest, DisabledCategoriesNeverAppear)
{
	PasswordGeneratorModel model(PasswordGeneratorModel::MaxLength(), false, true, true, false);
	PasswordCapture capture(model);

	for (int i = 0; i < kRepeatCount; ++i)
	{
		model.GeneratePassword();

		ASSERT_FALSE(ContainsAnyOf(capture.Last(), kUpper));
		ASSERT_FALSE(ContainsAnyOf(capture.Last(), kSymbols));
	}
}

TEST(PasswordGeneratorModelTest, EveryEnabledCategoryAppearsAtMinimumLength)
{
	PasswordGeneratorModel model(PasswordGeneratorModel::MinLength(), true, true, true, true);
	PasswordCapture capture(model);

	for (int i = 0; i < kRepeatCount; ++i)
	{
		model.GeneratePassword();

		ASSERT_TRUE(ContainsAnyOf(capture.Last(), kDigits));
		ASSERT_TRUE(ContainsAnyOf(capture.Last(), kUpper));
		ASSERT_TRUE(ContainsAnyOf(capture.Last(), kLower));
		ASSERT_TRUE(ContainsAnyOf(capture.Last(), kSymbols));
	}
}

TEST(PasswordGeneratorModelTest, EnabledCategoryStillAppearsAfterToggling)
{
	PasswordGeneratorModel model;
	PasswordCapture capture(model);

	model.SetUpperCase(false);
	model.SetLowerCase(false);
	model.SetSymbols(false);

	for (int i = 0; i < kRepeatCount; ++i)
	{
		model.GeneratePassword();

		ASSERT_TRUE(ConsistsOnlyOf(capture.Last(), kDigits));
	}
}

TEST(PasswordGeneratorModelTest, EmptyAlphabetYieldsEmptyPassword)
{
	PasswordGeneratorModel model(16, false, false, false, false);
	PasswordCapture capture(model);

	model.GeneratePassword();

	EXPECT_EQ(capture.Count(), 1);
	EXPECT_TRUE(capture.Last().isEmpty());
}

TEST(PasswordGeneratorModelTest, ConsecutivePasswordsDiffer)
{
	PasswordGeneratorModel model(PasswordGeneratorModel::MaxLength(), true, true, true, true);
	PasswordCapture capture(model);

	model.GeneratePassword();
	const QString first = capture.Last();

	model.GeneratePassword();
	const QString second = capture.Last();

	EXPECT_NE(first, second);
}
