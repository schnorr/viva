/*
    This program is free software: you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <string>
#include <iostream>
#include <exception>
#include "PajeFileReader.h"
#include "PajeEventDecoder.h"
#include "PajeSimulator.h"
#include <argp.h>

#define VALIDATE_INPUT_SIZE 2
static char doc[] = "Dumps the <paje.trace> file in a CSV-like textual format";
static char args_doc[] = "<paje.trace>";

static struct argp_option options[] = {
  { 0 }
};

struct arguments {
  char *input[VALIDATE_INPUT_SIZE];
  int input_size;
};

static int parse_options (int key, char *arg, struct argp_state *state)
{
  struct arguments *arguments = (struct arguments*)(state->input);
  switch (key){
  case ARGP_KEY_ARG:
    if (arguments->input_size == VALIDATE_INPUT_SIZE) {
      /* Too many arguments. */
      argp_usage (state);
    }
    arguments->input[state->arg_num] = arg;
    arguments->input_size++;
    break;
  case ARGP_KEY_END:
    if (state->arg_num < 1) {
      /* Not enough arguments. */
      argp_usage (state);
    }
    break;
  default: return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static struct argp argp = { options, parse_options, args_doc, doc };

bool is_readable (const std::string & filename)
{
  std::ifstream file(filename.c_str());
  bool ret = !file.fail();
  file.close();
  return ret;
}

void dump (PajeSimulator *simulator)
{
  std::vector<PajeContainer*> stack;
  stack.push_back (simulator->rootInstance());

  while (stack.size ()){
    PajeContainer *container = stack.back();
    stack.pop_back ();

    //output container description
    std::cout << container->description() << std::endl;

    std::vector<PajeType*> containedTypes;
    std::vector<PajeType*>::iterator it;
    containedTypes = simulator->containedTypesForContainerType (container->type());
    for (it = containedTypes.begin(); it != containedTypes.end(); it++){
      PajeType *type = *it;
      if (simulator->isContainerType (type)){
        std::vector<PajeContainer*> children;
        std::vector<PajeContainer*>::iterator it;
        children = simulator->enumeratorOfContainersTypedInContainer (type, container);
        for (it = children.begin(); it != children.end(); it++){
          stack.push_back (*it);
        }
      }else{
        std::vector<PajeEntity*> entities;
        std::vector<PajeEntity*>::iterator it;
        entities = simulator->enumeratorOfEntitiesTypedInContainer (type,
                                                                    container,
                                                                    simulator->startTime(),
                                                                    simulator->endTime());
        for (it = entities.begin(); it != entities.end(); it++){
          PajeEntity *entity = *it;

          //output entity description
          std::cout << entity->description() << std::endl;
        }
      }
    }
  }
}

int main (int argc, char **argv)
{
  struct arguments arguments;
  bzero (&arguments, sizeof(struct arguments));
  if (argp_parse (&argp, argc, argv, 0, 0, &arguments) == ARGP_KEY_ERROR){
    fprintf(stderr, "%s, error during the parsing of parameters\n", argv[0]);
    return 1;
  }

  if (!is_readable(std::string(arguments.input[0]))){
    std::cerr << "trace file \"" << argv[1] << "\" not found" << std::endl;
    return 1;
  }

  PajeFileReader *reader = new PajeFileReader (std::string(argv[1]), NULL);
  PajeEventDecoder *decoder = new PajeEventDecoder ();
  PajeSimulator *simulator = new PajeSimulator ();

  reader->setOutputComponent (decoder);
  decoder->setInputComponent (reader);
  decoder->setOutputComponent (simulator);
  simulator->setInputComponent (decoder);

  try {
    int i = 0;
    while (reader->hasMoreData()){
      reader->startChunk (i);
      reader->readNextChunk();
      reader->endOfChunkLast (!reader->hasMoreData());
      i++;
    }
  }catch (std::string exception){
    std::cout << "Exception: " << exception << std::endl;
    std::cout << "This trace file does not follow the Paje file format description. Sorry." << std::endl;
    return 1;
  }

  dump (simulator);

  delete reader;
  delete decoder;
  delete simulator;
  return 0;
}
