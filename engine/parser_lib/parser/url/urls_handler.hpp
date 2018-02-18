#pragma once

#include <easylogging/easylogging++.h>

namespace usl::parser::url
{
    class urls_handler
    {
    public:
        void handle(const std::string& content);
    };
}
