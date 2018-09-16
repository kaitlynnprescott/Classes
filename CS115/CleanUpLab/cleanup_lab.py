'''
Created on Dec 3, 2014
@author: Brian Borowski
@version: 2.0 alpha
Course: CS 115 - Intro to CS
Simple pygame to illustrate inheritance and responding to collisions.

Names:
Pledge:
'''
import pygame
import random
import sys
import os

SCREEN_WIDTH = 640
SCREEN_HEIGHT = 480
BROWN = (80, 53, 25)
YELLOW = (255, 255, 0)

class Actor(pygame.sprite.Sprite):
    '''An Actor is an object that moves across the screen.'''
    PAUSED = 0
    MOVING = 1
    HIT_TOP = 2
    HIT_RIGHT = 3
    HIT_BOTTOM = 4
    HIT_LEFT = 5

    def __init__(self, filename, center=False, speed=100):
        '''Constructor for Actor.

        Args:
            image_file: The path to the image file for the Actor.
            center: Whether or not to start the Actor in the center of the
                screen.
            speed: The number of pixels the Actor should move in a second.
        '''
        pygame.sprite.Sprite.__init__(self)
        self.image = pygame.image.load(filename).convert_alpha()
        self.rect = self.image.get_rect()
        if center:
            self.rect.left = self.x = (SCREEN_WIDTH - self.rect.width) // 2
            self.rect.top = self.y = (SCREEN_HEIGHT - self.rect.height) // 2
        else:
            self.rect.left = self.x = 0
            self.rect.top = self.y = 0
        self.delta_x = self.delta_y = 0
        self.speed = speed
        self.status = Actor.PAUSED

    def move_left(self, seconds):
        '''Moves the Actor left by the amount of pixels that correspond to the
        amount of seconds that have elapsed.

        Args:
            seconds: The amount of seconds that have elapsed since the last
                update. Most likely will be a small float.
        '''
        distance = self.speed * seconds
        if self.x >= distance:
            self.x -= distance
        else:
            self.x = 0
            self.status = Actor.HIT_LEFT
        if self.rect.left > self.x:
            self.rect.left = self.x

    def move_right(self, seconds):
        '''Moves the Actor right by the amount of pixels that correspond to the
        amount of seconds that have elapsed.

        Args:
            seconds: The amount of seconds that have elapsed since the last
                update. Most likely will be a small float.
        '''
        distance = self.speed * seconds
        rightmost = SCREEN_WIDTH - self.rect.width
        if self.x < rightmost - distance:
            self.x += distance
        else:
            self.x = rightmost
            self.status = Actor.HIT_RIGHT
        if self.rect.left < self.x:
            self.rect.left = self.x

    def move_up(self, seconds):
        '''Moves the Actor up by the amount of pixels that correspond to the
        amount of seconds that have elapsed.

        Args:
            seconds: The amount of seconds that have elapsed since the last
                update. Most likely will be a small float.
        '''
        distance = self.speed * seconds
        if self.y >= distance:
            self.y -= distance
        else:
            self.y = 0
            self.status = Actor.HIT_TOP
        if self.rect.top > self.y:
            self.rect.top = self.y

    def move_down(self, seconds):
        '''Moves the Actor down by the amount of pixels that correspond to the
        amount of seconds that have elapsed.

        Args:
            seconds: The amount of seconds that have elapsed since the last
                update. Most likely will be a small float.
        '''
        distance = self.speed * seconds
        bottommost = SCREEN_HEIGHT - self.rect.height
        if self.y < bottommost - distance:
            self.y += distance
        else:
            self.y = bottommost
            self.status = Actor.HIT_BOTTOM
        if self.rect.top < self.y:
            self.rect.top = self.y

    def move_composite(self, seconds):
        '''Moves the Actor in a random direction by the amount of pixels that
        correspond to the amount of seconds that have elapsed. If the Actor
        collides with the boundary of the screen, the Actor is put on a new
        trajectory away from the collision.

        Args:
            seconds: The amount of seconds that have elapsed since the last
                update. Most likely will be a small float.
        '''
        if self.status == Actor.PAUSED:
            sign_x = random.randrange(-1, 2, 2)
            sign_y = random.randrange(-1, 2, 2)
        elif self.status == Actor.HIT_TOP:
            sign_x = random.randrange(-1, 2, 2)
            sign_y = 1
        elif self.status == Actor.HIT_RIGHT:
            sign_x = -1
            sign_y = random.randrange(-1, 2, 2)
        elif self.status == Actor.HIT_BOTTOM:
            sign_x = random.randrange(-1, 2, 2)
            sign_y = -1
        elif self.status == Actor.HIT_LEFT:
            sign_x = 1
            sign_y = random.randrange(-1, 2, 2)

        if self.status == Actor.PAUSED or self.status >= Actor.HIT_TOP:
            self.delta_x = random.randint(1, 3) * sign_x
            self.delta_y = random.randint(1, 3) * sign_y
            self.set_moving()

        if self.delta_x >= 1:
            self.move_right(seconds * self.delta_x)
        else:
            self.move_left(seconds * -self.delta_x)
        if self.delta_y >= 1:
            self.move_down(seconds * self.delta_y)
        else:
            self.move_up(seconds * -self.delta_y)

    def set_moving(self):
        '''Sets the status of the Actor to MOVING.'''
        self.status = Actor.MOVING

    def set_paused(self):
        '''Sets the status of the Actor to PAUSED.'''
        self.status = Actor.PAUSED

    def paint(self, screen):
        '''Blits the Actor's image to the screen.'''
        screen.blit(self.image, self.rect)

