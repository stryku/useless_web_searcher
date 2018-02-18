#include "url_db/url_db_storage.hpp"

#include "common/fs/file_guard.hpp"

#include <vector>

namespace usl::url_db
{
    url_db_storage::url_db_storage(string_view working_directory)
        : m_data_file_path{ working_directory.data() + std::string { "/url_db" } }
    {}

    const url_db_storage::data_t& usl::url_db::url_db_storage::data() const
    {
        return m_data;
    }

    const uint8_t* usl::url_db::url_db_storage::ptr(offset_t offset) const
    {
        return std::next(m_data.data(), offset);
    }

    void url_db_storage::insert(const std::string &url)
    {
        common::fs::file_guard data_file_guard{ m_data_file_path };

        std::ofstream file{m_data_file_path, std::ios::out | std::ios::app | std::ios::binary };
    }
}
