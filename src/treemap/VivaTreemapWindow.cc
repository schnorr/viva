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
#include "VivaTreemapWindow.h"
#include "VivaTreemapWidget.h"

VivaTreemapWindow::VivaTreemapWindow (void)
{
  treemapWidget = new VivaTreemapWidget (this);

  QHBoxLayout *mainLayout = new QHBoxLayout;
  mainLayout->addWidget(treemapWidget);
  setLayout(mainLayout);
  setWindowTitle (tr("Treemap"));
}

void VivaTreemapWindow::keyPressEvent(QKeyEvent *e)
{
  if (e->key() == Qt::Key_Escape)
    close();
  else
    QWidget::keyPressEvent(e);
}
