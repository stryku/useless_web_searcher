#pragma once

#include "common/db/url_db_interface.hpp"

#include <memory>

namespace usl::parser
{
    namespace data
    {
        struct parse_data;
        class parse_data_and_response;
    }

    namespace content
    {
        class content_handler
        {
        public:
            explicit content_handler(const std::string &db_address);

            void handle(std::shared_ptr<data::parse_data_and_response> parse_data);

        private:
            common::db::url_db_interface m_db_requester;
        };
    }
}
