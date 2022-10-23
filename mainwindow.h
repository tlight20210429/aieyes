#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include "imgshowdialog.h"

#define GAY_LEVEL   256

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    enum Shape{Scatter=256, LineSeries, BarSeries, PieSeries};
    Q_ENUM(Shape)
    void showImHist(QImage *img, bool picType, int n);
    void imHistLineAdjust(QImage *img, int n, double fa, double fb, bool showPic);
    void drawScatter(qreal *dataX, qreal *dataY, int count);
    void drawLineSeries(qreal *dataX, qreal *dataY, int count);
    void drawBarSeries(qreal *dataX, qreal *dataY, int count);
    void drawPieSeries(qreal *dataX, qreal *dataY, int count);
private slots:
    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    QChart *m_ptrChart;
    ImgShowDialog *m_imgShow;
    qreal m_gayLevelY[GAY_LEVEL];
    qreal m_gayLevelX[GAY_LEVEL];
};
#endif // MAINWINDOW_H
