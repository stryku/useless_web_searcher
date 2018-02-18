#pragma once

#include "common/db/url_db_requester.hpp"

#include <easylogging/easylogging++.h>

namespace usl::parser::url
{
    class urls_handler
    {
    public:
        explicit urls_handler(const std::string& db_address);

        void handle(const std::string& content);

    private:
        common::db::url_db_requester m_db_requester;
    };
}
