#define _WIN32_WINNT 0x0501 //to hide console

#include <iostream>
#include "screens.hpp"
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <fstream>

std::string levelcomplete[3];





int main()
{   ShowWindow(GetConsoleWindow(),SW_HIDE); //to hide console
    std::vector<cScreen*> Screens;
    sf::RenderWindow window(sf::VideoMode(640,640,32),"Diamond Digger",sf::Style::Close);
    window.setFramerateLimit(60);



    int screen=0;

    screen0 s0; //main menu 0
    screen1 s1; //game  1
    screen2 s2; //player select 2
    screen3 s3; //level select 3
    screen4 s4; //credit screen 4

    //return -1 to exit

    Screens.push_back(&s0);
    Screens.push_back(&s1);
    Screens.push_back(&s2);
    Screens.push_back(&s3);
    Screens.push_back(&s4);

    while(screen>=0){
        screen = Screens[screen]->Run(window);
    }

    window.close();

    return 0;
}
