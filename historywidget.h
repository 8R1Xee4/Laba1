#ifndef HISTORYWIDGET_H
#define HISTORYWIDGET_H

#include <QListWidget>
#include <QCloseEvent>

class HistoryWidget : public QListWidget {
  Q_OBJECT
public:
    HistoryWidget(QWidget* parent = nullptr);
    ~HistoryWidget() = default;

protected:
    void closeEvent(QCloseEvent* event);
};

#endif // HISTORYWIDGET_H