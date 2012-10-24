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
#include <boost/foreach.hpp>

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

std::vector<PajeType*> QPajeTypeFilter::containedTypes (PajeType *type)
{
  return PajeComponent::containedTypesForContainerType (type);
}

std::vector<PajeValue*> QPajeTypeFilter::valuesForType (PajeType *type)
{
  return PajeComponent::valuesForEntityType (type);
}

void QPajeTypeFilter::typeChanged (PajeType *type)
{
  PajeComponent::hierarchyChanged ();
}

void QPajeTypeFilter::valueChanged (PajeValue *value)
{
  PajeComponent::dataChangedForEntityType (value->type());
}

std::vector<PajeType*> QPajeTypeFilter::containedTypesForContainerType (PajeType *type)
{
  std::vector<PajeType*> ret;
  std::set<PajeType*> hidden = pajeTypeModel->hiddenTypes();
  BOOST_FOREACH(PajeType *type, containedTypes(type)){
    if (!hidden.count(type)){
      ret.push_back(type);
    }
  }
  return ret;
}

std::vector<PajeValue*> QPajeTypeFilter::valuesForEntityType (PajeType *type)
{
  return valuesForType (type);

  std::vector<PajeValue*> ret;
  std::set<PajeValue*> hidden = pajeTypeModel->hiddenValues(type);
  BOOST_FOREACH(PajeValue *value, valuesForType(type)){
    if (!hidden.count(value)){
      ret.push_back(value);
    }
  }
  return ret;
}

PajeAggregatedDict QPajeTypeFilter::filterPajeAggregatedDict (PajeAggregatedDict unfiltered)
{
  PajeAggregatedDict ret;
  BOOST_FOREACH (PajeAggregatedDictEntry entry, unfiltered){
    PajeAggregatedType *aggtype = entry.first;
    PajeType *type = aggtype->type();
    PajeValue *value = aggtype->value();

    //check if type is hidden
    if (!pajeTypeModel->hiddenTypes().count (type)){
      //check if value is hidden
      if (!pajeTypeModel->hiddenValues(type).count(value)){
        ret.insert (entry);
      }
    }
  }
  return ret;
}

PajeAggregatedDict QPajeTypeFilter::timeIntegrationOfTypeInContainer (PajeType *type, PajeContainer *container)
{
  return filterPajeAggregatedDict(PajeComponent::timeIntegrationOfTypeInContainer (type, container));
}

PajeAggregatedDict QPajeTypeFilter::integrationOfContainer (PajeContainer *container)
{
  return filterPajeAggregatedDict (PajeComponent::integrationOfContainer (container));
}

PajeAggregatedDict QPajeTypeFilter::spatialIntegrationOfContainer (PajeContainer *container)
{
  return filterPajeAggregatedDict (PajeComponent::spatialIntegrationOfContainer (container));
}

void QPajeTypeFilter::keyPressEvent(QKeyEvent *e)
{
  if (e->key() == Qt::Key_Escape){
    qApp->exit(0);
  }else{
    QWidget::keyPressEvent(e);
  }
}
