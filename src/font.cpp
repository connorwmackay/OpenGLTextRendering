#include "font.h"

FontResult Font::Init() {
    if (FT_Init_FreeType(&library))
        return FontResult::Error;

    return FontResult::Success;
}

Font::Font(std::string fontFile, int fontSize) 
    : fontSize(fontSize) {
    error = FT_New_Face(library, fontFile.c_str(), 0, &face);

    if (error == FT_Err_Unknown_File_Format) {
        std::cout << "Could not load font due to unknown file format\n";
        return;
    } else if (error) {
        std::cout << "Encountered an error when loading the font\n";
        return;
    } else {
        std::cout << "Successfully loaded font\n";
    }

    error = FT_Set_Pixel_Sizes(face, 0, fontSize);
    HandleFontError();
    
    characterPositions = std::vector<glm::vec2>();
    characterColours = std::vector<glm::vec3>();
    characterGlyphIndices = std::vector<int>();

    LoadSupportedGlyphs();
}

void Font::Free() {
    FT_Done_Face(face);
    glDeleteTextures(1, &texture);
}

// Deal with an error if one if encountered
FontResult Font::HandleFontError() {
    if (error) {
        std::cout << "Encountered a font error\n";
        return FontResult::Error;
    }

    return FontResult::Success;
}

void Font::LoadSupportedGlyphs() {
    glyphs = std::unordered_map<char, FontGlyph>();

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D_ARRAY, texture);

    int glyph_index = 0;
    int x = 0;
    int y = 0;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    std::cout << "Start Loading Glyphs\n";
    maxCharacterWidth = 1;
    maxCharacterHeight = 1;

    for (char current_char = 32; current_char < 127; current_char++) {
        auto glyph_char_index = FT_Get_Char_Index(face, current_char);

        error = FT_Load_Glyph(face, glyph_char_index, FT_LOAD_RENDER);
        if (HandleFontError() == FontResult::Error)
            continue;

        if (face->glyph->bitmap.width > maxCharacterWidth)
            maxCharacterWidth = face->glyph->bitmap.width;
        
        if (face->glyph->bitmap.rows > maxCharacterHeight)
            maxCharacterHeight = face->glyph->bitmap.rows;
    }

    // Make sure it can fit even the largest character
    maxCharacterWidth++;
    maxCharacterWidth++;

    glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_R8, maxCharacterWidth, maxCharacterHeight, 95);
    for (char current_char = 32; current_char < 127; current_char++) {
        auto glyph_char_index = FT_Get_Char_Index(face, current_char);

        error = FT_Load_Glyph(face, glyph_char_index, FT_LOAD_RENDER);
        
        glyphs.insert({
            current_char, 
            {
                current_char,
                glyph_index,
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                face->glyph->advance.x,
                face->glyph->advance.y
            }
        });

        glTexSubImage3D(
            GL_TEXTURE_2D_ARRAY,
            0,
            0,
            0,
            glyph_index,
            glyphs.at(current_char).size.x,  
            glyphs.at(current_char).size.y,
            1,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );

        glyph_index++;
        x += face->glyph->advance.x >> 6;
        y += face->glyph->advance.y >> 6;
    }

    for (const auto& glyphPair : glyphs) {
        std::cout << "Char: " << glyphPair.first << ", Texture Index: " << glyphPair.second.glyphIndex << "\n";
    }

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

    SetupOpenGLState(maxCharacterWidth, maxCharacterHeight);
}

void Font::SetupOpenGLState(unsigned int maxCharacterWidth, unsigned int maxCharacterHeight) {
    // Create OpenGL Objects
    glCreateVertexArrays(1, &vertexArray);
    glCreateBuffers(1, &vertexBuffer);
    glCreateBuffers(1, &instancePositionBuffer);
    glCreateBuffers(1, &instanceGlyphIndexBuffer);
    glCreateBuffers(1, &instanceColourBuffer);

    glBindVertexArray(vertexArray);

    float unit = 1;
    float x = -1.0;
    float y = -1.0;

    float glyphVertices[6][4] = {
        {x, y + maxCharacterHeight*unit, 0.0f, 1.0f},
        {x, y, 0.0f, 0.0f},
        {x + maxCharacterWidth*unit, y, 1.0f, 0.0f},

        {x, y + maxCharacterHeight*unit, 0.0f, 1.0f},
        {x + maxCharacterWidth*unit, y, 1.0f, 0.0f},
        {x + maxCharacterWidth*unit, y + maxCharacterHeight*unit, 1.0, 1.0}
    };

    // Vertices
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, glyphVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Instance Positions
    glBindBuffer(GL_ARRAY_BUFFER,  instancePositionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2), nullptr, GL_STREAM_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glVertexAttribDivisor(1, 1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Instance Colours
    glBindBuffer(GL_ARRAY_BUFFER,  instanceColourBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3), nullptr, GL_STREAM_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glVertexAttribDivisor(2, 1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Instance Colours
    glBindBuffer(GL_ARRAY_BUFFER,  instanceGlyphIndexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(int), nullptr, GL_STREAM_DRAW);
    glEnableVertexAttribArray(3);
    glVertexAttribIPointer(3, 1, GL_INT, GL_FALSE, (void*)0);
    glVertexAttribDivisor(3, 1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Unbind OpenGL Objects
    glBindVertexArray(0);
}

void Font::DrawText(std::string text, glm::vec2 position, glm::vec3 colour, float scale) {
    glm::vec2 currentCharacterPosition = position;
    for (char c : text) {
        if (glyphs.find(c) != glyphs.end()) {
            FontGlyph glyph = glyphs.at(c);

            float curX = currentCharacterPosition.x + maxCharacterWidth * scale;
            float curY = currentCharacterPosition.y + (maxCharacterHeight - glyph.pos.y) * scale;

            characterPositions.push_back(glm::vec2(curX, curY));
            characterColours.push_back(colour);
            characterGlyphIndices.push_back((int)glyph.glyphIndex);

            currentCharacterPosition.x += (glyph.advanceX >> 6) * scale;
        }
    }
}

void Font::RenderText() {
    // Pass the Character Data to OpenGL
    glDepthMask(GL_FALSE);
    glBindBuffer(GL_ARRAY_BUFFER,  instancePositionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * characterPositions.size(), characterPositions.data(), GL_STREAM_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER,  instanceColourBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * characterColours.size(), characterColours.data(), GL_STREAM_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER,  instanceGlyphIndexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(int) * characterGlyphIndices.size(), characterGlyphIndices.data(), GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(vertexArray);
    glBindTexture(GL_TEXTURE_2D_ARRAY, texture);
    // Could be incorrect
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6 * characterPositions.size(), characterPositions.size());
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    glBindVertexArray(0);
    glDepthMask(GL_TRUE);

    // Clear Character Data
    characterPositions.clear();
    characterColours.clear();
    characterGlyphIndices.clear();
}