#include "common/communication/server/server_factory.hpp"
#include "common/communication/server/server.hpp"

#include "index_request_handler.hpp"
#include "index/indexer/indexer.hpp"
#include "index/indexer/content_indexer.hpp"
#include "index/page_rank/page_rank.hpp"
#include "index/getter/results_getter.hpp"

#include <easylogging/easylogging++.h>

INITIALIZE_EASYLOGGINGPP

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        LOG(ERROR) << "usage: index working_directory_path bind_ip";
        return 1;
    }

    const auto working_directory = argv[1];
    const auto bind_address = argc < 3 ? "tcp://*:5552" : argv[2];

    LOG(INFO) << "Indexer starting.";
    LOG(INFO) << "Working directory: " << working_directory;
    LOG(INFO) << "Bind address: " << bind_address;

    auto server = usl::common::communication::server::server_factory{}.create(bind_address);


    usl::index::indexer::content_indexer content_indexer{ working_directory };
    usl::index::page_rank::page_rank page_rank{ working_directory };

    usl::index::indexer::indexer indexer{ page_rank, content_indexer };
    usl::index::getter::results_getter results_getter{ page_rank, working_directory + std::string{ "/indexes" } };

    usl::index::index_request_handler request_handler{ indexer, results_getter };
    server.set_message_handler(std::move(request_handler));

    server.run();

    return 0;
}