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
    QObject::connect(ui->sendArea, SIGNAL(textChanged()),
                     this, SLOT(checkTextBox()));
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

void RoomWindow::checkTextBox() {
    if (ui->sendArea->toPlainText().length() > 250) {
        QString text = ui->sendArea->toPlainText();
        text.truncate(250);
        ui->sendArea->setText(text);
    }
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
