#ifndef ROOM_H
#define ROOM_H

#include <QObject>
#include <QVector>
#include <QString>
#include "Message.h"

class User;

class Room : public QObject {
    Q_OBJECT
private:
    QVector<QPair<QString, QString> > * users_;
    QString name_;

public:
    Room(QString name);
    virtual ~Room();

    QString getName() { return name_; }

    QVector<QPair<QString, QString> >* getUsers() { return users_; }

    QPair<QString, QString> getUser(int index) { return users_->at(index); }

    void addUser(User* user);

    void addUser(QPair<QString, QString> user);
};

#endif // ROOM_H
