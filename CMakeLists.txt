project(chartview)
set(VERSION 1.0)

cmake_minimum_required(VERSION 2.4.0)
find_package(Qt4 REQUIRED)

set(CMAKE_AUTOMOC TRUE)

include(${QT_USE_FILE})
include_directories(/usr/include/poppler/qt4)
include_directories(/usr/local/include/poppler/qt4)

set(sources
  src/main.cc
  src/MainWindow.cc
  src/ChartWidget.cc
  src/ChartTree.cc
  src/Database.cc
  src/Airport.cc
  src/Chart.cc
)

add_executable(ChartView MACOSX_BUNDLE ${sources})
target_link_libraries(ChartView ${QT_LIBRARIES} poppler-qt4)

install(TARGETS ChartView RUNTIME BUNDLE DESTINATION . COMPONENT RUNTIME)

set(CPACK_BINARY_DRAGNDROP ON)
include(CPack)
