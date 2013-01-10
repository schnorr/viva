/*
    This file is part of Viva

    Viva is free software: you can redistribute it and/or modify
    it under the terms of the GNU Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Viva is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Public License for more details.

    You should have received a copy of the GNU Public License
    along with Viva. If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef __PAJE_TREEMAP_H
#define __PAJE_TREEMAP_H
#include <QtGui>
#include <PajeComponent.h>

class PajeTreemap
{
private:
  unsigned int d; //depth
  unsigned int maxd; //max depth

public:
  PajeContainer *container;

protected:
  double _treemapValue;
  QRectF bb;
  PajeTreemap *_parent;
  PajeComponent *filter;

public:
  PajeTreemap (PajeTreemap *parent, PajeComponent *filter, PajeContainer *container);
  void setRect (QRectF bb) { this->bb = bb; };
  unsigned int depth (void) { return d; };
  unsigned int maxDepth (void) { return maxd; };
  void setMaxDepth (unsigned int m) { maxd = m; if (_parent) _parent->setMaxDepth (m); };
  QRectF rect (void) { return bb; };
  double treemapValue (void) const { return _treemapValue; };
  virtual PajeTreemap *parent (void) const { return _parent; };
  virtual std::vector<PajeTreemap*> children (void) = 0;
  virtual std::vector<PajeTreemap*> valueChildren (void) = 0;
  virtual void timeSelectionChanged (void) {};
  virtual void calculateTreemapWithFactor (double factor) {};
  virtual PajeAggregatedType *type (void) { return NULL; };
};

class PajeTreemapValue : public PajeTreemap
{
  PajeAggregatedType *_type;

public:
  PajeTreemapValue (PajeTreemap *parent, PajeComponent *filter, PajeContainer *container, PajeAggregatedType *type, double value);
  std::vector<PajeTreemap*> children (void);
  std::vector<PajeTreemap*> valueChildren (void);
  PajeAggregatedType *type (void) { return _type; };
};


class PajeTreemapNode : public PajeTreemap
{
  PajeAggregatedDict values;
  std::vector<PajeTreemap*> _children; //PajeTreemapNode
  std::vector<PajeTreemap*> _valueChildren; //PajeTreemapValue

public:
  PajeTreemapNode (PajeTreemap *parent, PajeComponent *filter, PajeContainer *container);
  void timeSelectionChanged (void);
  void calculateTreemapWithFactor (double factor);
  std::vector<PajeTreemap*> children (void) { return _children; };
  std::vector<PajeTreemap*> valueChildren (void) { return _valueChildren; };

protected:
  double worstf (std::vector<PajeTreemap*> row, double w, double factor);
  QRectF layoutRow (std::vector<PajeTreemap*> row, double w, QRectF r, double factor);
  std::vector<PajeTreemap*> prepareChildren (std::vector<PajeTreemap*> input);
  void squarifyWithOrderedChildren (std::vector<PajeTreemap*> sorted, double w, double factor);
};

#endif
