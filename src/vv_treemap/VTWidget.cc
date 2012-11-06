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

VTWidget::VTWidget (QWidget *parent)
  : QGLWidget (QGLFormat (QGL::SampleBuffers), parent)
{
  treemap = NULL;
  currentDepth = 0;
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
  QString default_filename (tr("vv_treemap_output.pdf"));

  bool ok;
  QString text;
  if (event->modifiers() & Qt::ControlModifier){
    text = default_filename;
  }else{
    text = QInputDialog::getText(this,
                                       tr("PDF Export"),
                                       tr("Filename:"),
                                       QLineEdit::Normal,
                                       default_filename,
                                       &ok);
    if (!ok) return;
  }

  if (!text.isEmpty()){
    QPrinter printer (QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(text);
    printer.setFullPage(true);
    printer.setPaperSize(QSizeF(size().width()*4,size().height()*4), QPrinter::DevicePixel);

    QPainter painter(&printer);
    painter.scale (4,4);
    redraw (&painter);
    painter.end();

    std::cout << "Treemap printed to " << text.toStdString() << std::endl;
  }
}

void VTWidget::mouseMoveEvent(QMouseEvent *event)
{
}

void VTWidget::wheelEvent (QWheelEvent *event)
{
  if (event->delta() > 0){
    zoomIn();
  }else{
    zoomOut();
  }
  update();
}

void VTWidget::zoomIn (void)
{
  currentDepth++;
  if (currentDepth > treemap->maxDepth()) currentDepth = treemap->maxDepth();
}

void VTWidget::zoomOut (void)
{
  currentDepth--;
  if (currentDepth < 0) currentDepth = 0;
}

void VTWidget::keyPressEvent(QKeyEvent *event)
{
  if(event->key() == Qt::Key_Up){
    zoomIn();
    update();
  }else if(event->key() == Qt::Key_Down){
    zoomOut();
    update();
  }else{
    QWidget::keyPressEvent(event);
  }
}
