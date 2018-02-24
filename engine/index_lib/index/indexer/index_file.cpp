#include "index/indexer/index_file.hpp"

#include "common/fs/file_creator.hpp"

#include <iterator>
#include <fstream>

namespace usl::index::indexer
{
    index_file::index_file(const std::string &path)
        : m_path{ path }
    {
        common::fs::file_creator{ m_path };
    }

    void index_file::new_hit(common::db::url_id_t id) const
    {
        boost::iostreams::mapped_file file;
        file.open(m_path, boost::iostreams::mapped_file::mapmode::readwrite);

        auto entry = get_file_entry(file, id);

        if(!entry)
        {
            file.close();
            append_new_id(id);
        }

        ++(entry->hits);
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

    void index_file::append_new_id(common::db::url_id_t id) const
    {
        std::ofstream file{ m_path, std::ios::app | std::ios::binary };
        index_file_entry entry{ id, 1u };
        file.write(reinterpret_cast<const char*>(&entry), sizeof(entry));
    }
}