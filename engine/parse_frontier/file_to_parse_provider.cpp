#include "file_to_parse_provider.hpp"

#include <boost/filesystem.hpp>

namespace
{
    const auto locked_directory = "locked";
}

namespace usl::parse_frontier
{
    file_to_parse_provider::file_to_parse_provider(std::experimental::string_view to_parse_directory)
        : m_to_parse_directory{ to_parse_directory }
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

            const auto locked_file_path = locked_directory / dir->path();
            boost::filesystem::rename(dir->path(), locked_file_path);
            return locked_file_path.string();
        }

        return boost::none;
    }
}