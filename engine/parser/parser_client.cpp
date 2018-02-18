#include "parser_client.hpp"

#include "common/fs/file_loader.hpp"
#include "parser/content/content_parser.hpp"
#include "file_paths_to_parse_provider.hpp"

#include <easylogging/easylogging++.h>

#include <thread>

namespace usl::parser
{
    parser_client::parser_client(file_paths_to_parse_provider& file_paths_provider, content::content_parser& parser)
        : m_file_paths_provider{ file_paths_provider }
        , m_parser{ parser }
    {}

    void parser_client::run()
    {
        while(true)
        {
            const auto path = m_file_paths_provider.get();
            const auto file_content = common::fs::file_loader{}.load<std::string>(path);
            const auto str_id = boost::filesystem::basename(path);
            const auto id = std::stoul(str_id);
            const auto extracted_data = extract_url_and_site(file_content);

            m_parser.parse(extracted_data.url, extracted_data.site_content, id);

            std::this_thread::sleep_for(std::chrono::seconds{59990});
        }
    }

    parser_client::url_and_site parser_client::extract_url_and_site(const std::string &file_content)
    {
        url_and_site extracted;

        extracted.url = file_content.c_str();
        const auto url_size = extracted.url.size();
        const auto site_content_begin = std::next(file_content.begin(), url_size + 1u); // +1 to omit null
        extracted.site_content = std::string{ site_content_begin, file_content.end() };

        return extracted;
    }
}