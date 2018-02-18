#include "file_to_parse_provider.hpp"

#include <boost/filesystem.hpp>

namespace
{
    const auto locked_directory = "locked";
}

namespace usl::parse_frontier
{
    file_to_parse_provider::file_to_parse_provider(const std::string& working_directory)
        : m_to_parse_directory{ working_directory + "/to_parse" }
    {}

    boost::optional<std::string> file_to_parse_provider::get_file_to_parse()
    {
        using namespace boost::filesystem;

        for(recursive_directory_iterator dir{ m_to_parse_directory }, end;
            dir != end;
            ++dir)
        {
            if (dir->path().filename() == locked_directory)
            {
                dir.no_push();
                continue;
            }

            auto path = dir->path();
            const auto filename = dir->path().filename();
            const auto locked_file_path =  path.remove_filename() / locked_directory / filename;
            boost::filesystem::rename(dir->path(), locked_file_path);
            return locked_file_path.string();
        }

        return boost::none;
    }
}