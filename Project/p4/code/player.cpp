#include<iostream>
#include<iomanip>
#include<string>
#include<cstdlib>
#include<cassert>

#include "hand.h"
#include "card.h"
#include "player.h"

class Simple_Player : public Player {
    private:
        int count = 0;
    public:
        int bet(unsigned int bankroll, unsigned int minimum) {
            return minimum;
        }
        bool draw(Card dealer, const Hand &player) {
            int player_val = player.handValue().count;
            int show_c = dealer.spot;
            if (!player.handValue().soft) {
                if (player_val <= 11) 
                    return true;
                else if (player_val == 12)
                    return !(show_c == FOUR || show_c == FIVE || show_c == SIX);
                else if (player_val >= 13 && player_val <=16)
                    return !(show_c >= TWO && show_c <= SIX);
                else return false;
            }
            if (player_val <= 17) 
                return true;
            else if (player_val == 18) 
                return !(show_c == TWO || show_c == SEVEN || show_c == EIGHT);
            else return false;
        }
        void expose(Card c) {}
        void shuffled() {}
}sPlayer;

class Counting_Player : public Simple_Player {
    private:
        int count;
    public:
        int bet(unsigned int bankroll, unsigned int minimum) override{
            if (bankroll >= minimum*2 && count>=2) 
                return minimum*2;
            else   
                return minimum;
        }
        void expose(Card c) override {
            if (c.spot >= TEN && c.spot <= ACE) 
                count--;
            if (c.spot >= TWO && c.spot <= SIX)
                count++;

            //std::cout << "Count after expose: " << count << std::endl;
        }
        void shuffled() override {
            count = 0;
        }
}cPlayer;

extern Player *get_Simple() {
    return &sPlayer;
}

extern Player *get_Counting() {
    return &cPlayer;
}

