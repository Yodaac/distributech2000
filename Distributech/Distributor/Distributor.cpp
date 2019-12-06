#include <sstream>
#include <iomanip>

#include "Distributor.h"
#include "JsonFileRepository.h"

void Distributor::InitializeDistributor(DistributorType type)
{
    // Set type
    this->type = type;

    // Init variable

    int nbItems = naNbLine * naNbColumn;
    if(type == EUDistributor)
        nbItems = euNbLine * euNbColumn;

    //currentTransaction = nullptr;

    //currentUser = nullptr;

    // Create classes

    coffeeMaker = new CoffeeMakerType();

    nfcReader = new NFCReaderType();

    mechanism = new DistributorMechanismType();

    coinMachine = new CoinMachineType();


    // Get Items

    JsonFileRepository repository;

    std::string filename = naItemFilename;

    if(type == EUDistributor)
        filename = euItemFilename;


    repository.ReadItemFile(filename, products, nbItems);

    // Get users

    repository.ReadUserFile(usersFilename, users);

    // Initialize hardware

    if(type == EUDistributor)
        mechanism->Initialize(euNbLine, euNbColumn);
    else if(type == NADistributor)
        mechanism->Initialize(naNbLine, naNbColumn);

    coinMachine->Initialize();

    nfcReader->Initialize();

    coffeeMaker->Initialize();

    // Adjust status
    state = Ready;

    mechanismState = ON;

    // Flag initialized
    initialized = true;
}

void Distributor::Free()
{
    // Destroy all allocated objects

    delete coffeeMaker;

    delete nfcReader;

    delete mechanism;

    delete coinMachine;

    // Free memory of products
    std::vector<Product*>::iterator prod_it = products.begin();

    while(prod_it != products.end())
    {
        delete *prod_it;
        products.erase(prod_it);
        prod_it = products.begin();
    }

    // Free memory of users
    std::vector<NFCUser*>::iterator user_it = users.begin();
    while(user_it != users.end())
    {
        delete *user_it;
        users.erase(user_it);
        user_it = users.begin();
    }
}

void Distributor::DisplayMessage(std::string message)
{

    std::cout << message << std::endl;

}

void Distributor::DisplayFormatedProducts()
{
    if(products.size() == 0)
    {
        DisplayMessage("Il n'y a pas de produits disponible");
        return;
    }

    std::vector<Product*>::iterator it = products.begin();

    int code = 1;

    std::stringstream ss;

    ss << "| " << std::setfill(' ') << std::setw(5) << "Code" << "| Produit" << std::setw(30-std::string("Produit").size()) << "|";
    DisplayMessage(ss.str());
    ss.str("");
    ss << std::setfill('=') << std::setw(36) << " ";
    DisplayMessage(ss.str());


    for(it; it < products.end(); it++, code++)
    {
        ss.str("");
        std::string name = (*it)->GetName();

        ss << "| " << std::setfill(' ') << std::setw(5) << code << "| " << name << std::setw(30-name.size()) << "|";
        DisplayMessage(ss.str());
    }

}


void Distributor::DisplayProducts()
{
    if(products.size() == 0)
    {
        DisplayMessage("Pas de produits");
    }

    std::vector<Product*>::iterator it;
    for(it = products.begin(); it<products.end(); it++)
    {
        (*it)->Print();
    }
}

void Distributor::DisplayUsers()
{
    if(users.size() == 0)
    {
        DisplayMessage("Pas d'utilisateurs");
    }

    std::vector<NFCUser*>::iterator it;
    for(it = users.begin(); it<users.end(); it++)
    {
        (*it)->Print();
    }

}


