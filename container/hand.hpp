#ifndef _HAND_H_
#define _HAND_H_

#include <list>
#include <vector>
#include <algorithm>
#include "components/card.hpp"

class Hand {
private:
    std::vector<Card> cardList;
    int size;

public:
    Hand() {
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
    std::vector<Card> getWholeHand() {
        return this->cardList;
    }
    
    Card getCard(int index) {
        return cardList[index];
    }
    bool isKey(int index) {
        return (cardList.at(index).getSymbol() == Card::KEY);
    }
    bool isGlyph(int index) {
        return (cardList.at(index).getSymbol() == Card::GLYPH);
    }
    bool isKeyWithColor(int index, Card::Color color) {
        return (cardList.at(index).getSymbol() == Card::KEY && cardList.at(index).getColor() == color);
    }
    void removeCard(int index) {
        cardList.erase(cardList.begin() + index, cardList.begin() + index + 1);
        --size;
    }
    bool hasKey(Card::Color color) {
        if (color == Card::NONE) {
            for (Card card : cardList) {
                if (card.getSymbol() == Card::KEY) return true;
            }
            return false;
        } else {
            for (Card card : cardList) {
                if (card.getSymbol() == Card::KEY && card.getColor() == color) return true;
            }
            return false;
        }
        
    }
    bool hasValidCardToLabyrinth(Card labCard) {
        for (Card card : cardList) {
            if (card.getSymbol() != labCard.getSymbol()) return true;
        }
        return false;
    }
};

#endif