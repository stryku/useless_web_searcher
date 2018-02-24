#include "index/indexer/indexes_storage.hpp"

#include <numeric>

#include <boost/filesystem.hpp>

namespace usl::index::indexer
{
    indexes_storage::indexes_storage(const std::string &working_directory)
        : m_indexes_dir{ working_directory + "/index/indexes" }
    {
        boost::filesystem::create_directories(m_indexes_dir);
    }


    void indexes_storage::new_hit(indexes_storage::word_iterator_t words_begin,
                                  indexes_storage::word_iterator_t words_end,
                                  common::db::url_id_t id) const
    {
        const auto path = build_index_path(words_begin, words_end);


    }

    std::string indexes_storage::build_index_path(word_iterator_t words_begin, word_iterator_t words_end) const
    {
        const auto k_path_break_step{ 2u };
        size_t break_counter{ 0u };

        std::string path;
        const auto predicted_path_size = predict_path_size(words_begin, words_end);
        path.reserve(predicted_path_size);

        while(words_begin != words_end)
        {
            path.append(*words_begin++);
            ++break_counter;
            if(words_begin == words_end)
            {
                break;
            }

            char separator{ '.' };
            if(break_counter == k_path_break_step)
            {
                separator = '/';
                break_counter = 0u;
            }
            path.append(separator);
        }

        return m_indexes_dir + '/' + path;
    }

    std::string::size_type indexes_storage::predict_path_size(word_iterator_t words_begin,
                                                              word_iterator_t words_end) const
    {
        std::string::size_type size;
        const auto pred = [](auto current, auto word_it)
        {
            return current + word_it->size();
        };

        const auto words_length = std::accumulate(words_begin, words_end, std::string::size_type{}, pred);
        const auto characters_between_count = std::distance(words_begin, words_end);

        return words_length + characters_between_count;
    }
}
