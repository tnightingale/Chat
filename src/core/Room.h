#ifndef ROOM_H
#define ROOM_H

#include <QObject>
#include <QSet>
#include <QString>
#include "Message.h"

class User;

class Room : public QObject {
    Q_OBJECT
private:
    QSet<User *> * users_;
    QString name_;

public:
    Room(QString name);
    virtual ~Room();

    QString getName() { return name_; }

    QSet<User *> getUsers() { return *users_; }

    /**
     * Add a user to the room.
     *
     * @param user The user you wish to add.
     *
     */
    void addUser(User * user);

    //void addUser(QPair<QString, QString> user);
};

#endif // ROOM_H
