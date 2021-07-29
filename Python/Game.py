import sys, pygame as pg

class Scene:
    def __init__(self):
        pass

    def onStart(self):
        print("Default start")
    
    def onFinish(self):
        print("Default finish")

class BeginScene(Scene):
    def __init__(self):
        super().__init__()
    
    def onStart(self):
        print("Begin start")
    
    def onFinish(self):
        print("Begin finish")

class MiddleScene(Scene):
    def __init__(self):
        super().__init__()
    
    def onStart(self):
        print("Middle start")
    
    def onFinish(self):
        print("Middle finish")

class EndScene(Scene):
    def __init__(self):
        super().__init__()

    def onStart(self):
        print("End start")
    
    def onFinish(self):
        print("End finish")

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

#The pygame.Rect class is aids. It uses like 10x more memory than it needs to hence the creation of this Box class ;)
class Box:
    def __init__(self, x, y, w, h):
        self.x = x
        self.y = y
        self.w = w
        self.h = h
    
    def rect() -> pg.Rect:
        return pg.Rect(x, y, w, h)


#class Button:
#    def __init__(self, x, y, w, h, onClickHandler):

pg.init()

canvas = pg.display.set_mode([640, 480])
ctx = pg.display.get_surface()
font = pg.font.Font('freesansbold.ttf', 32)
mouse = Point(0, 0)
mouseDown = False

black = pg.Color(0, 0, 0)
red = pg.Color(255, 0, 0)
green = pg.Color(0, 255, 0)
blue = pg.Color(0, 0, 255)
white = pg.Color(255, 255, 255)

#Runtime testing to make sure there's no instantiation errors.
a = BeginScene()
b = MiddleScene()
c = EndScene()

a.onStart()
b.onStart()
c.onStart()

def text(text, x, y, fg_colour, bg_colour):
    textRender = font.render(text, True, fg_colour, bg_colour)
    textRect = textRender.get_rect()
    textRect.center = (x, y)
    ctx.blit(textRender, textRect)

while 1:
    for event in pg.event.get():
        if event.type == pg.QUIT: sys.exit()
    
    #I swear there's a way to convert from tuple to Point in one line but I'm not good enough at Python to know how.
    mouse = Point(pg.mouse.get_pos()[0], pg.mouse.get_pos()[1])

    canvas.fill(pg.Color(0, 0, 0))
    text("Click to begin", 320, 240, white, black)
    pg.draw.rect(ctx, pg.Color(255, 0, 0), pg.Rect(320, 240, 60, 40))
    pg.display.flip()