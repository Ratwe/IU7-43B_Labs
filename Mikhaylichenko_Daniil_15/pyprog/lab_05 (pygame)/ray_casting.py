import pygame as pg
from map import world_map
from settings import *


def ray_casting(sc, player_pos, player_angle):
    xo, yo = player_pos
    sin_a = math.sin(player_angle)
    cos_a = math.cos(player_angle)
    for depth in range(MAX_DEPTH):
        x = xo + depth * cos_a
        y = yo + depth * sin_a
        pg.draw.line(sc, GREEN, player_pos, (x, y))
