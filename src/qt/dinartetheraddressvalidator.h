// Copyright (c) 2011-2014 The Bitcoin Core developers
// Copyright (c) 2023 The Dinartether Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DINARTETHER_QT_DINTADDRESSVALIDATOR_H
#define DINARTETHER_QT_DINTADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class DinartetherAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit DinartetherAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Dinartether address widget validator, checks for a valid dinartether address.
 */
class DinartetherAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit DinartetherAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // DINARTETHER_QT_DINTADDRESSVALIDATOR_H
