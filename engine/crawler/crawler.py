import urllib.request
import sys
import json
import zmq
import time


class Crawler:
    def __init__(self, working_dir, crawl_frontier_ip):
        self.working_dir = working_dir
        self.crawl_frontier_ip = crawl_frontier_ip
        self.context = zmq.Context()
        self.socket = self.context.socket(zmq.REQ)

    def run(self):
        print("connecting to crawl frontier: %s" % self.crawl_frontier_ip)
        self.socket.connect(self.crawl_frontier_ip)

        while True:
            print("sending request")
            self.socket.send(b'')
            received = self.socket.recv_string()
            print("received response: %s" % received)
            data = json.loads(received)
            print("downloading site from: %s" % data['url'])
            site = urllib.request.urlopen(data['url'])
            print(site.headers)
            time.sleep(2)


def main():
    while True:
        try:
            crawler = Crawler(sys.argv[1], sys.argv[2])
            crawler.run()
        except Exception as ex:
            print(ex)


if __name__ == "__main__":
    main()
