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
#ifndef VT_APPLICATION_H
#define VT_APPLICATION_H
#include <Qt>
#include <QtGui>
#include "PajeThreadReader.h"
#include "PajeFileReader.h"
#include "PajeEventDecoder.h"
#include "PajeSimulator.h"
#include <QPajeTypeFilter.h>

class VTWindow;
class VTSWindow;

class VTApplication : public QApplication
{
  Q_OBJECT;
  
private:
  PajeFileReader *reader;
  PajeEventDecoder *decoder;
  PajeSimulator *simulator;
  QPajeTypeFilter *typeFilter;

  VTWindow *window;
  VTSWindow *tswindow;
  QString filename;
  void disconnectComponents (PajeComponent *c1, PajeComponent *c2);
  void connectComponents (PajeComponent *c1, PajeComponent *c2);

public:
  VTApplication (int &argc, char **argv);
  void init (void);
};
#endif
