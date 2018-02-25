# Args
arg[1] = path to engine working directory (WD)
arg[2] = crawl frontier ip (IP) -- default: tcp://localhost:5555

# Execution algorithm
while true
    URL = get url from crawler frontier
    download site content from URL
    store downloaded site WD/to_parse

# Stored file
## Name
Filename will be equal to URL's id (from urls db)

## Content
Exact downloaded site content

