#include "index/page_rank/page_rank.hpp"

namespace usl::index::page_rank
{
    page_rank::page_rank(const std::string &working_directory)
        : m_page_rank_storage{ working_directory }
    {}

    void page_rank::new_page_reference(common::db::url_id_t id)
    {
        const auto k_page_reference_points = 0.1;
        const auto current_rank = m_page_rank_storage.get_rank(id);
        m_page_rank_storage.update(id, current_rank + k_page_reference_points);
    }

    double page_rank::get_rank(common::db::url_id_t id) const
    {
        return m_page_rank_storage.get_rank(id);
    }
}
