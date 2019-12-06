/**
    MockDistributorMechanism.h
    Mock the class DistributorMechanism for tests.
    Check DistributorMechanism.h for methods details

    @author A.C
    @version 1
*/

#ifndef MOCKDISTRIBUTORMOTOR_H_
#define MOCKDISTRIBUTORMOTOR_H_

#include "DistributorMechanism.h"

class MockDistributorMechanism : public DistributorMechanism{

public:

    // Return true
    bool DistributeItem(int item) { return true;};

    // Does nothing
    void Initialize(int line, int column) {};

    // Does nothing
    void Stop() {};

    // Does nothing
    void Restart() {};

};


#endif // MOCKDISTRIBUTORMOTOR_H_
