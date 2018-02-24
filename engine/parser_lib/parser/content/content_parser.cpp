#include "content_parser.hpp"
#include "parser/data/parse_data_and_response.hpp"

#include <easylogging/easylogging++.h>

namespace usl::parser::content
{
    void content_parser::parse(std::shared_ptr<data::parse_data_and_response> parse_data)
    {
        LOG(INFO) << "content_parser parsing: " << parse_data->data().id;

        for(auto& handler : m_content_handlers)
        {
            handler->handle(parse_data);
        }
    }
}
