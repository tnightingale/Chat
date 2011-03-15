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
    RoomWindow * getRW() {return rw; }

signals:
    void sendMessage(QString * message);

public slots:
    void connectRoom();

protected:
    Ui::MainWindow *ui;
    RoomWindow* rw;

    /**
     *
     *
     */
    bool eventFilter(QObject * obj, QEvent * event);
};

#endif // MAINWINDOW_H
