#pragma once

#include "common/db/url_db_interface.hpp"

#include <easylogging/easylogging++.h>

namespace usl::parser::url
{
    class urls_handler
    {
    public:
        explicit urls_handler(const std::string& db_address);

        void handle(const std::string& url, const std::string& content, size_t id);

    private:
        common::db::url_db_interface m_db_requester;
    };
}
