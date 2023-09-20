#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <time.h>
#include <limits.h>
#include <unistd.h>
#include <ncurses.h>
#include <vector>
#include <iterator>
#include <iostream>
#include <fstream>


#include "minHeap.h"
#include "charHeap.h"


/**
 * TESTING INFO - FULL BOX
*/

/**
 * Want to do post assignment:
 *  - saving via a button in menu that will write to a file
 *  - randomly generate gyms and have a button in menu that tells you where they are located
 *  - Make badges and elite four and champion
 *  - Make all moves work
*/

/**
 * 2-14 notes for 1.04
 * Give all moving characters a sequence number
 * when they move, they have their next turn set to their time of turn
 * they go in order of next turn weight (weight of place to move)
 * if there is a tie, the one with the lowest sequence number goes first.
 * 
 * Idea: move based on distance map generated every @ move, check neighbors and go to smallest one.
*/

//bottom row is 20 starting at 0
//last col is 79 starting at 0

/**
 * Next assignment: pathfinding.
 * Find the shortest path from all the places the npcs can be to the playable character
 * dijkstras algo
 * keep information on cost map inside of each respective map or world map
*/

//throw in random position and go up or down
class trainers_t{
    public:
        int hikerX, hikerY, rivalX, rivalY, swim1X, swim1Y, swim2X, swim2Y, pace1X, pace1Y, pace2X, pace2Y, wand1X, wand1Y, sentry1X, sentry1Y, sentry2X, sentry2Y, explorer1X, explorer1Y, hikerDef, rivalDef, swim1Def, swim2Def, pace1Def, pace2Def, wand1Def, sentry1Def, sentry2Def, exp1Def;
};

class map_t{
    public:
        char singleMap[21][80];
        int roadEastY;
        int roadWestY;
        int roadNorthX;
        int roadSouthX;
        int centerEntranceX;
        int centerEntranceY;
        char characterMap[21][80];
        trainers_t trainers;
};

class pokemon_t{
    public:
        int dexNum;
        std::string name;
        int speciesID;
        int height;
        int weight;
        int baseXP;
        int order;
        int isDefault;
};

class moves_t{
    public:
        int id;
        std::string name;
        int genID;
        int typeID;
        int power;
        int pp;
        int accuracy;
        int priority;
        int targetID;
        int dmgClassID;
        int effectID;
        int effectChance;
        int contestTypeID;
        int contestEffectID;
        int superContEffectID;
};

class pokemonMoves_t{
    public:
        int pokemonID;
        int versionGroupID;
        int moveID;
        int pokeMoveMethodID;
        int level;
        int order;
};

class pokemonStats_t {
    public:
        int pokemonID;
        int statID;
        int baseStat;
        int effort;
};

class pokemonSpecies_t{
    public:
        int dexNum;
        std::string name;
        int genID;
        int evolveFromID;
        int evolveChainID;
        int colorID;
        int shapeID;
        int habitatID;
        int genderRate;
        int captureRate;
        int baseHappy;
        int isBaby;
        int hatchCounter;
        int hasGenderDiff;
        int growthRateID;
        int formsSwitchable;
        int isLegendary;
        int isMythical;
        int order;
        int conqOrder;
};

class experience_t {
    public:
        int growthRateID;
        int level;
        int experience;
};

class typeNames_t {
    public:
        int typeID;
        int localLangID;
        std::string name;
};

class stats_t {
    public:
        int id;
        int damageClassID;
        std::string statName;
        int isBattleOnly;
        int gameIndex;
};

class pokemonType_t {
    public:
        int pokemonID;
        int typeID;
        int slot;
};

class extraPokeInfo_t{
    public:
        int currentHP;
        std::vector<int> ppLeft;
        int curXp;
        int curXpIndex;
};

class evolutionInfo_t {
    public:
        int evoID;
        int evoDexNum;
        int evoTriggerID;
        int triggerItemID;
        int minLevel;
        int genderID;
        int locID;
        int heldItemID;
        std::string tod;
        int knownMoveID;
        int kMoveTypeID;
        int minHap;
        int minBeau;
        int minAff;
        int relPhysStats;
        int partySID;
        int partyTID;
        int tradeID;
        int overrain;
        int upsidedown;
};

class allPokemonInfo_t {
    public:
        std::vector<pokemon_t> pokemon;
        std::vector<moves_t> moves;
        std::vector<pokemonMoves_t> pokemonMoves;
        std::vector<pokemonSpecies_t> pokemonSpecies;
        std::vector<experience_t> experience;
        std::vector<typeNames_t> typeNames;
        std::vector<pokemonStats_t> pokemonStats;
        std::vector<stats_t> stats;
        std::vector<pokemonType_t> pokemonTypes;
        std::vector<evolutionInfo_t> evolutionInfo;
};

class actualPokemon_t {
    public:
        pokemon_t pokemon;
        std::vector<moves_t> moves;
        std::vector<pokemonMoves_t> pokemonMoves;
        pokemonSpecies_t pokemonSpecies;
        experience_t experience;
        std::vector<typeNames_t> typeNames;
        std::vector<pokemonStats_t> pokemonStats;
        std::vector<int> stats;
        std::vector<pokemonType_t> pokemonTypes;
        extraPokeInfo_t extraInfo;
        evolutionInfo_t evolutionInfo;
        int uid;
        int learnMoveIndex;
};

//id order: pokeballs, greatballs, ultraballs, potions, superpotions, hyperpotions, revives, fullRevives
class item_t{
    public:
        std::vector<int> count{5, 0, 0, 5, 0, 0, 5, 0};
        std::vector<double> effect{0.75, 1.5, 2.25, 20, 60, 200, 0.5, 1};
};

class player_t{
    public:
        int playerX;
        int playerY;
        //only used for fly because im stupid
        int worldX;
        int worldY;
        std::vector<actualPokemon_t> pokemon;
        item_t bag;
        std::vector<actualPokemon_t> boxPokemon;
        int money = 1000;
};

