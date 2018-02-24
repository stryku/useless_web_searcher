#include "index/page_rank/page_rank_storage.hpp"
#include "index/page_rank/page_rank_storage_entry.hpp"

#include "common/fs/file_creator.hpp"

#include <boost/filesystem.hpp>

namespace usl::index::page_rank
{
    page_rank_storage::page_rank_storage(const std::string &working_directory_path)
        : m_storage_file_path{ working_directory_path + "/index/page_rank" }
    {
        common::fs::file_creator{ m_storage_file_path };
    }

    void page_rank_storage::update(common::db::url_id_t id, double rank)
    {

    }

    bool page_rank_storage::need_grow(common::db::url_id_t id) const
    {
        const auto file_size = boost::filesystem::file_size(m_storage_file_path);
        return file_size < get_entry_offset(id);
    }

    page_rank_storage::offset_t page_rank_storage::get_entry_offset(common::db::url_id_t id) const
    {
        return id * sizeof(page_rank_storage_entry);
    }
}
