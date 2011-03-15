#include "User.h"

User::User(char * address) 
: address_(new QString(address)) {
    qDebug("User::User(); User created.");
}

User::~User() {
    delete address_;
    delete userName_;
}
