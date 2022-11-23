#ifndef REGISTER_H
#define REGISTER_H

#include <passkey.h>

class POS;

class Register
{
public:
    /* Constructors */
    Register(int ID=0, int cents=20000) :
        ID(0), centsInDrawer(cents) {}
    Register(const Register& r) :
        ID(r.ID), centsInDrawer(r.centsInDrawer) {};

    /* Member Vars */
    int ID; /* ID of register */
    int centsInDrawer; /* Amount of cash in active Register drawer represented in cents */

    int addCents(int); /* Add cash to drawer */
    int subCents(int); /* Sub cash from drawer. Don't go below 0 */

    bool operator==(const Register&); /* Returns Register equality based on ID */
    Register operator=(const Register&); /* Copy assigns the given register */
};

#endif // REGISTER_H
