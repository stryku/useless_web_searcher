#include "common/db/url_db_request_keys.hpp"

namespace usl::common::db::request_keys
{
    const std::string k_get{ "get" };
    const std::string k_insert{ "insert" };
    const std::string k_update_state_as_processed{ "update_state_as_processed" };
    const std::string k_get_for_processing{ "get_for_processing" };
}
