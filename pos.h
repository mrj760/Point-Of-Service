/* POS is the module which oversees and controls all carts and registers */

#ifndef POS_H
#define POS_H

/* PROJECT INCLUDES */
#include <passkey.h>
#include <backbone.h>
#include <transaction.h>
#include <register.h>
#include <module.h>

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

//Archiving original inheretence just in case
//class POS : QWidget
class POS : public Module     //Do I need this inheretence? No idea. Will figure out later
{
public:
    /* Constructors */
    POS();

    /* Destructors */
    //Test module had one, so we're gonna go with that
    ~POS();

    /* PassKey*/
    //Please fix if this doesn't work
    /*
     * Notes to whoever decides to do backbone integration
     * 1. Adjust the backbone to call receive with passkey
     * 2. Figure out how to set up the passkey in the POS constructor
     * The passkey is commented out until I figure that out
    */
    //Key<Backbone> bb_key;

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

    /*Passkey functions*/
    //I'll sort out which one I need later
    //void receive(Key<Backbone>, WorkOrder& wo);    //For if/when passkey is implemented
    int getID() override;
    void setID(int id) override;
    std::string getName() override;
    bool setWaiting() override;
    bool receive(WorkOrder& wo) override;
};


#endif // POS_H
