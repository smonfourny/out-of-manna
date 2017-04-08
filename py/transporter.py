import cgi
import cgitb
cgitb.enable(display=0, logdir="./log/")

form = cgi.FieldStorage()

