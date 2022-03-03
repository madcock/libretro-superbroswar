#include "gfxFont.h"

#include "SDL_image.h"
#include "sdl12wrapper.h"

#include <cstdio>
#include <cassert>
#include <iostream>

using namespace std;

extern void libretro_printf(const char *fmt, ...);

extern SDL_Surface * blitdest;

gfxFont::gfxFont()
{
    m_font = NULL;
}

gfxFont::~gfxFont()
{
    if (m_font)
        SFont_FreeFont(m_font);
};

bool gfxFont::init(const std::string& filename)
{
    if (m_font)
        SFont_FreeFont(m_font);

    libretro_printf("loading font %s ...", filename.c_str());

    SDL_Surface *fontsurf = IMG_Load(filename.c_str());
    if (fontsurf == NULL) {
        libretro_printf(" ERROR: Couldn't load file %s: %s\n", filename.c_str(), SDL_GetError());
        return false;
    }

    m_font = SFont_InitFont(fontsurf);
    if (!m_font) {
        libretro_printf("\n ERROR: an error occurre while loading the font.\n");
        return false;
    }

    libretro_printf("done\n");
    return true;
}

void gfxFont::draw(int x, int y, const std::string& s)
{
    //if (y + getHeight() < 0)
    //	return;

    SFont_Write(blitdest, m_font, x, y, s.c_str());
}

void gfxFont::drawChopRight(int x, int y, int width, const char *s)
{
    //if (y + getHeight() < 0)
    //	return;

    SFont_WriteChopRight(blitdest, m_font, x, y, width, s);
}

void gfxFont::drawChopLeft(int x, int y, int width, const char *s)
{
    //if (y + getHeight() < 0)
    //	return;

    SFont_WriteChopLeft(blitdest, m_font, x, y, width, s);
}

void gfxFont::drawCentered(int x, int y, const char *text)
{
    //if (y + getHeight() < 0)
    //	return;

    SFont_WriteCenter(blitdest, m_font, x, y, text);
};

void gfxFont::drawChopCentered(int x, int y, int width, const char *text)
{
    //if (y + getHeight() < 0)
    //	return;

    SFont_WriteChopCenter(blitdest, m_font, x, y, width, text);
};

void gfxFont::drawRightJustified(int x, int y, const char *s, ...)
{
    char buffer[256];

    va_list zeiger;
    va_start(zeiger, s);
    vsprintf(buffer, s, zeiger);
    va_end(zeiger);

    //if (y + getHeight() < 0)
    //	return;

    SFont_WriteRight(blitdest, m_font, x, y, buffer);
};


void gfxFont::drawf(int x, int y, const char *s, ...)
{
    char buffer[256];

    va_list zeiger;
    va_start(zeiger, s);
    vsprintf(buffer, s, zeiger);
    va_end(zeiger);

    draw(x,y,buffer);
}

void gfxFont::setalpha(Uint8 alpha)
{
    if ( (SDL_SETALPHABYTE(m_font->Surface, SDL_TRUE, alpha)) < 0) {
        libretro_printf("\n ERROR: couldn't set alpha on sprite: %s\n", SDL_GetError());
    }
}
