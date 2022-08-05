//TANIA RUIZ AND CONNOR STURGEON DEVELOPED THE FOLLOWING CODE
//TO PLAY FOR MULTIPLE ROUNDS IN A GAME, ONE PLAYER MUST CHOOSE TO SWAP A CARD IN THEIR HAND WITH ONE IN DISCARD

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#include "structs.h"
#include "betPrototypes.h"

void initializePlayers(players* p, int numPlayers); //Prototype for initializing all players
int dealerBet(players* p, int numPlayers); //Prototype for getting the dealer's bet
void playerBets(players* p, int numPlayers, int bet); //Prototype for getting the players' bets
int potTotal(players* p, int numPlayers); //Prototype for getting total money in pot
void nextDealer(players* p, int numPlayers); //Prototype for getting next dealer

void shuffleAndDeal(players* p, int numPlayers, int bet, int pot, int gameCount); //Prototypes for shuffling the card deck
card* fileDeck(); //Prototype to read file of cards (Note: Reuses code from class)
card* newDeck(); //Prototype to make new deck
//card* discardDeck();
card* shuffleCards(card* pack); //Prototype to shuffle card deck
void DealCard(card** pack, card** hand1, card** hand2, card** hand3, card** hand4, card** hand5, card** hand6, int numOfCardsDealt, int numPlayers); //Prototype to deal cards to players AND to update left over cards
void printCard(card* pack, int option, int check, int numPlayers); //Prototype to display card number
void suitType(char suitChar, char suit[9], int option); //Prototype to display suit type

void printHandAndScore(players* p, int numPlayers, int i, int option, int check, card* hand1, card* hand2, card* hand3, card* hand4, card* hand5, card* hand6); //Prototype to go through a bunch of if-else statements to print each player's hand

bool playGame(players* p, int numPlayers, int pot, int gameCount, int round, card* hand1, card* hand2, card* hand3, card* hand4, card* hand5, card* hand6, card* pack, card* discardPile); //Prototype for each player's turn
int playerOptions(int player, int numPlayers, players* p, card* hand1, card* hand2, card* hand3, card* hand4, card* hand5, card* hand6); //Prototype for each player's 3 options on their turn


void swapStock(int i, card** hand1, card** hand2, card** hand3, card** hand4, card** hand5, card** hand6, card** pack); //Prototype to swap a card in hand for a card in stock
void swapDiscard(int i, card** hand1, card** hand2, card** hand3, card** hand4, card** hand5, card** hand6, card** discardPile); //Prototype to swap a card in hand for a card in discard
int scoreCount(card* pack, int option, int check, int numPlayers); //Prototype to count the score of each player's hand

void discardCard(int currentPlayer, card** hand1, card** hand2, card** hand3, card** hand4, card** hand5, card** hand6, card** pack, card** discardPile);

void winCondition(players* p, int numPlayers, int pot, int gameCount, card* hand1, card* hand2, card* hand3, card* hand4, card* hand5, card* hand6);
bool thirtyOneCheck(players* p, int i); //Prototype that checks if the player has a score of 31

int main(void) {
    char endCondition = 'a';
    int game = 1, bet = 0, numPlayers, pot = 0, gameCount = 1, i;
    const int playersNum;
    card* hand1, * hand2, * hand3, * hand4, * hand5, * hand6;
    srand(time(NULL)); //randomizes number ----- from the time.h and stdlib.h libraries

    printf("      [..           [..           [..           [..           [..           [..     \n");
    printf(" [..  [..  [.. [..  [..  [.. [..  [..  [.. [..  [..  [.. [..  [..  [.. [..  [..  [..\n");
    printf("   [. [. [..     [. [. [..     [. [. [..     [. [. [..     [. [. [..     [. [. [..  \n");
    printf("[.... [.......[.... [.......[.... [.......[.... [.......[.... [.......[.... [.......\n");
    printf("   ,--------.,--.     ,--.         ,--.                ,-----.                 \n");
    printf("   '--.  .--'|  ,---. `--',--.--.,-'  '-.,--. ,--.    '  .-.  ',--,--,  ,---.  \n");
    printf("      |  |   |  .-.  |,--.|  .--''-.  .-' \x92  '  /     |  | |  ||      \x92| .-. : \n");
    printf("      |  |   |  | |  ||  ||  |     |  |    \x92   '      '  '-'  '|  ||  |\x92   --. \n");
    printf("      `--'   `--' `--'`--'`--'     `--'  .-'  /        `-----' `--''--' `----' \n");
    printf("[.... [.......[.... [.......[.... [......`---'. [.......[.... [.......[.... [.......\n");
    printf("   [. [. [..     [. [. [..     [. [. [..     [. [. [..     [. [. [..     [. [. [..  \n");
    printf(" [..  [..  [.. [..  [..  [.. [..  [..  [.. [..  [..  [.. [..  [..  [.. [..  [..  [..\n");
    printf("      [..           [..           [..           [..           [..           [..     \n");


    printf("\nHow many people will be playing (max amount is 6): "); //For the extra credit
    scanf("%d", &numPlayers); //For the extra credit
    while (numPlayers > 6) {
        printf("You have too many players. Please re-enter how many people will be playing: ");
        scanf("%d", &numPlayers);
    }
    printf("\n");

    players p[6]; //Declares struct array with elements equal to the number of players

    initializePlayers(p, numPlayers); //Initializes the important info before game starts

    while (endCondition != 'q') { //Game will end if either player loses all their money or if user chooses to quit
        printf("                                                 ______ ____    \n");
        printf("                                                |__    |_   |   \n");
        printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ |__GAME|%d|  |_ \n", game);
        printf("                                                |______|______| \n\n");
        //printf("-------GAME %d BEGIN!-------\n", game); //Displays the round number

        for (i = 0; i < numPlayers; ++i) {
            p[i].knock = false; //Makes it so that no player has knocked
            p[i].score = 0;
        }

        for (i = 0; i < numPlayers; ++i) { //Iterates through all players
            if (p[i].dealer == true) { //If the iterated player is the dealer,
                printf("This round, PLAYER %d will be our DEALER.\n\n", i + 1); //Tells who will be dealer
            }
        }

        shuffleAndDeal(p, numPlayers, bet, pot, gameCount); //Shuffles and deals card to players

        ++gameCount;

        printf("Would you like to quit playing the game? (y/n)\n");
        scanf("%*c%c", &endCondition); //End condition for while loop

        if (endCondition == 'y') {
            break;
        }
        else {
            ++game; //Incremements round counter
            nextDealer(p, numPlayers); //Gets next dealer
            printf("\n\n");
        }
    }

    printf("\n\nYour game of THIRTY ONE has ended.\n");
    return 0;
}

