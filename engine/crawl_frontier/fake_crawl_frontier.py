import zmq
import json



def main():
    print("Starting fake crawl frontier")

    fake_id = 0
    while True:
        try:
            context = zmq.Context()
            socket = context.socket(zmq.REP)
            db_address = 'tcp://localhost:5553'
            socket.bind("tcp://*:5555")
            message = socket.recv()
            print("Received request: %s" % message)

            db_socket = context.socket(zmq.REQ)
            db_socket.connect(db_address)

            db_req_data = {
                'type': 'get_for_processing'
            }
            db_json_str = json.dumps(db_req_data)
            db_socket.send_string(db_json_str)
            db_msg = db_socket.recv_string()
            print("received from db: %s" % db_msg)

            data = json.load_string(db_msg)


            """data = {
                'url': 'http://en.cppreference.com/w/cpp/string/basic_string_view/find',
                'id': fake_id
            }"""


            json_str = json.dumps(data)
            print("Sending response: %s" % json_str)
            socket.send_string(json_str)
            fake_id += 1
        except Exception as ex:
            print(ex)


if __name__ == "__main__":
    main()
