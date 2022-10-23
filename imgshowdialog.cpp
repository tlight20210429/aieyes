#include "imgshowdialog.h"
#include "ui_imgshowdialog.h"

ImgShowDialog::ImgShowDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImgShowDialog)
{
    ui->setupUi(this);

}

ImgShowDialog::~ImgShowDialog()
{
    delete ui;
}

void ImgShowDialog::showImage(const QPixmap &pix)
{
    ui->lab_image->setPixmap(pix);
}

void ImgShowDialog::showImage(const QImage &pix)
{
    QPixmap mp;
    mp = mp.fromImage(pix);
    ui->lab_image->setPixmap(mp);
}

void ImgShowDialog::showGayImage(const QPixmap &pix)
{

}

void ImgShowDialog::showGayOneImage(const QPixmap &pix)
{

}
