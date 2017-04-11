#!/usr/bin/python

import cgi
import cgitb
import requests

cgitb.enable()

form = cgi.FieldStorage()
inventory= form.getvalue("inventory")
ra= form.getvalue("URL")

print "Content-Type: text/html"     # HTML is following
print                               # blank line, end of headers


fi = open('../resources.csv', 'r')
resources = fi.readline();
fi.close();

room_manna, room_gold, room_occupied=resources.split(',')
if (room_occupied == "1"):
    r = requests.post(ra, data={'inventory':inventory, 'URL':'http://cs.mcgill.ca/~smonfo1/cgi-bin/room.cgi'})
else:
    fo = open('../resources.csv', 'w')
    resources = ','
    elements = (room_manna, room_gold, "1")
    resources = resources.join(elements)
    fo.write(resources)
    fo.close()

    manna,gold=inventory.split(',')

    print """<html>
    <head>
        <title>T h e F l o r a l S h o p p e</title>
        <!--Linking CSS-->
        <link rel="stylesheet" type="text/css" href="./css/style.css">
    </head>
    <body>
    <div class="main" id="bg">
        <div id="text" class="output">
            <p> Welcome to my F l o r a l  S h o p p e. I am blank.banshee </p>
            <p> In this d i g i t a l reality, you can DROP 2 gold to get 1 manna. You may also REFRESH yourself with some delicious Arizona Iced Tea (c).</p>
            <p> Type PLAY to PLAY. Type EXIT to EXIT this mortal coil. </p>
            <p> Click a direction to travel to a new world. </p>
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
        <!-- Temporary, will change to transporter.py once implemented -->
        <form method="post" action="http://cs.mcgill.ca/~smonfo1/cgi-bin/transporter.py">
            <input type="hidden" name="inventory" value="%s,%s">
            <input type="hidden" name="URL" value="http://cs.mcgill.ca/~smonfo1">
            <input type="hidden" name="direc" value="North">
            <input id="N" class="button" type="submit" value="North" name="North">
        </form>
        </div>
        <!-- Temporary, will change to transporter.py once implemented -->
        <div>
            <div>
            <form method="post" action="http://cs.mcgill.ca/~jlore/cgi-bin/test.cgi">
                <input type="hidden" name="inventory" value="%s,%s">
                <input type="hidden" name="URL" value="http://cs.mcgill.ca/~smonfo1">
                <input type="hidden" name="direc" value="West">
                <input id="W" class="button" type="submit" value="West" name="West">
            </form>
            </div>
            <div>
            <form method="post" action="http://cs.mcgill.ca/~jlore/cgi-bin/test.cgi">
                <input type="hidden" name="inventory" value="%s,%s">
                <input id="cmd" type="text" name="command">
            </form>
            </div>
            <!-- Temporary, will change to transporter.py once implemented -->
            <div>
            <form method="post" action="http://cs.mcgill.ca/~jlore/cgi-bin/test.cgi">
                <input type="hidden" name="inventory" value="%s,%s">
                <input type="hidden" name="URL" value="http://cs.mcgill.ca/~smonfo1">
                <input type="hidden" name="direc" value="East">
                <input id="E" class="button" type="submit" value="East" name="East">
            </form>
            </div>
        </div>
        <div>
        <!-- Temporary, will change to transporter.py once implemented -->
        <form method="post" action="http://cs.mcgill.ca/~smonfo1/cgi-bin/pretransport.py">
            <input type="hidden" name="inventory" value="%s,%s">
            <input type="hidden" name="URL" value="http://cs.mcgill.ca/~smonfo1">
            <input type="hidden" name="direc" value="South">
            <input id="S" class="button" type="submit" value="South" name="South">
        </form>
        </div>
    </div>
    </body>
</html>""" % (gold, manna, manna, gold, manna, gold, manna, gold, manna, gold, manna, gold)