#pragma once

#include <string>
#include <vector>

namespace usl::index
{
    class index_file_path_builder
    {
    public:
        using words_iterator_t = std::vector<std::string>::const_iterator;

        std::string build(const std::string& indexes_path,
                          words_iterator_t words_begin,
                          words_iterator_t words_end) const;

    private:
        std::string::size_type predict_path_size(words_iterator_t words_begin, words_iterator_t words_end) const;
    };
}