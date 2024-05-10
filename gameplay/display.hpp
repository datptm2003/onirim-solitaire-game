#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#define ONE_SECOND 1000
#define MAX_WIDTH 120
#define MAX_HEIGHT 625

#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include "container/deck.hpp"
#include "container/labyrinth.hpp"
#include "container/limbo.hpp"
#include "container/discard.hpp"
#include "gameplay/action.hpp"

class Display {
private:
    class Point {
    private:
        short x;
        short y;
    public: 
        Point() {
            this->x = this->y = 0;
        }
        Point(int x, int y) {
            this->x = x;
            this->y = y;
        }
        short getX() {
            return this->x;
        }
        short getY() {
            return this->y;
        }
        void setX(short x) {
            this->x = x;
        }
        void setY(short y) {
            this->y = y;
        }
    };
    class Area {
    private:
        short height;
        short width;
        Point leftUpperCorner;
    public:
        Area() {
            this->height = this->width = 0;
        }
        Area(int height, int width, Point leftUpperCorner) {
            this->height = height;
            this->width = width;
            this->leftUpperCorner.setX(leftUpperCorner.getX());
            this->leftUpperCorner.setY(leftUpperCorner.getY());
        }
        short getHeight() {
            return this->height;
        }
        short getWidth() {
            return this->width;
        }
        void setHeight(short height) {
            this->height = width;
        }
        void setWidth(short width) {
            this->width = width;
        }
        short getLeftUpperCornerX() {
            return this->leftUpperCorner.getX();
        }
        void setLeftUpperCornerX(short x) {
            this->leftUpperCorner.setX(x);
        }
        short getLeftUpperCornerY() {
            return this->leftUpperCorner.getY();
        }
        void setLeftUpperCornerY(short y) {
            this->leftUpperCorner.setY(y);
        }
    };
private:
    HANDLE hConsole;
    int lastLimboCard;
    int lastLabyrinthCard;
    bool endGame;

