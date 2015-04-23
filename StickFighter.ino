#include <SPI.h>
#include <Gamebuino.h>
Gamebuino gb;
#include <Wire.h>

const byte idle1[] PROGMEM = {8,12,0x78,0x78,0x78,0x20,0x70,0xA8,0xEC,0x20,0x20,0x50,0x48,0x6C,};
const byte idle2[] PROGMEM = {8,12,0x0,0x78,0x78,0x78,0x20,0x70,0xA8,0xEC,0x20,0x50,0x48,0x6C,};
const byte run1[] PROGMEM = {8,12,0x78,0x78,0x78,0x70,0xA8,0xEC,0x20,0x20,0x24,0xDC,0x80,0x0,};
const byte run2[] PROGMEM = {8,12,0x78,0x78,0x78,0x20,0x70,0xA8,0xEC,0x20,0x20,0x20,0x20,0x30,};
const byte kick1[] PROGMEM = {16,12,0x78,0x0,0x78,0x0,0x78,0x0,0x30,0x0,0x7C,0x0,0xA0,0x0,0xE0,0x10,0x20,0xF0,0x3F,0x0,0x40,0x0,0x80,0x0,0xC0,0x0,};
const byte punchLeft1[] PROGMEM = {16,12,0x78,0x0,0x78,0x0,0x78,0x0,0x20,0x0,0x7F,0xF0,0xA0,0x0,0xE0,0x0,0x20,0x0,0x20,0x0,0x50,0x0,0x48,0x0,0x6C,0x0,};
const byte punchRight1[] PROGMEM = {16,12,0x78,0x0,0x78,0x0,0x78,0x0,0x20,0x0,0x60,0x0,0xFF,0x80,0x2C,0x0,0x20,0x0,0x20,0x0,0x50,0x0,0x48,0x0,0x6C,0x0,};
const byte duck1[] PROGMEM = {8,6,0x78,0x78,0x20,0xFC,0x48,0x6C,};
const byte duckKick1[] PROGMEM = {16,6,0x78,0x0,0x78,0x0,0x20,0x0,0xFC,0x0,0x48,0x0,0x47,0xC0,};
const byte jump1[] PROGMEM = {8,12,0x78,0x78,0x78,0x24,0x24,0x78,0xA0,0xA0,0x38,0x44,0x84,0x0,};
const byte jumpKick1[] PROGMEM = {16,12,0x78,0x0,0x78,0x0,0x78,0x0,0x24,0x0,0x24,0x0,0x78,0x0,0xA0,0x0,0xA0,0x0,0x3F,0xE0,0x40,0x0,0x80,0x0,0x0,0x0,};
const byte dead1[] PROGMEM = {16,4,0xE0,0x0,0xE0,0x0,0xEF,0x80,0xFC,0x70,};

const byte p2idle1[] PROGMEM = {8,12,0x78,0x58,0x78,0x20,0x70,0xA8,0xEC,0x20,0x20,0x50,0x48,0x6C,};
const byte p2idle2[] PROGMEM = {8,12,0x0,0x58,0x78,0x78,0x20,0x70,0xA8,0xEC,0x20,0x50,0x48,0x6C,};
const byte p2run1[] PROGMEM = {8,12,0x78,0x58,0x78,0x70,0xA8,0xEC,0x20,0x20,0x24,0xDC,0x80,0x0,};
const byte p2run2[] PROGMEM = {8,12,0x78,0x58,0x78,0x20,0x70,0xA8,0xEC,0x20,0x20,0x20,0x20,0x30,};
const byte p2jumpKick1[] PROGMEM = {16,12,0x78,0x0,0x58,0x0,0x78,0x0,0x24,0x0,0x24,0x0,0x78,0x0,0xA0,0x0,0xA0,0x0,0x3F,0xE0,0x40,0x0,0x80,0x0,0x0,0x0,};
const byte p2punchLeft1[] PROGMEM = {16,12,0x78,0x0,0x58,0x0,0x78,0x0,0x20,0x0,0x7F,0xF0,0xA0,0x0,0xE0,0x0,0x20,0x0,0x20,0x0,0x50,0x0,0x48,0x0,0x6C,0x0,};
const byte p2punchRight1[] PROGMEM = {16,12,0x78,0x0,0x58,0x0,0x78,0x0,0x20,0x0,0x60,0x0,0xFF,0x80,0x2C,0x0,0x20,0x0,0x20,0x0,0x50,0x0,0x48,0x0,0x6C,0x0,};
const byte p2duck1[] PROGMEM = {8,6,0x78,0x58,0x20,0xFC,0x48,0x6C,};
const byte p2duckKick1[] PROGMEM = {16,6,0x78,0x0,0x58,0x0,0x20,0x0,0xFC,0x0,0x48,0x0,0x47,0xC0,};
const byte p2jump1[] PROGMEM = {8,12,0x78,0x58,0x78,0x24,0x24,0x78,0xA0,0xA0,0x38,0x44,0x84,0x0,};
const byte p2kick1[] PROGMEM = {16,12,0x78,0x0,0x58,0x0,0x78,0x0,0x30,0x0,0x7C,0x0,0xA0,0x0,0xE0,0x10,0x20,0xF0,0x3F,0x0,0x40,0x0,0x80,0x0,0xC0,0x0,};
const byte p2dead1[] PROGMEM = {16,4,0xE0,0x0,0xE0,0x0,0xAF,0x80,0xFC,0x70,};


