add_library(Controller PasswordGeneratorController.h
                       PasswordGeneratorController.cpp)

target_include_directories(Controller PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Controller PUBLIC Model GUI Qt6::Core)
