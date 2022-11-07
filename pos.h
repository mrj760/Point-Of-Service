/* POS is the module which oversees and controls all carts and registers */

#ifndef POS_H
#define POS_H

/* PROJECT INCLUDES */
#include <backbone.h>

/* PATH INCLUDES */
#include <vector>
#include <tuple>
#include <QString>

/* USING */
using std::vector;
using std::tuple;

/* ALT TYPE NAMES */
typedef QString qstring;

/* FORWARD CLASS DECL'S */
class Cart;
class Item;
class Register;
class Customer;


/****************************** POS ******************************/
class POS
{
public:
    /* Constructors */
    POS();

private:
    /* Static Vars */
    static vector<Cart> _carts; /* All carts throughout the store */
    static vector<Register> _registers; /* All registers throughout the store */
    static vector<Cart> _finalizedCarts; /* All carts which cannot be edited anymore.
                                        * The transaction has been completed or voided. */
    static vector<Register> _finalizedRegisters; /* All registers which have been counted and closed. */

    /* Member Vars */
    Cart& _activeCart; /* Currently opened cart */
    Register& _activeReg; /* Currently active register */

public:
    /* Getters */
    const Cart& activeCart = _activeCart;
    const Register& activeReg = _activeReg;
    const vector<Cart>& carts = _carts;
    const vector<Register>& registers = _registers;
    const vector<Cart>& finalizedCarts = _finalizedCarts;
    const vector<Register> finalizedRegisters = _finalizedRegisters;

    /* Public Functions */
    Item readSKU(qstring); /* Reach out to backbone to obtain Item information from a SKU */

    /* ************************* */
    /* Everything Backbone below */
private:
    class Key
    {
        /* Require this as an argument in functions which
         * should only be accessible from the Backbone module */
        friend class Backbone;
        Key();
        ~Key();
    };
public:
    /* Semi-public Functions */
    void addCart(Key); /* Create new cart and add to list of carts */
    bool openCart(Key, int); /* Activate cart based on ID. Return false if cart is not in list. */
    bool closeCart(Key); /* Close currently active cart. Return false if no cart is active. */
    bool finalizeCart(Key); /* Finalize currently active cart. Return false if no active cart. */
    bool activateRegister(Key, int); /* Activate register based on ID. Return false if register not in list. */
    void addCashToRegister(Key); /* Add cash to active register */
    void subCashFromRegister(Key); /* Sub cash from active register */
    void openRegister(Key); /* Physically open active register */
    bool finalizeRegister(Key, int); /* Finalize register based on ID. Return false if not in list. */

};
/****************************** END POS ******************************/





/**************************************************/
/**************************************************/





/****************************** ITEM ******************************/
class Item
{
public:
    /* Constructors */
    Item(qstring ID, qstring name, int price) : _ID(ID), _name(name), _price(price){};

private:
    /* Member Vars */
    qstring _ID;     /* SKU ( ID ) */
    qstring _name;   /* Name of item */
    int _price;      /* Price in cents */

public:

    /* Getters */
    const qstring& ID = _ID;
    const qstring& name = _name;
    const int& price = _price;

    /* Public Functions */
    bool operator==(const Item&); /* Return whether one Item is equal to another based on ID */
};
/****************************** END ITEM ******************************/





/**************************************************/
/**************************************************/





/****************************** CUSTOMER ******************************/
class Customer
{
friend class Main_POS; /* Allow Main_POS to access all customer details */

public:
    /* Constructors */
    Customer(int, qstring="", qstring="");

private:

    /* Member Vars */
    int _ID; /* Numeric customer ID (Phone Number) */
    qstring _name; /* Customer name */
    qstring _address; /* Customer street address */

public:

    /* Getters */
    const int& ID = _ID;
    const qstring& name = _name;
    const qstring& address = _address;

    /* Public Functions */
    bool operator==(const Customer&); /* Return whether one Customer is equal to another based on ID */
};
/****************************** END CUSTOMER ******************************/





/**************************************************/
/**************************************************/





/****************************** CART ******************************/
class Cart
{
public:
    /* Constructors */
    Cart();
private:

    /* Static Vars */
    static int _IDs; /* Initialize to 1 and use/increment to assign new ID to each cart */

    /* Member Vars */
    int _ID; /* Get from static IDs */
    vector<tuple<Item, int, int>> _items; /* List of items in the cart, how many of them, and the total price of each group of items in cents */
    int _totalPrice; /* Total price represented in cents */
    Customer _customer; /* The customer which the cart is attributed to */
    bool _isOpen; /* Whether the cart is being edited by a POS module */

    class Key
    {
        /* Require this as an argument in functions which
         * should only be accessible from the POS module */
        friend class POS;
        Key();
        ~Key();
    };

public:

    /* Getters */
    const int& ID = _ID;
    const vector<tuple<Item, int, int>>& items = _items;
    const int& totalPrice = _totalPrice;
    const Customer& customer = _customer;
    const bool& isOpen = _isOpen;

    /* Semi-Public Functions */
    bool setItemGroupPrice(Key, Item, int); /* Set price of group of items. Update total.
                                                * Return false if Item not in cart. */
    void setFinalPrice(Key, int); /* Set final price of cart to certain amount. */
    bool open(Key); /* Open this cart for editing. Return false if already open. */
    bool close(Key); /* Stop editing this cart. Return false if already closed. */

    /* Public Functions */
    void addToCart(Item, int); /* Add X of a certain item to the cart. Update total if not already set manually */
    void removeFromCart(Item, int); /* Remove X of a certain to the cart. Update total if not already set manually */
    int& contains(const Item&) const; /* Return how many of a certain item exist in the cart */

    bool operator==(const Cart&); /* Returns cart equality based on ID */

};
/****************************** END CART ******************************/





/**************************************************/
/**************************************************/





/****************************** REGISTER ******************************/
class Register
{
public:
    /* Constructors */
    Register(int cash=20000) : _cashInDrawer(cash) {}

private:
    /* Member Vars */
    int _cashInDrawer; /* Amount of cash in active Register drawer represented in cents */

    class Key
    {
        /* Require this as an argument in functions which
         * should only be accessible from the POS module */
        friend class POS;
        Key();
        ~Key();
    };

public:

    /* Getters */
    const int& cashInDrawer = _cashInDrawer;

    /* Public Functions */
    int addCash(Key, int); /* Add cash to drawer */
    int subCash(Key, int); /* Sub cash from drawer. Don't go below 0 */

    bool operator==(const Register&); /* Returns Register equality based on ID */
};
/****************************** END REGISTER ******************************/





/**************************************************/
/**************************************************/





#endif // POS_H
