add_library(plox)

target_include_directories(plox
    PUBLIC
        ${plox_SOURCE_DIR}/include/plox/
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources( plox
    PUBLIC
        Token.cpp
        Scanner.cpp
        Lox.cpp
)

add_executable(plox_repl)
set_target_properties(plox_repl PROPERTIES OUTPUT_NAME "plox")

target_include_directories(plox_repl
  PUBLIC
    ${plox_SOURCE_DIR}/include/plox/
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(plox_repl
  PRIVATE
    main.cpp
)

set_target_properties(plox_repl PROPERTIES OUTPUT_NAME "plox")

target_include_directories(plox_repl
  PUBLIC
    ${plox_SOURCE_DIR}/include
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(plox_repl
  PRIVATE
    main.cpp
)

target_link_libraries(plox_repl PRIVATE plox)
