#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QDataStream>
#include "User.h"

/** Message Type defines. */
#define MSG_CHAT      0
#define MSG_USERLIST  1
#define MSG_JOINROOM  2
#define MSG_LEAVEROOM 3 
#define MSG_SETNICK   4 

class Message : public QObject {
    Q_OBJECT
private:

    /** The message type */
    quint8 type_;

    /** The message sender. (address, username) */
    QPair<QString, QString> sender_;

    /** The room the message belongs to. */
    QString room_;

    /** The message payload. */
    QByteArray data_;

public:
    Message() {} 
    Message(QByteArray * buffer); 
    virtual ~Message() {}


    /**
     * Returns the message type.
     *
     * @author Marcel Vangrootheest
     */
    qint8 getType() { return type_; }

    /**
     * Sets the message type.
     *
     * @author Marcel Vangrootheest
     */
    void setType(qint8 t) { type_ = t; }

    /**
     * Returns the message sender. This is returned in a Address & Name pair.
     *
     * @author Marcel Vangrootheest
     */
    QPair<QString, QString> getSender() { return sender_; }

    /**
     * Set's the messages sender.
     * 
     * @param user A pointer to a User object of which is the owner of this
     *             message.
     *
     * @author Marcel Vangrootheest
     */
    void setSender(User * user);

    /**
     * Reutrns the room to which this message belongs.
     *
     * @author Marcel Vangrootheest
     */
    QString getRoom() { return room_; }

    /**
     * Sets the messages room property.
     *
     * @author Marcel Vangrootheest
     */
    void setRoom(QString r) { room_ = r; }

    /**
     * Set's the messages data value.
     *
     * @author Marcel Vangrootheest
     */
    void setData(QByteArray d) { data_ = d; }

    /**
     * Returns the messages data value.
     *
     * @author Marcel Vangrootheest
     */
    QByteArray getMessage() { return data_; }

    /**
     * Unserializes and returns the userlist in this message.
     *
     * @author Marcel Vangrootheest
     */
    QString getUserList();

    /**
     * Serialize the message data.
     *
     * @author Marcel Vangrootheest
     */
    QByteArray* serialize();

    /**
     * Unserialize the message data.
     *
     * @author Marcel Vangrootheest
     */
    void deserialize(QByteArray* msg);

};

#endif // MESSAGE_H
