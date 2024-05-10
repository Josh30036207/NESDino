// collision data, made by exporting csv from Tiled, and slight modification by CSV2C.py
#include "BG/maps.c" 
#include "sprites.h"


// GLOBAL VARIABLES
// all variables should be global for speed  //I'm sorry Marius
// zeropage global is even faster

unsigned char pad1;
unsigned char pad1_new;
unsigned char collision;
unsigned char which_bg;
const unsigned char * p_maps;
unsigned char coordinates;
int steptimer = 0; //step timer - used to slow down the sprite step animation
int maxSTimer = 4; //max step timer
unsigned char stepAlt = '0';
const unsigned char *dinoSprite;
const unsigned char *obSprite;
const unsigned char *obSprite2;
const unsigned char *birbSprite;
const unsigned char *cloudSprite;

int score = 0;
int hiScr = 0;
int test;
int loop = 1;
int i;
int trwTmr = 10;
int rng = 0;
unsigned char jump = '0';
unsigned char fall = '0';
unsigned char grnd = '1';
unsigned char lose = '0';
unsigned char filpFlop = '0';

 struct object { //basic entity
	unsigned char x;
	unsigned char y;
	unsigned char width;
	unsigned char height;
	unsigned char thrown;
	const unsigned char *sprite;
	const unsigned char *ogSpr;
};


struct object dino = {32,211,14,14,'0',dinoSp1,dinoSp1};
struct object cacti = {254, 211, 6, 14,'0',null,cSp1};
struct object cacti2 = {254, 211, 6, 10,'0',null,cSp2};

struct object birb = {254, 202, 13, 9,'0',null,bSp};
struct object cloud = {0, 32, 30, 13,0,clSp,clSp};
struct object obs[3];



unsigned char c_map[240];
unsigned char test_map[240];
// collision map 
const unsigned char * const All_Collision_Maps[] = {map0};//add the maps to the array


//Prototypes
void drawSprites(void);
void moveCloud(void);	
void walk(void);	
void checkCollision(void);
void draw_bg(void);
void abBtn(void);
void ssBtn(void);
void moveObs(void);

void loseCheck(void);
void gameOver(void);
void clearScreen(void);
void displayScore(void);
void reset(void);

int rtnDig(int value);
int digit;
int counter = 0;
int test = 0;
void digNum(int value);
unsigned char scrBrd[5];
unsigned char hiBrd[5];

// bg draw variables
int address;
unsigned char x; 
unsigned char y;
unsigned char index;

int posChk = 0;
int pause = 0;
