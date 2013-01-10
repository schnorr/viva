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
#include "QPajeTypeModel.h"

QPajeTypeModel::QPajeTypeModel (QPajeTypeFilter *provider, QObject *parent)
  : QAbstractItemModel (parent)
{
  this->provider = provider;
}

QPajeTypeModel::~QPajeTypeModel (void)
{
  _hiddenTypes.clear();
  _hiddenValues.clear();
}

Qt::ItemFlags QPajeTypeModel::flags(const QModelIndex &index) const
{
  if (!index.isValid()) return 0;

  Qt::ItemFlags flags = Qt::ItemIsEnabled;// | Qt::ItemIsSelectable;

  if (index.column() != 0){
    return flags;
  }

  PajeObject *object = static_cast<PajeObject*>(index.internalPointer());
  PajeType *type = dynamic_cast<PajeType*>(object);
  PajeValue *value = dynamic_cast<PajeValue*>(object);
  if (type || value){
    flags |= Qt::ItemIsUserCheckable;
  }
  return flags;
}

QVariant QPajeTypeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole){
    switch (section){
    case 0: return QVariant(QString("Name")); break;
    case 1: return QVariant(QString("Nature")); break;
    }
  }else{
    return QVariant();
  }
}

QVariant QPajeTypeModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid()){
    return QVariant();
  }

  PajeObject *object = static_cast<PajeObject*>(index.internalPointer());
  PajeType *type = dynamic_cast<PajeType*>(object);
  PajeValue *value = dynamic_cast<PajeValue*>(object);

  if (role == Qt::CheckStateRole && index.column() == 0){
    Qt::CheckState ret;
    if (typeIsHidden(type) || valueIsHidden(value)) ret = Qt::Unchecked;
    else ret = Qt::Checked;
    return static_cast<int>(ret);
  }

  if (role != Qt::DisplayRole){
    return QVariant();
  }

  if (type){
    switch (index.column()){
    case 0: return QVariant (QString::fromStdString (type->name())); break;
    case 1: return QVariant (QString::fromStdString (type->kind())); break;
    }
  }else{
    switch (index.column()){
    case 0: return QVariant (QString::fromStdString (value->name())); break;
    case 1: return QVariant (QString()); break;
    }
  }
  return QVariant();
}

bool QPajeTypeModel::setData( const QModelIndex & index, const QVariant & val, int role)
{
  PajeObject *object = static_cast<PajeObject*>(index.internalPointer());
  PajeType *type = dynamic_cast<PajeType*>(object);
  PajeValue *value = dynamic_cast<PajeValue*>(object);

  if (role == Qt::CheckStateRole && index.column() == 0){
    if (type){
      if (typeIsHidden(type)){
        showType (type);
      }else{
        hideType (type);
      }
      return true;
    }

    if (value){
      if(valueIsHidden(value)){
        showValue (value);
      }else{
        hideValue (value);
      }
      return true;
    }
  }
  return false;
}


QModelIndex QPajeTypeModel::index(int row, int column, const QModelIndex &parent) const
{
  if (!hasIndex(row, column, parent)){
    return QModelIndex();
  }

  //find the parent type based on the QModelIndex parent
  PajeType *type;
  if (parent.isValid() == false){
    type = provider->rootEntityType();
  }else{
    type = static_cast<PajeType*>(parent.internalPointer());
  }

  if (provider->isContainerType (type)){
    int i;
    std::vector<PajeType*> children = provider->containedTypes (type);
    std::vector<PajeType*>::iterator c;
    for (i = 0, c = children.begin(); c != children.end(); i++, c++){
      if (i == row) break;
    }
    return createIndex (row, column, *c);    
  }else{
    int i;
    std::vector<PajeValue*> children = provider->valuesForType (type);
    std::vector<PajeValue*>::iterator c;
    for (i = 0, c = children.begin(); c != children.end(); i++, c++){
      if (i == row) break;
    }
    return createIndex (row, column, *c);    
  }
}

QModelIndex QPajeTypeModel::parent(const QModelIndex &index) const
{
  if (index.isValid() == false){
    return QModelIndex();
  }

  PajeObject *object = static_cast<PajeObject*>(index.internalPointer());
  PajeType *type = dynamic_cast<PajeType*>(object);
  PajeType *parentType = NULL;
  if (type){
    parentType = type->parent();
  }else{
    PajeValue *value = dynamic_cast<PajeValue*>(object);
    parentType = value->type();
  }

  if (parentType == NULL){
    return QModelIndex();
  }

  if (parentType == provider->rootEntityType()){
    return createIndex (0, 0, parentType);
  }

  //search for parentType row in parentType's parent children
  PajeType *parentParentType = parentType->parent();

  int row = -1;
  std::vector<PajeType*>::iterator parentSibling;
  std::vector<PajeType*> childrenType = provider->containedTypes (parentParentType);
  for (parentSibling = childrenType.begin(); parentSibling != childrenType.end(); parentSibling++){
    if (*parentSibling == parentType){
      row = std::distance (childrenType.begin(), parentSibling);
    }
  }
  return createIndex(row, 0, parentType);
}

int QPajeTypeModel::rowCount(const QModelIndex &parent) const
{
  if (parent.isValid() == false){
    PajeType *parentType = provider->rootEntityType();
    std::vector<PajeType*> childrenType = provider->containedTypes (parentType);
    return childrenType.size();
  }

  PajeObject *object = static_cast<PajeObject*>(parent.internalPointer());
  PajeType *parentType = dynamic_cast<PajeType*>(object);
  if (parentType){
    int ret;
    if (provider->isContainerType (parentType)){
      std::vector<PajeType*> childrenType = provider->containedTypes (parentType);
      ret = childrenType.size();
    }else{
      std::vector<PajeValue*> childrenValue = provider->valuesForType (parentType);
      ret = childrenValue.size();
    }
    return ret;
  }else{
    return 0;
  }
}

int QPajeTypeModel::columnCount(const QModelIndex &parent) const
{
  return 2;
}

bool QPajeTypeModel::typeIsHidden (PajeType *type) const
{
  if (!type) return false;
  if (_hiddenTypes.count(type)) return true;
  return false;
}

bool QPajeTypeModel::valueIsHidden (PajeValue *value) const
{
  if (!value) return false;
  std::map<PajeType*,std::set<PajeValue*> >::const_iterator it;
  it = _hiddenValues.find (value->type());
  if (it != _hiddenValues.end() && (*it).second.count (value)) return true;
  else return false;
}

void QPajeTypeModel::hideType (PajeType *type)
{
  if (!type) return;
  _hiddenTypes.insert(type);
  provider->typeChanged (type);
}

void QPajeTypeModel::showType (PajeType *type)
{
  if (!type) return;
  _hiddenTypes.erase(type);
  provider->typeChanged (type);
}

void QPajeTypeModel::hideValue (PajeValue *value)
{
  if (!value) return;
  if (!_hiddenValues.count(value->type())){
    _hiddenValues[value->type()] = std::set<PajeValue*>();
  }
  _hiddenValues[value->type()].insert(value);
  provider->valueChanged (value);
}

void QPajeTypeModel::showValue (PajeValue *value)
{
  if (!value) return;
  _hiddenValues[value->type()].erase(value);
  provider->valueChanged (value);
}

std::set<PajeType*> QPajeTypeModel::hiddenTypes (void)
{
  return _hiddenTypes;
}

std::set<PajeValue*> QPajeTypeModel::hiddenValues (PajeType *type)
{
  return _hiddenValues[type];
}
