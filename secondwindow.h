#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

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
#include <cmath>
#include "loghandler.h"

class SecondWindow : public QWidget
{
    Q_OBJECT

public:
    SecondWindow(QWidget* parent = nullptr);
    ~SecondWindow() = default;

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
    void onButtonPress();

protected:
    void initializeSecondWindow();
    void connectSecondWindow();
    void calculate();

private:
    QComboBox*      combobox;
    QCheckBox*      checkbox_isWrite;
    QTextEdit*      textedit_input;
    QLabel*         label_output;
    QPushButton*    button_count;
};


#endif // SECONDWINDOW_H