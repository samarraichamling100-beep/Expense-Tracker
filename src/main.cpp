#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <limits>
#include <cctype>
#include <ctime>

void toLower(std::string &str)
{
    for(auto & element : str)
    {
        element = std::tolower(
            static_cast<unsigned char>(element)
        );
    }
}

class System
{
    public:
    std::vector<std::string> ExpenseTypes = 
    {
        "bill",
        "food",
    };
    std::string ExpenseType;
    std::fstream DataAdder;
    void AskExpenditure(std::string &ExpenseItem,int &Price,std::string Type)
    {
        std::cout << "ExpenseItem : ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin,ExpenseItem);
        std::cout << "Price : ";
        std::cin >> Price;
        SaveExpense(ExpenseItem,Price,Type);
    };

    void SaveExpense(std::string expense,int price,std::string Type)
    {
        time_t timestamp;
        time(&timestamp);
        DataAdder.open("data.csv",std::ios::out | std::ios::app);
        DataAdder << Type + "," << expense + "," << price << "," << std::ctime(&timestamp) << '\n';
        DataAdder.close();
    }
    void AskExpenseType()
    {
        std::cout << "Please enter the expense type : ";
        std::cin >> ExpenseType;
        toLower(ExpenseType);

        for(int index = 0; index < ExpenseTypes.size();index ++)
        {
            bool matched{};
            matched = ExpenseType == ExpenseTypes[index];
            if (matched)
            {
                std::cout << "ExpenseType : " << ExpenseType << '\n';
                break;
            }
            else
            {
                if(!matched && index == ExpenseTypes.size() - 1)
                {
                    std::cout << "Please Enter a Type from following expense types : {" << '\n';
                    for (auto type : ExpenseTypes)std::cout << "    ExpenseType : " << type << '\n';
                    std::cout << "}" << '\n';
                }
            }
        }

    }
    void AskExpense()
    {
        std::string ExpenseItem{};
        int Price{};

        if (ExpenseType == "bill" || ExpenseType == "food")
        {
            AskExpenditure(ExpenseItem, Price,ExpenseType);
        }
    }
};


int main ()
{
    System ExpenseTracker;
    ExpenseTracker.AskExpenseType();
    ExpenseTracker.AskExpense();
    return 0;
}