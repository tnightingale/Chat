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
    void saveFile();

private:
    Ui::RoomWindow *ui;
};

#endif // ROOMWINDOW_H
