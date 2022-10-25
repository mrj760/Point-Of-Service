#include "item.h"

/* ID Functions */
QString Item::getId() const { return id; }


/* Quantity Functions */
double  Item::getQty() const { return qty; }
void    Item::setQty(double qty) { this->qty = qty; }
void    Item::setQty(int qty) { this->qty = qty; }

void    Item::subQty(double qty) { this->qty -= qty; }
void    Item::subQty(int qty) { this->qty -= qty; }

void    Item::addQty(double qty) { this->qty += qty; }
void    Item::addQty(int qty) { this->qty += qty; }


/* Sells By Unit Functions */
bool    Item::getSellsByUnit() const { return sellsByUnit; }
void    Item::setSellsByUnit(bool sellsByUnit) { this->sellsByUnit = sellsByUnit;}
