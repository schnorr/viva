# This file is part of Viva
#
# Viva is free software: you can redistribute it and/or modify it
# under the terms of the GNU Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Viva is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Public License for more details.
#
# You should have received a copy of the GNU Public License
# along with Viva. If not, see <http://www.gnu.org/licenses/>.
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT(viva)
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Define sources, headers for all targets
# Utils
SET(UTILS_HEADERS src/utils/PajeThreadReader.h)
SET(UTILS_SOURCES src/utils/PajeThreadReader.cc)
#
# The Tupi Library written in C (particle system)
SET(LIBTUPI_HEADERS
  src/libtupi/tupi.h)
SET(LIBTUPI_SOURCES
  src/libtupi/bary.c
  src/libtupi/basic.c
  src/libtupi/dynar.c
  src/libtupi/dict.c
  src/libtupi/particle.c
  src/libtupi/box.c
  src/libtupi/cell.c
  src/libtupi/layout.c
  src/libtupi/node.c)
#
# Viva Sources
SET(VIVA_HEADERS
  src/viva/VivaWindow.h
  src/viva/VivaGraphView.h
  src/viva/VivaApplication.h
  src/viva/VivaLayoutRunner.h
  src/viva/VivaGraph.h
  src/viva/VivaRenderingThread.h)
SET(VIVA_SOURCES
  src/viva/main.cc
  src/viva/VivaWindow.cc
  src/viva/VivaGraphView.cc
  src/viva/VivaApplication.cc
  src/viva/VivaLayoutRunner.cc
  src/viva/VivaGraph.cc
  src/viva/VivaNode.cc
  src/viva/VivaRenderingThread.cc)
SET(VIVA_RESOURCES
  src/viva/VivaResource.qrc)

# Viva
FIND_PACKAGE(Qt4 REQUIRED QtCore QtGui QtOpenGl)
FIND_PACKAGE(GLUT REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(LibConfig REQUIRED)
FIND_PACKAGE(PajeNG REQUIRED)

QT4_WRAP_CPP(UTILS_HEADERS_MOC ${UTILS_HEADERS})
QT4_WRAP_CPP(VIVA_HEADERS_MOC ${VIVA_HEADERS})
QT4_ADD_RESOURCES(VIVA_RESOURCES_RCC ${VIVA_RESOURCES})
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})
INCLUDE_DIRECTORIES(viva ${PROJECT_SOURCE_DIR}/src/libtupi/)
INCLUDE_DIRECTORIES(viva ${PAJENG_INCLUDE_PATH})
LINK_DIRECTORIES (${PAJENG_LIBRARY_PATH})

ADD_EXECUTABLE(viva
  ${LIBTUPI_SOURCES}
  ${VIVA_SOURCES}
  ${VIVA_HEADERS_MOC}
  ${VIVA_RESOURCES_RCC}
  ${UTILS_SOURCES}
  ${UTILS_HEADERS_MOC})
TARGET_LINK_LIBRARIES(viva ${QT_LIBRARIES})
TARGET_LINK_LIBRARIES(viva ${GLUT_glut_LIBRARY})
TARGET_LINK_LIBRARIES(viva ${OPENGL_gl_LIBRARY})
TARGET_LINK_LIBRARIES(viva ${OPENGL_glu_LIBRARY})
TARGET_LINK_LIBRARIES(viva ${LIBCONFIG_LIBRARIES})
TARGET_LINK_LIBRARIES(viva paje)
INSTALL(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/viva DESTINATION bin)