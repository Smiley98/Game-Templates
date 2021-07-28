import sys, pygame as pg
pg.init()

canvas = pg.display.set_mode([640, 480])
ctx = pg.display.get_surface()

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

#Runtime testing to make sure there's no instantiation errors.
a = BeginScene()
b = MiddleScene()
c = EndScene()

a.onStart()
b.onStart()
c.onStart()

while 1:
    for event in pg.event.get():
        if event.type == pg.QUIT: sys.exit()

    canvas.fill(pg.Color(0, 0, 0))
    pg.draw.rect(ctx, pg.Color(255, 0, 0), pg.Rect(0, 0, 60, 40))
    pg.display.flip()