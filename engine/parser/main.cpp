#include "file_paths_to_parse_provider.hpp"
#include "parser/content/content_parser.hpp"
#include "parser/url/urls_handler.hpp"

#include <easylogging/easylogging++.h>

INITIALIZE_EASYLOGGINGPP

int main(int argc, char* argv[])
{
    if(argc < 3)
    {
        LOG(ERROR) << "usage: parser working_directory_path parse_frontier_address";
        return 1;
    }

    const auto working_directory = argv[1];
    const auto parse_frontier_address = argv[2];

    LOG(INFO) << "Parser starting.";
    LOG(INFO) << "Working directory: " << working_directory;
    LOG(INFO) << "Parse frontier address: " << parse_frontier_address;

    usl::parser::content::content_parser content_parser;

    usl::parser::url::urls_handler urls_handler;
    content_parser.add_content_handler(urls_handler);

    usl::parser::poller::file_paths_to_parse_provider file_paths_provider;

    file_paths_provider.run(parse_frontier_address, content_parser);
}