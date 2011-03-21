#include "Room.h"

Room::Room(QString name) 
: users_(new QSet<User *>()), name_(name) {}

Room::~Room() {
    delete users_;
}

void Room::addUser(User * user) {
    //QString address = *user->getAddress();
    //QString username = *user->getUserName();

    //QPair<QString, QString> newUser(address, username);
    //if (!users_->contains(newUser)) {
    //    users_->append(newUser);
    //}
    users_->insert(user);
}

void Room::removeUser(User * user) {
    users_->remove(user);
}

//void Room::addUser(QPair<QString, QString> user) {
//    if (!users_->contains(user)) {
//        users_->append(user);
//    }
//}

