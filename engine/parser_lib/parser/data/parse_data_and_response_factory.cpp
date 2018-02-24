#include "parser/data/parse_data_and_response_factory.hpp"

namespace usl::parser::data
{
    parse_data_and_response_factory::parse_data_and_response_factory(const std::string &db_address)
        : m_db_address{ db_address }
    {}

    std::shared_ptr<parse_data_and_response> parse_data_and_response_factory::create(const std::string &url,
                                                                                     const std::string &content,
                                                                                     common::db::url_id_t id) const
    {
        return std::make_shared<parse_data_and_response>(parse_data{ url, content, id },
                                                         response::unique_response{ m_db_address, id });
    }
}

