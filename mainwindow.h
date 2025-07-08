#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QBoxLayout>
#include"menu.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void resizeEvent(QResizeEvent* ev) override;

private:
    const qreal menuWSize = 0.3;
    const qreal menuHSize = 0.3;
    Ui::MainWindow *ui;
    MainMenu* menu;
};
#endif // MAINWINDOW_H
