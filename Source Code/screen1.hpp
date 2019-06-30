//game screen

#include <iostream>
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include "screens.hpp"
#include <cstdlib>
#include <ctime>
#include <time.h>

using namespace sf;

class screen1:public cScreen{
public:
    virtual int Run (sf::RenderWindow &App);
};

extern int levelcomp[3];
extern int play;
extern int level;

int gemTypes=3;

int ts = 60; //tile size default 54
Vector2i offset(30,40); // default (48,24);

struct piece
{ int x,y,col,row,kind,match,alpha;
piece(){match=0; alpha=255;}
} grid[10][10];

void swap(piece p1,piece p2)
{
  std::swap(p1.col,p2.col);
  std::swap(p1.row,p2.row);

  grid[p1.row][p1.col]=p1;
  grid[p2.row][p2.col]=p2;
}

int checkgame(piece x[][10],int x1,int y1,int kind){
    if(x1>=1 && y1>=1 && x1<=8 && y1<=8&&x[y1][x1].match==0){
        if(x[y1][x1].kind==kind){
            x[y1][x1].match++;
            checkgame(x,x1-1,y1,kind);
            checkgame(x,x1+1,y1,kind);
            checkgame(x,x1,y1-1,kind);
            checkgame(x,x1,y1+1,kind);
        }
        else{
            return 0;
        }
    }
}

void rocketUp(piece x[][10],int y1,int x1){ //for rocket power up
    int coord[2][2]={{x1,0},{0,y1}};
    for(int i=0;i<10;i++){
        if(x[x1][i].match!=1)
            x[x1][i].match++;
        if(x[i][y1].match!=1)
            x[i][y1].match++;
    }
}

void saveGame(){
    std::ofstream file;
    std::string temp;
    file.open("resource/data1.txt");
    for(int i=0;i<3;i++){
        file<<levelcomp[i]<<std::endl;
    }
    file.close();
}


