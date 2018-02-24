#include "index/indexer/indexes_storage.hpp"

#include <boost/filesystem.hpp>

namespace usl::index::indexer
{
    indexes_storage::indexes_storage(const std::string &working_directory)
        : m_indexes_dir{ working_directory + "/index/indexes" }
    {
        boost::filesystem::create_directories(m_indexes_dir);
    }
}
