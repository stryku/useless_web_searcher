#pragma once

#include "common/db/url_id.hpp"

#include <string>

namespace usl::parse::response
{
    class unique_response
    {
    public:
        explicit unique_response(const std::string &db_address, common::db::url_id_t processed_id);

        unique_response(const unique_response&) = delete;
        unique_response& operator=(const unique_response&) = delete;

        unique_response(unique_response&&) = default;
        unique_response& operator=(unique_response&&) = default;

        ~unique_response();

    private:
        const std::string m_db_address;
        const common::db::url_id_t m_processed_id;
    };
}
