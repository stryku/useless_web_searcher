#include "index_file_path_builder.hpp"

#include <algorithm>
#include <numeric>

namespace usl::index
{

    std::string index_file_path_builder::build(const std::string &indexes_path,
                                               std::vector<std::string>::const_iterator words_begin,
                                               std::vector<std::string>::const_iterator words_end) const
    {
        const auto k_path_break_step{ 2u };
        size_t break_counter{ 0u };

        std::string path;
        const auto predicted_path_size = predict_path_size(words_begin, words_end);
        path.reserve(predicted_path_size);

        while(words_begin != words_end)
        {
            auto lower = *words_begin++;
            std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
            path.append(lower);
            ++break_counter;
            if(words_begin == words_end)
            {
                path.append(".___idx___");
                break;
            }

            char separator{ '.' };
            if(break_counter == k_path_break_step)
            {
                separator = '/';
                break_counter = 0u;
            }
            path += separator;
        }

        return indexes_path + '/' + path;
    }

    std::string::size_type index_file_path_builder::predict_path_size(words_iterator_t words_begin,
                                                                      words_iterator_t words_end) const
    {
        std::string::size_type size;
        const auto pred = [](auto current, auto word_it)
        {
            return current + word_it.size();
        };

        const auto words_length = std::accumulate(words_begin, words_end, std::string::size_type{}, pred);
        const auto characters_between_count = std::distance(words_begin, words_end);

        return words_length + characters_between_count;
    }
}
