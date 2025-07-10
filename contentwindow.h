#ifndef CONTENTWINDOW_H
#define CONTENTWINDOW_H

#include <QtWidgets>
#include <QTextEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QComboBox>
#include <QFile>
#include <QTextStream>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QDebug>
#include <QListWidget>
#include <cmath>
#include "loghandler.h"
#include "historywidget.h"

class ContentWindow : public QWidget
{
    Q_OBJECT

public:
    ContentWindow(QWidget* parent = nullptr);
    ~ContentWindow();

    void write(QTextStream& out);
    void read(QTextStream& in);
    bool isModified();
    void clear();
    void setModified(bool c);

    void undo();
    void redo();
    void cut();
    void paste();
    void copy();

public slots:
    void onButtonCalculatePress();
    void onButtonShowPress();

protected:
    void initializeContentWindow();
    void connectContentWindow();
    void handle_root(qreal n, QString& entry, qreal& result, QString inp = "");
    void handle_pow(qreal n, QString& entry, qreal& result, QString inp = "");
    void handle_fact(qreal n, QString& entry, qreal& result, QString inp = "");
    void handle();
    void showList();

private:
    QStringList g_history;
    bool is_m;

    HistoryWidget*    listView;
    QComboBox*      combobox;
    QCheckBox*      checkbox_isWrite;
    QTextEdit*      textedit_input;
    QLabel*         label_output;
    QPushButton*    button_count;
    QPushButton*    button_showlist;
};


#endif // CONTENTWINDOW_H