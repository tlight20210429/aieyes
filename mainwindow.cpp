#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_imgShow = new ImgShowDialog(this);
    ui->comboBox->addItem("散点图", Scatter);
    ui->comboBox->addItem("折线图", LineSeries);
    ui->comboBox->addItem("柱形图", BarSeries);
    ui->comboBox->addItem("饼图", PieSeries);
    m_ptrChart = new QChart;
    ui->graphicsView->setChart(m_ptrChart);
    m_ptrChart->setTitle("灰度直方图");
    m_ptrChart->setDropShadowEnabled(false);
    m_ptrChart->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);
    m_ptrChart->setTheme(QChart::ChartThemeLight);
    QPixmap pix = QPixmap("E:/OldProject/images/gay.tif");
    m_imgShow->showImage(pix);
    m_imgShow->show();
    QImage img = QImage("E:/OldProject/images/gay.tif");
    showImHist(&img, true);
}

MainWindow::~MainWindow()
{
    delete m_ptrChart;
    delete ui;
}
/**
 * @brief MainWindow::showImHist
 * @param img: 要显示灰度直方图的图片
 * @param picType: false普通直方图，true归一化直方图
 */
void MainWindow::showImHist(QImage *img, bool picType)
{
    int i, j;
    int size;

    for(i = 0; i < GAY_LEVEL; i++)
        m_gayLevel[i] = 0;
    //统计每个灰度级出现次数
    for(i = 0; i < img->height(); i++){
        const uchar *line = img->constScanLine(i);
        for(j = 0; j < img->width(); j++){
            m_gayLevel[line[j]]++;
        }
    }
    if(picType){
        size = img->width()*img->height();
        for(i = 0; i < GAY_LEVEL; i++)
            m_gayLevel[i] /= size;
    }
    switch(1){
        case 0: drawScatter(m_gayLevel, GAY_LEVEL); break;
        case 1: drawLineSeries(m_gayLevel, GAY_LEVEL); break;
        case 2: drawBarSeries(m_gayLevel, GAY_LEVEL); break;
        case 3: drawPieSeries(m_gayLevel, GAY_LEVEL); break;
    }
}

void MainWindow::drawScatter(qreal *data, int count)
{
    int i;
    m_ptrChart->removeAllSeries();
    QScatterSeries *mptrScatterSeries = new QScatterSeries();
    mptrScatterSeries->setName("gay");
    for(i = 0; i < count; i++)
        mptrScatterSeries->append(i, data[i]);
    mptrScatterSeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    mptrScatterSeries->setMarkerSize(8);
    m_ptrChart->addSeries(mptrScatterSeries);
    m_ptrChart->createDefaultAxes();
}

void MainWindow::drawLineSeries(qreal *data, int count)
{
    int i;
    m_ptrChart->removeAllSeries();
    QLineSeries *mptrScatterSeries = new QLineSeries();
    mptrScatterSeries->setName("gay");
    for(i = 0; i < count; i++){
        mptrScatterSeries->append(i, data[i]);
    }
    m_ptrChart->addSeries(mptrScatterSeries);
    m_ptrChart->createDefaultAxes();
}

void MainWindow::drawBarSeries(qreal *data, int count)
{

}

void MainWindow::drawPieSeries(qreal *data, int count)
{

}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{

}

