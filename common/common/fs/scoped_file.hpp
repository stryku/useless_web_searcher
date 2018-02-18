#pragma once

#include "common/string_view.hpp"

#include <boost/filesystem.hpp>

#include <fstream>

namespace usl::common::fs
{
    class scoped_file
    {
    public:
        explicit scoped_file(string_view path)
            : m_path{ path.data() }
        {
            std::ofstream{ m_path };
        }

        ~scoped_file()
        {
            boost::filesystem::remove(path());
        }

        const std::string& path() const
        {
            return m_path;
        }

    private:
        const std::string m_path;
    };
}
