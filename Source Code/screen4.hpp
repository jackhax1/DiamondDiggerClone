//credit screen

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "screens.hpp"

class screen4: public cScreen
{
public :
    virtual int Run (sf::RenderWindow &App);
};


int screen4::Run(sf::RenderWindow &App){
    sf::SoundBuffer buffer;
    sf::Sound sound;
    buffer.loadFromFile("resource/zap.wav");
    sound.setBuffer(buffer);
    sound.play();

    sf::Music music;
    music.openFromFile("resource/music.wav");
    music.play();


    int fadein=255;
    sf::Texture t0,t10;
    t0.loadFromFile("resource/images/credit.png");
    t10.loadFromFile("resource/images/transition.png");

    sf::Sprite background(t0),transition(t10);

    sf::Event e;

    while(App.isOpen()){
        while(App.pollEvent(e)){
            if(e.type==sf::Event::Closed)
                return -1;
            if(e.type==sf::Event::MouseButtonPressed){
                return 0;
            }
        }


        App.clear();
        App.draw(background);
        fadeIn(App,transition,fadein);
        App.display();
    }
    App.clear();
    return -1;

}
