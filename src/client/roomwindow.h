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

    Ui::RoomWindow * getUi() { return ui; }

private:
    Ui::RoomWindow *ui;
};

#endif // ROOMWINDOW_H
