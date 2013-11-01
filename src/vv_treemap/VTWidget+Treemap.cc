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

  if (t->depth() < currentDepth){
    //just recurse on normal children
    std::vector<PajeTreemap*> children = t->children();
    for (it = children.begin(); it != children.end(); it++){
      PajeTreemap *child = *it;
      this->drawTreemap (painter, child);
    }

    //draw children's border
    if (t->depth() < currentDepth){
      drawChildrensBorder (painter, t);
    }

  }else{
    //aggregated children
    std::vector<PajeTreemap*> valueChildren = t->valueChildren();
    for (it = valueChildren.begin(); it != valueChildren.end(); it++){
      PajeColor *color = (*it)->type()->color();
      if (!color){
	std::cout << "There is no color defined for type " << (*it)->type()->name() << std::endl;
	exit(1);
      }
      QBrush brush = QBrush (QColor (color->r*255, color->g*255, color->b*255, color->a*255));
      painter->fillRect ((*it)->rect(), brush);
    }
  }
}

void VTWidget::drawChildrensBorder (QPainter *painter, PajeTreemap *treemap)
{
  QPainterPath childrenBorderPath;
  std::vector<PajeTreemap*>::iterator it;
  std::vector<PajeTreemap*> children = treemap->children();
  for (it = children.begin(); it != children.end(); it++){
    PajeTreemap *child = *it;
    childrenBorderPath.addRect (child->rect());
  }

  QPen pen = QPen();
  int max = treemap->maxDepth() - 1;
  pen.setWidthF(max - treemap->depth());
  int childDepth = treemap->depth() + 1;
  if (max%2){
    //max depth is odd
    if (childDepth%2){
      //childDepth is odd
      pen.setColor(Qt::black);
    }else{
      //childDepth is even
      pen.setColor(Qt::white);
    }
  }else{
    //max depth is even
    if (childDepth%2){
      //childDepth is odd
      pen.setColor(Qt::white);
    }else{
      //childDepth is even
      pen.setColor(Qt::black);
    }
  }
  double width = treemap->maxDepth() - treemap->depth() - 1;
  pen.setWidthF (width);
  painter->setPen (pen);
  painter->drawPath (childrenBorderPath);
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
