//level select

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "screens.hpp"
#include <iostream>

extern int play;
extern std::string levelcomplete[3];
extern int levelcomp[3];
int level;


class screen3:public cScreen
{
public :
    virtual int Run (sf::RenderWindow &App);
};

int screen3::Run(sf::RenderWindow &App){
    sf::SoundBuffer buffer;
    sf::Sound sound;
    buffer.loadFromFile("resource/zap.wav");
    sound.setBuffer(buffer);
    sound.play();

    sf::Texture t[15],t0,twin[15];

    //load button file
    t[0].loadFromFile("resource/images/levelbutton/1.png");
    t[1].loadFromFile("resource/images/levelbutton/2.png");
    t[2].loadFromFile("resource/images/levelbutton/3.png");
    t[3].loadFromFile("resource/images/levelbutton/4.png");
    t[4].loadFromFile("resource/images/levelbutton/5.png");
    t[5].loadFromFile("resource/images/levelbutton/6.png");
    t[6].loadFromFile("resource/images/levelbutton/7.png");
    t[7].loadFromFile("resource/images/levelbutton/8.png");
    t[8].loadFromFile("resource/images/levelbutton/9.png");
    t[9].loadFromFile("resource/images/levelbutton/10.png");
    t[10].loadFromFile("resource/images/levelbutton/11.png");
    t[11].loadFromFile("resource/images/levelbutton/12.png");
    t[12].loadFromFile("resource/images/levelbutton/13.png");
    t[13].loadFromFile("resource/images/levelbutton/14.png");
    t[14].loadFromFile("resource/images/levelbutton/15.png");



    twin[0].loadFromFile("resource/images/levelbutton/win/1.png");
    twin[1].loadFromFile("resource/images/levelbutton/win/2.png");
    twin[2].loadFromFile("resource/images/levelbutton/win/3.png");
    twin[3].loadFromFile("resource/images/levelbutton/win/4.png");
    twin[4].loadFromFile("resource/images/levelbutton/win/5.png");
    twin[5].loadFromFile("resource/images/levelbutton/win/6.png");
    twin[6].loadFromFile("resource/images/levelbutton/win/7.png");
    twin[7].loadFromFile("resource/images/levelbutton/win/8.png");
    twin[8].loadFromFile("resource/images/levelbutton/win/9.png");
    twin[9].loadFromFile("resource/images/levelbutton/win/10.png");
    twin[10].loadFromFile("resource/images/levelbutton/win/11.png");
    twin[11].loadFromFile("resource/images/levelbutton/win/12.png");
    twin[12].loadFromFile("resource/images/levelbutton/win/13.png");
    twin[13].loadFromFile("resource/images/levelbutton/win/14.png");
    twin[14].loadFromFile("resource/images/levelbutton/win/15.png");

    bool expand[15]={false};
    bool expandwin[15]={false};
    t0.loadFromFile("resource/images/levelselectbg.png");

    sf::Sprite button[15],background(t0),buttonwin[15];

    int j=-1;

    for(int i=0;i<15;i++){
        button[i]=sf::Sprite(t[i]);
        if(i%5==0)
            j++;
        button[i].setPosition(100+i*100-j*95*5,200+j*100);
        button[i].setOrigin(button[i].getGlobalBounds().width/2,button[i].getGlobalBounds().height/2);

    }
    j=-1;
    for(int i=0;i<15;i++){ //5
        //buttonwin[i]=sf::Sprite(twin[i]);
        //buttonwin[i].setPosition(100+i*100,200);
        //buttonwin[i].setOrigin(buttonwin[i].getGlobalBounds().width/2,buttonwin[i].getGlobalBounds().height/2);
        buttonwin[i]=sf::Sprite(twin[i]);
        if(i%5==0)
            j++;
        buttonwin[i].setPosition(100+i*100-j*95*5,200+j*100);
        buttonwin[i].setOrigin(buttonwin[i].getGlobalBounds().width/2,buttonwin[i].getGlobalBounds().height/2);


    }

    int fadein=255;
    sf::Texture t1,t10;
    t1.loadFromFile("resource/images/leave.png");
    t10.loadFromFile("resource/images/transition.png");

    sf::Sprite leave(t1),transition(t10);
    bool leaveb = false;


    leave.setOrigin(leave.getGlobalBounds().width/2,leave.getGlobalBounds().height/2);
    leave.setPosition(550,100);

    sf::Event e;



    while(App.isOpen()){
        while(App.pollEvent(e)){
            if(e.type==sf::Event::Closed)
                return -1;
            if(e.type==sf::Event::MouseButtonPressed){
                for(int i=0;i<=levelcomp[play];i++)
                    if(mouseOverObj(App,button[i])){
                        level=i;
                        return 1;
                    }

                if(mouseOverObj(App,leave))
                        return 0;
            }
        }
        App.clear();
        App.draw(background);

        for(int i=0;i<15;i++){
            if(i<=levelcomp[play]){
                animateButton(App,button[i],expand[i]);
            }
            if(i<=levelcomp[play]-1){
                App.draw(buttonwin[i]);
                animateButton(App,buttonwin[i],expandwin[i]);

            }
            else
                App.draw(button[i]);
        }

        animateButton(App,leave,leaveb);

        App.draw(leave);

        fadeIn(App,transition,fadein);
        App.display();




    }

    App.clear();
    return -1;

}


