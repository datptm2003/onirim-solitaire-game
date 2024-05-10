#ifndef _ACTION_H_
#define _ACTION_H_

#include "container/deck.hpp"
#include "container/labyrinth.hpp"
#include "container/limbo.hpp"
#include "container/discard.hpp"
#include "container/hand.hpp"

class Action {
private:
    int nightmareCards;
    int totalCards;
public:
    Deck deck;
    Labyrinth labyrinth;
    Limbo limbo;
    Discard discard;
    Hand hand;
    int doors[4];
    
public:
    Action() {
        nightmareCards = 10;
        totalCards = 88;
        for (int i = 0; i < 4; ++i) doors[i] = 0;
    }

    int getNightmareCards() {
        return nightmareCards;
    }
    int getTotalCards() {
        return totalCards;
    }
    void decNightmareCards(int amount) {
        this->nightmareCards -= amount;
    }
    void decTotalCards(int amount) {
        this->totalCards -= amount;
    }
    void incTotalCards(int amount) {
        this->totalCards += amount;
    }
    void setTotalCards(int totalCards) {
        this->totalCards = totalCards;
    }
    void generateDeck() {
        int sunCards = 9;
        for (Card::Color color : {Card::RED, Card::BLUE, Card::GREEN, Card::BROWN}) {
            for (Card::Symbol symbol : {Card::SUN, Card::MOON, Card::GLYPH, Card::KEY, Card::DOOR}) {
                if (symbol == Card::SUN) {
                    for (int i = 0; i < sunCards; ++i) {
                        Card card = Card(color,symbol);
                        deck.pushCard(card);
                    }
                }
                if (symbol == Card::MOON) {
                    for (int i = 0; i < 4; ++i) {
                        Card card = Card(color,symbol);
                        deck.pushCard(card);
                    }
                }
                if (symbol == Card::GLYPH) {
                    for (int i = 0; i < 2; ++i) {
                        Card card = Card(color,symbol);
                        deck.pushCard(card);
                    }
                }
                if (symbol == Card::KEY) {
                    for (int i = 0; i < 3; ++i) {
                        Card card = Card(color,symbol);
                        deck.pushCard(card);
                    }
                }
                if (symbol == Card::DOOR) {
                    for (int i = 0; i < 3; ++i) {
                        Card card = Card(color,symbol);
                        deck.pushCard(card);
                    }
                }
            }
            --sunCards;
        }
        for (int i = 0; i < 10; ++i) {
            Card card = Card(Card::NONE,Card::NIGHTMARE);
            deck.pushCard(card);
        }
        deck.reshuffle();
    }
    int playCard(int index) {
        if (!labyrinth.isValid(hand.getCard(index))) return -1;
        else {
            Card::Color color = hand.getCard(index).getColor();
            labyrinth.pushCard(hand.getCard(index));
            hand.removeCard(index);
            if (!labyrinth.isVaidToDiscoverDoor()) return 0;
            else {
                ++doors[color];
                deck.getDoor(color);
                return 1;
            }
        } 
    }
    int discardCard(int index) {
        if (hand.getCard(index).getSymbol() == Card::DOOR) return -1;
        else {
            Card card = hand.getCard(index);
            discard.pushCard(card);
            hand.removeCard(index);
            if (card.getSymbol() == Card::GLYPH) return 1;
            else if (card.getSymbol() == Card::KEY) return 2;
            else return 0;
        } 
        

    }
    void triggerProphecy(std::list<Card> topFiveCards, std::vector<int> arr) {

        std::vector<Card> buf;
        while(!topFiveCards.empty()) {
            buf.push_back(topFiveCards.front());
            topFiveCards.pop_front();
        }
        for (int i : arr) {
            topFiveCards.push_back(buf.at(i));
        }
        deck.pushTopMultipleCards(topFiveCards);
        totalCards = totalCards + topFiveCards.size();

    }
    void triggerIncantation(std::list<Card> topFiveCards, std::vector<int> arr) {
        //std::list<Card> topFiveCards = deck.getTopMultipleCards(5);
        std::vector<Card> buf;
        while(!topFiveCards.empty()) {
            buf.push_back(topFiveCards.front());
            topFiveCards.pop_front();
        }
        for (int i : arr) {
            topFiveCards.push_back(buf.at(i));
            //buf.erase(buf.begin() + i, buf.begin() + i + 1);
        }
        deck.pushBackMultipleCards(topFiveCards);
        totalCards = totalCards + topFiveCards.size();

    }

};

#endif