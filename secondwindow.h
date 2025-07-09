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
#include "loghandler.h"

class SecondWindow : public QWidget
{
    Q_OBJECT

public:
    SecondWindow(QWidget* paren = nullptr);
    ~SecondWindow() = default;

public slots:


protected:


private:
    
};


#endif // SECONDWINDOW_H