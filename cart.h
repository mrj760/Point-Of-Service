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
    void addToCart(Item, int);
    void removeFromCart(Item, int);
    bool contains(Item);
};

#endif // CART_H