const byte fire1[] PROGMEM = {8,13,0x0,0xF0,0xF0,0xF0,0x48,0x78,0x40,0x78,0x48,0x40,0xA0,0xA0,0xF0,};
const byte fireBall1[] PROGMEM = {8,6,0xF8,0x7C,0xCC,0xCC,0x7C,0xF8,};
const byte fireBall2[] PROGMEM = {8,6,0x38,0xC4,0xB4,0xB4,0xC4,0x38,};


/* fake button for slave*/
boolean bt_up,bt_down,bt_left,bt_right,bt_a,bt_b;


typedef struct {
  byte const * sprite1;
  byte const * sprite2;
}animSprite;

#define NB_STATE 11
#define NB_SPRITE_STATE 2
#define TIME_ATTACK 2
#define SPEED_RUN 3
#define GROUND_Y 42
#define TIME_DEF 2
#define NB_MOVE_SAVE 4
#define TIME_LIVE_AYOUKEN 15
#define VITT_AYOUKEN 3
#define DAMAGE_AYOUKEN 10
typedef struct {
  byte posX,posY,timeLive,dir;
  animSprite sprites;
}
Ayouken;

#define TIME_FALL  5
typedef struct {
  uint8_t currentState; // IDL : 0 ,run : 1, kick : 2, punchLeft : 3, punchRight : 4,  duck1 : 5, duck1Kick : 6,jump1 : 7,jumpKick1 : 8 , dead1 : 9 , 10 Fire
  uint8_t currentSprite;//sprite 1 or 2
  float posX,posY;
  float vx,vy;
  uint8_t height,width;
  animSprite sprites[NB_STATE];
  int8_t life;
  int8_t oldLife;
  int8_t cadance;//speed of change sprite
  int8_t damage; //damage current punch
  byte dir; //NOFLIP -> and FLIPH <-
  int8_t timeAttack,timeNextAttack;
  boolean isJump;
  byte cptVictory;
  byte isDef;
  Ayouken ayouken;
  byte combo[NB_MOVE_SAVE];
  uint8_t timeFall;  
}
Figther;

Figther Player1 = {0,0,8,29,0,0,13,8,{{idle1,idle2},{run1,run2},{kick1,kick1},{punchLeft1,punchLeft1},{punchRight1,punchRight1},{duck1,duck1},{duckKick1,duckKick1},{jump1,jump1},{jumpKick1,jumpKick1},{dead1,dead1},{fire1,fire1}},100,100,2,5,NOFLIP,4,8,false,0,0,{0,0,0,NOFLIP,fireBall1,fireBall2},0};
Figther Player2 = {0,0,8,29,0,0,13,8,{{p2idle1,p2idle2},{p2run1,p2run2},{p2kick1,p2kick1},{p2punchLeft1,p2punchLeft1},{p2punchRight1,p2punchRight1},{p2duck1,p2duck1},{p2duckKick1,p2duckKick1},{p2jump1,p2jump1},{p2jumpKick1,p2jumpKick1},{p2dead1,p2dead1},{fire1,fire1}},100,100,2,5,FLIPH,4,8,false,0,0,{0,0,0,FLIPH,fireBall1,fireBall2},0};

#define CPT_COMBAT_INIT 30
byte cptCombat = 0;
byte stateFight;