    Action act;
    Area infoArea;
    Area handArea;
    Area labyrinthArea;
    Area commandArea;
    Area top5CardsArea;
    Area discardArea;
    Area topCardArea;
    Area limboArea;
    Area noteArea;
private:
    void gotoxy(short x, short y) {
        COORD c = { x, y };  
        SetConsoleCursorPosition(this->hConsole,c);
    }
    void printTextWithColor(std::string text, std::string color) {
        int c = 0;
        if (color == "RED") c = 4;
        else if (color == "BLUE") c = 3;
        else if (color == "GREEN") c = 2;
        else if (color == "BROWN") c = 6;
        else if (color == "GRAY") c = 8;
        else c = 7; 
        SetConsoleTextAttribute(hConsole, c);
        std::cout << text;
        SetConsoleTextAttribute(hConsole, 7);
    }
    void printTextWithColor(int text, std::string color) {
        int c = 0;
        if (color == "RED") c = 4;
        else if (color == "BLUE") c = 3;
        else if (color == "GREEN") c = 2;
        else if (color == "BROWN") c = 6;
        else if (color == "GRAY" || color == "NIGHTMARE") c = 8;
        else c = 7; 
        SetConsoleTextAttribute(hConsole, c);
        std::cout << text;
        SetConsoleTextAttribute(hConsole, 7);
    }  
    void drawArea(Area area) {
        for (short i = 0; i < area.getHeight(); ++i) {
            if (i == 0 || i == area.getHeight()-1) {
                for (short j = 0; j < area.getWidth(); ++j) {
                    gotoxy(j + area.getLeftUpperCornerX() - 1, i + area.getLeftUpperCornerY() - 1);
                    std::cout << "+";
                }
            } else {
                gotoxy(area.getLeftUpperCornerX() - 1, i + area.getLeftUpperCornerY() - 1);
                std::cout << "+";
                gotoxy(area.getWidth() + area.getLeftUpperCornerX() - 2, i + area.getLeftUpperCornerY() - 1);
                std::cout << "+";
            }
        }
    }
    void clearWholeArea(Area area) {
        for (short i = 0; i < area.getHeight(); ++i) {
            for (short j = 0; j < area.getWidth(); ++j) {
                gotoxy(j + area.getLeftUpperCornerX() - 1, i + area.getLeftUpperCornerY() - 1);
                std::cout << " ";
            }
        }
    }
    void clearWholeArea(short x, short y) {
        for (short i = 0; i < y; ++i) {
            for (short j = 0; j < x; ++j) {
                gotoxy(j, i);
                std::cout << " ";
            }
        }
    }
    void clearInnerArea(Area area) {
        for (short i = 1; i < area.getHeight() - 1; ++i) {
            for (short j = 1; j < area.getWidth() - 1; ++j) {
                gotoxy(j + area.getLeftUpperCornerX() - 1, i + area.getLeftUpperCornerY() - 1);
                std::cout << " ";
            }
        }
    }
    void clearLine(Point point, int length) {
        for (short i = 0; i < length; ++i) {
            gotoxy(point.getX() + i - 1, point.getY() - 1);
            std::cout << " ";
        }
    }
    void generateFrame() {
        drawArea(infoArea);
        drawArea(labyrinthArea);
        drawArea(handArea);
        drawArea(commandArea);
        drawArea(top5CardsArea);
        drawArea(topCardArea);
        drawArea(discardArea);
        drawArea(limboArea);
        drawArea(noteArea);

        gotoxy(infoArea.getLeftUpperCornerX() + 1, infoArea.getLeftUpperCornerY() + 1);
        std::cout << "NIGHTMARE: ";
        gotoxy(infoArea.getLeftUpperCornerX() + 12, infoArea.getLeftUpperCornerY() + 1);
        printTextWithColor(act.getNightmareCards(),"GRAY");

        gotoxy(infoArea.getLeftUpperCornerX() + 21, infoArea.getLeftUpperCornerY() + 1);
        std::cout << "DOOR: ";
        gotoxy(infoArea.getLeftUpperCornerX() + 27, infoArea.getLeftUpperCornerY() + 1);
        printTextWithColor(act.doors[0],"RED");
        gotoxy(infoArea.getLeftUpperCornerX() + 29, infoArea.getLeftUpperCornerY() + 1);
        printTextWithColor(act.doors[1],"BLUE");
        gotoxy(infoArea.getLeftUpperCornerX() + 31, infoArea.getLeftUpperCornerY() + 1);
        printTextWithColor(act.doors[2],"GREEN");
        gotoxy(infoArea.getLeftUpperCornerX() + 33, infoArea.getLeftUpperCornerY() + 1);
        printTextWithColor(act.doors[3],"BROWN");

        gotoxy(top5CardsArea.getLeftUpperCornerX() + 1, top5CardsArea.getLeftUpperCornerY() + 1);
        std::cout << act.getTotalCards();

        int position[4] = {0,4,10,16};
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                gotoxy(discardArea.getLeftUpperCornerX() + 2 + position[j], discardArea.getLeftUpperCornerY() + 1 + 3*i);
                printTextWithColor(symbolString((Card::Symbol) j), colorString((Card::Color) i));
                gotoxy(discardArea.getLeftUpperCornerX() + 2 + position[j], discardArea.getLeftUpperCornerY() + 2 + 3*i);
                printTextWithColor(0, colorString((Card::Color) i));
            }
        }
        
        gotoxy(noteArea.getLeftUpperCornerX() + 2, noteArea.getLeftUpperCornerY() + 1);
        printTextWithColor("1: Discard a key in your hand","GRAY");
        gotoxy(noteArea.getLeftUpperCornerX() + 2, noteArea.getLeftUpperCornerY() + 2);
        printTextWithColor("2: Discard your whole hand","GRAY");
        gotoxy(noteArea.getLeftUpperCornerX() + 2, noteArea.getLeftUpperCornerY() + 3);
        printTextWithColor("3: Discard 5 cards on top of deck","GRAY");
        gotoxy(noteArea.getLeftUpperCornerX() + 2, noteArea.getLeftUpperCornerY() + 4);
        printTextWithColor("4: Send a discovered door to limbo","GRAY");
    }
    void showCommand(std::string str) {
        clearInnerArea(commandArea);
        gotoxy(commandArea.getLeftUpperCornerX() + 1, commandArea.getLeftUpperCornerY() + 1);
        std::cout << str;
        gotoxy(commandArea.getLeftUpperCornerX() + 1, commandArea.getLeftUpperCornerY() + 2);
        std::cout << "Your option: ";

    }
    void showPrompt(std::string str, int sec) {
        clearInnerArea(commandArea);
        gotoxy(commandArea.getLeftUpperCornerX() + 1, commandArea.getLeftUpperCornerY() + 1);
        std::cout << str;
        Sleep(sec * ONE_SECOND);
    }
    void showHand(int sec) {
        clearInnerArea(handArea);
        std::vector<Card> listCards = act.hand.getWholeHand();
        for (int i = 0; i < listCards.size(); ++i) {
            gotoxy(handArea.getLeftUpperCornerX() + 1 + 7*i, handArea.getLeftUpperCornerY() + 1);
            printTextWithColor(symbolString(listCards[i].getSymbol()),colorString(listCards[i].getColor()));
            Sleep(sec * ONE_SECOND);
        }
    }
    void showTopFiveCards(std::list<Card> topFiveCards, int sec) {
        clearInnerArea(top5CardsArea);
        gotoxy(top5CardsArea.getLeftUpperCornerX() + 1, top5CardsArea.getLeftUpperCornerY() + 1);
        std::cout << act.getTotalCards();
        std::list<Card>::iterator it = topFiveCards.begin();
        for (int i = 0; it != topFiveCards.end(); ++it, ++i) {
            gotoxy(top5CardsArea.getLeftUpperCornerX() + 5 + 6*i, top5CardsArea.getLeftUpperCornerY() + 1);
            if (it->getSymbol() == Card::NIGHTMARE) printTextWithColor("N.M",colorString(it->getColor()));
            else printTextWithColor(symbolString(it->getSymbol()),colorString(it->getColor()));
            if (act.getTotalCards() > act.deck.sizeOf()) act.decTotalCards(1);
            clearLine(Point(11,16),2);
            gotoxy(top5CardsArea.getLeftUpperCornerX() + 1, top5CardsArea.getLeftUpperCornerY() + 1);
            std::cout << act.getTotalCards();
            Sleep(sec * ONE_SECOND);
        }
        act.setTotalCards(act.deck.sizeOf());
    }
    void showTopCard(Card card, int sec) {
        clearInnerArea(topCardArea);
        gotoxy(topCardArea.getLeftUpperCornerX() + 1, topCardArea.getLeftUpperCornerY() + 1);
        printTextWithColor(symbolString(card.getSymbol()),colorString(card.getColor()));
        updateTotalCards();
        Sleep(sec * ONE_SECOND);
    }
    void showLimbo(Card card, int sec) {
        gotoxy(limboArea.getLeftUpperCornerX() + 1, limboArea.getLeftUpperCornerY() + 1 + lastLimboCard);
        printTextWithColor(symbolString(card.getSymbol()),colorString(card.getColor()));
        //std::cout << lastLimboCard;
        Sleep(sec * ONE_SECOND);
    }
    void showLabyrinth(Card card) {
        gotoxy(labyrinthArea.getLeftUpperCornerX() + 1, labyrinthArea.getLeftUpperCornerY() + 1 + lastLabyrinthCard);
        printTextWithColor(symbolString(card.getSymbol()),colorString(card.getColor()));
        //std::cout << lastLimboCard;
    }
    void showDiscard(Card card) {
        int position[4] = {0,4,10,16};
        gotoxy(discardArea.getLeftUpperCornerX() + 2 + position[(int) card.getSymbol()], discardArea.getLeftUpperCornerY() + 2 + 3*((int) card.getColor()));
        printTextWithColor(act.discard.getCardNumber(card.getColor(),card.getSymbol()), colorString(card.getColor()));
    }
    void logInstruction() {
        std::ofstream f_rule (".\\oririm_game_rules.txt");

        f_rule  << "-----------------INSTRUCTION-----------------\n"
                << "\nYou are a Dreamwalker, lost in a mysterious Labyrinth.\n"
                << "Your goal is to find all the twelve Oneiric doors to escape!\n"
                << "There are 3 ways you can follow to discover a door, which will be mentioned in section 4, 6 and 8.\n"

                << "\n1. COMPONENTS:\n"
                << "\n    - Location cards (66 cards):\n"
                << "    These are the cards you will have in your hand. Play and discard them skillfully in order to obtain the Door cards.\n"
                << "\n    - Door cards (12 cards):\n"
                << "    The 12 oneiric Doors are the object of your quest: opening all 12 Doors is the victory condition of the game.\n"
                << "\n    - Dream cards (10 cards):\n"
                << "    Nightmare cards are the only type of Dream card in this expansion. \n"
                << "    They are also shuffled within the deck of cards, and will force you to choose one penalty once you draw such a card.\n"
                
                << "\n2. DECK CONTENT:\n"
                << "\n    Red location:   9 Sun, 4 Moon, 2 Glyph, 3 Key\n"
                << "    Blue location:  8 Sun, 4 Moon, 2 Glyph, 3 Key\n"
                << "    Green location: 7 Sun, 4 Moon, 2 Glyph, 3 Key\n"
                << "    Brown location: 6 Sun, 4 Moon, 2 Glyph, 3 Key\n"
                << "    Door:           2 Red, 2 Blue, 2 Green, 2 Brown\n"
                << "    Dream:          10 Nightmare\n"

                << "\n3. THE LABYRINTH:\n"
                << "\n    The labyrith is yours to build. Everytime you play a card, this card is placed at the end of the Labyrinth.\n"
                << "    There is one golden rule: the card played may not have any symbol (Sun, Moon, Glyph and Key) in common with the last card played.\n"
                << "    In this version, the Labyrinth area is located on the leftmost side of the window screen.\n"

                << "\n4. DISCOVERING DOORS:\n"
                << "\n    If the card just played is the third in a row of the same color, you obtain a Door card of that color.\n"
                << "    This Door card is taken from the deck and the deck will be reshuffled right after.\n"
                << "    If a card is the fourth in a row of the same color, it counts as the first card of a new series of the same color.\n"

                << "\n5. GAME TURN:\n"
                << "\n    Once you have five cards in hand, you got two options: Either you play a card on the Labyrinth or you discard a card.\n"
                << "    If you discard a Glyph or a Key card, you will trigger a special event, which will be mentioned in section 7 and 8.\n"

                << "\n6. CARD DRAWING:\n"
                << "\n    After you made an action, a card will automatically be drawn from the deck to your hand. There are 3 possible cases:\n"
                << "        - Location cards will be placed in your hand.\n"
                << "        - Dream cards will trigger a bad event that you will need to resolve immediately (section 9).\n"
                << "        - Door cards will be sent to the Limbo right away unless you have a key of the same color in your hand.\n"
                << "    If you are in third case, you have choice to discover the Door immediately by discarding that key.\n"

                << "\n7. PROPHECY:\n"
                << "\n    If you discard a location card with Key symbol on it, you trigger a Prophecy.\n"
                << "    During a prophecy, you will:\n"
                << "        - Look at the top five cards of the deck,\n"
                << "        - Discard one of them,\n"
                << "        - And place the 4 remaining cards back on top of the deck in which order you choose.\n"
                << "    If there are less than 5 cards remaining in the deck, all those cards will be revealed and you still need to do the same thing as above.\n"
                << "    BE CAREFUL: If all drawn cards are Doors, since it is mandatory that you discard a card, you will automatically lose the game.\n"

                << "\n8. INCANTATION:\n"
                << "\n    If you discard a location card with Glyph symbol on it, you trigger an Incantation.\n"
                << "    During an incantation, you will:\n"
                << "        - Look at the top five cards of the deck,\n"
                << "        - Discover one of the doors among them (if any),\n"
                << "        - And place the 4 or 5 remaining cards back on bottom of the deck in which order you choose.\n"
                << "    If there are less than 5 cards remaining in the deck, all those cards will be revealed and you still need to do the same thing as above.\n"
                << "    The color of the Door card and the color of the discarded Glyph card do not need to be the same.\n"
        
                << "\n9. NIGHTMARES:\n"
                << "\n    When you draw a nightmare card, you have to choose one of the following four options:\n"
                << "        - Discard a Key card from you hand.\n"
                << "        - Discard your whole hand and draw five new Location cards from the deck. Door and Dream cards are placed into the Limbo.\n"
                << "        - Reveal the top five cards from the deck and discard all of them, except Door and Dream cards, which are placed into the Limbo.\n"
                << "        - Send one of your discovered Door cards to the Limbo.\n"

                << "\n10. THE LIMBO:\n"
                << "\n    The Limbo is a temporary space for cards that are going to be reshuffled in the deck at the end of the turn.\n"
                << "    In this version, the Limbo area is located on the bottom right corner of the window screen.\n"

                << "\n11. DECK RESHUFFLING:\n"
                << "\n    The deck is reshuffled when you discover a Door by placing three cards of the same color in a row on the Labyrinth\n"
                << "    OR when your hand is full of Location cards while there are cards in the Limbo.\n"

                << "\n12. END GAME:\n"
                << "\n    - Victory: You win if, at any point, all 12 Door cards have been discovered.\n"
                << "    - Defeat: You lose if you must draw a card to fill your hand and there is no card left in the deck.\n";

        f_rule.close();
    }
    void updateDoors() {
        gotoxy(infoArea.getLeftUpperCornerX() + 27, infoArea.getLeftUpperCornerY() + 1);
        printTextWithColor(act.doors[0],"RED");
        gotoxy(infoArea.getLeftUpperCornerX() + 29, infoArea.getLeftUpperCornerY() + 1);
        printTextWithColor(act.doors[1],"BLUE");
        gotoxy(infoArea.getLeftUpperCornerX() + 31, infoArea.getLeftUpperCornerY() + 1);
        printTextWithColor(act.doors[2],"GREEN");
        gotoxy(infoArea.getLeftUpperCornerX() + 33, infoArea.getLeftUpperCornerY() + 1);
        printTextWithColor(act.doors[3],"BROWN");
    }
    void updateNightmare() {
        clearLine(Point(22,3),2);
        gotoxy(infoArea.getLeftUpperCornerX() + 12, infoArea.getLeftUpperCornerY() + 1);
        printTextWithColor(act.getNightmareCards(),"GRAY");
    }
    void updateTotalCards() {
        clearLine(Point(11,16),2);
        gotoxy(top5CardsArea.getLeftUpperCornerX() + 1, top5CardsArea.getLeftUpperCornerY() + 1);
        std::cout << act.deck.sizeOf();
    }
    std::string symbolString(Card::Symbol symbol) {
        switch (symbol) {
            case Card::SUN:
                return "SUN";
                break;
            case Card::MOON:
                return "MOON";
                break;
            case Card::GLYPH:
                return "GLYPH";
                break;
            case Card::KEY:
                return "KEY";
                break;
            case Card::DOOR:
                return "DOOR";
                break;
            case Card::NIGHTMARE:
                return "NIGHTMARE";
                break;
            default:
                return " ";
        }
    }
    std::string colorString(Card::Color color) {
        switch (color) {
            case Card::RED:
                return "RED";
                break;
            case Card::BLUE:
                return "BLUE";
                break;
            case Card::GREEN:
                return "GREEN";
                break;
            case Card::BROWN:
                return "BROWN";
                break;
            case Card::NONE:
                return "GRAY";
            default:
                return " ";
        }
    }
    void playTurn() {
        act.setTotalCards(act.deck.sizeOf());
        int op = 0;
        while (true) {
            showCommand("PLAY or DISCARD a card (1/2)?");
            std::cin >> op;
            if (op == 1) {
                if (!act.labyrinth.isEmpty() && !act.hand.hasValidCardToLabyrinth(act.labyrinth.getTopCard())) {
                    showPrompt("ERROR: No valid card to play!",2);
                    continue;
                }
                int index = 0;
                while (true) {
                    showCommand("Choose a card from hand (1->5)");
                    std::cin >> index;
                    if (index >= 1 && index <= 5) {
                        int res = act.playCard(index-1);
                        if (res == -1) {
                            showPrompt("ERROR: Invalid card sequence!",2);
                            continue;
                        } else if (res == 1) {
                            showLabyrinth(act.labyrinth.getTopCard());
                            ++lastLabyrinthCard;
                            updateDoors();
                            showHand(0);
                            showPrompt("You have discovered a DOOR!",2);
                            if (!endGame && act.doors[0] == 3 && act.doors[1] == 3 && act.doors[2] == 3 && act.doors[3] == 3) {
                                winGame();
                                Sleep(ONE_SECOND);
                                return;
                            }
                            break;
                        } else {
                            showLabyrinth(act.labyrinth.getTopCard());
                            ++lastLabyrinthCard;
                            showHand(0);
                            break;
                        }
                        
                    } else {
                        showPrompt("ERROR: Index out of range!",2);
                    }
                }
            } else if (op == 2) {
                int index = 0;
                while (true) {
                    showCommand("Choose a card from hand (1->5)");
                    std::cin >> index;
                    if (index >= 1 && index <= 5) {
                        Card card = act.hand.getCard(index-1);
                        int res = act.discardCard(index-1);
                        if (res == -1) {
                            showPrompt("ERROR: Cannot discard doors!",2);
                            continue;
                        } else if (res == 1) {
                            showHand(0);
                            showDiscard(card);
                            triggerIncantationCommand();
                            break;
                        } else if (res == 2) {
                            showHand(0);
                            showDiscard(card);
                            triggerProphecyCommand();
                            break;
                        } else {
                            showHand(0);
                            showDiscard(card);
                            break;
                        }
                        
                    } else {
                        showPrompt("ERROR: Index out of range!",2);
                        continue;
                    }
                }

            } else {
                showPrompt("ERROR: Invalid option!",2);
                continue;
            }
            break;
        }
        while (!endGame && act.hand.sizeOf() < 5) drawCard();
    }
    void triggerProphecyCommand() {
        showPrompt("You have triggered PROPHECY!",2);
        std::list<Card> topFiveCards = act.deck.getTopMultipleCards(5);
        
        bool allDoors = true;
        for (std::list<Card>::iterator it = topFiveCards.begin(); it != topFiveCards.end(); ++it) {
            if (it->getSymbol() != Card::DOOR) {
                allDoors = false;
            }
        }
        if (allDoors) {
            loseGame();
            return;
        }

        showTopFiveCards(topFiveCards,1);

        int index = 0;
        while (true) {
            showCommand("Choose a card to discard (1->" + std::to_string(topFiveCards.size()) + ")");
            std::cin >> index;
            if (index >= 1 && index <= topFiveCards.size()) {
                std::list<Card>::iterator it = topFiveCards.begin();
                for (int i = 0; it != topFiveCards.end(); ++it, ++i) {
                    if (i == index - 1) break;
                }
                if (it->getSymbol() == Card::DOOR) {
                    showPrompt("ERROR: Cannot discard doors!",2);
                    continue;
                }
                
                if (it->getSymbol() == Card::NIGHTMARE) {
                    act.decNightmareCards(1);
                    updateNightmare();
                }
                else {
                    act.discard.pushCard(*it);
                    showDiscard(*it);
                }
                topFiveCards.erase(it);

                showTopFiveCards(topFiveCards,0);
                std::vector<int> arr;
                bool outOfRange = false;
                while (true) {
                    arr.clear();
                    outOfRange = false;
                    showCommand("Rearrange cards (ex: 1 3 4 2)");
                    for (int i = 0; i < topFiveCards.size(); ++i) {
                        int n = 0;
                        std::cin >> n;
                        if (n < 1 || n > topFiveCards.size()) {
                            showPrompt("ERROR: Index out of range!",2);
                            outOfRange = true;
                            break;
                        }
                        arr.push_back(n-1);
                    }
                    if (outOfRange) continue;
                    else break;
                }
                
                act.triggerProphecy(topFiveCards,arr);
                break;
            } else {
                showPrompt("ERROR: Index out of range!",2);
                continue;
            }
        }
        clearInnerArea(top5CardsArea);
        updateTotalCards();
        
    }
    void triggerIncantationCommand() {
        showPrompt("You have triggered INCANTATION!",2);
        std::list<Card> topFiveCards = act.deck.getTopMultipleCards(5);

        bool hasDoors = false;
        for (std::list<Card>::iterator it = topFiveCards.begin(); it != topFiveCards.end(); ++it) {
            if (it->getSymbol() == Card::DOOR) {
                hasDoors = true;
                break;
            }
        }

        showTopFiveCards(topFiveCards,1);

        int index = 0;
        if (!hasDoors) {
            showPrompt("You have no door to discover!",2);
            std::vector<int> arr;
            bool outOfRange = false;
            while (true) {
                arr.clear();
                outOfRange = false;
                showCommand("Rearrange cards (ex: 1 3 4 2 5)");
                for (int i = 0; i < topFiveCards.size(); ++i) {
                    int n = 0;
                    std::cin >> n;
                    if (n < 1 || n > topFiveCards.size()) {
                        showPrompt("ERROR: Index out of range!",2);
                        outOfRange = true;
                        break;
                    }
                    arr.push_back(n-1);
                }
                if (outOfRange) continue;
                else break;
            }    
            act.triggerIncantation(topFiveCards,arr);
        } else {
            while (true) {
                showCommand("Choose a door to discover (1->" + std::to_string(topFiveCards.size()) + ")");
                std::cin >> index;
                if (index >= 1 && index <= topFiveCards.size()) {
                    std::list<Card>::iterator it = topFiveCards.begin();
                    for (int i = 0; it != topFiveCards.end(); ++it, ++i) {
                        if (i == index - 1) break;
                    }
                    if (it->getSymbol() != Card::DOOR) {
                        showPrompt("ERROR: Must discover door!",2);
                        continue;
                    }
                        
                    ++act.doors[it->getColor()];
                    updateDoors();
                    topFiveCards.erase(it);
                    showTopFiveCards(topFiveCards,0);
                    if (!endGame && act.doors[0] == 3 && act.doors[1] == 3 && act.doors[2] == 3 && act.doors[3] == 3) {
                        winGame();
                        Sleep(ONE_SECOND);
                        return;
                    }

                    std::vector<int> arr;
                    bool outOfRange = false;
                    while (true) {
                        arr.clear();
                        outOfRange = false;
                        showCommand("Rearrange cards (ex: 1 4 2 3)");
                        for (int i = 0; i < topFiveCards.size(); ++i) {
                            int n = 0;
                            std::cin >> n;
                            if (n < 1 || n > topFiveCards.size()) {
                                showPrompt("ERROR: Index out of range!",2);
                                outOfRange = true;
                                break;
                            }
                            arr.push_back(n-1);
                        }
                        if (outOfRange) continue;
                        else break;
                    }
                    
                    act.triggerIncantation(topFiveCards,arr);
                    break;
                } else {
                    showPrompt("ERROR: Index out of range!",2);
                    continue;
                }
            }
        }
        
        clearInnerArea(top5CardsArea);
        updateTotalCards();
        
    }
    void resolveNightmare() {
        showPrompt("You have encountered NIGHTMARE!",2);
        int op = 0;
        while (true) {
            showCommand("Choose a way to solve (1->4)");
            std::cin >> op;
            /*****************************************
             * 1. Using a key; 
             * 2. Discard whole hand; 
             * 3. Discard top 5 cards; 
             * 4. Send a door to limbo
            ******************************************/
            if (op == 1) {
                if (act.hand.hasKey(Card::NONE)) {
                    int index = 0;
                    while (true) {
                        showCommand("Choose a key to discard (1->" + std::to_string(act.hand.sizeOf()) + ")");
                        std::cin >> index;
                        if (index >= 1 && index <= 5) {
                            if (act.hand.getCard(index-1).getSymbol() == Card::KEY) {
                                act.discard.pushCard(act.hand.getCard(index-1));
                                showDiscard(act.hand.getCard(index-1));
                                act.hand.removeCard(index-1);
                                showHand(0);
                                act.decNightmareCards(1);
                                updateNightmare();
                                break;
                            } else {
                                showPrompt("ERROR: Must discard a key!",2);
                                continue;
                            }
                        } else {
                            showPrompt("ERROR: Index out of range!",2);
                            continue;
                        }
                        
                    }
                    break;
                } else {
                    showPrompt("You have no key to discard!",2);
                    continue;
                }
            } else if (op == 2) {
                while (!act.hand.isEmpty()) {
                    act.discard.pushCard(act.hand.getCard(0));
                    showDiscard(act.hand.getCard(0));
                    act.hand.removeCard(0);
                    showHand(0);
                }
                act.decNightmareCards(1);
                updateNightmare();
                drawCardsAfterDiscardWholeHand();

                break;
            } else if (op == 3) {
                if (act.deck.sizeOf() >= 5) {
                    for (int i = 0; i < 5; ++i) {
                        Card card = act.deck.getTopCard();
                        showTopCard(card,1);
                        if (card.getSymbol() == Card::NIGHTMARE || card.getSymbol() == Card::DOOR) {
                            act.limbo.pushCard(card);
                            clearInnerArea(topCardArea);
                            showLimbo(card,1);
                            ++lastLimboCard;
                            continue;
                        } else {
                            act.discard.pushCard(card);
                            showDiscard(card);
                        }
                    }
                    /*
                    bool needReshuffle = !act.limbo.isEmpty();
                    while (!act.limbo.isEmpty()) {
                        act.deck.pushCard(act.limbo.getCard());
                        updateTotalCards();
                    }
                    if (needReshuffle) act.deck.reshuffle();
                    clearInnerArea(limboArea);
                    clearInnerArea(topCardArea);
                    lastLimboCard = 0;
                    */
                    act.decNightmareCards(1);
                    updateNightmare();
                    break;
                } else {
                    showPrompt("You have no enough card!",2);
                    continue;
                }
            } else if (op == 4) {
                bool hasDiscoveredDoors = false;
                for (int i = 0; i < 4; ++i) {
                    if (act.doors[i] > 0) {
                        hasDiscoveredDoors = true;
                        break;
                    }
                }
                if (hasDiscoveredDoors) {
                    int doorColor = -1;
                    while (true) {
                        showCommand("Choose a door to remove (1->4)");
                        std::cin >> doorColor;
                        if (doorColor >= 1 && doorColor <= 4) {
                            if (act.doors[doorColor-1] > 0) {
                                --act.doors[doorColor-1];
                                updateDoors();
                                Card card = Card((Card::Color) (doorColor-1), Card::DOOR);
                                act.limbo.pushCard(card);
                                showLimbo(card,1);
                                ++lastLimboCard;
                                /*
                                while (!act.limbo.isEmpty()) {
                                    act.deck.pushCard(act.limbo.getCard());
                                }
                                act.deck.reshuffle();
                                clearInnerArea(limboArea);
                                lastLimboCard = 0;
                                */
                                act.decNightmareCards(1);
                                updateNightmare();
                                break;
                            } else {
                                showPrompt("ERROR: No door for this color!",2);
                                continue;
                            }

                        } else {
                            showPrompt("ERROR: Index out of range!",2);
                            continue;
                        }
                    }
                } else {
                    showPrompt("You have no discovered door!",2);
                    continue;
                }
                break;
            } else {
                showPrompt("ERROR: Invalid option!",2);
                continue;
            }
        }
    }
    void drawCard() {
        if (endGame) return;
        if (act.deck.isEmpty()) {
            loseGame();
            return;
        } else {
            while (act.hand.sizeOf() < 5) {
                if (act.deck.isEmpty()) {
                    loseGame();
                    return;
                }
                Card card = act.deck.getTopCard();
                showTopCard(card,1);
                if (card.getSymbol() == Card::DOOR && !act.hand.hasKey(card.getColor())) {
                    act.limbo.pushCard(card);
                    clearInnerArea(topCardArea);
                    showLimbo(card,1);
                    ++lastLimboCard;
                    continue;
                } else if (card.getSymbol() == Card::DOOR && act.hand.hasKey(card.getColor())) {
                    int op = 0;
                    discover_door:
                    showCommand("DISCOVER door or NOT (1/2)?");
                    std::cin >> op;
                    if (op == 2) {
                        act.limbo.pushCard(card);
                        clearInnerArea(topCardArea);
                        showLimbo(card,1);
                        ++lastLimboCard;
                        continue;
                    } else if (op == 1) {
                        ++act.doors[card.getColor()];
                        for (int i = 0; i < act.hand.sizeOf(); ++i) {
                            if (act.hand.isKeyWithColor(i,card.getColor())) {
                                act.discard.pushCard(act.hand.getCard(i));
                                showDiscard(act.hand.getCard(i));
                                act.hand.removeCard(i);
                                showHand(0);
                                break;
                            }
                        }
                        updateDoors();
                        if (!endGame && act.doors[0] == 3 && act.doors[1] == 3 && act.doors[2] == 3 && act.doors[3] == 3) {
                            winGame();
                            Sleep(ONE_SECOND);
                            return;
                        }
                        continue;
                    } else {
                        showPrompt("ERROR: Invalid option!",2);
                        goto discover_door;
                    }
                    
                } else if (card.getSymbol() == Card::NIGHTMARE) {
                    resolveNightmare();
                    continue;
                } else {
                    act.hand.pushCard(card);
                    clearInnerArea(topCardArea);
                    showHand(0);
                    Sleep(ONE_SECOND);
                }
            }
            bool needReshuffle = !act.limbo.isEmpty();
            while (!act.limbo.isEmpty()) {
                act.deck.pushCard(act.limbo.getCard());
                updateTotalCards();
            }
            if (needReshuffle) act.deck.reshuffle();

            clearInnerArea(limboArea);
            clearInnerArea(topCardArea);
            lastLimboCard = 0;

            if (act.deck.isEmpty()) {
                loseGame();
                return;
            }
        }
    }
    void drawCardsAfterDiscardWholeHand() {
        if (endGame) return;
        if (act.deck.isEmpty()) {
            loseGame();
            return;
        } else {
            int n = 0;
            clearInnerArea(topCardArea);
            while (n < 5) {
                if (act.deck.isEmpty()) {
                    loseGame();
                    return;
                }
                Card card = act.deck.getTopCard();
                act.decTotalCards(1);
                updateTotalCards();
                if (card.getSymbol() == Card::DOOR || card.getSymbol() == Card::NIGHTMARE) {
                    act.limbo.pushCard(card);
                    showLimbo(card,1);
                    ++lastLimboCard;
                    continue;
                } else {
                    act.hand.pushCard(card);
                    showHand(0);
                    Sleep(ONE_SECOND);
                    ++n;
                }
            }
            bool needReshuffle = !act.limbo.isEmpty();
            while (!act.limbo.isEmpty()) {
                act.deck.pushCard(act.limbo.getCard());
                updateTotalCards();
            }
            if (needReshuffle) act.deck.reshuffle();
            clearInnerArea(limboArea);
            lastLimboCard = 0;
            if (act.deck.isEmpty()) {
                loseGame();
                return;
            }
        }
    }
    void startGame() {
        generateFrame();
        act.generateDeck();
        Sleep(ONE_SECOND);
        drawCardsAfterDiscardWholeHand();
        while (!endGame) {
            playTurn();
        }
    }
    void loseGame() {
        endGame = true;
        clearInnerArea(labyrinthArea);
        clearInnerArea(handArea);
        clearInnerArea(commandArea);
        clearInnerArea(top5CardsArea);
        clearInnerArea(topCardArea);
        clearInnerArea(discardArea);
        clearInnerArea(limboArea);

        gotoxy(handArea.getLeftUpperCornerX() + 7, handArea.getLeftUpperCornerY() + 1);
        std::cout << "You LOST!";
        Sleep(3 * ONE_SECOND);
    }
    void winGame() {
        endGame = true;
        clearInnerArea(labyrinthArea);
        clearInnerArea(handArea);
        clearInnerArea(commandArea);
        clearInnerArea(top5CardsArea);
        clearInnerArea(topCardArea);
        clearInnerArea(discardArea);
        clearInnerArea(limboArea);

        gotoxy(handArea.getLeftUpperCornerX() + 7, handArea.getLeftUpperCornerY() + 1);
        std::cout << "You WON!";
        Sleep(3 * ONE_SECOND);
    }
    /*** DEBUG ***/
    void debugPrintDeck() {
        int n = act.deck.sizeOf();
        for (int i = 0; i < 88; ++i) {
            clearLine(Point(47,i+1),15);
        }
        for (int i = 0; i < n; ++i) {
            Card card = act.deck.getTopCard();
            act.deck.pushCard(card);
            gotoxy(46,i);
            std::cout << act.deck.sizeOf() - i << ".";
            gotoxy(50,i);
            printTextWithColor(symbolString(card.getSymbol()),colorString(card.getColor()));
        }
    }