void shuffleAndDeal(players* p, int numPlayers, int bet, int pot, int gameCount) {
    card* pack, * hand1, * hand2, * hand3, * hand4, * hand5, * hand6, * discardPile = NULL; //* discardPile,
    int option, score, check = 0, round = 1, i;
    bool win = false;

    printf("Press 1 to shuffle a brand new deck\n");
    printf("\t\t -or-\n");
    printf("Press 2 to load a deck from a file\n");
    scanf("%d", &option);

    pack = newDeck();
    //discardPile = discarDeck();

    if (option == 1) { //to create the brand new deck of 52 cards... I hope.
        pack = shuffleCards(pack);
        fflush(stdout); //clears the output buffer and move the buffered data to console.		  // nore info: https://www.geeksforgeeks.org/use-fflushstdin-c/
    }
    else if (option == 2) {
        pack = fileDeck(pack);
    }

    DealCard(&pack, &hand1, &hand2, &hand3, &hand4, &hand5, &hand6, 3, numPlayers);

    for (i = 0; i < numPlayers; ++i) {
        printf("\nPLAYER %d'S HAND:", i + 1);
        printHandAndScore(p, numPlayers, i, option, check, hand1, hand2, hand3, hand4, hand5, hand6);
    }

    bet = dealerBet(p, numPlayers); //Gets the dealer's bet, which is needed for the player's bets
    playerBets(p, numPlayers, bet); //Gets the players' bets
    pot = potTotal(p, numPlayers); //Gets how much money is now in the pot

    for (i = 0; i < numPlayers; ++i) {
        win = thirtyOneCheck(p, i);
        if (win == true) {
            printf("Well aren't you lucky, PLAYER %d! You were dealt a hand of exactly THIRTY ONE!\n", i + 1);
            p[i].money += pot; //The amount of money in the pot is divided among all winners and added to the money they own
            printf("You won %d dollars from the POT!\n You now own %d dollars in total!\n", pot, p[i].money);
        }
    }

    while (win != true) { //Iterate the gameplay until someone is declared a winner
        win = playGame(p, numPlayers, pot, gameCount, round, hand1, hand2, hand3, hand4, hand5, hand6, pack, discardPile);
        check = 1;
        ++round;
    }

    free(hand1); 	//free memory pointed by pointers when you don't need it anymore
    free(hand2);
    if (numPlayers == 3) {
        free(hand3);
    }
    if (numPlayers == 4) {
        free(hand4);
    }
    if (numPlayers == 5) {
        free(hand5);
    }
    if (numPlayers == 6) {
        free(hand6);
    }
    free(pack);
}

card* fileDeck() {
    card* pack = NULL, * temp, * tail = NULL;

    FILE* file;
    file = fopen("cards.txt", "r");
    temp = (card*)malloc(sizeof(card));

    while (!feof(file)) {
        fscanf(file, "%d %c", &temp->value, &temp->suitChar);
        if (pack == NULL) {
            pack = temp;
        }
        else {
            tail->next = temp;
        }
        tail = temp;
        temp->next = NULL;
        temp = (card*)malloc(sizeof(card));
    }

    fclose(file);
    return pack;
}

card* newDeck() {
    card* pack = NULL, * temp = NULL, * node = NULL;
    int i, j;

    for (j = 1; j <= 13; j++) { // crates the number of cards 2 to 10, A, J, Q, K .... at the end should total 52
        for (i = 0; i < 4; i++) { // suit type; spades, diamonds, hearts, clubs

            node = (card*)malloc(sizeof(card));
            node->value = j;

            if (i == 0) {
                node->suitChar = 60; //Spades
            }
            else if (i == 1) {
                node->suitChar = 40; //Diamonds
            }
            else if (i == 2) {
                node->suitChar = 30; //Hearts
            }
            else {
                node->suitChar = 50; //Clubs
            }

            node->next = NULL;

            //continues printing combinding number AND suittype
            if (temp == NULL) {
                pack = node;
            }

            else {
                temp->next = node;
            }
            temp = node;
        }
    }
    return pack;
}

