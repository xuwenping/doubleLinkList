#! /usr/bin/env python
# -*- coding: utf8 -*-

from sys import argv

script, filename = argv
print "the script is: ", script

txt = open(filename)

print "Here is your file %r:" % filename
print txt.read()
txt.close()
print "Type the filename again:"
file_again = raw_input("> ")
txt_again = open(file_again)

print txt_again.read()
txt_again.close()
