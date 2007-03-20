include_directories(${CMAKE_CURRENT_BINARY_DIR} ./)

set(kritadeskewfilter_PART_SRCS
bitutil.cc bwimage.cc deskewer.cc kis_deskew_filter.cc kis_deskew_filter_plugin.cc kritafact.cc   )

kde3_automoc(${kritadeskewfilter_PART_SRCS})

kde3_add_kpart(kritadeskewfilter ${kritadeskewfilter_PART_SRCS})

target_link_libraries(kritadeskewfilter ${KRITAUI_LIBRARY})

install(TARGETS kritadeskewfilter  DESTINATION ${PLUGIN_INSTALL_DIR})

install( FILES  kritadeskewfilter.desktop  DESTINATION ${SERVICES_INSTALL_DIR})
