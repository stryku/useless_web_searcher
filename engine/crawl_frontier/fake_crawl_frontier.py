import zmq
import json
import sys
import time



def main():
    db_address = 'tcp://localhost:5553' if len(sys.argv) < 2 else sys.argv[1]
    print("Starting fake crawl frontier. db addres: {}".format(db_address))
    fake_id = 0
    while True:
        context = zmq.Context()
        socket = context.socket(zmq.REP)
        db_socket = context.socket(zmq.REQ)
        db_socket.connect(db_address)
        socket.bind("tcp://*:5555")

        try:
            while True:
                message = socket.recv()
                print("Received request: %s" % message)


                db_req_data = {
                    'type': 'get_for_processing'
                }
                db_json_str = json.dumps(db_req_data)
                db_msg = ''

                while len(db_msg) == 0:
                    db_socket.send_string(db_json_str)
                    db_msg = db_socket.recv_string()

                    if len(db_msg) > 0:
                        print("received from db: {}, {}".format(len(db_msg), db_msg))
                        data = json.loads(db_msg)
                        json_str = json.dumps(data)
                        print("Sending response: %s" % json_str)
                        socket.send_string(json_str)
                    else:
                        time.sleep(1)

        except Exception as ex:
            print(ex)


if __name__ == "__main__":
    main()
