//
// Created by Prime on 9/12/2019.
//

#include "songDatabase.h"
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <experimental/optional>
#include <algorithm>
using namespace std;
using experimental::optional;
using experimental::nullopt;




int songDatabase::dumpSongList() {
    ofstream songFile;
    songFile.open ("songList.txt");
    for(auto it = songList.begin(); it != songList.end(); it++) {
        //write song name
        songFile << it->first << ":";
        //write artist names + extras if they exist
        songFile << it->second.writeArtists();
        songFile << endl;
    }
    songFile.close();
    return 0;
}

int songDatabase::openSongList() {
    ifstream songFile;
    songFile.open("songList.txt");
    string song;
    //lines are formatted as
    //song name:artist one:artist two:artist three:...:-g-group name
    while(getline(songFile, song)) {

        std::stringstream test(song);
        std::string segment;
        std::vector<std::string> segmentList;

        while(std::getline(test, segment, ':'))
        {
            segmentList.push_back(segment);
            cout << segment << endl;
        }

        songEntry newSong = songEntry();
        for(int i = 1; i < segmentList.size(); i++) {
            if (segmentList[i].at(0) == '-') {
                if (segmentList[i].at(1) == 'g')
                    newSong.addGroupName(segmentList[i].substr(3));
            }
            else
                newSong.addArtist(segmentList[i]);
        }

        songList.insert(pair<string, songEntry>(segmentList[0], newSong));
    }

    songFile.close();

    return 0;
}


int songDatabase::addSong(string songName, vector<string> &artistNames, optional<string> groupName) {
    songEntry newSong;
    for(int i = 0; i < artistNames.size(); i++)
        newSong.addArtist(artistNames[i]);
    if(groupName)
        newSong.addGroupName(*groupName);
    songList.insert(pair<string, songEntry>(songName, newSong));
}

int songDatabase::addSong(int vb) {

    //get song name to be dictionary key
    cout << "Song name?" << endl;
    string songName;
    getline(cin, songName);

    //get artist count
    cout << "How many artists?" << endl;
    string count;
    getline(cin, count);
    int artistCount = stoi(count);

    //artist name list
    vector<string> artists = {};
    for(int i = 0; i < artistCount; i++) {
        cout << "Artist name?" << endl;
        string name;
        getline(cin, name);
        artists.push_back(name);
    }

    cout << "Optional tags: (0) none, (1) group name" << endl;

    //get group name if applicable and add to entry
    string input;
    getline(cin, input);
    int i = stoi(input);

    optional<string> groupName;

    if(i == 1) {
        cout << "Group name?" << endl;
        getline(cin, *groupName);
    }

    //add entry to list
    addSong(songName, artists, groupName);

    printSongs(vb);

    return 0;
}

int songDatabase::sortGame() {
    return 0;
}

int songDatabase::listSongsByArtist(string artistName) {
    cout << "Songs by " << artistName << ":\n";

    for(map<string, songEntry>::iterator it = songList.begin(); it != songList.end(); it++) {
        if(it->second.hasArtist(artistName))
            cout << ">" << it->first << endl;
    }

    cout << endl;

    return 0;
}

int songDatabase::printSongs(bool verbose) {
    cout << "Tracklist:" << endl << endl;
    for(auto it = songList.begin(); it != songList.end(); it++) {
        cout << ">" << it->first << endl;
        if(verbose)
            it->second.printArtists();
    }

    cout << endl;
    return 0;
}

bool songDatabase::songEntry::hasArtist(string name) {
    if(group)
        if((*group).compare(name) == 0)
            return true;
    if (find(artist.begin(), artist.end(), name) != artist.end())
        return true;
    return false;
}

int songDatabase::songEntry::addArtist(string name) {
    artist.push_back(name);
    return 0;
}

int songDatabase::songEntry::addGroupName(string name) {
    group = name;
    return 0;
}

songDatabase::songEntry::songEntry() : artist() {
    group = nullopt;
}

int songDatabase::songEntry::printArtists() {
    if(group)
        cout << "    Group name: " << *group << endl;
    for(int i = 0; i < artist.size(); i++)
        cout << "\t" << artist[i] << endl;

    return 0;
}

string songDatabase::songEntry::writeArtists() {
    string rtn = "";
    if(artist.size() > 0)
        rtn = (artist[0] + ":");
    for(int i = 1; i < artist.size(); i++)
        rtn += (artist[i] + ":");
    if(group)
        rtn += ("-g-" + *group + ":");

    return rtn;
}
