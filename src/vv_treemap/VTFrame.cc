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
#include <QtGui>
#include "VTFrame.h"
#include "VTWidget.h"

VTFrame::VTFrame (QWidget *parent)
  : QFrame(parent)
{
  setFrameStyle(Plain | NoFrame);
  widget = new VTWidget (this);
  QBoxLayout *topLayout = new QBoxLayout (QBoxLayout::TopToBottom, this);
  topLayout->setMargin(0);
  topLayout->addWidget (widget);
  setLayout (topLayout);
}

VTFrame::~VTFrame (void)
{
}

void VTFrame::showEvent ( QShowEvent * event )
{
}

void VTFrame::resizeEvent ( QResizeEvent * event )
{
}
