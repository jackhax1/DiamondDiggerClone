//screen base class

#include <SFML/Graphics.hpp>
#include "screens.hpp"

class cScreen
{
public :
    virtual int Run (sf::RenderWindow &App)=0;
};
