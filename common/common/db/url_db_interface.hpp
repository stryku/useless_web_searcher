#pragma once

#include "common/communication/server/server_interface.hpp"
#include "common/db/url_id.hpp"

#include <string>
#include <sstream>

namespace usl::common::db
{
    class url_db_interface : public communication::server::server_interface
    {
    public:
        explicit url_db_interface(const std::string& db_address);

        struct insert_result
        {
            std::string url;
            common::db::url_id_t id;
        };

        insert_result insert(const std::string& url);
        std::string get(common::db::url_id_t id);
        std::string update_state_as_processed(common::db::url_id_t id);
    };
}
