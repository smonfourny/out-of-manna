#/usr/bin/python

import requests

print "Content-Type: text/html"     # HTML is following
print                               # blank line, end of headers

r = requests.get('http://github.com', allow_redirects=False)
