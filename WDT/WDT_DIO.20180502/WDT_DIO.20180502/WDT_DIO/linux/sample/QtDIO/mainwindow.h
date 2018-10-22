#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_lineEditPortDoValue_textChanged(QString );
    void on_labelPortDoBit0_clicked();
    void on_labelPortDoBit1_clicked();
    void on_labelPortDoBit2_clicked();
    void on_labelPortDoBit3_clicked();
    void on_labelPortDoBit4_clicked();
    void on_labelPortDoBit5_clicked();
    void on_labelPortDoBit6_clicked();
    void on_labelPortDoBit7_clicked();
    void on_labelPortDoBit8_clicked();
    void on_labelPortDoBit9_clicked();
    void on_labelPortDoBitA_clicked();
    void on_labelPortDoBitB_clicked();
    void on_labelPortDoBitC_clicked();
    void on_labelPortDoBitD_clicked();
    void on_labelPortDoBitE_clicked();
    void on_labelPortDoBitF_clicked();
    void on_pushButtonPortDi_clicked();
    void on_pushButtonPortDo_clicked();
    void on_pushButtonChnDi_clicked();
    void on_pushButtonChnDo_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
