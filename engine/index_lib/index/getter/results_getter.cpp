#include "index/getter/results_getter.hpp"
#include "index/page_rank/page_rank.hpp"
#include "index/page_rank/page_rank_storage_entry.hpp"
#include "index/index_file_path_builder.hpp"

namespace usl::index::getter
{
    results_getter::results_getter(page_rank::page_rank &page_rank, const std::string& indexes_dir)
        : m_page_rank{ page_rank }
        , m_indexes_dir{ indexes_dir }
    {}

    std::unordered_map<common::db::url_id_t, double> results_getter::get_results(const std::vector<std::string> &words)
    {
        const auto k_max_words_count{ 3u };
        std::vector<indexer::index_file::index_file_entry> all_hits;
        
        for(size_t count = 1; count <= k_max_words_count; ++count)
        {
            get_for_words(words, count, all_hits);
        }
        std::unordered_map<common::db::url_id_t, double> ranks;

        for(const auto& page_hit: all_hits)
        {
            ranks[page_hit.id] = 0.;
        }

        m_page_rank.get_ranks(ranks);

        for(const auto& page_hit : all_hits)
        {
            ranks[page_hit.id] *= static_cast<double>(page_hit.hits);
        }

        return ranks;
    }

    void results_getter::get_for_words(const std::vector<std::string> &words,
                                       size_t count,
                                       std::vector<indexer::index_file::index_file_entry>& hits)
    {
        auto first_word_idx{ 0u };
        auto last_word_idx{ first_word_idx + count };

        while(last_word_idx <= words.size())
        {
            auto words_begin = std::next(words.cbegin(), first_word_idx);
            auto words_end = std::next(words.cbegin(), last_word_idx);

            const auto index_file_path = index_file_path_builder{}.build(m_indexes_dir, words_begin, words_end);
            const auto all_hits = indexer::index_file{ index_file_path }.get_all();
            hits.insert(hits.end(), all_hits.begin(), all_hits.end());

            ++first_word_idx;
            ++last_word_idx;
        }
    }
}