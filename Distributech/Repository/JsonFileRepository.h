/**
    JsonFileRepository.h
    A simple json file repository implementation to load users and items.

    @author A.C
    @version 1
*/

#include <iostream>
#include <vector>
#include "NFCUser.h"
#include "Product.h"

class JsonFileRepository{

public:

    /**
     * Read a user file
     *
     * This method reads the json content of the file and store
     * each json object in the vector
     *
     * @param filename the filename or full path of file to open.
     * @param (out) users vector of user objects.
     * @return true if file was found and is valid json, false otherwise.
     */
    bool ReadUserFile(std::string filename, std::vector<NFCUser*>& users);

    /**
     * Read item file
     *
     * This method reads the json content of the file and store
     * each json object in the vector
     *
     * @param filename the filename or full path of file to open.
     * @param (out) items vector of item objects.
     * @return true if file was found and is valid json, false otherwise.
     */
    bool ReadItemFile(std::string filename, std::vector<Product*>& items, int max);

};
