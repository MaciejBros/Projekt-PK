#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "board.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QSpinBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initializeScene(int rows, int columns);
    void updateScene();

private slots:
    void updateBoardSize();
    void updateGameOfLife();

    void on_Random_clicked();

    void on_NextGen_clicked();

    void handleBoardUpdated(int,int,int);

private:
    Ui::MainWindow *ui;
    QVector<QVector<QGraphicsRectItem*>> cells;
    QGraphicsScene *scene;
    QVector<QVector<bool>> gameBoard;
    Board *m_board;
    QGraphicsRectItem* rectangle;


};
#endif // MAINWINDOW_H
