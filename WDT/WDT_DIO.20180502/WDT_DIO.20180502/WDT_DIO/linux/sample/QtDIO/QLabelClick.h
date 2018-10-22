#ifndef QLABELCLICK_H
#define QLABELCLICK_H

#include <qlabel.h>

class QLabelClick : public QLabel
{
    Q_OBJECT

public:
    explicit QLabelClick(QWidget *parent=0, Qt::WindowFlags f=0);
    explicit QLabelClick(const QString &text, QWidget *parent=0, Qt::WindowFlags f=0);
    ~QLabelClick();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // QLABELCLICK_H
