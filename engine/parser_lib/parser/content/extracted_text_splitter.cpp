#include "parser/content/extracted_text_splitter.hpp"

#include <boost/algorithm/string.hpp>

namespace usl::parser::content
{
    std::vector<extracted_text_splitter::sentence_t> extracted_text_splitter::split(const std::string &text) const
    {
        sentence_t splitted;
        boost::split(splitted, text, ' ');

        std::vector<sentence_t> sentences;

        for(auto i = 0u; i < splitted.size(); ++i)
        {
            sentence_t sentence;

            while(i < splitted.size())
            {
                sentence.emplace_back(std::move(splitted[i++]));

                if(is_end_of_sentence(splitted[i++]))
                {
                    break;
                }
            }

            if(!sentence.empty())
            {
                sentences.emplace_back(std::move(sentence));
            }
        }

        return sentences;
    }

    bool extracted_text_splitter::is_end_of_sentence(const std::string &word) const
    {
        const auto k_patterns = ".!?";
        return std::any_of(std::begin(k_patterns), std::end(k_patterns), word.back());
    }
}