class Hero(Actor):
    '''Hero is the main Actor which the user controls. If it collides with
    another Actor, it bursts into flames and cannot move for two seconds.'''
    ON_FIRE = 6

    def __init__(self, image_file, fire_image_file, center=False, speed=200):
        '''Constructor for Hero.

        Args:
            image_file: The path to the image file for the Actor.
            fire_image_file: The path to the image file for the Actor when it
                is on fire.
            speed: The number of pixels the Actor should move in a second.
        '''
        pass
        # TODO
        # Call the super class constructor

        # Create a member variable called fire_image the loads the image from
        # disk where the Hero is on fire.

        # Create a member variable called normal_image that saves a reference
        # to the image member variable from the superclass.

        # Create a member variable called timer that is initialized to 0.

    def check_collide(self, actor):
        '''Checks if this Hero collides with another Actor. If so, the Hero
        is set on fire and cannot move.

        Args:
            actor: Another Actor.
        '''
        if pygame.sprite.collide_mask(self, actor):
            pass
            # Set the image to the fire_image, set the status to ON_FIRE, and
            # reset the timer to 0.
            # TODO

    def update_timer(self, seconds):
        '''Updates the timer if the Hero is on fire. If, after updating, the
        timer contains at least 2 seconds, the image goes back to the normal
        image and the Hero is allowed to move again.

        Args:
            seconds: The amount of time that has elapsed since the last update.
        '''
        pass
        # TODO

    def move_left(self, seconds):
        '''Moves the Actor left by the amount of pixels that correspond to the
        amount of seconds that have elapsed ONLY IF the Actor is not on fire.

        Args:
            seconds: The amount of seconds that have elapsed since the last
                update. Most likely will be a small float.
        '''
        pass
        # TODO

    def move_right(self, seconds):
        '''Moves the Actor right by the amount of pixels that correspond to the
        amount of seconds that have elapsed ONLY IF the Actor is not on fire.

        Args:
            seconds: The amount of seconds that have elapsed since the last
                update. Most likely will be a small float.
        '''
        pass
        # TODO

    def move_up(self, seconds):
        '''Moves the Actor up by the amount of pixels that correspond to the
        amount of seconds that have elapsed ONLY IF the Actor is not on fire.

        Args:
            seconds: The amount of seconds that have elapsed since the last
                update. Most likely will be a small float.
        '''
        pass
        # TODO

    def move_down(self, seconds):
        '''Moves the Actor down by the amount of pixels that correspond to the
        amount of seconds that have elapsed ONLY IF the Actor is not on fire.

        Args:
            seconds: The amount of seconds that have elapsed since the last
                update. Most likely will be a small float.
        '''
        if self.status != Hero.ON_FIRE:
            Actor.move_down(self, seconds)

class BoardObject(pygame.sprite.Sprite):
    '''A BoardObject is a little colored rectangle that appears on the floor
    in the game.'''
    def __init__(self, position, size, color):
        pygame.sprite.Sprite.__init__(self)
        self.rect = pygame.Rect(position, size)
        self.color = color

    def paint(self, screen):
        pygame.draw.rect(screen, self.color, self.rect)

