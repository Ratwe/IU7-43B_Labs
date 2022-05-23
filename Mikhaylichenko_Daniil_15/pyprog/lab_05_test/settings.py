import math

# game settings
WIDTH = 1000
HEIGHT = 600
HALF_WIDTH = WIDTH // 2
HALF_HEIGHT = HEIGHT // 2
FPS = 60
TILE = 50

# ray casting settings
FOV = math.pi / 3
HALF_FOV = FOV / 2
MAX_DEPTH = 800

# player settings
player_pos = (HALF_WIDTH, HALF_HEIGHT)
player_angle = 270 * math.pi / 180
player_speed = 2

# colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (220, 0, 0)
GREEN = (0, 80, 0)
BLUE = (0, 0, 220)
LIGHTBLUE = (0, 191, 255)
SKYBLUE = (90, 186, 255)
DARKGRAY = (60, 60, 60)
PURPLE = (120, 0, 120)
BEIGE = (245, 245, 220)
YELLOW = (220, 220, 0)
SANDY = (244, 164, 96)