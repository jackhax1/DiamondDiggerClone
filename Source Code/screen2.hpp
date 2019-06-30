//player select


#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "screens.hpp"
#include <fstream>

extern std::string levelcomplete[3];
extern int play=0;
int levelcomp[3];

class screen2 : public cScreen{
public:
    virtual int Run (sf::RenderWindow &App);
};

void getPlayerInfo(int num){
    std::string temp;
    std::ifstream data;
    play = num;
    data.open("resource/data1.txt");
    for(int i=0;i<3;i++){
        getline(data,levelcomplete[i]);
        std::cout<<levelcomplete[i]<<std::endl;
    }
    data.close();
    for(int i=0;i<3;i++)
        levelcomp[i]= stoi(levelcomplete[i]);
}

int screen2::Run(sf::RenderWindow &App){

    sf::SoundBuffer buffer;
    sf::Sound sound;
    buffer.loadFromFile("resource/zap.wav");
    sound.setBuffer(buffer);
    sound.play();

    sf::Texture t1,t2,t3,t4,t5;
    t1.loadFromFile("resource/images/playerselectbg.png");
    t2.loadFromFile("resource/images/player1.png");
    t3.loadFromFile("resource/images/player2.png");
    t4.loadFromFile("resource/images/player3.png");
    t5.loadFromFile("resource/images/leave.png");

    sf::Sprite background(t1),player1(t2),player2(t3),player3(t4),leave(t5);
    bool playerb[3]={false};
    bool leaveb = false;

    player1.setOrigin(player1.getGlobalBounds().width/2,player1.getGlobalBounds().height/2);
    player2.setOrigin(player2.getGlobalBounds().width/2,player2.getGlobalBounds().height/2);
    player3.setOrigin(player3.getGlobalBounds().width/2,player3.getGlobalBounds().height/2);

    player1.setPosition(420,250);
    player2.setPosition(420,380);
    player3.setPosition(420,510);

    leave.setOrigin(leave.getGlobalBounds().width/2,leave.getGlobalBounds().height/2);
    leave.setPosition(550,100);

    int fadein=255;
    sf::Texture t10;
    t10.loadFromFile("resource/images/transition.png");

    sf::Sprite transition(t10);

    sf::Event e;



    while(App.isOpen()){
        while(App.pollEvent(e)){
            if(e.type==sf::Event::Closed)
                return -1;
            if(e.type==sf::Event::MouseButtonPressed){
                if(mouseOverObj(App,player1)){
                    getPlayerInfo(0);
                    return 3;
                }
                if(mouseOverObj(App,player2)){
                    getPlayerInfo(1);
                    return 3;
                }
                if(mouseOverObj(App,player3)){
                    getPlayerInfo(2);
                    return 3;
                }

                if(mouseOverObj(App,leave)){
                    return 0;
                }
            }
        }
        animateButton(App,player1,playerb[0]);
        animateButton(App,player2,playerb[1]);
        animateButton(App,player3,playerb[2]);
        animateButton(App,leave,leaveb);

        App.clear();
        App.draw(background);
        App.draw(player1);
        App.draw(player2);
        App.draw(player3);
        App.draw(leave);

        fadeIn(App,transition,fadein);
        App.display();
    }
    App.clear();
    return -1;








}


