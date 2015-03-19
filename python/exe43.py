#! /usr/bin/env python
# -*- coding: utf-8 -*-

from sys import exit
from random import randint

class Scene(object):
  
  def enter(self):
    print "This secne is not yet configured. Subclass  it and implement enter()."
    exit(1)

class Engine(object):

  def __init__(self, scene_map):
    self.scene_map = scene_map

  def play(self):
    current_scene = self.scene_map.opening_scene()
    last_scene = self.scene_map.next_scene('finished')

    while current_scene != last_scene:
      next_scene_name = current_scene.enter()
      current_scene = self.scene_map.next_scene(next_scene_name)

    current_scene.enter()

class Death(Scene):

  quips = [
        "you died. Yor kinda suck at this.",
        "Your mom would be proud...if she were smarter.",
        "Suck a luser.",
        "I have a small puppy that's better at this."
      ]

  def enter(self):
    print Death.quips[randint(0, len(self.quips) - 1)]
    exit(1)

class CentralCorridor(Scene):

  def enter(self):
    pass

class LaserWeaponArmory(Scene):

  def enter(self):
    pass

class TheBridge(Scene):

  def enter(self):
    pass

class EscapePod(Scene):
  
  def enter(self):
    pass

class Map(object):
  
  play_map = {
      'death': Death(),
      'central_corridor': CentralCorridor(),
      'laser_weapon_armory': LaserWeaponArmory(),
      'the_bridge': TheBridge(),
      'escape_pod': EscapePod(),
      'finished': Finished()
      }

  def __init__(self, start_scene):
    self.start_scene = start_scene 

  def next_scene(self, scene_name):
    val = Map.play_map.get(scene_name)
    return val

  def opening_scene(slef):
    return self.next_scene(self.start_scene)


a_map = Map('central_corridor')
a_game = Engine(a_map)
a_game.play()
