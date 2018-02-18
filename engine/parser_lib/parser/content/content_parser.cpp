//
// Created by stryku on 18.02.18.
//

#include "content_parser.hpp"

namespace usl::parser::content
{
    void content_parser::parse(const std::string &content)
    {
        for(auto& handler : m_content_handlers)
        {
            handler->handle(content);
        }
    }
}
