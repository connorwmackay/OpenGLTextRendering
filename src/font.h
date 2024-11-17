#ifndef FONT_H
#define FONT_H

#include "shader.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <unordered_map>

static FT_Library library;

enum class FontResult {
    Error,
    Success,
};

struct FontGlyph {
    char c;
    int glyphIndex;
    glm::ivec2 pos;
    glm::ivec2 size;

    long advanceX;
    long advancedY;
};

class Font {
    FT_Error error;
    FT_Face face;
    float fontSize;

    // OpenGL State
    GLuint texture;
    GLuint vertexArray;
    GLuint vertexBuffer;
    GLuint instancePositionBuffer;
    GLuint instanceGlyphIndexBuffer;
    GLuint instanceColourBuffer;

    std::unordered_map<char, FontGlyph> glyphs;

    std::vector<glm::vec2> characterPositions;
    std::vector<glm::vec3> characterColours;
    std::vector<int> characterGlyphIndices;

    unsigned int maxCharacterWidth, maxCharacterHeight;

    public:
        static FontResult Init();

        Font() {}

        Font(std::string fontFile, int fontSize);

        void DrawText(std::string text, glm::vec2 position, glm::vec3 colour, float scale);
        void RenderText();

        void Free();

    private:
        // Deal with an error if one if encountered
        FontResult HandleFontError();

        // Load the Glyph Data of All Ascii Characters (A-Z, punctuation etc.) and Pass Bitmap Data to an OpenGL Texture
        void LoadSupportedGlyphs();

        void SetupOpenGLState(unsigned int maxCharacterWidth, unsigned int maxCharacterHeight);
};

#endif