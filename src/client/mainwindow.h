#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QTextEdit>

namespace Ui {
    class MainWindow;
}

class RoomWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Ui::MainWindow * getUi() { return ui; }

    QMap<QString, RoomWindow*>* getRooms() {
        return rooms;
    }

signals:
    void sendMessage(QString * message);

protected:
    Ui::MainWindow *ui;
    QMap<QString, RoomWindow*>* rooms;
};

#endif // MAINWINDOW_H
