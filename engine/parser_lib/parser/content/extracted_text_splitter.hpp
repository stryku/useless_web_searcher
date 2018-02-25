#pragma once

#include <string>
#include <vector>


namespace usl::parser::content
{
    // Splits extracted text into sentences
    class extracted_text_splitter
    {
    public:
        using sentence_t = std::vector<std::string>;

        std::vector<sentence_t> split(const std::string& text) const;

    private:
        bool is_end_of_sentence(const std::string& word) const;
    };
}
