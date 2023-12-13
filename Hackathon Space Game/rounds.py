from ship import Ship
from shot import Shot
from trash import Trash
import curses
import time
import random

class Round:
    enemyShips = []
    player: Ship
    attacks = []
    player = 0
    lastTime = 0
    currentTime = 0
    stars = []
    global isBossLevel
    trash = []
    
    def __init__ (self,roundNumber,player):
        global isBossLevel
        self.roundNumber = roundNumber
        self.player = player
        self.lastTime = time.time()
        if roundNumber == 6:
            isBossLevel = True
        else:
            isBossLevel = False

        

    def generateEnemies(self):
        self.enemyShips.append(Ship(4,77, False))
        self.enemyShips.append(Ship(6,77, False))
        self.enemyShips.append(Ship(8,77, False))
        self.enemyShips.append(Ship(10,77, False))
        self.enemyShips.append(Ship(12,77, False))
        self.enemyShips.append(Ship(14,77, False))
        self.enemyShips.append(Ship(16,77, False))
        self.enemyShips.append(Ship(18,77, False))


    def generateRound(self):
        #self.generateEnemies()
        #self.generatePlayer()
        fname = './levels/level' + str(self.roundNumber) + '.txt'
        src = open(fname, 'r')
        tmp = src.readlines()
        enemies = []
        for e in tmp:
            enemies.append(e.split(' '))
            
        if isBossLevel: 
            self.enemyShips.append(Ship(int(enemies[1][1]), int(enemies[1][0]),
                                        False, int(enemies[1][3]), int(enemies[1][2]),
                                        enemies[1][5].strip(), int(enemies[1][4]))
                                    ) # y, x, player?, speed, health, icon, dmg
            
        else:
            for i in range(len(enemies)):
                # print(enemies[i])
                if i == 0: continue # first thing in enemies is dummy notation, ignore
                self.enemyShips.append(Ship(int(enemies[i][1]), int(enemies[i][0]),
                                            False, int(enemies[i][3]), int(enemies[i][2]),
                                            enemies[i][5].strip(), int(enemies[i][4]))
                                        ) # y, x, player?, speed, health, icon, dmg
            
    bossMoveCounter = 0
    bossMoveUp = True
    def bossMove(self):
        # for e in self.enemyShips:
        #     if(random.random() * e.speed > 0.9):
        #         if(e.posX > 2):
        #             e.move("a")
        #         else: 
        #             return True #return true that it made it to the other end
        bossShip = self.enemyShips[0]
        if self.bossMoveUp and random.randrange(10) <= bossShip.speed: 
            bossShip.move('w')
        elif not self.bossMoveUp and random.randrange(10) <= bossShip.speed:
            bossShip.move('s')
        if(bossShip.posY < 4):
            self.bossMoveUp = False
        elif(bossShip.posY > 20):
            self.bossMoveUp = True
        if(self.bossMoveCounter % 25 == 0):
            bossShip.move('a')
        self.bossMoveCounter += 1
        
        if(bossShip.posX > 3):
            return False
        else:
            return True

    def fireCannon(self):
        self.attacks.append(self.player.attack())
    
    def fireRocket(self):
        self.attacks.append(self.player.rocketAttack())
    def fireLaser(self):
        self.attacks.append(self.player.laserAttack())
    def enemiesDefeated(self):
        if(len(self.enemyShips) == 0):
            return True
        else:
            return False

    def enemyFire(self):
        factor = 0.05
        if isBossLevel: factor = 0.25
        for s in self.enemyShips:
            if(random.random() < factor):
                self.attacks.append(s.attack())
    
    def shotMove(self):
        for a in self.attacks:
            if(a.isPlayer == False):
                if(a.posX == 1):
                    self.attacks.remove(a)
                else:
                    didCollide = False
                    for a1 in self.attacks:
                        if(a.posX-1 == a1.posX and a.posY == a1.posY):
                            self.attacks.remove(a)
                            self.attacks.remove(a1)
                            didCollide = True
                    if(didCollide == False):
                        a.move('a')
                        playerHit = a.collideCheck(self.player.posX,self.player.posY)
                        if(playerHit):
                            return True
            else: #for when the player fires
                if(a.posX >= 78):
                    self.attacks.remove(a)
                else:
                    didCollide1 = False
                    for a1 in self.attacks:
                        if(a.posX+1 == a1.posX and a.posY == a1.posY):
                            self.attacks.remove(a)
                            self.attacks.remove(a1)
                            didCollide1 = True
                    if(didCollide1 == False):
                        a.move('d')
                        for e in self.enemyShips:
                            if(isBossLevel):
                                if e.posX - 1 == a.posX and (e.posY - 1 == a.posY or e.posY + 1 == a.posY or e.posY == a.posY):
                                    e.health -= 1
                                    if(e.health == 0):
                                        self.enemyShips.remove(e)
                                    self.attacks.remove(a)
                                    self.player.score += 20

                            elif(e.posX == a.posX and e.posY == a.posY): #if it hits, remove the ship and attack from respective arrays
                                e.health -= 1
                                if(e.health == 0):
                                    self.enemyShips.remove(e)
                                self.attacks.remove(a)
                                self.player.score += 1
        
                        
        return False
    
    def enemyMove(self):
        for e in self.enemyShips:
            if(random.randrange(10) <= e.speed):
                if(e.posX > 2):
                    e.move("a")
                else: 
                    return True #return true that it made it to the other end
        return False
    

    def trashMaker(self):
        #create the trash if we don't have any
        if(len(self.trash) < 3):
            if(len(self.trash) % 2 == 0):
                if(random.random() > 0.5):
                    self.trash.append(Trash(78,((random.random() * 487) % 22) + 1, 'a',"\u2727"))
                else:
                    self.trash.append(Trash(1,((random.random() * 487) % 22) + 1, 'd', "\u2727"))
            else:
                if(random.random() > 0.5):
                    self.trash.append(Trash(78,((random.random() * 487) % 22) + 1, 'a','o'))
                else:
                    self.trash.append(Trash(1,((random.random() * 487) % 22) + 1, 'd', 'o'))

    def trashMover(self):
        for t in self.trash:
            t.move()
            if(t.posX > 78 or t.posX < 1):
                self.trash.remove(t)


    
    def start(self, window):
        # star positions
        for i in range(10):
            color = 6
            if random.random() < 0.2: color = 7
            self.stars.append((random.randrange(22)+1, random.randrange(78)+1, '*',color))
        for i in range(15):
            color = 6
            if random.random() < 0.2: color = 7
            self.stars.append((random.randrange(22)+1, random.randrange(78)+1, '.', color))
        for i in range(10):
            color = 6
            if random.random() < 0.2: color = 7
            self.stars.append((random.randrange(22)+1, random.randrange(78)+1, '\u2727', color))

        curses.noecho()
        curses.cbreak()
        window.nodelay(True)
        window.keypad(True)
        printMap(self,window,self.stars)
        window.box()
        window.refresh()
        lasers, rockets = 5, 5
        # 4 is the 1 armor at start of round
        if 4 in self.player.itemsUnlocked:
            self.player.armor = min(self.player.health, self.player.armor + 1)
        playerHit = False
        ret = 0
        while(ret == 0):
            printMap(self,window,self.stars)
            window.refresh()
            try:
                userInput = window.getkey()
                if(userInput == 'w'):
                    self.player.move(userInput)
                if(userInput == 's'):
                    self.player.move(userInput)
                if(userInput == ' '):
                    self.fireCannon()
                # rockets are 5
                if (userInput == 'j' and 5 in self.player.itemsUnlocked and rockets > 0):
                    self.fireRocket()
                    rockets -= 1
                # laser is 11
                if (userInput == 'k' and 11 in self.player.itemsUnlocked and lasers > 0):
                    self.fireLaser()
                    lasers -= 1
            except curses.error:
                pass
            window.clear()
            window.box()
            printMap(self,window,self.stars)
            window.refresh()
            self.currentTime = time.time()
            if((self.currentTime - self.lastTime) > 0.05):
                if(random.random() < 0.5):
                    self.enemyFire()
                playerHit = self.shotMove()
                if(playerHit == True):
                    if (self.player.armor > 0):
                        self.player.armor -= 1
                    else:
                        self.player.health -= 1
                    if(self.player.health == 0):
                        ret = -1
                if(self.enemiesDefeated()):
                    ret = 1
                if(not isBossLevel and self.enemyMove()): #returns true if enemy made it to the other end
                    ret = -1
                elif len(self.enemyShips) > 0 and isBossLevel and self.bossMove():
                    ret = -1
                self.trashMover()
                self.trashMaker()
                self.lastTime = time.time()

            
            window.clear()
            window.box()
            printMap(self,window,self.stars)
            window.refresh()
        self.enemyShips.clear()
        self.attacks.clear()
        self.trash.clear()
        return ret
    

