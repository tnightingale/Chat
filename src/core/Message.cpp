#include "Message.h"

QByteArray* Message::serialize() {
    QByteArray* msg = new QByteArray();
    QDataStream ds(msg, QIODevice::WriteOnly);
    ds.setVersion(QDataStream::Qt_4_7);
    ds << type_
       << sender_
       << room_
       << data_;

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

QVector<QPair<QString, QString> > Message::getUserList() {
    QVector<QPair<QString, QString> > users;
    QDataStream ds(&data_, QIODevice::ReadOnly);
    ds.setVersion(QDataStream::Qt_4_7);
    ds >> users;
    return users;
}