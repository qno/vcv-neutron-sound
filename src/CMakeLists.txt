# http://urbanhonking.com/ideasfordozens/2009/05/18/an_tour_of_the_arduino_interna
# https://arduino.github.io/arduino-cli/sketch-build-process
# ls *ino | sort | xargs cat >> ../orgone_accumulator_2.0_for_144MHZ_overclock.ino

set(SOURCES NeutronSoundPlugin.cpp
            OrgoneAccumulator/OrgoneAccumulator.cpp
            OrgoneAccumulator/orgone_accumulator_2.0_for_144MHZ_overclock.cpp
)

add_library(${LIB_NAME} MODULE ${SOURCES})

target_compile_options(${LIB_NAME} PRIVATE "-fuse-ld=gold" "-flto")
target_include_directories(${LIB_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${LIB_NAME} ${CONAN_LIBS})

if (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
  set_target_properties(${LIB_NAME} PROPERTIES SUFFIX ".dylib")
endif ()

set_target_properties(${LIB_NAME} PROPERTIES PREFIX "")
