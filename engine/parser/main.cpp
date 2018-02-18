#include "parser/parser_lib.hpp"

#include <easylogging/easylogging++.h>
#include <zmq.hpp>

#include <chrono>
#include <thread>

INITIALIZE_EASYLOGGINGPP

int main(int argc, char* argv[])
{
    if(argc < 3)
    {
        LOG(ERROR) << "usage: parser working_directory_path parse_frontier_address";
        return 1;
    }

    const auto working_directory = argv[1];
    const auto parse_frontier_address = argv[2];

    LOG(INFO) << "Parser starting.";
    LOG(INFO) << "Working directory: " << working_directory;
    LOG(INFO) << "Parse frontier address: " << parse_frontier_address;

    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REQ);

    LOG(INFO) << "Connecting";
    socket.connect (parse_frontier_address);

    while(true)
    {
        LOG(INFO) << "Sending request";
        zmq::message_t request;
        socket.send (request);

        //  Get the reply.
        zmq::message_t reply;
        socket.recv (&reply);
        std::cout << "Received: " << static_cast<const char*>(reply.data()) << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds{5});
    }
}