#ifndef MAIN_POS_H
#define MAIN_POS_H

#include "pos_register.h"
#include "cart.h"

#include <vector>

using std::vector;

class MainPOS
{
public:
    MainPOS();

private:
    vector<Cart> carts;
    vector<Register> registers;
};

#endif // MAIN_POS_H
