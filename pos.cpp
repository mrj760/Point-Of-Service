#include <pos.h>
/********** POS **********/

const Cart POS::inactiveCart = Cart();
const Register POS::inactiveRegister = Register();

vector<Cart> POS::_carts = {};
vector<Register> POS::_registers = {};
vector<Cart> POS::_finalizedCarts = {};
vector<Register> POS::_finalizedRegisters = {};

POS::POS()
{
    _activeCart = inactiveCart;
    _activeRegister = inactiveRegister;

}

Item POS::readSKU(const QString& sku)
{
    // return database.getItem(sku);
    return Item();
}


bool POS::activateCart(Key<Backbone>, int ID)
{

    // _activeCart = database.activateCart(ID);

    for (const Cart& c : _carts)
    {
        if (c.ID == ID)
        {
            _activeCart = c;
            return true;
        }
    }
    return false;
}

void POS::deactivateCart(Key<Backbone>)
{
    _activeCart = inactiveCart;
}

bool POS::finalizeCart(Key<Backbone>)
{
    if (_activeCart == inactiveCart)
        return false;

    auto iter = _carts.begin();
    while (iter != _carts.end())
    {
        if (*iter == _activeCart)
        {
            _carts.erase(iter);
            _activeCart = inactiveCart;
            return true;
        }
        ++iter;
    }

    return false;
}

bool POS::activateRegister(Key<Backbone>, int ID)
{
    // _activeRegister = database.activateRegister(ID);
    for (const Register& r: _registers)
    {
        if (ID == r.ID)
        {
            _activeRegister = r;
            return true;
        }
    }
    return false;
}

void POS::deactivateRegister(Key<Backbone>)
{
    if (_activeRegister == inactiveRegister)
        return;
    // database.deactivateRegister(_activeRegister.ID);
    _activeRegister = inactiveRegister;
}

bool POS::addCashToRegister(Key<Backbone>, int cents)
{
    if (_activeRegister == inactiveRegister)
        return false;
    _activeRegister.addCash({}, cents);
    // database.updateRegister(_activeRegister.ID, _activeRegister.cashInDrawer);
    return true;
}

bool POS::subCashFromRegister(Key<Backbone>, int cents)
{
    if (_activeRegister == inactiveRegister)
        return false;
    _activeRegister.subCash({}, cents);
    // database.updateRegister(_activeRegister.ID, _activeRegister.cashInDrawer);
    return true;
}

void POS::openRegister(Key<Backbone>)
{
    // call to hardware (out of scope for our project?)
}

bool POS::finalizeRegister(Key<Backbone>)
{
    if (_activeRegister == inactiveRegister)
        return false;

    auto iter = _registers.begin();
    while (iter != _registers.end())
    {
        if (*iter == _activeRegister)
        {
            _registers.erase(iter);
            _activeRegister = inactiveRegister;
            return true;
        }
        ++iter;
    }
    return false;
}

/****************************** END POS ******************************/





/**************************************************/
/**************************************************/





/****************************** ITEM ******************************/

// TODO
bool Item::operator==(const Item&)
{
    return false;
}

// TODO
Item Item::operator=(const Item& i)
{
    return Item(i);
}

/****************************** END ITEM ******************************/





/**************************************************/
/**************************************************/





/****************************** CUSTOMER ******************************/

// TODO
bool Customer::operator==(const Customer&)
{
    return false;
}

// TODO
Customer Customer::operator=(const Customer& c)
{
    return Customer(c);
}

/****************************** END CUSTOMER ******************************/





/**************************************************/
/**************************************************/





/****************************** CART ******************************/

// TODO
bool Cart::setItemGroupPrice(Key<POS>, Item, int)
{
    return false;
}

// TODO
void Cart::setFinalPrice(Key<POS>, int)
{

}

// TODO
bool Cart::open(Key<POS>)
{
    return false;
}

// TODO
bool Cart::close(Key<POS>)
{
    return false;
}

// TODO
void Cart::addToCart(Item item, int qty)
{

}

// TODO
void Cart::removeFromCart(Item item, int qty)
{

}

// TODO
int Cart::contains(const Item &item) const
{
    return -1;
}

// TODO
bool Cart::operator==(const Cart& other)
{
    return false;
}

// TODO
Cart Cart::operator=(const Cart& c)
{
    return Cart(c);
}

/****************************** END CART ******************************/





/**************************************************/
/**************************************************/





/****************************** REGISTER ******************************/

// TODO
int Register::addCash(Key<POS>, int)
{
    return -1;
}

// TODO
int Register::subCash(Key<POS>, int)
{
    return -1;
}

// TODO
bool Register::operator==(const Register&)
{
    return false;
}

// TODO
Register Register::operator=(const Register& r)
{
    return Register(r);
}

/****************************** END REGISTER ******************************/





/**************************************************/
/**************************************************/



