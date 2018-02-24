#include "index/indexer/content_indexer.hpp"
#include "index/indexer/parsed_site_data.hpp"

namespace usl::index::indexer
{
    void content_indexer::index(const parsed_site_data &site_data) const
    {
        for(const auto& sentence : site_data.sentences)
        {

        }
    }

    void content_indexer::index_sentence(const std::vector<std::string> &sentence) const
    {
        const auto k_max_commonly_indexed_words{ 3 };

        if(sentence.empty())
        {
            return;
        }

        for(auto words_count = 1u; words_count <= k_max_commonly_indexed_words; ++words_count)
        {

        }
    }

    void content_indexer::index_words(const std::vector<std::string> &sentence, size_t words_count) const
    {
        auto first_word_idx{ 0u };
        auto last_word_idx{ first_word_idx + words_count };

        while(last_word_idx <= sentence.size())
        {
            auto words_begin = std::next(sentence.cbegin(), first_word_idx);
            auto words_end = std::next(sentence.cbegin(), last_word_idx);

            index_words(words_begin, words_end);
            ++first_word_idx;
            ++last_word_idx;
        }
    }

    void content_indexer::index_words(std::vector<std::string>::const_iterator words_begin,
                                      std::vector<std::string>::const_iterator words_end) const
    {

    }
}
