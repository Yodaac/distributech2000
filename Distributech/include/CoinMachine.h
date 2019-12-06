/**
    CoinMachine.h
    A really simplistic comportment for coin interface hardware.
    Coin machine is composed by:
    - a bank, holding money for all transaction
    - a temporary bank, holding coins inserted by user for a single transaction
    - a cancel button
    - a reserve of different coins for change

    @author A.C
    @version 1
*/

#ifndef COINMACHINE_H_
#define COINMACHINE_H_

class CoinMachine{

public:

    /**
     * Virtual class destructor
     *
     * @param none.
     * @return none.
     */
    virtual ~CoinMachine(){}

    /**
     * Insert a coin in the temporary bank.
     *
     * This method is called when a coin is inserted in the machine
     * and insert the coin in the bank. This method returns automatically false
     * if user took too much time to insert coin
     *
     * @param none.
     * @return true if a coin was inserted, false otherwise.
     */
    virtual bool InsertCoin() = 0;

    /**
     * Initialization method
     *
     * This method is used to initialize hardware.
     *
     * @param none.
     * @return none.
     */
    virtual void Initialize() = 0;

    /**
     * Give access to the current bank.
     *
     * This method return the total money value in the temporary
     * bank for a transaction.
     *
     * @param none.
     * @return The current value inside the temporary bank.
     */
    virtual double GetTemporaryBankValue() = 0;

    /**
     * Get the inserted coin currency.
     *
     * This method return the currency of the last inserted coin.
     *
     * @param none.
     * @return The inserted coin currency.
     */
    virtual int GetInsertedMoneyCurrency() = 0;

    /**
     * Give back a coin to user.
     *
     * This method gives back to user the last inserted coin,
     * typically when coin is rejected (bad currency, unrecognized coin).
     *
     * @param none.
     * @return none.
     */
    virtual void GiveBackCoin() = 0;

    /**
     * Empty bank and give it back to user.
     *
     * This method uses hardware to give money back to user.
     *
     * @param none.
     * @return none.
     */
    virtual void GiveBackMoney() = 0;

    /**
     * Valid a transaction .
     *
     * This method transfer all coins in temporary bank into
     * the bank.
     *
     * @param none.
     * @return none.
     */
    virtual void ValidateTransaction() = 0;

    /**
     * Gives user change after transaction.
     *
     * This method uses hardware to give money back to user.
     *
     * @param change the change value to give back to user.
     * @return none.
     */
    virtual void GiveBackChange(double change) = 0;

    /**
     * Check if transaction canceled.
     *
     * This method checks if user canceled the buy.
     *
     * @param none.
     * @return none.
     */
    virtual bool IsCanceled() = 0;

    /**
     * Set the coin machine state.
     *
     * The coin machine is stopped and the hardware is suspended
     * during maintenance.
     *
     * @param none.
     * @return none.
     */
    virtual void Stop() = 0;

    /**
     * Set the coin machine state.
     *
     * The coin machine and hardware are restarted after maintenance.
     *
     * @param none.
     * @return none.
     */
    virtual void Restart() = 0;

    /**
     * Reset coin machine.
     *
     * Reset the coin machine change coin to their defaults.
     *
     * @param none.
     * @return none.
     */
    virtual void Reset() = 0;

};


#endif // COINMACHINE_H_
