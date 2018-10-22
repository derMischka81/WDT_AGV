#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QTimer*  timer;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Append(const QString &text);

private slots:
    void on_timer();
    void on_pushButtonStart_clicked();
    void on_pushButtonStop_clicked();
    void on_pushButtonSend_clicked();

signals:
    void AppendText(const QString &text);

private slots:
    void SlotAppendText(const QString &text);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
