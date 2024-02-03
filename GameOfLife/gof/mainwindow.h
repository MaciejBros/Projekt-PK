#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "board.h"
//#include "gamecontroller.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QSpinBox>
#include <QPushButton>
#include <QGraphicsSceneMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class CustomGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    CustomGraphicsScene(QObject *parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void cellClicked(QGraphicsRectItem *clickedItem);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Board& brd, QWidget *parent = nullptr);
    ~MainWindow();

    void initializeScene(int rows, int columns);
    void updateScene();

private slots:
    void updateBoardSize();
    void updateGameOfLife();
    void on_Random_clicked();
    void on_NextGen_clicked();
    void cellClicked(QGraphicsRectItem *clickedItem);
    void NextGen();

    void on_Apply_clicked();

    void on_set_dimensions_clicked();

private:
    Ui::MainWindow *ui;
    QVector<QVector<QGraphicsRectItem*>> cells;
    CustomGraphicsScene *scene;
    QVector<QVector<bool>> gameBoard;
    bool** board = nullptr;
    Board *m_board;
    //GameController* cntrl;
    int m_numCols = 0;
    int m_numRows = 0;;
};

#endif // MAINWINDOW_H
