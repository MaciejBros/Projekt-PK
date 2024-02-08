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

    if (clickedItem)
    {
        emit cellClicked(clickedItem);
    }

    QGraphicsScene::mousePressEvent(event);
}

MainWindow::MainWindow(Board& brd, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->NextGen->setEnabled(false);
    ui->Random->setEnabled(false);
    ui->set_dimensions->setEnabled(false);

    m_numRows = 15;
    m_numCols = 15;

    m_board = &brd;

    ui->spinBoxHeight->setValue(m_numRows);
    ui->spinBoxWidth->setValue(m_numCols);

    scene = new CustomGraphicsScene(this);
    initializeScene(m_numRows, m_numCols);

    ui->okno->setScene(scene);

    gameBoard.resize(m_numRows, QVector<bool>(m_numCols, false));
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

    bool** tempBoard = nullptr;
    tempBoard = new bool* [rows];
    for (int i = 0; i < rows; i++)
    {
        tempBoard[i] = new bool[columns];
    }


    for (int i = 0; i < rows; i++)
    {
        QVector<QGraphicsRectItem*> rowCells;
        for (int j = 0; j < columns; j++)
        {
            QGraphicsRectItem *cell = new QGraphicsRectItem(j * 30, i * 30, 30, 30);
            tempBoard[i][j] = cell;
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
    m_numRows = ui->spinBoxHeight->value();
    m_numCols = ui->spinBoxWidth->value();
    initializeScene(m_numRows, m_numCols);
    gameBoard.resize(m_numRows, QVector<bool>(m_numCols, false));
    updateScene();
}

void MainWindow::updateGameOfLife()
{
    qDebug() << "Coumns: " << m_numCols<< "Rows" << m_numRows;
    bool** tempBoard = nullptr;
    tempBoard = new bool* [m_numRows];
    for (int i = 0; i < m_numRows; i++)
    {
        tempBoard[i] = new bool[m_numCols];
    }

    tempBoard = m_board->GetGameBoard();

    for (int rows = 0; rows < m_numRows; rows++)
    {
        for (int cols = 0; cols < m_numCols; cols++)
        {

            QGraphicsRectItem * cell = cells[rows][cols];
             qDebug() << cols << " " << rows;
            if (tempBoard[rows][cols] == true)
                {
                    cell->setBrush(QBrush(Qt::black));
                }
                else
                {
                    cell->setBrush(QBrush(Qt::white));
                }
        }
    }
}

void MainWindow::updateScene()
{

    QList<QGraphicsItem *> items = scene->items();
    for (int i = 0; i < items.size(); ++i)
    {
        QGraphicsRectItem *cell = qgraphicsitem_cast<QGraphicsRectItem *>(items.at(i));
        if (cell)
        {
            int row = cell->y();
            int col = cell->x();
            if (gameBoard.size() > row && gameBoard[row].size() > col)
            {
                if (gameBoard[row][col]) cell->setBrush(QBrush(Qt::black));
                else cell->setBrush(QBrush(Qt::white));
            }
        }
    }
}

void MainWindow::NextGen()
{

    bool** tempBoard = nullptr;
    tempBoard = new bool* [m_numRows];
    for (int i = 0; i < m_numRows; i++)
    {
        tempBoard[i] = new bool[m_numCols];
    }
    m_board->NextGeneration();

    tempBoard = m_board->GetGameBoard();

    for (int rows = 0; rows < m_numRows ; rows++)
    {
        for (int cols = 0; cols < m_numCols; cols++)
        {
            QGraphicsRectItem * cell = cells[rows][cols];
            if (tempBoard[rows][cols] == true)
            {
                cell->setBrush(QBrush(Qt::black));
            }
            else
            {
                cell->setBrush(QBrush(Qt::white));
            }
        }
    }
}

void MainWindow::cellClicked(QGraphicsRectItem *clickedItem)
{

}

void MainWindow::on_Random_clicked()
{
    m_board->set_random();
    updateGameOfLife();

}

void MainWindow::on_NextGen_clicked()
{
    NextGen();
}


void MainWindow::on_Apply_clicked()
{
    ui->spinBoxHeight->setEnabled(false);
    ui->spinBoxWidth->setEnabled(false);
    ui->Apply->setEnabled(false);
    m_board->realocateBoard(m_numCols, m_numRows);
    qDebug() << "cols: " << m_numCols << " rows: " << m_numRows;
    ui->NextGen->setEnabled(true);
    ui->Random->setEnabled(true);
    ui->set_dimensions->setEnabled(true);
}


void MainWindow::on_set_dimensions_clicked()
{
    ui->NextGen->setEnabled(false);
    ui->Random->setEnabled(false);
    ui->set_dimensions->setEnabled(false);
    ui->spinBoxHeight->setEnabled(true);
    ui->spinBoxWidth->setEnabled(true);
    ui->Apply->setEnabled(true);
}

