//
// Created by Prime on 9/15/2019.
//

#include <iostream>
#include "songDatabase.h"
using namespace std;

int main() {

    songDatabase songs;
    songs.openSongList();

    int in = -1;
    int vb = 0;
    string input;


    cout << "List artist info with all songs? (0) no (1) yes" << endl;
    getline(cin, input);
    vb = stoi(input);

    while(true) {
        cout << "(113) to quit, (1) to add a song, (2) to view songs, (3) to view songs by artist." << endl;
        getline(cin, input);
        in = stoi(input);
        if(in == 113) {
            songs.dumpSongList();
            return 0;
        }
        else if(in == 1)
            songs.addSong(vb);
        else if(in == 2)
            songs.printSongs(vb);
        else if(in == 3) {
            cout << "Artist name?" << endl;
            string name;
            getline(cin, name);
            songs.listSongsByArtist(name);
        }
    }
}