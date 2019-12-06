/**
    CoffeeMachine.h
    A really simplistic comportment for coffee machine hardware

    @author A.C
    @version 1
*/

#ifndef COFFEEMAKER_H_
#define COFFEEMAKER_H_

class CoffeeMaker{

public:

    // enum type to define coffee type
    enum CoffeeType { SHORT = 1, LONG};

    /**
     * Virtual class destructor
     *
     * @param none.
     * @return none.
     */
    virtual ~CoffeeMaker(){};

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
     * Distribute a coffee
     *
     * This method use hardware to make and distribute a coffee
     * in a plastic cup.
     *
     * @param CoffeeType the type of coffee to make.
     * @return none.
     */
    virtual bool DistributeCoffee(CoffeeType type) = 0;

    /**
     * Stop coffee maker.
     *
     * Coffee maker is suspended during maintenance.
     *
     * @param none.
     * @return none.
     */
    virtual void Stop() = 0;

    /**
     * Restart coffee maker.
     *
     * Coffee maker is restarted after maintenance.
     *
     * @param none.
     * @return none.
     */
    virtual void Restart() = 0;

    /**
     * Reset coffee maker.
     *
     * Reset the coffee maker water level, plastic cup number to their defaults.
     *
     * @param none.
     * @return none.
     */
    virtual void Reset() = 0;

private:

    // Used to stock the water level
    float currentWaterLevel;

    // Used to store the remaining number of plastic cups
    int nbCups;

    // .... many can be added but are not needed for the test
};

#endif // COFFEEMAKER_H_
