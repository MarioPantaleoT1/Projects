
class Trash():
    posX: int
    posY: int
    direction: chr
    head: chr

    def __init__(self,posX, posY, direction, head):
        self.posX = posX
        self.posY = posY
        self.direction = direction
        self.head = head

    def move(self):
        if(self.direction == 'a'):
            self.posX -= 1
        if(self.direction == 'd'):
            self.posX += 1
            