#include "User.h"

User::User(const char * address)
: address_(address), userName_(address) {
    qDebug() << "User::User(); User created, address:" << address_;
}

User::~User() {
    qDebug() << "User::~User(); User disconnected address:" << address_;
}

QDataStream& operator<<(QDataStream& os, const User& user) {
    return os << user.userName_ << "@" << user.address_;
}

QTextStream& operator<<(QTextStream& os, const User& user) {
    return os << user.userName_ << "@" << user.address_;
}

QString User::toString() {
    return userName_ + "@" + address_;
}
