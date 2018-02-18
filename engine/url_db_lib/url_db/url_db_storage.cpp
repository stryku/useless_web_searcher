#include "url_db/url_db_storage.hpp"

#include "common/string_view.hpp"

#include <vector>

namespace usl::url_db
{
    url_db_storage::url_db_storage(string_view working_directory)
    {

    }

    const url_db_storage::data_t& usl::url_db::url_db_storage::data() const
    {
        return m_data;
    }

    const uint8_t* usl::url_db::url_db_storage::ptr(offset_t offset) const
    {
        return std::next(m_data.data(), offset);
    }
}