bool Distributor::StartServing()
{
    // If not initilized, return
    if(!initialized)
    {
        DisplayMessage("Erreur, non initialise");
        return false;
    }

    // To store user input
    int choice = 0;

    // Check for maintenance
    if(state == InMaintenance)
    {
        DisplayMessage("En Maintenance");

        #ifdef SIMULATION
        // Make a pause in program for simulation
        DisplayMessage("Entrer n'importe quel chiffre pour simuler le scan de la carte NFC du technicien");
        GetUserInput();
        #endif // SIMULATION

        #ifdef SIMULATION
        // Emulate a technician NFC card scan
        int id = nfcReader->Scan(1234567);
        #else
           int id = nfcReader->Scan();
        #endif
        if(checkNFCUser(id, NFCUser::Technician))
        {
            DisplayMessage("Carte Technicien Scannee");
            maintenance();
            //state = InMaintenance;
        }

        return true;
    }

    // Display products
    DisplayFormatedProducts();

    DisplayMessage("Selectionnez un item");
    DisplayMessage("Pour Un cafe, utilisez le code 98");
    DisplayMessage("Pour simuler la mise en maintenance du distributeur par un technicien, utilisez le code 99");


    while(choice != 99 && choice != 98 && (choice < 1 || choice > products.size()))
    {
        choice = GetUserInput();
    }

    // coffee
    if(choice == 98)
    {
        DisplayMessage("Inserer une piece ou scanner un badge");
        DisplayMessage("1- Inserer Monnaie");
        DisplayMessage("2- Scanner badge employe");

         while(choice != 1 && choice != 2)
         {
             choice = GetUserInput();
         }

         // Coin simulation
         if(choice == 1)
         {
            if(getMoney(coffeePrice))
            {
                DisplayMessage("Distribution en cours");
                serveCoffee();
                DisplayMessage("Prenez votre cafe, bonne journee");
            }
            else
            {
                DisplayMessage("Annulation");
            }
         }

         // Scan emulation
         if(choice == 2)
         {
             #ifdef SIMULATION
             // Emulate a user NFC card scan
             int id = nfcReader->Scan(3216549);
             #else
                int id = nfcReader->Scan();
             #endif
             if(checkNFCUser(id, NFCUser::Employee))
             {
                 DisplayMessage("Carte Scannee");
                 DisplayMessage("Distribution en cours");
                 serveCoffee();
                 DisplayMessage("Prenez votre cafe, bonne journee");
             }
         }
    }
    // Technician
    else if(choice == 99)
    {
        #ifdef SIMULATION
        // Emulate a technician NFC card scan
        int id = nfcReader->Scan(1234567);
        #else
           int id = nfcReader->Scan();
        #endif
        if(checkNFCUser(id, NFCUser::Technician))
        {
            DisplayMessage("Carte Technicien Scannee");
            state = InMaintenance;
        }
    }
    else
    {
        Product* prod = searchProduct(choice - 1);

        if(getMoney(prod->GetPrice()))
        {
            DisplayMessage("Distribution en cours");
            distributeItem(choice - 1);
            DisplayMessage("Bonne journee");
        }
        else
        {
            DisplayMessage("Annulation");
        }

    }

    #ifdef SIMULATION
    // Make a pause in program for simulation
    DisplayMessage("Entrer n'importe quel chiffre pour continuer le programme");
    GetUserInput();
    #endif // SIMULATION

    return true;
}
bool Distributor::distributeItem(int item)
{
    bool result = mechanism->DistributeItem(item);

    // Perform other action, like update items quantities
    // ....

    return result;
}

bool Distributor::maintenance()
{
    // Get user choice
    int choice = 0;

    while(choice != 5)
    {
        DisplayMessage("======================================");
        DisplayMessage("    Mode Maintenance");
        DisplayMessage("======================================");
        DisplayMessage("1- Desactiver les mecanismes");
        DisplayMessage("2- Remise a zero");
        DisplayMessage("3- Reactiver les mecanismes");
        DisplayMessage("4- Afficher Statut");
        DisplayMessage("5- Quitter maintenance");

        while(choice < 1 || choice > 5)
        {
            choice = GetUserInput();
        }

        switch(choice){
            case 1:
                DisplayMessage("Mise en mode maintenance");

                coffeeMaker->Stop();
                coinMachine->Stop();
                mechanism->Stop();
                mechanismState = OFF;
                DisplayMessage("Mecanismes desactives");
                break;
            case 2:
                coffeeMaker->Reset();
                coinMachine->Reset();
                // Perform other action, like reset items quantities
                // ....
                break;
            case 3:
                coffeeMaker->Restart();
                coinMachine->Restart();
                mechanism->Restart();
                mechanismState = ON;
                DisplayMessage("Mecanismes reactives");
                break;
            case 4:
                if(state == InMaintenance)
                    DisplayMessage("Statut Distributeur: En Maintenance");
                if(state == Ready)
                    DisplayMessage("Statut Distributeur: Pret");
                if(mechanismState == ON)
                    DisplayMessage("Statut Mechanismes: Actives");
                if(mechanismState == OFF)
                    DisplayMessage("Statut Mechanismes: Desactives");
                break;
            case 5:
                if(mechanismState == OFF)
                    DisplayMessage("Attention, les mecanismes sont toujours desactives");
                else
                    state = Ready;
                break;
        }
        // Reset choice
        if(choice != 5)
            choice = 0;
    }


    return false;
}



