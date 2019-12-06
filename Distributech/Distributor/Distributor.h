/**
    Distributor.h
    This is the main class of the project.
    It is designed as a singleton, to ensure only one object can be instantiated
    and provide an access to some of the hardware (display).
    This class use two json files, one for users and one for products.
    The item order in the products file determine the position in the distributor matrix.

    The distributor is composed by:
    - a coin machine
    - a nfc reader
    - a display
    - a coffee maker
    - a mechanism manager

    @author A.C
    @version 1
*/

#ifndef DISTRIBUTOR_H_
#define DISTRIBUTOR_H_

#include <vector>
#include "TSingleton.h"
#include "Product.h"
#include "NFCUser.h"
#include "MockCoffeeMaker.h"
#include "MockCoinMachine.h"
#include "MockDistributorMecanism.h"
#include "MockNFCReader.h"

// Use a simple pre processor macro to select SIMMULATION mode
#define SIMULATION

// In simulation we use moked classes for hardware
// So we define some simple typedef to switch hardware class type
#ifdef SIMULATION
typedef MockCoffeeMaker CoffeeMakerType;
typedef MockCoinMachine CoinMachineType;
typedef MockDistributorMechanism DistributorMechanismType;
typedef MockNFCReader NFCReaderType;
#else
typedef CoffeeMaker CoffeeMakerType;
typedef CoinMachine CoinMachineType;
typedef DistributorMechanism DistributorMechanismType;
typedef NFCReader NFCReaderType;
#endif

class Distributor: public TSingleton<Distributor>
{
public:

    // enum for Distributor types
    enum DistributorType{NADistributor, EUDistributor};

    // enum for Distributor status
    enum DistributorStatus {Ready, InTransaction, InMaintenance, NoMoney};

    // enum for Distributor currencies
    enum DistributorCurrency {USD, CAD, EUR};

    // enum for mechanism state
    enum MechanismState{ON, OFF};


    /**
     * Initialization method
     *
     * This method is used to initialize the class and should be called first.
     * It allocates all memory and object needed by the class.
     *
     * @param type the distributor type.
     * @return none.
     */
    void InitializeDistributor(DistributorType type);

    /**
     * Free method
     *
     * This method should be called before the program exit.
     * It frees all the allocated memory by the class.
     *
     * @param type the distributor type.
     * @return none.
     */
    void Free();

    /**
     * Getter for type
     *
     * @param none.
     * @return the object type field.
     */
    DistributorType GetType() { return type; }

    /**
     * Getter for status
     *
     * @param none.
     * @return the object state field.
     */
    DistributorStatus GetStatus() { return state; }


    /**
     * Debug method
     *
     * Display all the products currently loaded.
     *
     * @param none.
     * @return none.
     */
    void DisplayProducts();

    /**
     * Debug method
     *
     * Display all the users currently loaded.
     *
     * @param none.
     * @return none.
     */
    void DisplayUsers();

    /**
     * Debug method
     *
     * Display all items currently loaded in a formatted way.
     *
     * @param none.
     * @return none.
     */
    void DisplayFormatedProducts();

    /**
     * Display string on the screen.
     *
     * Provide a way to display a string on the distributor screen.
     * Currently, the method simply use std::cout.
     *
     * @param message: the message to be displayed.
     * @return none.
     */
    void DisplayMessage(std::string message);

    /**
     * Get user input.
     *
     * Provide a way to get user inputs.
     * Currently, the method simply use std::cin.
     *
     * @param none.
     * @return int the keycode the user pressed.
     */
    int GetUserInput();

    /**
     * Start the main method.
     *
     * Main working method used to operate the distributor.
     * Execute one action per call
     *
     * @param none.
     * @return bool return true if the action succeed, false otherwise or if quit .
     */
    bool StartServing();


private:

    // Const to store the number of line for EU version
    static const int euNbLine = 6;

    // Const to store the number of column for EU version
    static const int euNbColumn = 6;

    // Const to store the number of line for NA version
    static const int naNbLine = 10;

    // Const to store the number of column for NA version
    static const int naNbColumn = 6;

    // Const to store the NA items filename
    const std::string naItemFilename = "NAItems.json";

    // Const to store the EU items filename
    const std::string euItemFilename = "EUItems.json";

    // Const to store the users filename
    const std::string usersFilename = "users.json";

    // Since nothing was specified for coffee,
    // use a const to hold the coffee price
    const double coffeePrice = 1.0;

    // Simple flag to check if class is initialized
    bool initialized = false;

    /**
     * Search NFCUser
     *
     * This method search for a user with his nfc tag.
     *
     * @param id the nfc tag to search.
     * @return a pointer to the NFCUser if found, nullptr otherwise.
     */
    NFCUser* searchUser(int id);

    /**
     * Search Product
     *
     * This method search for a product with his position.
     *
     * @param position the product position.
     * @return a pointer to Product if found, nullptr otherwise.
     */
    Product* searchProduct(int position);

    /**
     * Check NFUser role
     *
     * This method check if user defined by his nfc tag exists
     * and if user have the correct role.
     *
     * @param id the nfc tag to search.
     * @param role the user role to compare to.
     * @return true if user was found and if his role is ok, false otherwise.
     */
    bool checkNFCUser(int id, NFCUser::UserRole role);

    /**
     * Serve coffee
     *
     * This method perform hardware manipulation to serve a coffee to user.
     *
     * @param none.
     * @return true if all ok, false otherwise.
     */
    bool serveCoffee();

    /**
     * Distribute item
     *
     * This method perform hardware manipulation to distribute an item.
     *
     * @param item: the item index to deliver.
     * @return true if all ok, false otherwise.
     */
    bool distributeItem(int item);

    /**
     * Maintenance mode
     *
     * This method display options for maintenance mode.
     *
     * @param none.
     * @return true if all ok, false otherwise.
     */
    bool maintenance();

    /**
     * Get money
     *
     * This method perform hardware manipulation to check money.
     * in the coin machine
     *
     * @param price the item price.
     * @return true if all ok, false otherwise.
     */
    bool getMoney(double price);

    // Store the type
    DistributorType type;

    // Store the status
    DistributorStatus state;

    // Store the mechanism state
    MechanismState mechanismState;

    // Store all the NFCUsers loaded
    std::vector<NFCUser*> users;

    // Store all the Products loaded, ordered by position
    std::vector<Product*> products;

    // Pointer to the CoinMachine
    CoinMachineType * coinMachine;

    // Pointer to the CoffeeMaker
    CoffeeMakerType * coffeeMaker;

    // Pointer to the DistributorMechanism
    DistributorMechanismType * mechanism;

    // Pointer to the NFCReaderType
    NFCReaderType * nfcReader;

};


#endif // DISTRIBUTOR_H_