int screen1::Run(sf::RenderWindow &App){

    srand(time(0));

    Texture t1,t2,t3,t4,t5,t6,t7,t8,t9;
    t1.loadFromFile("resource/images/gamebg.png");
    t2.loadFromFile("resource/images/gems.png");
    t3.loadFromFile("resource/images/cursor.png");
    t4.loadFromFile("resource/images/leave.png");
    t5.loadFromFile("resource/images/firstplaymat.png");
    t6.loadFromFile("resource/images/win.png");
    t7.loadFromFile("resource/images/fail.png");
    t8.loadFromFile("resource/images/power.png");
    t9.loadFromFile("resource/images/ice.png");

    Sprite background(t1), gems(t2),cursor(t3), leave(t4),firstplaymat(t5),levelwin(t6),levelfail(t7),power(t8),ice(t9);

    leave.setOrigin(leave.getGlobalBounds().width/2,leave.getGlobalBounds().height/2);
    leave.setPosition(550,570);

    power.setOrigin(power.getGlobalBounds().width/2,power.getGlobalBounds().height/2);
    power.setPosition(100,570);


    Font font;
    font.loadFromFile("resource/font.ttf");
    Text text,turns,powerupTurn;
    text.setFont(font);
    turns.setFont(font);
    powerupTurn.setFont(font);

    int turn = 50;// <-------------------- set turns
    int powerupleft = 2;

    text.setString(std::to_string(turn));
    turns.setString("Turns: ");
    powerupTurn.setString(std::to_string(powerupleft));

    text.setCharacterSize(75);
    turns.setCharacterSize(50);
    powerupTurn.setCharacterSize(50);


    text.setColor(Color::Red);
    turns.setColor(Color::Black);
    powerupTurn.setColor(Color::Red);

    text.setPosition(550,100);
    turns.setPosition(510,50);
    powerupTurn.setPosition(200,540);


    bool leaveb=false,powerb=false;


    bool expand[10][10]={false};

	for (int i=1;i<=8;i++)
     for (int j=1;j<=8;j++)
      {
          grid[i][j].kind=rand()%3;
          grid[i][j].col=j;
          grid[i][j].row=i;
          grid[i][j].x = j*ts;
          grid[i][j].y = i*ts;
      }

    int x0,y0,x,y; int click=0; Vector2i pos;
    bool isSwap=false, isMoving=false;
    int score=0;
    int curscore=0;
    bool bg[10][10]={false}; //important for play mat <---------------------

    bool bgice[10][10]={false}; //for ice
    randIce(bgice,level*1.0/15*100); //generate random ice

    int levelincreased=0;

    int fadein=255;
    sf::Texture t10;
    t10.loadFromFile("resource/images/transition.png");

    sf::Sprite transition(t10);

    bool powerclicked=false;

    sf::SoundBuffer buffer;
    sf::Sound sound;
    buffer.loadFromFile("resource/zap.wav");
    sound.setBuffer(buffer);
    sound.play();

    sf::Music music;
    music.openFromFile("resource/music.wav");
    music.play();

    while (App.isOpen())
    {
        Event e;
        int gamedone =0;
        for(int i=1;i<=8;i++)
        for(int j=1;j<=8;j++){
            if(bg[i][j])
                gamedone++;
        }
        if(gamedone==64){
        //return 0;
            App.draw(levelwin);
            levelincreased++;
            if(levelincreased==1){
                levelcomp[play]++;
                saveGame();
            }

        }



        while (App.pollEvent(e))
        {
            if (e.type == Event::Closed)
                App.close();

			if (e.type == Event::MouseButtonPressed){
				if (e.key.code == Mouse::Left)
				{
				   if (!isSwap && !isMoving) click++;
				   pos = Mouse::getPosition(App)-offset;
				   sound.play();
                }
                if(gamedone==64)
                    return 3;
                if(turn<=0)
                    return 3;

                if(mouseOverObj(App,leave))
                    return 0;
                if(mouseOverObj(App,power)&&powerupleft>0){
                    powerclicked=true;
                    click=0;
                    powerupleft--;
                    powerupTurn.setString(std::to_string(powerupleft));
                }
			}
         }

    animateButton(App,leave,leaveb);
    animateButton(App,power,powerb);

    //for rocket power up
    if(powerclicked&&click==1){
        x0=pos.x/ts+1 ;  //get the index of the tile from the position of mouse
        y0=pos.y/ts+1 ;
        rocketUp(grid,x0,y0);
        powerclicked=false;
        click=0;
    }

    else{
        // mouse click
        if (click==1){
            x0=pos.x/ts+1 ;  //get the index of the tile from the position of mouse
            y0=pos.y/ts+1 ;
            int kind=grid[y0][x0].kind;
            checkgame(grid,x0,y0,kind);
            click=0;
        }
    }

    //check if match is more than 3, if not it resets every match to 0
    int totalmatch=0;

    for(int i=1;i<=8;i++)
    for(int j=1;j<=8;j++){
        if(grid[i][j].match)
            totalmatch++;
    }

    if(totalmatch<3)
        for(int i=1;i<=8;i++)
        for(int j=1;j<=8;j++){
            grid[i][j].match=0;
            curscore = 0;
        }
    else{
        if(curscore == 0){
            score+=totalmatch;
            curscore++;
            std::cout<<score<<std::endl;
            for(int i=1;i<=8;i++) //to change the background water
            for(int j=1;j<=8;j++){
                if(grid[i][j].match)
                    if(bgice[i][j]==false){
                        bgice[i][j]=true;
                        std::cout<<"changed bgice to true"<<std::endl;
                        std::cout<<bgice[i][j]<<std::endl;
                    }
                    else //<---------------------
                        bg[i][j]=true; //<---------------------------------
            }
           turn--;
        text.setString(std::to_string(turn));
        }
    }

   //Moving animation
   isMoving=false;
   for (int i=1;i<=8;i++)
    for (int j=1;j<=8;j++)
     {
       piece &p = grid[i][j];
       int dx,dy;
       for(int n=0;n<6;n++)   // 4 - speed
       {dx = p.x-p.col*ts;
        dy = p.y-p.row*ts;
        if (dx) p.x-=dx/abs(dx);
	    if (dy) p.y-=dy/abs(dy);}
       if (dx||dy) isMoving=1;
     }

   //Deleting amimation
   if (!isMoving)
    for (int i=1;i<=8;i++)
    for (int j=1;j<=8;j++)
    if (grid[i][j].match) if (grid[i][j].alpha>10) {grid[i][j].alpha-=15; isMoving=true;}



   //Update grid
   if (!isMoving)
    {
      for(int i=8;i>0;i--)
       for(int j=1;j<=8;j++)
         if (grid[i][j].match)
         for(int n=i;n>0;n--)
            if (!grid[n][j].match) {swap(grid[n][j],grid[i][j]); break;};

      for(int j=1;j<=8;j++)
       for(int i=8,n=0;i>0;i--)
         if (grid[i][j].match)
           {
            grid[i][j].kind = rand()%gemTypes; //how many gems
            grid[i][j].y = -ts*n++;
            grid[i][j].match=0;
			grid[i][j].alpha = 255;
           }
     }


    //////draw///////
    App.draw(background);

    for(int i=1;i<=8;i++) //draw water background
    for(int j=1;j<=8;j++){
        if(bgice[i][j])
            if(bg[i][j]){
                cursor.setPosition(ts*j-8,ts*i-7); //draw water
                cursor.move(offset.x-ts,offset.y-ts);
                App.draw(cursor);
            }
            else{
                firstplaymat.setPosition(ts*j-8,ts*i-7);  //draw first play mat
                firstplaymat.move(offset.x-ts,offset.y-ts);
                App.draw(firstplaymat);
            }
        else{
            firstplaymat.setPosition(ts*j-8,ts*i-7);  //draw first play mat
            firstplaymat.move(offset.x-ts,offset.y-ts);
            App.draw(firstplaymat);

            ice.setPosition(ts*j-8,ts*i-7);
            ice.move(offset.x-ts,offset.y-ts);
            App.draw(ice);
        }

    }




	for (int i=1;i<=8;i++)
     for (int j=1;j<=8;j++)
      {
        piece p = grid[i][j];
        gems.setTextureRect( IntRect(p.kind*49,0,49,49));
        gems.setColor(Color(255,255,255,p.alpha));
        gems.setPosition(p.x,p.y);
        gems.move(offset.x-ts,offset.y-ts);
        App.draw(gems);
      }
    App.draw(leave);
    App.draw(power);

    App.draw(text);
    App.draw(turns);
    App.draw(powerupTurn);

    if(gamedone==64)
        App.draw(levelwin);

    if(turn<=0 && gamedone<64)
        App.draw(levelfail);


    fadeIn(App,transition,fadein);
     App.display();

    }

    return -1;
}
