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
#include "QPajeTypeFilter.h"
#include <QtGui>
#include <QPushButton>

QPajeTypeFilter::QPajeTypeFilter (QWidget *parent)
{
  pajeTypeModel = new QPajeTypeModel (this);
  view = new QTreeView;
  view->setModel (pajeTypeModel);
  view->header()->setResizeMode(QHeaderView::ResizeToContents);

  QVBoxLayout *layout = new QVBoxLayout ();
  layout->addWidget (view);
  setLayout (layout);
}

QPajeTypeFilter::~QPajeTypeFilter (void)
{
}

void QPajeTypeFilter::hierarchyChanged (void)
{
  view->expandAll ();
  PajeComponent::hierarchyChanged ();
}

void QPajeTypeFilter::typeChanged (PajeType *type)
{
  PajeComponent::hierarchyChanged ();
}

void QPajeTypeFilter::valueChanged (PajeValue *value)
{
  PajeComponent::dataChangedForEntityType (value->type());
}
