#include "item.h"

/* ID Functions */
QString Item::getID() const { return id; }


/* Quantity Functions */
double  Item::getQty() const { return qty; }
void    Item::setQty(int qty) { this->qty = qty; }

void    Item::subQty(int qty) { this->qty -= qty; }

void    Item::addQty(int qty) { this->qty += qty; }
