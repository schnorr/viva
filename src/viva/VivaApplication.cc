#include "VivaApplication.h"
#include "PajeThreadReader.h"
#include "PajeFileReader.h"
#include "PajeEventDecoder.h"
#include "PajeSimulator.h"
#include "VivaGraph.h"

VivaApplication::VivaApplication( int &argc, char **argv) : QApplication(argc,argv)
{
  setApplicationName("Viva");
  filename = arguments().at(1);
  configuration = arguments().at(2);
}

void VivaApplication::init (void)
{
  tswindow = new VTSWindow ();
  typeFilter = new QPajeTypeFilter ();

  PajeFileReader *reader = new PajeFileReader (filename.toStdString());
  PajeEventDecoder *decoder = new PajeEventDecoder ();
  PajeSimulator *simulator = new PajeSimulator ();
  VivaGraph *vivagraph = new VivaGraph (configuration.toStdString());

  connectComponents (reader, decoder);
  connectComponents (decoder, simulator);
  connectComponents (simulator, typeFilter);
  connectComponents (typeFilter, tswindow->frame);
  connectComponents (tswindow->frame, vivagraph);

  {
    PajeThreadReader *thread = new PajeThreadReader (reader);
    thread->read (); //this blocks until all file is read or user is bored
    delete thread;
  }

  simulator->report();

  VivaWindow *vivaWindow = new VivaWindow (vivagraph);
  vivaWindow->show();
  tswindow->show();
  typeFilter->show();
}

void VivaApplication::connectComponents (PajeComponent *c1, PajeComponent *c2)
{
  c1->setOutputComponent (c2);
  c2->setInputComponent (c1);
}
