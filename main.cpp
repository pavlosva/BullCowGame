//  v1.0
//  main.cpp
//  BullCowGame
//  "This file contais the Actual Game Routine as welll as the User Interaction.
//  For game logic see FBullCowGame.cpp"
//  Created by Παύλος Βασιλείου on 14/04/2017.
//  Copyright © 2017 Paul Vasileiou. All rights reserved.

#include "FBullCowGame.hpp"

//Function Declaration
void printIntro();
void __newline();
void playGame();
bool askToPlayAgain();
FText getValidGuess();

//Game Starting
FBullCowGame BCGame;

int main()
{
    bool PlayAgain = false;
    do {
        printIntro();
        playGame();
        PlayAgain = askToPlayAgain();
    }
    while (PlayAgain);
    return 0; // exit the application
}

//Prints the actual environment of the game.
void printIntro() {
    std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
    std::cout << std::endl;
    std::cout << "          }   {         ___ " << std::endl;
    std::cout << "          (o o)        (o o) " << std::endl;
    std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
    std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
    std::cout << " *  |-,--- |              |------|  * " << std::endl;
    std::cout << "    ^      ^              ^      ^ " << std::endl;
    std::cout << "Can you guess the " << BCGame.getHiddenWordLength();
    std::cout << " letter isogram that I'm thinking of?\n";
    return;
}

//Just a funky way of making a newline!
void __newline(){
    std::cout << std::endl;
    return;
}

//Actual Game Routine
void playGame(){
    //Resets the Game for the new tries.
    BCGame.Reset();
    int32 maxTries = BCGame.getMaxTries();
    //Keeps on looping while the game is not over!
    while (!BCGame.isGameWon() && BCGame.getCurrentTry() <= maxTries){
        FText guess = getValidGuess();
        FBullCowCount BCC = BCGame.SubmitGuess(guess);
        std::cout << "Bulls = " << BCC.Bulls;
        std::cout << " Cows = " << BCC.Cows;__newline();__newline();
    }
    return;
}

//Function prompting the user to play again!
bool askToPlayAgain(){
    FText answer = "";
    std::cout << "Do you want to play again (y/n)? " << std::endl;
    getline(std::cin, answer);
    return (answer[0] == 'y' || answer[0] == 'Y');
}

//Error Catching Function
FText getValidGuess() {
    //Error Iterator
    EWordStatus Status = EWordStatus::Invalid_Status;
    do {
        FText guess = "";
        std::cout << "Try " << BCGame.getCurrentTry() << " of " << BCGame.getMaxTries() << ".";
        std::cout << " Enter your guess: " << std::endl;
        getline(std::cin,guess);
        std::cout << "Your guess was \"" << guess << "\"." << std::endl;
        //Error Checking
        Status = BCGame.checkGuessValidity(guess);
        switch (Status) {
            case EWordStatus::Wrong_Length:
                std::cout << "Please enter a " << BCGame.getHiddenWordLength() << " letter word\n";
                break;
            case EWordStatus::Not_Lowercase:
                std::cout << "The string is not in lowercase!\n";
                break;
            case EWordStatus::Not_Isogram:
                std::cout << "Please enter a word with non repeating letters!\n";
                break;
            default:
                return guess;
        }
    } while (Status != EWordStatus::OK);
    return "";
}
