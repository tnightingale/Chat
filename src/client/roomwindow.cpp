#include "roomwindow.h"
#include "ui_roomwindow.h"

RoomWindow::RoomWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoomWindow) {
    ui->setupUi(this);
}

RoomWindow::~RoomWindow() {
    delete ui;
}

bool RoomWindow::eventFilter(QObject * obj, QEvent * event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        QString * message = new QString();

        if (keyEvent->key() == Qt::Key_Return) {
            message->append(getUi()->sendArea->toPlainText());
            getUi()->sendArea->clear();

            emit sendMessage(message);

            return true;
        }
    }

    // standard event processing
    return QObject::eventFilter(obj, event);
}
