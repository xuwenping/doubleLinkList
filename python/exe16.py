#! /usr/bin/env python
# -*- coding: utf-8 -*-

from sys import argv

script, filename = argv

print "We're going to erase %r." % filename
print "If you don't want that, hit CTRL-C."
print "If you do want that, hit RETURN."

print "Opening the file..."
target = open(filename, 'w+r')
print "the file contents: \n"
print target.read()
raw_input("?")
print "Truncating the file. GoodByd!"
#target.truncate()

print "Now I'm going to ask you for three lines."

line1 = raw_input("line 1: ")
line2 = raw_input("line 2: ")
line3 = raw_input("line 3: ")

print "I'm going to ask you for three lines."

target.write(line1)
target.write("\n")
target.write(line2)
target.write("\n")
target.write(line3)
target.write("\n")

print "And finally, we close it."
target.close()
