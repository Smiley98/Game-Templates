import sys, pygame
pygame.init()

canvas = pygame.display.set_mode([640, 480])
ctx = pygame.display.get_surface()

while 1:
    for event in pygame.event.get():
        if event.type == pygame.QUIT: sys.exit()

    canvas.fill(pygame.Color(0, 0, 0))
    pygame.display.flip()