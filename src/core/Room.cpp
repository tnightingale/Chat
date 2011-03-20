#include "Room.h"

Room::Room(QString name) 
: name_(name), users_(new QSet<User *>()) {}

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
    users_->add(user);
}

//void Room::addUser(QPair<QString, QString> user) {
//    if (!users_->contains(user)) {
//        users_->append(user);
//    }
//}

void Room::newMessage(Message * msg) {
    // Broadcast message here.
    
}
