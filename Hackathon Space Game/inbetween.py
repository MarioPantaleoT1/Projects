import curses
import random
from curses import textpad
class Frame:
    screen = 0
    inbetweenBox = 0
    healBox = 0
    shopBox = 0
    upgBox = 0
    conBox = 0
    def __init__(self, stdscr):    
        curses.curs_set(0)
        maxY, maxX = stdscr.getmaxyx()
        self.screen = stdscr
        self.inbetweenBox = curses.newwin(maxY, maxX)

    def printScreen(self, playerShip):
        self.inbetweenBox.clear()
        self.inbetweenBox.box()
        self.healBox = self.inbetweenBox.subwin(11, 39, 1, 1)
        self.healBox.box()
        self.healBox.addstr(1, 1 , "        _____             _____")
        self.healBox.addstr(2, 1,  "     /  ____  \\       /  ____  \\")
        self.healBox.addstr(3, 3,    "  /  |         \\ /          | \\")
        self.healBox.addstr(4, 6,        "|  |                    | |")
        self.healBox.addstr(5, 6,          " |  |               |  |")
        self.healBox.addstr(6, 8,            " |  |           |  |")
        self.healBox.addstr(7, 10,             " |  |       |  |")
        self.healBox.addstr(8, 12,               " |  |   |  |")
        self.healBox.addstr(9, 15,                 "|  |  |")

        self.healBox.addstr(5, 17, "Heal")
        self.healBox.addstr(6, 17, "[H]")
        self.shopBox = self.inbetweenBox.subwin(11, 39, 12, 1)
        self.shopBox.box()
        # from patorjk.com
        self.shopBox.addstr(1, 3, " _____ _")                
        self.shopBox.addstr(2, 3, "/  ___| |")                
        self.shopBox.addstr(3, 3, "\ `--.| |__   ___  _ __")
        self.shopBox.addstr(4, 3, " `--. \ '_ \ / _ \| '_ \ ")
        self.shopBox.addstr(5, 3, "/\__/ / | | | (_) | |_) |")
        self.shopBox.addstr(6, 3, "\____/|_| |_|\___/| .__/")
        self.shopBox.addstr(7, 3, "                | |    ")
        self.shopBox.addstr(8, 3, "                |_|    ")
        self.shopBox.addstr(8, 23, "[S]")
        self.upgBox = self.inbetweenBox.subwin(11, 39, 1, 40)
        self.upgBox.box()
        # from FBG
        self.upgBox.addstr(3, 11, ".-------..___")
        self.upgBox.addstr(4, 11, "'-._     :_.-'")
        self.upgBox.addstr(5, 11, ".- ) _ ( --.")
        self.upgBox.addstr(6, 11, ":  '-' '-'  ;.")
        self.upgBox.addstr(7, 11, "/'-.._____.-' |")
        self.upgBox.addstr(8, 11, "|   |     \   |")
        self.upgBox.addstr(9, 11, "\   |     /   \\")
        self.upgBox.addstr(2, 13, "Upgrade [U]")
        self.conBox = self.inbetweenBox.subwin(11, 39, 12, 40)
        self.conBox.box()
        self.conBox.addstr(2, 11, "⠀⠀⠀⢀⣴⣾⣦⣀⣀⣠⣿⣿⣷⠀⠀⠀⠀")
        self.conBox.addstr(3, 11, "⠀⠀⠀⠈⢻⣿⣿⣿⣿⣿⣿⣿⣧⠀⠀⠀⠀")
        self.conBox.addstr(4, 11, "⠀⠀⠀⢀⣾⣿⡿⠋⠁⠈⠙⢿⣿⣷⣶⣶⡆")
        self.conBox.addstr(5, 11, "⠀⢸⣿⣿⣿⣿⡇⠀⠀⠀⠀⢸⣿⣿⣿⣿⡇⠀")
        self.conBox.addstr(6, 11, "⠀⠘⠛⠛⠻⣿⣷⣤⣀⣀⣴⣿⣿⠏⠀⠀⠀⠀")
        self.conBox.addstr(7, 11, "⠀⠀⠀⠀⠀⣾⣿⣿⡿⠿⢿⣿⣿⣷⣿")
        self.conBox.addstr(8, 11, "⠀⠀⠀⠀⠸⠿⣿⡿⠀⠀⠀⠻⠿⠋")
        self.conBox.addstr(1, 15, "Configure")
        self.conBox.addstr(5, 18, "[C]")
        self.inbetweenBox.refresh()
    
    def makeSelection(self, playerShip):
        choice = ''
        while choice != 'h' and choice != 's' and choice != 'u' and choice != 'c':
            choice = self.inbetweenBox.getkey()
            choice = choice.lower()
        match choice:
            case 'h':
                self.healBox.clear()
                self.healBox.box()
                self.healBox.addstr(5, 10, "Heal to full health?")
                self.healBox.addstr(6, 17, "[Y]/[N]")
                self.healBox.refresh()
                while choice != 'y' and choice != 'n':
                    choice = self.healBox.getkey()
                if (choice == 'y'):
                    playerShip.health = min(playerShip.maxHealth, playerShip.health + 2)
                    return 'heal'
                else:
                    self.healBox.clear()
                    return '0'
            case 's':
                self.shopBox.clear()
                self.shopBox.box()
                self.shopBox.addstr(5, 11, "Enter the shop?")
                self.shopBox.addstr(6, 15, "[Y]/[N]")
                self.shopBox.refresh()
                while choice != 'y' and choice != 'n':
                    choice = self.shopBox.getkey()
                if (choice == 'y'):
                    active, inShop, exit = self.shopEvent([1, 2, 3, 4, 5, 6], [], playerShip)
                    while exit != 27:
                        active, inShop, exit = self.shopEvent(active, inShop, playerShip)
                    self.inbetweenBox.clear()
                    self.inbetweenBox.refresh()
                    return 'shop'
                else:
                    self.shopBox.clear()
                    return '0'
            case 'u':
                self.upgBox.clear()
                self.upgBox.box()
                self.upgBox.addstr(5, 10, "Upgrade your ship?")
                self.upgBox.addstr(6, 16, "[Y]/[N]")
                self.upgBox.refresh()
                while choice != 'y' and choice != 'n':
                    choice = self.upgBox.getkey()
                if (choice == 'y'):
                    self.inbetweenBox.clear()
                    self.inbetweenBox.box()
                    self.inbetweenBox.addstr(1, 1, "What would you like to upgrade?")
                    self.inbetweenBox.addstr(2, 1, "[1] Max Health + 1")
                    self.inbetweenBox.addstr(3, 1, "[2] Basic Attack Damage + 1")
                    # self.inbetweenBox.addstr(4, 1, "[3] Barrier Charges + 1")
                    while choice != '1' and choice != '2' and choice != '3':
                        choice = self.inbetweenBox.getkey()
                    match choice:
                        case '1':
                            playerShip.maxHealth = playerShip.maxHealth + 1
                            playerShip.health = playerShip.health + 1
                        case '2':
                            playerShip.attackprotos[0].dmg += 1
                        case '3':
                            playerShip.barriers += 1
                    return 'upgrade'
                else:
                    self.upgBox.clear()
                    return '0'
            case 'c':
                self.conBox.clear()
                self.conBox.box()
                self.conBox.addstr(5, 10, "Configure your ship?")
                self.conBox.addstr(6, 13, "(Free action)")
                self.conBox.addstr(7, 16, "[Y]/[N]")
                self.conBox.refresh()
                while choice != 'y' and choice != 'n':
                    choice = self.conBox.getkey()
                if (choice == 'y'):
                    self.inbetweenBox.clear()
                    self.inbetweenBox.box()
                    self.inbetweenBox.addstr(1, 1, "What skin would you like to equip?")
                    skinList = ['Blue Ship Skin', 'Pink Ship Skin', 'Green Ship Skin', 'Red Ship Skin']
                    skinString = ''
                    iter = 1
                    optionList = []
                    for option in playerShip.itemsUnlocked:
                        if option == 7 or option == 8 or option == 9 or option == 10:
                            skinString += '[' + str(iter) + '] ' + skinList[option - 7]
                            skinString += ' '
                            iter += 1
                            optionList.append(option)
                    self.inbetweenBox.addstr(2, 1, skinString)
                    self.inbetweenBox.addstr(3, 1, "[Esc]")
                    while choice != 49 and choice != 50 and choice != 51 and choice != 52 and choice != 27:
                        choice = self.inbetweenBox.getch()
                    if choice == 27:
                        return '0'
                    choice = choice - 49
                    skinDict = {7: 3, 8: 1, 9: 4, 10: 2}
                    match choice:
                        case 0:
                            playerShip.colorCode = skinDict[optionList[0]]
                        case 1:
                            playerShip.colorCode = skinDict[optionList[1]]
                        case 2:
                            playerShip.colorCode = skinDict[optionList[2]]
                        case 3:
                            playerShip.colorCode = skinDict[optionList[3]]
                            
                    return '0'
                else:
                    self.conBox.clear()
                    return '0'
        # self.inbetweenBox.refresh()
        # self.inbetweenBox.getch()
        
        
    def shopEvent(self, active, items, playerShip):
        choice = 0
        # Add more Items
        shopItems = {1: ['+2 Health', 2],
                     2: ['+2 Armor', 2],
                     3: ['+1 Max Health', 3],
                     4: ['+1 Armor each round', 5],
                     5: ['+5 Rockets [j to fire]', 5],
                     6: ['Mines', 5],
                     7: ['Blue Ship Skin', 3],
                     8: ['Pink Ship Skin', 3],
                     9: ['Green Ship Skin', 3],
                     10: ['Red Ship Skin', 3],
                     11: ['+5 Lasers [k to fire]', 5]
                     }
        if (len(items) == 0):
            inShop = random.sample(range(1, 12), 6)
        else:
            inShop = items.copy()
        self.inbetweenBox.clear()
        self.inbetweenBox.box()
        item1 = self.inbetweenBox.subwin(10, 26, 1, 1)
        if 1 in active:
            item1.addstr(4, 2, '$' + str(shopItems[inShop[0]][1]))
            item1.addstr(5, 2, shopItems[inShop[0]][0])
            item1.addstr(6, 2, '[1]')
        item1.box()
        item2 = self.inbetweenBox.subwin(10, 26, 1, 27)
        if 2 in active:
            item2.addstr(4, 2, '$' + str(shopItems[inShop[1]][1]))
            item2.addstr(5, 2, shopItems[inShop[1]][0])
            item2.addstr(6, 2, '[2]')
        item2.box()
        item3 = self.inbetweenBox.subwin(10, 26, 1, 53)
        if 3 in active:
            item3.addstr(4, 2, '$' + str(shopItems[inShop[2]][1]))
            item3.addstr(5, 2, shopItems[inShop[2]][0])
            item3.addstr(6, 2, '[3]')
        item3.box()
        item4 = self.inbetweenBox.subwin(10, 26, 11, 1)
        if 4 in active:
            item4.addstr(4, 2, '$' + str(shopItems[inShop[3]][1]))
            item4.addstr(5, 2, shopItems[inShop[3]][0])
            item4.addstr(6, 2, '[4]')
        item4.box()
        item5 = self.inbetweenBox.subwin(10, 26, 11, 27)
        if 5 in active:
            item5.addstr(4, 2, '$' + str(shopItems[inShop[4]][1]))
            item5.addstr(5, 2, shopItems[inShop[4]][0])
            item5.addstr(6, 2, '[5]')
        item5.box()
        item6 = self.inbetweenBox.subwin(10, 26, 11, 53)
        if 6 in active:
            item6.addstr(4, 2, '$' + str(shopItems[inShop[5]][1]))
            item6.addstr(5, 2, shopItems[inShop[5]][0])
            item6.addstr(6, 2, '[6]')
        item6.box()
        self.inbetweenBox.addstr(22, 34, "Leave: [Esc]")
        self.inbetweenBox.addstr(21, 34, "Money: $" + str(playerShip.money))
        self.inbetweenBox.refresh()
        while (choice != 49 and choice != 50 and choice != 51 and choice != 52
        and choice != 53 and choice != 54 and choice != 27):
            choice = self.inbetweenBox.getch()
        if (choice == 27):
            return active, inShop, choice
        choice = choice - 49
        chosen = False
        match inShop[choice]:
            case 1:
                if (playerShip.money >= shopItems[1][1] and ((choice + 1) in active)):
                    playerShip.health = min(playerShip.maxHealth, playerShip.health + 2)
                    playerShip.money -= shopItems[1][1]
                    chosen = True
            case 2:
                if (playerShip.money >= shopItems[2][1] and ((choice + 1) in active)):
                    playerShip.armor = min(playerShip.health, playerShip.armor + 2)
                    playerShip.money -= shopItems[2][1]
                    chosen = True
            case 3:
                if (playerShip.money >= shopItems[3][1] and ((choice + 1) in active)):
                    playerShip.maxHealth = playerShip.maxHealth + 1
                    playerShip.health = playerShip.health + 1
                    playerShip.money -= shopItems[3][1]
                    chosen = True
            case 4:
                if (playerShip.money >= shopItems[4][1] and ((choice + 1) in active)):
                    playerShip.itemsUnlocked.append(4)
                    playerShip.money -= shopItems[4][1]
                    chosen = True
            case 5:
                if (playerShip.money >= shopItems[5][1] and ((choice + 1) in active)):
                    playerShip.itemsUnlocked.append(5)
                    playerShip.money -= shopItems[5][1]
                    chosen = True
            case 6:
                if (playerShip.money >= shopItems[6][1] and ((choice + 1) in active)):
                    playerShip.itemsUnlocked.append(6)
                    playerShip.money -= shopItems[6][1]
                    chosen = True
            case 7:
                if (playerShip.money >= shopItems[7][1] and ((choice + 1) in active)):
                    playerShip.itemsUnlocked.append(7)
                    playerShip.money -= shopItems[7][1]
                    chosen = True
            case 8:
                if (playerShip.money >= shopItems[8][1] and ((choice + 1) in active)):
                    playerShip.itemsUnlocked.append(8)
                    playerShip.money -= shopItems[8][1]
                    chosen = True
            case 9:
                if (playerShip.money >= shopItems[9][1] and ((choice + 1) in active)):
                    playerShip.itemsUnlocked.append(9)
                    playerShip.money -= shopItems[9][1]
                    chosen = True
            case 10:
                if (playerShip.money >= shopItems[10][1] and ((choice + 1) in active)):
                    playerShip.itemsUnlocked.append(10)
                    playerShip.money -= shopItems[10][1]
                    chosen = True
            case 11:
                if (playerShip.money >= shopItems[11][1] and ((choice + 1) in active)):
                    playerShip.itemsUnlocked.append(11)
                    playerShip.money -= shopItems[11][1]
                    chosen = True
        if chosen:
            match choice:
                case 0:
                    item1.clear()
                    item1.box()
                    active.remove(1)
                case 1:
                    item2.clear()
                    item2.box()
                    active.remove(2)
                case 2:
                    item3.clear()
                    item3.box()
                    active.remove(3)
                case 3:
                    item4.clear()
                    item4.box()
                    active.remove(4)
                case 4:
                    item5.clear()
                    item5.box()
                    active.remove(5)
                case 5:
                    item6.clear()
                    item6.box()
                    active.remove(6)
        return active, inShop, choice
            


    
