#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QGraphicsScene>
#include <QSpinBox>
#include <QGraphicsRectItem>
#include <QRandomGenerator>
#include <QDebug>
#include "board.h"

CustomGraphicsScene::CustomGraphicsScene(QObject *parent)
    : QGraphicsScene(parent)
{
}

void CustomGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
    QGraphicsRectItem *clickedItem = qgraphicsitem_cast<QGraphicsRectItem*>(item);

    if (clickedItem) {
        emit cellClicked(clickedItem);
    }

    QGraphicsScene::mousePressEvent(event);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int defaultRows = 15;
    int defaultColumns = 15;

    ui->spinBoxHeight->setValue(defaultRows);
    ui->spinBoxWidth->setValue(defaultColumns);

    scene = new CustomGraphicsScene(this);
    initializeScene(defaultRows, defaultColumns);

    ui->okno->setScene(scene);

    gameBoard.resize(defaultRows, QVector<bool>(defaultColumns, false));
    updateScene();

    connect(ui->spinBoxWidth, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::updateBoardSize);
    connect(ui->spinBoxHeight, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::updateBoardSize);

    connect(scene, &CustomGraphicsScene::cellClicked, this, &MainWindow::cellClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeScene(int rows, int columns)
{
    scene->clear();
    cells.clear();

    for (int row = 0; row < rows; ++row) {
        QVector<QGraphicsRectItem*> rowCells;
        for (int col = 0; col < columns; ++col) {
            QGraphicsRectItem *cell = new QGraphicsRectItem(col * 30, row * 30, 30, 30);

            QBrush blackBrush(Qt::red);
            cell->setBrush(blackBrush);

            cell->setAcceptHoverEvents(true);
            cell->setFlag(QGraphicsItem::ItemIsSelectable);

            scene->addItem(cell);
            rowCells.push_back(cell);
        }
        cells.push_back(rowCells);
    }
}

void MainWindow::updateBoardSize()
{
    int rows = ui->spinBoxHeight->value();
    int columns = ui->spinBoxWidth->value();

    initializeScene(rows, columns);
    gameBoard.resize(rows, QVector<bool>(columns, false));
    updateScene();
}

void MainWindow::updateGameOfLife()
{
    for (int row = 0; row < gameBoard.size(); row++) {
        for (int col = 0; col < gameBoard[row].size(); col++) {
            gameBoard[row][col] = QRandomGenerator::global()->bounded(2) == 1;
        }
    }

    updateScene();
}

void MainWindow::updateScene()
{
    QList<QGraphicsItem *> items = scene->items();
    for (int i = 0; i < items.size(); ++i) {
        QGraphicsRectItem *cell = qgraphicsitem_cast<QGraphicsRectItem *>(items.at(i));
        if (cell) {
            int row = cell->y() / 30;
            int col = cell->x() / 30;

            if (gameBoard.size() > row && gameBoard[row].size() > col) {
                if (gameBoard[row][col]) {
                    cell->setBrush(QBrush(Qt::black));
                } else {
                    cell->setBrush(QBrush(Qt::white));
                }
            }
        }
    }
}

void MainWindow::cellClicked(QGraphicsRectItem *clickedItem)
{
    int row = clickedItem->y() / 30;
    int col = clickedItem->x() / 30;

    if (gameBoard.size() > row && gameBoard[row].size() > col) {
        gameBoard[row][col] = !gameBoard[row][col];

        if (gameBoard[row][col]) {
            clickedItem->setBrush(QBrush(Qt::black));
        } else {
            clickedItem->setBrush(QBrush(Qt::white));
        }
    }
}

void MainWindow::on_Random_clicked()
{
    updateGameOfLife();
}

void MainWindow::on_NextGen_clicked()
{
    // Implementacja logiki dla kolejnej generacji
}

void MainWindow::handleBoardUpdated(int,int,int)
{
    qDebug() << "dupa";
}
