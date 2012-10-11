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
#include "VTSFrame.h"

VTSFrame::VTSFrame (QWidget *parent)
{
  startText = new QLineEdit;
  startSlider = new QSlider(Qt::Horizontal);;
  sizeText = new QLineEdit;
  sizeSlider = new QSlider(Qt::Horizontal);

  QGroupBox *startBox = new QGroupBox (tr("Time Slice Start"));
  QFormLayout *startFormLayout = new QFormLayout;
  startFormLayout->addRow(startText);
  startFormLayout->addRow (startSlider);
  startBox->setLayout (startFormLayout);

  QGroupBox *sizeBox = new QGroupBox (tr("Time Slice Size"));
  QFormLayout *sizeFormLayout = new QFormLayout;
  sizeFormLayout->addRow(sizeText);
  sizeFormLayout->addRow (sizeSlider);
  sizeBox->setLayout (sizeFormLayout);
  

  // formLayout->addRow(tr("&Size:"), sizeText);
  // formLayout->addRow (sizeSlider);
  // formLayout->setVerticalSpacing (10);


  QVBoxLayout *vbox = new QVBoxLayout;
  vbox->addWidget(startBox);
  vbox->addWidget(sizeBox);
  vbox->addWidget(new QFrame);
  setLayout(vbox);

  // //start

  // QHBoxLayout *startLayout = new QHBoxLayout;
  // startLayout->addWidget(startLabel);
  // startLayout->addWidget(startSlider);
  // startLayout->addWidget(startText);

  // //size
  // QHBoxLayout *sizeLayout = new QHBoxLayout;
  // sizeLayout->addWidget(sizeLabel);
  // sizeLayout->addWidget(sizeSlider);
  // sizeLayout->addWidget(sizeText);

  // //everything
  // QVBoxLayout *mainLayout = new QVBoxLayout;
  // mainLayout->addLayout(startLayout);
  // mainLayout->addLayout(sizeLayout);
  // setLayout(mainLayout);
  setWindowTitle(tr("VTSFrame"));
}

VTSFrame::~VTSFrame (void)
{
}

