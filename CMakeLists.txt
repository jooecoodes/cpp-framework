cmake_minimum_required(VERSION 3.29.2)


project(pkg-test VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Set vcpkg toolchain BEFORE project()
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/vcpkg_installed/x64-windows/" CACHE STRING "" FORCE)

# if encountering errors like this 
# Add the installation prefix of "CURL" to CMAKE_PREFIX_PATH or set
# "CURL_DIR" to a directory containing one of the above files.  If "CURL"
# provides a separate development package or SDK, be sure it has been
# installed.

# set it as this, they're usually in the share folder too like the 2nd example, in this case it was fmt on the first one
# set(fmt_DIR "${CMAKE_SOURCE_DIR}/vcpkg_installed/x64-windows-static/include/fmt")
# set(CURL_DIR "${CMAKE_SOURCE_DIR}/vcpkg_installed/x64-windows-static/share/curl")

set(CURL_DIR "${CMAKE_SOURCE_DIR}/vcpkg_installed/x64-windows-static/share/curl")


set(VCPKG_TARGET_TRIPLET "x64-windows") # sets vcpkg to use x64-windows libraries without full-packed supported ddls or something, for that use x64-windows-static
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON) # remove unused codes

# set cmake build typesm cmake --build . --config <build-type>
# set(CMAKE_BUILD_TYPE Debug)  # slow, w debug symbols, biggest, slow
set(CMAKE_BUILD_TYPE Release) # optimized no debug symbols and command is: cmake --build . --config Release, smallest, fastest
# set(CMAKE_BUILD_TYPE RelWithDebInfo) # optimized and w debug symbols, medium size, fast
# set(CMAKE_BUILD_TYPE MinSizeRel) # optimized and w/o debug symbols, smallest, fastest

# MinsizeRel is optimized for size like for embedded systems where size matters, whereas Release is optimized for speed, though MinSizeRel often requires you to be with x64-windows-static librarues



find_package(fmt CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED) # ✅ Find your packages here
find_package(CURL CONFIG REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt  nlohmann_json::nlohmann_json CURL::libcurl) # ✅ Link them just liek so (add)