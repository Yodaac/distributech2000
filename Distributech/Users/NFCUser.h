/**
    NFCUser.h
    Defines users object that are allowed to identify with their NFC card

    @author A.C
    @version 1
*/

#ifndef NFCUSERS_H_
#define NFCUSERS_H_

#include <jsoncpp/json/json.h>

class NFCUser{

public:

    // enum to define the different NFCUsers role
    enum UserRole { Technician, Employee };

    /**
     * Getter for role
     *
     * @param none.
     * @return the object role field.
     */
    UserRole GetRole() { return role;}

    /**
     * Getter for name
     *
     * @param none.
     * @return the object name field.
     */
    std::string GetName() { return name;}

    /**
     * Getter for nfc id
     *
     * @param none.
     * @return the object id field.
     */
    int GetId() { return id;}

    /**
     * Serialize object
     *
     * This method returns the object serialized in json.
     *
     * @param none.
     * @return the json serialized object.
     */
    Json::Value ToJson();

    /**
     * Initialize object
     *
     * This method initialize a NFCUser fields with value.
     *
     * @param value a json representation of the object.
     * @return true if ok, false otherwise.
     */
    bool FromJson(Json::Value value);

    /**
     * Display object fields
     *
     * This method is only for debug, and displays the object fields value.
     *
     * @param none.
     * @return none.
     */
    void Print();


private:

    // Store user name
    std::string name;

    // Store the nfc id
    int id;

    // Store the user role
    UserRole role;

};

#endif // NFCUSERS_H_
