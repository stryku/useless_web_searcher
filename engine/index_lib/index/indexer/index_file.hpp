#pragma once

#include "common/db/url_id.hpp"

#include <boost/iostreams/device/mapped_file.hpp>

#include <string>

namespace usl::index::indexer
{
    class index_file
    {
    public:
        explicit index_file(const std::string& path);

        void new_hit(common::db::url_id_t id) const;

    private:
        using hits_t = uint64_t;
        using offset_t = uint64_t;

        struct index_file_entry
        {
            common::db::url_id_t id;
            hits_t hits;
        };

        index_file_entry* get_file_entry(boost::iostreams::mapped_file& file, common::db::url_id_t id) const;
        void append_new_id(common::db::url_id_t id) const;

        const std::string m_path;
    };
}