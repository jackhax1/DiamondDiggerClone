//Main menu screen


#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "screens.hpp"

class screen0:public cScreen{
public:
    virtual int Run (sf::RenderWindow &App);
};



//void fadeIn(sf::RenderWindow& App,sf::Sprite& transition,int& fadeIn);


int screen0::Run(sf::RenderWindow &App){
    std::vector <bool> element;
    sf::Texture t1,t2,t3,t4;
    t1.loadFromFile("resource/images/start.png");
    t2.loadFromFile("resource/images/menubg.png");
    t3.loadFromFile("resource/images/exit.png");
    t4.loadFromFile("resource/images/creditbutton.png");

    sf::Sprite start(t1);
    sf::Sprite background(t2);
    sf::Sprite exit(t3);
    sf::Sprite credit(t4);

    start.setOrigin(start.getGlobalBounds().width/2,start.getGlobalBounds().height/2);
    start.setPosition(320,300);

    exit.setOrigin(exit.getGlobalBounds().width/2,exit.getGlobalBounds().height/2);
    exit.setPosition(320,440);

    credit.setOrigin(credit.getGlobalBounds().width/2,credit.getGlobalBounds().height/2);
    credit.setPosition(320,370);


    sf::Texture t10;
    t10.loadFromFile("resource/images/transition.png");

    sf::Sprite transition(t10);



    sf::Event e;

    bool startb=false,exitb=false, creditb=false;

    bool fadein=true;
    int xfade=255;

    sf::SoundBuffer buffer;
    sf::Sound sound;
    buffer.loadFromFile("resource/zap.wav");

    sound.setBuffer(buffer);


    sf::Music music;
    music.openFromFile("resource/music.wav");
    music.play();

    while(App.isOpen()){



        while(App.pollEvent(e)){
            if(e.type==sf::Event::Closed)
                return -1;
            if(e.type==sf::Event::MouseButtonPressed){

                if(mouseOverObj(App,start)){
                    sound.play();
                    return 2;
                }

                if(mouseOverObj(App,exit))
                    return -1;

                if(mouseOverObj(App,credit))
                    return 4;
            }
        }
        animateButton(App,start,startb);
        animateButton(App,exit,exitb);
        animateButton(App,credit,creditb);

        App.clear();
        App.draw(background);
        App.draw(start);
        App.draw(exit);
        App.draw(credit);


        fadeIn(App,transition,xfade);

        App.display();
    }
    App.clear();
    return -1;
}