card* shuffleCards(card* pack) {
    card* cardList;
    int n, i, j, k;
    card** cardArray; //double pointer so it stores as in a array in order to shuffle.
    //the first pointer is used to store the address of the variable
    //the second pointer is used to store the address of the first pointer

    for (n = 0, cardList = pack; cardList != NULL; n++, cardList = cardList->next); // gets the size of the list

    cardArray = (card**)malloc(n * sizeof(card*));

    for (i = 0, cardList = pack; cardList != NULL; i++, cardList = cardList->next) { //stores cards in an array
        cardArray[i] = cardList;
    }

    //SHUFFLING LOOP
    for (i = 0; i < 52; i++) { //52 shuffles for 52 cards :)
        for (j = 0; j < n; j++) { //for every index in the suffle it gets a random number to swap
            k = rand() % n;
            cardList = cardArray[j];
            cardArray[j] = cardArray[k];
            cardArray[k] = cardList;
        }
    }

    for (i = 0; i < n - 1; i++) { //creates a new order for the lists... puts them together.
        cardArray[i]->next = cardArray[i + 1];
    }

    cardArray[i]->next = NULL; // list end
    cardList = cardArray[0]; // new order for list
    free(cardArray);
    return cardList;
}

//deals cards AND updates left over cards
void DealCard(card** pack, card** hand1, card** hand2, card** hand3, card** hand4, card** hand5, card** hand6, int number, int numPlayers) {
    card* pickedCard, * card1, * card2, * card3, * card4, * card5, * card6; // stores scanned/picked card in each list... 3 lists total; player 1, player 2, left-over list.
    int deal, i;

    card1 = card2 = card3 = card4 = card5 = card6 = NULL;
    pickedCard = *pack;
    //makes sure it deals one card per player
    for (deal = 0; deal < (numPlayers * number) && pickedCard != NULL; deal++, pickedCard = pickedCard->next) {
        //variable number is the amount of cards that's going to be dealt to each player.
        //this for loop initilizes two variables simultaneously... deal and picked card
        //it has two test conditions joined togeter using logical operator (deal < 2 * number && pickedCard != NULL).
        //it has two varaibles in increments part (deal incrememts by one, and it moves the linked list to the next).
        // source: https://beginnersbook.com/2014/01/c-for-loop/

        if (deal % numPlayers == 0) {
            if (card1 == NULL) { //1st elmt in lst
                *hand1 = pickedCard;
            }
            else {
                card1->next = pickedCard;
            }
            card1 = pickedCard;
        }
        else if ((deal - 1) % numPlayers == 0) {
            if (card2 == NULL) { //1st elmt in lst
                *hand2 = pickedCard;
            }
            else {
                card2->next = pickedCard;
            }
            card2 = pickedCard;
        }
        else if ((deal - 2) % numPlayers == 0) {
            if (card3 == NULL) { //1st elmt in lst
                *hand3 = pickedCard;
            }
            else {
                card3->next = pickedCard;
            }
            card3 = pickedCard;
        }
        else if ((deal - 3) % numPlayers == 0) {
            if (card4 == NULL) { //1st elmt in lst
                *hand4 = pickedCard;
            }
            else {
                card4->next = pickedCard;
            }
            card4 = pickedCard;
        }
        else if ((deal - 4) % numPlayers == 0) {
            if (card5 == NULL) { //1st elmt in lst
                *hand5 = pickedCard;
            }
            else {
                card5->next = pickedCard;
            }
            card5 = pickedCard;
        }
        else if ((deal - 5) % numPlayers == 0) {
            if (card6 == NULL) { //1st elmt in lst
                *hand6 = pickedCard;
            }
            else {
                card6->next = pickedCard;
            }
            card6 = pickedCard;
        }
    }

    for (i = 0; i < numPlayers; ++i) {
        if (i == 0) {
            card1->next = NULL;
        }
        else if (i == 1) {
            card2->next = NULL;
        }
        else if (i == 2) {
            card3->next = NULL;
        }
        else if (i == 3) {
            card4->next = NULL;
        }
        else if (i == 4) {
            card5->next = NULL;
        }
        else if (i == 5) {
            card6->next = NULL;
        }
    }
    *pack = pickedCard; // this is what updates the deck with the left-over cards 
}

//Linked list
//prints the card into console
void printCard(card* pack, int option, int check, int numPlayers) {
    int i;
    for (i = 0; pack != NULL; i++, pack = pack->next) { //goes through all the cards until there are 0. 
        if (i % 4 == 0) { //prints enter every 4 cards... so it's four columns
            printf("\n");
        }

        //frist, special cases for cards AJQK by taking the value from 
        if (check == 0) {
            if (i < 52) {
                if (pack->value == 14) {
                    printf("A");
                }
                else if (pack->value == 11) {
                    printf("J");
                }
                else if (pack->value == 12) {
                    printf("Q");
                }
                else if (pack->value == 13) {
                    printf("K");
                }
                else if (pack->value == 1) {
                    printf("A");
                }
                else {
                    printf("%d", pack->value);
                }
                suitType(pack->suitChar, pack->suit, option);
                printf("\t");
            }
        }
        else if (check == 1) { //For discard
            if (i < 52 - (3 * numPlayers)) {
                if (pack->value == 14) {
                    printf("A");
                }
                else if (pack->value == 11) {
                    printf("J");
                }
                else if (pack->value == 12) {
                    printf("Q");
                }
                else if (pack->value == 13) {
                    printf("K");
                }
                else if (pack->value == 1) {
                    printf("A");
                }
                else {
                    printf("%d", pack->value);
                }
                suitType(pack->suitChar, pack->suit, option);
                printf("\t");
            }
        }
    }
    printf("\n");
}

void suitType(char suitChar, char suit[9], int option) { //unicode codes https://stackoverflow.com/questions/47229429/how-can-i-print-card-suit-characters-in-c-win32-console-application

    //Some characters are chaged for whatever reason, so this changes them back
    if (suitChar == 50) {
        suitChar = '\x05';
    }
    else if (suitChar == 30) {
        suitChar = '\x03';
    }
    else if (suitChar == 60) {
        suitChar = '\x06';
    }
    else if (suitChar == 40) {
        suitChar = '\x04';
    }

    suit[0] = suitChar;
    printf("%c", suit[0]);
}

