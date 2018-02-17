import urllib.request
import sys


class Crawler:
    def __init__(self, working_dir, crawl_frontier_ip):
        self.working_dir = working_dir
        self.crawl_frontier_ip = crawl_frontier_ip

    def run(self):
        while True:
            site = urllib.request.urlopen("https://stackoverflow.com")
            print(site.headers)


def main():
    while True:
        try:
            crawler = Crawler(sys.argv[1], sys.argv[2])
            crawler.run()
        except Exception as ex:
            print(ex)


if __name__ == "__main__":
    main()
