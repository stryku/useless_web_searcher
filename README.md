# Useless Web Searcher
![alt text](https://github.com/stryku/useless_web_searcher/blob/master/searcher/gui/useless_logo.png)

A pet project. At this point you probably know that its purpose is not to replace the google, it is useless. I made it as an exercise for multiprocess and multithread applications. At the beginning I treated it as a challenge - wanted to write it during one weekend. Unfortunately whole Saturday I was out of home and started working at 21:00 till end of Sunday + Saturday next week. Basically first 235 commits were made during one weekend so I consider this challenge as completed.

I'm aware that this project is far from being perfect but it was able to crawl and index [http://en.cppreference.com](http://en.cppreference.com) so it is a good starting point.

## What is it?
There are basically two projects - indexing engine and searcher.

## Searcher
Simple Qt application that is able to communicate with index and get search results. You can find it in `searcher` directory.

## Engine
Set of small services that together are able to crawl and index web sites. You can find them in `engine` directory.

Consists of:
* crawl frontier - provides URLs to crawlers
* crawler - downloads web pages contents
* index - indexes page content and provides results for search queries
* parse frontier - provides downloaded pages for parsers
* parser - parses web pages contents
* url_db - storage for URLs

More information about engine's services and searcher you can find in their READMEs

## How it works
1. Start url_db with some seed URLs
2. Start crawl frontier
3. Start crawler[s]
4. Crawler[s] gets URLs from crawl frontier, which gets URLs from url_db.
5. Crawler[s] downloads web pages
6. Start parse frontier.
7. Start parser[s]
8. Parser[s] gets downloaded pages paths from parse frontier
9. Parser[s] parses pages for URLs and text content.
10. Parser[s] inserts URLs into the url_db and sends pages text content to index for indexing
11. Start index. Index receives page text content and indexes it.
12. And so on...


## Building
Most of the services are written in C++17 so you will need a compiler for that. Crawl frontier and crawler are simple python3 scripts.

## Dependencies
* boost
* zmqpp

and if you'd want to build the searcher
* Qt5

## Contribution
If you find this project interesting and would want to contribute - be my guest. Just fork, make changes and create a pull request.
