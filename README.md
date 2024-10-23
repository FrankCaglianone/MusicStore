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

1. **Start the executable**:
   ```bash
   ./ms
   ```

2. **Read the provided music files**:
   ```bash
   read tests
   ```

3. **Start Querying**:
   - `?`: Prints the current musicstore index and set query parameters (artist, album, title).
   - `+`: Creates a new musicstore object and switches to it.
   - `-<index>`: Destroys the musicstore object at the specified index.
   - `=<index>`: Switches to the musicstore object at the specified index.
   - `artist`: <name>: Sets the artist filter to the specified name.
   - `album`: <name>: Sets the album filter to the specified name.
   - `title`: <name>: Sets the title filter to the specified name.
   - `read <directory>`: Reads the specified directory and stores the music data in the current musicstore.
   - `get_songs`: Prints all songs matching the current artist, album, and title filters.
   - `get_artist`: Prints all artists matching the current artist filter.
   - `get_albums`: Prints all albums matching the current artist and album filters.
   - `>`: Prints a message to the console.


## License 📄
This project is licensed under the [MIT License](LICENSE).

## Credits 💳
This project is inspired by the Systems Programming course at **Università della Svizzera italiana (USI)**. Special thanks to **A. Carzaniga** for the project guidelines and support.

