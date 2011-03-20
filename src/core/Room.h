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

    QVector<QPair<QString, QString> >* getUsers() { return users_; }

    QPair<QString, QString> getUser(int index) { return users_->at(index); }

    void addUser(User * user);

    //void addUser(QPair<QString, QString> user);

    /**
     * A new message has been posted in this room.
     *
     * @param msg The message that has been posted.
     * 
     * @author Tom Nightingale
     */
    void newMessage(Message * msg);

signals:
    void broadcastMessage(QByteArray * message, QList<User *> * users);
};

#endif // ROOM_H
