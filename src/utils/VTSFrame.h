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
#ifndef __VTS_FRAME_H
#define __VTS_FRAME_H
#include <QFrame>
#include <PajeComponent.h>

class QLabel;
class QSlider;
class QLineEdit;

class VTSFrame : public QFrame, public PajeComponent
{
  Q_OBJECT

public:
  VTSFrame (QWidget *parent = 0);
  ~VTSFrame (void);

private:
  QLabel *startLabel;
  QSlider *startSlider;
  QLineEdit *startText;

  QLabel *sizeLabel;
  QSlider *sizeSlider;
  QLineEdit *sizeText;

  QLabel *forwardLabel;
  QSlider *forwardSlider;
  QLineEdit *forwardText;

  QLabel *frequencyLabel;
  QSlider *frequencySlider;
  QLineEdit *frequencyText;
};

#endif
