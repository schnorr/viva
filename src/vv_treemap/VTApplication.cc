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
#include "VTApplication.h"
#include "VTWindow.h"
#include "VTFrame.h"
#include "VTWidget.h"

VTApplication::VTApplication( int &argc, char **argv) : QApplication(argc,argv)
{
  setApplicationName("");
  filename.clear();
  if (arguments().count() > 1){
    filename = arguments().at(1);
  }
}

void VTApplication::init (void)
{
  window = new VTWindow ();

  if (filename.isEmpty()){
    reader = new PajeFileReader ();
  }else{
    reader = new PajeFileReader (filename.toStdString());
  }
  decoder = new PajeEventDecoder ();
  simulator = new PajeSimulator ();

  connectComponents (reader, decoder);
  connectComponents (decoder, simulator);
  connectComponents (simulator, window->frame->widget);

  {
    PajeThreadReader *thread = new PajeThreadReader (reader);
    thread->read (); //this blocks until all file is read or user is bored
    delete thread;
  }

  window->show();
}

void VTApplication::connectComponents (PajeComponent *c1, PajeComponent *c2)
{
  c1->setOutputComponent (c2);
  c2->setInputComponent (c1);
}

void VTApplication::disconnectComponents (PajeComponent *c1, PajeComponent *c2)
{
  c1->disconnectOutputComponent (c2);
  c2->disconnectFromInput ();
}
