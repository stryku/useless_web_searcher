#include "common/db/url_db_interface.hpp"
#include "common/db/url_db_request_keys.hpp"

#include <easylogging/easylogging++.h>

namespace usl::common::db
{
    url_db_interface::url_db_interface(const std::string& db_address)
        : communication::server::server_interface{ db_address }
    {}

    std::string url_db_interface::insert(const std::string &url)
    {
        return send_and_recv(common::db::request_keys::k_insert, "url", url);
    }

    std::string url_db_interface::get(common::db::url_id_t id)
    {
        return send_and_recv(common::db::request_keys::k_get, "id", id);
    }

    std::string url_db_interface::update_state_as_processed(common::db::url_id_t id)
    {
        return send_and_recv(common::db::request_keys::k_update_state_as_processed, "id", id);
    }
}
