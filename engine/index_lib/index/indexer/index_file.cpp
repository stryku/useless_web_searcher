#include "index/indexer/index_file.hpp"

#include "common/fs/file_creator.hpp"

namespace usl::index::indexer
{
    index_file::index_file(const std::string &path)
        : m_path{ path }
    {
        common::fs::file_creator{ m_path };
    }

    void index_file::new_hit(common::db::url_id_t id) const
    {

    }
}