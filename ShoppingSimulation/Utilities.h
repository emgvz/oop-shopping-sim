#pragma once

#include <iostream>


bool continueTransaction()
{
    while (true)
    {
        std::string userChoice{};

        std::cout << "Are you sure you want to exit the application? (y to exit, n to return to menu): ";
        std::cin >> userChoice;

        if (userChoice == "n" || userChoice == "N")
        {
            return true;
        }
        if (userChoice == "y" || userChoice == "Y")
        {
            return false; // stop running
        }
    }

}

inline void clearScreen()
{
#if defined(_WIN32) || defined (_WIN64)
    std::system("cls");
#else
    std::system("clear");
#endif
}

inline void ignoreLine()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


}