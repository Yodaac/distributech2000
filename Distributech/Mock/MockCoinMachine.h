/**
    MockCoinMachine.h
    Mock the class CoinMachine.
    Check CoinMachine.h for methods details

    @author A.C
    @version 1
*/

#ifndef MOCKCOINMACHINE_H_
#define MOCKCOINMACHINE_H_

#include <utility>
#include "CoinMachine.h"

class MockCoinMachine: public CoinMachine{

public:

    // Always return true
    bool InsertCoin() { return true;};

    // Does nothing
    void Initialize() {};

    // always return false
    bool IsCanceled() { return false;}

    // Return a default value
    std::pair<float, int> GetInsertedMoneyValue() { return std::pair<float,int>(1000.0,1); }

    // Return a default value
    double GetTemporaryBankValue() { return 100.0;}

    // Does nothing
    void ValidateTransaction() {}

    // Does nothing
    void GiveBackCoin() {}

    // Does nothing
    void GiveBackChange(double change) {}

    // Return a default value
    int GetInsertedMoneyCurrency() {return 1;}

    /**
     * This method is only an overload test method.
     *
     * it forces the currency of the last inserted coin.
     *
     * @param id the id to scan.
     * @return none.
     */
    int GetInsertedMoneyCurrency(int currency) {return currency;}

    // Does nothing
    void GiveBackMoney() {};

    // Does nothing
    void Restart() {};

    // Does nothing
    void Stop() {};

    void Reset() {}

};

#endif // MOCKCOINMACHINE_H_
