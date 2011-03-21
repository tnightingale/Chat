#include "roomwindow.h"
#include "ui_roomwindow.h"
#include "../core/Message.h"
#include <QFileDialog>

RoomWindow::RoomWindow(QString name) : QWidget(0), ui(new Ui::RoomWindow) {
    ui->setupUi(this);
    ui->sendArea->installEventFilter(this);
    ui->rommName->setText(name);
    setWindowTitle(name);
    QObject::connect(ui->saveLog, SIGNAL(clicked()), this, SLOT(saveFile()));
}

RoomWindow::~RoomWindow() {
    delete ui;
}

void RoomWindow::saveFile() {
    QString saveFile = QFileDialog::getSaveFileName(this, tr("Save Log"), "",
                                                    tr("Text Files (*.txt)"));
    QFile file(saveFile);

    if (!file.open( QIODevice::WriteOnly | QIODevice::Append )) {
        qDebug("Failed to open file.");
        return;
    }

    QTextStream ts(&file);
    ts << ui->roomLog->toPlainText();
    file.close();
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
