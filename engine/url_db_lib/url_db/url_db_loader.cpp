#include "url_db/url_db_loader.hpp"
#include "common/fs/file_loader.hpp"
#include "url_db/url_db.hpp"

namespace usl::url_db
{
    url_db url_db_loader::load(url_db_storage& storage) const
    {
        url_db db{ storage };
        load(storage.data(), db);
        return db;
    }

    url_db url_db_loader::load(const std::vector<uint8_t> &file_content, url_db& db) const
    {
        auto entry = load_next_entry(file_content);
        offset_t offset{ 0u };
        common::db::url_id_t index{ 0u };

        while(entry)
        {
            db.m_id_to_offset[index] = offset;

            const auto url = url_db::url_t{ entry->url() };
            const auto url_size = url.size() + 1u; // with null
            db.m_urls.emplace(std::move(url));

            if(static_cast<common::db::url_state>(entry->status) != common::db::url_state::processed)
            {
                db.m_not_processed.push(index);
            }

            offset += 1u + url_size;
            ++index;

            entry = load_next_entry(file_content, offset);
        }

        return db;
    }

    const db_entry_view* url_db_loader::load_next_entry(const std::vector<uint8_t> &file_content, offset_t offset) const
    {
        if(offset >= file_content.size())
        {
            return nullptr;
        }

        return reinterpret_cast<const db_entry_view*>(std::next(file_content.data(), offset));
    }
}
