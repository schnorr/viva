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
#include <PajeComponent.h>
#include "PajeTreemap.h"
#include "EntropyConfigurationWidget.h"

class EntropyConfigurationWidget;

class VTWidget : public QGLWidget, public PajeComponent
{
  Q_OBJECT

public:
  VTWidget (QWidget *parent = 0);
  ~VTWidget (void);

  QSize minimumSizeHint (void) const;
  QSize sizeHint (void) const;

public slots:
  void updateEntropyData (void);

protected:
  void mousePressEvent (QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void resizeEvent (QResizeEvent *event);
  void wheelEvent (QWheelEvent *event);
  void paintEvent(QPaintEvent *event);
  void keyPressEvent(QKeyEvent *event);

protected: //from PajeComponent protocol
  void hierarchyChanged (void);
  void timeSelectionChanged (void);
  void dataChangedForEntityType (PajeType *type);

public slots:
  void recomputeGainDivergence (void);

private:
  EntropyConfigurationWidget *entropyConfigurationWidget;
  PajeTreemapNode *treemap;
  int currentDepth;
  void zoomIn (void);
  void zoomOut (void);
  enum {GlobalZoom, LocalZoom, EntropyZoom} zoomType;

  //entropy properties
  std::pair<double,std::vector<PajeContainer*> > bestAggregation;

protected: //myself
  void drawTreemap (QPainter *painter, PajeTreemap *treemap);
  void drawChildrensBorder (QPainter *painter, PajeTreemap *treemap);
  void recreate (void);
  void repopulate (void);
  void redraw (QPainter *painter);
};

#endif
