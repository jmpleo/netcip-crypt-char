set(AI_SOURCES key.cpp
               netcip.cpp
               block.cpp
               lin-comb.cpp
               ai.cpp
               gaus.cpp
               calc-ai.cpp)

set(MDP_SOURCES key.cpp
                netcip.cpp
                block.cpp
                calc-mdp.cpp)

set(NL_SOURCES key.cpp
               netcip.cpp
               block.cpp
               lin-comb.cpp
               wa-coef.cpp
               calc-nl.cpp)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h)

add_executable(netcip-mdp-${__N}-${__M}-${__H} ${MDP_SOURCES})
add_executable(netcip-ai-${__N}-${__M}-${__H} ${AI_SOURCES})
add_executable(netcip-nl-${__N}-${__M}-${__H} ${NL_SOURCES})

