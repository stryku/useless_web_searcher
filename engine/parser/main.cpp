#include "file_paths_to_parse_provider.hpp"
#include "parser/content/content_parser.hpp"
#include "parser/url/urls_handler.hpp"
#include "parser_client.hpp"

#include <easylogging/easylogging++.h>

INITIALIZE_EASYLOGGINGPP

int main(int argc, char* argv[])
{
    if(argc < 4)
    {
        LOG(ERROR) << "usage: parser working_directory_path parse_frontier_address";
        return 1;
    }

    const auto working_directory = argv[1];
    const auto parse_frontier_address = argv[2];
    const auto db_address = argv[3];

    LOG(INFO) << "Parser starting.";
    LOG(INFO) << "Working directory: " << working_directory;
    LOG(INFO) << "Parse frontier address: " << parse_frontier_address;
    LOG(INFO) << "URL database address: " << db_address;

    usl::parser::content::content_parser content_parser;

    usl::parser::url::urls_handler urls_handler{ db_address };
    content_parser.add_content_handler(std::move(urls_handler));

    usl::parser::file_paths_to_parse_provider file_paths_provider{ parse_frontier_address };
    usl::parser::parser_client client{ file_paths_provider, content_parser };
    client.run();
}