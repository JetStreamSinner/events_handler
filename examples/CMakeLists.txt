project(Samples)

set(SAMPLE_SOURCES sample1.cpp)
set(INCLUDE_DIRS ../include)
set(LIBRARY EventsHandler)

link_directories(${CMAKE_BINARY_DIR}/lib)

foreach( SAMPLE ${SAMPLE_SOURCES} )
    string(REGEX MATCH "^(.*)\\.[^.]*$" dummy ${SAMPLE})
    set(SAMPLE_TITLE ${CMAKE_MATCH_1})
    add_executable(${SAMPLE_TITLE} ${SAMPLE})
    target_link_libraries(${SAMPLE_TITLE} ${LIBRARY})
    target_include_directories(${SAMPLE_TITLE} PUBLIC ${INCLUDE_DIRS})
endforeach()