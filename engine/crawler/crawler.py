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
        print('sending request')
        self.socket.send(b'')
        received = self.socket.recv_string()
        print('received response: %s' % received)
        return json.loads(received)

    def download_site_content(self, url):
        print('downloading site from: %s' % url)
        site = urllib.request.urlopen(url)
        return site.read()

    def build_site_filename(self, url_data):
        return '{}/to_parse/{}'.format(self.working_dir, str(url_data['id']))

    def store_site(self, url_data, site_content):
        path_to_store = self.build_site_filename(url_data)
        print('storing site to: %s' % path_to_store)
        with open(path_to_store, mode='wb') as file:
            file.write(site_content)

    def run(self):
        print('connecting to crawl frontier: %s' % self.crawl_frontier_ip)
        self.socket.connect(self.crawl_frontier_ip)

        while True:
            url_data = self.get_next_url_data()
            site_content = self.download_site_content(url_data['url'])
            self.store_site(url_data, site_content)
            time.sleep(4)


def main():
    if len(sys.argv) < 3:
        print("usage: crawler working_directory crawl_frontier_ip")
        return

    while True:
        try:
            crawler = Crawler(sys.argv[1], sys.argv[2])
            crawler.run()
        except Exception as ex:
            print(ex)


if __name__ == "__main__":
    main()
