#pragma once

#include <boost/optional.hpp>

#include <string>

namespace usl::parse_frontier
{
    class file_to_parse_provider
    {
    public:
        explicit file_to_parse_provider(const std::string& working_directory);

        boost::optional<std::string> get_file_to_parse();

    private:
        const std::string m_to_parse_directory;
    };
}
