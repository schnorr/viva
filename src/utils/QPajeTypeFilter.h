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
#ifndef QPAJE_TYPE_FILTER_H
#define QPAJE_TYPE_FILTER_H
#include <QAbstractItemModel>
#include <QWidget>
#include <PajeComponent.h>
#include "QPajeTypeModel.h"

class QTreeView;
class QPajeTypeModel;

class QPajeTypeFilter : public QWidget, public PajeComponent
{
  Q_OBJECT

public:
  QPajeTypeFilter (QWidget *parent = 0);
  ~QPajeTypeFilter (void);
  void keyPressEvent(QKeyEvent *e);

public: //messages from QPajeTypeModel
  std::vector<PajeType*> containedTypes (PajeType *type);
  std::vector<PajeValue*> valuesForType (PajeType *type);
  void typeChanged (PajeType *type);
  void valueChanged (PajeValue *type);

protected: //Methods from PajeComponent
  void hierarchyChanged (void);

public:
  std::vector<PajeType*> containedTypesForContainerType (PajeType *type);
  std::vector<PajeValue*> valuesForEntityType (PajeType *type);
  PajeAggregatedDict timeIntegrationOfTypeInContainer (PajeType *type, PajeContainer *container);
  PajeAggregatedDict integrationOfContainer (PajeContainer *container);
  PajeAggregatedDict spatialIntegrationOfContainer (PajeContainer *container);

private:
  QTreeView *view;
  QPajeTypeModel *pajeTypeModel;
  PajeAggregatedDict filterPajeAggregatedDict (PajeAggregatedDict unfiltered);
};

#endif
