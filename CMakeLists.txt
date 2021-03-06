#https://github.com/SFML/SFML/wiki/Tutorial:-Build-your-SFML-project-with-CMake
cmake_minimum_required(VERSION 2.6)

set(EXECUTABLE_NAME "Arkanoid")

# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

set (CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT ${MSVC})
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Og -ggdb")
endif(NOT ${MSVC})

project(${EXECUTABLE_NAME})

# Set Variables and SDKs Folders
set(SRC_PATH ${CMAKE_SOURCE_DIR}/Source)
set(SDK_PATH ${CMAKE_SOURCE_DIR}/External)
set(BIN_PATH ${CMAKE_SOURCE_DIR}/Build)
set(SFML_ROOT ${SDK_PATH}/SFML)
#set(SFML_STATIC_LIBRARIES TRUE)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BIN_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BIN_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_PATH})
set(CMAKE_MODULE_PATH "${SDK_PATH}/cmake_modules" ${CMAKE_MODULE_PATH})

# Sources
FILE(GLOB SourceGroup_Game
    "${SRC_PATH}/Game/*.h"
    "${SRC_PATH}/Game/*.cpp"
)

FILE(GLOB SourceGroup_GDCore
    "${SRC_PATH}/GDCore/*.h"
    "${SRC_PATH}/GDCore/*.cpp"
)
set (SourceGroup_Main
    "${SRC_PATH}/main.cpp"
)

# Filters
source_group("Game" FILES ${SourceGroup_Game})
source_group("GDCore" FILES ${SourceGroup_GDCore})
source_group("Main" FILES ${SourceGroup_Main})

set (SOURCE_FILES
	${SourceGroup_Game}
	${SourceGroup_GDCore}
	${SourceGroup_Main}
)
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

# Detect and add SFML
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDECIES})
endif()

# Copying shared libraries
if (WIN32)
  ADD_CUSTOM_COMMAND (TARGET ${EXECUTABLE_NAME} POST_BUILD

    # DEBUG
    #if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
      COMMAND ${CMAKE_COMMAND} -E copy ${SFML_ROOT}/Library_Windows/sfml-audio-d-2.dll ${BIN_PATH}/Debug
      COMMAND ${CMAKE_COMMAND} -E copy ${SFML_ROOT}/Library_Windows/sfml-graphics-d-2.dll ${BIN_PATH}/Debug
      COMMAND ${CMAKE_COMMAND} -E copy ${SFML_ROOT}/Library_Windows/sfml-network-d-2.dll ${BIN_PATH}/Debug
      COMMAND ${CMAKE_COMMAND} -E copy ${SFML_ROOT}/Library_Windows/sfml-system-d-2.dll ${BIN_PATH}/Debug
      COMMAND ${CMAKE_COMMAND} -E copy ${SFML_ROOT}/Library_Windows/sfml-window-d-2.dll ${BIN_PATH}/Debug
    #endif (CMAKE_BUILD_TYPE EQUAL "DEBUG")

    # RELEASE
    #if (CMAKE_BUILD_TYPE EQUAL "RELEASE")
      COMMAND ${CMAKE_COMMAND} -E copy ${SFML_ROOT}/Library_Windows/sfml-audio-2.dll ${BIN_PATH}/Release
      COMMAND ${CMAKE_COMMAND} -E copy ${SFML_ROOT}/Library_Windows/sfml-graphics-2.dll ${BIN_PATH}/Release
      COMMAND ${CMAKE_COMMAND} -E copy ${SFML_ROOT}/Library_Windows/sfml-network-2.dll ${BIN_PATH}/Release
      COMMAND ${CMAKE_COMMAND} -E copy ${SFML_ROOT}/Library_Windows/sfml-system-2.dll ${BIN_PATH}/Release
      COMMAND ${CMAKE_COMMAND} -E copy ${SFML_ROOT}/Library_Windows/sfml-window-2.dll ${BIN_PATH}/Release
    #endif (CMAKE_BUILD_TYPE EQUAL "RELEASE")

    # Output Message
    COMMENT "Copying SFML libraries" VERBATIM
  )
endif(WIN32)

# cppcheck
find_program(CPPCHECK_BIN cppcheck)
if(EXISTS ${CPPCHECK_BIN})
  add_custom_target(cppcheck
          COMMAND cppcheck
          --enable=all 
          ${SOURCE_FILES}
          --suppress=missingIncludeSystem --suppress=unusedFunction --suppress=unmatchedSuppression
          -v -q --error-exitcode=2 --language=c++
          --template='[{file}:{line}] [{severity},{id}] {message}'
          --suppress=unusedStructMember
  )

  add_dependencies(${EXECUTABLE_NAME} cppcheck)
else()
  message(AUTHOR_WARNING "cppcheck is not installed, some checks will not be performed")
endif()



# clang-format
file(GLOB CLANG_FORMAT_FILE .clang-format)
find_program(CLANG_FORMAT clang-format) 
if(EXISTS ${CLANG_FORMAT})
  add_custom_target(clangformat
        COMMAND clang-format
        -style=file
        -assume-filename=${CLANG_FORMAT_FILE}
        -i
        ${SOURCE_FILES}
  )

  add_dependencies(${EXECUTABLE_NAME} clangformat)
else()
  message(AUTHOR_WARNING "clang-format is not installed, auto formating will not be performed")
endif()
