#include "Game.h"
#include "Utils/Exception.h"

#include <iostream>

int main(int argc, char* argv[]) {
    
    try {
        Game::get().setArguments(argc, argv);
        Game::get().start();

    } catch(const Util::Exception::FatalError& exception) {
        std::cerr << "Fatal error occured:" << std::endl;
        std::cerr << exception.what() << std::endl;
        system("pause");
        
    }  catch(const std::exception& exception) {
        std::cerr << "Exception thrown:" << std::endl;
        std::cerr << exception.what() << std::endl;
        system("pause");

    } catch(...) {
        std::cerr << "Unidentified exception unhandled" << std::endl;
        system("pause");
    }

    return 0;
}