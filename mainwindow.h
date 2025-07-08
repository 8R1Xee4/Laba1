#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBoxLayout>
#include <QtWidgets>
#include <QDebug>
#include <QDialog>
#include "menu.h"
#include "infodialog.h"
#include "loghandler.h"

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
    void slotStartButton();
    void slotInfoButton();
    void slotExitButton();

protected:
    void initializeLogHandler();
    void initializeMainWindow();
    void initializeMainMenu();
    void initializeStack();
    void initializeMenuBar();
    void initializeApp();


    void connectMainMenu();
    void connectApp();


    void closeEvent(QCloseEvent *ev);

    void showAppInfo();
    void onExit();


private:
    bool canClose;

    Ui::MainWindow *ui;
    MainMenu* menu;
    QWidget* app;
    QStackedWidget* stack;
    
};
#endif // MAINWINDOW_H
