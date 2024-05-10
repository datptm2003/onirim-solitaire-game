#ifndef _DECK_H_
#define _DECK_H_

#include <list>
#include <vector>
#include <algorithm>
#include <iterator>
#include <random>
#include <chrono>
#include "components/card.hpp"

class Deck {
private:
    std::list<Card> cardList;
    int size;
    
    
public:
    Deck() {
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
    }

    void reshuffle() {
        std::vector<Card> buf;
        if (cardList.empty()) return;
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        while(!cardList.empty()) {
            buf.push_back(cardList.front());
            cardList.pop_front();
        }
        std::shuffle(buf.begin(), buf.end(), std::default_random_engine(seed));
        while(!buf.empty()) {
            cardList.push_back(buf.front());
            buf.erase(buf.begin(),buf.begin() + 1);
        }
    }
    Card getTopCard() {
        Card card = cardList.front();
        cardList.pop_front();
        --size;
        return card;
    }
    std::list<Card> getTopMultipleCards(int numOfCards) {
        std::list<Card> listCards;
        int n = 0;
        while (!cardList.empty() && n < numOfCards) {
            listCards.push_back(cardList.front());
            cardList.pop_front();
            ++n;
            --size;
        }
        return listCards;
    }
    void pushTopMultipleCards(std::list<Card> cards) {
        while (!cards.empty()) {
            cardList.push_front(cards.back());
            cards.pop_back();
            ++size;
        }
    }
    void pushBackMultipleCards(std::list<Card> cards) {
        while (!cards.empty()) {
            cardList.push_back(cards.front());
            cards.pop_front();
            ++size;
        }
    }
    void getDoor(Card::Color color) {
        std::list<Card>::iterator it = cardList.begin();
        while (it != cardList.end()) {
            if (it->getSymbol() == Card::DOOR && it->getColor() == color) {
                it = cardList.erase(it);
                --size;
                break;
            } else {
                it++;
            }
        }
        reshuffle();
    }
};

#endif