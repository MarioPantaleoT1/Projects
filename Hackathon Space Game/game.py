import curses
from ship import Ship
from attack import Attack
from startup import startup
from rounds import Round
from match import Match
from loading import doLoading
# Bugs found: need to make money reset after game, make box appear after lose game and restart

def parsescore(f: list):
    ret: str
    name:str = list[0]
    score:str = list[1]
    ret = '' + score + ' -- ' + name
    return ret

def main():
    
    
    curses.initscr()
    stdscr = curses.newwin(24, 80)
    curses.noecho()
    curses.cbreak()
    curses.curs_set(0)
    curses.start_color()
    curses.init_pair(1, curses.COLOR_MAGENTA, curses.COLOR_BLACK)    
    curses.init_pair(2, curses.COLOR_RED, curses.COLOR_BLACK)
    curses.init_pair(3, curses.COLOR_BLUE, curses.COLOR_BLACK)
    curses.init_pair(4, curses.COLOR_GREEN, curses.COLOR_BLACK)
    curses.init_pair(5, curses.COLOR_WHITE, curses.COLOR_BLACK)
    curses.init_pair(6, curses.COLOR_YELLOW, curses.COLOR_BLACK)
    curses.init_pair(7, curses.COLOR_CYAN, curses.COLOR_BLACK)
    stdscr.keypad(True)
    stdscr.box()

    while(True):
        choice = startup(stdscr)
        playerShip = Ship(11, 2, True)
        
        match choice:
            case 'g':
                doLoading(stdscr)
                m = Match(stdscr, playerShip)
                m.run()
            case 'q':
                break

    stdscr.refresh()
    curses.endwin()




if __name__ == '__main__':
    main()