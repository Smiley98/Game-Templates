import sys, pygame as pg
from enum import Enum

def drawText(text, x, y, colour, font, surface):
    textRender = font.render(text, True, colour)
    textRect = textRender.get_rect()
    textRect.center = (x, y)
    surface.blit(textRender, textRect)

class Button(pg.Rect):
    def __init__(self, x, y, w, h, button_colour, onClickHandler):
        super().__init__(x, y, w, h)
        self.button_colour = button_colour
        self.onClickHandler = onClickHandler

    def draw(self, surface):
        pg.draw.rect(surface, self.button_colour, pg.Rect(self.x, self.y, self.w, self.h))

    def onClick(self, x, y):
        if (super().collidepoint(x, y)):
            self.onClickHandler()

class TextButton(Button):
    def __init__(self, x, y, w, h,  button_colour, text_colour, font, onClickHandler):
        super().__init__(x, y, w, h, button_colour, onClickHandler)
        self.text_colour = text_colour
        self.font = font

    def draw(self, text, surface):
        super().draw(surface)
        drawText(text, self.x + self.w / 2, self.y + self.h / 2, self.text_colour, self.font, surface)

#Creating globals here because the scene classes need them.
black = pg.Color(0, 0, 0)
red = pg.Color(255, 0, 0)
green = pg.Color(0, 255, 0)
blue = pg.Color(0, 0, 255)
white = pg.Color(255, 255, 255)

pg.init()
font10 = pg.font.Font('freesansbold.ttf', 10)
font20 = pg.font.Font('freesansbold.ttf', 20)
font30 = pg.font.Font('freesansbold.ttf', 30)

class SceneType(Enum):
    BEGIN = 0
    MIDDLE = 1
    END = 2

class Scene:
    def __init__(self, bounds):
        self.bounds = bounds

    def onStart(self):
        print("Default start")
    
    def onFinish(self):
        print("Default finish")

    def onUpdate(self, surface):
        print("Default update")

    def onClick(self, x, y):
        print("Default click")

    scene = None

    @classmethod
    def change(clazz, sceneType, bounds):
        if not clazz.scene == None:
            clazz.scene.onFinish()

        if sceneType == SceneType.BEGIN:
            clazz.scene = BeginScene(bounds)
        elif sceneType == SceneType.MIDDLE:
            clazz.scene = MiddleScene(bounds)
        elif sceneType == SceneType.END:
            clazz.scene = EndScene(bounds)

        clazz.scene.onStart()

class BeginScene(Scene):
    def __init__(self, bounds):
        super().__init__(bounds)
        self.button = TextButton(bounds.centerx - 30, bounds.centery - 20, 60, 40, red, white, font10, lambda: (
            Scene.change(SceneType.MIDDLE, bounds)
        ))
    
    def onStart(self):
        print("Begin start")
    
    def onFinish(self):
        print("Begin finish")

    def onUpdate(self, surface):
        self.button.draw("Begin", surface)

    def onClick(self, x, y):
        self.button.onClick(x, y)

class MiddleScene(Scene):
    def __init__(self, bounds):
        super().__init__(bounds)
        self.button = TextButton(bounds.centerx - 30, bounds.centery - 20, 60, 40, green, white, font10, lambda: (
            Scene.change(SceneType.END, bounds)
        ))

    def onStart(self):
        print("Middle start")
    
    def onFinish(self):
        print("Middle finish")

    def onUpdate(self, surface):
        self.button.draw("End", surface)

    def onClick(self, x, y):
        self.button.onClick(x, y)

class EndScene(Scene):
    def __init__(self, bounds):
        super().__init__(bounds)
        self.button = TextButton(bounds.centerx - 30, bounds.centery - 20, 60, 40, blue, white, font10, lambda: (
            Scene.change(SceneType.BEGIN, bounds)
        ))

    def onStart(self):
        print("End start")
    
    def onFinish(self):
        print("End finish")

    def onUpdate(self, surface):
        self.button.draw("Restart", surface)

    def onClick(self, x, y):
        self.button.onClick(x, y)

screen = pg.display.set_mode([640, 480])
surface = pg.display.get_surface()
mouse = (0, 0)
mouseDown = False
lit = surface.get_rect()

Scene.change(SceneType.BEGIN, screen.get_rect())

while 1:
    mouse = pg.mouse.get_pos()
    for event in pg.event.get():
        if event.type == pg.QUIT:
            sys.exit()

        elif event.type == pg.MOUSEBUTTONUP:
            Scene.scene.onClick(mouse[0], mouse[1])

    #Do not put any rendering code above this!
    screen.fill(pg.Color(0, 0, 0))
    Scene.scene.onUpdate(surface)

    #pg.draw.rect(surface, red, pg.Rect(320, 240, 60, 40))
    #drawText("Memes", 350, 260, white, font10, surface)
    
    pg.display.flip()