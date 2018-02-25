#include "parse_data_handler.hpp"
#include "parser/data/parse_data_and_response.hpp"

#include <easylogging/easylogging++.h>

namespace usl::parser::data
{
    void parse_data_handler::parse(std::shared_ptr<data::parse_data_and_response> parse_data)
    {
        LOG(INFO) << "parse_data_handler parsing: " << parse_data->data().id;

        for(auto& handler : m_content_handlers)
        {
            handler->handle(parse_data);
        }
    }
}
