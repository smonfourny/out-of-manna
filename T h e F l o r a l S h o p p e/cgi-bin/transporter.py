#!/usr/bin/python

import cgi
import cgitb
import requests

cgitb.enable()

form = cgi.FieldStorage()
inventory = form.getvalue("inventory")
ra= form.getvalue("URL")

log = open('log.txt', 'w+')

print "Content-Type: text/html"     # HTML is following
print                               # blank line, end of headers

fi = open('../resources.csv', 'r')
resources = fi.readline();
fi.close();

manna,gold = inventory.split(',')

room_manna, room_gold, room_occupied=resources.split(',')
if (room_occupied == "1"):
    formatted_data = "inventory={}%2C{}&command=REFRESH".format(manna, gold)
    print """<html>
    <head>
        <title>T h e F l o r a l S h o p p e</title>
        <!--Linking CSS-->
        <link rel="stylesheet" type="text/css" href="../css/exit.css">
    </head>
    <body>
    <div class="main" id="bg">
        <div id="text" class="output">
            <p>This room is occupied, mortal ! L e a v e</p>
        </div>
        <div id="inv" class="output">
            <p><b> Inventory </b> </p>
            <p> gold: %s </p>
            <p> "manna": %s </p>
        </div>
    </div>
    <div class="controls">

        <h1>The F l o r a l Shoppe</h1>
        <div>
        <div>
        <form method="post" action="%s">
            <input type="hidden" name="inventory" value="%s,%s">
            <input type="hidden" name="command" value="REFRESH">
            <input type="hidden" name="direc" value="South">
            <input id="leave" class="button" type="submit" value="Normies get out !" name="leave">
        </form>
        </div>
    </div>
    </body>
</html>""" % (gold, manna, ra, manna, gold)
else:
    manna = int(manna) - 1
    manna = str(manna)
    formatted_data = "inventory={}%2C{}&command=REFRESH".format(manna, gold)
    log.write("reached else statement")
    fo = open('../resources.csv', 'w')
    resources = ','
    elements = (room_manna, room_gold, "1")
    resources = resources.join(elements)
    fo.write(resources)
    fo.close()

    log.write("\n wrote to resources.csv")
    log.close()

    ra = ra.replace('cgi-bin/room.cgi', 'cgi-bin/success.py')
    if (ra == "http://cs.mcgill.ca/~jmanal2/cgi-bin/success.py"):
        success_data = "inventory={}%2C{}&URL=http://cs.mcgill.ca/~smonfo1/cgi-bin/".format(manna, gold)
    else:
        success_data = "inventory={}%2C{}&URL=http://cs.mcgill.ca/~smonfo1/cgi-bin/room.cgi".format(manna, gold)
    r = requests.post(ra, data=success_data, allow_redirects=False)
    
    b = requests.post("http://cs.mcgill.ca/~smonfo1/cgi-bin/room.cgi", data=formatted_data, allow_redirects=True)
    print b.text
