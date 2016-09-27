#include "mainwindow.h"
#include "ui_mainwindow.h"

void delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::solution(int n, int origin, int middle, int destination)
{
    if (n)
    {
       solution(n - 1, origin, destination, middle);
       obj->moveDisk(origin, destination);
       renderArea->update();
       delay();
       solution(n - 1, middle, origin, destination);
   }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    obj = new TowerOfHanoi(7);
    ui->setupUi(this);
    renderArea = new RenderArea(obj, ui->undoButton, ui->redoButton, this);
    ui->verticalLayout->addWidget(renderArea);
    ui->undoButton->setShortcut(Qt::CTRL + Qt::Key_Z);
    ui->redoButton->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_Z);
    ui->newGameButton->setShortcut(Qt::Key_Return);
    new QShortcut(Qt::Key_Enter, this, SLOT(on_newGameButton_clicked()));
    setWindowTitle(tr("Tower of Hanoi"));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete obj;
}

void MainWindow::on_newGameButton_clicked()
{
    bool ok;
    int n_Disks = QInputDialog::getInt(this, tr(""), tr("Number of disks:"), 3, 3, 7, 1, &ok);
    if (ok)
    {
        delete obj;
        obj = new TowerOfHanoi(n_Disks);
        renderArea->setTowerOfHanoi(obj);
    }
}

void MainWindow::on_undoButton_clicked()
{
    obj->undo();
    renderArea->update();
}

void MainWindow::on_redoButton_clicked()
{
    obj->redo();
    renderArea->update();
}

void MainWindow::on_solutionButton_clicked()
{
    int n_Disks = obj->getN_Disk();
//    delete obj;
//    obj = new TowerOfHanoi(n_Disks);
//    renderArea->setTowerOfHanoi(obj);
    delay();
    solution(n_Disks, 0, 1 , 2);
}
