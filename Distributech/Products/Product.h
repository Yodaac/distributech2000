/**
    Product.h
    Defines item objects

    @author A.C
    @version 1
*/
#ifndef PRODUCT_H_
#define PRODUCT_H_

#include <jsoncpp/json/json.h>

class Product {

public:

    /**
     * Getter for name
     *
     * @param none.
     * @return the object name field.
     */
    std::string GetName() { return name;}

    /**
     * Getter for description
     *
     * @param none.
     * @return the object description field.
     */
    std::string GetDescription() { return description;}

    /**
     * Getter for price
     *
     * @param none.
     * @return the object price field.
     */
    double GetPrice() { return price;}

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
     * This method initialize a Product fields with value.
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

    // Store the products name
    std::string name;

    // Store the products description
    std::string description;

    // Store the products price
    double price;

};

#endif //PRODUCT_H_
