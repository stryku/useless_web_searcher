#pragma once

#include <string>

namespace usl::index::indexer
{
    class indexes_storage
    {
    public:
        explicit indexes_storage(const std::string& working_directory);

    private:
        const std::string m_indexes_dir;
    };
}
