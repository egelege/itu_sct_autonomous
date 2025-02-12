cmake_minimum_required(VERSION 3.10)
project(RestaurantBot)

# C++17 standardını kullanmak için ayarlama
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Eğer json.hpp ayrı bir klasörde ise include dizinini ekleyin, örn:
# include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR})

# Kaynak dosyaları ekliyoruz
add_executable(RestaurantBot main.cpp Menu.cpp)