class Game(object):
    PAUSED = 0
    RUNNING = 1
    OVER = 2
    GAME_OVER_MESSAGE = "GAME OVER"
    GAME_OVER_DIRECTIONS = "Press S to start a new game."

    def __init__(self):
        os.environ['SDL_VIDEO_CENTERED'] = '1'
        pygame.init()
        self.screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
        pygame.display.set_caption("Clean Up!")
        self.background = pygame.image.load("images/floor.jpg")
        self.clock = pygame.time.Clock()
        self.fade_rect = pygame.Surface((SCREEN_WIDTH, SCREEN_HEIGHT))
        self.fade_rect.set_alpha(96)
        self.fade_rect.fill((0, 0, 0))
        self.large_font = pygame.font.Font(None, 64)
        self.medium_font = pygame.font.Font(None, 28)
        self.small_font = pygame.font.Font(None, 20)
        self.game_over_msg_image = self.large_font.render(Game.GAME_OVER_MESSAGE, True, YELLOW).convert_alpha()
        self.game_over_dir_image = self.medium_font.render(Game.GAME_OVER_DIRECTIONS, True, BROWN).convert_alpha()
        self.reset()

    def reset(self):
        self.hero = Hero("images/roomba.png", "images/fireroomba.png")
        self.enemy = Actor("images/angrybird.png", center=True)
        self.items = pygame.sprite.Group()
        for _ in range(100):
            random_color = (random.randint(0, 255), \
                            random.randint(0, 255), \
                            random.randint(0, 255))
            random_size = (random.randint(10, 25), \
                           random.randint(10, 25))
            random_pos = (random.randint(0, SCREEN_WIDTH - 1 - random_size[0]), \
                          random.randint(0, SCREEN_HEIGHT - 1 - random_size[1]))
            self.items.add(BoardObject(random_pos, random_size, random_color))
        self.status = Game.RUNNING
        self.elapsed_time = 0
        self.fps = 0
        self.last_fps_update = 0
        items_text = "Items remaining: {:0d}".format(len(self.items.sprites()))
        self.items_image = self.small_font.render(items_text, True, BROWN).convert_alpha()
        time_text = "Elapsed time (s): {0:0.3f}".format(0)
        self.time_image = self.small_font.render(time_text, True, BROWN).convert_alpha()

    def update(self, seconds):
        pressed = pygame.key.get_pressed()
        if self.status == Game.OVER:
            if pressed[pygame.K_s]:
                self.reset()
            return

        # Check if game should be paused first.
        if pressed[pygame.K_p]:
            self.status = Game.PAUSED
        elif pressed[pygame.K_r]:
            self.status = Game.RUNNING
        if self.status == Game.PAUSED:
            return

        # Our roomba hero cannot move diagonally!
        if pressed[pygame.K_LEFT]:
            self.hero.move_left(seconds)
        elif pressed[pygame.K_RIGHT]:
            self.hero.move_right(seconds)
        elif pressed[pygame.K_UP]:
            self.hero.move_up(seconds)
        elif pressed[pygame.K_DOWN]:
            self.hero.move_down(seconds)
        # But our angry bird enemy can!
        self.enemy.move_composite(seconds)

        self.hero.check_collide(self.enemy)
        self.hero.update_timer(seconds)

        self.elapsed_time += seconds
        time_text = "Elapsed time (s): {0:0.3f}".format(self.elapsed_time)
        self.time_image = self.small_font.render(time_text, True, BROWN).convert_alpha()

        self.last_fps_update += seconds
        if self.last_fps_update >= 1 or self.fps == 0:
            self.fps = self.clock.get_fps()
            fps_text = "FPS: {0:0.1f}".format(self.fps)
            self.fps_image = self.small_font.render(fps_text, True, BROWN).convert_alpha()
            self.last_fps_update = 0

        collisions = pygame.sprite.spritecollide(self.hero, self.items, dokill=True)
        if len(collisions) > 0:
            num_remaining = len(self.items.sprites())
            items_text = "Items remaining: {0:0d}".format(num_remaining)
            self.items_image = self.small_font.render(items_text, True, BROWN).convert_alpha()
            if num_remaining == 0:
                self.status = Game.OVER
        # Optional TODO - add a scoring mechanism

    def render(self):
        self.screen.blit(self.background, (0, 0))
        for item in self.items:
            item.paint(self.screen)
        self.hero.paint(self.screen)
        self.enemy.paint(self.screen)
        self.screen.blit(self.fps_image, (10, SCREEN_HEIGHT - 20))
        self.screen.blit(self.items_image, (SCREEN_WIDTH - 145, SCREEN_HEIGHT - 20))
        self.screen.blit(self.time_image, (SCREEN_WIDTH - 170, 10))
        # Optional TODO - display the score
        if self.status == Game.OVER:
            self.screen.blit(self.fade_rect, (0, 0))
            (text_width, text_height) = self.large_font.size(Game.GAME_OVER_MESSAGE)
            x = (SCREEN_WIDTH - text_width) // 2
            y = (SCREEN_HEIGHT - text_height) // 2
            self.screen.blit(self.game_over_msg_image, (x, y - 20))
            (text_width, text_height) = self.medium_font.size(Game.GAME_OVER_DIRECTIONS)
            x = (SCREEN_WIDTH - text_width) // 2
            self.screen.blit(self.game_over_dir_image, (x, y + 30))
        pygame.display.update()

    def run(self):
        while True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    sys.exit(0)
            time_ms = self.clock.tick()
            if time_ms < 100:
                self.update(time_ms / 1000.0)
                self.render()

if __name__ == '__main__':
    game = Game()
    game.run()
