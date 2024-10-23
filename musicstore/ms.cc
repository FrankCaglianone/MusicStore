#include <iostream>
#include <ostream>
#include <cassert>
#include <string>
#include <vector>

#include "musicstore.h"

void song_print (const char * artist, const char * album, unsigned sequence, const char * title) {
    std::cout << "Artist: " << artist << ", Album: " << album
	      << "Track (" << sequence << "): " << title << std::endl;
}

void album_print (const char * artist, const char * album, unsigned songs_count) {
    std::cout << "Artist: " << artist << ", Album: " << album
	      <<  ", Songs: " << songs_count << std::endl;
}

void artist_print (const char * artist, unsigned albums_count, unsigned songs_count) {
    std::cout << "Artist: " << artist << ", Albums: " << albums_count
	      <<  ", Songs: " << songs_count << std::endl;
}

int main (int argc, char * argv[]) {
    bool prompt;
    if (argc > 1 && std::string(argv[1]) == "-i")
	prompt = true;
    else
	prompt = false;
    std::vector <struct musicstore *> M;
    unsigned i = 0;
    M.push_back (ms_create ()); 
    assert (M[0]);

    std::string artist, album, title, command;

    for (std::cout << (prompt ? "> " : "") << std::flush;
	 std::getline (std::cin , command);
	 std::cout << (prompt ? "> " : "") << std::flush) {
	if (command.substr(0,1) == "?") {
	    std::cout << "M: " << i << std::endl
		      << "artist: " << artist << std::endl
		      << "album: " << album << std::endl
		      << "title: " << title << std::endl;
	} else if (command.substr(0,1) == "+") {
	    i = M.size();
	    M.push_back (ms_create());
	    assert (M[i]);
	    std::cout << i << std::endl;
	} else if (command.substr(0,1) == "-") {
	    unsigned j = stoul(command.substr(1, std::string::npos));
	    ms_destroy (M[j]);
	    M[j] = nullptr;
	} else if (command.substr(0,1) == "=") {
	    i = stoul(command.substr(1, std::string::npos));
	} else if (command.substr(0,1) == ">") {
	    std::cout << command.substr(1, std::string::npos) << std::endl;
	} else if (command.substr(0,8) == "artist: ") {
	    artist = command.substr(8, std::string::npos);
	} else if (command.substr(0,7) == "album: ") {
	    album = command.substr(7, std::string::npos);
	} else if (command.substr(0,7) == "title: ") {
	    title = command.substr(7, std::string::npos);
	} else if (command.substr(0,5) == "read ") {
	    std::string dir = command.substr(5, std::string::npos);
	    if (! ms_read_from_directory (M[i], dir.c_str()))
		std::cout << "errors in reading directory '" << dir << "'" << std::endl;
	} else if (command == "get_songs") {
	    ms_get_songs (M[i],
			  (artist.length() > 0 ? artist.c_str() : nullptr),
			  (album.length() > 0 ? album.c_str() : nullptr),
			  (title.length() > 0 ? title.c_str() : nullptr),
			  song_print);
	} else if (command == "get_artist") {
	    ms_get_artist (M[i], (artist.length() > 0 ? artist.c_str() : nullptr), artist_print);
	} else if (command == "get_albums") {
	    ms_get_albums (M[i], (artist.length() > 0 ? artist.c_str() : nullptr),
			   (album.length() > 0 ? album.c_str() : nullptr),
			   album_print);
	} else { 
	    std::cout << "unknown command: '" << command << "'" << std::endl;
	}
    }
    for (struct musicstore * m : M)
	if (m)
	    ms_destroy (m);
}
