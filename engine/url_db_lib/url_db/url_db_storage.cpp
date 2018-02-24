#include "url_db/url_db_storage.hpp"

#include "common/db/url_state.hpp"
#include "common/fs/file_loader.hpp"


namespace usl::url_db
{
    url_db_storage::url_db_storage(string_view working_directory, const common::fs::file_loader& file_loader)
        : m_data_file_path{ working_directory.data() + std::string { "/url_db" } }
        , m_data{ file_loader.load<data_t>(m_data_file_path) }
    {}

    const url_db_storage::data_t& usl::url_db::url_db_storage::data() const
    {
        return m_data;
    }

    const uint8_t* usl::url_db::url_db_storage::ptr(offset_t offset) const
    {
        return std::next(m_data.data(), offset);
    }

    uint8_t *url_db_storage::ptr(offset_t offset)
    {
        return std::next(m_data.data(), offset);
    }

    offset_t url_db_storage::insert(const std::string &url)
    {
        std::ofstream file{ m_data_file_path, std::ios::out | std::ios::app | std::ios::binary };

        const auto url_size_with_null = url.size() + 1u;

        const auto kState = common::db::url_state::not_processed;
        file.write(reinterpret_cast<const char*>(&kState), sizeof(kState));
        file.write(url.data(), url_size_with_null);

        const auto insert_offset = m_data.size();

        m_data.push_back(static_cast<uint8_t>(kState));
        const auto url_begin = reinterpret_cast<const uint8_t*>(url.data());
        const auto url_end = std::next(url_begin, url_size_with_null);
        m_data.insert(m_data.end(), url_begin, url_end);

        return insert_offset;
    }

    void url_db_storage::update_state(offset_t offset, uint8_t state)
    {
        m_data[offset] = state;
        std::ofstream file{ m_data_file_path, std::ios::out | std::ios::app | std::ios::binary };

        file.seekp(offset);
        file.write(reinterpret_cast<char*>(&state), sizeof(state));
    }
}
