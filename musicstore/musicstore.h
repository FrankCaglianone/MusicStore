#ifndef MUSICSTORE_H
#define MUSICSTORE_H

#ifdef __cplusplus
extern "C" {
#endif

struct musicstore;

struct musicstore * ms_create ();
void ms_destroy (struct musicstore *);

int ms_read_from_directory (struct musicstore * s, const char * dirname);

typedef void (*song_callback)(const char * artist, const char * album,
			      unsigned sequence, const char * title);

typedef void (*album_callback)(const char * artist, const char * album,
			       unsigned songs_count);

typedef void (*artist_callback)(const char * artist, unsigned albums_count,
				unsigned songs_count);

void ms_get_artist (const struct musicstore * s,
		    const char * artist, artist_callback cb);

void ms_get_albums (const struct musicstore * s,
		    const char * artist, const char * album, album_callback cb);

void ms_get_songs (const struct musicstore * s,
		   const char * artist, const char * album, const char * title,
		   song_callback cb);

#ifdef __cplusplus
}
#endif

#endif
