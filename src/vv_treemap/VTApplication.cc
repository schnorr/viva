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
#include <VTSWindow.h>
#include <VTSFrame.h>

VTApplication::VTApplication(struct arguments *args, int &argc, char **argv) : QApplication(argc,argv)
{
  setApplicationName("vv_treemap");
  this->args = args;
}

void VTApplication::init (void)
{
  window = new VTWindow ();
  tswindow = new VTSWindow ();
  typeFilter = new QPajeTypeFilter ();

  if (args->input_size == 0){
    reader = new PajeFileReader ();
  }else{
    reader = new PajeFileReader (std::string(args->input[0]));
  }
  definitions= new PajeDefinitions(args->noStrict == 1? false : true);
  decoder = new PajeEventDecoder (definitions);
  simulator = new PajeSimulator (args->stopat, args->ignoreIncompleteLinks);

  connectComponents (reader, decoder);
  connectComponents (decoder, simulator);
  connectComponents (simulator, typeFilter);
  connectComponents (typeFilter, tswindow->frame);
  connectComponents (tswindow->frame, window->frame->widget);

  {
    PajeThreadReader *thread = new PajeThreadReader (reader);
    thread->read (); //this blocks until all file is read or user is bored
    delete thread;
  }

  window->show();
  tswindow->show();
  typeFilter->show();
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
