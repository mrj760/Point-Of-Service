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

/* FORWARD CLASS DECL'S */
class Customer;
class Item;
class Register;
class Cart;
class POS;


template <typename T>
class Key {friend T; Key() {} Key(Key const&) {} };


/****************************** CUSTOMER ******************************/

class Customer
{
    friend class Main_POS; /* Allow Main_POS to access all customer details */

public:
    /* Constructors */
    Customer() : _ID(0), _name("NaN"), _address("NaN") {};
    Customer(int ID, QString name, QString address) : _ID(ID), _name(name), _address(address) {};
    Customer(const Customer& c) : ID(c.ID), name(c.name), address(c.address) {};

private:

    /* Member Vars */
    int _ID; /* Numeric customer ID (Phone Number) */
    QString _name; /* Customer name */
    QString _address; /* Customer street address */

public:

    /* Getters */
    const int& ID = _ID;
    const QString& name = _name;
    const QString& address = _address;

    /* Public Functions */
    bool operator==(const Customer&); /* Return whether one Customer is equal to another based on ID */
    Customer operator=(const Customer&); /* Copy assigns the given customer */
};

/****************************** END CUSTOMER ******************************/





/**************************************************/
/**************************************************/





/****************************** ITEM ******************************/

class Item
{
public:
    /* Constructors */
    Item() : _ID("NaN"), _name("NaN"), _price(0) {};
    Item(QString ID, QString name, int price) : _ID(ID), _name(name), _price(price){};
    Item(const Item& i) : _ID(i.ID), _name(i.name), _price(i.price) {};

private:
    /* Member Vars */
    QString _ID;     /* SKU ( ID ) */
    QString _name;   /* Name of item */
    int _price;      /* Price in cents */

public:

    /* Getters */
    const QString& ID = _ID;
    const QString& name = _name;
    const int& price = _price;

    /* Public Functions */
    bool operator==(const Item&); /* Return whether one Item is equal to another based on ID */
    Item operator=(const Item&); /* Copy assigns the given item */
};

/****************************** END ITEM ******************************/





/**************************************************/
/**************************************************/





/****************************** REGISTER ******************************/

class Register
{
public:
    /* Constructors */
    Register(int cash=20000) : _cashInDrawer(cash) {}
    Register(const Register& r) : _ID(r.ID), _cashInDrawer(r.cashInDrawer) {};

private:
    /* Member Vars */
    int _ID; /* ID of register */
    int _cashInDrawer; /* Amount of cash in active Register drawer represented in cents */

public:

    /* Getters */
    const int& ID = _ID;
    const int& cashInDrawer = _cashInDrawer;

    /* Public Functions */
    int addCash(Key<POS>, int); /* Add cash to drawer */
    int subCash(Key<POS>, int); /* Sub cash from drawer. Don't go below 0 */

    bool operator==(const Register&); /* Returns Register equality based on ID */
    Register operator=(const Register&); /* Copy assigns the given register */
};
/****************************** END REGISTER ******************************/





/**************************************************/
/**************************************************/





/****************************** CART ******************************/

class Cart
{
public:
    /* Constructors */
    Cart() : _ID(0), _items(), _totalPrice(0), _customer(Customer()) {};
    Cart(int ID, Customer customer) : _ID(ID), _items(), _totalPrice(0), _customer(customer) {};
    Cart(const Cart& c) : _ID(c.ID), _items(c.items), _totalPrice(c.totalPrice), _customer(c.customer), _isOpen(c.isOpen) {}

private:

    /* Member Vars */
    int _ID; /* Get from static IDs */
    vector<tuple<Item, int, int>> _items; /* List of items in the cart, how many of them, and the total price of each group of items in cents */
    int _totalPrice; /* Total price represented in cents */
    Customer _customer; /* The customer which the cart is attributed to */
    bool _isOpen; /* Whether the cart is being edited by a POS module */

public:

    /* Getters */
    const int& ID = _ID;
    const vector<tuple<Item, int, int>>& items = _items;
    const int& totalPrice = _totalPrice;
    const Customer& customer = _customer;
    const bool& isOpen = _isOpen;

    /* Semi-Public Functions */
    bool setItemGroupPrice(Key<POS>, Item, int); /* Set price of group of items. Update total.
                                                * Return false if Item not in cart. */
    void setFinalPrice(Key<POS>, int); /* Set final price of cart to certain amount. */
    bool open(Key<POS>); /* Open this cart for editing. Return false if already open. */
    bool close(Key<POS>); /* Stop editing this cart. Return false if already closed. */

    /* Public Functions */
    void addToCart(Item, int); /* Add X of a certain item to the cart. Update total if not already set manually */
    void removeFromCart(Item, int); /* Remove X of a certain to the cart. Update total if not already set manually */
    int contains(const Item&) const; /* Return how many of a certain item exist in the cart */

    bool operator==(const Cart&); /* Returns cart equality based on ID */
    Cart operator=(const Cart&); /* Copy assigns the given cart */

};

/****************************** END CART ******************************/





/**************************************************/
/**************************************************/





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

    static const Cart inactiveCart;
    static const Register inactiveRegister;

    /* Member Vars */
    Cart _activeCart; /* Currently opened cart */
    Register _activeRegister; /* Currently active register */

public:
    /* Getters */
    const Cart& activeCart = _activeCart;
    const Register& activeRegister = _activeRegister;
    const vector<Cart>& carts = _carts;
    const vector<Register>& registers = _registers;
    const vector<Cart>& finalizedCarts = _finalizedCarts;
    const vector<Register> finalizedRegisters = _finalizedRegisters;

    /* Public Functions */
    Item readSKU(const QString&); /* Reach out to backbone to obtain Item information from a SKU */

    /* ************************* */

    /* Everything Backbone below */
private:

public:
    /* Semi-public Functions */
    void addCart(Key<Backbone>); /* Create new cart and add to list of carts */
    bool activateCart(Key<Backbone>, int); /* Activate cart based on ID. Return false if cart is not in list. */
    void deactivateCart(Key<Backbone>); /* Close currently active cart if there is one. */
    bool finalizeCart(Key<Backbone>); /* Finalize currently active cart. Return false if no active cart. */
    bool activateRegister(Key<Backbone>, int); /* Activate register based on ID. Return false if register not in list. */
    void deactivateRegister(Key<Backbone>); /* Close currently active Register */
    bool addCashToRegister(Key<Backbone>, int); /* Add cash to active register. Return false if no active register. */
    bool subCashFromRegister(Key<Backbone>, int); /* Sub cash from active register. Return false if no active register. */
    void openRegister(Key<Backbone>); /* Physically open active register */
    bool finalizeRegister(Key<Backbone>); /* Finalize register based on ID. Return false if not in list. */

};

/****************************** END POS ******************************/





/**************************************************/
/**************************************************/





#endif // POS_H
