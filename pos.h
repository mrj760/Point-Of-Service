/* POS is the module which oversees and controls all carts and registers */

#ifndef POS_H
#define POS_H

/* PROJECT INCLUDES */
#include <backbone.h>
#include <passkey.h>
#include <transaction.h>
#include <register.h>

/* PATH INCLUDES */
#include <vector>
#include <tuple>
#include <QString>
#include <QWidget>

/* USING */
using std::vector;
using std::tuple;

/* FORWARD CLASS DECL'S */
class Customer;
class Item;
class Register;
class Transaction;
class POS;


class POS : QWidget
{
public:
    /* Constructors */
    POS();

    /* Member Vars */
    Transaction _activeCart; /* Currently opened cart */
    Register _activeRegister; /* Currently active register */

    /* Getters */
    const Transaction& activeCart = _activeCart;
    const Register& activeRegister = _activeRegister;

    /* Public Functions */
    Item readSKU(const QString&); /* Reach out to backbone to obtain Item information from a SKU */

    bool activateCart(int); /* Activate cart based on ID. Return false if cart is not in list. */
    void deactivateCart(); /* Close currently active cart if there is one. */
    bool finalizeCart(); /* Finalize currently active cart. Return false if no active cart. */
    bool activateRegister(int); /* Activate register based on ID. Return false if register not in list. */
    void deactivateRegister(); /* Close currently active Register */
    bool addCashToRegister(int); /* Add cash to active register. Return false if no active register. */
    bool subCashFromRegister(int); /* Sub cash from active register. Return false if no active register. */

};


#endif // POS_H
