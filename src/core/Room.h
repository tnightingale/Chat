#ifndef ROOM_H
#define ROOM_H

#include <QObject>
#include <QVector>
#include <QString>

class User;
class Message;

class Room : public QObject {
    Q_OBJECT
private:
    QVector<User*> users;
    QVector<Message*> messages;
    QString name;

public:
    Room(){}
    ~Room(){}
};

#endif // ROOM_H
