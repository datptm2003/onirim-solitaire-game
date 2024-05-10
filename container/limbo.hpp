#ifndef _LIMBO_H_
#define _LIMBO_H_

#include <list>
#include <vector>
#include <algorithm>
#include "components/card.hpp"

class Limbo {
private:
    std::list<Card> cardList;
    int size;

public:
    Limbo() {
        this->size = 0;

    }

    bool isEmpty() {
        return cardList.empty();
    }
    int sizeOf() {
        return size;
    }
    void pushCard(Card card) {
        cardList.push_back(card);
        ++size;
        //card.setStatus(Card::IN_LIMBO);
    }
    Card getCard() {
        Card card = cardList.front();
        cardList.pop_front();
        --size;
        return card;
    }
    
};

#endif