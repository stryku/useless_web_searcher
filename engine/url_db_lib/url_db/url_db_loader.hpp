#pragma once

#include "common/string_view.hpp"

#include "url_db/db_entry_view.hpp"
#include "url_db/url_db_offset.hpp"
#include "url_db/url_db_storage.hpp"

#include <vector>

namespace usl
{
    namespace common::fs
    {
        class file_loader;
    }

    namespace url_db
    {
        class url_db;
        class url_db_storage;

        class url_db_loader
        {
        public:
            url_db load(url_db_storage storage) const;
            url_db load(const std::vector<uint8_t>& file_content) const;

        private:
            db_entry_view* load_next_entry(const std::vector<uint8_t>& file_content, offset_t offset = 0) const;
        };
    }
}
