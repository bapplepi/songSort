//
// Created by Prime on 9/12/2019.
//

#ifndef SONGSDATABASE_SONGDATABASE_H
#define SONGSDATABASE_SONGDATABASE_H

#include <string>
#include <vector>
#include <map>
#include <experimental/optional>
using namespace std;
using experimental::optional;


class songDatabase {
public:
    //read and write file
    int openSongList();
    int dumpSongList();

    int addSong(int vb);
    int addSong(const string &songName, vector<string> &artistNames, optional<vector<string>> groupName);

    //print info
    int listSongsByArtist(string artistName);
    int printSongs(bool verbose);

    //if i get around to implementing it
    //lets user rank favorite songs
    int sortGame();

private:
    class songEntry {
    public:
        songEntry();

        int addArtist(string name);
        int addGroupName(string name);

        //for searching by artist
        bool hasArtist(string name);
        int printArtists();

        //write to file
        string writeArtists();

    private:
        vector<string> artist;
        optional<vector<string>> group;
    };
    map<string, songEntry> songList;

    int printSong(pair<string, songEntry> song, bool verbose);

    int getPreferredSong(pair<string, songEntry> &songOne, pair<string, songEntry> &songTwo);

    int binarySearch(vector<pair<string, songEntry>> &songVector, pair<string, songEntry> songToPlace, int bestSong,
                     int worstSong);
};

#endif //SONGSDATABASE_SONGDATABASE_H
