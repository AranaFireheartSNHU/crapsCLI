//
// Created by Arana on 3/18/20.
//
#include <iostream>
#include "craps.h"
#include "die.h"

std::tuple<bool, float> playFirstRoll(int rollValue, float currentBank, float currentBet);
std::tuple<bool, float> playSecondRoll(int rollValue, int previousRoll, float currentBank, float currentBet);
float processWin(int rollValue, int rollNumber, float currentBank, float currentBet);
float processLoss(int rollValue, int rollNumber, float currentBank, float currentBet);
float calculateCurrentBank(int rollValue, int rollNumber, float currentBank, float currentBet, bool wonBet);

float calculateCurrentBank(int rollValue, int rollNumber, float currentBank, float currentBet);

float playGame(float currentBank, float currentBet) {
    int firstRoll = 1;
    int rollValue = 0;
    Die die1, die2;
    int previousRoll = 0;
    bool rollCompleted = false;
    float localBank = currentBank;

    while(firstRoll >= 0) {
        rollValue = die1.roll() + die2.roll();
        std::cout << "You rolled a " << rollValue << "\n";
        if (firstRoll == 1) {
            std::tie(rollCompleted, localBank) = playFirstRoll(rollValue, currentBank, currentBet);
            if (rollCompleted) {
                firstRoll = 0;
                rollCompleted = false;
            } else {
                previousRoll = rollValue;
                firstRoll = 2;
                rollCompleted = false;
                continue;
            }
        } else if (firstRoll == 2) {
            std::tie(rollCompleted, localBank) = playSecondRoll(rollValue, previousRoll, currentBank, currentBet);
            if (rollCompleted) {
                previousRoll = rollValue;
                firstRoll = 0;
                rollCompleted = false;
            }
        }
        firstRoll = 0;
        return localBank;
    }
}

std::tuple<bool, float>  playFirstRoll(int rollValue, float currentBank, float currentBet){
    std::cout << rollValue << "\n";
    switch (rollValue) {
        case 7:
        case 11: {
            currentBank = processWin(rollValue, 1, currentBank, currentBet);
            return std::make_tuple(true, currentBank);
        }
        case 2:
        case 3:
        case 12: {
            currentBank = processLoss(rollValue, 1, currentBank, currentBet);
            return std::make_tuple(true, currentBank);
        }
        default: {
            return std::make_tuple(false, currentBank);
        }
    }
};

std::tuple<bool, float>  playSecondRoll(int rollValue, int previousRoll,  float currentBank, float currentBet){
    if (rollValue == previousRoll) {
        return std::make_tuple(true, processWin(rollValue, 2, currentBank, currentBet));
    } else {
        return std::make_tuple(true, processLoss(rollValue, 2, currentBank, currentBet));
    }
};

float processWin(int rollValue, int rollNumber, float currentBank, float currentBet) {
    std::cout << "You won!" << "\n";
    return calculateCurrentBank(rollValue, rollNumber, currentBank, currentBet, true);
}

float processLoss(int rollValue, int rollNumber, float currentBank, float currentBet) {
    std::cout << "You lost." << "\n";
    return calculateCurrentBank(rollValue, rollNumber, currentBank, currentBet, false);
};

float calculateCurrentBank(int rollValue, int rollNumber, float currentBank, float currentBet, bool wonBet) {
    if (rollNumber == 1) {
        if(wonBet)
            return currentBank + currentBet;
        else
            return currentBank - currentBet;
    }
    else {
        if(wonBet)
            return currentBank + currentBet * payouts[rollValue];
        else
            return currentBank - currentBet * payouts[rollValue];
    }
};