void printHandAndScore(players* p, int numPlayers, int i, int option, int check, card* hand1, card* hand2, card* hand3, card* hand4, card* hand5, card* hand6) {
    if (i == 0) {
        printCard(hand1, option, check, numPlayers);
        p[i].score = scoreCount(hand1, option, check, numPlayers);
        printf("SCORE: %d\n", p[i].score);
    }
    else if (i == 1) {
        printCard(hand2, option, check, numPlayers);
        p[i].score = scoreCount(hand2, option, check, numPlayers);
        printf("SCORE: %d\n", p[i].score);
    }
    else if (i == 2) {
        printCard(hand3, option, check, numPlayers);
        p[i].score = scoreCount(hand3, option, check, numPlayers);
        printf("SCORE: %d\n", p[i].score);
    }
    else if (i == 3) {
        printCard(hand4, option, check, numPlayers);
        p[i].score = scoreCount(hand4, option, check, numPlayers);
        printf("SCORE: %d\n", p[i].score);
    }
    else if (i == 4) {
        printCard(hand5, option, check, numPlayers);
        p[i].score = scoreCount(hand5, option, check, numPlayers);
        printf("SCORE: %d\n", p[i].score);
    }
    else if (i == 5) {
        printCard(hand6, option, check, numPlayers);
        p[i].score = scoreCount(hand6, option, check, numPlayers);
        printf("SCORE: %d\n", p[i].score);
    }
}