def bossprint(bossShip, std):
    #print around the 'M'
    for i in range(-1,2):
        for j in range(-1,2):
            std.addstr(bossShip.posY + i, bossShip.posX + j, bossShip.icon)

def printMap(roundObject,std,stars):
    global isBossLevel

    for t in roundObject.trash:
        if(t.direction == 'a'):
            std.addstr(int(t.posY),int(t.posX),str(t.head) + "=-")
        if(t.direction == 'd'):
            std.addstr(int(t.posY),int(t.posX), "-=" + str(t.head))

    for s in stars:
        std.addstr(s[0],s[1],s[2], curses.color_pair(s[3]))

    for s in roundObject.enemyShips:
        std.addstr(s.posY,s.posX,s.icon)
        if isBossLevel:
            bossprint(s,std)
    std.addstr(roundObject.player.posY,roundObject.player.posX,">", curses.color_pair(roundObject.player.colorCode))
    for a in roundObject.attacks:
        if a.dmg == 3:
            std.addstr(a.posY,a.posX,"\u2e27", curses.color_pair(1))
        elif a.dmg == 2:
            std.addstr(a.posY,a.posX,"\u2301", curses.color_pair(2))
        else:
            std.addstr(a.posY,a.posX,"~")

    for t in roundObject.trash:
        if(t.direction == 'a'):
            std.addstr(int(t.posY),int(t.posX),str(t.head) + "=-")
        if(t.direction == 'd'):
            std.addstr(int(t.posY),int(t.posX), "-=" + str(t.head))
    std.addstr(0,5, " Health:" + "\u2764" * roundObject.player.armor, curses.color_pair(3))
    std.addstr(0, (13 + roundObject.player.armor), "\u2764" * (roundObject.player.health - roundObject.player.armor) + " ", curses.color_pair(2)) 

    std.addstr(0,26, " Round: " + str(roundObject.roundNumber) + " ", curses.color_pair(3))
    std.addstr(0,46, " Score: " + str(roundObject.player.score) + " ", curses.color_pair(6))
    std.addstr(0,64, " Money: $" + str(roundObject.player.money) + " ", curses.color_pair(4))


