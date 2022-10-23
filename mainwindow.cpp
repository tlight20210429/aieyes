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
    ui->comboBox->setCurrentIndex(0);
    m_ptrChart = new QChart;
    ui->graphicsView->setChart(m_ptrChart);
    m_ptrChart->setTitle("灰度直方图");
    m_ptrChart->setDropShadowEnabled(false);
    m_ptrChart->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);
    m_ptrChart->setTheme(QChart::ChartThemeLight);
    QPixmap pix = QPixmap("E:/OldProject/images/coins.png");
    m_imgShow->showImage(pix);
    m_imgShow->setWindowTitle("原始图像");
    m_imgShow->show();
    QImage img = QImage("E:/OldProject/images/coins.png");
 //   showImHist(&img, false, 64);
  //  imHistLineAdjust(&img, 64, 2, -55, true);
  //  imHistLineAdjust(&img, 64, 0.5, -55, true);
    imHistLineAdjust(&img, 64, 1, 55, true);
  //  imHistLineAdjust(&img, 64, -1, 255, true);
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
 * @param n: 将256级灰度重新分配为n级，0 < n <= 256
 */
void MainWindow::showImHist(QImage *img, bool picType, int n)
{
    int i, j, k, xLen;
    int size;
    double level[2];
    for(i = 0; i < GAY_LEVEL; i++)
        m_gayLevelY[i] = 0;
    //统计每个灰度级出现次数
    xLen = 0;
    for(i = 0; i < img->height(); i++){
        const uchar *line = img->constScanLine(i);
        for(j = 0; j < img->width(); j++){
            for(k = 0; k < n; k++){
                level[0] = 255*(k+1-1.5)/(n-1);
                level[1] = 255*(k+1-0.5)/(n-1);
                if(line[j] >= level[0] && line[j] < level[1]){
                    m_gayLevelY[k]++;
                    break;
                }
            }
        }
    }
    for(k = 0; k < n; k++){
        level[0] = 255*(k+1-1.5)/(n-1);
        level[1] = 255*(k+1-0.5)/(n-1);
        if(xLen == 0){
            m_gayLevelX[xLen++] = level[0]+level[1];
        }else if(xLen < n){
            m_gayLevelX[xLen++] = level[0]*2;
            m_gayLevelX[xLen++] = level[0]+level[1];
        }
    }
    if(picType){
        size = img->width()*img->height();
        for(i = 0; i < GAY_LEVEL; i++)
            m_gayLevelY[i] /= size;
    }
    switch(ui->comboBox->currentIndex()){
        case 0: drawScatter(m_gayLevelX, m_gayLevelY, n); break;
        case 1: drawLineSeries(m_gayLevelX, m_gayLevelY, n); break;
        case 2: drawBarSeries(m_gayLevelX, m_gayLevelY, n); break;
        case 3: drawPieSeries(m_gayLevelX, m_gayLevelY, n); break;
    }
}
/**
 * @brief MainWindow::imHistLineAdjust 灰度线性变换
 * @param img: 输入的灰度图像
 * @param n: 将256级灰度重新分配为n级，0 < n <= 256
 * @param fa: 线性变换斜率, fa > 1:对比度增大，fa < 1:对比度减小，fa=1且fb!=0时，图像所有像素灰度上移或下移，结果是图像变亮或变暗。fa=-1且fb=255时，灰度反转，结果是图像反相
 * @param fb: 线性变换截距
 */
void MainWindow::imHistLineAdjust(QImage *img, int n, double fa, double fb, bool showPic)
{
    int i, j, k, xLen;
    int size;
    double level[2];
    for(i = 0; i < GAY_LEVEL; i++)
        m_gayLevelY[i] = 0;
    //统计每个灰度级出现次数
    xLen = 0;
    for(i = 0; i < img->height(); i++){
        uchar *line = img->scanLine(i);
        for(j = 0; j < img->width(); j++){
            line[j] = fa*line[j]+fb;
            for(k = 0; k < n; k++){
                level[0] = 255*(k+1-1.5)/(n-1);
                level[1] = 255*(k+1-0.5)/(n-1);
                if(line[j] >= level[0] && line[j] < level[1]){
                    m_gayLevelY[k]++;
                    break;
                }
            }
        }
    }
    for(k = 0; k < n; k++){
        level[0] = 255*(k+1-1.5)/(n-1);
        level[1] = 255*(k+1-0.5)/(n-1);
        if(xLen == 0){
            m_gayLevelX[xLen++] = level[0]+level[1];
        }else if(xLen < n){
            m_gayLevelX[xLen++] = level[0]*2;
            m_gayLevelX[xLen++] = level[0]+level[1];
        }
    }
    size = img->width()*img->height();
    for(i = 0; i < GAY_LEVEL; i++){
        m_gayLevelY[i] /= size;
    }
    if(showPic){
        ImgShowDialog *imgShow = new ImgShowDialog();
        imgShow->showImage(*img);
        imgShow->setWindowTitle("fa=2");
        imgShow->show();
    }
    switch(ui->comboBox->currentIndex()){
        case 0: drawScatter(m_gayLevelX, m_gayLevelY, n); break;
        case 1: drawLineSeries(m_gayLevelX, m_gayLevelY, n); break;
        case 2: drawBarSeries(m_gayLevelX, m_gayLevelY, n); break;
        case 3: drawPieSeries(m_gayLevelX, m_gayLevelY, n); break;
    }
}
/*!
    @Function    : Name
    @Description : 详细描述
    @Author      : Kevin
    @Parameter   : 参数说明
    @Return      : 返回值说明
    @Output      :
    @Call by     :
    @Date        : 2022-10-23 18:38:36
    @Modify      : 日期加修改描述
*/
void MainWindow::drawScatter(qreal *dataX, qreal *dataY, int count)
{
    int i;
    m_ptrChart->removeAllSeries();
    QScatterSeries *mptrScatterSeries = new QScatterSeries();
    mptrScatterSeries->setName("gay");
    for(i = 0; i < count; i++)
        mptrScatterSeries->append(dataX[i], dataY[i]);
    mptrScatterSeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    mptrScatterSeries->setMarkerSize(8);
    m_ptrChart->addSeries(mptrScatterSeries);
    m_ptrChart->createDefaultAxes();
}

void MainWindow::drawLineSeries(qreal *dataX, qreal *dataY, int count)
{
    int i;
    m_ptrChart->removeAllSeries();
    QLineSeries *mptrScatterSeries = new QLineSeries();
    mptrScatterSeries->setName("gay");
    for(i = 0; i < count; i++)
        mptrScatterSeries->append(dataX[i], dataY[i]);
    m_ptrChart->addSeries(mptrScatterSeries);
    m_ptrChart->createDefaultAxes();
}

void MainWindow::drawBarSeries(qreal *dataX, qreal *dataY, int count)
{

}

void MainWindow::drawPieSeries(qreal *dataX, qreal *dataY, int count)
{

}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{

}