bool playGame(players* p, int numPlayers, int pot, int gameCount, int round, card* hand1, card* hand2, card* hand3, card* hand4, card* hand5, card* hand6, card* pack, card* discardPile) {
    int choice, i, a = 0, b, option = 0, check = 0;
    bool win = false;

    for (i = 0; i < numPlayers; ++i) { //Cycles to find dealer and gives them their option
        if (p[i].dealer == true && p[i].fold == false) { //First player is the dealer, so long as they haven't yet folded
            printf("\n\n--------------------------------------------------------");
            printf("\nIt is now the DEALER'S turn. This is your current hand:");
            printHandAndScore(p, numPlayers, i, option, check, hand1, hand2, hand3, hand4, hand5, hand6);
            printf("You have the following options:\n");
            if (round == 1) {
                printf("PRESS 1 if you would like to swap a card in your hand from the STOCK pile.\n");
                printf("PRESS 3 if you are confident in your hand and want to KNOCK on the table.\n");
            }
            else {
                printf("PRESS 1 if you would like to swap a card in your hand from the STOCK pile.\n");
                printf("PRESS 2 if you would like to swap a card in your hand from the DISCARD pile.\n");
                printf("PRESS 3 if you are confident in your hand and want to KNOCK on the table.\n");
            }

            scanf("%d", &choice);

            while (choice < 1 || choice > 3) { //If player's choice is out of range
                printf("Your choice is not an option. Re-enter 1, 2, or 3: ");
                scanf("%d", &choice);
                printf("\n");
            }

            if (choice == 1) { //If they want to swap with stock pile

                swapStock(i, &hand1, &hand2, &hand3, &hand4, &hand5, &hand6, &pack);
                printHandAndScore(p, numPlayers, i, option, check, hand1, hand2, hand3, hand4, hand5, hand6);
                discardCard(i, &hand1, &hand2, &hand3, &hand4, &hand5, &hand6, &pack, &discardPile);
                printf("Your new hand is: ");
                printHandAndScore(p, numPlayers, i, option, check, hand1, hand2, hand3, hand4, hand5, hand6);
            }
            else if (choice == 2) { //If they want to swap with discard pile

                swapDiscard(i, &hand1, &hand2, &hand3, &hand4, &hand5, &hand6, &discardPile);
                printHandAndScore(p, numPlayers, i, option, check, hand1, hand2, hand3, hand4, hand5, hand6);
                discardCard(i, &hand1, &hand2, &hand3, &hand4, &hand5, &hand6, &pack, &discardPile);
                printf("Your new hand is: ");
                printHandAndScore(p, numPlayers, i, option, check, hand1, hand2, hand3, hand4, hand5, hand6);
            }
            else if (choice == 3) { //If they want to knock
                p[i].knock = true;
                a = i; //Holds the array value for the dealer
                printf("\n\n***********ATTENTION! The DEALER just KNOCKED on the table!***********\n*****All other PLAYERS have one more turn to improve their hand!******\n");

                for (i = 0; i < numPlayers; ++i) { //Goes through all other players who didn't knock
                    if (p[i].knock == false) {
                        choice = playerOptions(i + 1, numPlayers, p, hand1, hand2, hand3, hand4, hand5, hand6); //Goes through the list of different options the player has
                    }
                    if (choice == 1) {

                        swapStock(i, &hand1, &hand2, &hand3, &hand4, &hand5, &hand6, &pack);
                        printHandAndScore(p, numPlayers, i, option, check, hand1, hand2, hand3, hand4, hand5, hand6);
                        discardCard(i, &hand1, &hand2, &hand3, &hand4, &hand5, &hand6, &pack, &discardPile);
                        printf("Your new hand is: ");
                        printHandAndScore(p, numPlayers, i, option, check, hand1, hand2, hand3, hand4, hand5, hand6);
                    }
                    else if (choice == 2) {

                        swapDiscard(i, &hand1, &hand2, &hand3, &hand4, &hand5, &hand6, &discardPile);
                        printHandAndScore(p, numPlayers, i, option, check, hand1, hand2, hand3, hand4, hand5, hand6);
                        discardCard(i, &hand1, &hand2, &hand3, &hand4, &hand5, &hand6, &pack, &discardPile);
                        printf("Your new hand is: ");
                        printHandAndScore(p, numPlayers, i, option, check, hand1, hand2, hand3, hand4, hand5, hand6);
                    }
                }

                winCondition(p, numPlayers, pot, gameCount, hand1, hand2, hand3, hand4, hand5, hand6);
                win = true; //Somebody has won
            }

        }
    }

    if (p[a].knock == false) { //If the dealer did not knock on the table
        for (i = 0; i < numPlayers; ++i) { //Cycles through the rest of the players and their options
            if (p[i].dealer == false && p[i].fold == false) { //The rest of the players are non-dealers, so long as they haven't folded
                printf("\n\n--------------------------------------------------------");
                printf("\nIt is now the PLAYER %d'S turn. This is your current hand:", i + 1);
                printHandAndScore(p, numPlayers, i, option, check, hand1, hand2, hand3, hand4, hand5, hand6);
                printf("You have the following options:\nPRESS 1 if you would like to swap a card in your hand from the STOCK pile.\n");
                printf("PRESS 2 if you would like to swap a card in your hand from the DISCARD pile.\n");
                printf("PRESS 3 if you are confident in your hand and want to KNOCK on the table.\n");
                scanf("%d", &choice);

                while (choice < 1 || choice > 3) { //If player's choice is out of range
                    printf("Your choice is not an option. Re-enter 1, 2, or 3: ");
                    scanf("%d", &choice);
                    printf("\n");
                }

                if (choice == 1) { //If they want to swap with stock pile
                    swapStock(i, &hand1, &hand2, &hand3, &hand4, &hand5, &hand6, &pack);
                    printHandAndScore(p, numPlayers, i, option, check, hand1, hand2, hand3, hand4, hand5, hand6);
                    discardCard(i, &hand1, &hand2, &hand3, &hand4, &hand5, &hand6, &pack, &discardPile);
                    printHandAndScore(p, numPlayers, i, option, check, hand1, hand2, hand3, hand4, hand5, hand6);
                }
                else if (choice == 2) { //If they want to swap with discard pile
                    swapDiscard(i, &hand1, &hand2, &hand3, &hand4, &hand5, &hand6, &discardPile);
                    printHandAndScore(p, numPlayers, i, option, check, hand1, hand2, hand3, hand4, hand5, hand6);
                    discardCard(i, &hand1, &hand2, &hand3, &hand4, &hand5, &hand6, &pack, &discardPile);
                    printHandAndScore(p, numPlayers, i, option, check, hand1, hand2, hand3, hand4, hand5, hand6);
                }
                else if (choice == 3) { //If they want to knock
                    p[i].knock = true;
                    a = i; //Holds the array value for the dealer
                    printf("\n************ATTENTION! PLAYER %d just KNOCKED on the table!**********\n*****All other PLAYERS have one more turn to improve their hand!*****\n", i + 1);

                    for (i = 0; i < numPlayers; ++i) { //Goes through all other players who didn't knock
                        if (p[i].knock == false && p[i].fold == false) {
                            choice = playerOptions(i + 1, numPlayers, p, hand1, hand2, hand3, hand4, hand5, hand6); //Goes through the list of different options the player has
                        }
                        if (choice == 1 && p[i].fold == false) {
                            swapStock(i, &hand1, &hand2, &hand3, &hand4, &hand5, &hand6, &pack);
                            printHandAndScore(p, numPlayers, i, option, check, hand1, hand2, hand3, hand4, hand5, hand6);
                            discardCard(i, &hand1, &hand2, &hand3, &hand4, &hand5, &hand6, &pack, &discardPile);
                            printHandAndScore(p, numPlayers, i, option, check, hand1, hand2, hand3, hand4, hand5, hand6);
                        }
                        else if (choice == 2 && p[i].fold == false) {
                            swapDiscard(i, &hand1, &hand2, &hand3, &hand4, &hand5, &hand6, &discardPile);
                            printHandAndScore(p, numPlayers, i, option, check, hand1, hand2, hand3, hand4, hand5, hand6);
                            discardCard(i, &hand1, &hand2, &hand3, &hand4, &hand5, &hand6, &pack, &discardPile);
                            printHandAndScore(p, numPlayers, i, option, check, hand1, hand2, hand3, hand4, hand5, hand6);
                        }
                    }
                    winCondition(p, numPlayers, pot, gameCount, hand1, hand2, hand3, hand4, hand5, hand6);
                    win = true; //Somebody has won
                }

            }
        }
    }

    return win;
}

int playerOptions(int player, int numPlayers, players* p, card* hand1, card* hand2, card* hand3, card* hand4, card* hand5, card* hand6) { //Three options the other players have once one player has knocked
    int choice, option = 0, check = 0, i;

    i = player - 1;
    printf("\n\n--------------------------------------------------------");
    printf("\nIt is now the PLAYER %d'S turn. This is your current hand:", player);
    printHandAndScore(p, numPlayers, i, option, check, hand1, hand2, hand3, hand4, hand5, hand6);
    printf("You have the following options:\n");
    printf("PRESS 1 if you would like to swap a card in your hand from the STOCK pile.\n");
    printf("PRESS 2 if you would like to swap a card in your hand from the DISCARD pile.\n");
    printf("PRESS ANY OTHER NUMBER to do nothing\n");
    scanf("%d", &choice);

    return choice;
}

