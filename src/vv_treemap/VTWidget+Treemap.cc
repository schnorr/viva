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

void VTWidget::drawTreemap (QPainter *painter, PajeTreemap *t)
{

  std::vector<PajeTreemap*>::iterator it;

//GlobalZoom
  if (zoomType == GlobalZoom){
    if (t->depth() < currentDepth){
      //just recurse on normal children
      std::vector<PajeTreemap*> children = t->children();
      for (it = children.begin(); it != children.end(); it++){
        PajeTreemap *child = *it;
        this->drawTreemap (painter, child);
      }
    }else{
      //aggregated children
      std::vector<PajeTreemap*> valueChildren = t->valueChildren();
      for (it = valueChildren.begin(); it != valueChildren.end(); it++){
        PajeColor *color = (*it)->type()->color();
        QBrush brush = QBrush (QColor (color->r*255, color->g*255, color->b*255, color->a*255));
        painter->fillRect ((*it)->rect(), brush);
      }
    }

//EntropyZoom
  }else if (zoomType == EntropyZoom){
    std::vector<PajeContainer*>::iterator found = std::find (bestAggregation.second.begin(), bestAggregation.second.end(), t->container);
    if (found == bestAggregation.second.end()){

      //just recurse on normal children
      std::vector<PajeTreemap*> children = t->children();
      for (it = children.begin(); it != children.end(); it++){
        PajeTreemap *child = *it;
        this->drawTreemap (painter, child);
      }

    }else{

  // std::cout << "Drawing " << t->container->name() << std::endl;

      //aggregated children
      std::vector<PajeTreemap*> valueChildren = t->valueChildren();
      for (it = valueChildren.begin(); it != valueChildren.end(); it++){
        PajeColor *color = (*it)->type()->color();
        QBrush brush = QBrush (QColor (color->r*255, color->g*255, color->b*255, color->a*255));
        painter->fillRect ((*it)->rect(), brush);
      }

    }
  }  


  QPen pen = QPen();
  if (t->depth() >= 1){
    pen.setWidth (treemap->maxDepth() - t->depth());
    painter->setPen (pen);
  }
  painter->drawRect (t->rect());

}

void VTWidget::recreate (void)
{
  if (treemap){
    delete treemap;
  }
  treemap = new PajeTreemapNode (NULL, this, rootInstance());
}

void VTWidget::repopulate (void)
{
  if (!treemap){
    throw "nothing to repopulate";
  }

  if (selectionEndTime() - selectionStartTime() != 0){
    QSize s = size();
    QRectF bb = QRectF(QPointF(0,0), s);
    treemap->setRect (bb);
    treemap->calculateTreemapWithFactor ((bb.width() * bb.height())/treemap->treemapValue());
  }
}

void VTWidget::redraw (QPainter *painter)
{
  if (treemap->treemapValue()){
    drawTreemap (painter, treemap);
  }else{
    painter->drawText (QPointF(10,height()-10), tr("Nothing to draw"));
  }
}
