#include "./roomwindow.h"
#include "./mainwindow.h"
#include "./ui_mainwindow.h"
#include "./ui_roomwindow.h"

MainWindow::MainWindow(QWidget *parent) 
  : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);
    rw = new RoomWindow();

    ui->connectButton->setEnabled(TRUE);
    connect(ui->connectButton, SIGNAL(clicked()),
            this, SLOT(connectRoom()));
    
    rw->getUi()->sendArea->installEventFilter(this);
}

void MainWindow::connectRoom() {
    rw->show();
}

MainWindow::~MainWindow() {
    delete ui;
    delete rw;
}

bool MainWindow::eventFilter(QObject * obj, QEvent * event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        QString * message = new QString();

        if (keyEvent->key() == Qt::Key_Return) {
            message->append(rw->getUi()->sendArea->toPlainText());
            rw->getUi()->sendArea->clear();
            
            emit sendMessage(message);

            return true;
        }
    }

    // standard event processing
    return QObject::eventFilter(obj, event);
}
