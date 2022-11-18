size = [ 1500, 500 ]
FPS = 60
count__ = 0
running = True
count_layers = 10
layer_offset = 12
color_offset = 8
cloud_size = ( 200, 100 )
cloud_offset = 100
cloud_filenames = [ 'cloud.png', 'cloud1.png', 'cloud2.png', 'cloud3.png', 'cloud4.png', 'cloud5.png', 'cloud6.png', 'cloud7.png' ]

ground_color = [ 6, 68, 32 ]
cloud_color = [255, 255, 255 ]
ground_size = ( 711, 400 )
layers = []
ground_layers = []
cloud_layers = []
paralax_scale = 0.9
move_speed = -16
cloud_speed = -10
hero_layer = 17
rainbow_color = False

import pygame as pg
import random
from pygame.locals import *

class Layer:
    def __init__(self, image_names, color, img_size, offset):
        self.color = color
        self.offset = offset
        self.image_names = image_names
        self.img_size = img_size
        base_pos = ( random.randrange(size[0]), size[1] - offset )

        middle = Sprite(random.choice(self.image_names), color, img_size, base_pos)
        self.objects = [ middle ]
        
        self.leftid = 0
        while (self.objects[self.leftid].rect.right > 0):
            left = Sprite(random.choice(self.image_names), color, img_size, base_pos)
            left.rect.right = self.objects[self.leftid].rect.left
            left.update_pos() 
            self.leftid = len(self.objects)
            self.objects.append(left)
       
        self.rightid = 0
        while (self.objects[self.rightid].rect.left < size[0]):
            right = Sprite(random.choice(self.image_names), color, img_size, base_pos)
            right.rect.left = self.objects[self.rightid].rect.right
            right.update_pos()
            self.rightid = len(self.objects)
            self.objects.append(right)
        layers.insert(0, self)

    def update_bound(self):
        min_i, max_i = 0, 0
        min_v, max_v = float("inf"), float("-inf")
        for i, obj in enumerate(self.objects):
            v = obj.rect.centerx
            if v < min_v:
                min_v = v
                min_i = i

            if v > max_v:
                max_v = v
                max_i = i
        
        self.leftid = min_i
        self.rightid = max_i

    def move_layer(self, offset):
        for obj in self.objects:
            obj.rect.centerx += offset

        if self.objects[self.leftid].rect.left > -10:
            base_pos = self.objects[self.leftid].rect.midbottom
            left = Sprite(random.choice(self.image_names), self.color, self.img_size, base_pos)
            left.rect.right = self.objects[self.leftid].rect.left
            left.update_pos() 
            self.leftid = len(self.objects)
            self.objects.append(left)

        if self.objects[self.rightid].rect.right < size[0] + 10:
            base_pos = self.objects[self.rightid].rect.midbottom
            right = Sprite(random.choice(self.image_names), self.color, self.img_size, base_pos)
            right.rect.left = self.objects[self.rightid].rect.right
            right.update_pos() 
            self.rightid = len(self.objects)
            self.objects.append(right) 
        
        if self.objects[self.leftid].rect.right < -10:
            self.objects.pop(self.leftid)
            self.update_bound()

        if self.objects[self.rightid].rect.left > size[0] + 10:
            self.objects.pop(self.rightid)
            self.update_bound()

    def update(self, window):
        for obj in self.objects:
            window.blit(obj.image, obj.rect)

class Sprite(pg.sprite.Sprite):
    def __init__(self, image_name, color, img_size, position = ( 0, 0 )):
        super().__init__()
        self.image = pg.image.load(image_name)
        self.image = pg.transform.scale(self.image, img_size)
        self._image = self.image.copy()
        self.rect = self.image.get_rect()
        self.change_color(color)
        self.rect.centerx, self.rect.bottom = position
        self.update_pos()
        global count__
        count__ += 1

    def change_color(self, color):
        temp_image = pg.Surface(self.image.get_size()).convert_alpha()
        temp_image.fill(color)
        self.image = self._image.copy()
        self.image.blit(temp_image, (0, 0), special_flags = pg.BLEND_RGBA_MULT)

    def update_pos(self):
        self.image.blit(self.image, self.rect)

pg.init()

clock = pg.time.Clock()
window = pg.display.set_mode(size)

for i in range(count_layers):
    ground_layers.append(Layer([ 'source/fg/grass.png' ], 
        pg.Color(*ground_color),
        ground_size, 
        layer_offset * i))
    
    for j, c in enumerate(ground_color):
        value = c - color_offset
        if value < 0: 
            value = 0
        ground_color[j] = value


clouds = [ 'source/clouds/' + i for i in cloud_filenames ]
for i in range(count_layers):
    cloud_layers.append(Layer(clouds, 
        pg.Color(*cloud_color),
        cloud_size, 
        size[1] - cloud_offset - layer_offset * i))
    
    for j, c in enumerate(cloud_color):
        value = c - color_offset
        if value < 0: 
            value = 0
        cloud_color[j] = value


hero_color = tuple(random.randint(0, 255) for _ in range(3))
hero = Sprite('source/slime/base.png', 
        pg.Color(*hero_color),
        (400, 200),
        (size[0] // 2, size[1] - 50))

print(count__)
while running:
    clock.tick(FPS)
    window.fill(pg.Color(228, 239, 231))

    cs = cloud_speed
    pk = pg.key.get_pressed()
    if pk[K_d]:
        ms = move_speed
        cs += ms
        for i in ground_layers:
            i.move_layer(ms)
            ms *= paralax_scale
    if pk[K_a]:
        ms = -move_speed
        cs += ms
        for i in ground_layers:
            i.move_layer(ms)
            ms *= paralax_scale
    if pk[K_g]:
        rainbow_color = True
        hue = 0
    
    for i in cloud_layers:
        i.move_layer(cs)
        cs *= paralax_scale

    if rainbow_color:
        hero_color.hsla = (hue, 100, 50, 100)
        hue = (hue + 1) if hue < 360 else 0
        hero.change_color(hero_color)

    for e in pg.event.get():
        if e.type == pg.QUIT:
            running = False

    for i, l in enumerate(layers):
        if i == hero_layer:
            window.blit(hero.image, hero.rect)
        l.update(window)

    pg.display.update()
pg.quit()
