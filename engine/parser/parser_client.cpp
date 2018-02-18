#include "parser_client.hpp"

#include "common/fs/file_loader.hpp"
#include "parser/content/content_parser.hpp"
#include "file_paths_to_parse_provider.hpp"

#include <thread>

namespace usl::parser
{
    parser_client::parser_client(file_paths_to_parse_provider& file_paths_provider, content::content_parser& parser)
        : m_file_paths_provider{ file_paths_provider }
        , m_parser{ parser }
    {}

    void parser_client::run()
    {
        while(true)
        {
            const auto path = m_file_paths_provider.get();
            const auto file_content = common::fs::file_loader{}.load<std::string>(path);
            m_parser.parse(file_content);

            std::this_thread::sleep_for(std::chrono::seconds{59990});
        }
    }
}