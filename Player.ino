
void updPlayer(Figther * player);
void drwPlayer(Figther * player);
void movePlayer(Figther * player);
void moveIAPlayer(Figther * player);
void changeBoundPlayer(Figther * player);



/*
uint8_t currentSprite;//permet de savoir sur quel sprite on est 0 : heliport,   1 -> 49 bat deco , >49 bat attaque
  uint8_t posX,posY;
  float vx,vy;
  uint8_t height;
  animSprite sprites[NB_STATE];
  int8_t life;
  int8_t cadance;//speed of change sprite
  int8_t damage; //damage current punch
  boolean dir; //true -> and false <-
  */
void initPlayer()
{
  Player1.currentState = 0;
  Player1.currentSprite = 0;
  Player1.posX = 8;
  Player1.posY = 42;
  Player1.vx = 0;
  Player1.vy = 0;
  Player1.height = 12;
  Player1.width = 8;
  Player1.life = 100;
  Player1.cadance = 2;
  Player1.damage = 5;
  Player1.dir = NOFLIP;
  Player1.timeAttack = TIME_ATTACK;
  Player1.isJump = false;
  
  
  Player2.currentState = 0;
  Player2.currentSprite = 0;
  Player2.posX = 76;
  Player2.posY = 42;
  Player2.vx = 0;
  Player2.vy = 0;
  Player2.height = 12;
  Player2.width = 8;
  Player2.life = 100;
  Player2.cadance = 2;
  Player2.damage = 5;
  Player2.dir = FLIPH;
  Player2.timeAttack = TIME_ATTACK;
  Player2.isJump = false;
}

void updatePlayer()
{
  if(stateFight == 1)
  {
    if(isOnePlayer)
    {
      //gestion IA
      if(isMaster)
      {
        moveIAPlayer(&Player2);
      }
      else 
      {
        moveIAPlayer(&Player1);
      }
    }
    if(isMaster)
    {
      movePlayer(&Player1);
    }
    else 
    {
      movePlayer(&Player2);
    }
  }
  
  updPlayer(&Player1);
  updPlayer(&Player2);
}

void drawPlayer()
{
  drwPlayer(&Player1);
  drwPlayer(&Player2);
}

void drwPlayer(Figther * player)
{
  gb.display.drawBitmap( ((player->dir == FLIPH) ?  (player->posX - player->width)  : player->posX ),(player->posY - player->height) , ((player->currentSprite == 0) ? player->sprites[player->currentState].sprite1 : player->sprites[player->currentState].sprite2 ), 0,player->dir);
}

void updPlayer(Figther * player)
{
  if(gb.frameCount%player->cadance == 0)
  {
    player->currentSprite++;
    player->currentSprite = player->currentSprite%NB_SPRITE_STATE;
  }
  
  if(player->timeAttack>0)
  {
    player->timeAttack--;
    if(player->timeAttack==0)
    {
      player->currentState = 0;
      changeBoundPlayer(player);
    }
  }
}


void movePlayer(Figther * player)
{
  if(gb.buttons.pressed(BTN_A))
  {
    punchFigther(player);
  }
  else if(gb.buttons.pressed(BTN_B))
  {
    kickFigther(player);
  }
}

void moveIAPlayer(Figther * player)
{
  if(random(0,100) ==0)
  {
    punchFigther(player);
  }
}

void leftFigther(Figther * player)
{
  player->currentState = 3;
  changeBoundPlayer(player);
}

void rightFigther(Figther * player)
{
  player->currentState = 3;
  changeBoundPlayer(player);
}

void highFigther(Figther * player)
{
  player->currentState = 3;
  changeBoundPlayer(player);
}

void bottomFigther(Figther * player)
{
  player->currentState = 3;
  changeBoundPlayer(player);
}

void punchFigther(Figther * player)
{
  player->timeAttack = TIME_ATTACK;
  player->currentState = 3;
  changeBoundPlayer(player);
}

void kickFigther(Figther * player)
{
  player->timeAttack = TIME_ATTACK;
  player->currentState = 2;
  changeBoundPlayer(player);
}

void changeBoundPlayer(Figther * player)
{
  player->width = pgm_read_byte(player->sprites[player->currentState].sprite1);
  player->height = pgm_read_byte(player->sprites[player->currentState].sprite1 + 1);
}

