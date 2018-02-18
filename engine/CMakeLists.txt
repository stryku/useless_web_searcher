add_subdirectory(indexer)

include_directories(parser_lib)
add_subdirectory(parser_lib)

add_subdirectory(parser)
add_subdirectory(parse_frontier)

include_directories(url_db_lib)
add_subdirectory(url_db_lib)

add_subdirectory(url_db)
