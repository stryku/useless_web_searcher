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

    def get_next_url_data(self):
        print("sending request")
        self.socket.send(b'')
        received = self.socket.recv_string()
        print("received response: %s" % received)
        return json.loads(received)

    def download_site_content(self, url):
        print("downloading site from: %s" % url)
        site = urllib.request.urlopen(url)
        return site.read()

    def store_site(self, url_data, site_content):
        pass

    def run(self):
        print("connecting to crawl frontier: %s" % self.crawl_frontier_ip)
        self.socket.connect(self.crawl_frontier_ip)

        while True:
            url_data = self.get_next_url_data()
            site_content = self.download_site_content(url_data['url'])
            self.store_site(url_data, site_content)
            time.sleep(4)


def main():
    while True:
        try:
            crawler = Crawler(sys.argv[1], sys.argv[2])
            crawler.run()
        except Exception as ex:
            print(ex)


if __name__ == "__main__":
    main()
