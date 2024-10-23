#include <iostream>
#include <ostream>
#include <cassert>
#include <string>
#include <vector>

#include "musicstore.h"

bool found_flag = false;  // Global flag to track if a query result was found

void song_print(const char *artist, const char *album, unsigned sequence, const char *title) {
    found_flag = true;
    std::cout << "Artist: " << artist << ", Album: " << album
              << " Track (" << sequence << "): " << title << std::endl;
}

void album_print(const char *artist, const char *album, unsigned songs_count) {
    found_flag = true;
    std::cout << "Artist: " << artist << ", Album: " << album
              << ", Songs: " << songs_count << std::endl;
}

void artist_print(const char *artist, unsigned albums_count, unsigned songs_count) {
    found_flag = true;
    std::cout << "Artist: " << artist << ", Albums: " << albums_count
              << ", Songs: " << songs_count << std::endl;
}

void reset_found_flag() {
    found_flag = false;
}

int main(int argc, char *argv[]) {
    bool prompt;
    if (argc > 1 && std::string(argv[1]) == "-i")
        prompt = true;
    else
        prompt = false;

    std::vector<struct musicstore *> M;
    unsigned i = 0;
    M.push_back(ms_create());
    if (!M[0]) {
        std::cerr << "Error: Failed to create the initial music store." << std::endl;
        return 1;
    }

    std::string artist, album, title, command;

    for (std::cout << (prompt ? "> " : "") << std::flush;
         std::getline(std::cin, command);
         std::cout << (prompt ? "> " : "") << std::flush) {

        if (command.substr(0, 1) == "?") {
            std::cout << "M: " << i << std::endl
                      << "artist: " << artist << std::endl
                      << "album: " << album << std::endl
                      << "title: " << title << std::endl;

        } else if (command.substr(0, 1) == "+") {
            i = M.size();
            M.push_back(ms_create());
            if (!M[i]) {
                std::cerr << "Error: Failed to create a new music store." << std::endl;
            } else {
                std::cout << "Created music store index: " << i << std::endl;
            }

        } else if (command.substr(0, 1) == "-") {
            unsigned j;
            try {
                j = std::stoul(command.substr(1, std::string::npos));
                if (j >= M.size() || !M[j]) {
                    std::cerr << "Error: Invalid index or music store already destroyed." << std::endl;
                } else {
                    ms_destroy(M[j]);
                    M[j] = nullptr;
                    std::cout << "Destroyed music store index: " << j << std::endl;
                }
            } catch (const std::exception &e) {
                std::cerr << "Error: Invalid index for destruction." << std::endl;
            }

        } else if (command.substr(0, 1) == "=") {
            try {
                unsigned newIndex = std::stoul(command.substr(1, std::string::npos));
                if (newIndex >= M.size() || !M[newIndex]) {
                    std::cerr << "Error: Invalid music store index." << std::endl;
                } else {
                    i = newIndex;
                    std::cout << "Switched to music store index: " << i << std::endl;
                }
            } catch (const std::exception &e) {
                std::cerr << "Error: Invalid index format." << std::endl;
            }

        } else if (command.substr(0, 1) == ">") {
            std::cout << command.substr(1, std::string::npos) << std::endl;

        } else if (command.substr(0, 8) == "artist: ") {
            artist = command.substr(8, std::string::npos);

        } else if (command.substr(0, 7) == "album: ") {
            album = command.substr(7, std::string::npos);

        } else if (command.substr(0, 7) == "title: ") {
            title = command.substr(7, std::string::npos);

        } else if (command.substr(0, 5) == "read ") {
            std::string dir = command.substr(5, std::string::npos);
            if (!ms_read_from_directory(M[i], dir.c_str())) {
                std::cerr << "Error: Failed to read directory '" << dir << "'" << std::endl;
            } else {
                std::cout << "Successfully read directory: " << dir << std::endl;
            }

        } else if (command == "get_songs") {
            if (M[i]) {
                reset_found_flag();
                ms_get_songs(M[i],
                             (artist.length() > 0 ? artist.c_str() : nullptr),
                             (album.length() > 0 ? album.c_str() : nullptr),
                             (title.length() > 0 ? title.c_str() : nullptr),
                             song_print);
                if (!found_flag) {
                    std::cout << "Error: No songs found with the specified criteria." << std::endl;
                }
            } else {
                std::cerr << "Error: No active music store to get songs from." << std::endl;
            }

        } else if (command == "get_artist") {
            if (M[i]) {
                reset_found_flag();
                ms_get_artist(M[i], (artist.length() > 0 ? artist.c_str() : nullptr), artist_print);
                if (!found_flag) {
                    std::cout << "Error: No artists found with the specified criteria." << std::endl;
                }
            } else {
                std::cerr << "Error: No active music store to get artists from." << std::endl;
            }

        } else if (command == "get_albums") {
            if (M[i]) {
                reset_found_flag();
                ms_get_albums(M[i], (artist.length() > 0 ? artist.c_str() : nullptr),
                              (album.length() > 0 ? album.c_str() : nullptr),
                              album_print);
                if (!found_flag) {
                    std::cout << "Error: No albums found with the specified criteria." << std::endl;
                }
            } else {
                std::cerr << "Error: No active music store to get albums from." << std::endl;
            }

        } else {
            std::cerr << "Error: Unknown command: '" << command << "'" << std::endl;
        }
    }

    for (struct musicstore *m : M)
        if (m)
            ms_destroy(m);

    return 0;
}
