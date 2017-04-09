import cgi
import cgitb
cgitb.enable(display=0, logdir="./log/")

form = cgi.FieldStorage()
inventory= form.getvalue("inventory")
ra= form.getvalue("URL")

manna,gold=inventory.split(',')

print "Content-Type: text/html"     # HTML is following
print                               # blank line, end of headers
print "<html><head><title>4 2 0</title><!--Linking CSS--><link rel=\"stylesheet\" type=\"text/css\" href=\"../css/style.css\"></head>"
print "<body><div class=\"main\"><div id=\"text\" class=\"output\"><p>It is pitch black. You are likely to be eaten by a grue. </p>"
print "<p>Lorem ipsum dolor sit amet, consectetur adipiscing elit.</p>"
print "</div><div id=\"inv\" class=\"output\"><p><b> Inventory </b> </p><p> gold:%s <p> \"manna\": %s</p>" % (gold,manna)
print "</div></div><div class=\"controls\"><h1>4 2 0</h1><div>"
print "<!-- Temporary, will change to transporter.py once implemented --><form method=\"post\" action=\"http://cs.mcgill.ca/~smonfo1/cgi-bin/transporter.py\">"
print "<input type=\"hidden\" name=\"inventory\" value=\"10,10\"><input type=\"hidden\" name=\"URL\" value=\"http://cs.mcgill.ca/~smonfo1\">"
print "<input id=\"N\" class=\"button\" type=\"submit\" value=\"North\" name=\"North\"></form></div>"
print "<!-- Temporary, will change to transporter.py once implemented --><div><div><form method=\"post\" action=\"http://cs.mcgill.ca/~jlore/cgi-bin/test.cgi\">"
print "<input type=\"hidden\" name=\"inventory\" value=\"10,10\"><input type=\"hidden\" name=\"URL\" value=\"http://cs.mcgill.ca/~smonfo1\">"
print "<input id=\"W\" class=\"button\" type=\"submit\" value=\"West\" name=\"West\"></form></div>"
print "<div><form method=\"post\" action=\"http://cs.mcgill.ca/~jlore/cgi-bin/test.cgi\"><input type=\"hidden\" name=\"inventory\" value=\"10,10\">"
print "<input type=\"hidden\" name=\"URL\" value=\"http://cs.mcgill.ca/~smonfo1\"><input id=\"cmd\" type=\"text\" name=\"command\"></form></div>"
print "<!-- Temporary, will change to transporter.py once implemented --><div><form method=\"post\" action=\"http://cs.mcgill.ca/~jlore/cgi-bin/test.cgi\">"
print "<input type=\"hidden\" name=\"inventory\" value=\"10,10\"><input type=\"hidden\" name=\"URL\" value=\"http://cs.mcgill.ca/~smonfo1\">"
print "<input id=\"E\" class=\"button\" type=\"submit\" value=\"East\" name=\"East\">"
print "</form></div></div><div><!-- Temporary, will change to transporter.py once implemented -->"
print "<form method=\"post\" action=\"http://www.cs.mcgill.ca/~dmarci1/cgi-bin/transporter.py\"><input type=\"hidden\" name=\"inventory\" value=\"10,10\">"
print "<input type=\"hidden\" name=\"URL\" value=\"http://cs.mcgill.ca/~smonfo1\"><input id=\"S\" class=\"button\" type=\"submit\" value=\"South\" name=\"South\">"
print "</form></div></div></body></html>"