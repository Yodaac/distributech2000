/**
    DistributorMechanism.h
    A really simplistic comportment for items distribution hardware.
    It is composed of a matrix of motors, 6x6 or 6x10, or...
    Numbers of lines and columns are passed during initialization.

    @author A.C
    @version 1
*/

#ifndef DISTRIBUTORMECHANISME_H_
#define DISTRIBUTORMECHANISME_H_

class DistributorMechanism {

public:

    /**
     * Virtual class destructor
     *
     * @param none.
     * @return none.
     */
    virtual ~DistributorMechanism(){};

    /**
     * Distribute a selected item
     *
     * Activate motor to release the item at index 'item'.
     *
     * @param item the item index to distribute.
     * @return true if everything was ok, false otherwise.
     */
    virtual bool DistributeItem(int item) = 0;

    /**
     * Initialization method
     *
     * This method is used to initialize hardware.
     *
     * @param line the motors matrix line number.
     * @param column the motors matrix column number.
     * @return none.
     */
    virtual void Initialize(int line, int column) = 0;

    /**
     * Set the mechanism state.
     *
     * Distributor mechanism are stopped and the hardware is suspended
     * during maintenance.
     *
     * @param none.
     * @return none.
     */
    virtual void Stop() = 0;

    /**
     * Set the mechanism state.
     *
     * Distributor mechanism are restarted after maintenance.
     *
     * @param none.
     * @return none.
     */
    virtual void Restart() = 0;


};

#endif // DISTRIBUTORMECHANISME_H_
