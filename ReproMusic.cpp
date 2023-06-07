#include <iostream>
#include <vector>
#include <string>

// Patrón Iterator
class SongIterator {
public:
    virtual bool hasNext() const = 0;
    virtual std::string next() = 0;
};

// Implementación concreta del Iterator
class PlaylistIterator : public SongIterator {
private:
    std::vector<std::string> playlist;
    int currentIndex;
public:
    PlaylistIterator(const std::vector<std::string>& songs) : playlist(songs), currentIndex(0) {}

    bool hasNext() const override {
        return currentIndex < playlist.size();
    }

    std::string next() override {
        return playlist[currentIndex++];
    }
};

// Patrón Memento
class PlayerState {
private:
    std::string currentSong;
    int currentTime;
public:
    PlayerState(const std::string& song, int time) : currentSong(song), currentTime(time) {}

    std::string getCurrentSong() const {
        return currentSong;
    }

    int getCurrentTime() const {
        return currentTime;
    }
};

// Patrón Mediator
class MusicPlayerMediator {
private:
    std::vector<std::string> playlist;
    SongIterator* iterator;
    PlayerState* currentState;
public:
    MusicPlayerMediator(const std::vector<std::string>& songs) : playlist(songs), iterator(nullptr), currentState(nullptr) {}

    void play() {
        std::cout << "Reproduciendo la canción: " << currentState->getCurrentSong() << std::endl;
        std::cout << "Tiempo de reproducción: " << currentState->getCurrentTime() << " segundos" << std::endl;
    }

    void pause() {
        std::cout << "Pausando la canción: " << currentState->getCurrentSong() << std::endl;
        std::cout << "Tiempo de reproducción: " << currentState->getCurrentTime() << " segundos" << std::endl;
    }

    void stop() {
        std::cout << "Deteniendo la reproducción" << std::endl;
    }

    void setIterator(SongIterator* iter) {
        iterator = iter;
    }

    SongIterator* createIterator() {
        setIterator(new PlaylistIterator(playlist));
        return iterator;
    }

    PlayerState* saveState() {
        return new PlayerState(iterator->next(), 120); // Simulación de obtener el estado actual de reproducción
    }

    void restoreState(PlayerState* state) {
        currentState = state;
    }
};

int main() {
    std::vector<std::string> playlist = {"Canción 1", "Canción 2", "Canción 3"};

    MusicPlayerMediator player(playlist);

    std::cout << "Sistema de Reproducción de Música" << std::endl;

    // Crear Iterator y reproducir canciones
    SongIterator* iterator = player.createIterator();

    while (iterator->hasNext()) {
        PlayerState* currentState = player.saveState();
        player.restoreState(currentState);

        player.play();

        delete currentState;
    }

    // Liberar memoria
    delete iterator;

    return 0;
}
