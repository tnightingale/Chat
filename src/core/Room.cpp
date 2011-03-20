#include "Room.h"

Room::Room(QString name) : name_(name) {
    users_ = new QVector<QPair<QString, QString> >();
}

Room::~Room() {
    delete users_;
}
