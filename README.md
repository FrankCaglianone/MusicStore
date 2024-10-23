# MusicStore 🎵
A dynamic music store application for efficiently organizing and retrieving music collections based on artists, albums, and songs.

## Project Purpose 🎯
The purpose of **MusicStore** is to provide a structured and efficient solution for managing and querying music collections. It reads and categorizes music files based on artist, album, and track details, enabling streamlined access to your favorite music. The project is designed to support large collections and ensure efficient querying, making it suitable for music enthusiasts and digital archivists.

## Important Features ✨
- **Music Organization**: Automatically categorizes music files based on the artist, album, and track information extracted from file names.
- **Efficient Query System**: Retrieve specific artists, albums, or songs with callback-based query functions.
- **Support for Multiple Formats**: Recognizes and processes popular audio file formats, including `.mp3`, `.flac`, `.ogg`, `.wma`, and `.mpc`.
- **Scalable Structure**: Efficient handling of large collections with sublinear query complexity.
- **Extensible Callbacks**: Flexibility to define custom callback functions to handle query results.

## Requirements 📋
To get **MusicStore** up and running locally, follow these steps:

1. **Prerequisites**:
   - C or C++ compiler (GCC, Clang, or MSVC)
   - Standard C/C++ libraries

2. **Installation**:
   ```bash
   git clone https://github.com/FrankCaglianone/MusicStore.git
   cd MusicStore/musicstore
   ```

3. **Build the Project**:
   ```bash
   # To create the executable 
   make
   ```

## Usage 🛠️
**MusicStore** provides several functions to work with your music collection:

1. **Create and Destroy a Music Store**:
   ```c
   struct musicstore *store = ms_create();
   ms_destroy(store);
   ```

2. **Read Music Files from a Directory**:
   ```c
   ms_read_from_directory(store, "./path/to/music/folder");
   ```

3. **Query Artists**:
   ```c
   void print_artist(const char *artist, unsigned albums_count, unsigned songs_count) {
       printf("Artist: %s, Albums: %u, Songs: %u\n", artist, albums_count, songs_count);
   }
   ms_get_artist(store, NULL, print_artist); // Retrieve all artists
   ```

4. **Query Albums and Songs**:
   Similar to artist queries, you can define callback functions for albums and songs using `ms_get_albums` and `ms_get_songs`.

## License 📄
This project is licensed under the [MIT License](LICENSE).

## Credits 💳
This project is inspired by the Systems Programming course at **Università della Svizzera italiana (USI)**. Special thanks to **A. Carzaniga** for the project guidelines and support.

