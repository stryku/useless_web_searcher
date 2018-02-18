#include "url_db/url_db_loader.hpp"
#include "common/fs/file_loader.hpp"
#include "url_db/url_db.hpp"

namespace usl::url_db
{
    url_db_loader::url_db_loader(const usl::common::fs::file_loader &file_loader)
        : m_file_loader{ file_loader }
    {}

    url_db url_db_loader::load(string_view file_path) const
    {
        const auto file_content = m_file_loader.load(file_path);
        return load(file_content);
    }

    url_db url_db_loader::load(const std::vector<uint8_t> &file_content) const
    {
        url_db db;

        auto entry = load_next_entry(file_content);
        offset_t offset{ 0u };
        url_db::id_t index{ 0u };

        while(entry)
        {
            db.m_id_to_offset[index] = offset;

            const auto url = url_db::url_t{ entry->url() };
            const auto url_size = url.size();
            db.m_urls.emplace(std::move(url));

            offset += url_size;
            ++index;

            entry = load_next_entry(file_content, offset);
        }

        return db;
    }

    db_entry* url_db_loader::load_next_entry(const std::vector<uint8_t> &file_content, offset_t offset) const
    {
        if(offset >= file_content.size())
        {
            return nullptr;
        }

        return reinterpret_cast<db_entry*>(std::next(file_content.data(), offset));
    }
}
