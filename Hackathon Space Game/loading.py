import time
import curses
import random

# percentage and update_progress from stackoverflow
def percentage(win):
    loading = 0
    while loading < 100:
        loading += 1
        time.sleep(0.1)
        update_progress(win, loading)

def update_progress(win, progress):
    rangex = (60 / float(100)) * progress
    pos = int(rangex)
    display = '#'
    if pos != 0:
        win.addstr(19, pos+8, "{}".format(display))
        win.addstr(18, 41, str(progress) + "%")
        win.refresh()

def doLoading(window):
    window.clear()
    window.box()
    for i in range(10):
        color = 6
        if random.random() < 0.2: color = 7
        window.addstr(random.randrange(22)+1, random.randrange(78)+1, '*', curses.color_pair(color))
    for i in range(15):
        color = 6
        if random.random() < 0.2: color = 7
        window.addstr(random.randrange(22)+1, random.randrange(78)+1, '.', curses.color_pair(color))
    for i in range(10):
        color = 6
        if random.random() < 0.2: color = 7
        window.addstr(random.randrange(22)+1, random.randrange(78)+1, '\u2727', curses.color_pair(color))
    window.addstr(8, 5, "Aliens are attacking! Destroy them before they get you! (⋋_⋌)")
    window.addstr(10, 33, '[ Controls ] ')
    window.addstr(11, 22, 'w: move up')
    window.addstr(12, 22, 's: move down')
    window.addstr(13, 22, 'SPACE: shoot cannon')
    # window.addstr(14, 22, 'b: raise shield')
    window.addstr(18, 33, 'Loading ')
    percentage(window)