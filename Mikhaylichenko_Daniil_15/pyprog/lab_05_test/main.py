import pygame as pg
import math
from settings import *
from drawning import Drawning
from player import Player
from map import world_map
from ray_casting import ray_casting


def main():
    pg.init()
    sc = pg.display.set_mode((WIDTH, HEIGHT))
    drawning = Drawning(sc)
    player = Player()
    clock = pg.time.Clock()

    while True:
        for event in pg.event.get():
            if event.type == pg.QUIT:
                exit()

        player.movement()
        # drawning.background()
        sc.fill(BLACK)

        ray_casting(sc, player.pos, player.angle)
        pg.draw.circle(sc, BLUE, player.pos, 12)
        # pg.draw.line(sc, GREEN, player.pos, (player.x + WIDTH * math.cos(player.angle),
        #                                      player.y + WIDTH * math.sin(player.angle)))
        for x, y in world_map:
            pg.draw.rect(sc, SANDY, (x, y, TILE, TILE), 2)

        pg.display.flip()
        clock.tick(60)


if __name__ == '__main__':
    main()
