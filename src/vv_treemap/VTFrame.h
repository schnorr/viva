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
#ifndef __VIVA_TREEMAP_FRAME_H
#define __VIVA_TREEMAP_FRAME_H
#include <QFrame>

class VTWidget;

class VTFrame : public QFrame
{
  Q_OBJECT;
public:
  VTFrame (QWidget *parent = 0);
  ~VTFrame (void);

protected:
  void showEvent (QShowEvent *event);
  void resizeEvent (QResizeEvent *event);

public:
  VTWidget *widget;
};

#endif
