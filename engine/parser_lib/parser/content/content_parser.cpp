#include "content_parser.hpp"

namespace usl::parser::content
{
    void content_parser::parse(std::shared_ptr<data::parse_data_and_response> parse_data)
    {
        for(auto& handler : m_content_handlers)
        {
            handler->handle(parse_data);
        }
    }
}
