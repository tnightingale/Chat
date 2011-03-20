#include "Room.h"

Room::Room(QString name) : name_(name) {
    users_ = new QVector<QPair<QString, QString> >();
}

Room::~Room() {
    delete users_;
}

void Room::addUser(User *user) {
    QString address = *user->getAddress();
    QString username = *user->getUserName();
    QPair<QString, QString> newUser(address, username);
    if (!users_->contains(newUser)) {
        users_->append(newUser);
    }
}

void Room::addUser(QPair<QString, QString> user) {
    if (!users_->contains(user)) {
        users_->append(user);
    }
}
