#include "roomwindow.h"
#include "ui_roomwindow.h"
#include "../core/Message.h"

RoomWindow::RoomWindow(QString name) : QWidget(0), ui(new Ui::RoomWindow) {
    ui->setupUi(this);
    ui->sendArea->installEventFilter(this);
    ui->rommName->setText(name);
    setWindowTitle(name);
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

            emit sendMessage(message, ui->rommName->text());

            return true;
        }
    }

    // standard event processing
    return QObject::eventFilter(obj, event);
}
