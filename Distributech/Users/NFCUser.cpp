#include <exception>
#include "NFCUser.h"


Json::Value NFCUser::ToJson()
{
    Json::Value value;

    value["name"] = name;
    value["id"] = id;
    value["role"] = role;

    return value;
}

bool NFCUser::FromJson(Json::Value value)
{
    // Check object integrity
    try{
        if(!value.isNull() && value.isObject())
        {
            if(!value["name"].isNull() && value["name"].type() == Json::stringValue &&
               !value["id"].isNull() && value["id"].type() == Json::intValue &&
               !value["role"].isNull() && value["role"].type() == Json::intValue)
               {
                    id = value["id"].asInt();
                    role = (UserRole)value["role"].asInt();
                    name = value["name"].asString();

                    return true;
               }
            else
            {
                std::cerr << "Error with Json Object" << std::endl;
            }
        }
    }catch(std::exception &e)
    {
        std::cerr << e.what() << std::endl;

    }

    return false;
}

void NFCUser::Print()
{
    std::cout << "Username " << name << " | ";
    std::cout << "Id " << id << " | ";
    std::cout << "Role " << role << std::endl;
}
