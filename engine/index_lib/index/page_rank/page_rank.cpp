#include "index/page_rank/page_rank.hpp"

namespace usl::index::page_rank
{
    page_rank::page_rank(const std::string &working_directory)
        : m_page_rank_storage{ working_directory }
    {}

    void page_rank::new_page_reference(common::db::url_id_t id)
    {
        const auto k_page_reference_points = .1;
        const auto current_rank = m_page_rank_storage.get_rank(id);
        const auto fixed_rank = current_rank < 1. ? 1. : current_rank;
        m_page_rank_storage.update(id, fixed_rank + k_page_reference_points);
    }

    double page_rank::get_rank(common::db::url_id_t id) const
    {
        return m_page_rank_storage.get_rank(id);
    }

    void page_rank::get_ranks(std::unordered_map<common::db::url_id_t, double>& ids) const
    {
        m_page_rank_storage.get_ranks(ids);
    }
}
