import urllib.request
site = urllib.request.urlopen("https://stackoverflow.com").read()

print(site)
