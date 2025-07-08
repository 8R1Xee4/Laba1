#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBoxLayout>
#include <QtWidgets>
#include <QDebug>
#include "menu.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

public slots:
    void slotChangeWindow();

private:
    void initializeMainMenu();
    void initializeStack();
    void initializeMenuBar();
    void initializeApp();

    
    void connectMainMenu();
    void connectApp();

private:
    Ui::MainWindow *ui;
    MainMenu* menu;
    QWidget* app;
    QStackedWidget* stack;
    
};
#endif // MAINWINDOW_H
