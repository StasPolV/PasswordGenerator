#include "PasswordGeneratorModel.h"

PasswordGeneratorModel::PasswordGeneratorModel(QObject* parent) : QObject(parent) {}

PasswordGeneratorModel::PasswordGeneratorModel(int length, bool upper_case, bool lower_case,
                                               bool digits, bool symbols, QObject* parent)
    : QObject(parent), m_length(length), m_upper_case(upper_case), m_lower_case(lower_case),
      m_digits(digits), m_symbols(m_symbols)
{}
