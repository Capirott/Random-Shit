#include "configdialog.h"
#include "ui_configdialog.h"
#include "mainwindow.h"
#include "Class/Pieces/Targets/breed.h"


ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDialog)
{
    ui->setupUi(this);
    setFixedSize(250, 300);
    setWindowTitle("New Game");
}

ConfigDialog::~ConfigDialog()
{
    delete ui;
}

void ConfigDialog::on_startButton_clicked()
{
    DWORD   x                 = ui->rowsSpinBox->value();
    DWORD   y                 = ui->columnSpinBox->value();
    DWORD   cChests           = ui->chestsSpinBox->value();
    DWORD   cRocks            = ui->rocksSpinBox->value();
    QString player1Name       = ui->player1NameLineEdit->text();
    DWORD   player1Breed      = ui->player1BreedBox->currentIndex();
    QString player2Name       = ui->player2NameLineEdit->text();
    DWORD   player2Breed      = ui->player2BreedBox->currentIndex();

    if (cChests + cRocks <=  x * y - 2)
    {
        MainWindow *w = new MainWindow(x, y, cRocks, cChests, player1Name, player1Breed, player2Name, player2Breed);
        w->show();
        close();
    }
}
