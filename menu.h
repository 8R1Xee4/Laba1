#ifndef MENU_H
#define MENU_H

#include<QWidget>
#include<QPushButton>
#include<QBoxLayout>
#include<QResizeEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainMenu;
}
QT_END_NAMESPACE

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    MainMenu(QWidget *parent = nullptr);
    ~MainMenu() = default;

    QVector<QPushButton*>& getButtons();
    void addButton(QString text = "");
protected:
    void resizeEvent(QResizeEvent* ev) override;

private:
    const qreal wcoef = 0.3;
    const qreal hcoef = 0.3;
    const qreal cellHcoef = 0.7;
    const qreal cellWcoef = 1;
    const qreal fcoef = 0.5;
    QVector<QPushButton*> buttons;

};

#endif // MENU_H