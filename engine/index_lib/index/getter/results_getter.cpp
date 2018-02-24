#include "index/getter/results_getter.hpp"
#include "index/page_rank/page_rank.hpp"
#include "index/page_rank/page_rank_storage_entry.hpp"

namespace usl::index::getter
{
    results_getter::results_getter(page_rank::page_rank &page_rank)
        : m_page_rank{ page_rank }
    {}

    std::vector<page_rank::page_rank_storage_entry> results_getter::get_results(const std::vector<std::string> &words)
    {
        return std::vector<page_rank::page_rank_storage_entry>();
    }
}