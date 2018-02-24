#pragma once

namespace usl::common::db
{
    enum class url_state : uint8_t
    {
        not_processed,
        processing,
        processed
    };
}
