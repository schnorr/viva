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
#include "VTApplication.h"
#include <argp.h>


static char doc[] = "Interactive treemap visualization of a trace file";
static char args_doc[] = "[TRACEFILE]";

static struct argp_option options[] = {
  {"stop-at", 'a', "TIME", 0, "Stop the trace simulation at TIME"},
  {"no-strict", 'n', 0, OPTION_ARG_OPTIONAL, "Support old field names in event definitions"},
  {"ignore-incomplete-links", 'z', 0, OPTION_ARG_OPTIONAL, "Ignore incomplete links (not recommended)"},
  {"flex", 'f', 0, OPTION_ARG_OPTIONAL, "Use flex-based file reader"},
  { 0 }
};

static error_t parse_options (int key, char *arg, struct argp_state *state)
{
  struct arguments *arguments = (struct arguments*)(state->input);
  switch (key){
  case 'a': arguments->stopat = atof(arg); break;
  case 'n': arguments->noStrict = 1; break;
  case 'z': arguments->ignoreIncompleteLinks = 1; break;
  case 'f': arguments->flex = 1; break;
  case ARGP_KEY_ARG:
    if (arguments->input_size == VALIDATE_INPUT_SIZE) {
      /* Too many arguments. */
      argp_usage (state);
    }
    arguments->input[state->arg_num] = arg;
    arguments->input_size++;
    break;
  case ARGP_KEY_END:
    if (state->arg_num < 0) {
      /* Not enough arguments. */
      argp_usage (state);
    }
    break;
  default: return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static struct argp argp = { options, parse_options, args_doc, doc };

int main(int argc, char *argv[])
{
  struct arguments arguments;
  bzero (&arguments, sizeof(struct arguments));
  arguments.stopat = -1;
  if (argp_parse (&argp, argc, argv, 0, 0, &arguments) == ARGP_KEY_ERROR){
    fprintf(stderr, "%s, error during the parsing of parameters\n", argv[0]);
    return 1;
  }

  QApplication::setAttribute( Qt::AA_X11InitThreads );
  VTApplication app(&arguments, argc, argv);
  try {
    app.init();
  }catch (std::string exception){
    std::cout << "Exception: " << exception << std::endl;
    return 1;
  }
  return app.exec();
}