class world_t{
    public:
        map_t *worldMap[401][401];
        int hikerMap[21][80];
        int rivalMap[21][80];
        //char characterMap[21][80];
        player_t player;
};
/**
 * 1) Normal    2) Fighting     3) Flying   4) Poison   5) Ground
 * 6) Rock      7) Bug          8) Ghost    9) Steel    10) Fire
 * 11) Water    12) Grass     13) Electric  14) Psychic 15) Ice
 * 16) Dragon   17) Dark        18) Fairy
*/
class typeChart_t {
    public:
        double typeChart[18][18] = {{1, 1, 1, 1, 1, 0.5, 1, 0, 0.5, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                    {2, 1, 0.5, 0.5, 1, 2, 0.5, 0, 2, 1, 1, 1, 1, 0.5, 2, 1, 2, 0.5},
                                    {1, 2, 1, 1, 1, 0.5, 2, 1, 0.5, 1, 1, 2, 0.5, 1, 1, 1, 1, 1},
                                    {1, 1, 1, 0.5, 0.5, 0.5, 1, 0.5, 0, 1, 1, 2, 1, 1, 1, 1, 1, 2},
                                    {1, 1, 0, 2, 1, 2, 0.5, 1, 2, 2, 1, 0.5, 2, 1, 1, 1, 1, 1},
                                    {1, 0.5, 2, 1, 0.5, 1, 2, 1, 0.5, 2, 1, 1, 1, 1, 2, 1, 1, 1},
                                    {1, 0.5, 0.5, 0.5, 1, 1, 1, 0.5, 0.5, 0.5, 1, 2, 1, 2, 1, 1, 2, 0.5},
                                    {0, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 0.5, 1},
                                    {1, 1, 1, 1, 1, 2, 1, 1, 0.5, 0.5, 0.5, 1, 0.5, 1, 2, 1, 1, 2},
                                    {1, 1, 1, 1, 1, 0.5, 2, 1, 2, 0.5, 0.5, 2, 1, 1, 2, 0.5, 1, 1},
                                    {1, 1, 1, 1, 2, 2, 1, 1, 1, 2, 0.5, 0.5, 1, 1, 1, 0.5, 1, 1},
                                    {1, 1, 0.5, 0.5, 2, 2, 0.5, 1, 0.5, 0.5, 2, 0.5, 1, 1, 1, 0.5, 1, 1},
                                    {1, 1, 2, 1, 0, 1, 1, 1, 1, 1, 2, 0.5, 0.5, 1, 1, 0.5, 1, 1},
                                    {1, 2, 1, 2, 1, 1, 1, 1, 0.5, 1, 1, 1, 1, 0.5, 1, 1, 0, 1},
                                    {1, 1, 2, 1, 2, 1, 1, 1, 0.5, 0.5, 0.5, 2, 1, 1, 0.5, 2, 1, 1},
                                    {1, 1, 1, 1, 1, 1, 1, 1, 0.5, 1, 1, 1, 1, 1, 1, 2, 1, 0},
                                    {1, 0.5, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 0.5, 0.5},
                                    {1, 2, 1, 0.5, 1, 1, 1, 1, 0.5, 0.5, 1, 1, 1, 1, 1, 2, 2, 1}};
};

world_t myWorld;
allPokemonInfo_t allPokeInfo;
typeChart_t typeChart;


int min(int i, int j){
    if (i < j){
        return i;
    }
    return j;
}

int max(int i, int j){
    if (i > j){
        return i;
    }
    return j;
}

/**
 * Check Sets check all cardinal directions to see if a pokecenter/mart can go there
 * Also rolls the equation to see if one will go there if there is space.
*/
int checkSetUp(map_t *map, int x, int y, char c, float dist, float randFloat){
    if (map->singleMap[y - 1][x] != '%' && map->singleMap[y - 1][x] != '#' && map->singleMap[y - 1][x] != 'C'
     && map->singleMap[y - 2][x] != '%' && map->singleMap[y - 2][x] != '#' && map->singleMap[y - 2][x] != 'C'
     && map->singleMap[y - 1][x + 1] != '%' && map->singleMap[y - 1][x + 1] != '#' && map->singleMap[y - 1][x + 1] != 'C'
     && map->singleMap[y - 2][x + 1] != '%' && map->singleMap[y - 2][x + 1] != '#' && map->singleMap[y - 2][x + 1] != 'C'){
        if (randFloat > dist){
            map->singleMap[y - 1][x] = c;
            map->singleMap[y - 2][x] = c;
            map->singleMap[y - 1][x + 1] = c;
            map->singleMap[y - 2][x + 1] = c;
        }
        return 1;
    }
    return 0;
}

int checkSetDown(map_t *map, int x, int y, char c, float dist, float randFloat){
    if (map->singleMap[y + 1][x] != '%' && map->singleMap[y + 1][x] != '#' && map->singleMap[y + 1][x] != 'C'
     && map->singleMap[y + 2][x] != '%' && map->singleMap[y + 2][x] != '#' && map->singleMap[y + 2][x] != 'C'
     && map->singleMap[y + 1][x + 1] != '%' && map->singleMap[y + 1][x + 1] != '#' && map->singleMap[y + 1][x + 1] != 'C'
     && map->singleMap[y + 2][x + 1] != '%' && map->singleMap[y + 2][x + 1] != '#' && map->singleMap[y + 2][x + 1] != 'C'){
        if (randFloat > dist){
            map->singleMap[y + 1][x] = c;
            map->singleMap[y + 2][x] = c;
            map->singleMap[y + 1][x + 1] = c;
            map->singleMap[y + 2][x + 1] = c;
        }
        return 1;
    }
    return 0;
}

int checkSetRight(map_t *map, int x, int y, char c, float dist, float randFloat){
    if (map->singleMap[y][x + 1] != '%' && map->singleMap[y][x + 1] != '#' && map->singleMap[y][x + 1] != 'C'
     && map->singleMap[y][x + 2] != '%' && map->singleMap[y][x + 2] != '#' && map->singleMap[y][x + 2] != 'C'
     && map->singleMap[y + 1][x + 1] != '%' && map->singleMap[y + 1][x + 1] != '#' && map->singleMap[y + 1][x + 1] != 'C'
     && map->singleMap[y + 1][x + 2] != '%' && map->singleMap[y + 1][x + 2] != '#' && map->singleMap[y + 1][x + 2] != 'C'){
        if (randFloat > dist ){
            map->singleMap[y][x + 1] = c;
            map->singleMap[y][x + 2] = c;
            map->singleMap[y + 1][x + 1] = c;
            map->singleMap[y + 1][x + 2] = c;
        }
        return 1;
    }
    return 0;
}

int checkSetLeft(map_t *map, int x, int y, char c, float dist, float randFloat){
    if (map->singleMap[y][x - 1] != '%' && map->singleMap[y][x - 1] != '#' && map->singleMap[y][x - 1] != 'C'
     && map->singleMap[y][x - 2] != '%' && map->singleMap[y][x - 2] != '#' && map->singleMap[y][x - 2] != 'C'
     && map->singleMap[y + 1][x - 1] != '%' && map->singleMap[y + 1][x - 1] != '#' && map->singleMap[y + 1][x - 1] != 'C'
     && map->singleMap[y + 1][x - 2] != '%' && map->singleMap[y + 1][x - 2] != '#' && map->singleMap[y + 1][x - 2] != 'C'){
        if (randFloat > dist){
            map->singleMap[y][x - 1] = c;
            map->singleMap[y][x - 2] = c;
            map->singleMap[y + 1][x - 1] = c;
            map->singleMap[y + 1][x - 2] = c;
        }
        return 1;
    }
    return 0;
}

void printMap(map_t map){
    clear();
    int color = 0;
    for (int j = 0; j < 21; j++){
        for (int k = 0; k < 80; k++){
            if (map.characterMap[j][k] == 'X'){
                if (map.singleMap[j][k] == '.' || map.singleMap[j][k] == ':'){
                    attron(COLOR_PAIR(3));
                    color = 3;
                }
                else if (map.singleMap[j][k] == '~'){
                    attron(COLOR_PAIR(1));
                    color = 1;
                }
                else if (map.singleMap[j][k] == '^'){
                    attron(COLOR_PAIR(6));
                    color = 2;
                }
                else if (map.singleMap[j][k] == '#'){
                    attron(COLOR_PAIR(5));
                    color = 4;
                }
                else if (map.singleMap[j][k] == 'C' || map.singleMap[j][k] == 'M'){
                    attron(COLOR_PAIR(4));
                    color = 6;
                }
                else if (map.singleMap[j][k] == '%'){
                    attron(COLOR_PAIR(2));
                    color = 5;
                }
                printw("%c", map.singleMap[j][k]);
                attroff(COLOR_PAIR(color));
            }
            else {
                attron(COLOR_PAIR(8));
                color = 8;
                printw("%c", map.characterMap[j][k]);
                attroff(COLOR_PAIR(color));
            }
        }
        printw("\n");
    }
    refresh();
}

/**
 * Actual function that puts things into place on each map
*/
void buildMap(map_t *map, int worldY, int worldX, char dir){
    
    for (int j = 0; j < 21; j++){
        for (int k = 0; k < 80; k++){
            if (j == 0 || k == 0 || j == 20 || k == 79){
                map->singleMap[j][k] = '%';
            }
            else {
                map->singleMap[j][k] = '.';
            }
            map->characterMap[j][k] = 'X';
        }
    }
    //add if statements to check neighbors for exits

    map->roadEastY = rand() % (19 + 1 - 1) + 1;
    map->roadWestY = rand() % (19 + 1 - 1) + 1;
    map->roadNorthX = rand() % (78 + 1 - 1) + 1;
    map->roadSouthX = rand() % (78 + 1 - 1) + 1;

    //check right map
    if (worldX + 1 <= 400 && myWorld.worldMap[worldY][worldX + 1] != NULL){
        map->roadEastY = myWorld.worldMap[worldY][worldX + 1]->roadWestY;
    }
    //check left map
    if (worldX - 1 >= 0 && myWorld.worldMap[worldY][worldX - 1] != NULL){
        map->roadWestY = myWorld.worldMap[worldY][worldX - 1]->roadEastY;
    }
    //check down map
    if (worldY + 1 <= 400 && myWorld.worldMap[worldY + 1][worldX] != NULL){
        map->roadSouthX = myWorld.worldMap[worldY + 1][worldX]->roadNorthX;
    }
    //check up map
    if (worldY - 1 >= 0 && myWorld.worldMap[worldY - 1][worldX] != NULL){
        map->roadNorthX = myWorld.worldMap[worldY - 1][worldX]->roadSouthX;
    }

    //edge of world road checks, only set up edge roads if not on edge
    if (worldX - 1 >= 0){
        map->singleMap[map->roadWestY][0] = '#';
    }
    if (worldX + 1 <= 400){
        map->singleMap[map->roadEastY][79] = '#';
    }
    if (worldY - 1 >= 0){
        map->singleMap[0][map->roadNorthX] = '#';
    }
    if (worldY + 1 <= 400){
        map->singleMap[20][map->roadSouthX] = '#';
    }

    //tall grass
    int tempX = rand() % (78 + 1 - 1) + 1;
    int tempY = rand() % (19 + 1 - 1) + 1;
    map->singleMap[tempY][tempX] = ':';
    int areaX = min(79, tempX + (rand() % (25 + 1 - 1) + 1));
    int areaY = min(20, tempY + (rand() % (15 + 1 - 1) + 1));
    for (int i = tempY; i < areaY; i++){
        for (int j = tempX; j < areaX; j++){
            if (map->singleMap[i][j] != '%' && map->singleMap[i][j] != '#'){
                map->singleMap[i][j] = ':';
            }
        }
    }
    //if tall grass was so good then where's tall grass 2?
    for (int x = 0; x < 2; x++){
        tempX = rand() % (78 + 1 - 1) + 1;
        tempY = rand() % (19 + 1 - 1) + 1;
        map->singleMap[tempY][tempX] = ':';
        areaX = min(79, tempX + (rand() % (25 + 1 - 1) + 1));
        areaY = min(20, tempY + (rand() % (15 + 1 - 1) + 1));
        for (int i = tempY; i < areaY; i++){
            for (int j = tempX; j < areaX; j++){
                if (map->singleMap[i][j] != '%' && map->singleMap[i][j] != '#'){
                    map->singleMap[i][j] = ':';
                }
            }
        }
    }
    //water
    tempX = rand() % (78 + 1 - 1) + 1;
    tempY = rand() % (19 + 1 - 1) + 1;
    map->singleMap[tempY][tempX] = '~';
    areaX = min(79, tempX + (rand() % (25 + 1 - 1) + 1));
    areaY = min(20, tempY + (rand() % (15 + 1 - 2) + 2));
    for (int i = tempY; i < areaY; i++){
        for (int j = tempX; j < areaX; j++){
            if (map->singleMap[i][j] != '%' && map->singleMap[i][j] != '#' && map->singleMap[i][j] != ':'){
                map->singleMap[i][j] = '~';
            }
        }
    }
    //trees
    for (int i = 0; i < 40; i++){
        int k = rand() % (78 + 1 - 1) + 1;
        int j = rand() % (19 + 1 - 1) + 1;
        if (map->singleMap[j][j] != '%' && map->singleMap[j][k] != '#' && map->singleMap[j][k] != ':' && map->singleMap[j][k] != '~'){
                map->singleMap[j][k] = '^';
            }
    }
    //ඞ
    //roads
    for (int i = 1; i < 79; i++){
        map->singleMap[map->roadWestY][i] = '#';
    }
    if (map->roadWestY <= map->roadEastY) {
        for (int i = 1; map->roadWestY + i <= map->roadEastY; i++){
            map->singleMap[map->roadWestY + i][78] = '#';
        }
    }
    else {
        for (int i = 1; map->roadWestY - i >= map->roadEastY; i++){
            map->singleMap[map->roadWestY - i][78] = '#';
        }
    }
    for (int i = 1; i < 20; i++){
        map->singleMap[i][map->roadNorthX] = '#';
    }
    if (map->roadNorthX <= map->roadSouthX){
        for (int i = 1; map->roadNorthX + i <= map->roadSouthX; i++){
            map->singleMap[19][map->roadNorthX + i] = '#';
        }
    }
    else {
        for (int i = 1; map->roadNorthX - i >= map->roadSouthX; i++){
            map->singleMap[19][map->roadNorthX - i] = '#';
        }
    }

    //hiker and rival
    while (1){
        tempX = rand() % (78 + 1 - 1) + 1;
        tempY = rand() % (19 + 1 - 1) + 1;
        if (map->singleMap[tempY][tempX] != '~' && map->singleMap[tempY][tempX] != '^' && map->singleMap[tempY][tempX] != '#'){
            map->trainers.hikerX = tempX;
            map->trainers.hikerY = tempY;
            map->trainers.hikerDef = 0;
            map->characterMap[tempY][tempX] = 'h';
            break;
        }
    }
    while (1){
        tempX = rand() % (78 + 1 - 1) + 1;
        tempY = rand() % (19 + 1 - 1) + 1;
        if (map->singleMap[tempY][tempX] != '~' && map->singleMap[tempY][tempX] != '^' && map->singleMap[tempY][tempX] != '#' && map->characterMap[tempY][tempX] == 'X'){
            map->trainers.rivalX = tempX;
            map->trainers.rivalY = tempY;
            map->trainers.rivalDef = 0;
            map->characterMap[tempY][tempX] = 'r';
            break;
        }
    }

    //swimmers
    while (1){
        tempX = rand() % (78 + 1 - 1) + 1;
        tempY = rand() % (19 + 1 - 1) + 1;
        if (map->singleMap[tempY][tempX] == '~'){
            map->trainers.swim1X = tempX;
            map->trainers.swim1Y = tempY;
            map->trainers.swim1Def = 0;
            map->characterMap[tempY][tempX] = 'm';
            break;
        }
    }
    while (1){
        tempX = rand() % (78 + 1 - 1) + 1;
        tempY = rand() % (19 + 1 - 1) + 1;
        if (map->singleMap[tempY][tempX] == '~'){
            map->trainers.swim2X = tempX;
            map->trainers.swim2Y = tempY;
            map->trainers.swim2Def = 0;
            map->characterMap[tempY][tempX] = 'm';
            break;
        }
    }

    //sentries
    while (1){
        tempX = rand() % (78 + 1 - 1) + 1;
        tempY = rand() % (19 + 1 - 1) + 1;
        if (map->singleMap[tempY][tempX] != '~' && map->singleMap[tempY][tempX] != 'M' && map->singleMap[tempY][tempX] != 'C'
        && map->singleMap[tempY][tempX] != '#' && map->characterMap[tempY][tempX] == 'X'){
            map->trainers.sentry1X = tempX;
            map->trainers.sentry1Y = tempY;
            map->trainers.sentry1Def = 0;
            map->characterMap[tempY][tempX] = 's';
            break;
        }
    }
    while (1){
        tempX = rand() % (78 + 1 - 1) + 1;
        tempY = rand() % (19 + 1 - 1) + 1;
        if (map->singleMap[tempY][tempX] != '~' && map->singleMap[tempY][tempX] != 'M' && map->singleMap[tempY][tempX] != 'C'
        && map->singleMap[tempY][tempX] != '#' && map->characterMap[tempY][tempX] == 'X'){
            map->trainers.sentry2X = tempX;
            map->trainers.sentry2Y = tempY;
            map->trainers.sentry2Def = 0;
            map->characterMap[tempY][tempX] = 's';
            break;
        }
    }

    //pacers
    while (1){
        tempX = rand() % (78 + 1 - 1) + 1;
        tempY = rand() % (19 + 1 - 1) + 1;
        if (map->singleMap[tempY][tempX] != '~' && map->singleMap[tempY][tempX] != 'M' && map->singleMap[tempY][tempX] != 'C'
        && map->singleMap[tempY][tempX] != '#' && map->characterMap[tempY][tempX] == 'X'){
            map->trainers.pace1X = tempX;
            map->trainers.pace1Y = tempY;
            map->trainers.pace1Def = 0;
            map->characterMap[tempY][tempX] = 'p';
            break;
        }
    }

    while (1){
        tempX = rand() % (78 + 1 - 1) + 1;
        tempY = rand() % (19 + 1 - 1) + 1;
        if (map->singleMap[tempY][tempX] != '~' && map->singleMap[tempY][tempX] != 'M' && map->singleMap[tempY][tempX] != 'C'
        && map->singleMap[tempY][tempX] != '#' && map->characterMap[tempY][tempX] == 'X'){
            map->trainers.pace2X = tempX;
            map->trainers.pace2Y = tempY;
            map->trainers.pace2Def = 0;
            map->characterMap[tempY][tempX] = 'p';
            break;
        }
    }

    //explorer
    while (1){
        tempX = rand() % (78 + 1 - 1) + 1;
        tempY = rand() % (19 + 1 - 1) + 1;
        if (map->singleMap[tempY][tempX] != '~' && map->singleMap[tempY][tempX] != 'M' && map->singleMap[tempY][tempX] != 'C'
        && map->singleMap[tempY][tempX] != '#' && map->characterMap[tempY][tempX] == 'X'){
            map->trainers.explorer1X = tempX;
            map->trainers.explorer1Y = tempY;
            map->trainers.exp1Def = 0;
            map->characterMap[tempY][tempX] = 'e';
            break;
        }
    }

    //wanderer
    while (1){
        tempX = rand() % (78 + 1 - 1) + 1;
        tempY = rand() % (19 + 1 - 1) + 1;
        if (map->singleMap[tempY][tempX] != '~' && map->singleMap[tempY][tempX] != 'M' && map->singleMap[tempY][tempX] != 'C'
        && map->singleMap[tempY][tempX] != '#' && map->characterMap[tempY][tempX] == 'X'){
            map->trainers.wand1X = tempX;
            map->trainers.wand1Y = tempY;
            map->trainers.wand1Def = 0;
            map->characterMap[tempY][tempX] = 'w';
            break;
        }
    }

    //poke center and mart
    //gets equation then generates a random float and sees if it is < random float
    int manDist = (worldX + worldY - 400) * (worldX + worldY - 400);
    float spawnEq = ((-45 * manDist)/200 + 50)/100;
    if (spawnEq < 0){
        spawnEq = spawnEq * -1;
    }
    float spawnRand;
    while (1){
        int x = rand() % (76 + 1 - 1) + 1;
        int y = rand() % (17 + 1 - 1) + 1;
        spawnRand = ((float) rand() / RAND_MAX);
        spawnRand *= 400;
        if (map->singleMap[y][x] == '#' && (checkSetDown(map, x, y, 'C', spawnEq, spawnRand) == 1 || checkSetUp(map, x, y, 'C', spawnEq, spawnRand) == 1
         || checkSetLeft(map, x, y, 'C', spawnEq, spawnRand) == 1 || checkSetRight(map, x, y, 'C', spawnEq, spawnRand) == 1)){
            map->centerEntranceX = x;
            map->centerEntranceY = y;
            if (dir == 'x') {
                myWorld.player.playerX = x;
                myWorld.player.playerY = y;
                map->characterMap[myWorld.player.playerY][myWorld.player.playerX] = '@';
                dir = 'X';
            }
            break;
        }
    }
    while(1){
        int i = rand() % (76 + 1 - 1) + 1;
        int j = rand() % (17 + 1 - 1) + 1;
        spawnRand = ((float) rand() / RAND_MAX);
        spawnRand *= 100;
        if (map->singleMap[j][i] == '#' && (checkSetDown(map, i, j, 'M', spawnEq, spawnRand) == 1 || checkSetUp(map, i, j, 'M', spawnEq, spawnRand) == 1
            || checkSetLeft(map, i, j, 'M', spawnEq, spawnRand) == 1 || checkSetRight(map, i, j, 'M', spawnEq, spawnRand) == 1)){
            break;
        }
    }

    //player location on map
    while(1){
        if (dir == 'n'){
            myWorld.player.playerX = myWorld.worldMap[worldY][worldX]->roadSouthX;
            myWorld.player.playerY = 19;
            map->characterMap[myWorld.player.playerY][myWorld.player.playerX] = '@';
            break;
        }
        else if (dir == 'e'){
            myWorld.player.playerX = 1;
            myWorld.player.playerY = myWorld.worldMap[worldY][worldX]->roadWestY;
            map->characterMap[myWorld.player.playerY][myWorld.player.playerX] = '@';
            break;
        }
        else if (dir == 's'){
            myWorld.player.playerX = myWorld.worldMap[worldY][worldX]->roadNorthX;
            myWorld.player.playerY = 1;
            map->characterMap[myWorld.player.playerY][myWorld.player.playerX] = '@';
            break;
        }
        else if (dir == 'w'){
            myWorld.player.playerX = 78;
            myWorld.player.playerY = myWorld.worldMap[worldY][worldX]->roadEastY;
            map->characterMap[myWorld.player.playerY][myWorld.player.playerX] = '@';
            break;
        }
        else if (dir == 'X'){
            break;
        }
        else {
            int tempX = rand() % (78 + 1 - 1) + 1;
            int tempY = rand() % (19 + 1 - 1) + 1;
            if (map->singleMap[tempY][tempX] == '#'){
                myWorld.player.playerX = tempX;
                myWorld.player.playerY = tempY;
                map->characterMap[tempY][tempX] = '@';
                break;
            }
        }
    }
    printMap(*map);
}


/**
 * Goes thru world array and frees every index
*/
void freeHomies(){
    for (int i = 0; i < 401; i++){
        for (int j = 0; j < 401; j++){
            if (myWorld.worldMap[i][j] != NULL){
                free(myWorld.worldMap[i][j]);
            }
        }
    }
}

/**
 * Method used to generate the cost maps for the hiker and rival dependent upon character passed in
 * Can also print it out, but that is currently commented out
*/
void generateCostMap(map_t *map, char c){
    heap_t h;
    heap_init(&h);
    //keeps id on nodes
    int idIncrementer = 0;
    heapNode_t* defaultMap[21][80];
    for (int i = 0; i < 21; i++){
        for (int j = 0; j < 80; j++){
            //creates the node in the map directly
            if (c == 'H'){
                myWorld.hikerMap[i][j] = -1;
            }
            else {
                myWorld.rivalMap[i][j] = -1;
            }
            defaultMap[i][j] = (heapNode_t *) malloc (sizeof (heapNode_t));
            defaultMap[i][j]->mapX = j;
            defaultMap[i][j]->mapY = i;
            defaultMap[i][j]->id = idIncrementer++;
            defaultMap[i][j]->symbol = map->singleMap[i][j];
            if (defaultMap[i][j]->symbol == '#'){
                defaultMap[i][j]->weight = 10;
            }
            else if (defaultMap[i][j]->symbol == '^'){
                defaultMap[i][j]->weight = INT_MAX;
            }
            else if (defaultMap[i][j]->symbol == '%'){
                defaultMap[i][j]->weight = INT_MAX;
            }
            else if (defaultMap[i][j]->symbol == 'M'){
                defaultMap[i][j]->weight = 50;
            }
            else if (defaultMap[i][j]->symbol == 'C'){
                defaultMap[i][j]->weight = 50;
            }
            else if (defaultMap[i][j]->symbol == ':'){
                if (c == 'H'){
                    defaultMap[i][j]->weight = 15;
                }
                else {
                    defaultMap[i][j]->weight = 20;
                }
            }
            else if (defaultMap[i][j]->symbol == '.'){
                defaultMap[i][j]->weight = 10;
            }
            else if (defaultMap[i][j]->symbol == '~'){
                defaultMap[i][j]->weight = INT_MAX;
            }
            //swimmer
            else if (defaultMap[i][j]->symbol == 'm'){
                defaultMap[i][j]->weight = INT_MAX;
            }
            //other trainers
            else {
                defaultMap[i][j]->weight = 10;
            }
            if (map->characterMap[i][j] != '@'){
                defaultMap[i][j]->totalDist = INT_MAX;
            }
            else {
                defaultMap[i][j]->totalDist = 0;
                defaultMap[i][j]->weight = 0;
                myWorld.player.playerY = i;
                myWorld.player.playerX = j;

            }
            if (defaultMap[i][j]->symbol != '%' && defaultMap[i][j]->symbol != '^'){
                heap_add(&h, *defaultMap[i][j]);
            }
        }
    }
    while (heap_isEmpty(&h) > 0){
        heapNode_t u = heap_pop(&h);
        for (int i = max(0, u.mapY - 1); i <= min(u.mapY + 1, 20); i++){
            for (int j = max(0, u.mapX - 1); j <= min(u.mapX + 1, 79); j++){
                //not self >:(
                if (i != u.mapY || j != u.mapX){
                heapNode_t *v = defaultMap[i][j];
                int testDist = u.totalDist + v->weight;
                //if checks in order: if weight is max aka unreachable, testDist<total is only update if its less than
                //the rest checks gates on the edges
                if (v->weight != INT_MAX && testDist < v->totalDist && testDist > -1 && 
                (v->mapX != 79 && v->mapX != 0 && v->mapY != 0 && v->mapY != 20)){
                    v->totalDist = testDist;
                    if (c == 'H'){
                        myWorld.hikerMap[v->mapY][v->mapX] = v->totalDist;
                    }
                    else {
                        myWorld.rivalMap[v->mapY][v->mapX] = v->totalDist;
                    }
                    int temploc;
                    for (int k = 0; k < 1680; k++){
                        if (h.heapArray[k].id == v->id){
                            temploc = k;
                            break;
                        }
                    }
                    h.heapArray[temploc] = *v;
                    heapifyUp(&h, temploc);
                }
                }
            }
        }
    }
}

int npcDefeated(map_t *m, char c, int y, int x){
    switch(c) {
        case 'h':
            return m->trainers.hikerDef;
        case 'r':
            return m->trainers.rivalDef;
        case 'm':
            if (y == m->trainers.swim1Y && x == m->trainers.swim1X){
                return m->trainers.swim1Def;
            }
            return m->trainers.swim2Def;
        case 'w':
            return m->trainers.wand1Def;
        case 's':
            if (y == m->trainers.sentry1Y && x == m->trainers.sentry1X){
                return m->trainers.sentry1Def;
            }
            return m->trainers.sentry2Def;
        case 'p':
            if (y == m->trainers.pace1Y && x == m->trainers.pace1X){
                return m->trainers.pace1Def;
            }
            return m->trainers.pace2Def;
        case 'e':
            return m->trainers.exp1Def;
    }
    return 0;
}

void npcKill(map_t *m, char c, int y, int x){
    switch(c) {
        case 'h':
            m->trainers.hikerDef = 1;
            break;
        case 'r':
            m->trainers.rivalDef = 1;
            break;
        case 'm':
            if (y == m->trainers.swim1Y && x == m->trainers.swim1X){
                m->trainers.swim1Def = 1;
                break;
            }
            m->trainers.swim2Def = 1;
            break;
        case 'w':
            m->trainers.wand1Def = 1;
            break;
        case 's':
            if (y == m->trainers.sentry1Y && x == m->trainers.sentry1X){
                m->trainers.sentry1Def = 1;
                break;
            }
            m->trainers.sentry2Def = 1;
            break;
        case 'p':
            if (y == m->trainers.pace1Y && x == m->trainers.pace1X){
                m->trainers.pace1Def = 1;
                break;
            }
            m->trainers.pace2Def = 1;
            break;
        case 'e':
            m->trainers.exp1Def = 1;
            break;
    }
}

WINDOW *create_newwin(int x, int y)
{	WINDOW *local_win;

	local_win = newwin(y, x, 0, 0);
	box(local_win, 0 , 0);			 
	wrefresh(local_win);

	return local_win;
}

/**
 * Method takes information that was in the save and uses it to finish building the pokemon to what it was at save time
*/
void pokeLoadFinisher(actualPokemon_t *poke) {
    int loopCounter = 0;
    //pokemon
    poke->pokemon = allPokeInfo.pokemon[poke->pokemonSpecies.dexNum];
    //pokemon species
    poke->pokemonSpecies = allPokeInfo.pokemonSpecies[poke->pokemon.speciesID - 1];
    //experience
    poke->experience.experience = allPokeInfo.experience[((poke->pokemonSpecies.growthRateID - 1) * 100) + poke->experience.level - 1].experience;
    poke->experience.growthRateID = allPokeInfo.experience[((poke->pokemonSpecies.growthRateID - 1) * 100) + poke->experience.level - 1].growthRateID;
    //pokemon types
    std::vector<pokemonType_t>::iterator pi;
    for (pi = allPokeInfo.pokemonTypes.begin(); pi != allPokeInfo.pokemonTypes.end(); pi++){
        if (pi->pokemonID == poke->pokemon.dexNum){
            loopCounter++;
            poke->pokemonTypes.push_back(*pi);
        }
        if (loopCounter == 2){
            break;
        }
    }
    //type names
    if (poke->pokemonTypes.size() == 1){
        poke->typeNames.push_back(allPokeInfo.typeNames[poke->pokemonTypes[0].typeID - 1]);
    }
    else {
        poke->typeNames.push_back(allPokeInfo.typeNames[poke->pokemonTypes[0].typeID - 1]);
        poke->typeNames.push_back(allPokeInfo.typeNames[poke->pokemonTypes[1].typeID - 1]);
    }
    //pokemon moves, may be sus
    for (int i = 0; i < poke->pokemonMoves.size(); i++){
        poke->pokemonMoves.push_back(allPokeInfo.pokemonMoves[poke->pokemonMoves[i].moveID - 1]);
    }
    //moves
    for (int i = 0; i < poke->pokemonMoves.size(); i++){
        poke->moves.push_back(allPokeInfo.moves[poke->pokemonMoves[i].moveID - 1]);
    }
    //pokemon stats currently just adding ivs to base stats, not keeping seperate field
    std::vector<pokemonStats_t>::iterator st;
    for (st = allPokeInfo.pokemonStats.begin(); st != allPokeInfo.pokemonStats.end(); st++){
        if (st->pokemonID == poke->pokemon.dexNum){
            st->baseStat += rand() % 16;
            poke->pokemonStats.push_back(*st);
        }
        if (st->pokemonID > poke->pokemon.dexNum){
            break;
        }
    }
    //stats
    poke->stats.push_back(((poke->pokemonStats[0].baseStat * 2 * poke->experience.level) / 100) + poke->experience.level + 10);
    for (int i = 1; i < 6; i++){
        poke->stats.push_back(((poke->pokemonStats[i].baseStat * 2 * poke->experience.level) / 100) + 5);
    }
    //extra info already set

    //evolution info and same actual pokemon line check
    bool assigned = false;
    for (int i = 0; i < allPokeInfo.evolutionInfo.size(); i++){
        if (poke->pokemon.dexNum + 1 == allPokeInfo.evolutionInfo[i].evoDexNum && poke->pokemonSpecies.evolveChainID == allPokeInfo.pokemonSpecies[allPokeInfo.evolutionInfo[i].evoDexNum - 1].evolveChainID){
            poke->evolutionInfo = allPokeInfo.evolutionInfo[i];
            assigned = true;
            break;
        }
    }
    //means pokemon doesn't evolve, so assign it to some poke that doesn't evolve
    if (!assigned){
        poke->evolutionInfo = allPokeInfo.evolutionInfo[40];
    }
}

void tallGrassEncounter(map_t *m, actualPokemon_t *poke, int worldX, int worldY, bool starter){
    int loopCounter = 0;
    //temp 898 because long name formatting is hard
    int random;
    if (!starter){
        random = rand() % (898);
    }
    else {
        int startArr[] = {0, 3, 6, 151, 154, 157, 251, 254, 257, 386, 389, 392, 494, 497, 500, 649, 652, 655, 721, 724, 727, 809, 812, 815};
        random = startArr[rand() % 24];
    }
    int manDist = abs(worldX - 200) + abs(worldY - 200);
    if (manDist == 0 || manDist == 1) manDist = 2;
    if (manDist <= 200){
        poke->experience.level = rand() % ((manDist / 2) + 1 - 1) + 1;
    }
    else {
        poke->experience.level = rand() % (100 + 1 - ((manDist - 200) / 2)) + ((manDist - 200) / 2);
    }
    if (starter){
        poke->experience.level = 5;
    }
    //pokemon
    poke->pokemon = allPokeInfo.pokemon[random];
    //pokemon species
    poke->pokemonSpecies = allPokeInfo.pokemonSpecies[poke->pokemon.speciesID - 1];
    //experience
    poke->experience.experience = allPokeInfo.experience[((poke->pokemonSpecies.growthRateID - 1) * 100) + poke->experience.level - 1].experience;
    poke->experience.growthRateID = allPokeInfo.experience[((poke->pokemonSpecies.growthRateID - 1) * 100) + poke->experience.level - 1].growthRateID;
    //pokemon types
    std::vector<pokemonType_t>::iterator pi;
    for (pi = allPokeInfo.pokemonTypes.begin(); pi != allPokeInfo.pokemonTypes.end(); pi++){
        if (pi->pokemonID == poke->pokemon.dexNum){
            loopCounter++;
            poke->pokemonTypes.push_back(*pi);
        }
        if (loopCounter == 2){
            break;
        }
    }
    //type names
    if (poke->pokemonTypes.size() == 1){
        poke->typeNames.push_back(allPokeInfo.typeNames[poke->pokemonTypes[0].typeID - 1]);
    }
    else {
        poke->typeNames.push_back(allPokeInfo.typeNames[poke->pokemonTypes[0].typeID - 1]);
        poke->typeNames.push_back(allPokeInfo.typeNames[poke->pokemonTypes[1].typeID - 1]);
    }
    //very VERY slow moveset FOR WILD POKEMON (only shows moves learned my level up)
    //pokemon moves
    GETMOREMOVES:
    std::vector<pokemonMoves_t> possibleMoves;
    std::vector<pokemonMoves_t>::iterator mv;
    std::vector<int> seenMoves;
    bool firstMove = false;
    int indexCounter = 0;
    for (mv = allPokeInfo.pokemonMoves.begin(); mv != allPokeInfo.pokemonMoves.end(); mv++){
        if (poke->pokemon.dexNum >= 10001 && mv->pokemonID < 898){
            mv += 486983;
        }
        if (mv->pokemonID == poke->pokemon.dexNum && mv->pokeMoveMethodID == 1 && poke->experience.level >= mv->level){
            bool alreadyAdded = false;
            for (int i = 0; i < seenMoves.size(); i++){
                if (mv->moveID == seenMoves[i]){
                    alreadyAdded = true;
                }
            }
            if (!alreadyAdded){
                possibleMoves.push_back(*mv);
                seenMoves.push_back(mv->moveID);
                if (!firstMove){
                    firstMove = true;
                    poke->learnMoveIndex = indexCounter;
                }
            } 
        }
        if (mv->pokemonID > poke->pokemon.dexNum){
            break;
        }
        indexCounter++;
    }
    //if they havent learned any more moves by 15, chances are they never will
    //forcibly gives tackle 
    if (possibleMoves.size() < 1){
        if (poke->experience.level >= 15){
            possibleMoves.push_back(allPokeInfo.pokemonMoves[3]);
        }
        poke->experience.level += 3;
        poke->experience.level += 3;
        goto GETMOREMOVES;
    }
    int it1 = 0;
    poke->pokemonMoves.push_back(possibleMoves[rand() % (possibleMoves.size() - 1 + 1)]);
    if (possibleMoves.size() > 1) {
        poke->pokemonMoves.push_back(possibleMoves[rand() % (possibleMoves.size() - 1 + 1)]);
        //if it manages to random the same move 3 times, fuck it, bro gets two of the same move
        while (poke->pokemonMoves[0].moveID == poke->pokemonMoves[1].moveID){
            poke->pokemonMoves.pop_back();
            poke->pokemonMoves.push_back(possibleMoves[(rand() + it1) % (possibleMoves.size() - 1 + 1)]);
            it1++;
        }
    }
    if ((rand() % 100) < 80 && possibleMoves.size() > 3){
        it1 = 0;
        poke->pokemonMoves.push_back(possibleMoves[rand() % (possibleMoves.size() - 1 + 1)]);
        while (poke->pokemonMoves[2].moveID == poke->pokemonMoves[0].moveID || poke->pokemonMoves[2].moveID == poke->pokemonMoves[1].moveID){
            poke->pokemonMoves.pop_back();
            poke->pokemonMoves.push_back(possibleMoves[(rand() + it1) % (possibleMoves.size() - 1 + 1)]);
            it1++;
        }
        if ((rand() % 100) < 40){
            it1 = 0;
            poke->pokemonMoves.push_back(possibleMoves[rand() % (possibleMoves.size() - 1 + 1)]);
            while (poke->pokemonMoves[3].moveID == poke->pokemonMoves[0].moveID || poke->pokemonMoves[3].moveID == poke->pokemonMoves[1].moveID || poke->pokemonMoves[3].moveID == poke->pokemonMoves[2].moveID){
                poke->pokemonMoves.pop_back();
                poke->pokemonMoves.push_back(possibleMoves[(rand() + it1) % (possibleMoves.size() - 1 + 1)]);
                it1++;
            }
        }
    }
    
    //moves
    for (int i = 0; i < poke->pokemonMoves.size(); i++){
        poke->moves.push_back(allPokeInfo.moves[poke->pokemonMoves[i].moveID - 1]);
    }
    //pokemon stats currently just adding ivs to base stats, not keeping seperate field
    std::vector<pokemonStats_t>::iterator st;
    for (st = allPokeInfo.pokemonStats.begin(); st != allPokeInfo.pokemonStats.end(); st++){
        if (st->pokemonID == poke->pokemon.dexNum){
            st->baseStat+= rand() % 16;
            poke->pokemonStats.push_back(*st);
        }
        if (st->pokemonID > poke->pokemon.dexNum){
            break;
        }
    }
    //stats
    poke->stats.push_back(((poke->pokemonStats[0].baseStat * 2 * poke->experience.level) / 100) + poke->experience.level + 10);
    for (int i = 1; i < 6; i++){
        poke->stats.push_back(((poke->pokemonStats[i].baseStat * 2 * poke->experience.level) / 100) + 5);
    }
    //extra info
    poke->extraInfo.currentHP = poke->stats[0];
    for (int i = 0; i < poke->pokemonMoves.size(); i++){
        poke->extraInfo.ppLeft.push_back(poke->moves[i].pp);
    }
    poke->uid = rand();
    poke->extraInfo.curXp = allPokeInfo.experience[poke->experience.level - 1].experience;
    poke->extraInfo.curXpIndex = poke->experience.level - 1;

    //evolution info and same actual pokemon line check
    bool assigned = false;
    for (int i = 0; i < allPokeInfo.evolutionInfo.size(); i++){
        if (poke->pokemon.dexNum + 1 == allPokeInfo.evolutionInfo[i].evoDexNum && poke->pokemonSpecies.evolveChainID == allPokeInfo.pokemonSpecies[allPokeInfo.evolutionInfo[i].evoDexNum - 1].evolveChainID){
            poke->evolutionInfo = allPokeInfo.evolutionInfo[i];
            assigned = true;
            break;
        }
    }
    //means pokemon doesn't evolve, so assign it to some poke that doesn't evolve
    if (!assigned){
        poke->evolutionInfo = allPokeInfo.evolutionInfo[40];
    }
    
     
}

bool teamAliveCheck(){
    for (int i = 0; i < myWorld.player.pokemon.size(); i++){
        if (myWorld.player.pokemon[i].extraInfo.currentHP > 0){
            return true;
        }
    }
    return false;
}

int pokeSwap(bool mustSwap, WINDOW *bottom, int curPlayerPoke){
    BATTLESWAP:
        wclear(bottom);
        box(bottom, 0, 0);
        mvwprintw(bottom, 1, 1, "Who should swap in? (1, 2, 3...)");
        mvwprintw(bottom, 2, 1, "Pokemon:");
        mvwprintw(bottom, 2, 45, "HP:");
        for (int i = 0; i < myWorld.player.pokemon.size(); i++){
            mvwprintw(bottom, i + 3, 1, "(%d) %s", i+1, myWorld.player.pokemon[i].pokemon.name.c_str());
            mvwprintw(bottom, i + 3, 45, "%d/%d", myWorld.player.pokemon[i].extraInfo.currentHP, myWorld.player.pokemon[i].stats[0]);
        }
        wrefresh(bottom);
        int temptInput = getch();
        while (temptInput != '1' && temptInput != '2' && temptInput != '3' && temptInput != '4' && temptInput != '5' && temptInput != '6' && temptInput != 27){
            temptInput = getch();
        }
    if (temptInput == '1'){
        if (myWorld.player.pokemon[curPlayerPoke].uid == myWorld.player.pokemon[0].uid){
            wclear(bottom);
            box(bottom, 0, 0);
            mvwprintw(bottom, 1, 1, "That pokemon is already battling! Press ESC");
            wrefresh(bottom);
            int goOn = getch();
            while (goOn != 27){
                goOn = getch();
            }
            goto BATTLESWAP;
        }
        else if (myWorld.player.pokemon[0].extraInfo.currentHP == 0){
            wclear(bottom);
            box(bottom, 0, 0);
            mvwprintw(bottom, 1, 1, "That pokemon has fainted! Press ESC");
            wrefresh(bottom);
            int goOn = getch();
            while (goOn != 27){
                goOn = getch();
            }
            goto BATTLESWAP;
        }
        else {
            return 0;
        }
    }
    else if (temptInput == '2'){
        if (myWorld.player.pokemon.size() < 2){
            wclear(bottom);
            box(bottom, 0, 0);
            mvwprintw(bottom, 1, 1, "Invalid Pokemon! Press ESC");
            wrefresh(bottom);
            int goOn = getch();
            while (goOn != 27){
                goOn = getch();
            }
            goto BATTLESWAP;
        }
        else if (myWorld.player.pokemon[curPlayerPoke].uid == myWorld.player.pokemon[1].uid){
            wclear(bottom);
            box(bottom, 0, 0);
            mvwprintw(bottom, 1, 1, "That pokemon is already battling! Press ESC");
            wrefresh(bottom);
            int goOn = getch();
            while (goOn != 27){
                goOn = getch();
            }
            goto BATTLESWAP;
        }
        else if (myWorld.player.pokemon[1].extraInfo.currentHP == 0){
            wclear(bottom);
            box(bottom, 0, 0);
            mvwprintw(bottom, 1, 1, "That pokemon has fainted! Press ESC");
            wrefresh(bottom);
            int goOn = getch();
            while (goOn != 27){
                goOn = getch();
            }
            goto BATTLESWAP;
        }
        else {
            return 1;
        }
    }
    else if (temptInput == '3'){
        if (myWorld.player.pokemon.size() < 3){
            wclear(bottom);
            box(bottom, 0, 0);
            mvwprintw(bottom, 1, 1, "Invalid Pokemon! Press ESC");
            wrefresh(bottom);
            int goOn = getch();
            while (goOn != 27){
                goOn = getch();
            }
            goto BATTLESWAP;
        }
        else if (myWorld.player.pokemon[curPlayerPoke].uid == myWorld.player.pokemon[2].uid){
            wclear(bottom);
            box(bottom, 0, 0);
            mvwprintw(bottom, 1, 1, "That pokemon is already battling! Press ESC");
            wrefresh(bottom);
            int goOn = getch();
            while (goOn != 27){
                goOn = getch();
            }
            goto BATTLESWAP;
        }
        else if (myWorld.player.pokemon[2].extraInfo.currentHP == 0){
            wclear(bottom);
            box(bottom, 0, 0);
            mvwprintw(bottom, 1, 1, "That pokemon has fainted! Press ESC");
            wrefresh(bottom);
            int goOn = getch();
            while (goOn != 27){
                goOn = getch();
            }
            goto BATTLESWAP;
        }
        else {
            return 2;
        }
    }
    else if (temptInput == '4'){
        if (myWorld.player.pokemon.size() < 4){
            wclear(bottom);
            box(bottom, 0, 0);
            mvwprintw(bottom, 1, 1, "Invalid Pokemon! Press ESC");
            wrefresh(bottom);
            int goOn = getch();
            while (goOn != 27){
                goOn = getch();
            }
            goto BATTLESWAP;
        }
        else if (myWorld.player.pokemon[curPlayerPoke].uid == myWorld.player.pokemon[3].uid){
            wclear(bottom);
            box(bottom, 0, 0);
            mvwprintw(bottom, 1, 1, "That pokemon is already battling! Press ESC");
            wrefresh(bottom);
            int goOn = getch();
            while (goOn != 27){
                goOn = getch();
            }
            goto BATTLESWAP;
        }
        else if (myWorld.player.pokemon[3].extraInfo.currentHP == 0){
            wclear(bottom);
            box(bottom, 0, 0);
            mvwprintw(bottom, 1, 1, "That pokemon has fainted! Press ESC");
            wrefresh(bottom);
            int goOn = getch();
            while (goOn != 27){
                goOn = getch();
            }
            goto BATTLESWAP;
        }
        else {
            return 3;
        }
    }
    else if (temptInput == '5'){
        if (myWorld.player.pokemon.size() < 5){
            wclear(bottom);
            box(bottom, 0, 0);
            mvwprintw(bottom, 1, 1, "Invalid Pokemon! Press ESC");
            wrefresh(bottom);
            int goOn = getch();
            while (goOn != 27){
                goOn = getch();
            }
            goto BATTLESWAP;
        }
        else if (myWorld.player.pokemon[curPlayerPoke].uid == myWorld.player.pokemon[4].uid){
            wclear(bottom);
            box(bottom, 0, 0);
            mvwprintw(bottom, 1, 1, "That pokemon is already battling! Press ESC");
            wrefresh(bottom);
            int goOn = getch();
            while (goOn != 27){
                goOn = getch();
            }
            goto BATTLESWAP;
        }
        else if (myWorld.player.pokemon[4].extraInfo.currentHP == 0){
            wclear(bottom);
            box(bottom, 0, 0);
            mvwprintw(bottom, 1, 1, "That pokemon has fainted! Press ESC");
            wrefresh(bottom);
            int goOn = getch();
            while (goOn != 27){
                goOn = getch();
            }
            goto BATTLESWAP;
        }
        else {
            return 4;
        }
    }
    else if (temptInput == '6'){
        if (myWorld.player.pokemon.size() < 6){
            wclear(bottom);
            box(bottom, 0, 0);
            mvwprintw(bottom, 1, 1, "Invalid Pokemon! Press ESC");
            wrefresh(bottom);
            int goOn = getch();
            while (goOn != 27){
                goOn = getch();
            }
            goto BATTLESWAP;
        }
        else if (myWorld.player.pokemon[curPlayerPoke].uid == myWorld.player.pokemon[5].uid){
            wclear(bottom);
            box(bottom, 0, 0);
            mvwprintw(bottom, 1, 1, "That pokemon is already battling! Press ESC");
            wrefresh(bottom);
            int goOn = getch();
            while (goOn != 27){
                goOn = getch();
            }
            goto BATTLESWAP;
        }
        else if (myWorld.player.pokemon[5].extraInfo.currentHP == 0){
            wclear(bottom);
            box(bottom, 0, 0);
            mvwprintw(bottom, 1, 1, "That pokemon has fainted! Press ESC");
            wrefresh(bottom);
            int goOn = getch();
            while (goOn != 27){
                goOn = getch();
            }
            goto BATTLESWAP;
        }
        else {
            return 5;
        }
    }
    else {
        if (!mustSwap){
            wclear(bottom);
            box(bottom, 0, 0);
            mvwprintw(bottom, 1, 1, "What will %s do? (1 to attack, 2 for bag, 3 to switch, 4 to run)", myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str());
            wrefresh(bottom);
            return curPlayerPoke + 10;
        }
        else {
            goto BATTLESWAP;
        }
        
    }
}

void visitPokeCenter(){
    for (int i = 0; i < myWorld.player.pokemon.size(); i++){
        myWorld.player.pokemon[i].extraInfo.currentHP = myWorld.player.pokemon[i].stats[0];
        for (int j = 0; j < myWorld.player.pokemon[i].moves.size(); j++){
            myWorld.player.pokemon[i].extraInfo.ppLeft[j] = myWorld.player.pokemon[i].moves[j].pp;
        }
    }
}

void whiteOut(){
    myWorld.worldMap[myWorld.player.worldY][myWorld.player.worldX]->characterMap[myWorld.player.playerY][myWorld.player.playerX] = 'X';
    myWorld.worldMap[myWorld.player.worldY][myWorld.player.worldX]->characterMap[myWorld.worldMap[myWorld.player.worldY][myWorld.player.worldX]->centerEntranceY][myWorld.worldMap[myWorld.player.worldY][myWorld.player.worldX]->centerEntranceX] = '@';
    myWorld.player.playerY = myWorld.worldMap[myWorld.player.worldY][myWorld.player.worldX]->centerEntranceY;
    myWorld.player.playerX = myWorld.worldMap[myWorld.player.worldY][myWorld.player.worldX]->centerEntranceX;
    visitPokeCenter();
    WINDOW *w = create_newwin(80, 24);
    mvwprintw(w, 1, 1, "You whited out and were sent to the pokemon center. Press Esc");
    wrefresh(w);
    int goOn = getch();
    while (goOn != 27){
        goOn = getch();
    }
    delwin(w);

}

void newMove(actualPokemon_t * poke, pokemonMoves_t m, WINDOW * top, WINDOW * bottom){
    moves_t move = allPokeInfo.moves[m.moveID - 1];
    if (poke->moves.size() < 4){
        poke->pokemonMoves.push_back(m);
        poke->moves.push_back(move);
        wclear(top);
        box(top, 0, 0);
        mvwprintw(top, 1, 1, "%s learned %s!", poke->pokemon.name.c_str(), move.name.c_str());
        mvwprintw(top, 2, 1, "Press Esc");
        wrefresh(top);
        int goOn = getch();
        while (goOn != 27){
            goOn = getch();
        }
        wclear(top);
        box(top, 0, 0);
        wrefresh(top);
        return;
    }
    wclear(top);
    box(top, 0, 0);
    mvwprintw(top, 1, 1, "%s would like to learn a %s. Would you like to replace a move?", poke->pokemon.name.c_str(), move.name.c_str());
    mvwprintw(top, 2, 1, "(1) Yes");
    mvwprintw(top, 3, 1, "(2) No");
    wrefresh(top);
    int choice = getch();
    while (choice != '1' && choice != '2'){
        choice = getch();
    }
    if (choice == '1'){
        wclear(top);
        box(top, 0, 0);
        wclear(bottom);
        box(bottom, 0, 0);
        mvwprintw(top, 1, 1, "What move would you like to replace with %s?", move.name.c_str());
        for (int i = 0; i < poke->moves.size(); i++){
            mvwprintw(bottom, i + 2, 1, "(%d) %s", i+1, poke->moves[i].name.c_str());
        }
        wrefresh(top);
        wrefresh(bottom);
        int replace = getch();
        while (replace - 48 < 0 || replace - 48 > poke->moves.size()){
            replace = getch();
        }
        poke->moves.erase(poke->moves.begin() + (replace - 49));
        poke->pokemonMoves.erase(poke->pokemonMoves.begin() + (replace - 49));
        poke->pokemonMoves.push_back(m);
        poke->moves.push_back(move);
        wclear(top);
        box(top, 0, 0);
        wclear(bottom);
        box(bottom, 0, 0);
        mvwprintw(top, 1, 1, "%s successfully learned %s!", poke->pokemon.name.c_str(), move.name.c_str());
        mvwprintw(top, 2, 1, "Press Esc");
        int goOn = getch();
        while (goOn != 27){
            goOn = getch();
        }
        wclear(top);
        wclear(bottom);
        box(top, 0, 0);
        box(bottom, 0, 0);
        wrefresh(top);
        wrefresh(bottom);
        return;
    }
    else {
        wclear(top);
        wclear(bottom);
        box(top, 0, 0);
        box(bottom, 0, 0);
        wrefresh(top);
        wrefresh(bottom);
        return;
    }

}

void levelUp(actualPokemon_t * poke, WINDOW * top, WINDOW * bottom){
    std::vector<pokemonMoves_t>::iterator mv;
    std::vector<pokemonMoves_t> foundMoves;
    bool alreadyFound = false;
    poke->experience.level++;
    poke->extraInfo.curXpIndex++;
    //tell it moves it already knows
    for (int i = 0; i < poke->pokemonMoves.size(); i++){
        foundMoves.push_back(poke->pokemonMoves[i]);
    }
    //update stats
    poke->stats[0] = (((poke->pokemonStats[0].baseStat * 2 * poke->experience.level) / 100) + poke->experience.level + 10);
    for (int i = 1; i < 6; i++){
        poke->stats[i] = (((poke->pokemonStats[i].baseStat * 2 * poke->experience.level) / 100) + 5);
    }
    for (mv = allPokeInfo.pokemonMoves.begin() + poke->learnMoveIndex; mv->pokemonID == poke->pokemon.dexNum; mv++){
        if (mv->level == poke->experience.level && mv->pokeMoveMethodID == 1){
            for(int i = 0; i < foundMoves.size(); i++){
                if (foundMoves[i].moveID == mv->moveID){
                    alreadyFound = true;
                }
            }
            if (!alreadyFound){
                newMove(poke, *mv, top, bottom);
                foundMoves.push_back(*mv);
                alreadyFound = false;
            }
        }
    }
}

void expGain(actualPokemon_t defeatedPoke, actualPokemon_t * winningPoke, bool trainerBattle, WINDOW * top, WINDOW * bottom){
    if (trainerBattle){
        winningPoke->extraInfo.curXp += (((defeatedPoke.pokemon.baseXP * defeatedPoke.experience.level) / 7) * 1.5);
    }
    else {
        winningPoke->extraInfo.curXp += ((defeatedPoke.pokemon.baseXP * defeatedPoke.experience.level) / 7);
    }
    while (winningPoke->extraInfo.curXpIndex < 100 && winningPoke->extraInfo.curXp > allPokeInfo.experience[winningPoke->extraInfo.curXpIndex].experience){
        levelUp(winningPoke, top, bottom);
    }
}
/**
 *         pokemon_t pokemon;
        std::vector<moves_t> moves;
        std::vector<pokemonMoves_t> pokemonMoves;
        pokemonSpecies_t pokemonSpecies;
        experience_t experience;
        std::vector<typeNames_t> typeNames;
        std::vector<pokemonStats_t> pokemonStats;
        std::vector<int> stats;
        std::vector<pokemonType_t> pokemonTypes;
        extraPokeInfo_t extraInfo;
        evolutionInfo_t evolutionInfo;
        int uid;
*/

void evolvePoke(actualPokemon_t * poke){
    int loopCounter = 0;
    //pokemon
    poke->pokemon = allPokeInfo.pokemon[poke->evolutionInfo.evoDexNum - 1];
    //pokemon species
    poke->pokemonSpecies = allPokeInfo.pokemonSpecies[poke->pokemon.speciesID - 1];
    //experience
    poke->experience.experience = allPokeInfo.experience[((poke->pokemonSpecies.growthRateID - 1) * 100) + poke->experience.level - 1].experience;
    poke->experience.growthRateID = allPokeInfo.experience[((poke->pokemonSpecies.growthRateID - 1) * 100) + poke->experience.level - 1].growthRateID;
    //poke types
    poke->pokemonTypes.clear();
    std::vector<pokemonType_t>::iterator pi;
    for (pi = allPokeInfo.pokemonTypes.begin(); pi != allPokeInfo.pokemonTypes.end(); pi++){
        if (pi->pokemonID == poke->pokemon.dexNum){
            loopCounter++;
            poke->pokemonTypes.push_back(*pi);
        }
        if (loopCounter == 2){
            break;
        }
    }
    //type names
    poke->typeNames.clear();
    if (poke->pokemonTypes.size() == 1){
        poke->typeNames.push_back(allPokeInfo.typeNames[poke->pokemonTypes[0].typeID - 1]);
    }
    else {
        poke->typeNames.push_back(allPokeInfo.typeNames[poke->pokemonTypes[0].typeID - 1]);
        poke->typeNames.push_back(allPokeInfo.typeNames[poke->pokemonTypes[1].typeID - 1]);
    }
    //baseStats
    poke->pokemonStats.clear();
    std::vector<pokemonStats_t>::iterator st;
    for (st = allPokeInfo.pokemonStats.begin(); st != allPokeInfo.pokemonStats.end(); st++){
        if (st->pokemonID == poke->pokemon.dexNum){
            st->baseStat+= rand() % 16;
            poke->pokemonStats.push_back(*st);
        }
        if (st->pokemonID > poke->pokemon.dexNum){
            break;
        }
    }
    //stats
    poke->stats.clear();
    poke->stats.push_back(((poke->pokemonStats[0].baseStat * 2 * poke->experience.level) / 100) + poke->experience.level + 10);
    for (int i = 1; i < 6; i++){
        poke->stats.push_back(((poke->pokemonStats[i].baseStat * 2 * poke->experience.level) / 100) + 5);
    }
    //extra info
    poke->extraInfo.ppLeft.clear();
    poke->extraInfo.currentHP = poke->stats[0];
    for (int i = 0; i < poke->pokemonMoves.size(); i++){
        poke->extraInfo.ppLeft.push_back(poke->moves[i].pp);
    }
    poke->extraInfo.curXp = allPokeInfo.experience[poke->experience.level - 1].experience;
    poke->extraInfo.curXpIndex = poke->experience.level - 1;
    //evolution info and same actual pokemon line check
    bool assigned = false;
    for (int i = 0; i < allPokeInfo.evolutionInfo.size(); i++){
        if (poke->pokemon.dexNum + 1 == allPokeInfo.evolutionInfo[i].evoDexNum && poke->pokemonSpecies.evolveChainID == allPokeInfo.pokemonSpecies[allPokeInfo.evolutionInfo[i].evoDexNum - 1].evolveChainID){
            poke->evolutionInfo = allPokeInfo.evolutionInfo[i];
            assigned = true;
            break;
        }
    }
    //means pokemon doesn't evolve, so assign it to some poke that doesn't evolve
    if (!assigned){
        poke->evolutionInfo = allPokeInfo.evolutionInfo[40];
    }
}

/**
 * checks if move used has stab, returns stab = 1.5 if it does else stab = 1 for damageCalc equation
*/
double stabCheck(actualPokemon_t poke, moves_t move){
    if (poke.pokemonTypes.size() > 1){
        return ((double) max(((int) (poke.pokemonTypes[0].typeID == move.typeID || poke.pokemonTypes[1].typeID == move.typeID)) * 1.5, 1));
    }
    return ((double) max(((int) (poke.pokemonTypes[0].typeID == move.typeID)) * 1.5, 1));
}

//for p1 attacking p2, 2 is physical, 1 is non-attacking, 3 is special for damage_class, type id is to match types
int damageCalc(actualPokemon_t p1, actualPokemon_t p2, moves_t move, double * crit, double * type){
    double stab = stabCheck(p1, move);
    double random = ((rand() % 16) + 85) / 100.001;
    //implement later
    *type = typeChart.typeChart[move.typeID - 1][p2.pokemonTypes[0].typeID - 1];
    if (p2.pokemonTypes.size() > 1){
        *type = *type * (typeChart.typeChart[move.typeID - 1][p2.pokemonTypes[1].typeID - 1]);
    }
    *crit = 1.0;
    int critRand = rand() % 256;
    if (critRand < (p1.pokemonStats[5].baseStat / 2)){
        *crit = 1.5;
    }

    if (move.typeID == p1.pokemonTypes[0].typeID)
    {
        stab = 1.5;
    }
    else if (p1.pokemonTypes.size() > 1 && p1.pokemonTypes[1].typeID == move.typeID){
        stab = 1.5;
    }
    //dragon rage dealing max damage is funny
    if (move.dmgClassID == 2){
        if (move.power == INT_MAX){ move.power = 40; }
        return ((((((2 * p1.experience.level) / 5) + 2) * move.power * (((double) p1.stats[1]) / ((double) p2.stats[2]))) / 50) + 2) * *crit * random * stab * *type;
    }
    else if(move.dmgClassID == 3){
        if (move.power == INT_MAX){ move.power = 40; }
        return ((((((2 * p1.experience.level) / 5) + 2) * move.power * (((double) p1.stats[3]) / ((double) p2.stats[4]))) / 50) + 2) * *crit * random * stab * *type;
    }
    //idk how we are doing status moves
    else {
        return 0;
    }
}

/**
 * Method where battling actually takes place. Called for wild battles and trainer battles, encapsulates all functionality of battling
 * makes calls to outside functions like bag, attack, etc
*/
void battleStart(std::vector<actualPokemon_t> trainerTeam, bool trainerBattle){
    WINDOW *top = newwin(10, 78, 1, 1);
    WINDOW *bottom = newwin(12, 78, 11, 1);
    box(top, 0, 0);
    box(bottom, 0, 0);
    wrefresh(top);
    wrefresh(bottom);
    int npcMove = 0;
    int trainerMove = 0;
    int curTrainerPoke = 0;
    int curPlayerPoke = -1;
    bool trainerOnlyMove = false;
    moves_t actualTrainerMove;
    moves_t actualPlayerMove;
    bool battleFinished = false;
    for (int i = 0; i < myWorld.player.pokemon.size(); i++){
        if (myWorld.player.pokemon[i].extraInfo.currentHP > 0){
            curPlayerPoke = i;
            break;
        }
    }
    if (curPlayerPoke == -1){
        mvwprintw(top, 1, 1, "All your pokemon are fainted! Press Esc");
        int goOn = getch();
        while (goOn != 27){
            goOn = getch();
        }
        delwin(top);
        delwin(bottom);
        whiteOut();
        return;
    }

    if (trainerBattle){
        mvwprintw(top, 1, 1, "Opposing trainer threw out level %d %s!", trainerTeam[0].experience.level, trainerTeam[0].pokemon.name.c_str());
    }
    else {
        mvwprintw(top, 1, 1, "A wild level %d %s appeared!", trainerTeam[0].experience.level, trainerTeam[0].pokemon.name.c_str());
    }
    mvwprintw(top, 2, 1, "You threw out level %d %s!", myWorld.player.pokemon[curPlayerPoke].experience.level, myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str());
    mvwprintw(top, 3, 1, "What will %s do? (1 to attack, 2 for bag, 3 to switch, 4 to run)", myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str());
    wrefresh(top);
    while (!battleFinished){
        STARTBATTLE:
        trainerMove = rand() % trainerTeam[curTrainerPoke].moves.size();
        actualTrainerMove = trainerTeam[curTrainerPoke].moves[trainerMove];
        npcMove = getch();
        while (npcMove != '1' && npcMove != '2' && npcMove != '3' && npcMove != '4'){
            npcMove = getch();
        }
        if (npcMove == '1'){
            CHOOSEMOVE:
            wclear(bottom);
            box(bottom, 0, 0);
            mvwprintw(bottom, 1, 1, "Choose a move");
            mvwprintw(bottom, 2, 1, "%s  HP: %d/%d", myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str(), myWorld.player.pokemon[curPlayerPoke].extraInfo.currentHP, myWorld.player.pokemon[curPlayerPoke].stats[0]);
            for (int i = 0; i < myWorld.player.pokemon[curPlayerPoke].moves.size(); i++){
                mvwprintw(bottom, i + 3, 1, "(%d) %s", i+1, myWorld.player.pokemon[curPlayerPoke].moves[i].name.c_str());
            }
            wrefresh(bottom);
            npcMove = getch();
            wclear(bottom);
            box(bottom, 0, 0);
            mvwprintw(bottom, 1, 1, "%s  HP: %d/%d", myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str(), myWorld.player.pokemon[curPlayerPoke].extraInfo.currentHP, myWorld.player.pokemon[curPlayerPoke].stats[0]);
            wrefresh(bottom);
            while (npcMove != '1' && npcMove != '2' && npcMove != '3' && npcMove != '4' && npcMove != 27){
                npcMove = getch();
            }
            if (npcMove == '1'){
                actualPlayerMove = myWorld.player.pokemon[curPlayerPoke].moves[0];
            }
            else if (npcMove == '2'){
                actualPlayerMove = myWorld.player.pokemon[curPlayerPoke].moves[1];
            }
            else if (npcMove == '3'){
                if (myWorld.player.pokemon[curPlayerPoke].moves.size() > 2){
                    actualPlayerMove = myWorld.player.pokemon[curPlayerPoke].moves[2];
                }
                else {
                    goto CHOOSEMOVE;
                }
            }
            else if (npcMove == '4'){
                if (myWorld.player.pokemon[curPlayerPoke].moves.size() > 3){
                    actualPlayerMove = myWorld.player.pokemon[curPlayerPoke].moves[3];
                }
                else {
                    goto CHOOSEMOVE;
                }
            }
            else {
                wclear(bottom);
                box(bottom, 0, 0);
                mvwprintw(bottom, 1, 1, "Level (%d) %s  HP: %d/%d", myWorld.player.pokemon[curPlayerPoke].experience.level, myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str(), myWorld.player.pokemon[curPlayerPoke].extraInfo.currentHP, myWorld.player.pokemon[curPlayerPoke].stats[0]);
                wrefresh(bottom);
                wclear(top);
                box(top, 0, 0);
                mvwprintw(top, 1, 1, "What will %s do? (1 to attack, 2 for bag, 3 to switch, 4 to run)", myWorld.player.pokemon[0].pokemon.name.c_str());
                mvwprintw(top, 2, 1, "Level (%d) %s  HP: %d/%d", trainerTeam[curTrainerPoke].experience.level, trainerTeam[curTrainerPoke].pokemon.name.c_str(), trainerTeam[curTrainerPoke].extraInfo.currentHP, trainerTeam[curTrainerPoke].stats[0]);
                wrefresh(top);
                goto STARTBATTLE;
            }
            TRAINERONLYMOVE:
            wclear(top);
            box(top, 0, 0);
            wrefresh(top);
            double * crit = (double *) malloc(sizeof (double));
            *crit = 1.0;
            double * type = (double *) malloc(sizeof (double));
            *type = 1.0;
            bool missed = ((rand() % 100) < actualPlayerMove.accuracy);
            int damageDealt;
            if (trainerOnlyMove){
                goto TRAINERONLYMOVE2;
            }
            //player move
            if (actualPlayerMove.priority > actualTrainerMove.priority || myWorld.player.pokemon[curPlayerPoke].stats[5] > trainerTeam[curTrainerPoke].stats[5]){
                damageDealt = damageCalc(myWorld.player.pokemon[curPlayerPoke], trainerTeam[curTrainerPoke], actualPlayerMove, crit, type) * int(missed);
                trainerTeam[curTrainerPoke].extraInfo.currentHP -= damageDealt;
                if (!missed){
                    mvwprintw(top, 1, 1, "%s tried to attack but missed! Press ESC", myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str());
                }
                else if (*crit == 1.5){
                    mvwprintw(top, 1, 1, "%s used %s and crit %s dealing %d damage! Press ESC", myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str(), actualPlayerMove.name.c_str(), trainerTeam[curTrainerPoke].pokemon.name.c_str(), damageDealt);
                }
                else {
                    mvwprintw(top, 1, 1, "%s used %s on %s dealing %d damage! Press ESC", myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str(), actualPlayerMove.name.c_str(), trainerTeam[curTrainerPoke].pokemon.name.c_str(), damageDealt);
                }

                if (*type > 1 && damageDealt > 0){
                    mvwprintw(top, 2, 1, "It was super-effective!");
                }
                else if (*type < 1 && damageDealt > 0){
                    mvwprintw(top, 2, 1, "It was not very effective!");
                }
                wrefresh(top);
                if (trainerTeam[curTrainerPoke].extraInfo.currentHP <= 0 && curTrainerPoke + 1 < trainerTeam.size()){
                    if (*type > 1 || *type < 1 && damageDealt > 0){
                        mvwprintw(top, 3, 1, "The opposing %s fainted!", trainerTeam[curTrainerPoke].pokemon.name.c_str());
                        mvwprintw(top, 4, 1, "Your %s gained %d xp!", myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str(), int(((trainerTeam[curTrainerPoke].pokemon.baseXP * trainerTeam[curTrainerPoke].experience.level) / 7) * 1.5));
                        curTrainerPoke += 1;
                        mvwprintw(top, 5, 1, "The opposing trainer swaped in a level %d %s!", trainerTeam[curTrainerPoke].experience.level, trainerTeam[curTrainerPoke].pokemon.name.c_str());
                        mvwprintw(top, 6, 1, "Press ESC");
                    }
                    else {
                        mvwprintw(top, 2, 1, "The opposing %s fainted!", trainerTeam[curTrainerPoke].pokemon.name.c_str());
                        mvwprintw(top, 4, 1, "Your %s gained %d xp!", myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str(), int(((trainerTeam[curTrainerPoke].pokemon.baseXP * trainerTeam[curTrainerPoke].experience.level) / 7) * 1.5));
                        curTrainerPoke += 1;
                        mvwprintw(top, 5, 1, "The opposing trainer swaped in a level %d %s!", trainerTeam[curTrainerPoke].experience.level, trainerTeam[curTrainerPoke].pokemon.name.c_str());
                        mvwprintw(top, 6, 1, "Press ESC");
                    }

                    wrefresh(top);
                    int goOn = getch();
                    while (goOn != 27){
                        goOn = getch();
                    }
                    expGain(trainerTeam[curTrainerPoke], &myWorld.player.pokemon[curPlayerPoke], trainerBattle, top, bottom);
                    wclear(bottom);
                    box(bottom, 0, 0);
                    mvwprintw(bottom, 1, 1, "Level (%d) %s  HP: %d/%d", myWorld.player.pokemon[curPlayerPoke].experience.level, myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str(), myWorld.player.pokemon[curPlayerPoke].extraInfo.currentHP, myWorld.player.pokemon[curPlayerPoke].stats[0]);
                    wrefresh(bottom);
                    wclear(top);
                    box(top, 0, 0);
                    mvwprintw(top, 1, 1, "What will %s do? (1 to attack, 2 for bag, 3 to switch, 4 to run)", myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str());
                    mvwprintw(top, 2, 1, "Level (%d) %s  HP: %d/%d", trainerTeam[curTrainerPoke].experience.level, trainerTeam[curTrainerPoke].pokemon.name.c_str(), trainerTeam[curTrainerPoke].extraInfo.currentHP, trainerTeam[curTrainerPoke].stats[0]);
                    wrefresh(top);
                    goto STARTBATTLE;
                }
                else if (trainerTeam[curTrainerPoke].extraInfo.currentHP <= 0 && curTrainerPoke + 1 >= trainerTeam.size()){
                    if (*type > 1 || *type < 1 && damageDealt > 0){
                        mvwprintw(top, 3, 1, "The opposing %s fainted!", trainerTeam[curTrainerPoke].pokemon.name.c_str());
                        if (trainerBattle){
                            mvwprintw(top, 4, 1, "Your %s gained %d xp!", myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str(), int(((trainerTeam[curTrainerPoke].pokemon.baseXP * trainerTeam[curTrainerPoke].experience.level) / 7) * 1.5));
                            mvwprintw(top, 5, 1, "The opposing trainer has no more pokemon left, you win!");
                            mvwprintw(top, 6, 1, "The trainer paid out $%d!", (30 * trainerTeam[0].experience.level));
                            myWorld.player.money += (30 * trainerTeam[0].experience.level);
                        }
                        else {
                            mvwprintw(top, 4, 1, "Your %s gained %d xp!", myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str(), int(((trainerTeam[curTrainerPoke].pokemon.baseXP * trainerTeam[curTrainerPoke].experience.level) / 7)));
                        }
                        mvwprintw(top, 7, 1, "Press ESC");
                    }
                    else {
                        mvwprintw(top, 2, 1, "The opposing %s fainted!", trainerTeam[curTrainerPoke].pokemon.name.c_str());
                        if (trainerBattle){
                            mvwprintw(top, 3, 1, "Your %s gained %d xp!", myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str(), int(((trainerTeam[curTrainerPoke].pokemon.baseXP * trainerTeam[curTrainerPoke].experience.level) / 7) * 1.5));
                            mvwprintw(top, 4, 1, "The opposing trainer has no more pokemon left, you win!");
                            mvwprintw(top, 5, 1, "The trainer paid out $%d!", (30 * trainerTeam[0].experience.level));
                            myWorld.player.money += (30 * trainerTeam[0].experience.level);
                        }
                        else {
                            mvwprintw(top, 4, 1, "Your %s gained %d xp!", myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str(), int(((trainerTeam[curTrainerPoke].pokemon.baseXP * trainerTeam[curTrainerPoke].experience.level) / 7)));
                        }
                        mvwprintw(top, 6, 1, "Press ESC");
                    }
                    wrefresh(top);
                    int goOn = getch();
                    while (goOn != 27){
                        goOn = getch();
                    }
                    expGain(trainerTeam[curTrainerPoke], &myWorld.player.pokemon[curPlayerPoke], trainerBattle, top, bottom);
                    break;
                }
                //trainer move
                else {
                    TRAINERONLYMOVE2:
                    if (!trainerOnlyMove){
                        int goOn = getch();
                        while (goOn != 27){
                            goOn = getch();
                        }
                    }
                    wclear(top);
                    box(top, 0, 0);
                    wrefresh(top);
                    missed = ((rand() % 100) < actualTrainerMove.accuracy);
                    *type = 1;
                    *crit = 1;
                    damageDealt = damageCalc(trainerTeam[curTrainerPoke], myWorld.player.pokemon[curPlayerPoke], actualTrainerMove, crit, type) * int(missed);
                    myWorld.player.pokemon[curPlayerPoke].extraInfo.currentHP = max(0, myWorld.player.pokemon[curPlayerPoke].extraInfo.currentHP - damageDealt);
                    if (!missed){
                        mvwprintw(top, 1, 1, "%s tried to attack but missed! Press ESC", trainerTeam[curTrainerPoke].pokemon.name.c_str());
                    }
                    else if (*crit == 1.5){
                        mvwprintw(top, 1, 1, "%s used %s and crit %s dealing %d damage! Press ESC", trainerTeam[curTrainerPoke].pokemon.name.c_str(), actualTrainerMove.name.c_str(), myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str(), damageDealt);
                    }
                    else {
                        mvwprintw(top, 1, 1, "%s used %s on %s dealing %d damage! Press ESC", trainerTeam[curTrainerPoke].pokemon.name.c_str(), actualTrainerMove.name.c_str(), myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str(), damageDealt);
                    }

                    if (*type > 1 && damageDealt > 0){
                        mvwprintw(top, 2, 1, "It was super-effective!");
                    }
                    else if (*type < 1 && damageDealt > 0){
                        mvwprintw(top, 2, 1, "It was not very effective!");
                    }
                    wrefresh(top);
                    if (myWorld.player.pokemon[curPlayerPoke].extraInfo.currentHP == 0 && teamAliveCheck()){
                        curPlayerPoke = pokeSwap(true, bottom, curPlayerPoke);
                        if (trainerOnlyMove){
                            trainerOnlyMove = false;
                        }
                        wclear(bottom);
                        box(bottom, 0, 0);
                        mvwprintw(bottom, 1, 1, "Level (%d) %s  HP: %d/%d", myWorld.player.pokemon[curPlayerPoke].experience.level, myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str(), myWorld.player.pokemon[curPlayerPoke].extraInfo.currentHP, myWorld.player.pokemon[curPlayerPoke].stats[0]);
                        wrefresh(bottom);
                        wclear(top);
                        box(top, 0, 0);
                        mvwprintw(top, 1, 1, "What will %s do? (1 to attack, 2 for bag, 3 to switch, 4 to run)", myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str());
                        mvwprintw(top, 2, 1, "Level (%d) %s  HP: %d/%d", trainerTeam[curTrainerPoke].experience.level, trainerTeam[curTrainerPoke].pokemon.name.c_str(), trainerTeam[curTrainerPoke].extraInfo.currentHP, trainerTeam[curTrainerPoke].stats[0]);
                        wrefresh(top);
                        goto STARTBATTLE;
                    }
                    else if (myWorld.player.pokemon[curPlayerPoke].extraInfo.currentHP == 0 && !(teamAliveCheck())){
                        if (*type < 1 || *type > 1 && damageDealt > 0){
                            mvwprintw(top, 3, 1, "You have no more usable Pokemon! You whited out! Press ESC");
                        }
                        else {
                            mvwprintw(top, 2, 1, "You have no more usable Pokemon! You whited out! Press ESC");
                        }
                        wrefresh(top);
                        int goOn = getch();
                        while (goOn != 27){
                            goOn = getch();
                        }
                        delwin(top);
                        delwin(bottom);
                        whiteOut();
                        break;
                    }
                    else {
                        if (trainerOnlyMove){
                            trainerOnlyMove = false;
                        }
                        wrefresh(top);
                        int goOn = getch();
                        while (goOn != 27){
                            goOn = getch();
                        }
                        wclear(bottom);
                        box(bottom, 0, 0);
                        mvwprintw(bottom, 1, 1, "Level (%d) %s  HP: %d/%d", myWorld.player.pokemon[curPlayerPoke].experience.level, myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str(), myWorld.player.pokemon[curPlayerPoke].extraInfo.currentHP, myWorld.player.pokemon[curPlayerPoke].stats[0]);
                        wrefresh(bottom);
                        wclear(top);
                        box(top, 0, 0);
                        mvwprintw(top, 1, 1, "What will %s do? (1 to attack, 2 for bag, 3 to switch, 4 to run)", myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str());
                        mvwprintw(top, 2, 1, "Level (%d) %s  HP: %d/%d", trainerTeam[curTrainerPoke].experience.level, trainerTeam[curTrainerPoke].pokemon.name.c_str(), trainerTeam[curTrainerPoke].extraInfo.currentHP, trainerTeam[curTrainerPoke].stats[0]);
                        wrefresh(top);
                        goto STARTBATTLE;
                    }


                }
                
            }
            //trainer move
            else {
                wclear(top);
                box(top, 0, 0);
                wrefresh(top);
                double * crit = (double *) malloc(sizeof (double));
                double * type = (double *) malloc(sizeof (double));
                *type = 1.0;
                int damageDealt;
                missed = ((rand() % 100) < actualTrainerMove.accuracy);
                *crit = 1;
                damageDealt = damageCalc(trainerTeam[curTrainerPoke], myWorld.player.pokemon[curPlayerPoke], actualTrainerMove, crit, type) * int(missed);
                myWorld.player.pokemon[curPlayerPoke].extraInfo.currentHP = max(0, myWorld.player.pokemon[curPlayerPoke].extraInfo.currentHP - damageDealt);
                if (!missed){
                    mvwprintw(top, 1, 1, "%s tried to attack but missed! Press ESC", trainerTeam[curTrainerPoke].pokemon.name.c_str());
                }
                else if (*crit == 1.5){
                    mvwprintw(top, 1, 1, "%s used %s and crit %s dealing %d damage! Press ESC", trainerTeam[curTrainerPoke].pokemon.name.c_str(), actualTrainerMove.name.c_str(), myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str(), damageDealt);
                }
                else {
                    mvwprintw(top, 1, 1, "%s used %s on %s dealing %d damage! Press ESC", trainerTeam[curTrainerPoke].pokemon.name.c_str(), actualTrainerMove.name.c_str(), myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str(), damageDealt);
                }

                if (*type > 1 && damageDealt > 0){
                    mvwprintw(top, 2, 1, "It was super-effective!");
                }
                else if (*type < 1 && damageDealt > 0){
                    mvwprintw(top, 2, 1, "It was not very effective!");
                }

                wrefresh(top);
                if (myWorld.player.pokemon[curPlayerPoke].extraInfo.currentHP == 0 && teamAliveCheck()){
                    curPlayerPoke = pokeSwap(true, bottom, curPlayerPoke);
                    wclear(bottom);
                    box(bottom, 0, 0);
                    mvwprintw(bottom, 1, 1, "Level (%d) %s  HP: %d/%d", myWorld.player.pokemon[curPlayerPoke].experience.level, myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str(), myWorld.player.pokemon[curPlayerPoke].extraInfo.currentHP, myWorld.player.pokemon[curPlayerPoke].stats[0]);
                    wrefresh(bottom);
                    wclear(top);
                    box(top, 0, 0);
                    mvwprintw(top, 1, 1, "What will %s do? (1 to attack, 2 for bag, 3 to switch, 4 to run)", myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str());
                    mvwprintw(top, 2, 1, "Level (%d) %s  HP: %d/%d", trainerTeam[curTrainerPoke].experience.level, trainerTeam[curTrainerPoke].pokemon.name.c_str(), trainerTeam[curTrainerPoke].extraInfo.currentHP, trainerTeam[curTrainerPoke].stats[0]);
                    wrefresh(top);
                    goto STARTBATTLE;
                }
                else if (myWorld.player.pokemon[curPlayerPoke].extraInfo.currentHP == 0 && !(teamAliveCheck())){
                    if (*type < 1 || *type > 1 && damageDealt > 0){
                        mvwprintw(top, 3, 1, "You have no more usable Pokemon! You whited out! Press ESC");
                    }
                    else{
                        mvwprintw(top, 2, 1, "You have no more usable Pokemon! You whited out! Press ESC");
                    }
                    wrefresh(top);
                    int goOn = getch();
                    while (goOn != 27){
                        goOn = getch();
                    }
                    delwin(top);
                    delwin(bottom);
                    whiteOut();
                    break;
                }
                //player move
                else {
                    int goOn = getch();
                    while (goOn != 27){
                        goOn = getch();
                    }
                    wclear(top);
                    box(top, 0, 0);
                    wrefresh(top);
                    *type = 1;
                    *crit = 1;
                    missed = ((rand() % 100) < actualPlayerMove.accuracy);
                    damageDealt = damageCalc(myWorld.player.pokemon[curPlayerPoke], trainerTeam[curTrainerPoke], actualPlayerMove, crit, type) * int(missed);
                    trainerTeam[curTrainerPoke].extraInfo.currentHP -= damageDealt;
                    if (!missed){
                    mvwprintw(top, 1, 1, "%s tried to attack but missed! Press ESC", myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str());
                    
                    }
                    else if (*crit == 1.5){
                        mvwprintw(top, 1, 1, "%s used %s and crit %s dealing %d damage! Press ESC", myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str(), actualPlayerMove.name.c_str(), trainerTeam[curTrainerPoke].pokemon.name.c_str(), damageDealt);
                    }
                    else {
                        mvwprintw(top, 1, 1, "%s used %s on %s dealing %d damage! Press ESC", myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str(), actualPlayerMove.name.c_str(), trainerTeam[curTrainerPoke].pokemon.name.c_str(), damageDealt);
                    }

                    if (*type > 1 && damageDealt > 0){
                    mvwprintw(top, 2, 1, "It was super-effective!");
                    }
                    else if (*type < 1 && damageDealt > 0){
                        mvwprintw(top, 2, 1, "It was not very effective!");
                    }

                    wrefresh(top);
                    if (trainerTeam[curTrainerPoke].extraInfo.currentHP <= 0 && curTrainerPoke + 1 < trainerTeam.size()){
                        if (*type > 1 || *type < 1 && damageDealt > 0){
                            mvwprintw(top, 3, 1, "The opposing %s fainted!", trainerTeam[curTrainerPoke].pokemon.name.c_str());
                            mvwprintw(top, 4, 1, "Your %s gained %d xp!", myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str(), int(((trainerTeam[curTrainerPoke].pokemon.baseXP * trainerTeam[curTrainerPoke].experience.level) / 7) * 1.5));
                            curTrainerPoke += 1;
                            mvwprintw(top, 5, 1, "The opposing trainer swaped in a level %d %s!", trainerTeam[curTrainerPoke].experience.level, trainerTeam[curTrainerPoke].pokemon.name.c_str());
                            mvwprintw(top, 6, 1, "Press ESC");
                        }
                        else {
                            mvwprintw(top, 2, 1, "The opposing %s fainted!", trainerTeam[curTrainerPoke].pokemon.name.c_str());
                            mvwprintw(top, 3, 1, "Your %s gained %d xp!", myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str(), int(((trainerTeam[curTrainerPoke].pokemon.baseXP * trainerTeam[curTrainerPoke].experience.level) / 7) * 1.5));
                            curTrainerPoke += 1;
                            mvwprintw(top, 4, 1, "The opposing trainer swaped in a level %d %s!", trainerTeam[curTrainerPoke].experience.level, trainerTeam[curTrainerPoke].pokemon.name.c_str());
                            mvwprintw(top, 5, 1, "Press ESC");
                        }
                        wrefresh(top);
                        int goOn = getch();
                        while (goOn != 27){
                            goOn = getch();
                        }
                        expGain(trainerTeam[curTrainerPoke], &myWorld.player.pokemon[curPlayerPoke], trainerBattle, top, bottom);
                        wclear(bottom);
                        box(bottom, 0, 0);
                        mvwprintw(bottom, 1, 1, "Level (%d) %s  HP: %d/%d", myWorld.player.pokemon[curPlayerPoke].experience.level, myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str(), myWorld.player.pokemon[curPlayerPoke].extraInfo.currentHP, myWorld.player.pokemon[curPlayerPoke].stats[0]);
                        wrefresh(bottom);
                        wclear(top);
                        box(top, 0, 0);
                        mvwprintw(top, 1, 1, "What will %s do? (1 to attack, 2 for bag, 3 to switch, 4 to run)", myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str());
                        mvwprintw(top, 2, 1, "Level (%d) %s  HP: %d/%d", trainerTeam[curTrainerPoke].experience.level, trainerTeam[curTrainerPoke].pokemon.name.c_str(), trainerTeam[curTrainerPoke].extraInfo.currentHP, trainerTeam[curTrainerPoke].stats[0]);
                        wrefresh(top);
                        goto STARTBATTLE;
                    }
                    else if (trainerTeam[curTrainerPoke].extraInfo.currentHP <= 0 && curTrainerPoke + 1 >= trainerTeam.size()){
                        if (*type < 1 || *type > 1 && damageDealt > 0){
                            mvwprintw(top, 3, 1, "The opposing %s fainted!", trainerTeam[curTrainerPoke].pokemon.name.c_str());
                            if (trainerBattle){
                                mvwprintw(top, 4, 1, "Your %s gained %d xp!", myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str(), int(((trainerTeam[curTrainerPoke].pokemon.baseXP * trainerTeam[curTrainerPoke].experience.level) / 7) * 1.5));
                                mvwprintw(top, 5, 1, "The opposing trainer has no more pokemon left, you win!");
                                mvwprintw(top, 6, 1, "The trainer paid out $%d!", (30 * trainerTeam[0].experience.level));
                                myWorld.player.money += (30 * trainerTeam[0].experience.level);
                            }
                            else {
                                mvwprintw(top, 4, 1, "Your %s gained %d xp!", myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str(), int(((trainerTeam[curTrainerPoke].pokemon.baseXP * trainerTeam[curTrainerPoke].experience.level) / 7)));
                            }
                            mvwprintw(top, 7, 1, "Press ESC");
                        }
                        else {
                            mvwprintw(top, 2, 1, "The opposing %s fainted!", trainerTeam[curTrainerPoke].pokemon.name.c_str());
                            if (trainerBattle){
                                mvwprintw(top, 3, 1, "Your %s gained %d xp!", myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str(), int(((trainerTeam[curTrainerPoke].pokemon.baseXP * trainerTeam[curTrainerPoke].experience.level) / 7) * 1.5));
                                mvwprintw(top, 4, 1, "The opposing trainer has no more pokemon left, you win!");
                                mvwprintw(top, 5, 1, "The trainer paid out $%d!", (30 * trainerTeam[0].experience.level));
                                myWorld.player.money += (30 * trainerTeam[0].experience.level);
                            }
                            else {
                                mvwprintw(top, 3, 1, "Your %s gained %d xp!", myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str(), int(((trainerTeam[curTrainerPoke].pokemon.baseXP * trainerTeam[curTrainerPoke].experience.level) / 7)));
                            }
                            mvwprintw(top, 6, 1, "Press ESC");
                        }
                        wrefresh(top);
                        int goOn = getch();
                        while (goOn != 27){
                            goOn = getch();
                        }
                        expGain(trainerTeam[curTrainerPoke], &myWorld.player.pokemon[curPlayerPoke], trainerBattle, top, bottom);
                        break;
                    }
                    else {
                        wrefresh(top);
                        goOn = getch();
                        while (goOn != 27){
                            goOn = getch();
                        }
                        wclear(bottom);
                        box(bottom, 0, 0);
                        mvwprintw(bottom, 1, 1, "Level (%d) %s  HP: %d/%d", myWorld.player.pokemon[curPlayerPoke].experience.level, myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str(), myWorld.player.pokemon[curPlayerPoke].extraInfo.currentHP, myWorld.player.pokemon[curPlayerPoke].stats[0]);
                        wrefresh(bottom);
                        wclear(top);
                        box(top, 0, 0);
                        mvwprintw(top, 1, 1, "What will %s do? (1 to attack, 2 for bag, 3 to switch, 4 to run)", myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str());
                        mvwprintw(top, 2, 1, "Level (%d) %s  HP: %d/%d", trainerTeam[curTrainerPoke].experience.level, trainerTeam[curTrainerPoke].pokemon.name.c_str(), trainerTeam[curTrainerPoke].extraInfo.currentHP, trainerTeam[curTrainerPoke].stats[0]);
                        wrefresh(top);
                        goto STARTBATTLE;
                    }
                }
            }
            
        }
        else if (npcMove == '2'){
            BATTLEBAG:
            wclear(bottom);
            box(bottom, 0, 0);
            mvwprintw(bottom, 3, 1, "(1) Pokeballs: %d", myWorld.player.bag.count[0]);
            mvwprintw(bottom, 4, 1, "(2) Great Balls: %d", myWorld.player.bag.count[1]);
            mvwprintw(bottom, 5, 1, "(3) Ultra Balls: %d", myWorld.player.bag.count[2]);
            mvwprintw(bottom, 6, 1, "(4) Potions: %d", myWorld.player.bag.count[3]);
            mvwprintw(bottom, 7, 1, "(5) Super Potions: %d", myWorld.player.bag.count[4]);
            mvwprintw(bottom, 8, 1, "(6) Hyper Potions: %d", myWorld.player.bag.count[5]);
            mvwprintw(bottom, 9, 1, "(7) Revives: %d", myWorld.player.bag.count[6]);
            mvwprintw(bottom, 10, 1, "(8) Full Revives: %d", myWorld.player.bag.count[7]);
            mvwprintw(bottom, 1, 1, "Press 1, 2, or 3 to");
            mvwprintw(bottom, 2, 1, "use the respective item");
            wrefresh(bottom);
            int tempInput = getch();
            while (tempInput != '1' && tempInput != '2' && tempInput != '3' && tempInput != '4' && tempInput != '5'
            && tempInput != '6' && tempInput != '7' && tempInput != '8' && tempInput != 27){
                tempInput = getch();
            }
            //do an inbetween for selecting which kind to use
            if (tempInput == '1' || tempInput == '2' || tempInput == '3'){
                if (trainerBattle){
                    wclear(bottom);
                    box(bottom, 0, 0);
                    mvwprintw(bottom, 1, 1, "Cannot be used right now.");
                    mvwprintw(bottom, 2, 1, "Press ESC");
                    wrefresh(bottom);
                    int goOn = getch();
                    while (goOn != 27){
                        goOn = getch();
                    }
                    goto BATTLEBAG;
                }
                else {
                    if (myWorld.player.bag.count[tempInput - 49] == 0){
                        wclear(bottom);
                        box(bottom, 0, 0);
                        mvwprintw(bottom, 1, 1, "You have no more pokeballs.");
                        mvwprintw(bottom, 2, 1, "Go to a PokeMart to refill. Press Esc");
                        wrefresh(bottom);
                        int goOn = getch();
                        while (goOn != 27){
                            goOn = getch();
                        }
                        wclear(bottom);
                        box(bottom, 0, 0);
                        goto BATTLEBAG;
                    }
                    //figure out different pokeballs and status
                    double ballUsed = myWorld.player.bag.effect[tempInput - 49];
                    double status = 1;
                    int random = rand() % 256;
                    double catchRate = min(int(((((3 * trainerTeam[0].stats[0]) - (2 * trainerTeam[0].extraInfo.currentHP)) * trainerTeam[0].pokemonSpecies.captureRate * ballUsed)) / ((3 * trainerTeam[0].stats[0])) * status), 256);
                    bool caught = catchRate > random;
                    // bool caught = true;
                    if (caught){
                        if (myWorld.player.pokemon.size() < 6){
                            myWorld.player.pokemon.push_back(trainerTeam[0]);
                        }
                        else {
                            myWorld.player.boxPokemon.push_back(trainerTeam[0]);
                        }
                        wclear(top);
                        box(top, 0, 0);
                        mvwprintw(top, 1, 1, "The %s was caught!", trainerTeam[0].pokemon.name.c_str());
                        mvwprintw(top, 2, 1, "Press Esc");
                        wrefresh(top);
                        int goOn = getch();
                        while (goOn != 27){
                            goOn = getch();
                        }
                        myWorld.player.bag.count[tempInput - 49]--;
                        wclear(top);
                        wclear(bottom);
                        delwin(top);
                        delwin(bottom);
                        break;
                    }
                    else {
                        wclear(top);
                        box(top, 0, 0);
                        mvwprintw(top, 1, 1, "%s broke free! Press Esc", trainerTeam[0].pokemon.name.c_str());
                        wrefresh(top);
                        int goOn = getch();
                        while (goOn != 27){
                            goOn = getch();
                        }
                        myWorld.player.bag.count[tempInput - 49]--;
                        trainerOnlyMove = true;
                        wclear(bottom);
                        box(bottom, 0, 0);
                        wrefresh(bottom);
                        goto TRAINERONLYMOVE;
                    }
                }

            }
            else if (tempInput == '4' || tempInput == '5' || tempInput == '6'){
                POTIONTIME:
                int chosen;
                wclear(bottom);
                box(bottom, 0, 0);
                wrefresh(bottom);
                if (myWorld.player.bag.count[tempInput - 49] == 0){
                    mvwprintw(bottom, 1, 1, "You have no more potions.");
                    mvwprintw(bottom, 2, 1, "Go to a PokeMart to refill. Press Esc");
                    wrefresh(bottom);
                    int goOn = getch();
                    while (goOn != 27){
                        goOn = getch();
                    }
                    wclear(bottom);
                    box(bottom, 0, 0);
                    goto BATTLEBAG;
                }
                mvwprintw(bottom, 1, 1, "Who to use on? (1, 2, 3...)");
                mvwprintw(bottom, 2, 1, "Pokemon:");
                mvwprintw(bottom, 2, 45, "HP:");
                for (int i = 0; i < myWorld.player.pokemon.size(); i++){
                    mvwprintw(bottom, i + 3, 1, "(%d) %s", i+1, myWorld.player.pokemon[i].pokemon.name.c_str());
                    mvwprintw(bottom, i + 3, 45, "%d/%d", myWorld.player.pokemon[i].extraInfo.currentHP, myWorld.player.pokemon[i].stats[0]);
                }
                wrefresh(bottom);
                int temptInput = getch();
                while (temptInput != '1' && temptInput != '2' && temptInput != '3' && temptInput != '4' && temptInput != '5' && temptInput != '6' && temptInput != 27){
                    temptInput = getch();
                }
                bool potionWorked = false;
                if (temptInput == '1'){
                    if (myWorld.player.pokemon[0].extraInfo.currentHP > 0 && myWorld.player.pokemon[0].extraInfo.currentHP < myWorld.player.pokemon[0].stats[0]){
                        potionWorked = true;
                        chosen = 0;
                        myWorld.player.pokemon[0].extraInfo.currentHP = min(myWorld.player.pokemon[0].extraInfo.currentHP + myWorld.player.bag.effect[tempInput - 49], myWorld.player.pokemon[0].stats[0]);
                        mvwprintw(bottom, 3, 1, "%s         %d/%d", myWorld.player.pokemon[0].pokemon.name.c_str(), myWorld.player.pokemon[0].extraInfo.currentHP, myWorld.player.pokemon[0].stats[0]);
                    }
                }
                else if (temptInput == '2'){
                    if (myWorld.player.pokemon.size() > 1 && myWorld.player.pokemon[1].extraInfo.currentHP > 0 && myWorld.player.pokemon[1].extraInfo.currentHP < myWorld.player.pokemon[1].stats[0]){
                        potionWorked = true;
                        chosen = 1;
                        myWorld.player.pokemon[1].extraInfo.currentHP = min(myWorld.player.pokemon[1].extraInfo.currentHP + myWorld.player.bag.effect[tempInput - 49], myWorld.player.pokemon[1].stats[0]);
                        mvwprintw(bottom, 4, 1, "%s         %d/%d", myWorld.player.pokemon[1].pokemon.name.c_str(), myWorld.player.pokemon[1].extraInfo.currentHP, myWorld.player.pokemon[1].stats[0]);
                    }
                }
                else if (temptInput == '3'){
                    if (myWorld.player.pokemon.size() > 2 && myWorld.player.pokemon[2].extraInfo.currentHP > 0 && myWorld.player.pokemon[2].extraInfo.currentHP < myWorld.player.pokemon[2].stats[0]){
                        potionWorked = true;
                        chosen = 2;
                        myWorld.player.pokemon[2].extraInfo.currentHP = min(myWorld.player.pokemon[2].extraInfo.currentHP + myWorld.player.bag.effect[tempInput - 49], myWorld.player.pokemon[2].stats[0]);
                        mvwprintw(bottom, 5, 1, "%s         %d/%d", myWorld.player.pokemon[2].pokemon.name.c_str(), myWorld.player.pokemon[2].extraInfo.currentHP, myWorld.player.pokemon[2].stats[0]);
                    }
                }
                else if (temptInput == '4'){
                    if (myWorld.player.pokemon.size() > 3 && myWorld.player.pokemon[3].extraInfo.currentHP > 0 && myWorld.player.pokemon[3].extraInfo.currentHP < myWorld.player.pokemon[3].stats[0]){
                        potionWorked = true;
                        chosen = 3;
                        myWorld.player.pokemon[3].extraInfo.currentHP = min(myWorld.player.pokemon[3].extraInfo.currentHP + myWorld.player.bag.effect[tempInput - 49], myWorld.player.pokemon[3].stats[0]);
                        mvwprintw(bottom, 6, 1, "%s         %d/%d", myWorld.player.pokemon[3].pokemon.name.c_str(), myWorld.player.pokemon[3].extraInfo.currentHP, myWorld.player.pokemon[3].stats[0]);
                    }
                }
                else if (temptInput == '5'){
                    if (myWorld.player.pokemon.size() > 4 && myWorld.player.pokemon[4].extraInfo.currentHP > 0 && myWorld.player.pokemon[4].extraInfo.currentHP < myWorld.player.pokemon[4].stats[0]){
                        potionWorked = true;
                        chosen = 4;
                        myWorld.player.pokemon[4].extraInfo.currentHP = min(myWorld.player.pokemon[4].extraInfo.currentHP + myWorld.player.bag.effect[tempInput - 49], myWorld.player.pokemon[4].stats[0]);
                        mvwprintw(bottom, 7, 1, "%s         %d/%d", myWorld.player.pokemon[4].pokemon.name.c_str(), myWorld.player.pokemon[4].extraInfo.currentHP, myWorld.player.pokemon[4].stats[0]);
                    }
                }
                else if (temptInput == '6'){
                    if (myWorld.player.pokemon.size() > 5 && myWorld.player.pokemon[5].extraInfo.currentHP > 0 && myWorld.player.pokemon[5].extraInfo.currentHP < myWorld.player.pokemon[5].stats[0]){
                        potionWorked = true;
                        chosen = 5;
                        myWorld.player.pokemon[5].extraInfo.currentHP = min(myWorld.player.pokemon[5].extraInfo.currentHP + myWorld.player.bag.effect[tempInput - 49], myWorld.player.pokemon[5].stats[0]);
                        mvwprintw(bottom, 8, 1, "%s         %d/%d", myWorld.player.pokemon[5].pokemon.name.c_str(), myWorld.player.pokemon[5].extraInfo.currentHP, myWorld.player.pokemon[5].stats[0]);
                    }
                }
                else {
                    wclear(bottom);
                    box(bottom, 0, 0);
                    mvwprintw(bottom, 1, 1, "Level (%d) %s  HP: %d/%d", myWorld.player.pokemon[curPlayerPoke].experience.level, myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str(), myWorld.player.pokemon[curPlayerPoke].extraInfo.currentHP, myWorld.player.pokemon[curPlayerPoke].stats[0]);
                    wrefresh(bottom);
                    wclear(top);
                    box(top, 0, 0);
                    mvwprintw(top, 1, 1, "What will %s do? (1 to attack, 2 for bag, 3 to switch, 4 to run)", myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str());
                    mvwprintw(top, 2, 1, "Level (%d) %s  HP: %d/%d", trainerTeam[curTrainerPoke].experience.level, trainerTeam[curTrainerPoke].pokemon.name.c_str(), trainerTeam[curTrainerPoke].extraInfo.currentHP, trainerTeam[curTrainerPoke].stats[0]);
                    wrefresh(top);
                    goto STARTBATTLE;
                }
                if (potionWorked){
                    wclear(top);
                    box(top, 0, 0);
                    mvwprintw(top, 1, 1, "%s was healed! Press Esc", myWorld.player.pokemon[chosen].pokemon.name.c_str());
                    wrefresh(top);
                    int goOn = getch();
                    while (goOn != 27){
                        goOn = getch();
                    }
                    myWorld.player.bag.count[tempInput - 49]--;
                    trainerOnlyMove = true;
                    wclear(bottom);
                    box(bottom, 0, 0);
                    wrefresh(bottom);
                    goto TRAINERONLYMOVE;
                }
                else {
                    wclear(bottom);
                    box(bottom, 0, 0);
                    mvwprintw(bottom, 1, 1, "Not a valid choice");
                    mvwprintw(bottom, 2, 1, "Press ESC");
                    wrefresh(bottom);
                    int goOn = getch();
                    while (goOn != 27){
                        goOn = getch();
                    }
                    goto POTIONTIME;
                }

            }
            else if (tempInput == '7' || tempInput == '8'){
                REVIVETIME:
                int chosen;
                wclear(bottom);
                box(bottom, 0, 0);
                if (myWorld.player.bag.count[tempInput - 49] == 0){
                    mvwprintw(bottom, 1, 1, "You have no more revives.");
                    mvwprintw(bottom, 2, 1, "Go to a PokeMart to refill. Press Esc");
                    wrefresh(bottom);
                    int goOn = getch();
                    while (goOn != 27){
                        goOn = getch();
                    }
                    wclear(bottom);
                    box(bottom, 0, 0);
                    goto BATTLEBAG;
                }
                mvwprintw(bottom, 1, 1, "Who to use on? (1, 2, 3...)");
                mvwprintw(bottom, 2, 1, "Pokemon:");
                mvwprintw(bottom, 2, 1, "HP:");
                for (int i = 0; i < myWorld.player.pokemon.size(); i++){
                    mvwprintw(bottom, i + 3, 1, "(%d) %s", i+1, myWorld.player.pokemon[i].pokemon.name.c_str());
                    mvwprintw(bottom, i + 3, 45, "%d/%d",myWorld.player.pokemon[i].extraInfo.currentHP, myWorld.player.pokemon[i].stats[0]);
                }
                wrefresh(bottom);
                int temptInput = getch();
                while (temptInput != '1' && temptInput != '2' && temptInput != '3' && temptInput != '4' && temptInput != '5' && temptInput != '6' && temptInput != 27){
                    temptInput = getch();
                }
                bool reviveWorked = false;
                if (temptInput == '1'){
                    if (myWorld.player.pokemon[0].extraInfo.currentHP == 0){
                    reviveWorked = true;
                    chosen = 0;
                    myWorld.player.pokemon[0].extraInfo.currentHP = myWorld.player.pokemon[0].stats[0] * myWorld.player.bag.effect[tempInput - 49];
                    mvwprintw(bottom, 3, 1, "%s         %d/%d", myWorld.player.pokemon[0].pokemon.name.c_str(), myWorld.player.pokemon[0].extraInfo.currentHP, myWorld.player.pokemon[0].stats[0]);
                    }
                }
                else if (temptInput == '2'){
                    if (myWorld.player.pokemon.size() > 1 && myWorld.player.pokemon[1].extraInfo.currentHP == 0){
                        reviveWorked = true;
                        chosen = 1;
                        myWorld.player.pokemon[1].extraInfo.currentHP = myWorld.player.pokemon[1].stats[0] * myWorld.player.bag.effect[tempInput - 49];
                        mvwprintw(bottom, 4, 1, "%s        %d/%d", myWorld.player.pokemon[1].pokemon.name.c_str(), myWorld.player.pokemon[1].extraInfo.currentHP, myWorld.player.pokemon[1].stats[0]);
                    }
                }
                else if (temptInput == '3'){
                    if (myWorld.player.pokemon.size() > 2 && myWorld.player.pokemon[2].extraInfo.currentHP == 0){
                        reviveWorked = true;
                        chosen = 2;
                        myWorld.player.pokemon[2].extraInfo.currentHP = myWorld.player.pokemon[2].stats[0] * myWorld.player.bag.effect[tempInput - 49];
                        mvwprintw(bottom, 5, 1, "%s         %d/%d", myWorld.player.pokemon[2].pokemon.name.c_str(), myWorld.player.pokemon[2].extraInfo.currentHP, myWorld.player.pokemon[2].stats[0]);
                    }
                }
                else if (temptInput == '4'){
                    if (myWorld.player.pokemon.size() > 3 && myWorld.player.pokemon[3].extraInfo.currentHP == 0){
                        reviveWorked = true;
                        chosen = 3;
                        myWorld.player.pokemon[3].extraInfo.currentHP = myWorld.player.pokemon[3].stats[0] * myWorld.player.bag.effect[tempInput - 49];
                        mvwprintw(bottom, 6, 1, "%s         %d/%d", myWorld.player.pokemon[3].pokemon.name.c_str(), myWorld.player.pokemon[3].extraInfo.currentHP, myWorld.player.pokemon[3].stats[0]);
                    }
                }
                else if (temptInput == '5'){
                    if (myWorld.player.pokemon.size() > 4 && myWorld.player.pokemon[4].extraInfo.currentHP == 0){
                        reviveWorked = true;
                        chosen = 4;
                        myWorld.player.pokemon[4].extraInfo.currentHP = myWorld.player.pokemon[4].stats[0] * myWorld.player.bag.effect[tempInput - 49];
                        mvwprintw(bottom, 7, 1, "%s         %d/%d", myWorld.player.pokemon[4].pokemon.name.c_str(), myWorld.player.pokemon[4].extraInfo.currentHP, myWorld.player.pokemon[4].stats[0]);
                    }
                }
                else if (temptInput == '6'){
                    if (myWorld.player.pokemon.size() > 5 && myWorld.player.pokemon[5].extraInfo.currentHP == 0){
                        reviveWorked = true;
                        chosen = 5;
                        myWorld.player.pokemon[5].extraInfo.currentHP = myWorld.player.pokemon[5].stats[0] * myWorld.player.bag.effect[tempInput - 49];
                        mvwprintw(bottom, 8, 1, "%s         %d/%d", myWorld.player.pokemon[5].pokemon.name.c_str(), myWorld.player.pokemon[5].extraInfo.currentHP, myWorld.player.pokemon[5].stats[0]);
                    }
                }
                else {
                    wclear(bottom);
                    box(bottom, 0, 0);
                    mvwprintw(bottom, 1, 1, "Level (%d) %s  HP: %d/%d", myWorld.player.pokemon[curPlayerPoke].experience.level, myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str(), myWorld.player.pokemon[curPlayerPoke].extraInfo.currentHP, myWorld.player.pokemon[curPlayerPoke].stats[0]);
                    wrefresh(bottom);
                    wclear(top);
                    box(top, 0, 0);
                    mvwprintw(top, 1, 1, "What will %s do? (1 to attack, 2 for bag, 3 to switch, 4 to run)", myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str());
                    mvwprintw(top, 2, 1, "Level (%d) %s  HP: %d/%d", trainerTeam[curTrainerPoke].experience.level, trainerTeam[curTrainerPoke].pokemon.name.c_str(), trainerTeam[curTrainerPoke].extraInfo.currentHP, trainerTeam[curTrainerPoke].stats[0]);
                    wrefresh(top);
                    goto STARTBATTLE;
                }
                if (reviveWorked){
                    wclear(top);
                    box(top, 0, 0);
                    mvwprintw(top, 1, 1, "%s was revived! Press Esc", myWorld.player.pokemon[chosen].pokemon.name.c_str());
                    wrefresh(top);
                    int goOn = getch();
                    while (goOn != 27){
                        goOn = getch();
                    }
                    myWorld.player.bag.count[tempInput - 49]--;
                    wclear(bottom);
                    box(bottom, 0, 0);
                    trainerOnlyMove = true;
                    goto TRAINERONLYMOVE;
                }
                else {
                    wclear(bottom);
                    box(bottom, 0, 0);
                    mvwprintw(bottom, 1, 1, "That didn't work!");
                    mvwprintw(bottom, 2, 1, "Press ESC");
                    wrefresh(bottom);
                    int goOn = getch();
                    while (goOn != 27){
                        goOn = getch();
                    }
                    goto REVIVETIME;
                }
            }
            else {
                wclear(bottom);
                box(bottom, 0, 0);
                mvwprintw(bottom, 1, 1, "Level (%d) %s  HP: %d/%d", myWorld.player.pokemon[curPlayerPoke].experience.level, myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str(), myWorld.player.pokemon[curPlayerPoke].extraInfo.currentHP, myWorld.player.pokemon[curPlayerPoke].stats[0]);
                wrefresh(bottom);
                wclear(top);
                box(top, 0, 0);
                mvwprintw(top, 1, 1, "What will %s do? (1 to attack, 2 for bag, 3 to switch, 4 to run)", myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str());
                mvwprintw(top, 2, 1, "Level (%d) %s  HP: %d/%d", trainerTeam[curTrainerPoke].experience.level, trainerTeam[curTrainerPoke].pokemon.name.c_str(), trainerTeam[curTrainerPoke].extraInfo.currentHP, trainerTeam[curTrainerPoke].stats[0]);
                wrefresh(top);
                goto STARTBATTLE;
            }
        }
        else if (npcMove == '3'){
            curPlayerPoke = pokeSwap(false, bottom, curPlayerPoke);
            if (curPlayerPoke > 9){
                curPlayerPoke = curPlayerPoke - 10;
                wclear(bottom);
                box(bottom, 0, 0);
                mvwprintw(bottom, 1, 1, "Level (%d) %s  HP: %d/%d", myWorld.player.pokemon[curPlayerPoke].experience.level, myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str(), myWorld.player.pokemon[curPlayerPoke].extraInfo.currentHP, myWorld.player.pokemon[curPlayerPoke].stats[0]);
                wrefresh(bottom);
                wclear(top);
                box(top, 0, 0);
                mvwprintw(top, 1, 1, "What will %s do? (1 to attack, 2 for bag, 3 to switch, 4 to run)", myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str());
                mvwprintw(top, 2, 1, "Level (%d) %s  HP: %d/%d", trainerTeam[curTrainerPoke].experience.level, trainerTeam[curTrainerPoke].pokemon.name.c_str(), trainerTeam[curTrainerPoke].extraInfo.currentHP, trainerTeam[curTrainerPoke].stats[0]);
                wrefresh(top);
                goto STARTBATTLE;
            }
            trainerOnlyMove = true;
            goto TRAINERONLYMOVE;
        }
        else {
            if (trainerBattle){
                wclear(bottom);
                box(bottom, 0, 0);
                mvwprintw(bottom, 1, 1, "You can't flee from trainer battles! Press ESC");
                wrefresh(bottom);
                int goOn = getch();
                while (goOn != 27){
                    goOn = getch();
                }
                wclear(bottom);
                box(bottom, 0, 0);
                mvwprintw(bottom, 1, 1, "Level (%d) %s  HP: %d/%d", myWorld.player.pokemon[curPlayerPoke].experience.level, myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str(), myWorld.player.pokemon[curPlayerPoke].extraInfo.currentHP, myWorld.player.pokemon[curPlayerPoke].stats[0]);
                wrefresh(bottom);
                wclear(top);
                box(top, 0, 0);
                mvwprintw(top, 1, 1, "What will %s do? (1 to attack, 2 for bag, 3 to switch, 4 to run)", myWorld.player.pokemon[curPlayerPoke].pokemon.name.c_str());
                mvwprintw(top, 2, 1, "Level (%d) %s  HP: %d/%d", trainerTeam[curTrainerPoke].experience.level, trainerTeam[curTrainerPoke].pokemon.name.c_str(), trainerTeam[curTrainerPoke].extraInfo.currentHP, trainerTeam[curTrainerPoke].stats[0]);
                wrefresh(top);
                goto STARTBATTLE;
            }
            else {
                int escapeChance = ((myWorld.player.pokemon[curPlayerPoke].stats[5] * 32) / ((trainerTeam[0].stats[5] / 4) % 256)) + 30;
                if ((rand() % 100) < escapeChance){
                    wclear(bottom);
                    box(bottom, 0, 0);
                    mvwprintw(bottom, 1, 1, "You successfully ran away! Press ESC");
                    int goOn = getch();
                    while (goOn != 27){
                        goOn = getch();
                    }
                    break;
                }
                else {
                    wclear(bottom);
                    box(bottom, 0, 0);
                    mvwprintw(bottom, 1, 1, "You failed to run away! Press ESC");
                    int goOn = getch();
                    while (goOn != 27){
                        goOn = getch();
                    }
                }
            }
        }
    }
}

void getVoiceLine(WINDOW *w, map_t *m, char c, int y, int x, char d, char wandTerrain){
    if (d == 'd'){
        int goOn = 0;
        switch(c){
            case 'h':
                mvprintw(1, 1, "Gotta go evolve all six of my geodude.");
                mvprintw(2, 1, "Press ESC to Close.");
                goOn = getch();
                while (goOn != 27){
                    goOn = getch();
                }
                return;
            case 'r':
                mvprintw(1, 1, "Just wait till you get to the next map. Im going to be cracked.");
                mvprintw(2, 1, "Press ESC to Close.");
                goOn = getch();
                while (goOn != 27){
                    goOn = getch();
                }
                return;
            case 's':
                mvprintw(1, 1, "You choose to stand still because you get tired. I choose to stand still");
                mvprintw(2, 1, "because I am lazy. We are not the same.");
                mvprintw(3, 1, "Press ESC to Close.");
                goOn = getch();
                while (goOn != 27){
                    goOn = getch();
                }
                return;
            case 'm':
                mvprintw(1, 1, "I don't know how I'm doing these laps, I can't swim.");
                mvprintw(2, 1, "PRESS ESC TO CLOSE");
                goOn = getch();
                while (goOn != 27){
                    goOn = getch();
                }
                return;
            case 'p':
                if (y == m->trainers.pace1Y && x == m->trainers.pace1X){
                    mvprintw(1, 1, "Back to the grass, I hope I don't run into to that other guy, he is weird.");
                    mvprintw(2, 1, "PRESS ESC TO CLOSE");
                    goOn = getch();
                    while (goOn != 27){
                        goOn = getch();
                    }
                }
                else {
                    mvprintw(1, 1, "Back to the grass, maybe i'll spice it up and step outta line.");
                    mvprintw(2, 1, "PRESS ESC TO CLOSE");
                    goOn = getch();
                    while (goOn != 27){
                        goOn = getch();
                    }
                }
                return;
            case 'w':
                mvprintw(1, 1, "New %c tile just dropped, I gotta get to it.", wandTerrain);
                mvprintw(2, 1, "PRESS ESC TO CLOSE");
                goOn = getch();
                while (goOn != 27){
                    goOn = getch();
                }
                return;
            case 'e':
                mvprintw(1, 1, "Time to Battle!");
                mvprintw(2, 1, "Wait, why are all my pokemon fainted? Who are you? Where are we?");
                mvprintw(3, 1, "PRESS ESC TO CLOSE");
                goOn = getch();
                while (goOn != 27){
                    goOn = getch();
                }
                return;

        }
    }
    else {
        std::vector<actualPokemon_t> trainerPokemon;
        actualPokemon_t * poke = new actualPokemon_t;
        tallGrassEncounter(m, poke, myWorld.player.worldX, myWorld.player.worldY, false);
        trainerPokemon.push_back(*poke);
        int chance = rand() % 100;
        while (chance < 60 && trainerPokemon.size() < 6){
            poke = new actualPokemon_t;
            tallGrassEncounter(m, poke, myWorld.player.worldX, myWorld.player.worldY, false);
            trainerPokemon.push_back(*poke);
            chance = rand() % 100;
        }
        int goOn = 0;
        switch(c){
            case 'h':
                mvprintw(1, 1, "Explain right now how oxygen isotopes could show us how the climate changed");
                mvprintw(2, 1, "hundreds of millions of years ago.");
                mvprintw(3, 1, "Lets Battle!");
                mvprintw(5, 1, "Hiker sent out level %d %s!", trainerPokemon[0].experience.level, trainerPokemon[0].pokemon.name.c_str());
                mvprintw(6, 1, "Press ESC");
                refresh();
                goOn = getch();
                while (goOn != 27){
                    goOn = getch();
                }
                wclear(w);
                wrefresh(w);
                delwin(w);
                battleStart(trainerPokemon, true);
                for (int i = 0; i < myWorld.player.pokemon.size(); i++){
                    if (myWorld.player.pokemon[i].experience.level >= myWorld.player.pokemon[i].evolutionInfo.minLevel){
                        std::string ogName = myWorld.player.pokemon[i].pokemon.name;
                        evolvePoke(&myWorld.player.pokemon[i]);
                        w = create_newwin(80,24);
                        box(w, 0, 0);
                        mvwprintw(w, 1, 1, "Congratulations! Your %s evolved into a %s!", ogName.c_str(), myWorld.player.pokemon[i].pokemon.name.c_str());
                        mvwprintw(w, 2, 1, "Press Esc");
                        wrefresh(w);
                        int goOn = getch();
                        while (goOn != 27){
                            goOn = getch();
                        }
                        delwin(w);
                    }
                }
                
                return;
            case 'r':
                mvprintw(1, 1, "Call me Silver because my Pokemon aren't good enough. But I can make up for");
                mvprintw(2, 1, "that in order to take you down.");
                mvprintw(3, 1, "Lets Battle!");
                mvprintw(5, 1, "Rival sent out level %d %s!", trainerPokemon[0].experience.level, trainerPokemon[0].pokemon.name.c_str());
                mvprintw(6, 1, "Press ESC");
                refresh();
                goOn = getch();
                while (goOn != 27){
                    goOn = getch();
                }
                wclear(w);
                wrefresh(w);
                delwin(w);
                battleStart(trainerPokemon, true);
                for (int i = 0; i < myWorld.player.pokemon.size(); i++){
                    if (myWorld.player.pokemon[i].experience.level >= myWorld.player.pokemon[i].evolutionInfo.minLevel){
                        std::string ogName = myWorld.player.pokemon[i].pokemon.name;
                        evolvePoke(&myWorld.player.pokemon[i]);
                        w = create_newwin(80,24);
                        box(w, 0, 0);
                        mvwprintw(w, 1, 1, "Congratulations! Your %s evolved into a %s!", ogName.c_str(), myWorld.player.pokemon[i].pokemon.name.c_str());
                        mvwprintw(w, 2, 1, "Press Esc");
                        wrefresh(w);
                        int goOn = getch();
                        while (goOn != 27){
                            goOn = getch();
                        }
                        delwin(w);
                    }
                }
                return;
            case 's':
                mvprintw(1, 1, "Why do people keep walking up and talking to me? What ever happened to");
                mvprintw(2, 1, "antisocial people. Everybodys gotta be an extrovert nowadays");
                mvprintw(3, 1, "Lets Battle!");
                mvprintw(5, 1, "Sentry sent out level %d %s!", trainerPokemon[0].experience.level, trainerPokemon[0].pokemon.name.c_str());
                mvprintw(6, 1, "Press ESC");
                refresh();
                goOn = getch();
                while (goOn != 27){
                    goOn = getch();
                }
                wclear(w);
                wrefresh(w);
                delwin(w);
                battleStart(trainerPokemon, true);
                for (int i = 0; i < myWorld.player.pokemon.size(); i++){
                    if (myWorld.player.pokemon[i].experience.level >= myWorld.player.pokemon[i].evolutionInfo.minLevel){
                        std::string ogName = myWorld.player.pokemon[i].pokemon.name;
                        evolvePoke(&myWorld.player.pokemon[i]);
                        w = create_newwin(80,24);
                        box(w, 0, 0);
                        mvwprintw(w, 1, 1, "Congratulations! Your %s evolved into a %s!", ogName.c_str(), myWorld.player.pokemon[i].pokemon.name.c_str());
                        mvwprintw(w, 2, 1, "Press Esc");
                        wrefresh(w);
                        int goOn = getch();
                        while (goOn != 27){
                            goOn = getch();
                        }
                        delwin(w);
                    }
                }
                return;
            case 'm':
                mvprintw(1, 1, "Surprised you didn't I?");
                mvprintw(2, 1, "Lets Battle!");
                mvprintw(4, 1, "Swimmer sent out level %d %s!", trainerPokemon[0].experience.level, trainerPokemon[0].pokemon.name.c_str());
                mvprintw(5, 1, "Press ESC");
                refresh();
                goOn = getch();
                while (goOn != 27){
                    goOn = getch();
                }
                wclear(w);
                wrefresh(w);
                delwin(w);
                battleStart(trainerPokemon, true);
                for (int i = 0; i < myWorld.player.pokemon.size(); i++){
                    if (myWorld.player.pokemon[i].experience.level >= myWorld.player.pokemon[i].evolutionInfo.minLevel){
                        std::string ogName = myWorld.player.pokemon[i].pokemon.name;
                        evolvePoke(&myWorld.player.pokemon[i]);
                        w = create_newwin(80,24);
                        box(w, 0, 0);
                        mvwprintw(w, 1, 1, "Congratulations! Your %s evolved into a %s!", ogName.c_str(), myWorld.player.pokemon[i].pokemon.name.c_str());
                        mvwprintw(w, 2, 1, "Press Esc");
                        wrefresh(w);
                        int goOn = getch();
                        while (goOn != 27){
                            goOn = getch();
                        }
                        delwin(w);
                    }
                }
                return;
            case 'p':
                if (y == m->trainers.pace1Y && x == m->trainers.pace1X){
                    mvprintw(1, 1, "Twelve pieces of grass, Thirteen pieces of grass, TREE!");
                    mvprintw(2, 1, "Time to turn around -- Wait! You're not a tree.");
                    mvprintw(3, 1, "Don't compare me to that other guy over there, he is weird.");
                    mvprintw(4, 1, "Lets Battle!");
                    mvprintw(6, 1, "Pacer sent out level %d %s!", trainerPokemon[0].experience.level, trainerPokemon[0].pokemon.name.c_str());
                    mvprintw(7, 1, "Press ESC");
                    refresh();
                    goOn = getch();
                    while (goOn != 27){
                        goOn = getch();
                    }
                    wclear(w);
                    wrefresh(w);
                    delwin(w);
                    battleStart(trainerPokemon, true);  
                }
                else {
                    mvprintw(1, 1, "Sup, don't listen to what that other dude is saying,");
                    mvprintw(2, 1, "I've never seen him walk north or south, I don't think he knows how.");
                    mvprintw(3, 1, "I walk like this mostly just to spite him.");
                    mvprintw(4, 1, "Lets Battle!");
                    mvprintw(6, 1, "Pacer sent out level %d %s!", trainerPokemon[0].experience.level, trainerPokemon[0].pokemon.name.c_str());
                    mvprintw(7, 1, "Press ESC");
                    refresh();
                    goOn = getch();
                    while (goOn != 27){
                        goOn = getch();
                    }
                    wclear(w);
                    wrefresh(w);
                    delwin(w);
                    battleStart(trainerPokemon, true);
                }
                for (int i = 0; i < myWorld.player.pokemon.size(); i++){
                    if (myWorld.player.pokemon[i].experience.level >= myWorld.player.pokemon[i].evolutionInfo.minLevel){
                        std::string ogName = myWorld.player.pokemon[i].pokemon.name;
                        evolvePoke(&myWorld.player.pokemon[i]);
                        w = create_newwin(80,24);
                        box(w, 0, 0);
                        mvwprintw(w, 1, 1, "Congratulations! Your %s evolved into a %s!", ogName.c_str(), myWorld.player.pokemon[i].pokemon.name.c_str());
                        mvwprintw(w, 2, 1, "Press Esc");
                        wrefresh(w);
                        int goOn = getch();
                        while (goOn != 27){
                            goOn = getch();
                        }
                        delwin(w);
                    }
                }
                return;
            case 'w':
                mvprintw(1, 1, "What are you doing? You are in the way of my next %c tile. I need you to move.", wandTerrain);
                mvprintw(2, 1, "Whatever, I'll just move you out of the way.");
                mvprintw(3, 1, "Lets Battle!");
                mvprintw(5, 1, "Wanderer sent out level %d %s!", trainerPokemon[0].experience.level, trainerPokemon[0].pokemon.name.c_str());
                mvprintw(6, 1, "Press ESC");
                refresh();
                goOn = getch();
                while (goOn != 27){
                    goOn = getch();
                }
                wclear(w);
                wrefresh(w);
                delwin(w);
                battleStart(trainerPokemon, true);
                for (int i = 0; i < myWorld.player.pokemon.size(); i++){
                    if (myWorld.player.pokemon[i].experience.level >= myWorld.player.pokemon[i].evolutionInfo.minLevel){
                        std::string ogName = myWorld.player.pokemon[i].pokemon.name;
                        evolvePoke(&myWorld.player.pokemon[i]);
                        w = create_newwin(80,24);
                        box(w, 0, 0);
                        mvwprintw(w, 1, 1, "Congratulations! Your %s evolved into a %s!", ogName.c_str(), myWorld.player.pokemon[i].pokemon.name.c_str());
                        mvwprintw(w, 2, 1, "Press Esc");
                        wrefresh(w);
                        int goOn = getch();
                        while (goOn != 27){
                            goOn = getch();
                        }
                        delwin(w);
                    }
                }
                return;
            case 'e':
                mvprintw(1, 1, "They all say I've lost my mind, but one day I will explore the entire world.");
                mvprintw(2, 1, "I've never travelled the same place twice just like");
                mvprintw(3, 1, "I've never forgotten the face of a stronger trainer.");
                mvprintw(4, 1, "Lets Battle!");
                mvprintw(6, 1, "Explorer sent out level %d %s!", trainerPokemon[0].experience.level, trainerPokemon[0].pokemon.name.c_str());
                mvprintw(7, 1, "Press ESC");
                refresh();
                goOn = getch();
                while (goOn != 27){
                    goOn = getch();
                }
                wclear(w);
                wrefresh(w);
                delwin(w);
                battleStart(trainerPokemon, true);
                for (int i = 0; i < myWorld.player.pokemon.size(); i++){
                    if (myWorld.player.pokemon[i].experience.level >= myWorld.player.pokemon[i].evolutionInfo.minLevel){
                        std::string ogName = myWorld.player.pokemon[i].pokemon.name;
                        evolvePoke(&myWorld.player.pokemon[i]);
                        w = create_newwin(80,24);
                        box(w, 0, 0);
                        mvwprintw(w, 1, 1, "Congratulations! Your %s evolved into a %s!", ogName.c_str(), myWorld.player.pokemon[i].pokemon.name.c_str());
                        mvwprintw(w, 2, 1, "Press Esc");
                        wrefresh(w);
                        int goOn = getch();
                        while (goOn != 27){
                            goOn = getch();
                        }
                        delwin(w);
                    }
                }
                return;
        }
    }
}
/**
 * Tells the hiker or rival where to go based on their shortest path towards the player until they battle
*/
int trainerMoveHelper(map_t *m, int x, int y, char c){
    WINDOW *w;
    int lowest = INT_MAX;
    int counter = 0;
    int dir = 0;
    for (int i = y - 1; i <= y + 1; i++){
        for (int j = x - 1; j <= x + 1; j++){
            if (i != y || j != x){
                if (c == 'H'){
                    if (m->characterMap[i][j] == '@'){
                        if (npcDefeated(m, 'h', m->trainers.hikerY, m->trainers.hikerX) == 0){
                        npcKill(m, 'h', m->trainers.hikerY, m->trainers.hikerX);
                        int exit = 0;
                        w = create_newwin(80, 24);
                        getVoiceLine(w, m, 'h', m->trainers.hikerY, m->trainers.hikerX, 'n', '.');
                        delwin(w);
                        }
                        return 8;
                    }
                    if (myWorld.hikerMap[i][j] < lowest && myWorld.hikerMap[i][j] >= 0 && m->characterMap[i][j] == 'X'){
                        lowest = myWorld.hikerMap[i][j];
                        if (counter == 0){
                            dir = 0;
                        }
                        else if (counter == 1){
                            dir = 1;
                        }
                        else if (counter == 2){
                            dir = 2;
                        }
                        else if (counter == 3){
                            dir = 3;
                        }
                        else if (counter == 4){
                            dir = 4;
                        }
                        else if (counter == 5){
                            dir = 5;
                        }
                        else if (counter == 6){
                            dir = 6;
                        }
                        else if (counter == 7){
                            dir = 7;
                        }
                    }
                }
                else{
                    if (m->characterMap[i][j] == '@'){
                        if (npcDefeated(m, 'r', m->trainers.rivalY, m->trainers.rivalX) == 0){
                        npcKill(m, 'r', m->trainers.rivalY, m->trainers.rivalX);
                        int exit = 0;
                        w = create_newwin(80, 24);
                        getVoiceLine(w, m, 'r', m->trainers.rivalY, m->trainers.rivalX, 'n', '.');
                        delwin(w);
                        }
                        return 8;
                    }
                    if (myWorld.rivalMap[i][j] < lowest && myWorld.rivalMap[i][j] >= 0 && m->characterMap[i][j] == 'X'){
                        lowest = myWorld.rivalMap[i][j];
                        if (counter == 0){
                            dir = 0;
                        }
                        else if (counter == 1){
                            dir = 1;
                        }
                        else if (counter == 2){
                            dir = 2;
                        }
                        else if (counter == 3){
                            dir = 3;
                        }
                        else if (counter == 4){
                            dir = 4;
                        }
                        else if (counter == 5){
                            dir = 5;
                        }
                        else if (counter == 6){
                            dir = 6;
                        }
                        else if (counter == 7){
                            dir = 7;
                        }
                    }
                }
                counter++;
            }    
        }
        
    }
    return dir;
    
}


void distanceFromPlayer(char c, int x, int y, int index){
    x = x - myWorld.player.playerX;
    y = y - myWorld.player.playerY;
    if (x < 0) {
        x = x * -1;
        if (y < 0) {
            y = y * -1;
            mvprintw(index, 1, "%c, %d north, %d west", c, y, x);
        }
        else if (y > 0){
            mvprintw(index, 1, "%c, %d south, %d west", c, y, x);
        }
        else {
            mvprintw(index, 1, "%c, %d west", c, x);
        }
    }
    else if (x > 0){
        if (y < 0){
            y = y * -1;
            mvprintw(index, 1, "%c, %d north, %d east", c, y, x);
        }
        else if (y > 0){
            mvprintw(index, 1, "%c, %d south, %d east", c, y, x);
        }
        else {
            mvprintw(index, 1, "%c, %d east", c, x);
        }
    }
    else {
        if (y < 0){
            y = y * -1;
             mvprintw(index, 1, "%c, %d north", c, y);
        }
        else if (y > 0){
            mvprintw(index, 1, "%c, %d south", c, y);
        }
    }
    refresh();
}

/**
 * Movement for hiker and rival post being defeated
*/
void defeatedMovement(map_t *m, char c, int *y, int *x){
    WINDOW *w;
    while (1){
            int tempX = rand() % (1 + 1 - 0) + 0;
            int tempY = rand() % (1 + 1 - 0) + 0;
            int negX = rand() % (1 + 1 - 0) + 0;
            int negY = rand() % (1 + 1 - 0) + 0;
            if (!(tempX == 0 && tempY == 0)){
                if (negX == 0){
                    if (negY == 0){
                        if (myWorld.hikerMap[*y][*x] >= 0 && myWorld.hikerMap[*y + tempY][*x + tempX] != INT_MAX
                        && m->characterMap[*y + tempY][*x + tempX] == 'X'){
                            m->characterMap[*y + tempY][*x + tempX] = c;
                            m->characterMap[*y][*x] = 'X';
                            *x += tempX;
                            *y += tempY;
                            break;
                        }
                        else if (m->characterMap[*y + tempY][*x + tempX] == '@') {
                            int exit = 0;
                            w = create_newwin(80, 24);
                            mvprintw(1, 1, "Sorry I bumped into you, I need to go heal my pokemon.");
                            mvprintw(2, 1, "PRESS ESC TO CLOSE");
                            refresh();
                            while(exit != 27){
                                exit = getch();
                            }
                            delwin(w);
                        }
                    }
                    else if (negY == 1){
                        if (myWorld.hikerMap[*y - tempY][*x + tempX] >= 0 && myWorld.hikerMap[*y - tempY][*x + tempX] != INT_MAX
                        && m->characterMap[*y - tempY][*x + tempX] == 'X'){
                            m->characterMap[*y - tempY][*x + tempX] = c;
                            m->characterMap[*y][*x] = 'X';
                            *x += tempX;
                            *y -= tempY;
                            break;
                        }
                        else if (m->characterMap[*y + tempY][*x + tempX] == '@') {
                            int exit = 0;
                            w = create_newwin(80, 24);
                            mvprintw(1, 1, "Sorry I bumped into you, I need to go heal my pokemon.");
                            mvprintw(2, 1, "PRESS ESC TO CLOSE");
                            refresh();
                            while(exit != 27){
                                exit = getch();
                            }
                            delwin(w);
                        }
                    }
                }
                if (negY == 0){
                        if (myWorld.hikerMap[*y + tempY][*x - tempX] >= 0 && myWorld.hikerMap[*y + tempY][*x - tempX] != INT_MAX
                        && m->characterMap[*y + tempY][*x - tempX] == 'X'){
                            m->characterMap[*y + tempY][*x - tempX] = c;
                            m->characterMap[*y][*x] = 'X';
                            *x -= tempX;
                            *y += tempY;
                            break;
                        }
                        else if (m->characterMap[*y + tempY][*x + tempX] == '@') {
                            int exit = 0;
                            w = create_newwin(80, 24);
                            mvprintw(1, 1, "Sorry I bumped into you, I need to go heal my pokemon.");
                            mvprintw(2, 1, "PRESS ESC TO CLOSE");
                            refresh();
                            while(exit != 27){
                                exit = getch();
                            }
                            delwin(w);
                        }
                }
                else if (negY == 1){
                        if (myWorld.hikerMap[*y - tempY][*x - tempX] >= 0 && myWorld.hikerMap[*y - tempY][*x - tempX] != INT_MAX
                        && m->characterMap[*y - tempY][*x - tempX] == 'X'){
                            m->characterMap[*y - tempY][*x - tempX] = c;
                            m->characterMap[*y][*x] = 'X';
                            *x -= tempX;
                            *y -= tempY;
                            break;
                        }
                        else if (m->characterMap[*y + tempY][*x + tempX] == '@') {
                            int exit = 0;
                            w = create_newwin(80, 24);
                            mvprintw(1, 1, "Sorry I bumped into you, I need to go heal my pokemon.");
                            mvprintw(2, 1, "PRESS ESC TO CLOSE");
                            refresh();
                            while(exit != 27){
                                exit = getch();
                            }
                            delwin(w);
                        }
                }
            }
        }
}


std::string getPokeSaveInfo(actualPokemon_t poke){
    std::string pokeString = "";
    int i = 0;
    while (i < poke.moves.size()) {
        pokeString += std::to_string(poke.moves[i].id);
        pokeString += " ";
        pokeString += std::to_string(poke.extraInfo.ppLeft[i]);
        pokeString += " ";
        i++;
    }
    pokeString += "X ";
    i = 0;
    while (i < poke.pokemonMoves.size()) {
        pokeString += std::to_string(poke.pokemonMoves[i].moveID);
        pokeString += " ";
        i++;
    }
    pokeString += "X ";
    pokeString += std::to_string(poke.pokemonSpecies.dexNum);
    pokeString += " X ";
    pokeString += std::to_string(poke.extraInfo.currentHP);
    pokeString += " ";
    pokeString += std::to_string(poke.experience.level);
    pokeString += " ";
    pokeString += std::to_string(poke.extraInfo.curXp);
    pokeString += " ";
    pokeString += std::to_string(poke.extraInfo.curXpIndex);
    pokeString += " ";
    pokeString += std::to_string(poke.uid);
    pokeString += " ";
    pokeString += std::to_string(poke.learnMoveIndex);
    pokeString += " Y ";

    return pokeString;
}
/**
 * Writes data to a .enc textfile
 * Password: pokemoniscool
 * Order: Pokemon 1, 2, 3, 4, 5, 6 (one number for each actual_pokemont_t entry)
 *        Bag: pokeballs, greatballs, ultraballs, potions, superpotions, hyperpotions, revives, fullRevives Z
 *        Box Pokemon: 1-x
*/
void writeSave(int saveSlot){
    std::string commandString = "echo \"";
    for (int i = 0; i < myWorld.player.pokemon.size(); i++){
        commandString += getPokeSaveInfo(myWorld.player.pokemon[i]);
    }
    commandString += " * ";
    for (int i = 0; i < myWorld.player.bag.count.size(); i++){
        commandString += std::to_string(myWorld.player.bag.count[i]);
    }
    commandString += " * ";
    for (int i = 0; i < myWorld.player.boxPokemon.size(); i++){
        commandString += getPokeSaveInfo(myWorld.player.boxPokemon[i]);
    }
    commandString += "Z";
    commandString += "\" | openssl enc -base64 -e -aes-256-cbc -salt -pass pass:pokemoniscool -pbkdf2 > pokemonSave" + std::to_string(saveSlot - 48) + ".enc";
    system(commandString.c_str());
}


/**
 * Reads save file by unencrypting it into another file and then reading it in the order it was saved. Needs to be fixed, cant store data in poke, needs to be saved elsewhere
 * like a vector, then read in during the pokeLoadFinisher method.
*/
void readSave(int saveFile) {
    std::string data;
    bool boxPoke = false;
    int count = 0;
    std::string commandString = "openssl enc -base64 -d -aes-256-cbc -in pokemonSave" + std::to_string(saveFile) + ".enc" + " -salt -pass pass:pokemoniscool -pbkdf2 > pokemonLoad";
    system(commandString.c_str());
    std::ifstream ifs("/home/pantaleo/cs327/pantaleo_pokemon1/pantaleo_10/pokemonLoad");
    actualPokemon_t * poke = new actualPokemon_t;
    if (ifs){
        POKEASSIGNMENT:
        std::getline(ifs, data, ' ');
        while (data != std::string("X")) {
            poke->moves[count].id = std::stoi(data);
            std::getline(ifs, data, ' ');
            poke->extraInfo.ppLeft[count] = std::stoi(data);
            std::getline(ifs, data, ' ');
            count ++;
        }
        count = 0;
        std::getline(ifs, data, ' '); //skip X
        poke->pokemonMoves[count].moveID = std::stoi(data);
        count ++;
        std::getline(ifs, data, ' ');
        while (data != std::string("X")) {
            poke->pokemonMoves[count].moveID = std::stoi(data);
            count ++;
            std::getline(ifs, data, ' ');
        }
        std::getline(ifs, data, ' '); //skip X
        poke->pokemonSpecies.dexNum = std::stoi(data);
        std::getline(ifs, data, ' ');
        poke->extraInfo.currentHP = std::stoi(data);
        std::getline(ifs, data, ' ');
        poke->experience.level = std::stoi(data);
        std::getline(ifs, data, ' ');
        poke->extraInfo.curXp = std::stoi(data);
        std::getline(ifs, data, ' ');
        poke->extraInfo.curXpIndex = std::stoi(data);
        std::getline(ifs, data, ' ');
        poke->uid = std::stoi(data);
        std::getline(ifs, data, ' ');
        poke->learnMoveIndex = std::stoi(data);
        std::getline(ifs, data, ' ');
        if (data == std::string("Z")) {
            ifs.close();
            ifs.clear();
            return;
        }
        else if (data == std::string("*")) {
            for (int i = 0; i < myWorld.player.bag.count.size(); i++){
                std::getline(ifs, data, ' ');
                myWorld.player.bag.count[i] = std::stoi(data);
            }
            std::getline(ifs, data, ' ');
            if (data != std::string("*")) {
                mvprintw(1, 1, "FOR DEBUG ERROR AFTER TRAINER ITEM ASSIGNMENT");
                abort();
            }
            else {
                boxPoke = true;
                goto POKEASSIGNMENT;
            }
        }
        else if (data != std::string("Y")) {
            mvprintw(1, 1, "FOR DEBUG ERROR AFTER TRAINER POKE ASSIGNMENT");
            abort();
        }
        else {
            pokeLoadFinisher(poke);
            if (boxPoke) {
                myWorld.player.boxPokemon.push_back(*poke);
            }
            else {
                myWorld.player.pokemon.push_back(*poke);
            }
            goto POKEASSIGNMENT;
        }
        
    }
    
}

/**
 * Method used to move any given trainer, including the player, based on the char input passed in.
 * This is called in the main with the character being the symbol drawn from the character node that is 
 * popped off the top of the minHeap.
 * Each case has an if statement for if the character is on the edge, otherwise they move like normal.
 */
int movingTrainers(map_t *m, int* swimDown, int* swimLeft, int* paceDown, int* paceLeft, char c, int worldX, int worldY){
    WINDOW *w;
    if (c == '@'){
        int key = getch();
        switch(key) {
            case '7':
            case 'y':
            {
                if (m->singleMap[myWorld.player.playerY - 1][myWorld.player.playerX - 1] != '^' && m->singleMap[myWorld.player.playerY - 1][myWorld.player.playerX - 1] != '%' && m->singleMap[myWorld.player.playerY - 1][myWorld.player.playerX - 1] != '~'){
                    m->characterMap[myWorld.player.playerY][myWorld.player.playerX] = 'X';
                    if (m->characterMap[myWorld.player.playerY - 1][myWorld.player.playerX - 1] == 'X'){
                        myWorld.player.playerX -= 1;
                        myWorld.player.playerY -= 1;
                        m->characterMap[myWorld.player.playerY][myWorld.player.playerX] = '@';
                    }
                    else if (m->characterMap[myWorld.player.playerY - 1][myWorld.player.playerX - 1] != 'X'){
                        if (npcDefeated(m, m->characterMap[myWorld.player.playerY - 1][myWorld.player.playerX - 1], myWorld.player.playerY - 1, myWorld.player.playerX - 1) == 0){
                            npcKill(m, m->characterMap[myWorld.player.playerY - 1][myWorld.player.playerX - 1], myWorld.player.playerY - 1, myWorld.player.playerX - 1);
                            int exit = 0;
                            w = create_newwin(80, 24);
                            getVoiceLine(w, m, m->characterMap[myWorld.player.playerY - 1][myWorld.player.playerX - 1], myWorld.player.playerY - 1, myWorld.player.playerX - 1, 'n', m->singleMap[myWorld.player.playerY - 1][myWorld.player.playerX - 1]);
                            delwin(w);
                        }
                        else {
                            int exit = 0;
                            w = create_newwin(80, 24);
                            getVoiceLine(w, m, m->characterMap[myWorld.player.playerY - 1][myWorld.player.playerX - 1], myWorld.player.playerY - 1, myWorld.player.playerX - 1, 'd', m->singleMap[myWorld.player.playerY - 1][myWorld.player.playerX - 1]);
                            refresh();
                            delwin(w);
                        }
                        m->characterMap[myWorld.player.playerY][myWorld.player.playerX] = '@';
                    }
                }
                break; 
            }
            case '8':
            case 'k':
            {
                if (m->singleMap[myWorld.player.playerY - 1][myWorld.player.playerX] != '^' && m->singleMap[myWorld.player.playerY - 1][myWorld.player.playerX] != '%' && m->singleMap[myWorld.player.playerY - 1][myWorld.player.playerX] != '~'){
                    m->characterMap[myWorld.player.playerY][myWorld.player.playerX] = 'X';
                    if (m->characterMap[myWorld.player.playerY - 1][myWorld.player.playerX] == 'X'){
                        myWorld.player.playerY -= 1;
                        m->characterMap[myWorld.player.playerY][myWorld.player.playerX] = '@';
                    }
                    else if (m->characterMap[myWorld.player.playerY - 1][myWorld.player.playerX] != 'X'){
                        if (npcDefeated(m, m->characterMap[myWorld.player.playerY - 1][myWorld.player.playerX], myWorld.player.playerY - 1, myWorld.player.playerX) == 0){
                            npcKill(m, m->characterMap[myWorld.player.playerY - 1][myWorld.player.playerX], myWorld.player.playerY - 1, myWorld.player.playerX);
                            int exit = 0;
                            w = create_newwin(80, 24);
                            getVoiceLine(w, m, m->characterMap[myWorld.player.playerY - 1][myWorld.player.playerX], myWorld.player.playerY - 1, myWorld.player.playerX, 'n', m->singleMap[myWorld.player.playerY - 1][myWorld.player.playerX]);
                            delwin(w);
                        }
                        else {
                            int exit = 0;
                            w = create_newwin(80, 24);
                            getVoiceLine(w, m, m->characterMap[myWorld.player.playerY - 1][myWorld.player.playerX], myWorld.player.playerY - 1, myWorld.player.playerX, 'd', m->singleMap[myWorld.player.playerY - 1][myWorld.player.playerX]);
                            refresh();
                            delwin(w);
                        }
                        m->characterMap[myWorld.player.playerY][myWorld.player.playerX] = '@';
                    }
                }
                break;
            }
            case '9':
            case 'u':
            {
                if (m->singleMap[myWorld.player.playerY - 1][myWorld.player.playerX + 1] != '^' && m->singleMap[myWorld.player.playerY - 1][myWorld.player.playerX + 1] != '%' && m->singleMap[myWorld.player.playerY - 1][myWorld.player.playerX + 1] != '~'){
                    m->characterMap[myWorld.player.playerY][myWorld.player.playerX] = 'X';
                    if (m->characterMap[myWorld.player.playerY - 1][myWorld.player.playerX + 1] == 'X'){
                        myWorld.player.playerX += 1;
                        myWorld.player.playerY -= 1;
                        m->characterMap[myWorld.player.playerY][myWorld.player.playerX] = '@';
                    }
                    else if (m->characterMap[myWorld.player.playerY - 1][myWorld.player.playerX + 1] != 'X'){
                        if (npcDefeated(m, m->characterMap[myWorld.player.playerY - 1][myWorld.player.playerX + 1], myWorld.player.playerY - 1, myWorld.player.playerX + 1) == 0){
                            npcKill(m, m->characterMap[myWorld.player.playerY - 1][myWorld.player.playerX + 1], myWorld.player.playerY - 1, myWorld.player.playerX + 1);
                            int exit = 0;
                            w = create_newwin(80, 24);
                            getVoiceLine(w, m, m->characterMap[myWorld.player.playerY - 1][myWorld.player.playerX + 1], myWorld.player.playerY - 1, myWorld.player.playerX + 1, 'n', m->singleMap[myWorld.player.playerY - 1][myWorld.player.playerX + 1]);
                            delwin(w);
                        }
                        else {
                            int exit = 0;
                            w = create_newwin(80, 24);
                            getVoiceLine(w, m, m->characterMap[myWorld.player.playerY - 1][myWorld.player.playerX + 1], myWorld.player.playerY - 1, myWorld.player.playerX + 1, 'd', m->singleMap[myWorld.player.playerY - 1][myWorld.player.playerX + 1]);
                            refresh();
                            delwin(w);
                        }
                        m->characterMap[myWorld.player.playerY][myWorld.player.playerX] = '@';
                    }
                }
                break;
            }
            case '6':
            case 'l':
            {
                if (m->singleMap[myWorld.player.playerY][myWorld.player.playerX + 1] != '^' && m->singleMap[myWorld.player.playerY][myWorld.player.playerX + 1] != '%' && m->singleMap[myWorld.player.playerY][myWorld.player.playerX + 1] != '~'){
                    m->characterMap[myWorld.player.playerY][myWorld.player.playerX] = 'X';
                    if (m->characterMap[myWorld.player.playerY][myWorld.player.playerX + 1] == 'X'){
                        myWorld.player.playerX += 1;
                        m->characterMap[myWorld.player.playerY][myWorld.player.playerX] = '@';
                    }
                    else if (m->characterMap[myWorld.player.playerY][myWorld.player.playerX + 1] != 'X'){
                        if (npcDefeated(m, m->characterMap[myWorld.player.playerY][myWorld.player.playerX + 1], myWorld.player.playerY, myWorld.player.playerX + 1) == 0){
                            npcKill(m, m->characterMap[myWorld.player.playerY][myWorld.player.playerX + 1], myWorld.player.playerY, myWorld.player.playerX + 1);
                            int exit = 0;
                            w = create_newwin(80, 24);
                            getVoiceLine(w, m, m->characterMap[myWorld.player.playerY][myWorld.player.playerX + 1], myWorld.player.playerY, myWorld.player.playerX + 1, 'n', m->singleMap[myWorld.player.playerY][myWorld.player.playerX + 1]);
                            delwin(w);
                        }
                        else {
                            int exit = 0;
                            w = create_newwin(80, 24);
                            getVoiceLine(w, m, m->characterMap[myWorld.player.playerY][myWorld.player.playerX + 1], myWorld.player.playerY, myWorld.player.playerX + 1, 'd', m->singleMap[myWorld.player.playerY][myWorld.player.playerX + 1]);
                            refresh();
                            delwin(w);
                        }
                        m->characterMap[myWorld.player.playerY][myWorld.player.playerX] = '@';
                    }
                }
                break;
            }
            case '4':
            case 'h':
            {
                if (m->singleMap[myWorld.player.playerY][myWorld.player.playerX - 1] != '^' && m->singleMap[myWorld.player.playerY][myWorld.player.playerX - 1] != '%' && m->singleMap[myWorld.player.playerY][myWorld.player.playerX - 1] != '~'){
                    m->characterMap[myWorld.player.playerY][myWorld.player.playerX] = 'X';
                    if (m->characterMap[myWorld.player.playerY][myWorld.player.playerX - 1] == 'X'){
                        myWorld.player.playerX -= 1;
                        m->characterMap[myWorld.player.playerY][myWorld.player.playerX] = '@';
                    }
                    else if (m->characterMap[myWorld.player.playerY][myWorld.player.playerX - 1] != 'X'){
                        if (npcDefeated(m, m->characterMap[myWorld.player.playerY][myWorld.player.playerX - 1], myWorld.player.playerY, myWorld.player.playerX - 1) == 0){
                            npcKill(m, m->characterMap[myWorld.player.playerY][myWorld.player.playerX - 1], myWorld.player.playerY, myWorld.player.playerX - 1);
                            int exit = 0;
                            w = create_newwin(80, 24);
                            getVoiceLine(w, m, m->characterMap[myWorld.player.playerY][myWorld.player.playerX - 1], myWorld.player.playerY, myWorld.player.playerX - 1, 'n', m->singleMap[myWorld.player.playerY][myWorld.player.playerX - 1]);
                            delwin(w);
                        }
                        else {
                            int exit = 0;
                            w = create_newwin(80, 24);
                            getVoiceLine(w, m, m->characterMap[myWorld.player.playerY][myWorld.player.playerX - 1], myWorld.player.playerY, myWorld.player.playerX - 1, 'd', m->singleMap[myWorld.player.playerY][myWorld.player.playerX - 1]);
                            refresh();
                            delwin(w);
                        }
                        m->characterMap[myWorld.player.playerY][myWorld.player.playerX] = '@';
                    }
                }
                break;
            }
            case '3':
            case 'n':
            {
                if (m->singleMap[myWorld.player.playerY + 1][myWorld.player.playerX + 1] != '^' && m->singleMap[myWorld.player.playerY + 1][myWorld.player.playerX + 1] != '%' && m->singleMap[myWorld.player.playerY + 1][myWorld.player.playerX + 1] != '~'){
                    m->characterMap[myWorld.player.playerY][myWorld.player.playerX] = 'X';
                    if (m->characterMap[myWorld.player.playerY + 1][myWorld.player.playerX + 1] == 'X'){
                        myWorld.player.playerX += 1;
                        myWorld.player.playerY += 1;
                        m->characterMap[myWorld.player.playerY][myWorld.player.playerX] = '@';
                    }   
                    else if (m->characterMap[myWorld.player.playerY + 1][myWorld.player.playerX + 1] != 'X'){
                        if (npcDefeated(m, m->characterMap[myWorld.player.playerY + 1][myWorld.player.playerX + 1], myWorld.player.playerY + 1, myWorld.player.playerX + 1) == 0){
                            npcKill(m, m->characterMap[myWorld.player.playerY + 1][myWorld.player.playerX + 1], myWorld.player.playerY + 1, myWorld.player.playerX + 1);
                            int exit = 0;
                            w = create_newwin(80, 24);
                            getVoiceLine(w, m, m->characterMap[myWorld.player.playerY + 1][myWorld.player.playerX + 1], myWorld.player.playerY + 1, myWorld.player.playerX + 1, 'n', m->singleMap[myWorld.player.playerY + 1][myWorld.player.playerX + 1]);
                            delwin(w);
                        }
                        else {
                            int exit = 0;
                            w = create_newwin(80, 24);
                            getVoiceLine(w, m, m->characterMap[myWorld.player.playerY + 1][myWorld.player.playerX + 1], myWorld.player.playerY + 1, myWorld.player.playerX + 1, 'd', m->singleMap[myWorld.player.playerY + 1][myWorld.player.playerX + 1]);
                            refresh();
                            delwin(w);
                        }
                        m->characterMap[myWorld.player.playerY][myWorld.player.playerX] = '@';
                    }
                }
                break;
            }
            case '2':
            case 'j':
            {
                if (m->singleMap[myWorld.player.playerY + 1][myWorld.player.playerX] != '^' && m->singleMap[myWorld.player.playerY + 1][myWorld.player.playerX] != '%' && m->singleMap[myWorld.player.playerY + 1][myWorld.player.playerX] != '~'){
                    m->characterMap[myWorld.player.playerY][myWorld.player.playerX] = 'X';
                    if (m->characterMap[myWorld.player.playerY + 1][myWorld.player.playerX] == 'X'){
                        myWorld.player.playerY += 1;
                        m->characterMap[myWorld.player.playerY][myWorld.player.playerX] = '@';
                    }
                    else if (m->characterMap[myWorld.player.playerY + 1][myWorld.player.playerX] != 'X'){
                        if (npcDefeated(m, m->characterMap[myWorld.player.playerY + 1][myWorld.player.playerX], myWorld.player.playerY + 1, myWorld.player.playerX) == 0){
                            npcKill(m, m->characterMap[myWorld.player.playerY + 1][myWorld.player.playerX], myWorld.player.playerY + 1, myWorld.player.playerX);
                            int exit = 0;
                            w = create_newwin(80, 24);
                            getVoiceLine(w, m, m->characterMap[myWorld.player.playerY + 1][myWorld.player.playerX], myWorld.player.playerY + 1, myWorld.player.playerX, 'n', m->singleMap[myWorld.player.playerY + 1][myWorld.player.playerX]);
                            delwin(w);
                        }
                        else {
                            int exit = 0;
                            w = create_newwin(80, 24);
                            getVoiceLine(w, m, m->characterMap[myWorld.player.playerY + 1][myWorld.player.playerX], myWorld.player.playerY + 1, myWorld.player.playerX, 'd', m->singleMap[myWorld.player.playerY + 1][myWorld.player.playerX]);
                            refresh();
                            delwin(w);
                        }
                        m->characterMap[myWorld.player.playerY][myWorld.player.playerX] = '@';
                    }
                }
                break;
            }
            case '1':
            case 'b':
            {
                if (m->singleMap[myWorld.player.playerY + 1][myWorld.player.playerX - 1] != '^' && m->singleMap[myWorld.player.playerY + 1][myWorld.player.playerX - 1] != '%' && m->singleMap[myWorld.player.playerY + 1][myWorld.player.playerX - 1] != '~'){
                    m->characterMap[myWorld.player.playerY][myWorld.player.playerX] = 'X';
                    if (m->characterMap[myWorld.player.playerY + 1][myWorld.player.playerX - 1] == 'X'){
                        myWorld.player.playerX -= 1;
                        myWorld.player.playerY += 1;
                        m->characterMap[myWorld.player.playerY][myWorld.player.playerX] = '@';
                    }
                    else if (m->characterMap[myWorld.player.playerY + 1][myWorld.player.playerX - 1] != 'X'){
                        if (npcDefeated(m, m->characterMap[myWorld.player.playerY + 1][myWorld.player.playerX - 1], myWorld.player.playerY + 1, myWorld.player.playerX - 1) == 0){
                            npcKill(m, m->characterMap[myWorld.player.playerY + 1][myWorld.player.playerX - 1], myWorld.player.playerY + 1, myWorld.player.playerX - 1);
                            int exit = 0;
                            w = create_newwin(80, 24);
                            getVoiceLine(w, m, m->characterMap[myWorld.player.playerY + 1][myWorld.player.playerX - 1], myWorld.player.playerY + 1, myWorld.player.playerX - 1, 'n', m->singleMap[myWorld.player.playerY + 1][myWorld.player.playerX - 1]);
                            delwin(w);
                        }
                        else {
                            int exit = 0;
                            w = create_newwin(80, 24);
                            getVoiceLine(w, m, m->characterMap[myWorld.player.playerY + 1][myWorld.player.playerX - 1], myWorld.player.playerY + 1, myWorld.player.playerX - 1, 'd', m->singleMap[myWorld.player.playerY + 1][myWorld.player.playerX - 1]);
                            refresh();
                            delwin(w);
                        }
                        m->characterMap[myWorld.player.playerY][myWorld.player.playerX] = '@';
                    }
                }
                break;
            }
            case '.':
            {
                //goes into pokemart/center
                if (m->singleMap[myWorld.player.playerY][myWorld.player.playerX] == 'C'){
                    w = create_newwin(80, 24);
                    mvprintw(1, 1, "This is the PokeCenter!");
                    mvprintw(2, 1, "May I see you pokemon for a second?");
                    mvprintw(3, 1, "Your pokemon have been fully healed!");
                    visitPokeCenter();
                    char insideShop = 'x';
                    while (insideShop != ','){
                        insideShop = getch();
                    }
                }
                else if ( m->singleMap[myWorld.player.playerY][myWorld.player.playerX] == 'M'){
                    w = create_newwin(80, 24);
                    box(w, 0, 0);
                    MARTOPEN:
                    mvwprintw(w, 1, 1, "This is the PokeMart!");
                    mvwprintw(w, 2, 1, "What can we help you with today?");
                    mvwprintw(w, 3, 1, "(1) Buy");
                    mvwprintw(w, 4, 1, "(2) Sell");
                    wrefresh(w);
                    int choice = getch();
                    while (choice != '1' && choice != '2' && choice != ','){
                        choice = getch();
                    }
                    if (choice == ','){
                        wclear(w);
                        delwin(w);
                        break;
                    }
                    else if (choice == '1'){
                        int cost[8] = {200, 600, 1200, 300, 700, 1200, 1500, 3000};
                        MARTBUY:
                        wclear(w);
                        box(w, 0, 0);
                        mvwprintw(w, 1, 1, "What would you like to buy?");
                        mvwprintw(w, 2, 1, "Money: $%d", myWorld.player.money);
                        mvwprintw(w, 3, 1, "(1) Poke Ball: $200");
                        mvwprintw(w, 4, 1, "(2) Great Ball: $600");
                        mvwprintw(w, 5, 1, "(3) Ultra Ball: $1200");
                        mvwprintw(w, 6, 1, "(4) Potion: $300");
                        mvwprintw(w, 7, 1, "(5) Super Potion: $700");
                        mvwprintw(w, 8, 1, "(6) Hyper Potion: $1200");
                        mvwprintw(w, 9, 1, "(7) Revive: $1500");
                        mvwprintw(w, 10, 1, "(8) Full Revive: $3000");
                        wrefresh(w);
                        int buying = getch();
                        while (buying != '1' && buying != '2' && buying != '3' && buying != '4' && 
                        buying != '5' && buying != '6' && buying != '7' && buying != '8' && buying != 27){
                            buying = getch();
                        }
                        wclear(w);
                        box(w, 0, 0);
                        mvwprintw(w, 1, 1, "How many would you like to buy? (9 per sale max)");
                        wrefresh(w);
                        if (buying == 27){
                            wclear(w);
                            box(w, 0, 0);
                            goto MARTOPEN;
                        }
                        else if (myWorld.player.money >= cost[buying - 49]){
                            int howMany = getch();
                            if (myWorld.player.money >= ((howMany - 48) * cost[buying - 49]) && howMany - 48 > 0){
                                myWorld.player.bag.count[buying - 49] += (howMany - 48);
                                myWorld.player.money -= cost[buying - 49] * (howMany - 48);
                            }
                            else {
                                mvwprintw(w, 1, 1, "You don't have enough money! Press Esc");
                                wrefresh(w);
                                int goOn = getch();
                                while (goOn != 27){
                                    goOn = getch();
                                }
                            }
                            goto MARTBUY;
                        }
                        else {
                            wclear(w);
                            box(w, 0, 0);
                            mvwprintw(w, 1, 1, "You don't have enough money! Press Esc");
                            wrefresh(w);
                            int goOn = getch();
                            while (goOn != 27){
                                goOn = getch();
                            }
                            goto MARTBUY;
                        }

                    }
                    else if (choice == '2'){
                        int cost[8] = {100, 300, 600, 150, 350, 600, 750, 1500};
                        MARTSELL:
                        wclear(w);
                        box(w, 0, 0);
                        mvwprintw(w, 1, 1, "What would you like to sell?");
                        mvwprintw(w, 2, 1, "Money: $%d", myWorld.player.money);
                        mvwprintw(w, 3, 1, "(1) Poke Ball: $100");
                        mvwprintw(w, 4, 1, "(2) Great Ball: $300");
                        mvwprintw(w, 5, 1, "(3) Ultra Ball: $600");
                        mvwprintw(w, 6, 1, "(4) Potion: $150");
                        mvwprintw(w, 7, 1, "(5) Super Potion: $350");
                        mvwprintw(w, 8, 1, "(6) Hyper Potion: $600");
                        mvwprintw(w, 9, 1, "(7) Revive: $750");
                        mvwprintw(w, 10, 1, "(8) Full Revive: $1500");
                        wrefresh(w);
                        int selling = getch();
                        while (selling != '1' && selling != '2' && selling != '3' && selling != '4' && 
                        selling != '5' && selling != '6' && selling != '7' && selling != '8' && selling != 27){
                            selling = getch();
                        }
                        if (selling == 27){
                            wclear(w);
                            box(w, 0, 0);
                            goto MARTOPEN;
                        }
                        else if (myWorld.player.bag.count[selling - 49] > 0){
                            wclear(w);
                            box(w, 0, 0);
                            mvwprintw(w, 1, 1, "How many would you like to sell? (9 per sale max)");
                            mvwprintw(w, 2, 1, "Money: $%d", myWorld.player.money);
                            mvwprintw(w, 3, 1, "Currently selling for $%d each.", cost[selling - 49]);
                            wrefresh(w);
                            int howMany = getch();
                            if (howMany == 27){
                                goto MARTSELL;
                            }
                            else if (howMany - 48 > 0 && howMany - 48 <= myWorld.player.bag.count[selling - 49]){
                                myWorld.player.money += ((howMany - 48) * (cost[selling - 49]));
                                myWorld.player.bag.count[selling - 49] -= (howMany - 48);
                                goto MARTSELL;
                            }
                            else {
                                wclear(w);
                                box(w, 0, 0);
                                mvwprintw(w, 1, 1, "You don't have that many! Press Esc");
                                wrefresh(w);
                                int goOn = getch();
                                while (goOn != 27){
                                    goOn = getch();
                                }
                                goto MARTSELL;
                            }

                        }
                        else {
                            wclear(w);
                            box(w, 0, 0);
                            mvwprintw(w, 1, 1, "You don't have any of those! Press Esc");
                            wrefresh(w);
                            int goOn = getch();
                            while (goOn != 27){
                                goOn = getch();
                            }
                            goto MARTSELL;
                        }
                        
                    }
                }
                break;
            }
            case '5':
            case ' ':
            {
                break;
            }
            case 'f':
            {
                char xStr[5];
                char yStr[5];
                mvprintw(21, 0, "What is the X of your destination? (-200 - 200)");
                getstr(xStr);
                refresh();
                mvprintw(21, 0, "What is the Y of your destination? (-200 - 200)");
                getstr(yStr);
                int realX = atoi(xStr) + 200;
                int realY = atoi(yStr) + 200;
                if (realX <= 400 && realX >= 0) {
                    if (realY <= 400 && realY >= 0){
                        m->characterMap[myWorld.player.playerY][myWorld.player.playerX] = 'X';
                        if (myWorld.worldMap[realY][realX] == NULL){
                            myWorld.worldMap[realY][realX] = (map_t *) malloc(sizeof (map_t));
                            buildMap(myWorld.worldMap[realY][realX], realY, realX, 'x');
                            generateCostMap(myWorld.worldMap[realY][realX], 'H');
                            generateCostMap(myWorld.worldMap[realY][realX], 'R');
                        }
                        else {
                            myWorld.player.playerY = myWorld.worldMap[realY][realX]->centerEntranceY;
                            myWorld.player.playerX = myWorld.worldMap[realY][realX]->centerEntranceX;
                            myWorld.worldMap[realY][realX]->characterMap[myWorld.player.playerY][myWorld.player.playerX] = '@';
                            printMap(*myWorld.worldMap[realY][realX]);
                        }
                        myWorld.player.worldX = realX;
                        myWorld.player.worldY = realY;
                        return 2;
                    }
                }
                break;
            }
            case '\t':
            {   
                BAGOPEN:
                int exit = 0;
                w = newwin(19, 39, 1, 40);
                box(w, 0, 0);
                mvwprintw(w, 1, 1, "Money: $%d", myWorld.player.money);
                mvwprintw(w, 2, 1, "Press p to see pokemon");
                mvwprintw(w, 3, 1, "Press b to open bag");
                mvwprintw(w, 4, 1, "Press x to view box");
                mvwprintw(w, 5, 1, "Press s to save");
                mvwprintw(w, 6, 1, "Press esc to exit");
                wrefresh(w);
                int input = getch();
                while (input != 'p' && input != 'b' && input != 'x' && input != 's' && input != 27){
                    input = getch();
                }
                if (input == 'p'){
                    POKEOPEN:
                    WINDOW *temp;
                    temp = newwin(19, 39, 1, 40);
                    box(temp, 0, 0);
                    wrefresh(temp);
                    mvwprintw(temp, 1, 1, "Pokemon:");
                    mvwprintw(temp, 2, 1, "Press s to swap Pokemon.");
                    mvwprintw(temp, 2, 31, "HP:");
                    for (int i = 0; i < myWorld.player.pokemon.size(); i++){
                        mvwprintw(temp, i + 3, 1, "Level %d %s", myWorld.player.pokemon[i].experience.level, myWorld.player.pokemon[i].pokemon.name.c_str());
                        mvwprintw(temp, i + 3, 31, "%d/%d", myWorld.player.pokemon[i].extraInfo.currentHP, myWorld.player.pokemon[i].stats[0]);
                    }
                    wrefresh(temp);
                    int tempInput = getch();
                    while (tempInput != 27 && tempInput != 's'){
                        tempInput = getch();
                    }
                    if (tempInput == 27){
                        delwin(temp);
                    }
                    else {
                        wclear(temp);
                        box(temp, 0, 0);
                        mvwprintw(temp, 1, 1, "Give two numbers to switch.");
                        for (int i = 0; i < myWorld.player.pokemon.size(); i++){
                            mvwprintw(temp, i + 2, 1, "(%d) %s        %d/%d", i + 1, myWorld.player.pokemon[i].pokemon.name.c_str(), myWorld.player.pokemon[i].extraInfo.currentHP, myWorld.player.pokemon[i].stats[0]);
                        }
                        wrefresh(temp);
                        tempInput = getch();
                        while (tempInput != 27 && tempInput != '1' && tempInput != '2' && tempInput != '3' && tempInput != '4' && tempInput != '5' && tempInput != '6'){
                            tempInput = getch();
                        }
                        if (tempInput == 27){
                            delwin(temp);
                            goto BAGOPEN;
                        }
                        int tempInput2 = getch();
                        while (tempInput != 27 && tempInput != '1' && tempInput != '2' && tempInput != '3' && tempInput != '4' && tempInput != '5' && tempInput != '6'){
                            tempInput = getch();
                        }
                        if (tempInput2 == 27){
                            delwin(temp);
                            goto BAGOPEN;
                        }
                        else {
                            if ((tempInput - 49) < myWorld.player.pokemon.size() && (tempInput2 - 49) < myWorld.player.pokemon.size()){
                                std::vector<actualPokemon_t> holder;
                                for (int i = 0; i < myWorld.player.pokemon.size(); i++){
                                    holder.push_back(myWorld.player.pokemon[i]);
                                }
                                myWorld.player.pokemon.clear();
                                for (int i = 0; i < holder.size(); i++){
                                    if ((tempInput - 49) == i){
                                        myWorld.player.pokemon.push_back(holder[tempInput2 - 49]);
                                    }
                                    else if ((tempInput2 - 49) == i){
                                        myWorld.player.pokemon.push_back(holder[tempInput - 49]);
                                    }
                                    else {
                                        myWorld.player.pokemon.push_back(holder[i]);
                                    }
                                }
                                holder.clear();
                                delwin(temp);
                                goto POKEOPEN;
                            }
                            else {
                                delwin(temp);
                                goto POKEOPEN;
                            }
                        }
                    }
                    
                }
                else if (input == 'b'){
                    WINDOW *temp;
                    temp = newwin(19, 39, 1, 40);
                    box(temp, 0, 0);
                    wrefresh(temp);
                    mvwprintw(temp, 3, 1, "(1) Poke Balls: %d", myWorld.player.bag.count[0]);
                    mvwprintw(temp, 4, 1, "(2) Great Balls: %d", myWorld.player.bag.count[1]);
                    mvwprintw(temp, 5, 1, "(3) Ultra Balls: %d", myWorld.player.bag.count[2]);
                    mvwprintw(temp, 6, 1, "(4) Potions: %d", myWorld.player.bag.count[3]);
                    mvwprintw(temp, 7, 1, "(5) Super Potions: %d", myWorld.player.bag.count[4]);
                    mvwprintw(temp, 8, 1, "(6) Hyper Potions: %d", myWorld.player.bag.count[5]);
                    mvwprintw(temp, 9, 1, "(7) Revives: %d", myWorld.player.bag.count[6]);
                    mvwprintw(temp, 10, 1, "(8) Full Revives: %d", myWorld.player.bag.count[7]);
                    mvwprintw(temp, 1, 1, "Press 1, 2, 3... to");
                    mvwprintw(temp, 2, 1, "use the respective item");
                    wrefresh(temp);
                    int tempInput = getch();
                    while (tempInput != '1' && tempInput != '2' && tempInput != '3' && tempInput != '4' 
                    && tempInput != '5' && tempInput != '6' && tempInput != '7' && tempInput != '8' && tempInput != 27){
                        tempInput = getch();
                    }
                    if (tempInput == '1' || tempInput == '2' || tempInput == '3'){
                        wclear(temp);
                        box(temp, 0, 0);
                        mvwprintw(temp, 1, 1, "Cannot be used right now.");
                        mvwprintw(temp, 2, 1, "Press ESC");
                        wrefresh(temp);
                        int goOn = getch();
                            while (goOn != 27){
                                goOn = getch();
                            }
                        delwin(temp);
                    }
                    else if (tempInput == '4' || tempInput == '5' || tempInput == '6'){
                        POTIONTIME:
                        WINDOW *tempt = newwin(19, 39, 1, 40);
                        box(tempt, 0, 0);
                        wrefresh(tempt);
                        if (myWorld.player.bag.count[tempInput - 49] == 0){
                            mvwprintw(tempt, 1, 1, "You have no more left!");
                            mvwprintw(tempt, 2, 1, "Go to a PokeMart to buy more.");
                            wrefresh(tempt);
                            int goOn = getch();
                            while (goOn != 27){
                                goOn = getch();
                            }
                            wclear(tempt);
                            delwin(tempt);
                            goto BAGOPEN;
                        }
                        mvwprintw(tempt, 1, 1, "Who to use on? (1, 2, 3...)");
                        mvwprintw(tempt, 2, 1, "Pokemon:");
                        mvwprintw(tempt, 2, 31, "HP:");
                        for (int i = 0; i < myWorld.player.pokemon.size(); i++){
                            mvwprintw(tempt, i + 3, 1, "(%d) %s", i+1, myWorld.player.pokemon[i].pokemon.name.c_str());
                            mvwprintw(tempt, i + 3, 31, "%d/%d", myWorld.player.pokemon[i].extraInfo.currentHP, myWorld.player.pokemon[i].stats[0]);
                        }
                        wrefresh(tempt);
                        int temptInput = getch();
                        while (temptInput != '1' && temptInput != '2' && temptInput != '3' && temptInput != '4' && temptInput != '5' && temptInput != '6' && temptInput != 27){
                            temptInput = getch();
                        }
                        bool potionWorked = false;
                        if (temptInput == '1'){
                            if (myWorld.player.pokemon[0].extraInfo.currentHP > 0 && myWorld.player.pokemon[0].extraInfo.currentHP < myWorld.player.pokemon[0].stats[0]){
                                potionWorked = true;
                                myWorld.player.pokemon[0].extraInfo.currentHP = min(myWorld.player.pokemon[0].extraInfo.currentHP + myWorld.player.bag.effect[tempInput - 49], myWorld.player.pokemon[0].stats[0]);
                                mvwprintw(tempt, 3, 1, "%s         %d/%d", myWorld.player.pokemon[0].pokemon.name.c_str(), myWorld.player.pokemon[0].extraInfo.currentHP, myWorld.player.pokemon[0].stats[0]);
                            }
                        }
                        else if (temptInput == '2'){
                            if (myWorld.player.pokemon.size() > 1 && myWorld.player.pokemon[1].extraInfo.currentHP > 0 && myWorld.player.pokemon[1].extraInfo.currentHP < myWorld.player.pokemon[1].stats[0]){
                                potionWorked = true;
                                myWorld.player.pokemon[1].extraInfo.currentHP = min(myWorld.player.pokemon[1].extraInfo.currentHP + myWorld.player.bag.effect[tempInput - 49], myWorld.player.pokemon[1].stats[0]);
                                mvwprintw(tempt, 4, 1, "%s         %d/%d", myWorld.player.pokemon[1].pokemon.name.c_str(), myWorld.player.pokemon[1].extraInfo.currentHP, myWorld.player.pokemon[1].stats[0]);
                            }
                        }
                        else if (temptInput == '3'){
                            if (myWorld.player.pokemon.size() > 2 && myWorld.player.pokemon[2].extraInfo.currentHP > 0 && myWorld.player.pokemon[2].extraInfo.currentHP < myWorld.player.pokemon[2].stats[0]){
                                potionWorked = true;
                                myWorld.player.pokemon[2].extraInfo.currentHP = min(myWorld.player.pokemon[2].extraInfo.currentHP + myWorld.player.bag.effect[tempInput - 49], myWorld.player.pokemon[2].stats[0]);
                                mvwprintw(tempt, 5, 1, "%s         %d/%d", myWorld.player.pokemon[2].pokemon.name.c_str(), myWorld.player.pokemon[2].extraInfo.currentHP, myWorld.player.pokemon[2].stats[0]);
                            }
                        }
                        else if (temptInput == '4'){
                            if (myWorld.player.pokemon.size() > 3 && myWorld.player.pokemon[3].extraInfo.currentHP > 0 && myWorld.player.pokemon[3].extraInfo.currentHP < myWorld.player.pokemon[3].stats[0]){
                                potionWorked = true;
                                myWorld.player.pokemon[3].extraInfo.currentHP = min(myWorld.player.pokemon[3].extraInfo.currentHP + myWorld.player.bag.effect[tempInput - 49], myWorld.player.pokemon[3].stats[0]);
                                mvwprintw(tempt, 6, 1, "%s         %d/%d", myWorld.player.pokemon[3].pokemon.name.c_str(), myWorld.player.pokemon[3].extraInfo.currentHP, myWorld.player.pokemon[3].stats[0]);
                            }
                        }
                        else if (temptInput == '5'){
                            if (myWorld.player.pokemon.size() > 4 && myWorld.player.pokemon[4].extraInfo.currentHP > 0 && myWorld.player.pokemon[4].extraInfo.currentHP < myWorld.player.pokemon[4].stats[0]){
                                potionWorked = true;
                                myWorld.player.pokemon[4].extraInfo.currentHP = min(myWorld.player.pokemon[4].extraInfo.currentHP + myWorld.player.bag.effect[tempInput - 49], myWorld.player.pokemon[4].stats[0]);
                                mvwprintw(tempt, 7, 1, "%s         %d/%d", myWorld.player.pokemon[4].pokemon.name.c_str(), myWorld.player.pokemon[4].extraInfo.currentHP, myWorld.player.pokemon[4].stats[0]);
                            }
                        }
                        else if (temptInput == '6'){
                            if (myWorld.player.pokemon.size() > 5 && myWorld.player.pokemon[5].extraInfo.currentHP > 0 && myWorld.player.pokemon[5].extraInfo.currentHP < myWorld.player.pokemon[5].stats[0]){
                                potionWorked = true;
                                myWorld.player.pokemon[5].extraInfo.currentHP = min(myWorld.player.pokemon[5].extraInfo.currentHP + myWorld.player.bag.effect[tempInput - 49], myWorld.player.pokemon[5].stats[0]);
                                mvwprintw(tempt, 8, 1, "%s         %d/%d", myWorld.player.pokemon[5].pokemon.name.c_str(), myWorld.player.pokemon[5].extraInfo.currentHP, myWorld.player.pokemon[5].stats[0]);
                            }
                        }
                        else {
                            wclear(tempt);
                            delwin(tempt);
                            goto BAGOPEN;
                        }
                        if (potionWorked){
                            myWorld.player.bag.count[tempInput - 49]--;
                            wclear(tempt);
                            delwin(tempt);
                        }
                        else {
                            wclear(tempt);
                            box(tempt, 0, 0);
                            mvwprintw(tempt, 1, 1, "Not a valid choice");
                            mvwprintw(tempt, 2, 1, "Press ESC");
                            wrefresh(tempt);
                            int goOn = getch();
                            while (goOn != 27){
                                goOn = getch();
                            }
                            delwin(tempt);
                            goto POTIONTIME;
                        }
                    }
                    else if (tempInput == '7' || tempInput == '8'){
                        REVIVETIME:
                        WINDOW *tempt = newwin(19, 39, 1, 40);
                        box(tempt, 0, 0);
                        wrefresh(tempt);
                        if (myWorld.player.bag.count[tempInput - 49] == 0){
                            mvwprintw(tempt, 1, 1, "You have no more revives!");
                            mvwprintw(tempt, 2, 1, "Go to a PokeMart to buy more.");
                            wrefresh(tempt);
                            int goOn = getch();
                            while (goOn != 27){
                                goOn = getch();
                            }
                            wclear(tempt);
                            delwin(tempt);
                            goto BAGOPEN;
                        }
                        mvwprintw(tempt, 1, 1, "Who to use on? (1, 2, 3...)");
                        mvwprintw(tempt, 2, 1, "Pokemon:");
                        mvwprintw(tempt, 2, 31, "HP:");
                        for (int i = 0; i < myWorld.player.pokemon.size(); i++){
                            mvwprintw(tempt, i + 3, 1, "(%d) %s", i+1, myWorld.player.pokemon[i].pokemon.name.c_str());
                            mvwprintw(tempt, i + 3, 31, "%d/%d", myWorld.player.pokemon[i].extraInfo.currentHP, myWorld.player.pokemon[i].stats[0]);
                        }
                        wrefresh(tempt);
                        int temptInput = getch();
                        while (temptInput != '1' && temptInput != '2' && temptInput != '3' && temptInput != '4' && temptInput != '5' && temptInput != '6' && temptInput != 27){
                            temptInput = getch();
                        }
                        bool reviveWorked = false;
                        if (temptInput == '1'){
                            if (myWorld.player.pokemon[0].extraInfo.currentHP == 0){
                            reviveWorked = true;
                            myWorld.player.pokemon[0].extraInfo.currentHP = myWorld.player.pokemon[0].stats[0] * myWorld.player.bag.effect[tempInput - 49];
                            mvwprintw(tempt, 3, 1, "%s         %d/%d", myWorld.player.pokemon[0].pokemon.name.c_str(), myWorld.player.pokemon[0].extraInfo.currentHP, myWorld.player.pokemon[0].stats[0]);
                            }
                        }
                        else if (temptInput == '2'){
                            if (myWorld.player.pokemon.size() > 1 && myWorld.player.pokemon[1].extraInfo.currentHP == 0){
                                reviveWorked = true;
                                myWorld.player.pokemon[1].extraInfo.currentHP = myWorld.player.pokemon[1].stats[0] * myWorld.player.bag.effect[tempInput - 49];
                                mvwprintw(tempt, 4, 1, "%s         %d/%d", myWorld.player.pokemon[1].pokemon.name.c_str(), myWorld.player.pokemon[1].extraInfo.currentHP, myWorld.player.pokemon[1].stats[0]);
                            }
                        }
                        else if (temptInput == '3'){
                            if (myWorld.player.pokemon.size() > 2 && myWorld.player.pokemon[2].extraInfo.currentHP == 0){
                                reviveWorked = true;
                                myWorld.player.pokemon[2].extraInfo.currentHP = myWorld.player.pokemon[2].stats[0] * myWorld.player.bag.effect[tempInput - 49];
                                mvwprintw(tempt, 5, 1, "%s         %d/%d", myWorld.player.pokemon[2].pokemon.name.c_str(), myWorld.player.pokemon[2].extraInfo.currentHP, myWorld.player.pokemon[2].stats[0]);
                            }
                        }
                        else if (temptInput == '4'){
                            if (myWorld.player.pokemon.size() > 3 && myWorld.player.pokemon[3].extraInfo.currentHP == 0){
                                reviveWorked = true;
                                myWorld.player.pokemon[3].extraInfo.currentHP = myWorld.player.pokemon[3].stats[0] * myWorld.player.bag.effect[tempInput - 49];
                                mvwprintw(tempt, 6, 1, "%s         %d/%d", myWorld.player.pokemon[3].pokemon.name.c_str(), myWorld.player.pokemon[3].extraInfo.currentHP, myWorld.player.pokemon[3].stats[0]);
                            }
                        }
                        else if (temptInput == '5'){
                            if (myWorld.player.pokemon.size() > 4 && myWorld.player.pokemon[4].extraInfo.currentHP == 0){
                                reviveWorked = true;
                                myWorld.player.pokemon[4].extraInfo.currentHP = myWorld.player.pokemon[4].stats[0] * myWorld.player.bag.effect[tempInput - 49];
                                mvwprintw(tempt, 7, 1, "%s         %d/%d", myWorld.player.pokemon[4].pokemon.name.c_str(), myWorld.player.pokemon[4].extraInfo.currentHP, myWorld.player.pokemon[4].stats[0]);
                            }
                        }
                        else if (temptInput == '6'){
                            if (myWorld.player.pokemon.size() > 5 && myWorld.player.pokemon[5].extraInfo.currentHP == 0){
                                reviveWorked = true;
                                myWorld.player.pokemon[5].extraInfo.currentHP = myWorld.player.pokemon[5].stats[0] * myWorld.player.bag.effect[tempInput - 49];
                                mvwprintw(tempt, 8, 1, "%s         %d/%d", myWorld.player.pokemon[5].pokemon.name.c_str(), myWorld.player.pokemon[5].extraInfo.currentHP, myWorld.player.pokemon[5].stats[0]);
                            }
                        }
                        else {
                            wclear(tempt);
                            delwin(tempt);
                            goto BAGOPEN;
                        }
                        if (reviveWorked){
                            myWorld.player.bag.count[tempInput - 49]--;
                            wclear(tempt);
                            delwin(tempt);
                        }
                        else {
                            wclear(tempt);
                            box(tempt, 0, 0);
                            mvwprintw(tempt, 1, 1, "That didn't work!");
                            mvwprintw(tempt, 2, 1, "Press ESC");
                            wrefresh(tempt);
                            int goOn = getch();
                            while (goOn != 27){
                                goOn = getch();
                            }
                            delwin(tempt);
                            goto REVIVETIME;
                        }
                    }
                    delwin(temp);
                }
                else if (input == 'x'){
                    BOXVIEW:
                    WINDOW *temp;
                    int i = 0;
                    int page = 1;
                    temp = newwin(19, 39, 1, 40);
                    box(temp, 0, 0);
                    wrefresh(temp);
                    PAGING:
                    mvwprintw(temp, 1, 1, "Press s to swap/withdraw.");
                    mvwprintw(temp, 2, 1, "Press d to deposit, <- -> for paging");
                    for (i = i; i < myWorld.player.boxPokemon.size() && i < 15 * page; i++){
                        mvwprintw(temp, (i % 15) + 3, 1, "(%d) Level %d %s", (i % 15) + 1, myWorld.player.boxPokemon[i].experience.level, myWorld.player.boxPokemon[i].pokemon.name.c_str());
                    }
                    wrefresh(temp);
                    int tempt = getch();
                    while (tempt != KEY_RIGHT && tempt != KEY_LEFT && tempt != 's' && tempt != 'd' && tempt != 27){
                        tempt = getch();
                    }
                    if (tempt == KEY_RIGHT && myWorld.player.boxPokemon.size() > i){
                        page++;
                        wclear(temp);
                        box(temp, 0, 0);
                        goto PAGING;
                    }
                    else if (tempt == KEY_LEFT && i > 15){
                        page = max(1, page - 1);
                        wclear(temp);
                        box(temp, 0, 0);
                        i -= min(32, myWorld.player.boxPokemon.size());
                        goto PAGING;
                    }
                    else if (tempt == 's'){
                        WINDOW *playerPoke;
                        playerPoke = newwin(19, 39, 1, 1);
                        box(playerPoke, 0, 0);
                        mvwprintw(playerPoke, 1, 1, "Who to swap/withdraw?");
                        mvwprintw(playerPoke, 2, 1, "Type box # first then press enter");
                        for (int j = 0; j < myWorld.player.pokemon.size(); j++){
                            mvwprintw(playerPoke, j+4, 1, "(%d) Level %d %s", j+1, myWorld.player.pokemon[j].experience.level, myWorld.player.pokemon[j].pokemon.name.c_str());
                        }
                        wrefresh(playerPoke);
                        char pokeBoxChar[4];
                        getstr(pokeBoxChar);
                        int pokeBox = atoi(pokeBoxChar);
                        while (pokeBox < 1 || pokeBox > i){
                            getstr(pokeBoxChar);
                            pokeBox = atoi(pokeBoxChar);
                        }
                        if (myWorld.player.pokemon.size() < 6){
                            myWorld.player.pokemon.push_back(myWorld.player.boxPokemon[pokeBox + (15 * (page - 1)) - 1]);
                            myWorld.player.boxPokemon.erase(myWorld.player.boxPokemon.begin() + pokeBox + (15 * (page - 1)) - 1);
                            wclear(playerPoke);
                            wrefresh(playerPoke);
                            delwin(playerPoke);
                            delwin(temp);
                            refresh();
                            goto BOXVIEW;
                        }
                        mvwprintw(playerPoke, 3, 1, "Now press the pokemon #");
                        wrefresh(playerPoke);
                        int playerPokeNum = getch();
                        while (playerPokeNum - 49 > myWorld.player.pokemon.size() || playerPokeNum - 49 < 0 && playerPokeNum != 27){
                            playerPokeNum = getch();
                        }
                        if (playerPokeNum == 27){
                            wclear(playerPoke);
                            delwin(playerPoke);
                            goto BAGOPEN;
                        }
                        std::vector<actualPokemon_t> holder;
                        for (int j = 0; j < myWorld.player.pokemon.size(); j++){
                            holder.push_back(myWorld.player.pokemon[j]);
                        }
                        myWorld.player.pokemon.clear();
                        for (int j = 0; j < holder.size(); j++){
                            if (j == (playerPokeNum - 49)){
                                myWorld.player.pokemon.push_back(myWorld.player.boxPokemon[pokeBox + (15 * (page - 1)) - 1]);
                            }
                            else {
                                myWorld.player.pokemon.push_back(holder[j]);
                            }
                        }
                        myWorld.player.boxPokemon.erase(myWorld.player.boxPokemon.begin() + pokeBox + (15 * (page - 1)) - 1);
                        myWorld.player.boxPokemon.push_back(holder[playerPokeNum - 49]);
                        //this will not delete and i cant figure out why
                        wclear(playerPoke);
                        wrefresh(playerPoke);
                        delwin(playerPoke);
                        delwin(temp);
                        refresh();
                        goto BOXVIEW;
                    }
                    else if (tempt == 'd'){
                        wclear(temp);
                        box(temp, 0, 0);
                        mvwprintw(temp, 1, 1, "Who to deposit?");
                        for (int i = 0; i < myWorld.player.pokemon.size(); i++){
                            mvwprintw(temp, i + 2, 1, "(%d) Level %d %s", i + 1, myWorld.player.pokemon[i].experience.level, myWorld.player.pokemon[i].pokemon.name.c_str());
                        }
                        wrefresh(temp);
                        int depNum = getch();
                        while (depNum != '1' && depNum != '2' && depNum != '3' && depNum != '4' && depNum != '5' && depNum != '6' && depNum != 27){
                            depNum = getch();
                        }
                        if ((depNum - 49) < myWorld.player.pokemon.size() && myWorld.player.pokemon.size() > 1){
                            myWorld.player.boxPokemon.push_back(myWorld.player.pokemon[depNum - 49]);
                            myWorld.player.pokemon.erase(myWorld.player.pokemon.begin() + depNum - 49);
                            wclear(temp);
                            delwin(temp);
                            goto BOXVIEW;
                        }
                        else {
                            wclear(temp);
                            delwin(temp);
                            goto BOXVIEW;
                        }

                    }
                    else if (tempt == KEY_RIGHT || tempt == KEY_LEFT){
                        wclear(temp);
                        box(temp, 0, 0);
                        i = max(0, i - 15);
                        goto PAGING;
                    }

                }
                else if (input == 's'){
                    WINDOW *temp;
                    int goOn = 0;
                    temp = newwin(19, 39, 1, 40);
                    box(temp, 0, 0);
                    wrefresh(temp);
                    mvwprintw(temp, 1, 1, "Save Slot 1");
                    mvwprintw(temp, 2, 1, "Save Slot 2");
                    mvwprintw(temp, 3, 1, "Save Slot 3");
                    mvwprintw(temp, 4, 1, "Save Slot 4");
                    mvwprintw(temp, 6, 1, "Choose a save slot");
                    wrefresh(temp);
                    int saveSlot = getch();
                    while (saveSlot != '1' && saveSlot != '2' && saveSlot != '3' && saveSlot != '4') {
                        saveSlot = getch();
                    }
                    writeSave(saveSlot);
                    wclear(temp);
                    box(temp, 0, 0);
                    mvwprintw(temp, 3, 1, "Game Saved!");
                    mvwprintw(temp, 4, 1, "Press ESC");
                    wrefresh(temp);
                    while (goOn != 27){
                        goOn = getch();
                    }
                    wclear(temp);
                    delwin(temp);
                    goto BAGOPEN;
                }
                else {
                    wclear(w);
                    delwin(w);
                    refresh();
                    break;
                }
                delwin(w);
                goto BAGOPEN;
            }
            case 't':
            {
                int exit = 0;
                w = create_newwin(30, 8);
                mvprintw(1, 1, "PRESS ESC TO CLOSE");
                refresh();
                distanceFromPlayer('h', m->trainers.hikerX, m->trainers.hikerY, 2);
                distanceFromPlayer('r', m->trainers.rivalX, m->trainers.rivalY, 3);
                distanceFromPlayer('p', m->trainers.pace1X, m->trainers.pace1Y, 4);
                distanceFromPlayer('p', m->trainers.pace2X, m->trainers.pace2Y, 5);
                distanceFromPlayer('w', m->trainers.wand1X, m->trainers.wand1Y, 6);
                
                while(exit != 27){
                    exit = getch();
                    if (exit == KEY_UP){
                        w = create_newwin(30, 8);
                        mvprintw(1, 1, "PRESS ESC TO CLOSE");
                        refresh();
                        distanceFromPlayer('h', m->trainers.hikerX, m->trainers.hikerY, 2);
                        distanceFromPlayer('r', m->trainers.rivalX, m->trainers.rivalY, 3);
                        distanceFromPlayer('p', m->trainers.pace1X, m->trainers.pace1Y, 4);
                        distanceFromPlayer('p', m->trainers.pace2X, m->trainers.pace2Y, 5);
                        distanceFromPlayer('w', m->trainers.wand1X, m->trainers.wand1Y, 6);
                    }
                    if (exit == KEY_DOWN){
                        w = create_newwin(30, 8);
                        mvprintw(1, 1, "PRESS ESC TO CLOSE");
                        refresh();
                        distanceFromPlayer('e', m->trainers.explorer1X, m->trainers.explorer1Y, 2);
                        distanceFromPlayer('m', m->trainers.swim1X, m->trainers.swim1Y, 3);
                        distanceFromPlayer('m', m->trainers.swim2X, m->trainers.swim2Y, 4);
                        distanceFromPlayer('s', m->trainers.sentry1X, m->trainers.sentry1Y, 5);
                        distanceFromPlayer('s', m->trainers.sentry2X, m->trainers.sentry2Y, 6);
                    }
                }
                delwin(w);
                break;
            }
            case 'q':
            {
                return 0;
            }
        }
        generateCostMap(myWorld.worldMap[worldY][worldX], 'H');
        generateCostMap(myWorld.worldMap[worldY][worldX], 'R');

    }
    else if (c == 'h'){
        if (m->trainers.hikerDef == 1){
            defeatedMovement(m, 'h', &m->trainers.hikerY, &m->trainers.hikerX);
        }
        else {
            int dirH = trainerMoveHelper(m, m->trainers.hikerX, m->trainers.hikerY, 'H');
            if (dirH == 0){
                m->characterMap[m->trainers.hikerY][m->trainers.hikerX] = 'X';
                m->characterMap[m->trainers.hikerY - 1][m->trainers.hikerX - 1] = 'h';
                m->trainers.hikerY = m->trainers.hikerY - 1;
                m->trainers.hikerX = m->trainers.hikerX - 1;
            }
            else if (dirH == 1){
                m->characterMap[m->trainers.hikerY][m->trainers.hikerX] = 'X';
                m->characterMap[m->trainers.hikerY - 1][m->trainers.hikerX] = 'h';
                m->trainers.hikerY = m->trainers.hikerY - 1;
            }
            else if (dirH == 2){
                m->characterMap[m->trainers.hikerY][m->trainers.hikerX] = 'X';
                m->characterMap[m->trainers.hikerY - 1][m->trainers.hikerX + 1] = 'h';
                m->trainers.hikerY = m->trainers.hikerY - 1;
                m->trainers.hikerX = m->trainers.hikerX + 1;
            }
            else if (dirH == 3){
                m->characterMap[m->trainers.hikerY][m->trainers.hikerX] = 'X';
                m->characterMap[m->trainers.hikerY][m->trainers.hikerX - 1] = 'h';
                m->trainers.hikerX = m->trainers.hikerX - 1;
            }
            else if (dirH == 4){
                m->characterMap[m->trainers.hikerY][m->trainers.hikerX] = 'X';
                m->characterMap[m->trainers.hikerY][m->trainers.hikerX + 1] = 'h';
                m->trainers.hikerX = m->trainers.hikerX + 1;
            }
            else if (dirH == 5){
                m->characterMap[m->trainers.hikerY][m->trainers.hikerX] = 'X';
                m->characterMap[m->trainers.hikerY + 1][m->trainers.hikerX - 1] = 'h';
                m->trainers.hikerY = m->trainers.hikerY + 1;
                m->trainers.hikerX = m->trainers.hikerX - 1;
            }
            else if (dirH == 6){
                m->characterMap[m->trainers.hikerY][m->trainers.hikerX] = 'X';
                m->characterMap[m->trainers.hikerY + 1][m->trainers.hikerX] = 'h';
                m->trainers.hikerY = m->trainers.hikerY + 1;
            }
            else if (dirH == 7){
                m->characterMap[m->trainers.hikerY][m->trainers.hikerX] = 'X';
                m->characterMap[m->trainers.hikerY + 1][m->trainers.hikerX + 1] = 'h';
                m->trainers.hikerY = m->trainers.hikerY + 1;
                m->trainers.hikerX = m->trainers.hikerX + 1;
            }
        }
    }
    else if (c == 'r'){
        if (m->trainers.rivalDef == 1){
            defeatedMovement(m, 'r', &m->trainers.rivalY, &m->trainers.rivalX);
        }
        else {
            int dirR = trainerMoveHelper(m, m->trainers.rivalX, m->trainers.rivalY, 'R');
            if (dirR == 0){
                m->characterMap[m->trainers.rivalY][m->trainers.rivalX] = 'X';
                m->characterMap[m->trainers.rivalY - 1][m->trainers.rivalX - 1] = 'r';
                m->trainers.rivalY = m->trainers.rivalY - 1;
                m->trainers.rivalX = m->trainers.rivalX - 1;
            }
            else if (dirR == 1){
                m->characterMap[m->trainers.rivalY][m->trainers.rivalX] = 'X';
                m->characterMap[m->trainers.rivalY - 1][m->trainers.rivalX] = 'r';
                m->trainers.rivalY = m->trainers.rivalY - 1;
            }
            else if (dirR == 2){
                m->characterMap[m->trainers.rivalY][m->trainers.rivalX] = 'X';
                m->characterMap[m->trainers.rivalY - 1][m->trainers.rivalX + 1] = 'r';
                m->trainers.rivalY = m->trainers.rivalY - 1;
                m->trainers.rivalX = m->trainers.rivalX + 1;
            }
            else if (dirR == 3){
                m->characterMap[m->trainers.rivalY][m->trainers.rivalX] = 'X';
                m->characterMap[m->trainers.rivalY][m->trainers.rivalX - 1] = 'r';
                m->trainers.rivalX = m->trainers.rivalX - 1;
            }
            else if (dirR == 4){
                m->characterMap[m->trainers.rivalY][m->trainers.rivalX] = 'X';
                m->characterMap[m->trainers.rivalY][m->trainers.rivalX + 1] = 'r';
                m->trainers.rivalX = m->trainers.rivalX + 1;
            }
            else if (dirR == 5){
                m->characterMap[m->trainers.rivalY][m->trainers.rivalX] = 'X';
                m->characterMap[m->trainers.rivalY + 1][m->trainers.rivalX - 1] = 'r';
                m->trainers.rivalY = m->trainers.rivalY + 1;
                m->trainers.rivalX = m->trainers.rivalX - 1;
            }
            else if (dirR == 6){
                m->characterMap[m->trainers.rivalY][m->trainers.rivalX] = 'X';
                m->characterMap[m->trainers.rivalY + 1][m->trainers.rivalX] = 'r';
                m->trainers.rivalY = m->trainers.rivalY + 1;
            }
            else if (dirR == 7){
                m->characterMap[m->trainers.rivalY][m->trainers.rivalX] = 'X';
                m->characterMap[m->trainers.rivalY + 1][m->trainers.rivalX + 1] = 'r';
                m->trainers.rivalY = m->trainers.rivalY + 1;
                m->trainers.rivalX = m->trainers.rivalX + 1;
            }
        }
    }
    
    
    //swimmers
    else if(c == 'm') {
        if (m->singleMap[m->trainers.swim1Y][m->trainers.swim1X + 1] == '~' && *swimLeft == 0 && m->characterMap[m->trainers.swim1Y][m->trainers.swim1X + 1] == 'X'){
            m->characterMap[m->trainers.swim1Y][m->trainers.swim1X] = 'X';
            m->characterMap[m->trainers.swim1Y][m->trainers.swim1X + 1] = 'm';
            m->trainers.swim1X++;
        }
        else if (m->characterMap[m->trainers.swim1Y][m->trainers.swim1X + 1] == '@'){
            if (npcDefeated(m, 'm', m->trainers.swim1Y, m->trainers.swim1X) == 0){
                npcKill(m, 'm', m->trainers.swim1Y, m->trainers.swim1X);
                int exit = 0;
                w = create_newwin(80, 24);
                getVoiceLine(w, m, 'm', m->trainers.swim1Y, m->trainers.swim1X, 'n', '.');
                delwin(w);
            }
            else {
                int exit = 0;
                w = create_newwin(80, 24);
                getVoiceLine(w, m, 'm', m->trainers.swim1Y, m->trainers.swim1X, 'd', '.');
                delwin(w);
            }
        }
        else if (m->singleMap[m->trainers.swim1Y][m->trainers.swim1X + 1] != '~'){
            *swimLeft = 1;
        }
        if (m->singleMap[m->trainers.swim1Y][m->trainers.swim1X - 1] == '~' && *swimLeft == 1 && m->characterMap[m->trainers.swim1Y][m->trainers.swim1X - 1] == 'X'){
            m->characterMap[m->trainers.swim1Y][m->trainers.swim1X] = 'X';
            m->characterMap[m->trainers.swim1Y][m->trainers.swim1X - 1] = 'm';
            m->trainers.swim1X--;
        }
        else if (m->characterMap[m->trainers.swim1Y][m->trainers.swim1X - 1] == '@'){
            if (npcDefeated(m, 'm', m->trainers.swim1Y, m->trainers.swim1X) == 0){
                npcKill(m, 'm', m->trainers.swim1Y, m->trainers.swim1X);
                int exit = 0;
                w = create_newwin(80, 24);
                getVoiceLine(w, m, 'm', m->trainers.swim1Y, m->trainers.swim1X, 'n', '.');
                delwin(w);
            }
            else {
                int exit = 0;
                w = create_newwin(80, 24);
                getVoiceLine(w, m, 'm', m->trainers.swim1Y, m->trainers.swim1X, 'd', '.');
                delwin(w);
            }
        }
        else if (m->singleMap[m->trainers.swim1Y][m->trainers.swim1X - 1] != '~'){
            *swimLeft = 0;
        }

        if (m->singleMap[m->trainers.swim2Y - 1][m->trainers.swim2X] == '~' && *swimDown == 0 && m->characterMap[m->trainers.swim2Y - 1][m->trainers.swim2X] == 'X'){
            m->characterMap[m->trainers.swim2Y][m->trainers.swim2X] = 'X';
            m->characterMap[m->trainers.swim2Y - 1][m->trainers.swim2X] = 'm';
            m->trainers.swim2Y--;
        }
        else if (m->characterMap[m->trainers.swim2Y - 1][m->trainers.swim2X] == '@'){
            if (npcDefeated(m, 'm', m->trainers.swim2Y, m->trainers.swim2X) == 0){
                npcKill(m, 'm', m->trainers.swim2Y, m->trainers.swim2X);
                int exit = 0;
                w = create_newwin(80, 24);
                getVoiceLine(w, m, 'm', m->trainers.swim2Y, m->trainers.swim2X, 'n', '.');
                delwin(w);
            }
            else {
                int exit = 0;
                w = create_newwin(80, 24);
                getVoiceLine(w, m, 'm', m->trainers.swim2Y, m->trainers.swim2X, 'd', '.');
                delwin(w);
            }
        }
        else if (m->singleMap[m->trainers.swim2Y - 1][m->trainers.swim2X] != '~'){
            *swimDown = 1;
        }
        if (m->singleMap[m->trainers.swim2Y + 1][m->trainers.swim2X] == '~' && *swimDown == 1 && m->characterMap[m->trainers.swim2Y + 1][m->trainers.swim2X] == 'X'){
            m->characterMap[m->trainers.swim2Y][m->trainers.swim2X] = 'X';
            m->characterMap[m->trainers.swim2Y + 1][m->trainers.swim2X] = 'm';
            m->trainers.swim2Y++;
        }
        else if (m->characterMap[m->trainers.swim2Y + 1][m->trainers.swim2X] == '@'){
            if (npcDefeated(m, 'm', m->trainers.swim2Y, m->trainers.swim2X) == 0){
                npcKill(m, 'm', m->trainers.swim2Y, m->trainers.swim2X);
                int exit = 0;
                w = create_newwin(80, 24);
                getVoiceLine(w, m, 'm', m->trainers.swim2Y, m->trainers.swim2X, 'n', '.');
                delwin(w);
            }
            else {
                int exit = 0;
                w = create_newwin(80, 24);
                getVoiceLine(w, m, 'm', m->trainers.swim2Y, m->trainers.swim2X, 'd', '.');
                delwin(w);
            }
        }
        else if (m->singleMap[m->trainers.swim2Y + 1][m->trainers.swim2X] != '~'){
            *swimDown = 0;
        }
    }

    //pacer1
    else if(c == 'P'){
        if (m->singleMap[m->trainers.pace1Y][m->trainers.pace1X + 1] != '~' && m->singleMap[m->trainers.pace1Y][m->trainers.pace1X + 1] != '^' && 
            m->singleMap[m->trainers.pace1Y][m->trainers.pace1X + 1] != '%' && *paceLeft == 0 && m->characterMap[m->trainers.pace1Y][m->trainers.pace1X + 1] == 'X'){
                m->characterMap[m->trainers.pace1Y][m->trainers.pace1X] = 'X';
                m->characterMap[m->trainers.pace1Y][m->trainers.pace1X + 1] = 'p';
                m->trainers.pace1X++;
        }
        else if (m->characterMap[m->trainers.pace1Y][m->trainers.pace1X + 1] == '@'){
            if (npcDefeated(m, 'p', m->trainers.pace1Y, m->trainers.pace1X) == 0){
                npcKill(m, 'p', m->trainers.pace1Y, m->trainers.pace1X);
                int exit = 0;
                w = create_newwin(80, 24);
                getVoiceLine(w, m, 'p', m->trainers.pace1Y, m->trainers.pace1X, 'n', '.');
                delwin(w);
            }
            else {
                int exit = 0;
                w = create_newwin(80, 24);
                getVoiceLine(w, m, 'p', m->trainers.pace1Y, m->trainers.pace1X, 'd', '.');
                delwin(w);
            }
        }
        //using hiker map to tell if it hit some kind of wall
        else if (myWorld.hikerMap[m->trainers.pace1Y][m->trainers.pace1X + 1] < 0) {
            *paceLeft = 1;
        }
        if (m->singleMap[m->trainers.pace1Y][m->trainers.pace1X - 1] != '~' && m->singleMap[m->trainers.pace1Y][m->trainers.pace1X - 1] != '^' && 
            m->singleMap[m->trainers.pace1Y][m->trainers.pace1X - 1] != '%' && *paceLeft == 1 && m->characterMap[m->trainers.pace1Y][m->trainers.pace1X - 1] == 'X'){
                m->characterMap[m->trainers.pace1Y][m->trainers.pace1X] = 'X';
                m->characterMap[m->trainers.pace1Y][m->trainers.pace1X - 1] = 'p';
                m->trainers.pace1X--;
        }
        else if (m->characterMap[m->trainers.pace1Y][m->trainers.pace1X - 1] == '@'){
            if (npcDefeated(m, 'p', m->trainers.pace1Y, m->trainers.pace1X) == 0){
                npcKill(m, 'p', m->trainers.pace1Y, m->trainers.pace1X);
                int exit = 0;
                w = create_newwin(80, 24);
                getVoiceLine(w, m, 'p', m->trainers.pace1Y, m->trainers.pace1X, 'n', '.');
                delwin(w);
            }
            else {
                int exit = 0;
                w = create_newwin(80, 24);
                getVoiceLine(w, m, 'p', m->trainers.pace1Y, m->trainers.pace1X, 'd', '.');
                delwin(w);
            }
        }
        else if (myWorld.hikerMap[m->trainers.pace1Y][m->trainers.pace1X - 1] < 0) {
            *paceLeft = 0;
        }
    }

    //pace 2
    else if (c == 'p'){
        if (m->singleMap[m->trainers.pace2Y + 1][m->trainers.pace2X] != '~' && m->singleMap[m->trainers.pace2Y + 1][m->trainers.pace2X] != '^' && 
            m->singleMap[m->trainers.pace2Y + 1][m->trainers.pace2X] != '%' && *paceDown == 1 && m->characterMap[m->trainers.pace2Y + 1][m->trainers.pace2X] == 'X'){
                m->characterMap[m->trainers.pace2Y][m->trainers.pace2X] = 'X';
                m->characterMap[m->trainers.pace2Y + 1][m->trainers.pace2X] = 'p';
                m->trainers.pace2Y++;
        }
        else if (m->characterMap[m->trainers.pace2Y + 1][m->trainers.pace2X] == '@'){
            if (npcDefeated(m, 'p', m->trainers.pace2Y, m->trainers.pace2X) == 0){
                npcKill(m, 'p', m->trainers.pace2Y, m->trainers.pace2X);
                int exit = 0;
                w = create_newwin(80, 24);
                getVoiceLine(w, m, 'p', m->trainers.pace2Y, m->trainers.pace2X, 'n', '.');
                delwin(w);
            }
            else {
                int exit = 0;
                w = create_newwin(80, 24);
                getVoiceLine(w, m, 'p', m->trainers.pace2Y, m->trainers.pace2X, 'd', '.');
                delwin(w);
            }
        }
        else if (myWorld.hikerMap[m->trainers.pace2Y + 1][m->trainers.pace2X] < 0) {
            *paceDown = 0;
        }
        if (m->singleMap[m->trainers.pace2Y - 1][m->trainers.pace2X] != '~' && m->singleMap[m->trainers.pace2Y - 1][m->trainers.pace2X] != '^' && 
            m->singleMap[m->trainers.pace2Y - 1][m->trainers.pace2X] != '%' && *paceDown == 0 && m->characterMap[m->trainers.pace2Y - 1][m->trainers.pace2X] == 'X'){
                m->characterMap[m->trainers.pace2Y][m->trainers.pace2X] = 'X';
                m->characterMap[m->trainers.pace2Y - 1][m->trainers.pace2X] = 'p';
                m->trainers.pace2Y--;
        }
        else if (m->characterMap[m->trainers.pace2Y - 1][m->trainers.pace2X] == '@'){
            if (npcDefeated(m, 'p', m->trainers.pace2Y, m->trainers.pace2X) == 0){
                npcKill(m, 'p', m->trainers.pace2Y, m->trainers.pace2X);
                int exit = 0;
                w = create_newwin(80, 24);
                getVoiceLine(w, m, 'p', m->trainers.pace2Y, m->trainers.pace2X, 'n', '.');
                delwin(w);
            }
            else {
                int exit = 0;
                w = create_newwin(80, 24);
                getVoiceLine(w, m, 'p', m->trainers.pace2Y, m->trainers.pace2X, 'd', '.');
                delwin(w);
            }
        }
        else if (myWorld.hikerMap[m->trainers.pace2Y - 1][m->trainers.pace2X] < 0) {
            *paceDown = 1;
        }
    }

    //explorer
    else if (c == 'e') {
        while (1){
            int tempX = rand() % (1 + 1 - 0) + 0;
            int tempY = rand() % (1 + 1 - 0) + 0;
            int negX = rand() % (1 + 1 - 0) + 0;
            int negY = rand() % (1 + 1 - 0) + 0;
            if (!(tempX == 0 && tempY == 0)){
                if (negX == 0){
                    if (negY == 0){
                        if (myWorld.hikerMap[m->trainers.explorer1Y + tempY][m->trainers.explorer1X + tempX] >= 0 && myWorld.hikerMap[m->trainers.explorer1Y + tempY][m->trainers.explorer1X + tempX] != INT_MAX
                        && m->characterMap[m->trainers.explorer1Y + tempY][m->trainers.explorer1X + tempX] == 'X'){
                            m->characterMap[m->trainers.explorer1Y + tempY][m->trainers.explorer1X + tempX] = 'e';
                            m->characterMap[m->trainers.explorer1Y][m->trainers.explorer1X] = 'X';
                            m->trainers.explorer1X += tempX;
                            m->trainers.explorer1Y += tempY;
                            break;
                        }
                        else if (m->characterMap[m->trainers.explorer1Y + tempY][m->trainers.explorer1X + tempX] == '@'){
                            if (npcDefeated(m, 'e', m->trainers.explorer1Y, m->trainers.explorer1X) == 0){
                                npcKill(m, 'e', m->trainers.explorer1Y, m->trainers.explorer1X);
                                int exit = 0;
                                w = create_newwin(80, 24);
                                getVoiceLine(w, m, 'e', m->trainers.explorer1Y, m->trainers.explorer1X, 'n', '.');
                                delwin(w);
                            }
                            else {
                                int exit = 0;
                                w = create_newwin(80, 24);
                                getVoiceLine(w, m, 'e', m->trainers.explorer1Y, m->trainers.explorer1X, 'd', '.');
                                delwin(w);
                            }
                        }
                    }
                    else if (negY == 1){
                        if (myWorld.hikerMap[m->trainers.explorer1Y - tempY][m->trainers.explorer1X + tempX] >= 0 && myWorld.hikerMap[m->trainers.explorer1Y - tempY][m->trainers.explorer1X + tempX] != INT_MAX
                        && m->characterMap[m->trainers.explorer1Y - tempY][m->trainers.explorer1X + tempX] == 'X'){
                            m->characterMap[m->trainers.explorer1Y - tempY][m->trainers.explorer1X + tempX] = 'e';
                            m->characterMap[m->trainers.explorer1Y][m->trainers.explorer1X] = 'X';
                            m->trainers.explorer1X += tempX;
                            m->trainers.explorer1Y -= tempY;
                            break;
                        }
                        else if (m->characterMap[m->trainers.explorer1Y - tempY][m->trainers.explorer1X + tempX] == '@'){
                            if (npcDefeated(m, 'e', m->trainers.explorer1Y, m->trainers.explorer1X) == 0){
                                npcKill(m, 'e', m->trainers.explorer1Y, m->trainers.explorer1X);
                                int exit = 0;
                                w = create_newwin(80, 24);
                                getVoiceLine(w, m, 'e', m->trainers.explorer1Y, m->trainers.explorer1X, 'n', '.');
                                delwin(w);
                            }
                            else {
                                int exit = 0;
                                w = create_newwin(80, 24);
                                getVoiceLine(w, m, 'e', m->trainers.explorer1Y, m->trainers.explorer1X, 'd', '.');
                                delwin(w);
                            }
                        }
                    }
                }
                if (negY == 0){
                        if (myWorld.hikerMap[m->trainers.explorer1Y + tempY][m->trainers.explorer1X - tempX] >= 0 && myWorld.hikerMap[m->trainers.explorer1Y + tempY][m->trainers.explorer1X - tempX] != INT_MAX
                        && m->characterMap[m->trainers.explorer1Y + tempY][m->trainers.explorer1X - tempX] == 'X'){
                            m->characterMap[m->trainers.explorer1Y + tempY][m->trainers.explorer1X - tempX] = 'e';
                            m->characterMap[m->trainers.explorer1Y][m->trainers.explorer1X] = 'X';
                            m->trainers.explorer1X -= tempX;
                            m->trainers.explorer1Y += tempY;
                            break;
                        }
                        else if (m->characterMap[m->trainers.explorer1Y + tempY][m->trainers.explorer1X - tempX] == '@'){
                            if (npcDefeated(m, 'e', m->trainers.explorer1Y, m->trainers.explorer1X) == 0){
                                npcKill(m, 'e', m->trainers.explorer1Y, m->trainers.explorer1X);
                                int exit = 0;
                                w = create_newwin(80, 24);
                                getVoiceLine(w, m, 'e', m->trainers.explorer1Y, m->trainers.explorer1X, 'n', '.');
                                delwin(w);
                            }
                            else {
                                int exit = 0;
                                w = create_newwin(80, 24);
                                getVoiceLine(w, m, 'e', m->trainers.explorer1Y, m->trainers.explorer1X, 'd', '.');
                                delwin(w);
                            }
                        }
                }
                else if (negY == 1){
                        if (myWorld.hikerMap[m->trainers.explorer1Y - tempY][m->trainers.explorer1X - tempX] >= 0 && myWorld.hikerMap[m->trainers.explorer1Y - tempY][m->trainers.explorer1X - tempX] != INT_MAX
                        && m->characterMap[m->trainers.explorer1Y - tempY][m->trainers.explorer1X - tempX] == 'X'){
                            m->characterMap[m->trainers.explorer1Y - tempY][m->trainers.explorer1X - tempX] = 'e';
                            m->characterMap[m->trainers.explorer1Y][m->trainers.explorer1X] = 'X';
                            m->trainers.explorer1X -= tempX;
                            m->trainers.explorer1Y -= tempY;
                            break;
                        }
                        else if (m->characterMap[m->trainers.explorer1Y - tempY][m->trainers.explorer1X - tempX] == '@'){
                            if (npcDefeated(m, 'e', m->trainers.explorer1Y, m->trainers.explorer1X) == 0){
                                npcKill(m, 'e', m->trainers.explorer1Y, m->trainers.explorer1X);
                                int exit = 0;
                                w = create_newwin(80, 24);
                                getVoiceLine(w, m, 'e', m->trainers.explorer1Y, m->trainers.explorer1X, 'n', '.');
                                delwin(w);
                            }
                            else {
                                int exit = 0;
                                w = create_newwin(80, 24);
                                getVoiceLine(w, m, 'e', m->trainers.explorer1Y, m->trainers.explorer1X, 'd', '.');
                                delwin(w);
                            }
                        }
                }
            }
        }
    }

    //wanderer
    else if (c == 'w'){
        char wandTerrain = m->singleMap[m->trainers.wand1Y][m->trainers.wand1X];
        while (1){
            int tempX = rand() % (1 + 1 - 0) + 0;
            int tempY = rand() % (1 + 1 - 0) + 0;
            int negX = rand() % (1 + 1 - 0) + 0;
            int negY = rand() % (1 + 1 - 0) + 0;
            if (!(tempX == 0 && tempY == 0)){
                if (negX == 0){
                    if (negY == 0){
                        if (myWorld.hikerMap[m->trainers.wand1Y + tempY][m->trainers.wand1X + tempX] >= 0 && myWorld.hikerMap[m->trainers.wand1Y + tempY][m->trainers.wand1X + tempX] != INT_MAX
                        && m->characterMap[m->trainers.wand1Y + tempY][m->trainers.wand1X + tempX] == 'X' && m->singleMap[m->trainers.wand1Y + tempY][m->trainers.wand1X + tempX] == wandTerrain){
                            m->characterMap[m->trainers.wand1Y + tempY][m->trainers.wand1X + tempX] = 'w';
                            m->characterMap[m->trainers.wand1Y][m->trainers.wand1X] = 'X';
                            m->trainers.wand1X += tempX;
                            m->trainers.wand1Y += tempY;
                            break;
                        }
                        else if (m->characterMap[m->trainers.wand1Y + tempY][m->trainers.wand1X + tempX] == '@'){
                            if (npcDefeated(m, 'w', m->trainers.wand1Y, m->trainers.wand1X) == 0){
                                npcKill(m, 'w', m->trainers.wand1Y, m->trainers.wand1X);
                                int exit = 0;
                                w = create_newwin(80, 24);
                                getVoiceLine(w, m, 'w', m->trainers.wand1Y, m->trainers.wand1X, 'n', wandTerrain);
                                delwin(w);
                            }
                            else {
                                int exit = 0;
                                w = create_newwin(80, 24);
                                getVoiceLine(w, m, 'w', m->trainers.wand1Y, m->trainers.wand1X, 'd', wandTerrain);
                                delwin(w);
                            }
                        }
                    }
                    else if (negY == 1){
                        if (myWorld.hikerMap[m->trainers.wand1Y - tempY][m->trainers.wand1X + tempX] >= 0 && myWorld.hikerMap[m->trainers.wand1Y - tempY][m->trainers.wand1X + tempX] != INT_MAX
                        && m->characterMap[m->trainers.wand1Y - tempY][m->trainers.wand1X + tempX] == 'X' && m->singleMap[m->trainers.wand1Y - tempY][m->trainers.wand1X + tempX] == wandTerrain){
                            m->characterMap[m->trainers.wand1Y - tempY][m->trainers.wand1X + tempX] = 'w';
                            m->characterMap[m->trainers.wand1Y][m->trainers.wand1X] = 'X';
                            m->trainers.wand1X += tempX;
                            m->trainers.wand1Y -= tempY;
                            break;
                        }
                        else if (m->characterMap[m->trainers.wand1Y - tempY][m->trainers.wand1X + tempX] == '@'){
                            if (npcDefeated(m, 'w', m->trainers.wand1Y, m->trainers.wand1X) == 0){
                                npcKill(m, 'w', m->trainers.wand1Y, m->trainers.wand1X);
                                int exit = 0;
                                w = create_newwin(80, 24);
                                getVoiceLine(w, m, 'w', m->trainers.wand1Y, m->trainers.wand1X, 'n', wandTerrain);
                                delwin(w);
                            }
                            else {
                                int exit = 0;
                                w = create_newwin(80, 24);
                                getVoiceLine(w, m, 'w', m->trainers.wand1Y, m->trainers.wand1X, 'd', wandTerrain);
                                delwin(w);
                            }
                        }
                    }
                }
                if (negY == 0){
                        if (myWorld.hikerMap[m->trainers.wand1Y + tempY][m->trainers.wand1X - tempX] >= 0 && myWorld.hikerMap[m->trainers.wand1Y + tempY][m->trainers.wand1X - tempX] != INT_MAX
                        && m->characterMap[m->trainers.wand1Y + tempY][m->trainers.wand1X - tempX] == 'X' && m->singleMap[m->trainers.wand1Y + tempY][m->trainers.wand1X - tempX] == wandTerrain){
                            m->characterMap[m->trainers.wand1Y + tempY][m->trainers.wand1X - tempX] = 'w';
                            m->characterMap[m->trainers.wand1Y][m->trainers.wand1X] = 'X';
                            m->trainers.wand1X -= tempX;
                            m->trainers.wand1Y += tempY;
                            break;
                        }
                        else if (m->characterMap[m->trainers.wand1Y + tempY][m->trainers.wand1X - tempX] == '@'){
                            if (npcDefeated(m, 'w', m->trainers.wand1Y, m->trainers.wand1X) == 0){
                                npcKill(m, 'w', m->trainers.wand1Y, m->trainers.wand1X);
                                int exit = 0;
                                w = create_newwin(80, 24);
                                getVoiceLine(w, m, 'w', m->trainers.wand1Y, m->trainers.wand1X, 'n', wandTerrain);
                                delwin(w);
                            }
                            else {
                                int exit = 0;
                                w = create_newwin(80, 24);
                                getVoiceLine(w, m, 'w', m->trainers.wand1Y, m->trainers.wand1X, 'd', wandTerrain);
                                delwin(w);
                            }
                        }
                }
                else if (negY == 1){
                        if (myWorld.hikerMap[m->trainers.wand1Y - tempY][m->trainers.wand1X - tempX] >= 0 && myWorld.hikerMap[m->trainers.wand1Y - tempY][m->trainers.wand1X - tempX] != INT_MAX
                        && m->characterMap[m->trainers.wand1Y - tempY][m->trainers.wand1X - tempX] == 'X' && m->singleMap[m->trainers.wand1Y - tempY][m->trainers.wand1X - tempX] == wandTerrain){
                            m->characterMap[m->trainers.wand1Y - tempY][m->trainers.wand1X - tempX] = 'w';
                            m->characterMap[m->trainers.wand1Y][m->trainers.wand1X] = 'X';
                            m->trainers.wand1X -= tempX;
                            m->trainers.wand1Y -= tempY;
                            break;
                        }
                        else if (m->characterMap[m->trainers.wand1Y - tempY][m->trainers.wand1X - tempX] == '@'){
                            if (npcDefeated(m, 'w', m->trainers.wand1Y, m->trainers.wand1X) == 0){
                                npcKill(m, 'w', m->trainers.wand1Y, m->trainers.wand1X);
                                int exit = 0;
                                w = create_newwin(80, 24);
                                getVoiceLine(w, m, 'w', m->trainers.wand1Y, m->trainers.wand1X, 'n', wandTerrain);
                                delwin(w);
                            }
                            else {
                                int exit = 0;
                                w = create_newwin(80, 24);
                                getVoiceLine(w, m, 'w', m->trainers.wand1Y, m->trainers.wand1X, 'd', wandTerrain);
                                delwin(w);
                            }
                        }
                }
            }
        }
    }
    return 1;
}

/**
 * Method used to find the terrain that a character just moved to and returns the weight so
 * it can be added to that respective characters moveTime before being pushed back into the que.
 */
int terrainGetter(map_t *m, char c){
    char locTile = 'X';
    if (c == 'h'){
        locTile = m->singleMap[m->trainers.hikerY][m->trainers.hikerX];
    }
    else if (c == 'r'){
        locTile = m->singleMap[m->trainers.rivalY][m->trainers.rivalX];
    }
    else if (c == 'P'){
        locTile = m->singleMap[m->trainers.pace1Y][m->trainers.pace2Y];
    }
    else if (c == 'p'){
        locTile = m->singleMap[m->trainers.pace2Y][m->trainers.pace2X];
    }
    else if (c == 'w'){
        locTile = m->singleMap[m->trainers.wand1Y][m->trainers.wand1X];
    }
    else if (c == 'e'){
        locTile = m->singleMap[m->trainers.explorer1Y][m->trainers.explorer1X];
    }
    else if (c == '@'){
        locTile = m->singleMap[myWorld.player.playerY][myWorld.player.playerX];
    }
    
    if (locTile == '.'){
        return 10;
    }
    else if (locTile == ':'){
        if (c == 'h'){
            return 15;
        }
        return 20;
    }
    else if (locTile == 'M' || locTile == 'C'){
        return 50;
    }
    else if (locTile == '#'){
        return 10;
    }
    //swimmers
    else {
        return 7;
    }
}

/**
 * Goes through all 9 files and parses them into the object "allPokeInfo" ordered by data type. allPokeInfo stores them in vectors.
*/
void parseItAll() {
    std::ifstream ifs("/share/cs327/pokedex/pokedex/data/csv/pokemon.csv");
    std::string data;
    pokemon_t * pokeTemp = new pokemon_t;
    moves_t * moveTemp = new moves_t;
    pokemonMoves_t * pokeMovesTemp = new pokemonMoves_t;
    pokemonStats_t * pokeStatsTemp = new pokemonStats_t;
    pokemonSpecies_t * pokeSpeciesTemp = new pokemonSpecies_t;
    experience_t * expTemp = new experience_t;
    typeNames_t * typeNameTemp = new typeNames_t;
    stats_t * statsTemp = new stats_t;
    pokemonType_t * pokeTypeTemp = new pokemonType_t;
    evolutionInfo_t * evolutionTemp = new evolutionInfo_t;

    int count = 0;
    int firstRun = 1;
    //pokemon.csv
    if (ifs){
        PARSEPOKE:
        std::string nextData = "";
        getline(ifs, data);
        while (!ifs.eof()){
            count++;
            std::getline(ifs, data, ',');
            if (data.length() == 0){
                data = "2147483647";
            }
            switch(count) {
                case 1:
                    pokeTemp->dexNum = std::stoi(data);    
                    break;
                case 2:
                    if (!firstRun){
                        pokeTemp->dexNum = std::stoi(nextData);
                    }
                    pokeTemp->name = data;
                    break;
                case 3:
                    pokeTemp->speciesID = std::stoi(data);
                    break;
                case 4:
                    pokeTemp->height = std::stoi(data);
                    break;
                case 5:
                    pokeTemp->weight = std::stoi(data);
                    break;
                case 6:
                    pokeTemp->baseXP = std::stoi(data);
                    break;
                case 7:
                    pokeTemp->order = std::stoi(data);
                    break;
                case 8:
                    int start = data.find('\n');
                    pokeTemp->isDefault = std::stoi(data.substr(0, start));
                    nextData = data.substr(start + 1);
                    firstRun = 0;
                    allPokeInfo.pokemon.push_back(*pokeTemp);
                    count = 1;
                    pokeTemp = new pokemon_t;
                    break;
            }
        }
    }
    else {
        ifs.close();
        ifs.clear();
        //second location
        std::string home = std::getenv("HOME");
        home += "/.poke327/";
        ifs.open(home + "pokemon.csv");
        if (ifs){
            goto PARSEPOKE;
        }
        else {
            printw("File not found.");
            return;
        }
    }
    ifs.close();
    ifs.clear();

    ifs.open("/share/cs327/pokedex/pokedex/data/csv/moves.csv");
    count = 0;
    firstRun = 1;
    //moves.csv
    if (ifs){
        PARSEMOVES:
        std::string nextData = "";
        getline(ifs, data);
        while (!ifs.eof()){
            count++;
            std::getline(ifs, data, ',');
            if (data.length() == 0){
                data = "2147483647";
            }
            switch(count){
                case 1:
                    moveTemp->id = std::stoi(data);
                    break;
                case 2:
                    if (!firstRun){
                        moveTemp->id = std::stoi(nextData);
                    }
                    moveTemp->name = data;
                    break;
                case 3:
                    moveTemp->genID = std::stoi(data);
                    break;
                case 4:
                    moveTemp->typeID = std::stoi(data);
                    break;
                case 5:
                    moveTemp->power = std::stoi(data);
                    break;
                case 6:
                    moveTemp->pp = std::stoi(data);
                    break;
                case 7:
                    moveTemp->accuracy = std::stoi(data);
                    break;
                case 8:
                    moveTemp->priority = std::stoi(data);
                    break;
                case 9:
                    moveTemp->targetID = std::stoi(data);
                    break;
                case 10:
                    moveTemp->dmgClassID = std::stoi(data);
                    break;
                case 11:
                    moveTemp->effectID = std::stoi(data);
                    break;
                case 12:
                    moveTemp->effectChance = std::stoi(data);
                    break;
                case 13:
                    moveTemp->contestTypeID = std::stoi(data);
                    break;
                case 14:
                    moveTemp->contestEffectID = std::stoi(data);
                    break;
                case 15:
                    int start = data.find('\n');
                    if (start == 0){
                        data = "2147483647" + data;
                        start = data.find('\n');
                    }
                    moveTemp->superContEffectID = std::stoi(data.substr(0, start));
                    nextData = data.substr(start + 1);
                    firstRun = 0;
                    count = 1;
                    allPokeInfo.moves.push_back(*moveTemp);
                    moveTemp = new moves_t;
                    break;
            }
        }
    }
    else {
        ifs.close();
        ifs.clear();
        //second location
        std::string home = std::getenv("HOME");
        home += "/.poke327/";
        ifs.open(home + "moves.csv");
        if (ifs){
            goto PARSEMOVES;
        }
        else {
            printw("File not found.");
            return;
        }
    }
    ifs.close();
    ifs.clear();

    ifs.open("/share/cs327/pokedex/pokedex/data/csv/pokemon_moves.csv");
    count = 0;
    firstRun = 1;
    //pokemon_moves.csv
    if (ifs){
        PARSEPOKEMOVES:
        getline(ifs, data);
        std::string nextData;
        while (!ifs.eof()){
            count++;
            std::getline(ifs, data, ',');
            if (data.length() == 0){
                data = "2147483647";
            }
            switch(count){
                case 1:
                    pokeMovesTemp->pokemonID = std::stoi(data);
                    break;
                case 2:
                    if (!firstRun){
                        pokeMovesTemp->pokemonID = std::stoi(nextData);
                    }
                    pokeMovesTemp->versionGroupID = std::stoi(data);
                    break;
                case 3:
                    pokeMovesTemp->moveID = std::stoi(data);
                    break;
                case 4:
                    pokeMovesTemp->pokeMoveMethodID = std::stoi(data);
                    break;
                case 5:
                    pokeMovesTemp->level = std::stoi(data);
                    break;
                case 6:
                    int start = data.find('\n');
                    if (start == 0){
                        data = "2147483647" + data;
                        start = data.find('\n');
                    }
                    pokeMovesTemp->order = std::stoi(data.substr(0, start));
                    nextData = data.substr(start + 1);
                    firstRun = 0;
                    count = 1;
                    allPokeInfo.pokemonMoves.push_back(*pokeMovesTemp);
                    pokeMovesTemp = new pokemonMoves_t;
                    break;
            }
        }

    }
    else {
        ifs.close();
        ifs.clear();
        //second location
        std::string home = std::getenv("HOME");
        home += "/.poke327/";
        ifs.open(home + "pokemon_moves.csv");
        if (ifs){
            goto PARSEPOKESPECIES;
        }
        else {
            printw("File not found.");
            return;
        }
    }

    ifs.close();
    ifs.clear();

    ifs.open("/share/cs327/pokedex/pokedex/data/csv/pokemon_species.csv");
    count = 0;
    firstRun = 1;
    //pokemon_species.csv
    if (ifs) {
        PARSEPOKESPECIES:
        getline(ifs, data);
        std::string nextData;
        while (!ifs.eof()){
            count++;
            std::getline(ifs, data, ',');
            if (data.length() == 0){
                data = "2147483647";
            }
            switch(count){
                case 1:
                    pokeSpeciesTemp->dexNum = std::stoi(data);
                    break;
                case 2:
                    if (!firstRun){
                        pokeSpeciesTemp->dexNum = std::stoi(nextData);
                    }
                    pokeSpeciesTemp->name = data;
                    break;
                case 3:
                    pokeSpeciesTemp->genID = std::stoi(data);
                    break;
                case 4:
                    pokeSpeciesTemp->evolveFromID = std::stoi(data);
                    break;
                case 5:
                    pokeSpeciesTemp->evolveChainID = std::stoi(data);
                    break;
                case 6:
                    pokeSpeciesTemp->colorID = std::stoi(data);
                    break;
                case 7:
                    pokeSpeciesTemp->shapeID = std::stoi(data);
                    break;
                case 8:
                    pokeSpeciesTemp->habitatID = std::stoi(data);
                    break;
                case 9:
                    pokeSpeciesTemp->genderRate = std::stoi(data);
                    break;
                case 10:
                    pokeSpeciesTemp->captureRate = std::stoi(data);
                    break;
                case 11:
                    pokeSpeciesTemp->baseHappy = std::stoi(data);
                    break;
                case 12:
                    pokeSpeciesTemp->isBaby = std::stoi(data);
                    break;
                case 13:
                    pokeSpeciesTemp->hatchCounter = std::stoi(data);
                    break;
                case 14:
                    pokeSpeciesTemp->hasGenderDiff = std::stoi(data);
                    break;
                case 15:
                    pokeSpeciesTemp->growthRateID = std::stoi(data);
                    break;
                case 16:
                    pokeSpeciesTemp->formsSwitchable = std::stoi(data);
                    break;
                case 17:
                    pokeSpeciesTemp->isLegendary = std::stoi(data);
                    break;
                case 18:
                    pokeSpeciesTemp->isMythical = std::stoi(data);
                    break;
                case 19:
                    pokeSpeciesTemp->order = std::stoi(data);
                    break;
                case 20:
                    int start = data.find('\n');
                    if (start == 0){
                        data = "2147483647" + data;
                        start = data.find('\n');
                    }
                    pokeSpeciesTemp->conqOrder = std::stoi(data.substr(0, start));
                    nextData = data.substr(start + 1);
                    firstRun = 0;
                    count = 1;
                    allPokeInfo.pokemonSpecies.push_back(*pokeSpeciesTemp);
                    pokeSpeciesTemp = new pokemonSpecies_t;
                    break;
            }
        }
    }
    else {
        ifs.close();
        ifs.clear();
        //second location
        std::string home = std::getenv("HOME");
        home += "/.poke327/";
        ifs.open(home + "pokemon_species.csv");
        if (ifs){
            goto PARSEPOKESPECIES;
        }
        else {
            printw("File not found.");
            return;
        }
    }
    ifs.close();
    ifs.clear();

    ifs.open("/share/cs327/pokedex/pokedex/data/csv/experience.csv");
    count = 0;
    firstRun = 1;
    //experience.csv
    if (ifs){
        PARSEEXPERIENCE:
        getline(ifs, data);
        std::string nextData;
        while (!ifs.eof()){
            count++;
            std::getline(ifs, data, ',');
            if (data.length() == 0){
                data = "2147483647";
            }
            switch(count){
                case 1:
                    expTemp->growthRateID = std::stoi(data);
                    break;
                case 2:
                    if (!firstRun){
                        expTemp->growthRateID = std::stoi(nextData);
                    }
                    expTemp->level = std::stoi(data);
                    break;
                case 3:
                    int start = data.find('\n');
                    expTemp->experience = std::stoi(data.substr(0, start));
                    nextData = data.substr(start + 1);
                    firstRun = 0;
                    count = 1;
                    allPokeInfo.experience.push_back(*expTemp);
                    expTemp = new experience_t;
                    break;
            }
        }

    }
    else {
        ifs.close();
        ifs.clear();
        //second location
        std::string home = std::getenv("HOME");
        home += "/.poke327/";
        ifs.open(home + "experience.csv");
        if (ifs){
            goto PARSEEXPERIENCE;
        }
        else {
            printw("File not found.");
            return;
        }
    }

    ifs.close();
    ifs.clear();

    ifs.open("/share/cs327/pokedex/pokedex/data/csv/type_names.csv");
    count = 0;
    firstRun = 1;
    std::string typeID = "1";
    //type_names.csv this one fucking sucks
    if (ifs){
        PARSETYPENAMES:
        getline(ifs, data);
        std::string nextData;
        while (!ifs.eof()){
            count++;
            std::getline(ifs, data, ',');
            //gets the type id
            while (count == 1 && !data.compare(typeID) == 0){
                int start = data.find('\n');
                if (start != -1){
                    data = data.substr(start + 1);
                }
                else {
                    std::getline(ifs, data, ',');
                }
            }
            //because it for some reason skips to 10001
            if (stoi(typeID) == 18){
                typeID = "10000";
            }
            //gets to the line for english, the name is in the same line so it works.
            while (count == 2 && !data.compare("9") == 0){
                std::getline(ifs, data, ',');
            }
            if (data.length() == 0){
                data = "2147483647";
            }
            switch(count){
                case 1:
                    typeNameTemp->typeID = std::stoi(data);
                    break;
                case 2:
                    typeNameTemp->localLangID = std::stoi(data);
                    break;
                case 3:
                    int start = data.find('\n');
                    typeNameTemp->name = data.substr(0, start);
                    allPokeInfo.typeNames.push_back(*typeNameTemp);
                    typeNameTemp = new typeNames_t;
                    typeID = std::to_string(stoi(typeID) + 1);
                    count = 0;
                    break;
            }
        }
    }
    else {
        ifs.close();
        ifs.clear();
        //second location
        std::string home = std::getenv("HOME");
        home += "/.poke327/";
        ifs.open(home + "type_names.csv");
        if (ifs){
            goto PARSETYPENAMES;
        }
        else {
            printw("File not found.");
            return;
        }
    }

    ifs.close();
    ifs.clear();

    ifs.open("/share/cs327/pokedex/pokedex/data/csv/pokemon_stats.csv");
    count = 0;
    firstRun = 1;
    //pokemon_stats.csv
    if (ifs){
        PARSEPOKESTATS:
        getline(ifs, data);
        std::string nextData;
        while (!ifs.eof()){
            count++;
            std::getline(ifs, data, ',');
            if (data.length() == 0){
                data = "2147483647";
            }
            switch(count){
                case 1:
                    pokeStatsTemp->pokemonID = std::stoi(data);
                    break;
                case 2:
                    if (!firstRun){
                        pokeStatsTemp->pokemonID = std::stoi(nextData);
                    }
                    pokeStatsTemp->statID = std::stoi(data);
                    break;
                case 3:
                    pokeStatsTemp->baseStat = std::stoi(data);
                    break;
                case 4:
                    int start = data.find('\n');
                    pokeStatsTemp->effort = std::stoi(data.substr(0, start));
                    nextData = data.substr(start + 1);
                    firstRun = 0;
                    count = 1;
                    allPokeInfo.pokemonStats.push_back(*pokeStatsTemp);
                    pokeStatsTemp = new pokemonStats_t;
                    break;
            }
        }
    }
    else {
        ifs.close();
        ifs.clear();
        //second location
        std::string home = std::getenv("HOME");
        home += "/.poke327/";
        ifs.open(home + "pokemon_stats.csv");
        if (ifs){
            goto PARSEPOKESTATS;
        }
        else {
            printw("File not found.");
            return;
        }
    }

    ifs.close();
    ifs.clear();

    ifs.open("/share/cs327/pokedex/pokedex/data/csv/stats.csv");
    count = 0;
    firstRun = 1;
    //stats.csv
    if (ifs){
        PARSESTATS:
        getline(ifs, data);
        std::string nextData;
        while (!ifs.eof()){
            count++;
            std::getline(ifs, data, ',');
            if (data.length() == 0){
                data = "2147483647";
            }
            switch(count){
                case 1:
                    statsTemp->id = std::stoi(data);
                    break;
                case 2:
                    if (!firstRun){
                        statsTemp->id = std::stoi(nextData);
                    }
                    statsTemp->damageClassID = std::stoi(data);
                    break;
                case 3:
                    statsTemp->statName = data;
                    break;
                case 4:
                    statsTemp->isBattleOnly = std::stoi(data);
                    break;
                case 5:
                    int start = data.find('\n');
                    if (start == 0){
                        data = "2147483647" + data;
                        start = data.find('\n');
                    }
                    statsTemp->gameIndex = std::stoi(data.substr(0, start));
                    nextData = data.substr(start + 1);
                    firstRun = 0;
                    count = 1;
                    allPokeInfo.stats.push_back(*statsTemp);
                    statsTemp = new stats_t;
                    break;
            }
        }
    }
    else {
        ifs.close();
        ifs.clear();
        //second location
        std::string home = std::getenv("HOME");
        home += "/.poke327/";
        ifs.open(home + "stats.csv");
        if (ifs){
            goto PARSESTATS;
        }
        else {
            printw("File not found.");
            return;
        }
    }

    ifs.close();
    ifs.clear();

    ifs.open("/share/cs327/pokedex/pokedex/data/csv/pokemon_types.csv");
    count = 0;
    firstRun = 1;
    //pokemon_types.csv
    if (ifs){
        PARSEPOKETYPES:
        getline(ifs, data);
        std::string nextData;
        while (!ifs.eof()){
            count++;
            std::getline(ifs, data, ',');
            if (data.length() == 0){
                data = "2147483647";
            }
            switch(count){
                case 1:
                    pokeTypeTemp->pokemonID = std::stoi(data);
                    break;
                case 2:
                    if (!firstRun){
                        pokeTypeTemp->pokemonID = std::stoi(nextData);
                    }
                    pokeTypeTemp->typeID = std::stoi(data);
                    break;
                case 3:
                    int start = data.find('\n');
                    if (start == 0){
                        data = "2147483647" + data;
                        start = data.find('\n');
                    }
                    pokeTypeTemp->slot = std::stoi(data.substr(0, start));
                    nextData = data.substr(start + 1);
                    firstRun = 0;
                    count = 1;
                    allPokeInfo.pokemonTypes.push_back(*pokeTypeTemp);
                    pokeTypeTemp = new pokemonType_t;
                    break;
            }
        }
    }
    else {
        ifs.close();
        ifs.clear();
        //second location
        std::string home = std::getenv("HOME");
        home += "/.poke327/";
        ifs.open(home + "pokemon_types.csv");
        if (ifs){
            goto PARSEPOKETYPES;
        }
        else {
            printw("File not found.");
            return;
        }
    }

    ifs.close();
    ifs.clear();

    ifs.open("/share/cs327/pokedex/pokedex/data/csv/pokemon_evolution.csv");
    count = 0;
    firstRun = 1;

    if (ifs){
        PARSEPOKEEVO:
        getline(ifs, data);
        std::string nextData;
        while (!ifs.eof()){
            count++;
            std::getline(ifs, data, ',');
            if (data.length() == 0){
                data = "2147483647";
            }
            switch(count){
                case 1:
                    evolutionTemp->evoID = std::stoi(data);
                    break;
                case 2:
                    if (!firstRun){
                        evolutionTemp->evoID = std::stoi(nextData);
                    }
                    evolutionTemp->evoDexNum = std::stoi(data);
                    break;
                case 3:
                    evolutionTemp->evoTriggerID = std::stoi(data);
                    break;
                case 4:
                    evolutionTemp->triggerItemID = std::stoi(data);
                    break;
                case 5:
                    evolutionTemp->minLevel = std::stoi(data);
                    break;
                case 6:
                    evolutionTemp->genderID = std::stoi(data);
                    break;
                case 7:
                    evolutionTemp->locID = std::stoi(data);
                    break;
                case 8:
                    evolutionTemp->heldItemID = std::stoi(data);
                    break;
                case 9:
                    evolutionTemp->tod = data;
                    break;
                case 10:
                    evolutionTemp->knownMoveID = std::stoi(data);
                    break;
                case 11:
                    evolutionTemp->kMoveTypeID = std::stoi(data);
                    break;
                case 12:
                    evolutionTemp->minHap = std::stoi(data);
                    break;
                case 13:
                    evolutionTemp->minBeau = std::stoi(data);
                    break;
                case 14:
                    evolutionTemp->minAff = std::stoi(data);
                    break;
                case 15:
                    evolutionTemp->relPhysStats = std::stoi(data);
                    break;
                case 16:
                    evolutionTemp->partySID = std::stoi(data);
                    break;
                case 17:
                    evolutionTemp->partyTID = std::stoi(data);
                    break;
                case 18:
                    evolutionTemp->tradeID = std::stoi(data);
                    break;
                case 19:
                    evolutionTemp->overrain = std::stoi(data);
                    break;
                case 20:
                    int start = data.find('\n');
                    if (start == 0){
                        data = "2147483647" + data;
                        start = data.find('\n');
                    }
                    evolutionTemp->upsidedown = std::stoi(data.substr(0, start));
                    nextData = data.substr(start + 1);
                    firstRun = 0;
                    count = 1;
                    allPokeInfo.evolutionInfo.push_back(*evolutionTemp);
                    evolutionTemp = new evolutionInfo_t;
                    break;
            }
        }
    }
    else {
        ifs.close();
        ifs.clear();
        //second location
        std::string home = std::getenv("HOME");
        home += "/.poke327/";
        ifs.open(home + "pokemon_evolution.csv");
        if (ifs){
            goto PARSEPOKEEVO;
        }
        else {
            printw("File not found.");
            return;
        }
    }


    return;
}



//useless helper function that will be removed
// std::string isMax(std::string s){
//     if (s.compare("2147483647") == 0){
//         return "";
//     }
//     return s;
// }


//randomly just crashes?? is it because i am increasing the size of a variable inside of an object thats size itself doesnt increase?
void pokemonChoice(){
    refresh();
    WINDOW *w;
    int choice = 0;
    actualPokemon_t * p1 = new actualPokemon_t;
    tallGrassEncounter(myWorld.worldMap[200][200], p1, 200, 200, true);
    actualPokemon_t * p2 = new actualPokemon_t;
    tallGrassEncounter(myWorld.worldMap[200][200], p2, 200, 200, true);
    while (p2->pokemon.dexNum == p1->pokemon.dexNum){
        p2 = new actualPokemon_t;
        tallGrassEncounter(myWorld.worldMap[200][200], p2, 200, 200, true);
    }
    actualPokemon_t * p3 = new actualPokemon_t;
    tallGrassEncounter(myWorld.worldMap[200][200], p3, 200, 200, true);
    while (p3->pokemon.dexNum == p2->pokemon.dexNum || p3->pokemon.dexNum == p1->pokemon.dexNum){
        p3 = new actualPokemon_t;
        tallGrassEncounter(myWorld.worldMap[200][200], p3, 200, 200, true);
    }
    w = create_newwin(80, 24);
    mvprintw(1, 1, "Welcome new trainer, please select your first Pokemon!");
    if (p1->pokemonTypes.size() == 1){
        mvprintw(5, 1, "The %s pokemon, %s", p1->typeNames[0].name.c_str(), p1->pokemon.name.c_str());
    }
    else {
        mvprintw(5, 1, "The %s %s pokemon, %s", p1->typeNames[0].name.c_str(), p1->typeNames[1].name.c_str(), p1->pokemon.name.c_str());
    }
    if (p2->pokemonTypes.size() == 1){
        mvprintw(7, 1, "The %s pokemon, %s", p2->typeNames[0].name.c_str(), p2->pokemon.name.c_str());
    }
    else {
        mvprintw(7, 1, "The %s %s pokemon, %s", p2->typeNames[0].name.c_str(), p2->typeNames[1].name.c_str(), p2->pokemon.name.c_str());
    }
    if (p3->pokemonTypes.size() == 1){
        mvprintw(9, 1, "The %s pokemon, %s", p3->typeNames[0].name.c_str(), p3->pokemon.name.c_str());
    }
    else {
        mvprintw(9, 1, "The %s %s pokemon, %s", p3->typeNames[0].name.c_str(), p3->typeNames[1].name.c_str(), p3->pokemon.name.c_str());
    }
    mvprintw(11, 1, "Load from previous save state");

    mvprintw(17, 1, "Please select one of them by pressing 1, 2, 3, or 4 respectively.");
    choice = getch();
    while (choice != 49 && choice != 50 && choice != 51 && choice != 52){
        choice = getch();
    }
    if (choice == 49){
        myWorld.player.pokemon.push_back(*p1);
    }
    else if (choice == 50){
        myWorld.player.pokemon.push_back(*p2);
    }
    else if (choice == 51){
        myWorld.player.pokemon.push_back(*p3);
    }
    else {
        wclear(w);
        delwin(w);
        w = create_newwin(80, 24);
        mvwprintw(w, 1, 1, "Choose your save state you wish to load from!");
        mvwprintw(w, 3, 1, "Save Slot 1");
        mvwprintw(w, 5, 1, "Save Slot 2");
        mvwprintw(w, 7, 1, "Save Slot 3");
        mvwprintw(w, 9, 1, "Save Slot 4");
        wrefresh(w);
        int choice = getch();
        while (choice != 49 && choice != 50 && choice != 51 && choice != 52) {
            choice = getch();
        }
        if (choice == 49){
        readSave(1);
        }
        else if (choice == 50){
            readSave(2);
        }
        else if (choice == 51){
            readSave(3);
        }
        else {
            readSave(4);
        }
    }
    refresh();
    delete p1;
    delete p2;
    delete p3;
    delwin(w);
}


/**
 * Builds first map with cost maps
 */
int worldInit(){
    for (int i = 0; i < 401; i++){
        for (int j = 0; j < 401; j++){
            myWorld.worldMap[i][j] = NULL;
        }
    }
    myWorld.worldMap[200][200] = (map_t *) malloc(sizeof (map_t));
    buildMap(myWorld.worldMap[200][200], 200, 200, 'x');
    generateCostMap(myWorld.worldMap[200][200], 'H');
    generateCostMap(myWorld.worldMap[200][200], 'R');
    return 0;
}

int main(){
    srand(time(NULL));
    char dir[13];
    int x;
    int y;
    int lastVisitedX = 200;
    int lastVisitedY = 200;
    myWorld.player.worldX = 200;
    myWorld.player.worldY = 200;
    int* swimDown = (int *) malloc(sizeof (int) + 1);
    *swimDown = 0;
    int* swimLeft = (int *) malloc(sizeof (int) + 1);
    *swimLeft = 0;
    int* paceLeft = (int *) malloc(sizeof (int) + 1);
    *paceLeft = 0;
    int* paceDown = (int *) malloc(sizeof (int) + 1);
    *paceDown = 0;

    initscr();
    raw();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();

    WINDOW *w;
    w = create_newwin(80, 24);
    mvwprintw(w, 6, 1, "                                  ,'\\");
    mvwprintw(w, 7, 1, "    _.----.        ____         ,'  _\\   ___    ___     ____");
    mvwprintw(w, 8, 1, "_,-'       `.     |    |  /`.   \\,-'    |   \\  /   |   |    \\  |`.");
    mvwprintw(w, 9, 1, "\\      __    \\    '-.  | /   `.  ___    |    \\/    |   '-.   \\ |  |");
    mvwprintw(w, 10, 1, " \\.    \\ \\   |  __  |  |/    ,','_  `.  |          | __  |    \\|  |");
    mvwprintw(w, 11, 1, "   \\    \\/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  |");
    mvwprintw(w, 12, 1, "    \\     ,-'/  /   \\    ,'   | \\/ / ,`.|         /  /   \\  |     |");
    mvwprintw(w, 13, 1, "     \\    \\ |   \\_/  |   `-.  \\    `'  /|  |    ||   \\_/  | |\\    |");
    mvwprintw(w, 14, 1, "      \\    \\ \\      /       `-.`.___,-' |  |\\  /| \\      /  | |   |");
    mvwprintw(w, 15, 1, "       \\    \\ `.__,'|  |`-._    `|      |__| \\/ |  `.__,'|  | |   |");
    mvwprintw(w, 16, 1, "        \\_.-'       |__|    `-._ |              '-.|     '-.| |   |");
    mvwprintw(w, 17, 1, "                            `'                            '-._|");
    mvwprintw(w, 22, 64, "-artist unknown");
    wrefresh(w);

    parseItAll();
    
    // while (command.compare("q") != 0){
    
    //     std::cout << "Type command, q to quit" << std::endl;
    //     std::cin >> command;

    //     if (command.compare("pokemon") == 0){
    //         std::vector<pokemon_t>::iterator pi;
    //         printf("id,identifier,species_id,height,weight,base_experience,order,is_default\n");
    //         for (pi = allPokeInfo.pokemon.begin(); pi != allPokeInfo.pokemon.end(); pi++){
    //             std::cout << isMax(std::to_string(pi->dexNum)) << ", " << pi->name << ", " << isMax(std::to_string(pi->speciesID)) << ", " << isMax(std::to_string(pi->height)) << ", " << isMax(std::to_string(pi->weight)) << ", " << isMax(std::to_string(pi->baseXP)) << ", " << isMax(std::to_string(pi->order)) << ", " << isMax(std::to_string(pi->isDefault)) << std::endl;
    //         }
    //     }
    //     else if (command.compare("moves") == 0){
    //         std::vector<moves_t>::iterator pi;
    //         printf("id,identifier,generation_id,type_id,power,pp,accuracy,priority,target_id,damage_class_id,effect_id,effect_chance,contest_type_id,contest_effect_id,super_contest_effect_id\n");
    //         for (pi = allPokeInfo.moves.begin(); pi != allPokeInfo.moves.end(); pi++){
    //             std::cout << std::to_string(pi->id) << ", " << pi->name << ", " << isMax(std::to_string(pi->genID)) << ", " << isMax(std::to_string(pi->typeID)) << ", " << isMax(std::to_string(pi->power)) << ", " << isMax(std::to_string(pi->pp)) << ", " << isMax(std::to_string(pi->accuracy))
    //             << ", " << isMax(std::to_string(pi->priority)) << ", " << isMax(std::to_string(pi->targetID)) << ", " << isMax(std::to_string(pi->dmgClassID)) << ", " << isMax(std::to_string(pi->effectID))
    //             << ", " << isMax(std::to_string(pi->effectChance)) << ", " << isMax(std::to_string(pi->contestTypeID)) << ", " << isMax(std::to_string(pi->contestEffectID)) << ", " << isMax(std::to_string(pi->superContEffectID)) << std::endl;
    //         }
    //     }
    //     else if (command.compare("pokemon_moves") == 0){
    //         std::vector<pokemonMoves_t>::iterator pi;
    //         printf("pokemon_id,version_group_id,move_id,pokemon_move_method_id,level,order");
    //         for (pi = allPokeInfo.pokemonMoves.begin(); pi != allPokeInfo.pokemonMoves.end(); pi++){
    //             std::cout << isMax(std::to_string(pi->pokemonID)) << ", " << isMax(std::to_string(pi->versionGroupID)) << ", " << isMax(std::to_string(pi->moveID)) << ", " << isMax(std::to_string(pi->pokeMoveMethodID)) << ", " 
    //             << isMax(std::to_string(pi->level)) << ", " << isMax(std::to_string(pi->order)) << std::endl; 
    //         } 
    //     }
    //     else if (command.compare("pokemon_species") == 0){
    //         std::vector<pokemonSpecies_t>::iterator pi;
    //         printf("id,identifier,generation_id,evolves_from_species_id,evolution_chain_id,color_id,shape_id,habitat_id,gender_rate,capture_rate,base_happiness,is_baby,hatch_counter,has_gender_differences,growth_rate_id,forms_switchable,is_legendary,is_mythical,order,conquest_order\n");
    //         for (pi = allPokeInfo.pokemonSpecies.begin(); pi != allPokeInfo.pokemonSpecies.end(); pi++){
    //             std::cout << isMax(std::to_string(pi->dexNum)) << ", " << isMax(pi->name) << ", " << isMax(std::to_string(pi->genID)) << ", " << isMax(std::to_string(pi->evolveFromID)) << ", " <<
    //              isMax(std::to_string(pi->evolveChainID)) << ", " << isMax(std::to_string(pi->colorID)) << ", " << isMax(std::to_string(pi->shapeID)) << ", " << isMax(std::to_string(pi->habitatID)) << ", " <<
    //               isMax(std::to_string(pi->genderRate)) << ", " << isMax(std::to_string(pi->captureRate)) << ", " << isMax(std::to_string(pi->baseHappy)) << ", " << isMax(std::to_string(pi->isBaby)) << ", " <<
    //                isMax(std::to_string(pi->hatchCounter)) << ", " << isMax(std::to_string(pi->hasGenderDiff)) << ", " << isMax(std::to_string(pi->growthRateID)) << ", " << isMax(std::to_string(pi->formsSwitchable)) << ", " <<
    //                 isMax(std::to_string(pi->isLegendary)) << ", " << isMax(std::to_string(pi->isMythical)) << ", " << isMax(std::to_string(pi->order)) << ", " << isMax(std::to_string(pi->conqOrder)) << std::endl;
    //         } 
    //     }
    //     else if (command.compare("experience") == 0){
    //         std::vector<experience_t>::iterator pi;
    //         printf("growth_rate_id,level,experience\n");
    //         for (pi = allPokeInfo.experience.begin(); pi != allPokeInfo.experience.end(); pi++){
    //             std::cout << std::to_string(pi->growthRateID) << ", " << std::to_string(pi->level) << ", " << std::to_string(pi->experience) << std::endl;
    //         } 
    //     }
    //     else if (command.compare("type_names") == 0){
    //         std::vector<typeNames_t>::iterator pi;
    //         printf("type_id,local_language_id,name\n");
    //         for (pi = allPokeInfo.typeNames.begin(); pi != allPokeInfo.typeNames.end(); pi++){
    //             std::cout << std::to_string(pi->typeID) << ", " << std::to_string(pi->localLangID) << ", " << pi->name << std::endl;
    //         }
    //     }
    //     else if (command.compare("pokemon_stats") == 0){
    //         std::vector<pokemonStats_t>::iterator pi;
    //         printf("pokemon_id,stat_id,base_stat,effort\n");
    //         for (pi = allPokeInfo.pokemonStats.begin(); pi != allPokeInfo.pokemonStats.end(); pi++){
    //             std::cout << std::to_string(pi->pokemonID) << ", " << std::to_string(pi->statID) << ", " << std::to_string(pi->baseStat) << std::to_string(pi->effort) << std::endl;
    //         }
    //     }
    //     else if (command.compare("stats") == 0){
    //         std::vector<stats_t>::iterator pi;
    //         printf("id,damage_class_id,identifier,is_battle_only,game_index\n");
    //         for (pi = allPokeInfo.stats.begin(); pi != allPokeInfo.stats.end(); pi++){
    //             std::cout << std::to_string(pi->id) << ", " << isMax(std::to_string(pi->damageClassID)) << ", " << pi->statName << ", " << isMax(std::to_string(pi->isBattleOnly)) << ", "
    //             << isMax(std::to_string(pi->gameIndex)) << std::endl;
    //         }
    //     }
    //     else if (command.compare("pokemon_types") == 0){
    //         std::vector<pokemonType_t>::iterator pi;
    //         printf("pokemon_id,type_id,slot\n");
    //         for (pi = allPokeInfo.pokemonTypes.begin(); pi != allPokeInfo.pokemonTypes.end(); pi++){
    //             std::cout << std::to_string(pi->pokemonID) << ", " << std::to_string(pi->typeID) << ", " << std::to_string(pi->slot) << std::endl;
    //         }
    //     }
    //     else if (command.compare("q") == 0){
    //         return 0;
    //     }
    //     else {
    //         printf("Command does not exist\n");
    //     }
    // }

    usleep(800000);
    delwin(w);

    pokemonChoice();

    //water
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    //boulders
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
    //grass
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    //Centers and Marts
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    //roads
    init_pair(5, COLOR_WHITE, COLOR_BLACK);
    //trees
    init_pair(6, COLOR_BLUE, COLOR_BLACK);
    //trainers
    // init_pair(7, COLOR_WHITE, COLOR_BLACK);
    //all trainers
    init_pair(8, COLOR_RED, COLOR_BLACK);

    int keepLooping = 1;



    charHeap_t cH;
    charHeap_init(&cH);
    worldInit();

    // //TESTING
    for (int i = 0; i < 3; i++){
        actualPokemon_t * poke = new actualPokemon_t;
        tallGrassEncounter(myWorld.worldMap[200][200], poke, 200, 200, false);
        myWorld.player.boxPokemon.push_back(*poke);
        delete(poke);
    }

    while (keepLooping){
        charNode_t cN = charHeap_pop(&cH);
        keepLooping = movingTrainers(myWorld.worldMap[lastVisitedY][lastVisitedX], swimDown, swimLeft, paceDown, paceLeft, cN.symbol, lastVisitedX, lastVisitedY);
        if (cN.symbol == '@'){
            //they flew
            if (keepLooping == 2){
                lastVisitedX = myWorld.player.worldX;
                lastVisitedY = myWorld.player.worldY;
                charHeap_init(&cH);
                cN = charHeap_pop(&cH);
            }
            else if (myWorld.worldMap[lastVisitedY][lastVisitedX]->roadEastY == myWorld.player.playerY && myWorld.player.playerX == 79){
                myWorld.worldMap[lastVisitedY][lastVisitedX]->characterMap[myWorld.player.playerY][myWorld.player.playerX] = 'X';
                if (myWorld.worldMap[lastVisitedY][min(400, lastVisitedX + 1)] == NULL){
                    myWorld.worldMap[lastVisitedY][min(400, lastVisitedX + 1)] = (map_t *) malloc(sizeof (map_t));
                    buildMap(myWorld.worldMap[lastVisitedY][min(400, lastVisitedX + 1)], lastVisitedY, min(400, lastVisitedX + 1), 'e');
                    generateCostMap(myWorld.worldMap[lastVisitedY][min(400, lastVisitedX + 1)], 'H');
                    generateCostMap(myWorld.worldMap[lastVisitedY][min(400, lastVisitedX + 1)], 'R');
                }
                else {
                    myWorld.player.playerY = myWorld.worldMap[lastVisitedY][min(400, lastVisitedX + 1)]->roadWestY;
                    myWorld.player.playerX = 1;
                    myWorld.worldMap[lastVisitedY][min(400, lastVisitedX + 1)]->characterMap[myWorld.player.playerY][myWorld.player.playerX] = '@';
                    printMap(*myWorld.worldMap[lastVisitedY][min(400, lastVisitedX + 1)]);
                }
                lastVisitedX += 1;
                charHeap_init(&cH);
                cN = charHeap_pop(&cH);
            }
            else if (myWorld.worldMap[lastVisitedY][lastVisitedX]->roadWestY == myWorld.player.playerY && myWorld.player.playerX == 0){
                myWorld.worldMap[lastVisitedY][lastVisitedX]->characterMap[myWorld.player.playerY][myWorld.player.playerX] = 'X';
                if (myWorld.worldMap[lastVisitedY][max(0, lastVisitedX - 1)] == NULL){
                    myWorld.worldMap[lastVisitedY][max(0, lastVisitedX - 1)] = (map_t *) malloc(sizeof (map_t));
                    buildMap(myWorld.worldMap[lastVisitedY][max(0, lastVisitedX - 1)], lastVisitedY, max(0, lastVisitedX - 1), 'w');
                    generateCostMap(myWorld.worldMap[lastVisitedY][max(0, lastVisitedX - 1)], 'H');
                    generateCostMap(myWorld.worldMap[lastVisitedY][max(0, lastVisitedX - 1)], 'R');
                }
                else {
                    myWorld.player.playerY = myWorld.worldMap[lastVisitedY][min(400, lastVisitedX - 1)]->roadEastY;
                    myWorld.player.playerX = 78;
                    myWorld.worldMap[lastVisitedY][min(400, lastVisitedX - 1)]->characterMap[myWorld.player.playerY][myWorld.player.playerX] = '@';
                    printMap(*myWorld.worldMap[lastVisitedY][min(400, lastVisitedX - 1)]);
                    
                }
                lastVisitedX -= 1;
                charHeap_init(&cH);
                cN = charHeap_pop(&cH);
            }
            else if (myWorld.worldMap[lastVisitedY][lastVisitedX]->roadNorthX == myWorld.player.playerX && myWorld.player.playerY == 0){
                myWorld.worldMap[lastVisitedY][lastVisitedX]->characterMap[myWorld.player.playerY][myWorld.player.playerX] = 'X';
                if (myWorld.worldMap[max(0, lastVisitedY - 1)][lastVisitedX] == NULL){
                    myWorld.worldMap[max(0, lastVisitedY - 1)][lastVisitedX] = (map_t *) malloc(sizeof (map_t));
                    buildMap(myWorld.worldMap[max(0, lastVisitedY - 1)][lastVisitedX], max(0, lastVisitedY - 1), lastVisitedX, 'n');
                    generateCostMap(myWorld.worldMap[max(0, lastVisitedY - 1)][lastVisitedX], 'H');
                    generateCostMap(myWorld.worldMap[max(0, lastVisitedY - 1)][lastVisitedX], 'R');
                }
                else {
                    myWorld.player.playerX = myWorld.worldMap[max(0, lastVisitedY - 1)][lastVisitedX]->roadSouthX;
                    myWorld.player.playerY = 19;
                    myWorld.worldMap[max(0, lastVisitedY - 1)][lastVisitedX]->characterMap[myWorld.player.playerY][myWorld.player.playerX] = '@';
                    printMap(*myWorld.worldMap[max(0, lastVisitedY - 1)][lastVisitedX]);
                }
                lastVisitedY -= 1;
                charHeap_init(&cH);
                cN = charHeap_pop(&cH);
            }
            else if (myWorld.worldMap[lastVisitedY][lastVisitedX]->roadSouthX == myWorld.player.playerX && myWorld.player.playerY == 20){
                myWorld.worldMap[lastVisitedY][lastVisitedX]->characterMap[myWorld.player.playerY][myWorld.player.playerX] = 'X';
                if (myWorld.worldMap[min(400, lastVisitedY + 1)][lastVisitedX] == NULL){
                    myWorld.worldMap[min(400, lastVisitedY + 1)][lastVisitedX] = (map_t *) malloc(sizeof (map_t));
                    buildMap(myWorld.worldMap[min(400, lastVisitedY + 1)][lastVisitedX], min(400, lastVisitedY + 1), lastVisitedX, 's');
                    generateCostMap(myWorld.worldMap[min(400, lastVisitedY + 1)][lastVisitedX], 'H');
                    generateCostMap(myWorld.worldMap[min(400, lastVisitedY + 1)][lastVisitedX], 'R');            
                }
                else {
                    myWorld.player.playerX = myWorld.worldMap[min(400, lastVisitedY + 1)][lastVisitedX]->roadNorthX;
                    myWorld.player.playerY = 1;
                    myWorld.worldMap[min(400, lastVisitedY + 1)][lastVisitedX]->characterMap[myWorld.player.playerY][myWorld.player.playerX] = '@';
                    printMap(*myWorld.worldMap[min(400, lastVisitedY + 1)][lastVisitedX]);
                }
                lastVisitedY += 1;
                charHeap_init(&cH);
                cN = charHeap_pop(&cH);
            }
            else if (myWorld.worldMap[lastVisitedY][lastVisitedX]->singleMap[myWorld.player.playerY][myWorld.player.playerX] == ':'){
                int random = rand() % (10 + 1 - 1) + 1;
                if (random <= 2){
                    std::vector<actualPokemon_t> wildPoke;
                    actualPokemon_t * poke = new actualPokemon_t;
                    tallGrassEncounter(myWorld.worldMap[lastVisitedY][lastVisitedX], poke, lastVisitedX, lastVisitedY, false);
                    wildPoke.push_back(*poke);
                    //on screen
                    battleStart(wildPoke, false);
                    delete poke;
                }
            }
        }
        cN.moveTime += terrainGetter(myWorld.worldMap[lastVisitedY][lastVisitedX], cN.symbol);
        charHeap_add(&cH, cN);
        printMap(*myWorld.worldMap[lastVisitedY][lastVisitedX]);
        myWorld.player.worldX = lastVisitedX;
        myWorld.player.worldY = lastVisitedY;
        usleep(75000);
    }
    freeHomies();
    return 0;
}
    


