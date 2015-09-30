cmake_minimum_required(VERSION 2.8)
#Déclaration du projet

project(MyProject)
add_executable(MyProject main.c)



#Déclaration de l'exécutable

find_package(SDL REQUIRED)
if (SDL_FOUND)
  include_directories(${SDL_INCLUDE_DIR})
  target_link_libraries (MyProject ${SDL_LIBRARY})
endif (SDL_FOUND)
