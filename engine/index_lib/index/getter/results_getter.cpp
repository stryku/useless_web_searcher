#include "index/getter/results_getter.hpp"
#include "index/page_rank/page_rank.hpp"
#include "index/page_rank/page_rank_storage_entry.hpp"
#include "index/indexer/index_file.hpp"
#include "index/index_file_path_builder.hpp"

namespace usl::index::getter
{
    results_getter::results_getter(page_rank::page_rank &page_rank, const std::string& indexes_dir)
        : m_page_rank{ page_rank }
        , m_indexes_dir{ indexes_dir }
    {}

    std::vector<page_rank::page_rank_storage_entry> results_getter::get_results(const std::vector<std::string> &words)
    {
        const auto index_file_path = index_file_path_builder{}.build(m_indexes_dir, words.cbegin(), words.cend());
        const auto all_hits = indexer::index_file{ index_file_path }.get_all();



        return std::vector<page_rank::page_rank_storage_entry>();
    }
}