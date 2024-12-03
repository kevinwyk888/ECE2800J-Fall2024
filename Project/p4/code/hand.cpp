#include<iostream>
#include<iomanip>
#include<string>
#include<cstdlib>
#include<cassert>

#include "hand.h"
#include "card.h"

void Hand :: discardAll() {
    curValue.count = 0;
    curValue.soft = false;
}
Hand:: Hand() {
    discardAll();
}

void Hand:: addCard(Card c){
    if (c.spot <= NINE) curValue.count+=(c.spot+2);
    else if (c.spot == ACE) {
        if (curValue.count + 11 <= 21 ) {
            curValue.soft = true;
            curValue.count+=11;
        } 
        else 
            curValue.count+=1;
    }
    else curValue.count+=10;
    if (curValue.count>21 && curValue.soft) {
        curValue.count-=10;
        curValue.soft=false;
    }
}
HandValue Hand:: handValue() const{
    return curValue;
}
