set(simonddatabaseaccess_LIB_SRCS databaseaccess.cpp)

set(simonddatabaseaccess_LIB_HDRS simonddatabaseaccess_export.h databaseaccess.h)

kde4_add_library(simonddatabaseaccess  SHARED ${simonddatabaseaccess_LIB_SRCS})
target_link_libraries( simonddatabaseaccess ${KDE4_KDECORE_LIBS} 
  ${QT_QTGUI_LIBRARY} ${QT_QTSQL_LIBRARY})

set_target_properties(simonddatabaseaccess
  PROPERTIES VERSION ${CMAKE_SIMON_VERSION_STRING} SOVERSION ${CMAKE_SIMON_VERSION_MAJOR}
)

install(FILES ${simonddatabaseaccess_LIB_HDRS}
  DESTINATION ${INCLUDE_INSTALL_DIR}/simond/simonddatabaseaccess
  COMPONENT simonddevel
)
 
install(TARGETS simonddatabaseaccess DESTINATION ${SIMON_LIB_INSTALL_DIR} COMPONENT simond)
