#include "Game.h"

#include "path.h"

#include <cstdio>

#if	defined(_WIN32) && !defined(__LIBRETRO__)
#include <windows.h>
#endif

#if defined(unix) || defined(__unix__) || defined(__unix) || defined(__APPLE__)
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

CGame::CGame(const char *rootDirectory)
{
    // make sure that the .smw directory is created
    std::string smwHome = GetHomeDirectory();

#if	defined(_WIN32) && !defined(__LIBRETRO__)
    if (CreateDirectory(smwHome .c_str(), NULL) ||
            ERROR_ALREADY_EXISTS == GetLastError()) {
    	//TODO: print that directory already exists

    } else {
    	//TODO: print that we created the directory
    }
#else
    struct stat st;
    if (stat(smwHome.c_str(), &st) != 0) { // inode does not exist
        if (mkdir(smwHome.c_str(), 0775) != 0)
            perror("[error] Could not create settings directory");
    }
    else if (!S_ISDIR(st.st_mode)) // inode exist, but not a directory
        perror("[error] Could not access settings directory");
#endif

#if defined(_XBOX) && !defined(__LIBRETRO__)
    	//TODO: make this configurable!
    	//TV's seem to need extra shade
    	MenuTransparency = 96;
#else
    	MenuTransparency = 72;
#endif

    ScreenWidth = 640;
    ScreenHeight = 480;
}

CGame::~CGame(void)
{
}
