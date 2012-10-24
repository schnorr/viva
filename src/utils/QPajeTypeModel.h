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
#ifndef __PAJE_MODEL_H
#define __PAJE_MODEL_H
#include <QAbstractItemModel>
#include <PajeComponent.h>
#include "QPajeTypeFilter.h"

class QPajeTypeFilter;

class QPajeTypeModel : public QAbstractItemModel
{
  Q_OBJECT

public:
  QPajeTypeModel (QPajeTypeFilter *provider, QObject *parent = 0);
  ~QPajeTypeModel (void);

protected: //from QAbstractItemModel
  Qt::ItemFlags flags(const QModelIndex &index) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
  QVariant data(const QModelIndex &index, int role) const;
  bool setData( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
  QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
  QModelIndex parent(const QModelIndex &index) const;
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;

private:
  QPajeTypeFilter *provider;
  std::set<PajeType*> hiddenTypes;
  std::map<PajeType*,std::set<PajeValue*> > hiddenValues;

  bool typeIsHidden (PajeType *type) const;
  bool valueIsHidden (PajeValue *value) const;

  void hideType (PajeType *type);
  void showType (PajeType *type);
  void hideValue (PajeValue *value);
  void showValue (PajeValue *value);
};

#endif
