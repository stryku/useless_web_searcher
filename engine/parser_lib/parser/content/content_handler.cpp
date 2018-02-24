#include "parser/content/content_handler.hpp"

#include "parser/content/text_content_extractor.hpp"
#include "parser/content/extracted_text_cleaner.hpp"
#include "parser/content/extracted_text_splitter.hpp"
#include "parser/data/parse_data_and_response.hpp"

#include <easylogging/easylogging++.h>

namespace usl::parser::content
{
    content_handler::content_handler(const std::string &db_address)
        : m_db_requester{ db_address }
    {}

    void content_handler::handle(std::shared_ptr<data::parse_data_and_response> parse_data)
    {
        LOG(INFO) << "content_handler handling: " << parse_data->data().id;
        const auto extracted_text = text_content_extractor{ parse_data->data().site_content }.extract();
        const auto cleaned_text = extracted_text_cleaner{}.clean(extracted_text);


        LOG(INFO) << "content_handler handling: " << parse_data->data().id << " done";
    }
}
