#! /usr/bin/env python
# -*- coding: utf-8 -*-

# create a mapping of state to abbreviation
states = {
    'Oregon': 'OR',
    'Floriad': 'FL',
    'California': 'CA',
    'New York': 'NY',
    'Michigan': 'MI'
}

# Create a basic set of states and some cities in them
cities = {
    'CA': 'San Francisco',
    'MI': 'Detroit',
    'FL': 'Jacksonville'
}

# add some more cities
cities['NY'] = 'New York'
cities['OR'] = 'Portland'

# print out some cities
print '-' * 10
print "NY State has: ", cities['NY']
print "OR State has: ", cities['OR']
#print some states 
print '-' * 10
print "Michigan's abbreviation is: ", states['Michigan']
print "Floriad's abbreviation is: ", states['Floriad']

#do it by using the state then cities dict
print '-' * 10
print "Michigan has: ", cities[states['Michigan']]
print "Floriad has: ", cities[states['Floriad']]

#print every state abbreviation
print '-' * 10
for state, abbrev in states.items():
  print "%s is abbreviation %s" % (state, abbrev)

#print every city in state
print '-' * 10
for abbrev, city in cities.items():
  print "%s has the city %s" % (abbrev, city)

