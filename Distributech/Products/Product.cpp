#include "Product.h"


Json::Value Product::ToJson()
{
    Json::Value value;

    value["name"] = name;
    value["description"] = description;
    value["price"] = price;

    return value;

}

bool Product::FromJson(Json::Value value)
{
    // Check object integrity
    try{
        if(!value.isNull() && value.isObject())
        {
            if(!value["name"].isNull() && value["name"].type() == Json::stringValue &&
               !value["description"].isNull() && value["description"].type() == Json::stringValue &&
               !value["price"].isNull() && value["price"].type() == Json::realValue)
               {
                    description = value["description"].asString();
                    name = value["name"].asString();
                    price = value["price"].asDouble();

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

void Product::Print()
{
    std::cout << "Name " << name << " | ";
    std::cout << "description " << description << std::endl;


}
