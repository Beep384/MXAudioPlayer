#include <iostream>
#include <SFML/Audio.hpp>
#include <string>
#include <algorithm>
#include <thread>

std::string cleanPath(std::string path)
{
    // We trim the whitespaces
    path.erase(0, path.find_first_not_of(" \t\n\r"));
    path.erase(path.find_last_not_of(" \t\n\r") + 1);

    // We remove the surrounding quotes
    if ((path.front() == '"' && path.back() == '"') || (path.front() == '\'' && path.back() == '\''))
    {
        path = path.substr(1, path.size() - 2);
    }

    return path;
}
int main() {

    std::string path;
    std::cout << "Drag and drop a wav file ";
    std::getline(std::cin, path); 

    path = cleanPath(path);

    sf::Music music;
    if (!music.openFromFile(path))
    { 
        std::cerr << "Failed to load audio file " << path << ". Why? Because fuck you." << std::endl;
        return 1;
    }

    bool looping = false;

    std::thread inputThread([&]()
    {
        char c;
        while (std::cin.get(c))
        {
            if (c == 'l' || c == 'L')
            {
                if (!looping)
                {
                    looping = true;
                    music.setLoop(looping);
                    std::cout << "We are looping the song." << std::endl;
                } else
                {
                    looping = false;
                    music.setLoop(looping);
                    std::cout << "We are not looping the song." << std::endl;
                }
            } else if (c == 'q' || c == 'Q')
            {
                std::cout << "Closing the program..." << std::endl;
                sf::sleep(sf::seconds(1));
                std::exit(0);
            }
        }
    });

    std::cout << "Playing: " << path << std::endl;
    std::cout << "Press L to loop the audio file." << std::endl;
    std::cout << "Press Q to quit the program." << std::endl;
    std::cout << "Pausing is currently a work in progress behind the scenes. Remember, this is a prototype build." << std::endl;
    std::cout << "Also note this: .WAV FILES ARE THE ONLY ONES THAT ARE TESTED AND SUPPORTED RIGHT NOW. THIS IS A PROTOTYPE BUILD." << std::endl;
    music.play();


    while (music.getStatus() == sf::Music::Playing) 
    {
        sf::sleep(sf::milliseconds(100));
    }

    return 0;
}