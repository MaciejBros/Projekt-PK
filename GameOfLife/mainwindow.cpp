#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QGraphicsScene>
#include <QSpinBox>
#include <QGraphicsRectItem>
#include <QRandomGenerator>
#include "board.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int defaultRows = 17;
    int defaultColumns = 19;
    ui->spinBoxHeight->setValue(defaultRows);
    ui->spinBoxWidth->setValue(defaultColumns);

    scene = new QGraphicsScene(this);
    initializeScene(defaultRows, defaultColumns);


    ui->okno->setScene(scene);

     gameBoard.resize(defaultRows, QVector<bool>(defaultColumns, false));
     updateScene();

     connect(ui->spinBoxWidth, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::updateBoardSize);
     connect(ui->spinBoxHeight, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::updateBoardSize);
     connect(m_board, &Board::boardUpdated(int arg1,int arg2,int arg3)), this, &MainWindow::handleBoardUpdated(int arg1,int arg2,int arg3));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeScene(int rows, int columns)
{
    scene->clear();
    cells.clear();
    int targetRow = 7, targetCol = 3;

    // Inicjalizuj tablicę (dodaj komórki do sceny)
    for (int row = 0; row < rows; ++row) {
        QVector<QGraphicsRectItem*> rowCells;
        for (int col = 0; col < columns; ++col) {
            QGraphicsRectItem *cell = new QGraphicsRectItem(col * 30, row * 30, 30, 30);
            QBrush blackBrush(Qt::red);
            cell->setBrush(blackBrush);
            //cell->setBrush(QBrush(Qt::red));
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

    // Board brd(rows,columns);
    // m_board = &brd;

    initializeScene(rows, columns);

    // Zmiana rozmiaru planszy
    gameBoard.resize(rows, QVector<bool>(columns, false));
    updateScene();


}

void MainWindow::updateGameOfLife() {
    // Tu możesz zaimplementować logikę gry w życie (ewentualnie jako oddzielna metoda)
    // W tej wersji losujemy nowy stan dla każdej komórki



    for (int row = 0; row < gameBoard.size(); row++) {
        for (int col = 0; col < gameBoard[row].size(); col++) {
            gameBoard[row][col] = QRandomGenerator::global()->bounded(2) == 1;
        }
    }

    updateScene();
}

void MainWindow::updateScene() {
    // Aktualizuj kolory komórek na podstawie planszy gry

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
                    cell->setBrush(QBrush(Qt::red));
                }
            }
        }
    }

}




void MainWindow::on_Random_clicked()
{
    //m_board->set_random();
    //updateScene();
}


void MainWindow::on_NextGen_clicked()
{

}

void MainWindow::handleBoardUpdated(int,int,int)
{
    qDebug() << "dupa";
}
