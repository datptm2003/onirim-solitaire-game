#ifndef __CARD_H__
#define __CARD_H__

#include <iostream>

class Card {
public:
    enum Color {
        RED,
        BLUE,
        GREEN,
        BROWN,
        NONE
    };
    enum Symbol {
        SUN, MOON, GLYPH, KEY,
        DOOR,
        NIGHTMARE
    };
private:
    Color color;
    Symbol symbol;
public:
    Card(Color color, Symbol symbol) {
        this->color = color;
        this->symbol = symbol;
    }

    Color getColor() {
        return color;
    }
    void setColor(Color color) {
        this->color = color;
    }
    Symbol getSymbol() {
        return symbol;
    }
    void setSymbol(Symbol symbol) {
        this->symbol = symbol;
    }
};

#endif