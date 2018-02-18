#pragma once

#include "common/string_view.hpp"

#include "url_db/db_entry.hpp"
#include "url_db/url_db.hpp"

#include <vector>

namespace usl
{
    namespace common::fs
    {
        class file_loader;
    }

    namespace url_db
    {
        class url_db_loader
        {
        public:
            explicit url_db_loader(const common::fs::file_loader &file_loader);

            url_db load(string_view file_path) const;
            url_db load(const std::vector<uint8_t>& file_content) const;

        private:
            db_entry* load_next_entry(const std::vector<uint8_t>& file_content, url_db::offset_t offset = 0) const;

            const common::fs::file_loader &m_file_loader;
        };
    }
}
