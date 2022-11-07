#ifndef CART_H
#define CART_H


#include <item.h>
#include <customer.h>

#include <vector>
#include <tuple>

using std::vector;
using std::tuple;

class Cart
{
public:
    Cart();

private:
    int cartID;
    vector<tuple<Item, int>> items;
    int totalPrice; // represented in cents.
    Customer customer;

public:
    void addToCart(Item, int); /* add X of a certain item to the cart */
    void removeFromCart(Item, int); /* remove X of a certain to the cart */
    int contains(Item); /* return how many of a certain item exist in the cart */
};

#endif // CART_H
