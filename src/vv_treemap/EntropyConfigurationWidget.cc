/*
    This file is part of Viva.

    Viva is free software: you can redistribute it and/or modify it
    under the terms of the GNU Public License as published by
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
#include <QFormLayout>
#include "EntropyConfigurationWidget.h"
#include <boost/foreach.hpp>
#include <limits>

EntropyConfigurationWidget::EntropyConfigurationWidget (double startingP, VTWidget *treemap)
{
  this->treemap = treemap;

  /* configuring the p group */
  pInput = new QLineEdit;
  pInput->setValidator (new QDoubleValidator(0, 1, 4, pInput));
  connect (pInput, SIGNAL(editingFinished()),
           this, SLOT(pInputEditFinished()));
  QString str;
  str.setNum(startingP);
  pInput->setText (str);
  pSlider = new QSlider (Qt::Horizontal);
  pSlider->setMinimum (0);
  pSlider->setMaximum (std::numeric_limits<int>::max());
  pSlider->setSliderPosition (startingP * std::numeric_limits<int>::max());
  connect (pSlider, SIGNAL(sliderMoved(int)),
           this, SLOT(pSliderMoved(int)));

  QVBoxLayout *pGroupBoxLayout = new QVBoxLayout;
  pGroupBoxLayout->addWidget (pSlider);
  pGroupBoxLayout->addWidget (pInput);
  pGroupBox = new QGroupBox (tr("P"));
  pGroupBox->setLayout (pGroupBoxLayout);

  /* configure the type group */
  typeGroupBoxLayout = new QVBoxLayout;
  typeGroupBox = new QGroupBox (tr("Variable"));
  typeGroupBox->setLayout (typeGroupBoxLayout);

  /* configure miscelaneous group */
  debugCheckBox = new QCheckBox (tr("Debug messages"));
  debugCheckBox->setChecked (true);
  QHBoxLayout *miscGroupBoxLayout = new QHBoxLayout;
  miscGroupBoxLayout->addWidget (debugCheckBox);
  QGroupBox *miscGroupBox = new QGroupBox (tr("Miscelaneous"));
  miscGroupBox->setLayout (miscGroupBoxLayout);

  /* put everything together */
  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget (pGroupBox);
  layout->addWidget (typeGroupBox);
  layout->addWidget (miscGroupBox);

  /* set layout */
  setLayout (layout);
  setWindowTitle (tr("Entropy configuration"));
}

bool EntropyConfigurationWidget::showDebugMessages (void)
{
  return debugCheckBox->isChecked();
}

EntropyConfigurationWidget::~EntropyConfigurationWidget (void)
{
  delete pInput;
  delete typeGroupBox;
}

double EntropyConfigurationWidget::p (void)
{
  return pInput->text().toDouble();
}

PajeAggregatedType *EntropyConfigurationWidget::type (void)
{
  PajeAggregatedType *type;
  std::map<QRadioButton*,PajeAggregatedType*>::iterator it;
  for (it = button_to_type.begin(); it != button_to_type.end(); it++){
    if ((*it).first->isChecked()) return (*it).second;
  }
  return NULL;
}

void EntropyConfigurationWidget::updateVariables (PajeAggregatedDict variables)
{
  // clear existing layout and buttons
  QLayoutItem *child;
  while ((child = typeGroupBoxLayout->takeAt(0)) != 0) {
    delete child->widget();
    delete child;
  }
  button_to_type.clear();

  //fill new layout and buttons
  PajeAggregatedType *startingType = NULL;
  int flag = 0;
  BOOST_FOREACH (PajeAggregatedDictEntry entry, variables){
    PajeAggregatedType *type = entry.first;
    QString str = QString::fromStdString(type->description());
    QRadioButton *button = new QRadioButton (str, typeGroupBox);
    if (startingType == NULL){
      if (flag == 0){
        button->setChecked(true);
        flag = 1;
      }
    }else{
      if (type->description() == startingType->description()){
        button->setChecked (true);
      }
    }
    typeGroupBoxLayout->addWidget (button);
    button_to_type[button] = type;
    connect (button, SIGNAL(clicked()), treemap, SLOT(updateEntropyData()));
  }
  typeGroupBox->setLayout (typeGroupBoxLayout);
}

void EntropyConfigurationWidget::pSliderMoved (int value)
{
  double x = (double)value / std::numeric_limits<int>::max();
  pInput->setText (QString::number(x));
  treemap->updateEntropyData();
}

void EntropyConfigurationWidget::pInputEditFinished (void)
{
  pSlider->setSliderPosition (p() * std::numeric_limits<int>::max());
  treemap->updateEntropyData();
}
