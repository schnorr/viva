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
#include "VTWidget.h"
#include "EntropyDialog.h"

VTWidget::VTWidget (QWidget *parent)
  : QGLWidget (QGLFormat (QGL::SampleBuffers), parent)
{
  treemap = NULL;
  currentDepth = 0;
  setFocusPolicy (Qt::StrongFocus);
  entropyP = 0.3;
  entropyVariable = NULL;
}

VTWidget::~VTWidget (void)
{
  delete treemap;
}

QSize VTWidget::minimumSizeHint() const
{
  return QSize(50, 50);
}

QSize VTWidget::sizeHint() const
{
  return QSize(400, 400);
}

void VTWidget::resizeEvent (QResizeEvent *event)
{
  repopulate();
}

void VTWidget::paintEvent(QPaintEvent *event)
{
  QBrush whiteBackground = QBrush(QColor(255, 255, 255));

  QPainter painter;
  painter.begin(this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.fillRect(event->rect(), whiteBackground);
  redraw (&painter);
  painter.end();
}

void VTWidget::mousePressEvent(QMouseEvent *event)
{
}

void VTWidget::mouseMoveEvent(QMouseEvent *event)
{
}

void VTWidget::wheelEvent (QWheelEvent *event)
{
  if (event->delta() > 0){
    currentDepth++;
    if (currentDepth > treemap->maxDepth()) currentDepth = treemap->maxDepth();
  }else{
    currentDepth--;
    if (currentDepth < 0) currentDepth = 0;
  }
  update();
}

void VTWidget::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_E){
    rootInstance()->computeGainDivergence(selectionStartTime(), selectionEndTime());

    bool ok = false;
    EntropyDialog dialog (spatialIntegrationOfContainer(rootInstance()), entropyP, entropyVariable, this);
    dialog.exec();
    entropyP = dialog.p();
    entropyVariable = dialog.type();
    if (dialog.result() == QDialog::Accepted && entropyVariable){
      std::cout << "Considering a p: " << entropyP << " and variable: " << entropyVariable->description() << std::endl;
      std::pair<double,std::vector<PajeContainer*> > bestAgg = findBestAggregation (rootInstance(), entropyVariable, entropyP);
      std::cout << "-> maxRIC = " << bestAgg.first << std::endl;
      std::vector<PajeContainer*>::iterator it;
      std::cout << "-> bestAgg = {";
      for (it = bestAgg.second.begin(); it != bestAgg.second.end(); it++){
        PajeContainer *c = *it;
        std::cout << c->name() << ", ";
      }
      std::cout << "}" << std::endl;
    }else{
      std::cout << "dialog was rejected" << std::endl;
    }
  }else{
    QWidget::keyPressEvent(event);
  }
}
