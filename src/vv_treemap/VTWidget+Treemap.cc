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
  }else{
    painter->drawRect (t->rect());
    //aggregated children
    std::vector<PajeTreemap*> valueChildren = t->valueChildren();
    for (it = valueChildren.begin(); it != valueChildren.end(); it++){
      PajeColor *color = (*it)->type()->color();
      QBrush brush = QBrush (QColor (color->r*255, color->g*255, color->b*255, color->a*255));
      painter->fillRect ((*it)->rect(), brush);
    }
  }
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
    this->recreate (); //to create something to populate
  }

  QSize s = size();
  std::cout << "Size: " << s.width() << " " << s.height() << std::endl;
  QRectF bb = QRectF(QPointF(0,0), s);

  treemap->setRect (bb);
  treemap->calculateTreemapWithFactor ((bb.width() * bb.height())/treemap->treemapValue());
}

void VTWidget::redraw (QPainter *painter)
{
  drawTreemap (painter, treemap);
}
