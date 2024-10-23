//
//  main.cpp
//  musicstore
//
//  Created by Francesco Caglianone on 30/11/22.
//

#include <iostream>
#include <dirent.h>
#include <cassert>
#include <cstring>
#include <cstdio>
#include <vector>
#include <map>
#include <ctype.h>
#include <string>

#include "musicstore.h"


using namespace std;



/* STRUCTURE */
struct song {
    string artist;
    string album;
    unsigned songID;
    string title;
};

struct musicstore {
    vector<song> Songs;
};





/* CONSTRUCTOR & DESTRUCTOR */
struct musicstore * ms_create (){
    struct musicstore * s = new musicstore;
    assert(s);
    return s;
}

void ms_destroy (struct musicstore * s){
    delete s;
}



/* HELPER FUNCTIONS */
// Check if the extension is correct
int check_extension(const char * fileName){
    string tmp(fileName);
    if( tmp.find(".flac") != string::npos || tmp.find(".mp3") != string::npos || tmp.find(".mpc") != string::npos || tmp.find(".ogg") != string::npos || tmp.find(".wma") != string::npos){
        return 1;
    } else {
        return 0;
    }
}


// comparison for the sort function
bool song_compare (const song & a, const song & b) {
    if (a.artist < b.artist)
        return true;
    if (a.artist == b.artist && a.album < b.album)
        return true;
    if (a.album == b.album && a.songID < b.songID)
        return true;
    return false;
}


// Get the author, album, song_number, title and push it to struct
void push_to_struct(struct musicstore * s, const char * fileName){
    
    // Get all
    string author;
    string album;
    string song_number;
    string title;
    size_t index = 0;
    string str(fileName);
    
    for (int i=0; i<4; i++) {
        index = str.find(" - ");
        if (i == 0) {
            author = str.substr(0, index);
        } else if(i == 1){
            album = str.substr(0, index);
        } else if(i == 2){
            song_number = str.substr(0, index);
        } else {
            title = str.substr(0, index);
        }
        if(i != 3){
            str.erase(0, index+3);
        }
    }
    
    // Push to struct
    struct song * newSong = new song;
    newSong->artist = author;
    newSong->album = album;
    newSong->songID = stoi(song_number);
    newSong->title = title;
    
    s->Songs.push_back(*newSong);
    
    delete newSong;
}



/* READ FROM DIR */
int ms_read_from_directory (struct musicstore * s, const char * dirname){
    DIR * directory = opendir(dirname);
    if(!directory){
        printf("Error 404\n");
        return 0;
    }
    
    struct dirent * entity;
    entity = readdir(directory);
    while (entity) {
        const char * fileName = entity->d_name;
//        cout << fileName << endl;
        if (check_extension(fileName)){
//            cout << "This file is ok" << endl;
            push_to_struct(s, fileName);
            //cout << fileName << '\n';
        }
        if (entity->d_type == DT_DIR && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, "..") != 0) {   // DT_DIR == 4
            string newPath = "";
            newPath.append(dirname);
            newPath.append("/");
            newPath.append(entity->d_name);
            // cout << newPath << endl;
            // Transform from string to char *
            const char * str = newPath.c_str();
            // Recursion
            ms_read_from_directory(s, str);
        }
        entity = readdir(directory);
    }
    sort(s->Songs.begin(), s->Songs.end(), song_compare);
    
    // Close connection
    closedir(directory);
    
    return 1;
}


/* CALLBACKS */
typedef void (*song_callback)(const char * artist, const char * album, unsigned sequence, const char * title);
typedef void (*album_callback)(const char * artist, const char * album, unsigned songs_count);
typedef void (*artist_callback)(const char * artist, unsigned albums_count, unsigned songs_count);





/* GETTER METHODS */

/*
 *  Get the artists from the music store
 */
void ms_get_artist (const struct musicstore * s, const char * artist, artist_callback cb) {
    string tmp = "";
    unsigned checker = 0;
    for (int i = 0; i < s->Songs.size();) {
        unsigned song_count = 1;
        unsigned album_count = 0;
        if ((artist == nullptr || s->Songs[i].artist == artist)) {
            while (song_count + i < s->Songs.size() && s->Songs[i+song_count].artist == s->Songs[i].artist) {
                ++song_count;
                if(tmp != s->Songs[song_count + i].album){
                    ++album_count;
                    tmp = s->Songs[song_count + i].album;
                }
            }
            if (!checker) {
                checker = album_count - 1;
                cb(s->Songs[i].artist.c_str(), checker, song_count);
            } else {
                cb(s->Songs[i].artist.c_str(), album_count, song_count);
            }
        }
        i += song_count;
    }
}



/*
 *  Get the artists from the music store
 */
void ms_get_albums (const struct musicstore * s, const char * artist, const char * album, album_callback cb){
    for (int i = 0; i < s->Songs.size();) {
        unsigned count = 1;
        if ((artist == nullptr || s->Songs[i].artist == artist) &&
            (album == nullptr || s->Songs[i].album == album)) {
            while (count + i < s->Songs.size() && s->Songs[i+count].album == s->Songs[i].album)
                ++count;
            cb(s->Songs[i].artist.c_str(), s->Songs[i].album.c_str(), count);
        }
        i += count;
    }
}
        



/*
 *  Get the songs from the music store
 */
void ms_get_songs (const struct musicstore * s, const char * artist, const char * album, const char * title, song_callback cb){
    for (int i = 0; i < s->Songs.size(); i++) {
        if ((title == nullptr || s->Songs[i].title == title) && (artist == nullptr || s->Songs[i].artist == artist) && (album == nullptr || s->Songs[i].album == album)) {
            cb(s->Songs[i].artist.c_str(), s->Songs[i].album.c_str(), s->Songs[i].songID, s->Songs[i].title.c_str());
        }
    }
}
    




// MAIN
//int main(int argc, const char * argv[]) {
//    struct musicstore * s = ms_create();
//    ms_read_from_directory(s, "tests/pino_daniele");
//    ms_read_from_directory(s, "tests/vasco_rossi");
//    for (int i = 0; i < s->Songs.size(); i++) {
//        cout << s->Songs[i].artist << endl;
//        cout << s->Songs[i].album << endl;
//        cout << s->Songs[i].songID << endl;
//        cout << s->Songs[i].title << endl;
//    }
//    ms_destroy(s);
//}
