Viva
====

Viva is an open-source tool used to analyze traces (in the pajé
format) registered during the execution of parallel applications. The
tool serves also as a sandbox to the development of new visualization
techniques. Some features include:

* Temporal integration using dynamic time-intervals
* Spatial aggregation through hierarchical traces
* Interactive Graph Visualization with a force-directed algorithm
* Squarified Treemap to compare processes behavior on scale

Viva is released under the [GNU General Public
Licence](http://www.gnu.org/licenses/lgpl.html) and received funding
from the [CAPES/Cofecub](http://www.capes.gov.br),
[CNPq](http://www.cnpq.br), and
[ANR](http://www.agence-nationale-recherche.fr/) agencies. Currently,
the tool is developed as part of the french [INFRA-SONGS ANR
project](http://infra-songs.gforge.inria.fr/).

__We are still polishing things before the first implementation push to
this repository. Please, bear with us and check back soon__.

Dependencies
------------

Viva needs Qt, OpenGL, LibConfig, GLUT, Boost, and PajeNG.

Installation
------------

Just follow these steps:

     $ git clone git@github.com:schnorr/viva.git
     $ mkdir build
     $ cd build
     $ cmake ..
     $ make

How to run
----------

If you are in the build directory, just type:

     $ ./viva <trace_file.trace> <graph_configuration_file.plist>

Contact
-------

For more information, contact the author at: schnorr@gmail.com