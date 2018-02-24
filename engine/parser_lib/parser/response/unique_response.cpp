#include "parser/response/unique_response.hpp"

#include "common/db/url_db_interface.hpp"

namespace usl::parser::response
{
    unique_response::unique_response(const std::string &db_address, common::db::url_id_t processed_id)
        : m_db_address{ db_address }
        , m_processed_id{ processed_id }
    {}

    unique_response::~unique_response()
    {
        common::db::url_db_interface db_interface{ m_db_address };
        (void)db_interface.update_state_as_processed(m_processed_id);
    }
}

