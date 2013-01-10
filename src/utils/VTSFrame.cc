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
#include <climits>
#include "VTSFrame.h"

VTSFrame::VTSFrame (QWidget *parent)
{
  selectionStart = -1;
  selectionEnd = -1;

  //infobox
  QGroupBox *infoBox = new QGroupBox (tr("Trace Time"));
  QHBoxLayout *infoBoxLayout = new QHBoxLayout;
  startTimeLabel = new QLabel ();
  endTimeLabel = new QLabel ();
  infoBoxLayout->addWidget (new QLabel(tr("Start")));
  infoBoxLayout->addWidget (startTimeLabel);
  infoBoxLayout->addWidget (new QLabel(tr("End")));
  infoBoxLayout->addWidget (endTimeLabel);
  infoBox->setLayout (infoBoxLayout);

  //startbox
  startText = new QLineEdit;
  startText->setValidator (new QDoubleValidator);
  startSlider = new QSlider(Qt::Horizontal);;
  startSlider->setTracking (false);
  startSlider->setMaximum (INT_MAX);
  startSlider->setValue (0);
  startCheck = new QCheckBox ();

  QGroupBox *startBox = new QGroupBox (tr("Time Slice Start"));
  QFormLayout *startFormLayout = new QFormLayout;
  startFormLayout->addRow(startText);
  QHBoxLayout *startSliderBox = new QHBoxLayout ();
  startSliderBox->addWidget(startSlider);
  startSliderBox->addWidget(startCheck);
  startFormLayout->addRow (startSliderBox);
  startBox->setLayout (startFormLayout);

  //sizebox
  sizeText = new QLineEdit;
  sizeText->setValidator (new QDoubleValidator);
  sizeSlider = new QSlider(Qt::Horizontal);
  sizeSlider->setTracking (false);
  sizeSlider->setMaximum (INT_MAX);
  sizeSlider->setValue (INT_MAX);
  sizeCheck = new QCheckBox ();

  QGroupBox *sizeBox = new QGroupBox (tr("Time Slice Size"));
  QFormLayout *sizeFormLayout = new QFormLayout;
  sizeFormLayout->addRow(sizeText);
  QHBoxLayout *sizeSliderBox = new QHBoxLayout ();
  sizeSliderBox->addWidget(sizeSlider);
  sizeSliderBox->addWidget(sizeCheck);
  sizeFormLayout->addRow (sizeSliderBox);
  sizeBox->setLayout (sizeFormLayout);

  QVBoxLayout *vbox = new QVBoxLayout;
  vbox->addWidget(infoBox);
  vbox->addWidget(startBox);
  vbox->addWidget(sizeBox);
  setLayout(vbox);

  //signals
  connect (startSlider, SIGNAL(sliderMoved(int)),
           this, SLOT(startSliderMoved(int)));
  connect (startSlider, SIGNAL(valueChanged(int)),
           this, SLOT(startSizeSliderReleased(int)));
  connect (startCheck, SIGNAL(stateChanged(int)),
           this, SLOT(startCheckChanged(int)));

  connect (sizeSlider, SIGNAL(sliderMoved(int)),
           this, SLOT(sizeSliderMoved(int)));
  connect (sizeSlider, SIGNAL(valueChanged(int)),
           this, SLOT(startSizeSliderReleased(int)));
  connect (sizeCheck, SIGNAL(stateChanged(int)),
           this, SLOT(sizeCheckChanged(int)));

  //misc
  setWindowTitle(tr("VTSFrame"));
}

VTSFrame::~VTSFrame (void)
{
}

void VTSFrame::startSliderMoved (int value)
{
  double trace_time = endTime() - startTime();
  double selected = (double)value/(double)INT_MAX;
  QString valueAsString = QString::number (trace_time*selected);
  startText->setText (valueAsString);
}

void VTSFrame::startCheckChanged (int state)
{
  if (startCheck->checkState() == Qt::Checked){
    startSlider->setTracking (true);
  }else{
    startSlider->setTracking (false);
  }
}

void VTSFrame::sizeSliderMoved (int value)
{
  double max_size = endTime() - selectionStartTime();
  double selected = (double)value/(double)INT_MAX;
  QString valueAsString = QString::number (max_size*selected);
  sizeText->setText (valueAsString);
}

void VTSFrame::sizeCheckChanged (int state)
{
  if (sizeCheck->checkState() == Qt::Checked){
    sizeSlider->setTracking (true);
  }else{
    sizeSlider->setTracking (false);
  }
}

void VTSFrame::startSizeSliderReleased (int value)
{
  double selected_start = (double)startSlider->value()/(double)INT_MAX;
  double selected_size = (double)sizeSlider->value()/(double)INT_MAX;
  double start = endTime() * selected_start;
  double size = (endTime() - start) * selected_size;
  setSelectionStartEndTime (start, start+size);
}

void VTSFrame::timeSelectionChanged (void)
{
  selectionStart = selectionStartTime();
  selectionEnd = selectionEndTime();
  updateGUI();
  PajeComponent::timeSelectionChanged();
}

void VTSFrame::timeLimitsChanged (void)
{
  updateGUI();
  PajeComponent::timeLimitsChanged ();
}

void VTSFrame::setSelectionStartEndTime (double start, double end)
{
  selectionStart = start;
  selectionEnd = end;
  PajeComponent::setSelectionStartEndTime (start, end);
}

double VTSFrame::selectionStartTime (void)
{
  if (selectionStart > 0){
    return selectionStart;
  }else{
    return PajeComponent::selectionStartTime ();
  }
}

double VTSFrame::selectionEndTime (void)
{
  if (selectionEnd > 0){
    return selectionEnd;
  }else{
    return PajeComponent::selectionEndTime ();
  }
}

void VTSFrame::updateGUI (void)
{
  //trace time
  startTimeLabel->setText (QString::number(startTime()));
  endTimeLabel->setText (QString::number(endTime()));

  //time slice
  startText->setText (QString::number(selectionStartTime()));
  sizeText->setText (QString::number(selectionEndTime() - selectionStartTime()));
}
