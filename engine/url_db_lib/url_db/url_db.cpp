#include "url_db/url_db.hpp"

#include "url_db/db_entry_to_process.hpp"

namespace usl::url_db
{
    const db_entry_view& url_db::get(id_t id) const
    {
        const auto offset = m_id_to_offset[id];
        const auto ptr = m_storage.ptr(offset);

        return *reinterpret_cast<const db_entry_view*>(ptr);
    }

    db_entry_view& url_db::get(url_db::id_t id)
    {
        const auto offset = m_id_to_offset[id];
        const auto ptr = m_storage.ptr(offset);

        return *reinterpret_cast<db_entry_view*>(ptr);
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
        m_not_processed.push(new_id);
    }

    boost::optional<db_entry_to_process> url_db::get_for_processing()
    {
        if(m_not_processed.empty())
        {
            return boost::none;
        }

        const auto id_to_process = m_not_processed.front();
        m_not_processed.pop();

        const auto entry_offset = m_id_to_offset[id_to_process];
        m_storage.update_state(entry_offset, static_cast<uint8_t>(state_type::processing));

        const auto entry = get(id_to_process);
        return db_entry_to_process{ id_to_process, entry.url() };
    }
}