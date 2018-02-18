#include "common/communication/server/server_factory.hpp"
#include "common/communication/server/server.hpp"
#include "url_db_req_message_handler.hpp"
#include "url_db/url_db.hpp"
#include "url_db/url_db_loader.hpp"
#include "url_db/url_db_storage.hpp"
#include "common/fs/file_loader.hpp"

#include <easylogging/easylogging++.h>

INITIALIZE_EASYLOGGINGPP

int main(int argc, char* argv[])
{
    if(argc < 3)
    {
        LOG(ERROR) << "usage: parse_frontier working_directory_path bind_ip";
        return 1;
    }

    const auto working_directory = argv[1];
    const auto bind_address = argv[2];

    LOG(INFO) << "URL db starting.";
    LOG(INFO) << "Working directory: " << working_directory;
    LOG(INFO) << "Bind address: " << bind_address;

    auto server = usl::common::communication::server::server_factory{}.create(bind_address);

    std::ofstream{ working_directory + std::string{ "/url_db" }, std::ios::app   };

    usl::common::fs::file_loader file_loader;
    usl::url_db::url_db_storage db_storage{ working_directory, file_loader };
    usl::url_db::url_db db = usl::url_db::url_db_loader{}.load(db_storage);

    //for tests purpose. Add seed url
    db.insert("http://en.cppreference.com/w/");

    server.set_message_handler(usl::url_db::url_db_req_message_handler{ db });

    server.run();

    return 0;
}