import pygame, sys, heapq
from collections import deque

# Initialize pygame
pygame.init()

# Screen settings
WIDTH, HEIGHT = 800, 800
ROWS, COLS = 40, 40
CELL_SIZE = WIDTH // COLS
SCREEN = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Maze Pathfinding Visualizer - BFS / Dijkstra / A*")

# Colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GREEN = (0, 255, 0)
RED = (255, 0, 0)
BLUE = (0, 0, 255)
YELLOW = (255, 255, 0)
GREY = (200, 200, 200)

# Grid setup
grid = [[0]*COLS for _ in range(ROWS)]
start, end = None, None

# Utility functions
def draw_grid():
    for i in range(ROWS):
        for j in range(COLS):
            color = WHITE
            if grid[i][j] == 1:
                color = BLACK
            elif (i, j) == start:
                color = GREEN
            elif (i, j) == end:
                color = RED
            pygame.draw.rect(SCREEN, color, (j*CELL_SIZE, i*CELL_SIZE, CELL_SIZE-1, CELL_SIZE-1))

def get_clicked_pos(pos):
    y, x = pos
    return y // CELL_SIZE, x // CELL_SIZE

# BFS Algorithm
def bfs():
    q = deque([start])
    visited = {start: None}
    dirs = [(1,0),(-1,0),(0,1),(0,-1)]
    while q:
        pygame.time.delay(10)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit(); sys.exit()
        current = q.popleft()
        if current == end:
            reconstruct_path(visited)
            return
        for dx, dy in dirs:
            nx, ny = current[0]+dx, current[1]+dy
            if 0 <= nx < ROWS and 0 <= ny < COLS and grid[nx][ny] != 1 and (nx, ny) not in visited:
                visited[(nx, ny)] = current
                q.append((nx, ny))
                pygame.draw.rect(SCREEN, YELLOW, (ny*CELL_SIZE, nx*CELL_SIZE, CELL_SIZE-1, CELL_SIZE-1))
        draw_grid(); pygame.display.update()

# Dijkstra's Algorithm
def dijkstra():
    pq = [(0, start)]
    dist = {start: 0}
    prev = {start: None}
    dirs = [(1,0),(-1,0),(0,1),(0,-1)]
    while pq:
        pygame.time.delay(10)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit(); sys.exit()
        d, node = heapq.heappop(pq)
        if node == end:
            reconstruct_path(prev)
            return
        for dx, dy in dirs:
            nx, ny = node[0]+dx, node[1]+dy
            if 0 <= nx < ROWS and 0 <= ny < COLS and grid[nx][ny] != 1:
                new_d = d + 1
                if (nx, ny) not in dist or new_d < dist[(nx, ny)]:
                    dist[(nx, ny)] = new_d
                    prev[(nx, ny)] = node
                    heapq.heappush(pq, (new_d, (nx, ny)))
                    pygame.draw.rect(SCREEN, YELLOW, (ny*CELL_SIZE, nx*CELL_SIZE, CELL_SIZE-1, CELL_SIZE-1))
        draw_grid(); pygame.display.update()

# A* Algorithm
def heuristic(a, b):
    return abs(a[0]-b[0]) + abs(a[1]-b[1])

def astar():
    pq = [(0, start)]
    g = {start: 0}
    f = {start: heuristic(start, end)}
    came_from = {}
    dirs = [(1,0),(-1,0),(0,1),(0,-1)]
    while pq:
        pygame.time.delay(10)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit(); sys.exit()
        _, current = heapq.heappop(pq)
        if current == end:
            reconstruct_path(came_from)
            return
        for dx, dy in dirs:
            nx, ny = current[0]+dx, current[1]+dy
            if 0 <= nx < ROWS and 0 <= ny < COLS and grid[nx][ny] != 1:
                tentative_g = g[current] + 1
                if (nx, ny) not in g or tentative_g < g[(nx, ny)]:
                    g[(nx, ny)] = tentative_g
                    f[(nx, ny)] = tentative_g + heuristic((nx, ny), end)
                    came_from[(nx, ny)] = current
                    heapq.heappush(pq, (f[(nx, ny)], (nx, ny)))
                    pygame.draw.rect(SCREEN, YELLOW, (ny*CELL_SIZE, nx*CELL_SIZE, CELL_SIZE-1, CELL_SIZE-1))
        draw_grid(); pygame.display.update()

def reconstruct_path(prev):
    node = end
    while node and node in prev:
        pygame.draw.rect(SCREEN, BLUE, (node[1]*CELL_SIZE, node[0]*CELL_SIZE, CELL_SIZE-1, CELL_SIZE-1))
        node = prev[node]
        pygame.display.update()
        pygame.time.delay(20)

# Main loop
algo = None
while True:
    SCREEN.fill(WHITE)
    draw_grid()
    pygame.display.update()

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit(); sys.exit()
        if pygame.mouse.get_pressed()[0]:
            pos = pygame.mouse.get_pos()
            r, c = get_clicked_pos(pos)
            if not start:
                start = (r, c)
            elif not end and (r, c) != start:
                end = (r, c)
            elif (r, c) != start and (r, c) != end:
                grid[r][c] = 1  # obstacle
        elif pygame.mouse.get_pressed()[2]:
            pos = pygame.mouse.get_pos()
            r, c = get_clicked_pos(pos)
            if (r, c) == start:
                start = None
            elif (r, c) == end:
                end = None
            else:
                grid[r][c] = 0

        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_b and start and end:
                bfs()
            elif event.key == pygame.K_d and start and end:
                dijkstra()
            elif event.key == pygame.K_a and start and end:
                astar()
            elif event.key == pygame.K_c:
                start, end = None, None
                grid = [[0]*COLS for _ in range(ROWS)]
