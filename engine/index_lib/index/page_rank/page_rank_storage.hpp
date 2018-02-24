#pragma once

#include "common/db/url_id.hpp"

#include <boost/iostreams/device/mapped_file.hpp>

#include <string>

namespace usl::index::page_rank
{
    struct page_rank_storage_entry;

    class page_rank_storage
    {
    public:
        explicit page_rank_storage(const std::string& working_directory_path);

        void update(common::db::url_id_t id, double rank) const;
        double get_rank(common::db::url_id_t id) const;

    private:
        using offset_t = uint64_t;

        bool need_grow(common::db::url_id_t id) const;
        bool is_in_file(common::db::url_id_t id) const;
        offset_t get_entry_offset(common::db::url_id_t id) const;

        void grow(common::db::url_id_t id) const;
        page_rank_storage_entry& get_file_entry(boost::iostreams::mapped_file& file,
                                                common::db::url_id_t id) const;

    private:
        const std::string m_storage_file_path;
    };
}