#include<iostream>
#include<iomanip>
#include<string>
#include<cstdlib>
#include<cassert>

#include "hand.h"
#include "card.h"
#include "player.h"
#include "rand.h"
#include "deck.h"

using namespace std;

void shuffle(Deck &decks, Player* player){
    cout << "Shuffling the deck" <<endl;
    for (int i = 1; i <= 7; i++) {
        int cut = get_cut();
        cout << "cut at " << cut << endl; 
        decks.shuffle(cut);
    }
    player->shuffled();
}

int main(int argc, char* argv[]){
    unsigned int bankroll = atoi(argv[1]);
    int hands = atoi(argv[2]);
    unsigned int minimum = 5;
    Player* player = NULL;
    if (string(argv[3]) == "simple") {
        player = get_Simple();
    }
    if (string(argv[3]) == "counting") {
        player = get_Counting();
    }

    Deck decks;
    decks.reset();

    shuffle(decks,player);
    Hand player_hand, dealer_hand;

    int thishand;

    for (thishand = 1; thishand <= hands; thishand++) {

        if (bankroll < minimum) break;

        player_hand.discardAll();
        dealer_hand.discardAll();

        printf("Hand %d bankroll %d\n", thishand, bankroll);
        if (decks.cardsLeft()<20) shuffle(decks,player);
        
        int wager = player->bet(bankroll,minimum);
        cout << "Player bets " << wager << endl; 

        Card new_card = decks.deal();
        cout << "Player dealt " << SpotNames[new_card.spot] << " of " << SuitNames[new_card.suit] <<endl;
        player_hand.addCard(new_card);
        player->expose(new_card);

        Card dealer_card = decks.deal();
        cout << "Dealer dealt " << SpotNames[dealer_card.spot] << " of " << SuitNames[dealer_card.suit] <<endl;
        dealer_hand.addCard(dealer_card);
        player->expose(dealer_card);

        new_card = decks.deal();
        cout << "Player dealt " << SpotNames[new_card.spot] << " of " << SuitNames[new_card.suit] <<endl;
        player_hand.addCard(new_card);
        player->expose(new_card);

        Card hole_card = decks.deal();
        dealer_hand.addCard(hole_card);        

        if (player_hand.handValue().count == 21) {
            bankroll += (int)(wager * 1.5);
            cout << "Player dealt natural 21\n"; 
            continue;
        }
        while (player->draw(dealer_card, player_hand)) {
            new_card = decks.deal();
            cout << "Player dealt " << SpotNames[new_card.spot] << " of " << SuitNames[new_card.suit] <<endl;
            player_hand.addCard(new_card);
            player->expose(new_card);
        }
        int player_count = player_hand.handValue().count;
        cout << "Player's total is " << player_count << endl; 

        if (player_count > 21) {
            cout << "Player busts\n";
            bankroll -= wager;
            continue;
        }
        cout << "Dealer's hole card is " << SpotNames[hole_card.spot] << " of " << SuitNames[hole_card.suit] <<endl;
        player->expose(hole_card);

        while (dealer_hand.handValue().count < 17) {
            dealer_card = decks.deal();
            cout << "Dealer dealt " << SpotNames[dealer_card.spot] << " of " << SuitNames[dealer_card.suit] <<endl;
            dealer_hand.addCard(dealer_card);
            player->expose(dealer_card);
        }
        int dealer_count = dealer_hand.handValue().count;
        cout << "Dealer's total is " << dealer_count << endl;
        if (dealer_count > 21) {
            cout << "Dealer busts\n"; 
            bankroll += wager;
            continue;
        }
        if (player_count>dealer_count) {
            bankroll+=wager;
            cout << "Player wins\n";
        } 
        if (player_count==dealer_count) cout << "Push\n"; 
        if (player_count<dealer_count) {
            bankroll-=wager;
            cout << "Dealer wins\n"; 
        }
    }
    cout << "Player has " << bankroll  << " after " << thishand-1 << " hands\n"; 
    return 0;
}