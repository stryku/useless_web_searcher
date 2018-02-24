#pragma once

#include "common/db/url_db_interface.hpp"

#include <easylogging/easylogging++.h>

namespace usl::parser
{
    namespace data
    {
        class parse_data_and_response;
    }

    namespace url
    {
        class urls_handler
        {
        public:
            explicit urls_handler(const std::string &db_address);

            void handle(std::shared_ptr<data::parse_data_and_response> parse_data);

        private:
            common::db::url_db_interface m_db_requester;
        };
    }
}
