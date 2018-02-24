#include "parser/data/parse_data_and_response_factory.hpp"

#include <easylogging/easylogging++.h>

namespace usl::parser::data
{
    parse_data_and_response_factory::parse_data_and_response_factory(const std::string &db_address)
        : m_db_address{ db_address }
    {}

    std::shared_ptr<parse_data_and_response> parse_data_and_response_factory::create(const std::string &url,
                                                                                     const std::string &content,
                                                                                     common::db::url_id_t id) const
    {
        LOG(INFO) << "parse_data_and_response_factory creating: " << id;
        return parse_data_and_response::create(parse_data{ url, content, id },
                                               std::make_unique<response::unique_response>(m_db_address, id));
    }
}

