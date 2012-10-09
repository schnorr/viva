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
#include "VivaTreemapWidget.h"

VivaTreemapWidget::VivaTreemapWidget (QWidget *parent)
  : QGLWidget (QGLFormat (QGL::SampleBuffers), parent)
{
}

VivaTreemapWidget::~VivaTreemapWidget (void)
{
}

QSize VivaTreemapWidget::minimumSizeHint() const
{
  return QSize(50, 50);
}

QSize VivaTreemapWidget::sizeHint() const
{
  return QSize(400, 400);
}


void VivaTreemapWidget::initializeGL()
{
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_MULTISAMPLE);
  static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void VivaTreemapWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glTranslatef(0.0, 0.0, -10.0);
}

void VivaTreemapWidget::resizeGL(int width, int height)
{
  int side = qMin(width, height);
  glViewport((width - side) / 2, (height - side) / 2, side, side);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
#ifdef QT_OPENGL_ES_1
  glOrthof(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
#else
  glOrtho(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
#endif
  glMatrixMode(GL_MODELVIEW);
}

void VivaTreemapWidget::mousePressEvent(QMouseEvent *event)
{
}

void VivaTreemapWidget::mouseMoveEvent(QMouseEvent *event)
{
}
