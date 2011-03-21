#ifndef ROOMWINDOW_H
#define ROOMWINDOW_H

#include <QWidget>
#include <QKeyEvent>

namespace Ui {
    class RoomWindow;
}

class RoomWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RoomWindow(QString name);
    ~RoomWindow();

    Ui::RoomWindow * getUi() { return ui; }

    bool eventFilter(QObject * obj, QEvent * event);
signals:
    void sendMessage(QString * message, QString roomName);

public slots:
    /**
     * Saves file to specified text file in QFileDialog.
     *
     * @author Marcel Vangrootheest
     */
    void saveFile();
    /**
     * Limits the sendArea to 250 characters
     *
     * @author Marcel Vangrootheest
     */
    void checkTextBox();

private:
    Ui::RoomWindow *ui;
};

#endif // ROOMWINDOW_H
