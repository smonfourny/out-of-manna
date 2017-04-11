#!/usr/bin/python

import requests
import cgi
import cgitb

cgitb.enable(display=0, logdir="log")

form = cgi.FieldStorage()
inventory = form.getvalue("inventory")
ra = form.getvalue("URL")
direc = form.getvalue("direc")

fi = open("../resources.csv", 'r+')
line = fi.readline()
fi.close()

manna, gold, occupied=line.split(",")
occupied = "0"
separator =","
elements = [manna, gold, occupied]

newline=separator.join(elements)
fo = open("../resources.csv", 'w+')
fo.write(newline)
fo.close()

if (direc == "West"):

    r = requests.gett('http://www.cs.mcgill.ca/~dmarci1/cgi-bin/transporter.py', data={'inventory':inventory, 'URL':ra})
elif (direc == "East"):
    r = requests.get("http://www.cs.mcgill.ca/~dmarci1/cgi-bin/transporter.py", data={"inventory":inventory, "URL":ra})
elif (direc == "North"):
    r = requests.get("http://www.cs.mcgill.ca/~dmarci1/cgi-bin/transporter.py", data={"inventory":inventory, "URL":ra})
elif (direc == "South"):
    r = requests.get("http://www.cs.mcgill.ca/~dmarci1/cgi-bin/transporter.py", data={"inventory":inventory, "URL":ra}, allow_redirects=True)
else:
    pass