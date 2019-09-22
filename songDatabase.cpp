//
// Created by Prime on 9/12/2019.
//

#include "songDatabase.h"
#include <random>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <experimental/optional>
#include <algorithm>
using namespace std;
using experimental::optional;
using experimental::make_optional;
using experimental::nullopt;




int songDatabase::dumpSongList() {
    ofstream songFile;
    songFile.open ("songList.txt");
    for(auto & it : songList) {
        //write song name
        songFile << it.first << ":";
        //write artist names + extras if they exist
        songFile << it.second.writeArtists();
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
            segmentList.push_back(segment);

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

int songDatabase::addSong(const string& songName, vector<string> &artistNames, optional<vector<string>> groupName) {
    if(songName.empty()) {
        cout << "Invalid input." << endl;
        return 0;
    }
    songEntry newSong;
    for(const auto & artistName : artistNames)
        newSong.addArtist(artistName);
    if(groupName) {
        for(const auto & i : groupName.value())
            newSong.addGroupName(i);
    }
    songList.insert(pair<string, songEntry>(songName, newSong));
    return 0;
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

    //get group names if applicable and add to entry
    string input;
    getline(cin, input);
    int i = stoi(input);

    optional<vector<string>> groups = nullopt;

    if(i == 1) {

        groups = {};

        //get artist count
        cout << "How many groups?" << endl;
        getline(cin, count);
        int groupCount = stoi(count);

        //artist name list

        for(int j = 0; j < groupCount; j++) {
            cout << "Group name?" << endl;
            string name;
            getline(cin, name);
            groups.value().push_back(name);
        }
    }

    //add entry to list
    addSong(songName, artists, groups);

    printSongs(vb);

    return 0;
}

int songDatabase::getPreferredSong(pair<string, songEntry> &songOne, pair<string, songEntry> &songTwo) {
    cout << "Which song do you prefer?" << endl << "1." << endl;
    printSong(songOne, true);
    cout << endl << "2." << endl;
    printSong(songTwo, true);

    string input;
    getline(cin, input);
    int in = stoi(input);

    return in;
}

int songDatabase::binarySearch(vector<pair<string, songEntry>> &songVector, pair<string, songEntry> songToPlace, int bestSong, int worstSong) {

    //this leads to the occasional repeat question...
    if(worstSong <= bestSong) {
        while (true) {
            int i = getPreferredSong(songToPlace, songVector[bestSong]);
            if (i == 1)
                return bestSong;
            else if (i == 2)
                return bestSong + 1;
            else
                cout << "Invalid input, please try again" << endl;
        }
    }

    int mid = (bestSong + worstSong)/2;

    int in = getPreferredSong(songVector[mid], songToPlace);

    while(true) {
        if (in == 2)
            return binarySearch(songVector, songToPlace, bestSong, mid - 1);
        else if (in == 1)
            return binarySearch(songVector, songToPlace, mid + 1, worstSong);
        else
            cout << "Invalid input, please try again" << endl;
    }

}

int songDatabase::sortGame() {
    vector<pair<string, songEntry>> songVector;

    //move our songs to a vector so we can play our sorting game
    for(auto & it : songList)
        songVector.emplace_back(it);

    shuffle(songVector.begin(), songVector.end(), std::mt19937(std::random_device()()));

    for(int i = 1; i < songVector.size(); i++) {
        int worstSong = i - 1;
        auto currentSong = songVector[i];
        int currentSongDestination = binarySearch(songVector, currentSong, 0, worstSong);

        if(currentSongDestination != i) {
            songVector.erase(songVector.begin() + i);
            songVector.insert(songVector.begin() + currentSongDestination, currentSong);
        }
    }

    cout << "Your sorted list:" << endl;

    for(int i = 0; i < songVector.size(); i++)
        cout << i + 1 << ". " << songVector[i].first << endl;

    cout << endl;

    return 0;
}

int songDatabase::listSongsByArtist(string artistName) {
    cout << "Songs by " << artistName << ":\n";

    for(auto & it : songList) {
        if(it.second.hasArtist(artistName))
            cout << ">" << it.first << endl;
    }

    cout << endl;

    return 0;
}

int songDatabase::printSong(pair<string, songEntry> song, bool verbose) {
    cout << ">" << song.first << endl;
    if(verbose)
        song.second.printArtists();
    return 0;
}

int songDatabase::printSongs(bool verbose) {
    cout << "Tracklist:" << endl << endl;

    for(auto & it : songList)
        printSong(it, verbose);

    cout << endl;
    return 0;
}

bool songDatabase::songEntry::hasArtist(string name) {
    if(group)
        for(int i = 0; i < group.value().size(); i++) {
            if(group.value()[i].compare(name) == 0)
                return true;
        }
    return find(artist.begin(), artist.end(), name) != artist.end();
}

int songDatabase::songEntry::addArtist(string name) {
    artist.push_back(name);
    return 0;
}

int songDatabase::songEntry::addGroupName(string name) {
    if(group == nullopt)
        group = make_optional<vector<string>>({});
    group.value().push_back(name);
    return 0;
}

songDatabase::songEntry::songEntry() : artist(), group() {
    group = nullopt;
}

int songDatabase::songEntry::printArtists() {
    if(group != nullopt) {
        if(group.value().size() > 1)
            cout << "    Group names: " << endl;
        else
            cout << "    Group name: " << endl;
        for (const auto & i : group.value())
            cout << "\t" << i << endl;
    }

    if(artist.size() > 1)
        cout << "    Artists:" << endl;
    else
        cout << "    Artist:" << endl;

    for(const auto & i : artist)
        cout << "\t" << i << endl;

    return 0;
}

string songDatabase::songEntry::writeArtists() {
    string rtn = "";
    for(int i = 0; i < artist.size(); i++)
        rtn += (artist[i] + ":");
    if(group != nullopt)
        for (const auto & i : group.value())
            rtn += ("-g-" + i + ":");

    return rtn;
}
