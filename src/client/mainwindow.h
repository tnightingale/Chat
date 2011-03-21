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

    /**
     * Returns the window's ui object.
     */
    Ui::MainWindow * getUi() { return ui; }

    /**
     * Returns map of current room windows.
     *
     * @author Marcel Vangrootheest
     */
    QMap<QString, RoomWindow*>* getRooms() { return rooms; }

protected:
    /** Qt user interface object. */
    Ui::MainWindow *ui;

    /** Map of room windows. */
    QMap<QString, RoomWindow*>* rooms;
};

#endif // MAINWINDOW_H
