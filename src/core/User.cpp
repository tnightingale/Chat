#include "User.h"

User::User(char * address) 
: address_(new QString(address)), userName_(NULL) {
    qDebug() << "User::User(); User created, address:" << *address_;
}

User::~User() {
    qDebug() << "User::~User(); User disconnected address:" << *address_;
    delete address_;
    delete userName_;
}

QDataStream& operator<<(QDataStream& os, const User& user) {
    return os << user.userName_ << "@" << user.address_;
}
