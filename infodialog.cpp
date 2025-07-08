#include "infodialog.h"
#include "ui_infodialog.h"

InfoDialog::InfoDialog(QWidget *parent)
  : QDialog(parent)
  , ui(new Ui::InfoDialog)
{
    ui->setupUi(this);

    ui->label->setText("<html><head/><body><p>Это программа для расчёта степени, факториала и корня числа. Инструкция по использованию:</p><p>1. Выберите поле для ввода и введите число.</p><p>2. Выберите в комбинированном списке что будете считать.</p><p>3. Нажмите кнопку рассчитать, результат появится в текстовом виде под кнопкой.</p></body></html>");
}

InfoDialog::~InfoDialog()
{
    delete ui;
}