#include "Message.h"

Message::Message(QByteArray * buffer) {
    deserialize(buffer);
}

QByteArray* Message::serialize() {
    QByteArray* msg = new QByteArray();
    QDataStream ds(msg, QIODevice::WriteOnly);
    ds.setVersion(QDataStream::Qt_4_7);
    ds << type_
       << sender_
       << room_
       << data_;

    // Messages must always end with a \n.
    *msg += '\n';

    return msg;
}

void Message::deserialize(QByteArray* msg) {
    QDataStream ds(msg, QIODevice::ReadOnly);
    ds.setVersion(QDataStream::Qt_4_7);
    ds >> type_
       >> sender_
       >> room_
       >> data_;
}

void Message::setSender(User * user) {
    sender_.first = user->getAddress();
    sender_.second = user->getUserName();
}

QString Message::getUserList() {
    QString users;
    QTextStream ts(&data_);
    ts >> users;
    return users;
}
