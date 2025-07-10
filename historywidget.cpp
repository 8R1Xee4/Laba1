#include "historywidget.h"

HistoryWidget::HistoryWidget(QWidget* parent)
    : QListWidget(parent)
{
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    setWindowTitle(tr("Calculation History"));
}

void HistoryWidget::closeEvent(QCloseEvent* event) {
    this->hide();
    event->ignore();
}