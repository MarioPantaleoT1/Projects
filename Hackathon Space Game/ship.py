from shot import Shot
from attack import Attack
import curses

class Ship():
    health: int
    maxHealth: int
    armor: int
    colorCode: int
    speed: int
    money: int
    score: int
    barriers: int
    posX: int
    posY: int
    attackprotos:list
    attackIdx:int
    isPlayer: bool
    itemsUnlocked: list
    icon: str

    def __init__(self, y, x, p, spd=1, health=3, icon='<', dmg=1):
        self.health = health
        self.maxHealth = health
        self.colorCode = 5
        self.armor = 0
        self.speed = spd
        self.money = 5
        self.score = 0
        self.barriers = 1
        self.posX = x
        self.posY = y
        self.attackIdx = 0
        self.attackprotos = []
        self.attackprotos.append(Attack(dmg,1)) # basic attack
        self.attackprotos.append(Attack(3, 1))
        self.attackprotos.append(Attack(2, 2))
        self.isPlayer = p
        self.itemsUnlocked = []
        self.icon = icon

    def move(self, dir):
        if(dir == 'w'):
            if(self.posY > 1):
                self.posY -= 1 * self.speed
        elif(dir == 's'):
            if(self.posY < 22):
                self.posY += 1 * self.speed
        elif(dir == 'a'):
            if(self.posX > 1):
                self.posX -= 1 * self.speed
        elif(dir == 'd'):
            if(self.posX < 79):
                self.posX += 1 * self.speed

        return (self.posX, self.posY)
    
    def attack(self):
        return Shot(self.attackprotos[self.attackIdx], self.posX, self.posY, self.isPlayer)
    def rocketAttack(self):
        return Shot(self.attackprotos[1], self.posX, self.posY, self.isPlayer)
    def laserAttack(self):
        return Shot(self.attackprotos[2], self.posX, self.posY, self.isPlayer)
    def isDead(self):
        if(self.health <= 0):
            return True
        else:
            return False
        

    

        

