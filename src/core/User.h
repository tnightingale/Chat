#include <QObject>

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
     * Return's the user's username.
     *
     * @author Tom Nightingale
     */
    QString getUserName() { return *userName_; }
};
