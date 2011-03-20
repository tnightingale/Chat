#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QDataStream>
#include "User.h"

/** Message Type defines. */
#define CHAT_MSG 0
#define NEW_CNCT 1
#define USR_LIST 2

class Message : public QObject {
    Q_OBJECT
private:
    quint8 type_;
    QPair<QString, QString> sender_;
    QString room_;
    QByteArray data_;

public:
    Message() {} 
    Message(QByteArray * buffer); 
    virtual ~Message() {}


    qint8 getType() { return type_; }

    void setType(qint8 t) { type_ = t; }

    QPair<QString, QString> getSender() { return sender_; }

    void setSender(User * user);

    QString getRoom() { return room_; }

    void setRoom(QString r) { room_ = r; }

    void setData(QByteArray d) { data_ = d; }

    QByteArray getMessage() { return data_; }

    QVector<QPair<QString, QString> > getUserList();

    QByteArray* serialize();

    void deserialize(QByteArray* msg);

};

#endif // MESSAGE_H
