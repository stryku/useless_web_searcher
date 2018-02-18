#include "parser_client.hpp"

#include "file_paths_to_parse_provider.hpp"

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
        }
    }
}