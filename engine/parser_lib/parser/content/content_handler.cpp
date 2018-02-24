#include "parser/content/content_handler.hpp"

#include "parser/data/parse_data_and_response.hpp"

#include <easylogging/easylogging++.h>

namespace usl::parser::content
{
    content_handler::content_handler(const std::string &db_address)
        : m_db_requester{ db_address }
    {}

    void content_handler::handle(std::shared_ptr<data::parse_data_and_response> parse_data)
    {
        LOG(INFO) << "content_handler handling: " << parse_data->data().id;
        LOG(INFO) << "content_handler handling: " << parse_data->data().id << " done";
    }
}
