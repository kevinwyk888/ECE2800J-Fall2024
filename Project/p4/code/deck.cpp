#include<iostream>
#include<iomanip>
#include<string>
#include<cstdlib>
#include<cassert>

#include "deck.h"
#include "card.h"

void Deck :: reset(){
    next = 0;
    for (int i =  0; i <= 3; i++) {
        Card new_card;
        new_card.suit = (Suit) i;
        for (int j = 0; j <=12 ; j++) {
            new_card.spot = (Spot) j;
            deck[next++] = new_card;
        }
    }
    next = 0;
}
Deck :: Deck() {
    reset();
}

void Deck :: shuffle(int n) {
    if (next != 0 ) next = 0;
    Card new_deck[DeckSize];
    int cnt=0, l1 = 0, r1 = n-1;
    int l2 = n, r2 =DeckSize-1;
    while (l1<=r1 && l2<=r2) {
        new_deck[cnt++] = deck[l2++]; 
        new_deck[cnt++] = deck[l1++]; 
    } 
    while (l1<=r1)  new_deck[cnt++] = deck[l1++]; 
    while (l2<=r2)  new_deck[cnt++] = deck[l2++];
    for (int i=0;i<DeckSize;i++)
        deck[i] = new_deck[i];
}

Card Deck :: deal() {
    DeckEmpty deckempty;
    if (next >= DeckSize) throw deckempty;
    next++;
    return deck[next-1];
}

int Deck :: cardsLeft() {
    return DeckSize - next;
}