/**
    MockCoffeeMaker.h
    Mock the class CoffeeMaker.
    Check CoffeeMaker.h for methods details

    @author A.C
    @version 1
*/
#ifndef MOCKCOFFEEMACKER_H_
#define MOCKCOFFEEMACKER_H_

#include "CoffeMaker.h"

class MockCoffeeMaker: public CoffeeMaker{

public:

    // Does nothing
    void Initialize() {}

    // Does nothing
    bool DistributeCoffee(CoffeeType type) {}

    // Does nothing
    void Stop() {}

    // Does nothing
    void Restart() {}

    void Reset() {}
};


#endif // MOCKCOFFEEMACKER_H_
