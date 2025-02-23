#include <iostream>

// Subsystem Component 1: DVD Player
class DVDPlayer {
public:
    void turnOn() { std::cout << "DVD Player is ON.\n"; }
    void playMovie() { std::cout << "Playing movie on DVD Player.\n"; }
    void turnOff() { std::cout << "DVD Player is OFF.\n"; }
};

// Subsystem Component 2: Sound System
class SoundSystem {
public:
    void turnOn() { std::cout << "Sound System is ON.\n"; }
    void setVolume(int level) { std::cout << "Sound System Volume set to " << level << ".\n"; }
    void turnOff() { std::cout << "Sound System is OFF.\n"; }
};

// Subsystem Component 3: Projector
class Projector {
public:
    void turnOn() { std::cout << "Projector is ON.\n"; }
    void setInputSource(std::string source) { std::cout << "Projector input set to " << source << ".\n"; }
    void turnOff() { std::cout << "Projector is OFF.\n"; }
};

// Facade: Home Theater System
class HomeTheaterFacade {
    DVDPlayer dvdPlayer;
    SoundSystem soundSystem;
    Projector projector;

public:
    void watchMovie() {
        std::cout << "\nSetting up Home Theater...\n";
        dvdPlayer.turnOn();
        soundSystem.turnOn();
        soundSystem.setVolume(10);
        projector.turnOn();
        projector.setInputSource("DVD Player");
        dvdPlayer.playMovie();
        std::cout << "Enjoy your movie!\n";
    }

    void endMovie() {
        std::cout << "\nShutting down Home Theater...\n";
        dvdPlayer.turnOff();
        soundSystem.turnOff();
        projector.turnOff();
    }
};

int main() {
    HomeTheaterFacade homeTheater;
    
    homeTheater.watchMovie(); // Start movie with one function call
    homeTheater.endMovie();   // Stop movie with one function call

    return 0;
}
