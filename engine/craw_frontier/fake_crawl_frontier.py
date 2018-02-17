import zmq
import json


def main():
    print("Starting fake crawl frontier")

    fake_id = 0
    while True:
        try:
            context = zmq.Context()
            socket = context.socket(zmq.REP)
            socket.bind("tcp://*:5555")
            message = socket.recv()
            print("Received request: %s" % message)

            data = {
                'url': 'http://www.google.pl',
                'id': fake_id
            }

            json_str = json.dumps(data)
            print("Sending response: %s" % json_str)
            socket.send_string(json_str)
            fake_id += 1
        except Exception as ex:
            print(ex)


if __name__ == "__main__":
    main()
