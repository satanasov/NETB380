#ifndef EP_CUSTOMFUNCTIONS_H
#define EP_CUSTOMFUNCTIONS_H

#include <QString>
#include <QList>
#include "ep_customtypes.h"

namespace EP_CustomFunctions{
    /*Simple function to translate QString to EP_Currency type.*/
    EP_Currencies translateStringToCurrency(QString currentSelcetedCurrency);
    QString translateCurrencyToString(EP_Currencies currentSelectedCurrency);
    QString adapatCurrency(double ValueToAdapt, EP_Currencies currentCurrency, EP_Currencies selectedCurrency);

    /*const*/
    extern const QString defaultWelcomeScreenCurrency;
    extern const QList<QString> possibleCurrency;
    extern const QList<QString> possibleCurrencyAdapationValueToBGN;
}

#endif // EP_CUSTOMFUNCTIONS_H
