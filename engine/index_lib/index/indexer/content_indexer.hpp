#pragma once

#include <string>
#include <vector>

namespace usl::index::indexer
{
    class parsed_site_data;

    class content_indexer
    {
    public:
        void index(const parsed_site_data& site_data) const;

    private:
        void index_sentence(const std::vector<std::string>& sentence) const;
        void index_words(const std::vector<std::string>& sentence, size_t words_count) const;

        void index_words(std::vector<std::string>::const_iterator words_begin,
                         std::vector<std::string>::const_iterator words_end) const;
    };
}