#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "renderarea.h"
#include "Class/game.h"
#include <QKeyEvent>
#include <QApplication>
#include <iostream>
#include "Class/Pieces/Targets/breed.h"
#include "renderareastatus.h"

MainWindow::MainWindow(DWORD x, DWORD y, DWORD cRocks, DWORD cChests, QString player1Name, DWORD player1Breed, QString player2Name, DWORD player2Breed, QWidget *parent)
        :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    game = 0;
    ui->setupUi(this);
    renderArea = new RenderArea(this);
    ui->verticalLayout->addWidget(renderArea);
    Character player1;

    switch(player1Breed)
    {
    case 0:
        player1 = ROGUE;
        break;
    case 1:
        player1 = BARBARIAN;
        break;
    case 2:
        player1 = TROLL;
        break;
    case 3:
        player1 = URUKHAI;
        break;
    }

    Character player2;
    switch(player2Breed)
    {
    case 0:
        player2 = ROGUE;
        break;
    case 1:
        player2 = BARBARIAN;
        break;
    case 2:
        player2 = TROLL;
        break;
    case 3:
        player2 = URUKHAI;
        break;
    }
    Game::newGame(x, y, cRocks, cChests, player1Name.toStdString(), player1, player2Name.toStdString(), player2);
    game = Game::getGame();
    renderArea->setGame(game);
    renderAreaStatus = new RenderAreaStatus(game, this);
    ui->horizontalLayout->addWidget(renderAreaStatus);
    this->showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == 16777216)
    {
        this->close();
    }
    if (game)
    {
        int key = e->key();
        if (key == 'W' || key == 'A' || key == 'S' || key == 'D')
        {   //~ Player 1 Move
            game->player[0]->move(e->key());
        }
        else
        {
            if (key > 16777233 && key < 16777238)
            {   //~ Player 2 Move
                key %= 10;
                switch (key)
                {
                case 4:
                    game->player[1]->move('A');
                    break;
                case 5:
                    game->player[1]->move('W');
                    break;
                case 6:
                    game->player[1]->move('D');
                    break;
                case 7:
                    game->player[1]->move('S');
                    break;
                default:
                    break;
                }
            }
            else
            {
                if (key == 'Q' || key == 'E')
                {   //~ Player 1 Attack
                    game->player[0]->attack((key == 'Q' ? 'L' : 'R'));
                }
                else
                {
                    if (key == '1' || key == '2')
                    {   //~ Player 2 Attack
                        game->player[1]->attack((key == '1' ? 'L' : 'R'));
                    }
                    else
                    {
                        if (key == 'F')
                        {   //~ Player 1 openChest
                            game->player[0]->openChest();
                        }
                        else
                        {
                            if (key == '0')
                            {   //~ Player 2 openChest
                                game->player[1]->openChest();
                            }
                            else
                            {
                                if (key == 'R')
                                {   //~ Player 1 use Potion
                                    game->player[0]->usePotion();
                                }
                                else
                                {
                                    if (key == '3')
                                    {   //~ Player 2 usePotion
                                        game->player[1]->usePotion();
                                    }
                                    else
                                    {
                                        if (key == 'X')
                                        {   //~ Player 1 Block
                                            game->player[0]->block();
                                        }
                                        else
                                        {
                                            if (key == '4')
                                            {   //~ Player 2 Block
                                                game->player[1]->block();
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        renderArea->update();
        renderAreaStatus->update();
    }
}

