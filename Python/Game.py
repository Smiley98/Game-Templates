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

def drawText(text, x, y, colour, font, surface):
    textRender = font.render(text, True, colour)
    textRect = textRender.get_rect()
    textRect.center = (x, y)
    surface.blit(textRender, textRect)

#pygame has a Rect class that uses way too much memory, but it handles collisions for me.
#Writing this is already painful enough so I've decided to use its silly Rect class...
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

pg.init()

screen = pg.display.set_mode([640, 480])
surface = pg.display.get_surface()
mouse = (0, 0)
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

font10 = pg.font.Font('freesansbold.ttf', 10)
font20 = pg.font.Font('freesansbold.ttf', 20)
font30 = pg.font.Font('freesansbold.ttf', 30)

button = Button(0, 0, 60, 40, red, lambda : print("Button!"))
textButton = TextButton(0, 0, 60, 40, red, white, font10, lambda : print("Text button!"))

while 1:
    for event in pg.event.get():
        if event.type == pg.QUIT: sys.exit()
    
    #I swear there's a way to convert from tuple to Point in one line but I'm not good enough at Python to know how.
    mouse = pg.mouse.get_pos()

    screen.fill(pg.Color(0, 0, 0))

    textButton.draw("Memes", surface)

    pg.draw.rect(surface, red, pg.Rect(320, 240, 60, 40))
    drawText("Memes", 350, 260, white, font10, surface)
    
    pg.display.flip()