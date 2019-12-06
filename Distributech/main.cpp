#include <iostream>
#include "Distributor.h"

// For unit tests only
#include "NFCUser.h"
#include "Product.h"
#include "JsonFileRepository.h"

using namespace std;

void unitTestsNFCUser()
{
    NFCUser * u = new NFCUser();

    Json::Value value;

    value["id"] = 12345679;
    u->FromJson(value);
    value["name"] = "Testing";
    u->FromJson(value);
    value["type"] = 1;
    u->FromJson(value);
    value["name"] = 1;
    u->FromJson(value);

    u->Print();

    std::cout << "Username " << u->GetName() << std::endl;
    std::cout << "Id " << u->GetId() << std::endl;
    std::cout << "Role " << u->GetRole() << std::endl;

    std::cout << u->ToJson() << std::endl;

    delete u;

}

void unitTestsProduct()
{
    Product * p = new Product();

    Json::Value value;

    value["description"] = "Description of product";
    p->FromJson(value);
    value["name"] = 1;
    p->FromJson(value);
    value["name"] = "Banana";
    p->FromJson(value);


    p->Print();

    std::cout << "Name " << p->GetName() << std::endl;
    std::cout << "Description " << p->GetDescription() << std::endl;

    std::cout << p->ToJson() << std::endl;

    delete p;

}

void unitTestsJsonFileRepository()
{
    JsonFileRepository* t = new JsonFileRepository();
    std::vector<NFCUser*>::iterator it;

    std::vector<NFCUser*> users;
    t->ReadUserFile("users.json", users);

    for(it = users.begin(); it<users.end(); it++)
    {
        (*it)->Print();
    }

    std::vector<Product*> products;
    t->ReadItemFile("EUItems.json", products, 36);

    std::vector<Product*>::iterator prod_it;

    for(prod_it = products.begin(); prod_it<products.end(); prod_it++)
    {
        (*prod_it)->Print();
    }

    while(prod_it != products.end())
    {
        delete *prod_it;
        products.erase(prod_it);
        prod_it = products.begin();
    }

    t->ReadItemFile("NAItems.json", products, 60);

    for(prod_it = products.begin(); prod_it<products.end(); prod_it++)
    {
        (*prod_it)->Print();
    }

    while(prod_it != products.end())
    {
        delete *prod_it;
        products.erase(prod_it);
        prod_it = products.begin();
    }

    delete t;
}

void unitTestsDistributor()
{
    Distributor& d = Distributor::getInstance();

    d.InitializeDistributor(Distributor::NADistributor);

    d.DisplayProducts();

    d.DisplayUsers();



    d.Free();

}

int main()
{

    // Resize terminal size
    std::cout << "\e[8;50;200t";

    Distributor& d = Distributor::getInstance();

    int choice = 0;

    // Initialize Distributor for simulation
    d.DisplayMessage("Bienvenue sur le simulateur Distributech 2000");
    d.DisplayMessage("Quelle machine voulez-vous tester?");
    d.DisplayMessage("1- NA");
    d.DisplayMessage("2- EU");

    while(choice != 1 && choice != 2)
    {
        choice = d.GetUserInput();
    }

    if(choice == 1)
        d.InitializeDistributor(Distributor::NADistributor);
    else
        d.InitializeDistributor(Distributor::EUDistributor);

    while(d.StartServing());

    d.Free();

    return 0;
}
