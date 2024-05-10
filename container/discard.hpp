#ifndef _DISCARD_H_
#define _DISCARD_H_

#include <list>
#include <vector>
#include <algorithm>
#include "components/card.hpp"

class Discard {
private:
    std::list<Card> cardList;
    int size;

public:
    int redCards[4];
    int blueCards[4];
    int greenCards[4];
    int brownCards[4];

public:
    Discard() {
        this->size = 0;
        for (int i = 0; i < 4; ++i) {
            redCards[i] = 0;
            blueCards[i] = 0;
            greenCards[i] = 0;
            brownCards[i] = 0;
        }
    }

    bool isEmpty() {
        return cardList.empty();
    }
    int sizeOf() {
        return size;
    }
    int getCardNumber(Card::Color color, Card::Symbol symbol) {
        switch (color) {
            case Card::RED:
                return redCards[symbol];
            case Card::BLUE:
                return blueCards[symbol];
            case Card::GREEN:
                return greenCards[symbol];
            case Card::BROWN:
                return brownCards[symbol];
            default:
                return -1;
        }
    }
    void pushCard(Card card) {
        cardList.push_front(card);
        ++size;
        switch (card.getColor()) {
            case Card::RED:
                ++redCards[card.getSymbol()];
                break;
            case Card::BLUE:
                ++blueCards[card.getSymbol()];
                break;
            case Card::GREEN:
                ++greenCards[card.getSymbol()];
                break;
            case Card::BROWN:
                ++brownCards[card.getSymbol()];
                break;
        }
    }

    
};

#endif