//SWAP CARD FROM STOCK PILE
void swapStock(int i, card** hand1, card** hand2, card** hand3, card** hand4, card** hand5, card** hand6, card** pack) {
    //card* newNode = *pack;
    card* newNode = *pack;  // the front source node

    if (i == 0) {   //i + 1 is the current player
        *pack = (*pack)->next;           // advance the source pointer
        newNode->next = *hand1;          // link the old location off the new node
        *hand1 = newNode;                // move card to point to the new node

    }
    else if (i == 1) {
        *pack = (*pack)->next;
        newNode->next = *hand2;
        *hand2 = newNode;

    }
    else if (i == 2) {
        *pack = (*pack)->next;
        newNode->next = *hand3;
        *hand3 = newNode;

    }
    else if (i == 3) {
        *pack = (*pack)->next;
        newNode->next = *hand4;
        *hand4 = newNode;

    }
    else if (i == 4) {
        *pack = (*pack)->next;
        newNode->next = *hand5;
        *hand5 = newNode;

    }
    else if (i == 5) {
        *pack = (*pack)->next;
        newNode->next = *hand6;
        *hand6 = newNode;

    }
}

//TAKES CARD FROM DISCARD PILE
void swapDiscard(int i, card** hand1, card** hand2, card** hand3, card** hand4, card** hand5, card** hand6, card** discardPile) {
    struct card_s* newNode = *discardPile;

    if (i == 0) { //i + 1 is the current player
        *discardPile = (*discardPile)->next;
        newNode->next = *hand1;
        *hand1 = newNode;
    }
    else if (i == 1) {
        *discardPile = (*discardPile)->next;
        newNode->next = *hand2;
        *hand2 = newNode;
    }
    else if (i == 2) {
        *discardPile = (*discardPile)->next;
        newNode->next = *hand3;
        *hand3 = newNode;
    }
    else if (i == 3) {
        *discardPile = (*discardPile)->next;
        newNode->next = *hand4;
        *hand4 = newNode;
    }
    else if (i == 4) {
        *discardPile = (*discardPile)->next;
        newNode->next = *hand5;
        *hand5 = newNode;
    }
    else {
        *discardPile = (*discardPile)->next;
        newNode->next = *hand6;
        *hand6 = newNode;
    }
}



