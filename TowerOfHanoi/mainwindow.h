#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "renderarea.h"
#include <QInputDialog>
#include <QShortcut>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    void solution(int, int, int, int);
    ~MainWindow();
    
private slots:
    void on_newGameButton_clicked();

    void on_undoButton_clicked();

    void on_redoButton_clicked();

    void on_solutionButton_clicked();

private:
    Ui::MainWindow *ui;
    RenderArea *renderArea;
    TowerOfHanoi *obj;
};

#endif // MAINWINDOW_H
