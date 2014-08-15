file(GLOB Sources *.cpp)
file(GLOB Headers *.h)
add_executable(${CMAKE_PROJECT_NAME} ${Sources} ${Headers})

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

    target_link_libraries(${CMAKE_PROJECT_NAME} GL sfml-graphics sfml-window sfml-system sfml-audio)
	
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

    target_link_libraries(${CMAKE_PROJECT_NAME} OpenGL32 glew32 sfml-graphics sfml-window sfml-system sfml-audio)

endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

if (${CMAKE_BUILD_TYPE} MATCHES Debug)
    set(BUILD_POSTFIX "_d")
else (${CMAKE_BUILD_TYPE} MATCHES Debug)
    set(BUILD_POSTFIX "")
endif (${CMAKE_BUILD_TYPE} MATCHES Debug)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
if(MSVC)
    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin)
    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin)
    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_SOURCE_DIR}/bin)
    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_SOURCE_DIR}/bin)
    # etc for the other available configuration types (MinSizeRel, RelWithDebInfo)
endif(MSVC)
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES OUTPUT_NAME ${CMAKE_PROJECT_NAME}${BUILD_POSTFIX})
