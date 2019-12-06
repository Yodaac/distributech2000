#include <iostream>
#include <fstream>
#include "JsonFileRepository.h"
#include "NFCUser.h"


bool JsonFileRepository::ReadUserFile(std::string filename, std::vector<NFCUser*>& users)
{
    // Open file
    std::ifstream file(filename);

    if(!file.is_open())
    {
        return false;
    }

    Json::Reader reader;

    Json::Value values;

    // Parse file content
    reader.parse(file, values);

    // Check data integrity
    if(!values.empty() && values.isArray())
    {
        // Create NFCUser for each json objects
        for(int i = 0; i < values.size(); i++)
        {

            NFCUser * u = new NFCUser();

            if(u->FromJson(values[i]))
            {
                users.push_back(u);
            }
        }

        file.close();

        return true;
    }


    file.close();

    return false;
}

bool JsonFileRepository::ReadItemFile(std::string filename, std::vector<Product*>& items, int max)
{
    // Open file
    std::ifstream file(filename);

    if(!file.is_open())
    {
        return false;
    }

    Json::Reader reader;

    Json::Value values;

    // Parse file content
    reader.parse(file, values);

    // Check data integrity
    if(!values.empty() && values.isArray())
    {

        // Find the maximum number of element to read
        int max_ele = max;
        if(values.size() < max_ele)
            max_ele = values.size();

        // Create NFCUser for each json objects
        for(int i = 0; i < max_ele; i++)
        {

            Product * p = new Product();

            if(p->FromJson(values[i]))
            {
                items.push_back(p);
            }
        }

        file.close();

        return true;
    }


    file.close();

    return false;
}


