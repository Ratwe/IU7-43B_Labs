import pygame as pg
from settings import *


class Drawning():
    def __init__(self, sc):
        self.sc = sc
        self.textures = {
            '1': pg.image.load('img/1.jpg').convert()
        }

    def background(self):
        self.sc.blit(self.textures['1'], (0, 0))
