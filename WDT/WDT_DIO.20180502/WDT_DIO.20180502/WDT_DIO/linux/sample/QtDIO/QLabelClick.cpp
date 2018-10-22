#include "QLabelClick.h"

QLabelClick::QLabelClick(QWidget *parent, Qt::WindowFlags f)
    : QLabel(parent, f)
{
    // NOOP
}

QLabelClick::QLabelClick(const QString &text, QWidget *parent, Qt::WindowFlags f)
    : QLabel(text, parent, f)
{
    // NOOP
}

QLabelClick::~QLabelClick()
{
    // NOOP
}

void QLabelClick::mousePressEvent(QMouseEvent*)
{
    emit clicked();
}
