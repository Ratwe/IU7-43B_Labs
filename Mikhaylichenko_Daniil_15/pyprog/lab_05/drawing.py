import pygame as pg
from settings import *
from map import mini_map
from collections import deque
from random import randrange
import sys
from time import sleep

class Drawing:
    def __init__(self, window, window_map, player, clock):
        self.window = window
        self.window_map = window_map
        self.player = player
        self.clock = clock
        self.font = pg.font.SysFont('Arial', 36, bold=True)
        self.font_win = pg.font.Font('font/Tobec___.ttf', 100)
        self.textures = {
            1: pg.image.load('img/wall1.png').convert(),
            2: pg.image.load('img/wall2.png').convert(),
            3: pg.image.load('img/wall1.png').convert(),
            4: pg.image.load('img/wall2.png').convert(),
            'S': pg.image.load('img/sky3.png').convert()
        }

        # menu
        self.menu_trigger = True
        self.menu_picture = pg.image.load('img/bg.jpg').convert()

        # weapon parameters
        self.weapon_base_sprite = pg.image.load('sprites/weapons/shotgun/base/0.png').convert_alpha()
        self.weapon_shot_animation = deque([pg.image.load(f'sprites/weapons/shotgun/shot/{i}.png').convert_alpha()
                                            for i in range(20)])

        self.weapon_rect = self.weapon_base_sprite.get_rect()
        self.weapon_pos = (HALF_WIDTH - self.weapon_rect.width // 2, HEIGHT - self.weapon_rect.height)
        self.shot_length = len(self.weapon_shot_animation)
        self.shot_length_count = 0
        self.shot_animation_speed = 3
        self.shot_animation_count = 0
        self.shot_animation_trigger = True
        self.shot_sound = pg.mixer.Sound('sound/shot-and-reload.mp3')

        # sfx parameters
        self.sfx = deque([pg.image.load(f'sprites/weapons/sfx/{i}.png').convert_alpha() for i in range(9)])
        self.sfx_length_count = 0
        self.sfx_length = len(self.sfx)

    def background(self, angle):
        sky_offset = -10 * math.degrees(angle) % WIDTH
        self.window.blit(self.textures['S'], (sky_offset, 0))
        self.window.blit(self.textures['S'], (sky_offset - WIDTH, 0))
        self.window.blit(self.textures['S'], (sky_offset + WIDTH, 0))
        pg.draw.rect(self.window, DARKGRAY, (0, HALF_HEIGHT, WIDTH, HALF_HEIGHT))

    def world(self, world_objects):
        for obj in sorted(world_objects, key=lambda n: n[0], reverse=True):
            if obj[0]:
                _, object, object_pos = obj
                self.window.blit(object, object_pos)

    def fps(self, clock):
        display_fps = str(int(clock.get_fps()))
        render = self.font.render(display_fps, 0, DARKORANGE)
        self.window.blit(render, FPS_POS)

    def mini_map(self, player):
        self.window_map.fill(BLACK)
        map_x, map_y = player.x // MAP_SCALE, player.y // MAP_SCALE
        pg.draw.line(self.window_map, YELLOW, (map_x, map_y), (map_x + 12 * math.cos(player.angle),
                                                               map_y + 12 * math.sin(player.angle)), 2)
        pg.draw.circle(self.window_map, RED, (int(map_x), int(map_y)), 5)
        for x, y in mini_map:
            pg.draw.rect(self.window_map, DARKBROWN, (x, y, MAP_TILE, MAP_TILE))
        self.window.blit(self.window_map, MAP_POS)

    def player_weapon(self, shots):
        if self.player.shot:
            if not self.shot_length_count:
                self.shot_sound.play()

            self.shot_projection = min(shots)[1] // 2
            self.bullet_sfx()
            shot_sprite = self.weapon_shot_animation[0]
            self.window.blit(shot_sprite, self.weapon_pos)
            self.shot_animation_count += 1

            if self.shot_animation_count == self.shot_animation_speed:
                self.weapon_shot_animation.rotate(-1)
                self.shot_animation_count = 0
                self.shot_length_count += 1
                self.shot_animation_trigger = False

            if self.shot_length_count == self.shot_length:
                self.player.shot = False
                self.shot_length_count = 0
                self.sfx_length_count = 0
                self.shot_animation_trigger = True
        else:
            self.window.blit(self.weapon_base_sprite, self.weapon_pos)

    def bullet_sfx(self):
        if self.sfx_length_count < self.sfx_length:
            sfx = pg.transform.scale(self.sfx[0], (self.shot_projection, self.shot_projection))
            sfx_rect = sfx.get_rect()
            self.window.blit(sfx, (HALF_WIDTH - sfx_rect.w // 2, HALF_HEIGHT - sfx_rect.h // 2))
            self.sfx_length_count += 1
            self.sfx.rotate(-1)

    def win(self):
        sleep(4)
        render = self.font_win.render('To be continued...', 1, WHITE)
        rect = pg.Rect(0, 0, 1000, 175)
        rect.center = HALF_WIDTH, HALF_HEIGHT
        pg.draw.rect(self.window, BLACK, rect, border_radius=50)
        self.window.blit(render, (rect.centerx - 430, rect.centery - 50))
        pg.display.flip()
        self.clock.tick(15)

    def menu(self):
        x = 0
        button_font = pg.font.Font('font/font.ttf', 72)
        label_font = pg.font.Font('font/font1.otf', 270)
        start = button_font.render('START', 1, pg.Color('yellow'))
        button_start = pg.Rect(0, 0, 400, 150)
        button_start.center = HALF_WIDTH, HALF_HEIGHT
        exit = button_font.render('EXIT', 1, pg.Color('yellow'))
        button_exit = pg.Rect(0, 0, 400, 150)
        button_exit.center = HALF_WIDTH, HALF_HEIGHT + 200

        while self.menu_trigger:
            for event in pg.event.get():
                if event.type == pg.QUIT:
                    pg.quit()
                    sys.exit()

            self.window.blit(self.menu_picture, (0, 0), (x % WIDTH, HALF_HEIGHT, WIDTH, HEIGHT))
            x += 1

            pg.draw.rect(self.window, SKYBLUE, button_start, border_radius=25, width=10)
            self.window.blit(start, (button_start.centerx - 130, button_start.centery - 70))

            pg.draw.rect(self.window, SKYBLUE, button_exit, border_radius=25, width=10)
            self.window.blit(exit, (button_exit.centerx - 85, button_exit.centery - 70))

            color = randrange(40)
            label = label_font.render('HAPPINESS', 1, (200 + color, 215 + color, color))
            self.window.blit(label, (15, -30))

            mouse_pos = pg.mouse.get_pos()
            mouse_click = pg.mouse.get_pressed()
            if button_start.collidepoint(mouse_pos):
                pg.draw.rect(self.window, SKYBLUE, button_start, border_radius=25)
                self.window.blit(start, (button_start.centerx - 130, button_start.centery - 70))
                if mouse_click[0]:
                    self.menu_trigger = False
            elif button_exit.collidepoint(mouse_pos):
                pg.draw.rect(self.window, SKYBLUE, button_exit, border_radius=25)
                self.window.blit(exit, (button_exit.centerx - 85, button_exit.centery - 70))
                if mouse_click[0]:
                    pg.quit()
                    sys.exit()

            pg.display.flip()
            self.clock.tick(20)
