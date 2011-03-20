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

    QString getName() {
        return name_;
    }
};

#endif // ROOM_H
