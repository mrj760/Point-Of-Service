#ifndef PASSKEY_H
#define PASSKEY_H


template <typename T>
class Key {friend T; Key() {} Key(Key const&) {} };

#endif // PASSKEY_H
