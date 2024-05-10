#ifndef _LABYRINTH_H_
#define _LABYRINTH_H_

#include <list>
#include <vector>
#include <algorithm>
#include "components/card.hpp"

class Labyrinth {
private:
    std::list<Card> cardList;
    int size;
    int lastRow;

public:
    Labyrinth() {
        this->size = 0;
        this->lastRow = 0;
    }

    bool isEmpty() {
        return cardList.empty();
    }
    int sizeOf() {
        return size;
    }
    void pushCard(Card card) {
        cardList.push_front(card);
        ++size;
    }

    Card getTopCard() {
        return cardList.front();
    }
    bool isValid(Card card) {
        if (cardList.empty()) return true;
        return cardList.front().getSymbol() != card.getSymbol();

    }
    bool isVaidToDiscoverDoor() {
        if (size < 3) return false;
        else {
            Card card_1 = cardList.front();
            cardList.pop_front();
            Card card_2 = cardList.front();
            cardList.pop_front();
            Card card_3 = cardList.front();
            cardList.pop_front();
            bool isNotRowFour = true;
            if (!cardList.empty()) isNotRowFour = (this->size - lastRow >= 3 || cardList.front().getColor() != card_3.getColor());
            cardList.push_front(card_3);
            cardList.push_front(card_2);
            cardList.push_front(card_1);
            if (
                isNotRowFour &&
                card_1.getColor() == card_2.getColor() && 
                card_2.getColor() == card_3.getColor() &&
                card_1.getSymbol() != card_2.getSymbol() &&
                card_2.getSymbol() != card_3.getSymbol()
            ) {
                lastRow = this->size;
                return true;
            } else return false;
        }
    }
};

#endif