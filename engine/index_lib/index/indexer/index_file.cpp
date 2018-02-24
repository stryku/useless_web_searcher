#include "index/indexer/index_file.hpp"

#include <iterator>

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

    index_file::index_file_entry* index_file::get_file_entry(boost::iostreams::mapped_file &file,
                                                             common::db::url_id_t id) const
    {
        auto entries_begin = static_cast<index_file_entry*>(file.data());
        const auto entries_end = static_cast<const index_file_entry*>(file.end());

        for(; entries_begin != entries_end; std::advance(entries_begin, 1u))
        {
            if(entries_begin->id == id)
            {
                return entries_begin;
            }
        }

        return nullptr;
    }
}