#ifndef IMGSHOWDIALOG_H
#define IMGSHOWDIALOG_H

#include <QDialog>

namespace Ui {
class ImgShowDialog;
}

class ImgShowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImgShowDialog(QWidget *parent = nullptr);
    ~ImgShowDialog();
    void showImage(const QPixmap &pix);
    void showImage(const QImage &pix);
    void showGayImage(const QPixmap &pix);
    void showGayOneImage(const QPixmap &pix);
private:
    Ui::ImgShowDialog *ui;
};

#endif // IMGSHOWDIALOG_H
