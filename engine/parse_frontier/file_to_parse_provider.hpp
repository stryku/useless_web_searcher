#pragma once

#include <boost/optional.hpp>

#include <experimental/string_view>
#include <string>

namespace usl::parse_frontier
{
    class file_to_parse_provider
    {
    public:
        file_to_parse_provider(std::experimental::string_view to_parse_directory);

        boost::optional<std::string> get_file_to_parse();

    private:
        const std::string m_to_parse_directory;
    };
}