void discardCard(int currentPlayer, card** hand1, card** hand2, card** hand3, card** hand4, card** hand5, card** hand6, card** pack, card** discardPile) {
    int discardChoice = 0;
    card* temp = NULL;

    //first card will be the one that was just picked up from either the discard pile or the shuffled deck pile (pack)
    printf("First card is the card you just picked up.");
    printf("\nWhich card would you like to discard?");
    printf("\nPlease enter 2 for second card, 3 for third card, or 4 for fourth card\n");
    scanf("%d", &discardChoice);


    card* prev = NULL;
    card* traverseOne = NULL; //transverse list nodes one by one
    card* skiptrasverseOne = NULL; // to transverse list nodes by skipping one

    /*
    * identify which card the user wants to discard
    * move to the front of the hand
    * move it to discardPile
    */
    if (discardChoice == 2) { //Choice for discarding
        if (currentPlayer == 0) {
            traverseOne = (*hand1);
            skiptrasverseOne = (*hand1);

            //finds the node of where the desired card to be discarded is
            while (skiptrasverseOne != NULL && skiptrasverseOne->next != NULL) {
                prev = traverseOne;
                skiptrasverseOne = skiptrasverseOne->next->next->next;
                traverseOne = traverseOne->next;
            }

            //moves node to head
            prev->next = prev->next->next;
            traverseOne->next = (*hand1);
            (*hand1) = traverseOne;
        }
        else if (currentPlayer == 1) {
            traverseOne = (*hand2);
            skiptrasverseOne = (*hand2);

            while (skiptrasverseOne != NULL && skiptrasverseOne->next != NULL) {
                prev = traverseOne;
                skiptrasverseOne = skiptrasverseOne->next->next->next;
                traverseOne = traverseOne->next;
            }

            prev->next = prev->next->next;
            traverseOne->next = (*hand2);
            (*hand2) = traverseOne;
        }
        else if (currentPlayer == 2) {
            traverseOne = (*hand3);
            skiptrasverseOne = (*hand3);
            while (skiptrasverseOne != NULL && skiptrasverseOne->next != NULL) {
                prev = traverseOne;
                skiptrasverseOne = skiptrasverseOne->next->next->next;
                traverseOne = traverseOne->next;
            }

            prev->next = prev->next->next;
            traverseOne->next = (*hand3);
            (*hand3) = traverseOne;
        }
        else if (currentPlayer == 3) {
            traverseOne = (*hand4);
            skiptrasverseOne = (*hand4);

            while (skiptrasverseOne != NULL && skiptrasverseOne->next != NULL) {
                prev = traverseOne;
                skiptrasverseOne = skiptrasverseOne->next->next->next;
                traverseOne = traverseOne->next;
            }

            prev->next = prev->next->next;
            traverseOne->next = (*hand4);
            (*hand4) = traverseOne;
        }
        else if (currentPlayer == 4) {
            traverseOne = (*hand5);
            skiptrasverseOne = (*hand5);

            while (skiptrasverseOne != NULL && skiptrasverseOne->next != NULL) {
                prev = traverseOne;
                skiptrasverseOne = skiptrasverseOne->next->next->next;
                traverseOne = traverseOne->next;
            }

            prev->next = prev->next->next;
            traverseOne->next = (*hand5);
            (*hand5) = traverseOne;
        }
        else {
            traverseOne = (*hand6);
            skiptrasverseOne = (*hand6);

            while (skiptrasverseOne != NULL && skiptrasverseOne->next != NULL) {
                prev = traverseOne;
                skiptrasverseOne = skiptrasverseOne->next->next->next;
                traverseOne = traverseOne->next;
            }

            prev->next = prev->next->next;
            traverseOne->next = (*hand6);
            (*hand6) = traverseOne;
        }
    }

    else if (discardChoice == 3) { //Choice for discarding
        if (currentPlayer == 0) {
            traverseOne = (*hand1);
            skiptrasverseOne = (*hand1);

            while (skiptrasverseOne != NULL && skiptrasverseOne->next != NULL) {
                prev = traverseOne;
                skiptrasverseOne = skiptrasverseOne->next->next;
                traverseOne = traverseOne->next;
            }

            prev->next = prev->next->next;
            traverseOne->next = (*hand1);
            (*hand1) = traverseOne;
        }
        else if (currentPlayer == 1) {
            traverseOne = (*hand2);
            skiptrasverseOne = (*hand2);

            while (skiptrasverseOne != NULL && skiptrasverseOne->next != NULL) {
                prev = traverseOne;
                skiptrasverseOne = skiptrasverseOne->next->next;
                traverseOne = traverseOne->next;
            }

            prev->next = prev->next->next;
            traverseOne->next = (*hand2);
            (*hand2) = traverseOne;
        }
        else if (currentPlayer == 2) {
            traverseOne = (*hand3);
            skiptrasverseOne = (*hand3);
            while (skiptrasverseOne != NULL && skiptrasverseOne->next != NULL) {
                prev = traverseOne;
                skiptrasverseOne = skiptrasverseOne->next->next;
                traverseOne = traverseOne->next;
            }

            prev->next = prev->next->next;
            traverseOne->next = (*hand3);
            (*hand3) = traverseOne;
        }
        else if (currentPlayer == 3) {
            traverseOne = (*hand4);
            skiptrasverseOne = (*hand4);

            while (skiptrasverseOne != NULL && skiptrasverseOne->next != NULL) {
                prev = traverseOne;
                skiptrasverseOne = skiptrasverseOne->next->next;
                traverseOne = traverseOne->next;
            }

            prev->next = prev->next->next;
            traverseOne->next = (*hand4);
            (*hand4) = traverseOne;
        }
        else if (currentPlayer == 4) {
            traverseOne = (*hand5);
            skiptrasverseOne = (*hand5);

            while (skiptrasverseOne != NULL && skiptrasverseOne->next != NULL) {
                prev = traverseOne;
                skiptrasverseOne = skiptrasverseOne->next->next;
                traverseOne = traverseOne->next;
            }

            prev->next = prev->next->next;
            traverseOne->next = (*hand5);
            (*hand5) = traverseOne;
        }
        else {
            traverseOne = (*hand6);
            skiptrasverseOne = (*hand6);

            while (skiptrasverseOne != NULL && skiptrasverseOne->next != NULL) {
                prev = traverseOne;
                skiptrasverseOne = skiptrasverseOne->next->next;
                traverseOne = traverseOne->next;
            }

            prev->next = prev->next->next;
            traverseOne->next = (*hand6);
            (*hand6) = traverseOne;
        }
    }

    else if (discardChoice == 4) { //Choice for discarding
        if (currentPlayer == 0) {
            traverseOne = (*hand1);
            skiptrasverseOne = (*hand1);

            while (skiptrasverseOne != NULL && skiptrasverseOne->next != NULL) {
                prev = traverseOne;
                skiptrasverseOne = skiptrasverseOne->next;
                traverseOne = traverseOne->next;
            }

            prev->next = prev->next->next;
            traverseOne->next = (*hand1);
            (*hand1) = traverseOne;
        }
        else if (currentPlayer == 1) {
            traverseOne = (*hand2);
            skiptrasverseOne = (*hand2);

            while (skiptrasverseOne != NULL && skiptrasverseOne->next != NULL) {
                prev = traverseOne;
                skiptrasverseOne = skiptrasverseOne->next;
                traverseOne = traverseOne->next;
            }

            prev->next = prev->next->next;
            traverseOne->next = (*hand2);
            (*hand2) = traverseOne;
        }
        else if (currentPlayer == 2) {
            traverseOne = (*hand3);
            skiptrasverseOne = (*hand3);
            while (skiptrasverseOne != NULL && skiptrasverseOne->next != NULL) {
                prev = traverseOne;
                skiptrasverseOne = skiptrasverseOne->next;
                traverseOne = traverseOne->next;
            }

            prev->next = prev->next->next;
            traverseOne->next = (*hand3);
            (*hand3) = traverseOne;
        }
        else if (currentPlayer == 3) {
            traverseOne = (*hand4);
            skiptrasverseOne = (*hand4);

            while (skiptrasverseOne != NULL && skiptrasverseOne->next != NULL) {
                prev = traverseOne;
                skiptrasverseOne = skiptrasverseOne->next;
                traverseOne = traverseOne->next;
            }

            prev->next = prev->next->next;
            traverseOne->next = (*hand4);
            (*hand4) = traverseOne;
        }
        else if (currentPlayer == 4) {
            traverseOne = (*hand5);
            skiptrasverseOne = (*hand5);

            while (skiptrasverseOne != NULL && skiptrasverseOne->next != NULL) {
                prev = traverseOne;
                skiptrasverseOne = skiptrasverseOne->next;
                traverseOne = traverseOne->next;
            }

            prev->next = prev->next->next;
            traverseOne->next = (*hand5);
            (*hand5) = traverseOne;
        }
        else {
            traverseOne = (*hand6);
            skiptrasverseOne = (*hand6);

            while (skiptrasverseOne != NULL && skiptrasverseOne->next != NULL) {
                prev = traverseOne;
                skiptrasverseOne = skiptrasverseOne->next;
                traverseOne = traverseOne->next;
            }

            prev->next = prev->next->next;
            traverseOne->next = (*hand6);
            (*hand6) = traverseOne;
        }
    }

    //======================================= supposed to move card to discard pile

    if (currentPlayer == 0) {
        struct card_s* discardNode = *hand1;        // the front node
        *hand1 = (*hand1)->next;                    // advance the source pointer
        discardNode->next = *discardPile;           // link the old location off the new node
        *discardPile = discardNode;                 // move card to point to the new node
    }
    else if (currentPlayer == 1) {
        struct card_s* discardNode = *hand2;
        *hand2 = (*hand2)->next;
        discardNode->next = *discardPile;
        *discardPile = discardNode;
    }
    else if (currentPlayer == 2) {
        struct card_s* discardNode = *hand3;
        *hand3 = (*hand3)->next;
        discardNode->next = *discardPile;
        *discardPile = discardNode;
    }
    else if (currentPlayer == 3) {
        struct card_s* discardNode = *hand4;
        *hand4 = (*hand4)->next;
        discardNode->next = *discardPile;
        *discardPile = discardNode;
    }
    else if (currentPlayer == 4) {
        struct card_s* discardNode = *hand5;
        *hand5 = (*hand5)->next;
        discardNode->next = *discardPile;
        *discardPile = discardNode;
    }
    else {
        struct card_s* discardNode = *hand6;
        *hand6 = (*hand6)->next;
        discardNode->next = *discardPile;
        *discardPile = discardNode;
    }
}

