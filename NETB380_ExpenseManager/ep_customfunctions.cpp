#include "ep_customfunctions.h"

namespace EP_CustomFunctions
{
    /*Constants*/
    const QString defaultWelcomeScreenCurrency = "Your current balance is: ";
    /*TO DO create possibility to add custom currency and update currency rates.*/
    const QList<QString> possibleCurrency = {  "BGN",
            "EUR",
            "USD",
            "GBP",
            "JPY"};

    const QList<QString> possibleCurrencyAdapationValueToBGN = {  "1",
                                                                  "0.51",
                                                                  "0.62",
                                                                  "0.46",
                                                                  "64.93"};

    /*Simple function to translate current seleceted currency to EP_Currency type.*/
    EP_Currencies translateStringToCurrency(QString currentSelcetedCurrency)
    {
        /**/
        EP_Currencies result = EP_BGN;
        /**/
        int CurrencyArrayIndex = possibleCurrency.size();
        for(int i = 0;i< CurrencyArrayIndex; i++)
        {
            if(possibleCurrency.at(i) == currentSelcetedCurrency)
            {
                result = (EP_Currencies)i;
                break;
            }
        }

        return result;
    }
    /*Simple function to translate current currency to String.*/
    QString translateCurrencyToString(EP_Currencies currentSelectedCurrency)
    {
        /*Initialize return value.*/
        QString returnCurrencyInString = "";

        returnCurrencyInString = possibleCurrency.at((int)currentSelectedCurrency);

        return returnCurrencyInString;
    }

    /*Simple function to adapt currency to their respective BGN currency.*/
    QString adapatCurrency(double ValueToAdapt, EP_Currencies currentCurrency, EP_Currencies selectedCurrency)
    {
        /*Initialize return value of type QString*/
        QString valueToReturn = "";
        /*Get current value.*/
        double currentValue = ValueToAdapt;
        /*Make adaptations.*/
        double CurrentRate = EP_CustomFunctions::possibleCurrencyAdapationValueToBGN.at((int)currentCurrency).toDouble(nullptr);
        double AdapationRate = EP_CustomFunctions::possibleCurrencyAdapationValueToBGN.at((int)selectedCurrency).toDouble(nullptr);

        /*Current currency is BGN and requested is BGN do not change*/
        if ((CurrentRate == (double)1) && (AdapationRate == (double)1))
        {
            // do  nothing.
            //currentValue = currentValue * possibleCurrencyAdapationValueToBGN.at((int)AdapationRate).toDouble(nullptr);
        }
        /*Convert currency to BGN from higher rates.*/
        else if((CurrentRate == (double)1) && (AdapationRate < (double)1))
        {
            currentValue = currentValue * possibleCurrencyAdapationValueToBGN.at((int)selectedCurrency).toDouble(nullptr);
        }
        /*Convert currency to BGN from higher rates.*/
        else if((CurrentRate < (double)1) && (AdapationRate == (double)1))
        {
            currentValue = currentValue / possibleCurrencyAdapationValueToBGN.at((int)currentCurrency).toDouble(nullptr);
        }
        /*Convert lower rate currency to BGN.*/
        else if((CurrentRate > (double)1) && (AdapationRate == (double)1))
        {
            currentValue = currentValue / possibleCurrencyAdapationValueToBGN.at((int)currentCurrency).toDouble(nullptr);
        }
        /*Convert BGN currency to higher rates than BGN*/
        else if((CurrentRate == (double)1) && (AdapationRate > (double)1))
        {
            currentValue = currentValue * possibleCurrencyAdapationValueToBGN.at((int)selectedCurrency).toDouble(nullptr);
        }
        /*Transform to QString and apply format.*/
        valueToReturn = QString::number(currentValue,'f',2);

        return valueToReturn;

    }
}
