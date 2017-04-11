#!/usr/bin/python

import cgi
import cgitb
import requests

cgitb.enable()

form = cgi.FieldStorage()
inventory = form.getvalue("inventory")
ra= form.getvalue("URL")

print "Content-Type: text/html"     # HTML is following
print                               # blank line, end of headers


fi = open('../resources.csv', 'r')
resources = fi.readline();
fi.close();

room_manna, room_gold, room_occupied=resources.split(',')
if (room_occupied == "1"):
    r = requests.post(ra, data={'inventory':inventory, 'URL':'http://cs.mcgill.ca/~smonfo1/cgi-bin/room.cgi'})
    print r.text
else:
    fo = open('../resources.csv', 'w')
    resources = ','
    elements = (room_manna, room_gold, "1")
    resources = resources.join(elements)
    fo.write(resources)
    fo.close()

    ra = ra.replace('cgi-bin/room.cgi', 'cgi-bin/success.py')
    r = requests.post(ra, data={'inventory':inventory, 'URL':'http://cs.mcgill.ca/~smonfo1/cgi-bin/room.cgi'}, allow_redirects=False)
    print "<head>"
    manna,gold = inventory.split(',')
    manna = int(manna) - 1 
    manna = str(manna)
    separator = ','
    elements = (manna, gold)
    new_request = separator.join(elements)
    
    b = requests.post("http://cs.mcgill.ca/~smonfo1/cgi-bin/room.cgi", data={'inventory':new_request, 'command':"REFRESH"}, headers={'content-type':'text/html'}, verify=True, allow_redirects=True)
    print b.text