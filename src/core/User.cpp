#include "User.h"

User::User(char * address) 
: address_(new QString(address)) {
    qDebug() << "User::User(); User created, address:" << *address_;
}

User::~User() {
    qDebug() << "User::~User(); User disconnected address:" << *address_;
    delete address_;
    delete userName_;
}
