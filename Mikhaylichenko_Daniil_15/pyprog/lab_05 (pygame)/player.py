from settings import *
import pygame as pg
import math


class Player:
    def __init__(self):
        self.x, self.y = player_pos
        self.angle = player_angle

    @property
    def pos(self):
        return self.x, self.y

    def movement(self):
        keys = pg.key.get_pressed()

        if keys[pg.K_w]:
            self.y -= player_speed
            self.angle = 270 * math.pi / 180
            # print('W')
        elif keys[pg.K_s]:
            self.y += player_speed
            self.angle = 90 * math.pi / 180
            # print('S')
        elif keys[pg.K_a]:
            self.x -= player_speed
            self.angle = math.pi
            # print('A')
        elif keys[pg.K_d]:
            self.x += player_speed
            self.angle = 0
            # print('D')
        if keys[pg.K_ESCAPE]:
            exit()