public:
    Display() {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        lastLimboCard = 0;
        lastLabyrinthCard = 0;
        endGame = false;

        infoArea = Area(5,37,Point(9,1));
        handArea = Area(5,37,Point(9,5));
        labyrinthArea = Area(32,9,Point(1,1));
        commandArea = Area(6,37,Point(9,9));
        top5CardsArea = Area(5,37,Point(9,14));
        discardArea = Area(15,25,Point(9,18));
        topCardArea = Area(5,13,Point(33,18));
        limboArea = Area(11,13,Point(33,22));
        noteArea = Area(8,45,Point(1,32));
    };
    void play() {
        while (true) {
            int startOp = 2;
            bool pressed2 = false;
            gotoxy(0,0);
            std::cout   << "---------------------------------------------\n"
                        << "|             Welcome to ONIRIM             |\n"
                        << "---------------------------------------------\n"
                        << "|  1. Start     2. Instruction     3. Quit  |\n"
                        << "---------------------------------------------\n"
                        << "Choose your option: ";
            while (startOp == 2) {
                std:: cin >> startOp;
                if (startOp == 1) break;
                else if (startOp == 3) return;
                pressed2 = true;
                std::cout << "Game rules have been written to ./onirim_game_rule.txt!\n";
                logInstruction();
                clearLine(Point(21,6),10);
                gotoxy(20,5);
            }
            if (pressed2 == true) clearWholeArea(63,7);
            else clearWholeArea(45,6);
            int op = 1;
            while (op == 1) {
                startGame();
                clearInnerArea(commandArea);
                gotoxy(commandArea.getLeftUpperCornerX() + 1, handArea.getLeftUpperCornerY() + 1);
                showCommand("PLAY AGAIN or MENU (1/2)?");
                std::cin >> op;
                if (op == 1) {
                    lastLimboCard = 0;
                    lastLabyrinthCard = 0;
                    endGame = false;
                    act = Action();
                }
            }
            clearWholeArea(infoArea);
            clearWholeArea(labyrinthArea);
            clearWholeArea(handArea);
            clearWholeArea(commandArea);
            clearWholeArea(top5CardsArea);
            clearWholeArea(topCardArea);
            clearWholeArea(discardArea);
            clearWholeArea(limboArea);
            clearWholeArea(noteArea);
        }
        

    }
};

#endif