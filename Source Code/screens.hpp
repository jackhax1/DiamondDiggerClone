#ifndef SCREENS_HPP_INCLUDED
#define SCREENS_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include<iostream>
#include<ctime>
#include<cstdlib>





bool mouseOverObj(sf::RenderWindow& App,  sf::Sprite& obj){
    float mouseX = sf::Mouse::getPosition().x ;
    float mouseY = sf::Mouse::getPosition().y ;
    float objX = obj.getPosition().x - obj.getGlobalBounds().width/2.0;
    float objY = obj.getPosition().y - obj.getGlobalBounds().height/2.0;
    sf::Vector2i windowPosition = App.getPosition();
    if(mouseX > objX + windowPosition.x && mouseX < ( objX + obj.getGlobalBounds().width + windowPosition.x+10)
    && mouseY > objY + windowPosition.y + 30  && mouseY < ( objY + obj.getGlobalBounds().height + windowPosition.y + 30) )
        return true;
    else
        return false;
}


void animateButton(sf::RenderWindow& App, sf::Sprite& obj,bool& expanded){
    if(mouseOverObj(App,obj))
        if(!expanded){
            obj.setScale(0.95f,0.95f);
            obj.setColor(sf::Color(255,255,255,220));
            expanded = true;
        }
    if(!mouseOverObj(App,obj)&&expanded){
        obj.setScale(1.0f,1.0f);
        obj.setColor(sf::Color(255,255,255,255));
        expanded=false;
    }
}

void fadeIn(sf::RenderWindow& App,sf::Sprite& transition,int& fadeIn){
    if(fadeIn>5){
        transition.setColor(sf::Color(255,255,255,fadeIn));
        fadeIn-=15;
    }
    App.draw(transition);
}

void randIce(bool bgice[10][10],double percent){
    srand(time(0));
    bool isIce;
    int randNum;
    for(int i=0;i<10;i++)
    for(int j=0;j<10;j++){
        randNum=rand()%1000+1;
        if(randNum<=percent*10)
            bgice[i][j]=false;
        else
            bgice[i][j]=true;
    }
}



//main screen class
#include "cScreen.hpp"

//main menu
#include "screen0.hpp"

//credit screen
#include "screen4.hpp"

//player select

#include "screen2.hpp"

//level select
#include "screen3.hpp"


//game screen
#include "screen1.hpp"








#endif // SCREENS_HPP_INCLUDED
