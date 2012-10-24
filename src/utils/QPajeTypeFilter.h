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

public: //messages from QPajeTypeModel
  void typeChanged (PajeType *type);
  void valueChanged (PajeValue *type);

protected: //Methods from PajeComponent
  void hierarchyChanged (void);

private:
  QTreeView *view;
  QPajeTypeModel *pajeTypeModel;
};

#endif
