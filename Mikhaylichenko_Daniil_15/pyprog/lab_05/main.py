import pygame as pg

from player import Player
from sprite_objects import *
from ray_casting import ray_casting_walls
from drawing import Drawing
from interaction import Interaction

pg.init()
window = pg.display.set_mode((WIDTH, HEIGHT))
window_map = pg.Surface(MINIMAP_RES)

sprites = Sprites()
clock = pg.time.Clock()
player = Player(sprites)
drawing = Drawing(window, window_map, player, clock)
interaction = Interaction(player, sprites, drawing)

drawing.menu()
pg.mouse.set_visible(False)
interaction.play_music()

while True:

    player.movement()
    drawing.background(player.angle)
    walls, wall_shot = ray_casting_walls(player, drawing.textures)
    drawing.world(walls + [obj.object_locate(player) for obj in sprites.list_of_objects])
    drawing.fps(clock)
    drawing.mini_map(player)
    drawing.player_weapon([wall_shot, sprites.sprite_shot])

    interaction.interaction_objects()
    interaction.npc_action()
    interaction.clear_world()
    interaction.check_win()

    pg.display.flip()
    clock.tick(FPS)