// Copyright (c) 2011-2016 The Bitcoin Core developers
// Copyright (c) 2023 The Dinartether Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DINARTETHER_QT_CURRENCYUNITS_H
#define DINARTETHER_QT_CURRENCYUNITS_H

#include <QString>
#include <array>

/** Currency unit definitions. Stores basic title and symbol for a dint swap asset,
 * as well as how many decimals to format the dispaly with.
*/
struct CurrencyUnitDetails
{
    const char* Header;
    const char* Ticker;
    float Scalar;
    int Decimals;
};

class CurrencyUnits
{
public:
    static std::array<CurrencyUnitDetails, 5> CurrencyOptions;

    static int count() {
        return CurrencyOptions.size();
    }
};

#endif // DINARTETHER_QT_CURRENCYUNITS_H
