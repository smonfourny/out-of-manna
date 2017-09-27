#!/usr/bin/python

print "Content-Type: text/html"     # HTML is following
print                               # blank line, end of headers


fi = open('../resources.csv', 'r+')
manna,gold,occupied=fi.readline().split(',')
fi.close()

occupied = "0"
fo = open('../resources.csv', 'w+')
separator = ','
elements = [manna, gold, occupied]
newline = separator.join(elements)
fo.write(newline)
fo.close()

fi = open('../log.txt', 'w+')
fi.write("allo lol")
fi.close()
