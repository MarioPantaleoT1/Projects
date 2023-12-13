from rounds import Round
from ship import Ship
from inbetween import Frame
import curses
import time
import random



class Match():

    lost = False
    f: Frame
    player: Ship
    window = 0
    stars = []
    

    def __init__(self, window, player):
        
        self.f = Frame(window)
        self.window = window
        self.player = player


    def run(self):
        self.window.clear()
        roundnumber = 1
        while not self.lost:
            r = Round(roundnumber, self.player)
            r.generateRound()
            result = r.start(self.window)
            if result == -1:
                self.lost = True
                break
            
            self.player.money += (roundnumber + random.randrange(roundnumber) + 1)
            if roundnumber == 6: break

            # in between screen
            roundnumber += 1
            output = '0'
            while output == '0':
                self.f.printScreen(self.player)
                output = self.f.makeSelection(self.player)

        
        self.gameOverScreen(self.lost)
        


    def gameOverScreen(self, lost):
        self.window.nodelay(False)
        self.window.clear()
        self.window.box()
        f = open('highscore.txt', 'r')
        highscore= f.readlines()
        if lost:
            self.window.addstr(1,1, "Game Over - you lost :(")
        else:
            self.window.addstr(1,1, "Game Over - you won!!")
        self.window.addstr(3,1, "HIGH SCORE: " + highscore[1] + " [" + highscore[0].strip() + "]")
        self.window.addstr(4,1, "YOUR SCORE: " + str(self.player.score))
        if int(highscore[1]) < self.player.score:
            self.window.addstr(6,1, "New high score, please enter your name: ")
            self.window.move(6, 42)
            inkey = ''
            newName = ''
            inc = 0
            while(inc < 5):
                inkey = self.window.getch()
                newName += str(chr(inkey))
                self.window.addstr(6,42, newName)
                inc += 1
            
            f.close()
            f = open("highscore.txt", 'w')
            f.write(newName.strip() + '\n')
            f.write(str(self.player.score))
        self.window.refresh()
        self.window.getch()
        self.window.clear()

