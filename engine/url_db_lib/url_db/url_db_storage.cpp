#include "url_db/url_db_storage.hpp"

#include "common/fs/file_loader.hpp"
#include <boost/filesystem.hpp>


namespace usl::url_db
{
    url_db_storage::url_db_storage(const std::string& working_directory, const common::fs::file_loader& file_loader)
        : m_data_file_path{ working_directory + std::string { "/url_db" } }
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
        insert_to_file(url);
        return insert_to_data(url);
    }

    void url_db_storage::update_state(offset_t offset, common::db::url_state state)
    {
        m_data[offset] = static_cast<uint8_t>(state);
        boost::iostreams::mapped_file file;
        file.open(m_data_file_path, boost::iostreams::mapped_file::mapmode::readwrite);

        auto file_data = file.data();
        file_data[offset] = static_cast<uint8_t>(state);

//        write_state(file, state);
    }

    void url_db_storage::write_state(boost::iostreams::mapped_file& out, common::db::url_state state) const
    {
//        auto ptr = out.data() +

//        out.write(reinterpret_cast<const char*>(&state), sizeof(state));
    }

    void url_db_storage::insert_to_file(const std::string &url) const
    {
        const auto url_size_with_null = url.size() + 1u;
        auto insert_offset = m_data.size();

        const auto new_file_size = m_data.size() + 1u + url_size_with_null;

        boost::filesystem::resize_file(m_data_file_path, new_file_size);

        boost::iostreams::mapped_file file;
        file.open(m_data_file_path, boost::iostreams::mapped_file::mapmode::readwrite);
        auto file_data_ptr = file.data();

        file_data_ptr[insert_offset] = static_cast<uint8_t>(common::db::url_state::not_processed);
        ++insert_offset;
        std::copy(url.data(), url.data() + url_size_with_null, file_data_ptr + insert_offset);
        //auto file = open_file();


        //write_state(file, common::db::url_state::not_processed);
        //file.write(url.data(), url_size_with_null);
    }

    offset_t url_db_storage::insert_to_data(const std::string &url)
    {
        const auto url_size_with_null = url.size() + 1u;
        const auto insert_offset = m_data.size();

        m_data.push_back(static_cast<uint8_t>(common::db::url_state::not_processed));
        const auto url_begin = reinterpret_cast<const uint8_t*>(url.data());
        const auto url_end = std::next(url_begin, url_size_with_null);
        m_data.insert(m_data.end(), url_begin, url_end);

        return insert_offset;
    }

    std::fstream url_db_storage::open_file() const
    {

        return std::fstream{ m_data_file_path, std::ios::binary };
    }
}
