#ifndef ROOMWINDOW_H
#define ROOMWINDOW_H

#include <QWidget>

namespace Ui {
    class RoomWindow;
}

class RoomWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RoomWindow(QWidget *parent = 0);
    ~RoomWindow();

private:
    Ui::RoomWindow *ui;
};

#endif // ROOMWINDOW_H
