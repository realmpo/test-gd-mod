cmake_minimum_required(VERSION 3.25)

# This sets up your project name
project(MyTestGDMod VERSION 1.0.0 LANGUAGES CXX)

# This tells the builder to look for Geode's tools
find_package(Geode REQUIRED)

# This packages your code into the .geode format
add_geode_mod(
    ${PROJECT_NAME}
    VERSION ${PROJECT_VERSION}
)

# This points directly to your C++ file
target_sources(${PROJECT_NAME} PRIVATE src/main.cpp)
