/*
    This file is part of Viva.

    Viva is free software: you can redistribute it and/or modify it
    under the terms of the GNU Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Viva is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Public License for more details.

    You should have received a copy of the GNU Public License
    along with Viva. If not, see <http://www.gnu.org/licenses/>.
*/
#include <QtGui>
#include "VTWindow.h"
#include "VTFrame.h"

VTWindow::VTWindow (void)
{
  frame = new VTFrame (this);

  QHBoxLayout *mainLayout = new QHBoxLayout;
  mainLayout->setMargin(0);
  mainLayout->addWidget(frame);
  setLayout(mainLayout);
  setWindowTitle (tr("Treemap"));
}

void VTWindow::keyPressEvent(QKeyEvent *e)
{
  if (e->key() == Qt::Key_Escape){
    qApp->exit(0);
  }else{
    QWidget::keyPressEvent(e);
  }
}
