#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "board.h"
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
    void cellClicked(QGraphicsRectItem *clickedItem);

private:
    Ui::MainWindow *ui;
    QVector<QVector<QGraphicsRectItem*>> cells;
    CustomGraphicsScene *scene;  // Używamy naszej własnej klasy CustomGraphicsScene
    QVector<QVector<bool>> gameBoard;
    Board *m_board;
};

#endif // MAINWINDOW_H
