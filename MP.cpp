#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>
#include <string>
#include <cstring>
#include <windows.h>

using namespace std;

class MusicLibrary
{
private:
    std::vector<std::string> allSongs;
    std::vector<std::string> playlist;
    std::string currentlyPlaying;
    std::string folderPath;

public:
    void loadSongsFromFolder(const std::string &folderPath)
    {
        WIN32_FIND_DATA findFileData;
        HANDLE hFind = FindFirstFile((folderPath + "\\*").c_str(), &findFileData);

        if (hFind == INVALID_HANDLE_VALUE)
        {
            std::cerr << "Error opening directory\n";
            return;
        }

        do
        {
            if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                continue;

            allSongs.push_back(findFileData.cFileName);
        } while (FindNextFile(hFind, &findFileData) != 0);

        FindClose(hFind);
    }

    void displayAllSongs()
    {
        cout << "All Songs:\n";
        for (int i = 0; i < allSongs.size(); ++i)
        {
            cout << i + 1 << ". " << allSongs[i] << endl;
        }
        cout << endl;
    }

    void addToPlaylist(int songNumber)
    {
        if (songNumber >= 1 && songNumber <= allSongs.size())
        {
            playlist.push_back(allSongs[songNumber - 1]);
            cout << "Song added to the playlist.\n\n";
        }
        else
        {
            cout << "Invalid song number.\n\n";
        }
    }

    void removeFromPlaylist(int songNumber)
    {
        if (songNumber >= 1 && songNumber <= playlist.size())
        {
            playlist.erase(playlist.begin() + songNumber - 1);
            cout << "Song removed from the playlist.\n\n";
        }
        else
        {
            cout << "Invalid song number.\n\n";
        }
    }

    void displayPlaylist()
    {
        cout << "Playlist:\n";
        for (int i = 0; i < playlist.size(); ++i)
        {
            cout << i + 1 << ". " << playlist[i] << endl;
        }
        cout << endl;
    }

    void playWithVLC(int songNumber)
    {
        if (songNumber >= 1 && songNumber <= allSongs.size())
        {
            std::string songPath = folderPath + "\\" + allSongs[songNumber - 1];
            std::string vlcCommand = "\"C:\\Program Files\\VideoLAN\\VLC\\vlc.exe\" \"" + songPath + "\"";

            // Use system() to run the VLC command
            int result = system(vlcCommand.c_str());

            if (result == 0)
            {
                cout << "Now playing: " << allSongs[songNumber - 1] << " using VLC\n\n";
            }
            else
            {
                cout << "Error playing the song with VLC\n\n";
            }
        }
        else
        {
            cout << "Invalid song number.\n\n";
        }
    }

    void playSound(const std::string &audioFileName)
    {
        std::string soundPath = folderPath + "\\" + audioFileName;
        if (PlaySound(soundPath.c_str(), NULL, SND_SYNC) == 0)
        {
            cout << "Error playing the sound.\n\n";
        }
        else
        {
            cout << "Now playing sound: " << audioFileName << "\n\n";
        }
    }
};

int main()
{
    MusicLibrary musicLibrary;

    std::string folderPath = "C:\\Users\\Sabih\\Desktop\\DSA Project\\music";
    musicLibrary.loadSongsFromFolder(folderPath);

    int choice;
    while (true)
    {
        cout << "Choose an operation:\n"
             << "1. Display All Songs\n"
             << "2. Add Song to Playlist\n"
             << "3. Remove Song from Playlist\n"
             << "4. Display Playlist\n"
             << "5. Play Song with VLC\n"
             << "6. Play Sound\n"
             << "7. Quit\n"
             << "Enter choice: ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            musicLibrary.displayAllSongs();
            break;
        case 2:
        {
            int songNumber;
            cout << "Enter the number of the song to add to the playlist: ";
            cin >> songNumber;
            musicLibrary.addToPlaylist(songNumber);
        }
        break;
        case 3:
        {
            int songNumber;
            cout << "Enter the number of the song to remove from the playlist: ";
            cin >> songNumber;
            musicLibrary.removeFromPlaylist(songNumber);
        }
        break;
        case 4:
            musicLibrary.displayPlaylist();
            break;
        case 5:
        {
            int songNumber;
            cout << "Enter the number of the song to play with VLC: ";
            cin >> songNumber;
            musicLibrary.playWithVLC(songNumber);
        }
        break;
        case 6:
        {
            std::string soundFileName;
            cout << "Enter the name of the sound file to play: ";
            cin >> soundFileName;
            musicLibrary.playSound(soundFileName);
        }
        break;
        case 7:
            exit(0);
        default:
            cout << "Invalid choice. Please try again.\n\n";
        }
    }

    return 0;
}
