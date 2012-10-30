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
#ifndef __ENTROPY_DIALOG_H
#define __ENTROPY_DIALOG_H
#include <QWidget>
#include <PajeType.h>
#include "VTWidget.h"

class QLineEdit;
class QSlider;
class QGroupBox;
class QPushButton;
class QRadioButton;
class QCheckBox;
class VTWidget;

class EntropyConfigurationWidget : public QWidget
{
  Q_OBJECT;

public:
  EntropyConfigurationWidget (double startingP, VTWidget *treemap);
  ~EntropyConfigurationWidget (void);

private:
  VTWidget *treemap;

  QLineEdit *pInput;
  QSlider *pSlider;
  QGroupBox *pGroupBox;
  QGroupBox *typeGroupBox;
  QVBoxLayout *typeGroupBoxLayout;
  QCheckBox *debugCheckBox;
  std::map<QRadioButton*,PajeAggregatedType*> button_to_type;

public:
  double p (void);
  PajeAggregatedType *type (void);
  void updateVariables (PajeAggregatedDict variables);
  bool showDebugMessages (void);

public slots:
  void pSliderMoved (int value);
  void pInputEditFinished (void);
};

#endif
