Viva - Trace Visualization Tool
===============================

Viva is an open-source tool used to analyze traces (in the [Paje File
Format](http://paje.sourceforge.net/download/publication/lang-paje.pdf))
registered during the execution of parallel or distributed
applications. The tool also serves as a sandbox to the development of
new visualization techniques. Current features include:

* Temporal integration using dynamic time-intervals
* Spatial aggregation through hierarchical traces
* Interactive Graph Visualization with a force-directed algorithm, with __viva__
* Squarified Treemap to compare processes behavior on scale, with __vv_treemap__

Viva is released under the [GNU General Public
Licence](http://www.gnu.org/licenses/gpl.html) and is developed as
part of the french [INFRA-SONGS ANR
project](http://infra-songs.gforge.inria.fr/).


### Three-line Installation

     sudo apt-get install git cmake build-essential libboost-dev libconfig++-dev libconfig8-dev libgtk2.0-dev freeglut3-dev libqt4-dev ;
     # Install PajeNG
     git clone git://github.com/schnorr/viva.git ; mkdir -p viva/b ; cd viva/b ; cmake .. ; make install

[PajeNG Installation instructions](https://github.com/schnorr/pajeng/wiki)

### How to run

If you are in the build directory, just type:

     $ ./viva <trace_file.trace> <graph_configuration_file.plist>
     $ ./vv_treemap <trace_file.trace>

### Detailed Installation and everything else

[Check the Viva's wiki](https://github.com/schnorr/viva/wiki/).

### Contact

For more information, contact the author at: schnorr@gmail.com