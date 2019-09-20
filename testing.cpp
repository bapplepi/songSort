//
// Created by Prime on 9/12/2019.
//

#include "songDatabase.h"
#include <experimental/optional>
using experimental::optional;
using experimental::nullopt;

int main() {
    songDatabase songs;

    //1. attempt to print an empty database
    songs.printSongs(true);

    //2. pass empty arguments
    vector<string> artists = {};
    songs.addSong("", artists, "");

    //3. search for an artist that doesn't exist
    songs.listSongsByArtist("test");

    //4. print what should still be an empty list
    songs.printSongs(true);

    //5. add a proper song
    artists.push_back("Beethoven");
    songs.addSong("Ode to Joy", artists, nullopt);

    //6. print
    songs.printSongs(true);

    //7. search for an empty artist
    songs.listSongsByArtist("");

    //8. search for the artist added
    songs.listSongsByArtist("Beethoven");

    //9. add a second song
    artists.insert(artists.begin(), "Bach");
    songs.addSong("That's Classic", artists, "The Bs");

    //10. print
    songs.printSongs(true);

    //11. search artist
    songs.listSongsByArtist("Beethoven");
    songs.listSongsByArtist("Bach");
    songs.listSongsByArtist("Brahms");
}
