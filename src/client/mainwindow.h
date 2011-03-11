#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class RoomWindow;
class Socket;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void connectRoom();

protected:
    Ui::MainWindow *ui;
    RoomWindow* rw;
    Socket *s;
};

#endif // MAINWINDOW_H