int scoreCount(card* pack, int option, int check, int numPlayers) {
    int playerScore, i;
    int value, val1 = 0, val2 = 0, val3 = 0;
    char suit1 = 'z', suit2 = 'z', suit3 = 'z';

    for (i = 0; pack != NULL; i++, pack = pack->next) {
        //printf("suit type: %c ", pack->suit[0]); //VALUE IS CORRECT
        if (pack->value == 1 || pack->value == 14) {
            value = 11;
        }
        else if (pack->value == 11 || pack->value == 12 || pack->value == 13) {
            value = 10;
        }
        else {
            value = pack->value;
        }

        if (i == 0) {
            suit1 = pack->suit[0];
            val1 = value;
        }
        else if (i == 1) {
            suit2 = pack->suit[0];
            val2 = value;
        }
        else if (i == 2) {
            suit3 = pack->suit[0];
            val3 = value;
        }
    }

    if (suit1 == suit2 && suit2 == suit3) { //If hand has suits of all the same kind
        playerScore = val1 + val2 + val3;
    }
    else if (suit1 == suit2) { //If the first two cards are the same suit
        playerScore = val1 + val2;
    }
    else if (suit2 == suit3) { //If the last two cards are the same suit
        playerScore = val2 + val3;
    }
    else if (suit1 == suit3) { //If the first and last cards are the same suit
        playerScore = val1 + val3;
    }
    else { //If the cards are all diferet suits
        if (val1 == val2 && val2 == val3) { //If cards are of the same value
            playerScore = 30;
        }
        else {
            playerScore = 0;
        }
    }

    return playerScore;
}

bool thirtyOneCheck(players* p, int i) {
    if (p[i].score == 31) {
        return true;
    }
    else {
        return false;
    }
}

void winCondition(players* p, int numPlayers, int pot, int gameCount, card* hand1, card* hand2, card* hand3, card* hand4, card* hand5, card* hand6) {
    int option = 0, check = 0, maxScore = 0, winCounter = 0, splitMoney, i, j, a;

    for (i = 0; i < numPlayers; ++i) { //Cycle through all players
        if (thirtyOneCheck(p, i) == true) { //If the players hit exactly 31 points
            printf(" .------------------------------. \n");
            printf("| .---------------------------. | \n");
            printf("| |                           | | \n");
            printf("| |  |PLAYER %d has exactly|  | | \n", i + 1);
            printf("| |  |  THIRTY ONE points  |  | | \n");
            printf("| |                           | | \n");
            printf("| '---------------------------' | \n");
            printf(" '------------------------------' \n");
            //printf("PLAYER %d has exactly THIRTY ONE points!!\n", i + 1);
            p[i].win = true;

            for (j = 0; j < numPlayers; ++j) {
                p[j].win = false; //All other players are losers
            }
            break; //Finish cycling through the for loop
        }
        else if (p[i].score >= maxScore) { //If the player's score is greater than the current max score
            p[i].win = true; //That player is made a winning player
            maxScore = p[i].score; //The new max score is equal to the player's score

            for (j = 0; j < numPlayers; ++j) {
                if (p[j].score < maxScore) { //If any other previous winning players have scores less than the new max
                    p[j].win = false; //They are no longer made winning players
                }
            }
        }
    }

    for (i = 0; i < numPlayers; ++i) {
        if (p[i].win == true) {
            ++winCounter; //Count how many players have won the pot
        }
    }

    for (i = 0; i < numPlayers; ++i) {
        if (p[i].win == true) {
            splitMoney = pot / winCounter;
            p[i].money += splitMoney; //The amount of money in the pot is divided among all winners and added to the money they own
            printf("\n\n\t\t\tCONGRATULATIONS PLAYER %d!! You won %d dollars from the POT!\n \t\t\tYou now own %d dollars in total!\n", i + 1, splitMoney, p[i].money);

            ++p[i].winCount; //Add 1 to the win counter
            p[i].winRate = ((p[i].winCount * 1.0) / gameCount) * 100;
            printf("PLAYER %d has won %.2lf%% of games played.\n", i + 1, p[i].winRate);
        }
    }
}