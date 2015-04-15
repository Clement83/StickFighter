
void updPlayer(Figther * player);
void drwPlayer(Figther * player);
void movePlayer(Figther * player);
void moveIAPlayer(Figther * player);
void changeBoundPlayer(Figther * player);
boolean playerIsAttack(Figther player);
void gestionAttack(Figther * pAttack, Figther * pDef);

boolean stopGame=false;

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
  initPlayer(true);
}
void initPlayer(boolean isStartGame)
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
  Player1.oldLife = 100;
  Player1.cadance = 2;
  Player1.damage = 5;
  Player1.dir = NOFLIP;
  Player1.timeAttack = TIME_ATTACK;
  Player1.isJump = false;
  
  Player2.currentState = 0;
  Player2.currentSprite = 0;
  Player2.posX = 68;
  Player2.posY = 42;
  Player2.vx = 0;
  Player2.vy = 0;
  Player2.height = 12;
  Player2.width = 8;
  Player2.life = 100;
  Player2.oldLife = 100;
  Player2.cadance = 2;
  Player2.damage = 5;
  Player2.dir = FLIPH;
  Player2.timeAttack = TIME_ATTACK;
  Player2.isJump = false;
  
  if(isStartGame)
  {  
    Player1.cptVictory = 0;
    Player2.cptVictory = 0;
  }
  stopGame = true;
}
void updatePlayer()
{
  
   switch(stateFight)
  {
    case 0 :
       //3, 2, 1 Fight! 

    break;
    case 1 :
       //Fight 
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
    break;
    case 2 :
       //Figther KO 
    case 3 :
       //Time UP 
       if(stopGame)
       {
         if(Player1.life != Player2.life)
         {
           if(Player1.life>Player2.life)
           {
             Player1.cptVictory++;
           }
           else
           {
             Player2.cptVictory++;
           }
         }
         stopGame=false;
       }
    break;
  }
  
  
  updPlayer(&Player1);
  updPlayer(&Player2);
  
  //update dir player 
  if(Player1.posX<Player2.posX)
  {
    Player1.dir = NOFLIP;
    Player2.dir = FLIPH;
  }
  else 
  {
    Player1.dir = FLIPH;
    Player2.dir = NOFLIP;
  }
  
  if(playerIsAttack(Player1))
  {
    gestionAttack(&Player1,&Player2);
    
  }
  if(playerIsAttack(Player2)) 
  {
      gestionAttack(&Player2,&Player1);
  }
}

void gestionAttack(Figther * pAttack, Figther * pDef)
{
    // IDL : 0 ,run : 1, kick : 2, punchLeft : 3, punchRight : 4,  duck1 : 5, duck1Kick : 6,jump1 : 7,jumpKick1 : 8 , dead1 : 9
    byte damage = 0;
    if(pAttack->currentState == 3 || pAttack->currentState == 4)
    {
      if(gb.collideRectRect(pAttack->posX - 4, pAttack->posY, 16, 5, pDef->posX, pDef->posY, pDef->width, pDef->height))
      {
        damage = 10;
      }
    }
    else if(pAttack->currentState == 2 || pAttack->currentState == 8)
    {
        
    }
    else if(pAttack->currentState == 6)
    {
      
    }
    
    if(damage)
    {
      pDef->life -= damage;
      if(pDef->life <0)
      {
        pDef->life = 0;
      }
      //gestion des colisions
      if(pDef->dir == NOFLIP)
      {
        //Pdef a gauche 
        pDef->vx = -SPEED_RUN;
      }
      else 
      {
        //Pdef a droite 
        pDef->vx = SPEED_RUN;
      }
    }
}

void drawPlayer()
{
  drwPlayer(&Player1);
  drwPlayer(&Player2);
  //  gb.display.print(Player1.currentState);
  
  //vie P1
  gb.display.fillRect(14, 2, lifeTopixel(Player1.life), 3);
  //vie P2
  byte offsetPx = lifeTopixel(Player2.life);
  gb.display.fillRect(47 + (23-offsetPx) , 2, offsetPx , 3);
  
  for(byte i=0;i<Player1.cptVictory;i++)
  {
    //2 - 7 - 12
    gb.display.fillRect((i*5 + 2) , 8, 2 , 2);
    
  }
}

byte lifeTopixel(byte life)
{
  return (life*0.23);
}