boolean isMaster;
boolean isOnePlayer;
boolean isPaused;
boolean disconnected;
boolean slave_updated = false;
byte xoffsetCptGras;
byte yoffsetTimeUp;
byte cptTechArena;

byte stateGame = 3; //3 main menu, 0 game , 1 multiplayer menu , 2 option , 4 final screen ..... 

void leftFigther(Figther * player);
void rightFigther(Figther * player);
void highFigther(Figther * player);
void bottomFigther(Figther * player);
void punchFigther(Figther * player);
void kickFigther(Figther * player);
void initPlayer(boolean isStartGame);
void moveIAPlayer(Figther * player,Figther * human);

/***********************************************
************Multiplayer const ******************
************************************************/
#define SLAVE_PAUSED 1
#define I_AM_MASTER 2
#define GAME_STATE 3
#define STATE_FIGHT 4
#define CPT_TECH_ARENA 5

#define P1_X 10
#define P1_Y 11
#define P1_STATE 12
#define P1_CURRENT_SPRITE 13
#define P1_H 14
#define P1_W 15
#define P1_HP 16
#define P1_CPT_VICTORY 17
#define P1_DIR 18

#define P2_X 20
#define P2_Y 21
#define P2_STATE 22
#define P2_CURRENT_SPRITE 23
#define P2_H 24
#define P2_W 25
#define P2_HP 26
#define P2_CPT_VICTORY 27
#define P2_DIR 28

/*arene*/
#define X_OFFSET_CPT_GRAS 30
#define CPT_COMBAT 31
#define CPT_OFFFSET_TIME_UP 32

/*SLAVE*/
#define BT_UP 41
#define BT_DOWN 42
#define BT_LEFT 43
#define BT_RIGHT 44
#define BT_A 45
#define BT_B 46

#define SLAVE_DATA_BUFFER_LENGTH 12

void setup()
{
  gb.begin();
  goTitleScreen();
}

void initGame()
{
  gb.battery.show = false;
  stateGame = 3;
  isMaster = true; //TODO Multiplayer game 
  isOnePlayer = true; //TODO Multiplayer game 
  slave_updated = false;
  isPaused = false;
  disconnected = false;
  initMainMenu();
  initPlayer();
  initArena();
  initFinalScreen();
}

const char strMaster[] PROGMEM = "Host (master)";
const char strSlave[] PROGMEM = "Join (slave)";
const char* const multiPlayerMenu[2] PROGMEM = {
  strMaster,
  strSlave
};

void loop(){

 if(gb.update())
 {
    if(gb.buttons.pressed(BTN_C)){
      //initGame();
      goTitleScreen();
    }
    if(stateGame == 3)
    {
      updateMainMenu();
      drawMainMenu();
    }
    else if(stateGame == 4)
    {
      updateFinalScreen();
      drawFinalScreen();
      if(isMaster && !isOnePlayer)
      {
         updateMaster();
      }
    }
    else if(stateGame == 1)
    {
      //multiplayer menu
      switch(gb.menu(multiPlayerMenu, 2)){
        case 0: //Host      
          isPaused = false;
          disconnected = false;
          isMaster = true;
          isOnePlayer = false;
          stateGame = 0;
          break;
        case 1: //Join
          isPaused = false;
          disconnected = false;
          isMaster = false;
          isOnePlayer = false;
          stateGame = 0;
          break;
        default:
          stateGame = 3;
          break;
       }
    }
    else if(stateGame == 2)
    {
        moveIAPlayer(&Player2,&Player1);
        moveIAPlayer(&Player1,&Player2);
        updatePlayer();
        updateArena();
        drawPlayer();
        drawArena();
        credit();
    }
    else 
    {
      //gb.popup(F("Is not posed"),20);
      if(isMaster && !isOnePlayer)
      {
         updateMaster();
      }
      else if(!isMaster && !isOnePlayer)
      {
        updatePlayerSalve();
        updateSlave();
      }
      
      if(!isPaused || isOnePlayer || !isMaster)
      {
        if(isMaster || isOnePlayer)
        {
          updatePlayer();
          updateArena();
        }  
   
       if(isOnePlayer)
        {
            moveIAPlayer(&Player2,&Player1);
        }      
      }
      drawPlayer();
      drawArena();
      //gb.display.print(stateFight);
    }
 }
}


