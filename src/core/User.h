#include <QObject>
#include <QDebug>

class User : public QObject {
  Q_OBJECT

private:
    QString * address_;
    QString * userName_;
  
public:
    User(char * address);
    virtual ~User();

    /**
     * Set user's username. Users must be created with an associated ip address
     * but not a username, this is assigned after initialization.
     *
     * @param userName A pointer
     *
     * @author Tom Nightingale
     */
    void setUserName(QString& userName) { userName_ = &userName; }

    /**
     * Returns the user's username.
     *
     * @author Tom Nightingale
     */
    const QString * getUserName() { return userName_; }

    /**
     * Returns the user's address.
     *
     * @author Tom Nightingale
     */
    const QString * getAddress() { return address_; }
};
