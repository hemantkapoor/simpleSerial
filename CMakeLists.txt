file(GLOB_RECURSE sourcesCpp      comms/*.cpp utility/*.cpp)
file(GLOB_RECURSE sourcesH       comms/*.h utility/*.h)
target_sources(SimpleSerial
    PRIVATE
        ${sourcesCpp}
    PUBLIC
        ${sourcesH}
)

target_compile_options(SimpleSerial PUBLIC -std=c++1y -Wall -Wfloat-conversion)
