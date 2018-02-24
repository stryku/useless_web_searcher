#pragma once

namespace usl::common::db
{
    enum class state_type : uint8_t
    {
        not_processed,
        processing,
        processed
    };
}
