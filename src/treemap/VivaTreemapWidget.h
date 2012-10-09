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
#ifndef __VIVA_TREEMAP_WIDGET_H
#define __VIVA_TREEMAP_WIDGET_H
#include <QGLWidget>

class VivaTreemapWidget : public QGLWidget
{
  Q_OBJECT

public:
  VivaTreemapWidget (QWidget *parent = 0);
  ~VivaTreemapWidget (void);

  QSize minimumSizeHint (void) const;
  QSize sizeHint (void) const;

protected:
  void initializeGL (void);
  void paintGL (void);
  void resizeGL (int width, int height);
  void mousePressEvent (QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
};

#endif
