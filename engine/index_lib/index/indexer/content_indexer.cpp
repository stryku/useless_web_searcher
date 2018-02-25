#include "index/indexer/content_indexer.hpp"
#include "index/indexer/parsed_site_data.hpp"

namespace usl::index::indexer
{
    content_indexer::content_indexer(const std::string &working_directory)
        : m_indexes_storage{ working_directory }
    {}

    void content_indexer::index(const parsed_site_data &site_data) const
    {
        for(const auto& sentence : site_data.sentences)
        {
            index_sentence(sentence, site_data.id);
        }
    }

    void content_indexer::index_sentence(const std::vector<std::string> &sentence, common::db::url_id_t id) const
    {
        const auto k_max_commonly_indexed_words{ 3 };

        if(sentence.empty())
        {
            return;
        }

        for(auto words_count = 1u;
            words_count <= k_max_commonly_indexed_words;
            ++words_count)
        {
            index_words(sentence, words_count, id);
        }
    }

    void content_indexer::index_words(const std::vector<std::string> &sentence,
                                      size_t words_count,
                                      common::db::url_id_t id) const
    {
        auto first_word_idx{ 0u };
        auto last_word_idx{ first_word_idx + words_count };

        while(last_word_idx <= sentence.size())
        {
            auto words_begin = std::next(sentence.cbegin(), first_word_idx);
            auto words_end = std::next(sentence.cbegin(), last_word_idx);

            m_indexes_storage.new_hit(words_begin, words_end, id);
            ++first_word_idx;
            ++last_word_idx;
        }
    }
}
