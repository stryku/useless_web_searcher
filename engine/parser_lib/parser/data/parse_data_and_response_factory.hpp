#pragma once

#include "parser/data/parse_data_and_response.hpp"

#include <memory>

namespace usl::parser::data
{
    class parse_data_and_response_factory
    {
    public:
        explicit parse_data_and_response_factory(const std::string &db_address,
                                                 const std::string &index_address);

        std::shared_ptr<parse_data_and_response> create(const std::string& url,
                                                        const std::string& content,
                                                        common::db::url_id_t id) const;

    private:
        const std::string m_db_address;
        const std::string m_index_address;
    };
}
