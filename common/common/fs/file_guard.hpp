#pragma once

#include "common/fs/scoped_file.hpp"

#include <boost/interprocess/sync/file_lock.hpp>

#include <mutex>

namespace usl::common::fs
{
    class file_guard : public scoped_file
    {
    public:
        explicit file_guard(string_view file_path)
            : scoped_file{ get_lock_file_path(file_path).c_str() }
            , m_lock{ path().c_str() }
            , m_lock_guard{ m_lock }
        {}

    private:
        using lock_t = boost::interprocess::file_lock;

        static std::string get_lock_file_path(string_view file_path)
        {
            return std::string{ file_path.data() } + ".lock";
        }

        lock_t m_lock;
        std::lock_guard<lock_t> m_lock_guard;
    };
}
