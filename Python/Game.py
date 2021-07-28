import sys, pygame as pg
pg.init()

canvas = pg.display.set_mode([640, 480])
ctx = pg.display.get_surface()

while 1:
    for event in pg.event.get():
        if event.type == pg.QUIT: sys.exit()

    canvas.fill(pg.Color(0, 0, 0))
    pg.draw.rect(ctx, pg.Color(255, 0, 0), pg.Rect(0, 0, 60, 40))
    pg.display.flip()