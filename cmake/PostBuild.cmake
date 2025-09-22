

configure_file(${CMAKE_SOURCE_DIR}/src/app/preferences/config.json ${CMAKE_BINARY_DIR}/bin/config/config.json COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/app/preferences/theme.json ${CMAKE_BINARY_DIR}/bin/config/theme.json COPYONLY)

# Create fonts directory and copy all font files
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin/fonts)
file(GLOB FONT_FILES ${CMAKE_SOURCE_DIR}/fonts/*)
foreach(FONT_FILE ${FONT_FILES})
	configure_file(${FONT_FILE} ${CMAKE_BINARY_DIR}/bin/fonts/ COPYONLY)
endforeach()