
#include"menu.h"

MainMenu::MainMenu(QWidget* parent) : QWidget(parent) { }


void MainMenu::resizeEvent(QResizeEvent* ev)
{
  QWidget::resizeEvent(ev);
  QSize  s = ev->size();
  int    H = static_cast<int>(s.height() * hcoef);
  int    W = static_cast<int>(s.width() * wcoef);
  int    N = buttons.size();

  int   x0 = (s.width() - W) / 2;
  int   y0 = (s.height() - H) / 2;

  if(N != 0) {
    int cellH = H / N;
    int cellW = W;
    int btnH  = static_cast<int>(cellH * cellHcoef);
    int vMargin = (cellH - btnH) / 2;
    int btnW  = static_cast<int>(cellW * cellWcoef);
    int hMargin = (W - btnW) / 2;

    for (int i = 0; i < N; i++) {
      int y = y0 + i * cellH + vMargin;
      int x = x0 + hMargin;
      buttons[i]->setGeometry(x, y, btnW, btnH);

      QFont f = buttons[i]->font();
      f.setPixelSize(static_cast<int>(fcoef * btnH));
      buttons[i]->setFont(f);
    }
  }
}

QVector<QPushButton*>& MainMenu::getButtons()
{
  return buttons;
}

void MainMenu::addButton(QString text)
{
  buttons.append(new QPushButton(text, this));
}