
#include"menu.h"

MainMenu::MainMenu(QWidget* parent) : QWidget(parent)
{
    buttons.append(new QPushButton("start", this)); buttons[0]->show();
    buttons.append(new QPushButton("exit", this));  buttons[1]->show();
    buttons.append(new QPushButton("info", this));  buttons[2]->show();
}


void MainMenu::resizeEvent(QResizeEvent* ev)
{
  QWidget::resizeEvent(ev);
  QSize  s = ev->size();
  int    H = s.height();
  int    W = s.width();
  int    N = buttons.size();
  if (N == 0) return;

  // Full cell height
  int cellH = H / N;
  // Button height is coef * cellH
  int btnH  = int(cellH * wcoef);
  // Center vertically inside each cell
  int vMargin = (cellH - btnH) / 2;
  // (Optionally) you can also shrink the width by some factor:
  int btnW  = W;        // or int(W * someWidthCoef)
  int hMargin = (W - btnW) / 2;

  for (size_t i = 0; i < N; i++) {
    int y = i * cellH + vMargin;
    int x = hMargin;
    buttons[i]->setGeometry(x, y, btnW, btnH);
    QFont f = buttons[i]->font();
    f.setPixelSize(fcoef*btnH);
    buttons[i]->setFont(f);
  }
}