bool Distributor::getMoney(double price)
{

    DisplayMessage("Inserez des pieces");

    do
    {
        if(!coinMachine->InsertCoin())
        {
            // If user canceled, give his money back and return
            if(coinMachine->IsCanceled())
            {
                coinMachine->GiveBackMoney();
                return false;
            }
            else
                continue;
        }

        // Check coin validity
        #ifdef SIMULATION
        DistributorCurrency currency;
        if(type == NADistributor)
            currency = (DistributorCurrency)coinMachine->GetInsertedMoneyCurrency((int)USD);
        else
            currency = (DistributorCurrency)coinMachine->GetInsertedMoneyCurrency((int)EUR);
        #else
        DistributorCurrency currency = (DistributorCurrency)coinMachine->GetInsertedMoneyCurrency();
        #endif

        if(type == NADistributor && (currency == USD || currency == CAD) )
        {
            std::stringstream test;
            test << coinMachine->GetTemporaryBankValue() << "$";
            // Display current bank value
            DisplayMessage(test.str());
        }
        else if(type == EUDistributor && currency == EUR)
        {
            std::stringstream test;
            test << coinMachine->GetTemporaryBankValue() << "€";
            // Display current bank value
            DisplayMessage(test.str());
        }
        // Coin rejected
        else
        {
            coinMachine->GiveBackCoin();
        }
    }while(coinMachine->GetTemporaryBankValue() < price);

    // Give back user change
    double difference = coinMachine->GetTemporaryBankValue() - price;

    if(difference != 0.0){
        coinMachine->GiveBackChange(difference);
        DisplayMessage("Noubliez pas votre monnaie");
    }

    return true;
}


bool Distributor::checkNFCUser(int id, NFCUser::UserRole role)
{

    // Search user, if not found, display on error message and return
    NFCUser * currentUser = searchUser(id);

    if(currentUser == nullptr)
    {
        DisplayMessage("Utilisateur non enregistre");
        return false;
    }

    NFCUser::UserRole userRole = currentUser->GetRole();

    if( userRole == NFCUser::Employee && userRole == role )
    {
        return true;
    }
    else if(userRole == NFCUser::Technician && userRole == role)
    {
        return true;
    }
    else
    {
        DisplayMessage("Role incompatible");
        return false;
    }

}

bool Distributor::serveCoffee()
{
    // Get user choice
    int choice = 0;

    DisplayMessage("======================================");
    DisplayMessage("    Selectionnez votre cafe");
    DisplayMessage("======================================");
    DisplayMessage("1- Court");
    DisplayMessage("2- Long");

    while(choice != 1 && choice != 2)
    {
        choice = GetUserInput();
    }

    // Activate and wait Coffee Maker
    // Block until coffee is ready

    DisplayMessage("Cafe en preparation");

    coffeeMaker->DistributeCoffee((CoffeeMakerType::CoffeeType)choice);

    DisplayMessage("Votre cafe est pret");

    return true;
}

NFCUser* Distributor::searchUser(int id)
{
    std::vector<NFCUser*>::iterator it = users.begin();

    for(it; it < users.end(); it++)
    {
        if((*it)->GetId() == id)
            return *it;
    }

    return nullptr;
}

Product* Distributor::searchProduct(int position)
{
    if(position > products.size())
    {
        DisplayMessage("Erreur de selection");
        return nullptr;
    }

    std::vector<Product*>::iterator it = products.begin() + (position - 1);

    return *it;
}

int Distributor::GetUserInput()
{
    // Call Input class, in our case, it is cin

    int input;

    std::cin >> input;

    return input;
}


