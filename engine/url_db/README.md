# Args
* argv[1] = path to working directory
* argv[2] = bind ip

# Overview
URL db stores set of unique urls along with its metadata.

# Entry structure
* uint8_t status - 0: not processed, 1 processing, 2 processed
* null terminated string absolute url

# Requests
* get_for_processing() - response : { absolute url, id }
* get(id) - response: { absolute }
* insert(absolute url) - response: { ok } - if url is already in the db, it's noop
