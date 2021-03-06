#ifndef NIGHTINGALE_USER_H
#define NIGHTINGALE_USER_H

#include <QObject>
#include <QDebug>

class User : public QObject {
  Q_OBJECT

private:
    /** The user's address */
    QString address_;

    /** The user's username. */
    QString userName_;

    /** The user's socket descriptor. */
    int socketD_;
  
public:
    User(const char * address);
    virtual ~User();

    /**
     * Set user's username. Users must be created with an associated ip address
     * but not a username, this is assigned after initialization.
     *
     * @param userName A pointer
     *
     * @author Tom Nightingale
     */
    void setUserName(QString userName) { userName_ = userName; }

    /**
     * Returns the user's username.
     *
     * @author Tom Nightingale
     */
    const QString getUserName() { return userName_; }

    /**
     * Returns the user's address.
     *
     * @author Tom Nightingale
     */
    const QString getAddress() { return address_; }

    /**
     * FOR SERVER USE
     * Set the socket descriptor used to communicate with user's client.
     *
     * @param socketD A socketDesciptor that is paired with the user.
     *
     * @author Tom Nightingale
     */
    void setSocketD(int socketD) { socketD_ = socketD; }

    /**
     * FOR SERVER USE
     * Get the user's socket descriptor.
     * 
     * @author Tom Nightingale
     */
    int getSocketD() { return socketD_; }

    /**
     * Makes string representation of User
     *
     * @author Marcel Vangrootheest
     * @return string representation of user
     */
    QString toString();

    /**
     * Input and output stream operators for serializing and deserializing 
     * User objects.
     *
     * @author Tom Nightingale
     */
    friend QDataStream& operator<<(QDataStream& os, const User& user);
    friend QTextStream& operator<<(QTextStream& os, const User& user);

};

#endif
