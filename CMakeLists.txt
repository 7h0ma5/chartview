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

set(plugin_dest_dir bin)
set(qtconf_dest_dir bin)
set(APPS "\${CMAKE_INSTALL_PREFIX}/bin/ChartView")
if(APPLE)
  set(plugin_dest_dir ChartView.app/Contents/MacOS)
  set(qtconf_dest_dir ChartView.app/Contents/Resources)
  set(APPS "\${CMAKE_INSTALL_PREFIX}/ChartView.app")
endif(APPLE)
if(WIN32)
  set(APPS "\${CMAKE_INSTALL_PREFIX}/bin/ChartView.exe")
endif(WIN32)

install(TARGETS ChartView
    BUNDLE DESTINATION . COMPONENT Runtime
    RUNTIME DESTINATION bin COMPONENT Runtime
)

install(
    DIRECTORY "${QT_PLUGINS_DIR}/imageformats"
    DESTINATION ${plugin_dest_dir}/plugins
    COMPONENT Runtime
)

install(CODE "
    file(WRITE \"\${CMAKE_INSTALL_PREFIX}/${qtconf_dest_dir}/qt.conf\" \"\")
    " COMPONENT Runtime)

set(DIRS ${QT_LIBRARY_DIRS})

install(CODE "
    set(BU_CHMOD_BUNDLE_ITEMS ON)
    file(GLOB_RECURSE QTPLUGINS
      \"\${CMAKE_INSTALL_PREFIX}/${plugin_dest_dir}/plugins/*${CMAKE_SHARED_LIBRARY_SUFFIX}\")
    include(BundleUtilities)
    fixup_bundle(\"${APPS}\" \"\${QTPLUGINS}\" \"${DIRS}\")
    " COMPONENT Runtime)

set(CPACK_BINARY_DRAGNDROP ON)
include(CPack)
