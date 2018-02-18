#include "url_db/url_db.hpp"

namespace usl::url_db
{
    const db_entry_view& url_db::get(id_t id) const
    {
        const auto offset = m_id_to_offset[id];
        const auto ptr = m_storage.ptr(offset);

        return *reinterpret_cast<const db_entry_view*>(ptr);
    }

    void url_db::insert(const std::string &url)
    {
        if(m_urls.find(url) != m_urls.cend())
        {
            return;
        }

        const auto inserted_offset = m_storage.insert(url);

        m_urls.insert(std::move(url));

        const auto new_id = m_id_to_offset.size();
        m_id_to_offset[new_id] = inserted_offset;
    }
}