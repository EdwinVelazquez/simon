set(simondstreamer_LIB_SRCS
  simondstreamer.cpp
  simondstreamerclient.cpp
  simonsender.cpp
)

set(simondstreamer_LIB_HDRS
  simondstreamer_export.h
  simondstreamer.h
  simonsender.h
)

qt4_add_dbus_adaptor(simondstreamer_LIB_SRCS org.simon-listens.SimonSender.xml simonsender.h SimonSender)

kde4_add_library(simondstreamer SHARED ${simondstreamer_LIB_SRCS})

target_link_libraries(simondstreamer ${QT_LIBRARIES} ${KDE4_KDEUI_LIBS}
  simonsound simonwav simoncontextdetection ${QT_QTXML_LIBRARY})

set_target_properties(simondstreamer PROPERTIES VERSION ${CMAKE_SIMON_VERSION_STRING} SOVERSION ${CMAKE_SIMON_VERSION_MAJOR})
install(FILES ${simondstreamer_LIB_HDRS} DESTINATION ${INCLUDE_INSTALL_DIR}/simon/simondstreamer COMPONENT simondevel)
install(TARGETS simondstreamer DESTINATION ${SIMON_LIB_INSTALL_DIR} COMPONENT simon)
