//  v2.0
//  FBullCowGame.hpp
//  BullCowGame
//  Created by Παύλος Βασιλείου on 14/04/2017.
//  Copyright © 2017 Paul Vasileiou. All rights reserved.

#pragma once
#include "Fincludes.h"

bool OpenFile(FString);
FString GenerateHiddenWord();

//A pair counter
struct FBullCowCount {
    int32 Bulls = 0;
    int32 Cows = 0;
};

//An enum containing possible error codes
enum class EWordStatus {
    Invalid_Status,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase,
};

//Actual Class Declaration
class FBullCowGame {
public:
    FBullCowGame();
    void Reset();
    int32 getMaxTries() const;
    int32 getCurrentTry() const;
    int32 getHiddenWordLength() const;
    bool isGameWon() const;
    EWordStatus checkGuessValidity(FString) const;
    FBullCowCount SubmitGuess(FString);
    
private:
    int32 myCurrentTry = 1;
    FString myHiddenWord;
    bool bGameIsWon = false;
    bool isIsogram(FString) const;
    bool isLowercase(FString) const;
};

