import pygame
import math
BLACK = (  0,   0,   0)
BLUE =  (  0,   0, 255)
GREEN = (  0, 255,   0)
RED =   (255,   0,   0)
GREY =  (100, 100, 100)
size = [600, 600]
lmfao = 1
def main():
    pygame.init()
    screen = pygame.display.set_mode(size)
    pygame.display.set_caption("Bresenham Algorithm Line Demo")
    done = False
    clock = pygame.time.Clock()
    pixel = 50
    pixel_size = [size[0] / pixel, size[1] / pixel]
    fist_pixel = None
    second_pixel = None
    while not done:
        clock.tick(10)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                done = True
            if event.type == pygame.MOUSEBUTTONDOWN:
                x, y = event.pos
                if fist_pixel == None:
                    fist_pixel = [x / pixel_size[0] * pixel_size[0], y / pixel_size[1] * pixel_size[1]]
                else:
                    if second_pixel == None:
                        second_pixel = [x / pixel_size[0] * pixel_size[0], y / pixel_size[1] * pixel_size[1]]
                    else:
                        fist_pixel = [x / pixel_size[0] * pixel_size[0], y / pixel_size[1] * pixel_size[1]]
                        second_pixel = None
        screen.fill(GREY)
        for i in range(0, pixel):
            pygame.draw.line(screen, RED, [pixel_size[0] * i, 0], [pixel_size[0] * i, size[1]], 1)
            pygame.draw.line(screen, RED, [0, pixel_size[1] * i], [size[0], pixel_size[1] * i], 1)
        if (fist_pixel != None):
            pygame.draw.rect(screen, BLUE, (fist_pixel[0], fist_pixel[1], pixel_size[0], pixel_size[1]), 0)
            if (lmfao == 1):
                if (second_pixel != None):
                    for v in bresenham([fist_pixel[0] / pixel_size[0], fist_pixel[1] / pixel_size[1]], [second_pixel[0] / pixel_size[0], second_pixel[1] / pixel_size[1]]):
                        pygame.draw.rect(screen, BLUE, (v[0] * pixel_size[0], v[1] * pixel_size[1], pixel_size[0], pixel_size[1]), 0)
                    pygame.draw.line(screen, GREEN, [fist_pixel[0] + pixel_size[0] / 2, fist_pixel[1] + pixel_size[1] / 2],  [second_pixel[0] + pixel_size[0] / 2, second_pixel[1] + pixel_size[1] / 2], 1)
                else:
                    print "HAHHA"
        pygame.display.flip()
    pygame.quit()
def bresenham(a, b):
    lst = []
    x0 = a[0]
    y0 = a[1]
    x1 = b[0]
    y1 = b[1]
    steep = (abs(y1 - y0) > abs(x1 - x0))
    if steep:
        temp = y0
        y0 = x0
        x0 = temp
        temp = y1
        y1 = x1
        x1 = temp	
    deltax = abs(x1-x0)
    if deltax <= 1:
        if steep:
            lst.append([a[1], a[0]])
            lst.append([b[1], b[0]])
        else:
            lst.append(a)
            lst.append(b)
        return lst
    currentx = x0
    currenty = y0
    if x0 < x1:
        xinc = 1
    else:
        xinc = -1
    error = 0
    yinc = (y1 - y0) / (deltax)
    while currentx != x1:
        if steep:
            lst.append([currenty, currentx])
        else:
            lst.append([currentx, currenty])
        currentx += xinc
        error += yinc
        if error > 0.5:
            currenty += 1
            error -= 1
        elif error < -0.5:
            currenty -= 1
            error += 1
    if steep:
        lst.append([y1, x1])
    else:
        lst.append([x1, y1])
    return lst;

def abs(v):
    return (math.fabs(v));

if __name__ == "__main__":
    main()