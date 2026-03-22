cmake_minimum_required(VERSION 3.16)
project(replay-buffer-pro VERSION 1.4.0)

set(OBS_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../obs-studio" CACHE PATH "OBS Studio source code directory")
set(OBS_INSTALL_DIR "C:/Program Files/obs-studio/bin/64bit" CACHE PATH "OBS Studio install directory")

if(WIN32)
  get_filename_component(OBS_ROOT_DIR "${OBS_ROOT_DIR}" ABSOLUTE)

  # Reuse same dependencies used in OBS build
  set(OBS_CACHE_FILE "${OBS_ROOT_DIR}/build/CMakeCache.txt")
  if(EXISTS "${OBS_CACHE_FILE}")
    file(STRINGS "${OBS_CACHE_FILE}" OBS_CMAKE_PREFIX_PATH_LINE
         REGEX "^CMAKE_PREFIX_PATH:PATH=")

    if(OBS_CMAKE_PREFIX_PATH_LINE)
      string(REGEX REPLACE "^CMAKE_PREFIX_PATH:PATH=" "" OBS_CMAKE_PREFIX_PATH
             "${OBS_CMAKE_PREFIX_PATH_LINE}")
      list(APPEND CMAKE_PREFIX_PATH ${OBS_CMAKE_PREFIX_PATH})
      message(STATUS "Using CMAKE_PREFIX_PATH from OBS cache: ${OBS_CMAKE_PREFIX_PATH}")
    endif()
  else()
    message(FATAL_ERROR "${OBS_ROOT_DIR}/build/CMakeCache.txt doesn't exist, make sure to build obs-studio first.")
  endif()
endif()

# Find Qt
set(CMAKE_AUTOMOC ON)
find_package(Qt6 REQUIRED COMPONENTS Widgets Core)

# Find OBS
if(WIN32)
  if(NOT EXISTS "${OBS_ROOT_DIR}")
    message(FATAL_ERROR "OBS Studio source not found at ${OBS_ROOT_DIR}. Please clone obs-studio repository and specify -DOBS_ROOT_DIR=<obs-studio-path>")
  endif()

  set(OBS_INCLUDE_DIRS
    "${OBS_ROOT_DIR}/libobs"
    "${OBS_ROOT_DIR}/frontend/api"
    "${OBS_ROOT_DIR}/build/config"
  )

  set(OBS_LIBRARIES
    "${OBS_ROOT_DIR}/build/libobs/$<CONFIG>/obs.lib"
    "${OBS_ROOT_DIR}/build/frontend/api/$<CONFIG>/obs-frontend-api.lib"
  )
else()
  # For Linux/Mac use automatic discovery from installed OBS package
  # Install your obs-studio build output using:
  #   cmake --install <obs-build-dir> --prefix <obs-install-dir>
  # Then configure replay-buffer-pro with:
  #   cmake -S . -B build -DOBS_INSTALL_DIR=<obs-install-dir>

  if(OBS_INSTALL_DIR)
    list(APPEND CMAKE_PREFIX_PATH "${OBS_INSTALL_DIR}")
  endif()

  find_package(libobs REQUIRED)

  set(OBS_LIBRARIES "OBS::libobs")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
set(SOURCES
  src/main.cpp
  src/plugin/plugin.cpp
  src/utils/obs-utils.cpp
  src/utils/duration-format.cpp
  src/ui/ui-components.cpp
  src/managers/settings-manager.cpp
  src/managers/save-button-settings.cpp
  src/managers/replay-buffer-manager.cpp
  src/managers/hotkey-manager.cpp
)

add_library(${PROJECT_NAME} MODULE ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
  ${OBS_INCLUDE_DIRS}
  ${Qt6Widgets_INCLUDE_DIRS}
  src
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  ${OBS_LIBRARIES}
  Qt6::Widgets
  Qt6::Core
)

# Set plugin files install paths
if(WIN32)
  # You may need to specify --config <build-type> if you're not building as "Release".
  # Example: cmake --install build --config RelWithDebugInfo --prefix "<obs-path>"
  set(PLUGIN_DEST "obs-plugins/64bit")
  set(DATA_DEST "data/obs-plugins/${PROJECT_NAME}")
else()
  # Linux/Mac paths
  set(PLUGIN_DEST "lib/obs-plugins")
  set(DATA_DEST "share/obs/obs-plugins/${PROJECT_NAME}")
endif()

# Install plugin binaries
install(TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION "${PLUGIN_DEST}"
  RUNTIME DESTINATION "${PLUGIN_DEST}"
)

# Install data files
install(DIRECTORY data/ DESTINATION "${DATA_DEST}")

# Release package configuration
set(RELEASE_DIR "${CMAKE_BINARY_DIR}/obs-studio")
set(RELEASE_PLUGIN_DIR "${RELEASE_DIR}/obs-plugins/64bit")
set(RELEASE_DATA_DIR "${RELEASE_DIR}/data/obs-plugins/${PROJECT_NAME}")
set(RELEASE_ZIP_DIR "${CMAKE_BINARY_DIR}/releases/${PROJECT_VERSION}")
set(RELEASE_ZIP "${RELEASE_ZIP_DIR}/${PROJECT_NAME}-windows-x64.zip")

# Custom target that depends on the main target
add_custom_target(prepare_release
    DEPENDS ${PROJECT_NAME}
    # Create directory structure
    COMMAND ${CMAKE_COMMAND} -E make_directory "${RELEASE_PLUGIN_DIR}"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${RELEASE_DATA_DIR}"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${RELEASE_ZIP_DIR}"

    # Copy plugin DLL
    COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE:${PROJECT_NAME}>"
        "${RELEASE_PLUGIN_DIR}/"

    # Copy data files (locale)
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/data"
        "${RELEASE_DATA_DIR}"

    # Create ZIP file
    COMMAND ${CMAKE_COMMAND} -E tar "cf" "${RELEASE_ZIP}" --format=zip
        "${RELEASE_DIR}/"

    COMMENT "Creating release package..."
)
