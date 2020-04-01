#include <iostream>
#include "craps.h"

float processBet(float currentBank);
bool isInteger(const std::string & s);
void displayResults(float currentBank, float currentBet);

int main() {
    float currentBank = 10000.0;
    float currentBet = 10.0;

    std::string userInput = "";
    std::cout << "Roll (r), Bet(b), Quit(e): ";
    std::cin >> userInput;

    while(userInput != "e") {
        if(userInput == "r") {
            currentBank = playGame(currentBank, currentBet);
            displayResults(currentBank, currentBet);
            if (currentBank <= 0) {
                std::cout << "You don't have any more money!" << "\n";
                std::cout << "Get a job!!" << "\n";
                break;
            }
        } else if (userInput == "b") {
            currentBet = processBet(currentBank);
        }
        else {
            std::cout << "Invalid input";
        }
            std::cout << "Roll (r), Bet(b), Quit(e): ";
        std::cin >> userInput;
    }
    return 0;
}

float processBet(float currentBank) {
    float attemptedBet;
    bool  betAccepted = false;

    std::string userInput = "";
    while (!betAccepted){
        std::cout << "How much would you like to bet? ";
        std::cin >> userInput;
        if(isInteger(userInput)) {
            attemptedBet = stof(userInput);
            if (attemptedBet <= currentBank) {
                betAccepted = true;
                return attemptedBet;
            } else {
                std::cout << "You don't have that much money!" << "\n";
                betAccepted = false;
            }
        } else
            return 0.0;
    }
};

inline bool isInteger(const std::string & s) {
    if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;
    char * p;
    strtol(s.c_str(), &p, 10);
    return (*p == 0);
}

void displayResults(float currentBank, float currentBet){
    std::cout << "Current bank: " << currentBank << " Current bet: " << currentBet << "\n";
}