void drwPlayer(Figther * player)
{
  gb.display.drawBitmap(((player->dir == NOFLIP)? player->posX : (player->posX -(player->width-8) ) ) ,(player->posY - player->height) , ((player->currentSprite == 0) ? player->sprites[player->currentState].sprite1 : player->sprites[player->currentState].sprite2 ), 0,player->dir);
}
#define SEUIL_MIN_MOVE 0.1
void updPlayer(Figther * player)
{
  if(gb.frameCount%player->cadance == 0)
  {
    player->currentSprite++;
    player->currentSprite = player->currentSprite%NB_SPRITE_STATE;
  }
  
  if(player->timeNextAttack>0)
  {
    player->timeNextAttack--;
  }
  
  if(player->timeAttack>0)
  {
    player->timeAttack--;
  }
  
  if(player->life>0)
  {
    if(player->timeAttack==0 && player->currentState != 0 && player->currentState != 5)
    {
      if(player->currentState == 6)
        player->currentState = 5;
      else if(player->isJump)
        player->currentState = 7;
      else if(player->vx<SEUIL_MIN_MOVE && player->vx>-SEUIL_MIN_MOVE)
        player->currentState = 0;
      else 
        player->currentState = 1;
      
      changeBoundPlayer(player);
    }
  }
  else 
  {
    player->currentState = 9;
    changeBoundPlayer(player);
  }
  
  if(!player->isJump)
  {
    if(player->vx!=0)
    {
      player->posX += player->vx;
      player->vx = player->vx*0.4;//on ralentie rapidement
    }
    else if(player->vx<SEUIL_MIN_MOVE && player->vx>-SEUIL_MIN_MOVE)
    {
      player->vx = 0;
    }
  }
  else 
  {
    
    if(player->vy<-1)
    {
      player->vy *= 0.9;
      player->posY += player->vy;
    }
    else
    {
      if(player->vy<0) player->vy = -player->vy;
      player->vy *= 1.3;
      player->posY += player->vy;
    }
    player->posX += player->vx;
    player->vx = player->vx*0.9;//on ralentie rapidement
    
    if(player->posY>= GROUND_Y)
    {      
      player->posY = GROUND_Y;
      player->isJump = false;
      player->vy = 0;
      player->vx = 0;
    }
  }
  
  if(player->posX<0)
  {
    player->posX = 0;
  }
  else if((player->posX + player->width) >84)
  {
    player->posX = (84 - player->width);
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
  
  if(gb.buttons.repeat(BTN_RIGHT, 1))
  {
    rightFigther(player);
  }
  else if(gb.buttons.repeat(BTN_LEFT, 1))
  {
    leftFigther(player);
  }
  if(gb.buttons.pressed(BTN_UP))
  {
    highFigther(player);
  }
  else if(gb.buttons.repeat(BTN_DOWN, 1))
  {
    bottomFigther(player);
  }
}

void moveIAPlayer(Figther * player)
{
  if(random(0,100) ==0)
  {
    punchFigther(player);
  }
  if(random(0,30) ==0)
  {
    if(player->dir == NOFLIP) rightFigther(player);
    else leftFigther(player);
  }
}

// IDL : 0 ,run : 1, kick : 2, punchLeft : 3, punchRight : 4,  duck1 : 5, duck1Kick : 6,jump1 : 7,jumpKick1 : 8 , dead1 : 9
void leftFigther(Figther * player)
{
  if(player->life==0)
    return;
  if(!player->isJump)
  {
    player->vx =  -SPEED_RUN;
    if(!playerIsAttack(*player)) player->currentState = 1;
  }
  else 
  {
    if(player->vx>-SPEED_RUN) player->vx -= 0.1;
  }
    changeBoundPlayer(player);
}

void rightFigther(Figther * player)
{
  if(player->life==0)
    return;
  if(!player->isJump)
  {
    player->vx =  SPEED_RUN;
    if(!playerIsAttack(*player))player->currentState = 1;
  }
  else 
  {
    if(player->vx<SPEED_RUN) player->vx += 0.1;
  }
    changeBoundPlayer(player);
}

void highFigther(Figther * player)
{
  if(player->life==0)
    return;
 if(!player->isJump)
 {
    player->currentState = 7;
    changeBoundPlayer(player);
    player->isJump = true;
    player->vy = -SPEED_RUN;
 }
}

void bottomFigther(Figther * player)
{
  if(player->life==0)
    return;
  player->currentState = 5;
  changeBoundPlayer(player);
}

void punchFigther(Figther * player)
{
  if(player->life==0)
    return;
  if(player->timeNextAttack>0)
    return;
  if(!player->isJump)
 {
  player->currentState = random(3,5);
 }
 else 
 {
  player->currentState = 8;
 }
  player->timeAttack = TIME_ATTACK;
  player->timeNextAttack = TIME_ATTACK+1;
  changeBoundPlayer(player);
}

void kickFigther(Figther * player)
{
  if(player->life==0)
    return;
  if(player->timeNextAttack>0)
    return;
  player->timeAttack = TIME_ATTACK;
  player->timeNextAttack = TIME_ATTACK+1;
  player->currentState = 2;
  changeBoundPlayer(player);
}

void changeBoundPlayer(Figther * player)
{
  player->width = pgm_read_byte(player->sprites[player->currentState].sprite1);
  player->height = pgm_read_byte(player->sprites[player->currentState].sprite1 + 1);
}

boolean playerIsAttack(Figther player)
{
  return player.timeAttack>0;
}

