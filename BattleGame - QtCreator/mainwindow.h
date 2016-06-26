#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class RenderArea;
class RenderAreaStatus;
class Game;

typedef unsigned long int DWORD;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(DWORD x, DWORD y, DWORD cRocks, DWORD cChests, QString player1Name, DWORD player1Breed, QString player2Name, DWORD player2Breed, QWidget *parent = 0);

    void keyPressEvent(QKeyEvent *);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    RenderArea *renderArea;
    RenderAreaStatus *renderAreaStatus;
    Game *game;
};


#endif // MAINWINDOW_H
