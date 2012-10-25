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
#include "EntropyDialog.h"
#include <boost/foreach.hpp>
#include <limits>

EntropyDialog::EntropyDialog (PajeAggregatedDict variables,
                              double startingP,
                              PajeAggregatedType *startingType,
                              QWidget *parent)
  : QDialog (parent)
{
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
  pGroupBoxLayout->addWidget (new QWidget());
  pGroupBox = new QGroupBox (tr("P"));
  pGroupBox->setLayout (pGroupBoxLayout);

  /* configure the type group */
  QVBoxLayout *typeGroupBoxLayout = new QVBoxLayout;
  //fill typeInput
  int flag = 0;
  BOOST_FOREACH (PajeAggregatedDictEntry entry, variables){
    PajeAggregatedType *type = entry.first;
    QString str = QString::fromStdString(type->description());
    QRadioButton *button = new QRadioButton (str);
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
  }
  typeGroupBox = new QGroupBox (tr("Variable"));
  typeGroupBox->setLayout (typeGroupBoxLayout);

  /* configure the bottom */
  cancelButton = new QPushButton (tr("Cancel"));
  okButton = new QPushButton (tr("Ok"));
  QHBoxLayout *hbox = new QHBoxLayout;
  hbox->addWidget (cancelButton);
  hbox->addWidget (okButton);

  /* put everything together */
  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget (pGroupBox);
  layout->addWidget (typeGroupBox);
  layout->addLayout (hbox);

  setLayout (layout);
  setWindowTitle (tr("Entropy configuration"));

  connect (cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
  connect (okButton, SIGNAL(clicked()), this, SLOT(accept()));
}

EntropyDialog::~EntropyDialog (void)
{
  delete pInput;
  delete typeGroupBox;
  delete cancelButton;
  delete okButton;
}

double EntropyDialog::p (void)
{
  return pInput->text().toDouble();
}

PajeAggregatedType *EntropyDialog::type (void)
{
  PajeAggregatedType *type;
  std::map<QRadioButton*,PajeAggregatedType*>::iterator it;
  for (it = button_to_type.begin(); it != button_to_type.end(); it++){
    if ((*it).first->isChecked()) return (*it).second;
  }
  return NULL;
}

void EntropyDialog::pSliderMoved (int value)
{
  double x = (double)value / std::numeric_limits<int>::max();
  pInput->setText (QString::number(x));
}

void EntropyDialog::pInputEditFinished (void)
{
  pSlider->setSliderPosition (p() * std::numeric_limits<int>::max());
}
