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

EntropyDialog::EntropyDialog (PajeAggregatedDict variables,
                              double startingP,
                              PajeAggregatedType *startingType,
                              QWidget *parent)
  : QDialog (parent)
{
  pInput = new QLineEdit;
  pInput->setValidator (new QDoubleValidator(0, 1, 4, pInput));
  QString str;
  str.setNum(startingP);
  pInput->setText (str);
  typeGroupBox = new QGroupBox (tr("Variable"));

  QVBoxLayout *vbox = new QVBoxLayout;

  //fill typeInput
  PajeAggregatedDict::iterator it;
  for (it = variables.begin(); it != variables.end(); it++){
    PajeAggregatedType *type = (*it).first;
    QString str = QString::fromStdString(type->description());
    QRadioButton *button = new QRadioButton (str);
    if (startingType == NULL){
      if (it == variables.begin()) button->setChecked(true);
    }else{
      if (type->description() == startingType->description()){
        button->setChecked (true);
      }
    }
    vbox->addWidget (button);
    button_to_type[button] = type;
  }
  typeGroupBox->setLayout (vbox);

  cancelButton = new QPushButton (tr("Cancel"));
  okButton = new QPushButton (tr("Ok"));

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget (pInput);
  layout->addWidget (typeGroupBox);
  QHBoxLayout *hbox = new QHBoxLayout;
  hbox->addWidget (cancelButton);
  hbox->addWidget (okButton);
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
