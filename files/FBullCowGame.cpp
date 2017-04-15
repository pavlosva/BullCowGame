//  v1.0
//  FBullCowGame.cpp
//  BullCowGame
//  "This file contains the actual Game Logic.
//  For User Interaction see main.cpp"
//  Created by Παύλος Βασιλείου on 14/04/2017.
//  Copyright © 2017 Paul Vasileiou. All rights reserved.

#include "FBullCowGame.hpp"

FVector<FString> WordList;

bool OpenFile(FString filename) {
    std::ifstream file(filename);
    
    //Checking if the file is open
    if (!file.is_open()){
        std::cout << "Error opening the file! EXITING\n";
        return false;
    }
    
    //Getting the Words to the vector!
    while (file.good()) {
        FString word;
        std::getline(file,word);
        WordList.push_back(word);
    }
    //Checks if there's a random blank string at the end of the vector
    if (WordList[WordList.size()] == "") {
        WordList.pop_back();
    }
    //Deletes Pointer
    file.close();
    return true;
}

FString GenerateHiddenWord() {
    if (OpenFile("Wordlist.txt")) {
        srand((unsigned int)time(NULL));
        int32 ptr = rand() % (int32)WordList.size();
        return WordList[ptr];
    }
    exit(1);
    return DEFAULT_HIDDEN_WORD;
}

//Default Constructor
FBullCowGame::FBullCowGame() {
    Reset();
}

//Getting the max tries via a int32 TO int32 table, to keep the Flow Channel as linear as possible.
int32 FBullCowGame::getMaxTries() const{
    TMap<int32,int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };
    return WordLengthToMaxTries[(int32)myHiddenWord.length()];
}

//Resets the game
void FBullCowGame::Reset() {
    myCurrentTry = 1;
    myHiddenWord = GenerateHiddenWord();
    return;
}

//Getter Functions
int32 FBullCowGame::getCurrentTry() const {return myCurrentTry;}
int32 FBullCowGame::getHiddenWordLength() const {return (int32)myHiddenWord.length(); }
bool FBullCowGame::isGameWon() const {return bGameIsWon;}

//Submits a Valid Guess
FBullCowCount FBullCowGame::SubmitGuess(FString guess){
    myCurrentTry++;
    FBullCowCount BCC;
    for (int32 i = 0; i < myHiddenWord.length(); i++) {
        for (int32 j = 0; j < myHiddenWord.length(); j++) {
            if (guess[j] == myHiddenWord[i]) {
                if (i == j) {BCC.Bulls++;}
                else {BCC.Cows++;}
            }
        }
    }
    if (BCC.Bulls == getHiddenWordLength()) {
        bGameIsWon = true;
    }
    return BCC;
}

//Checks the Guess Validity (If it's an Isogram, Lowercase Letters, Incorrect Length)
EWordStatus FBullCowGame::checkGuessValidity(FString guess) const{
    if (!isIsogram(guess)){
        return EWordStatus::Not_Isogram;
    }
    else if (!isLowercase(guess)) {
        return EWordStatus::Not_Lowercase;
    }
    else if (guess.length() != getHiddenWordLength()) {
        return EWordStatus::Wrong_Length;
    }
    else {
        return EWordStatus::OK;
    }
}

//Checks via a char TO bool map if the Guess is an Isogram
bool FBullCowGame::isIsogram(FString guess) const {
    if (guess.length() <= 1) {return true;}
    TMap <char,bool> LetterSeen;
    for (auto Letter : guess) {
        Letter = tolower(Letter);
        if (LetterSeen[Letter]){
            return false;
        }
        else {
            LetterSeen[Letter] = true;
        }
    }
    return true;
}

//Checks if the Guess is in Capital or Lowercase
bool FBullCowGame::isLowercase(FString guess) const {
    for (auto Letter:guess){
        if (!islower(Letter))
        {
            return false;
        }
    }
    return true;
}
