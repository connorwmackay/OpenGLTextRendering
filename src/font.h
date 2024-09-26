#ifndef FONT_H
#define FONT_H
#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>
#include <glad/glad.h>

static FT_Library library;

enum class FontResult {
    Error,
    Success,
};

class Font {
    public:
        static FontResult init() {
            if (FT_Init_FreeType(&library))
                return FontResult::Error;

            return FontResult::Success;
        }

        Font(std::string fontFile, int fontSize) {
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
            handle_font_error();

            load_glyphs_gpu();
        }

        ~Font() {
            //glDeleteBuffers(1, &vbo);
            //glDeleteTextures(1, &texture);
            //glDeleteVertexArrays(1, &vao);
        }

        void draw_text(std::string text, int x, int y) {
            // TODO: Implement this.
        }
    protected:
        // Deal with an error if one if encountered
        void handle_font_error() {
            if (error) {
                std::cout << "Encountered a font error\n";
            }
        }

        // Select a glyph and load it into memory
        void load_glyph(const char& c) {
            int glyph_index = FT_Get_Char_Index(face, c);
            error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
            handle_font_error();
        }

        // Get a bitmap of the currently selected glyph
        void render_glyph() {
            error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
            handle_font_error();
        }

        // Load all the glyphs on the GPU side so they can be easily rendered
        void load_glyphs_gpu() {
            // TODO: Loop through all the glyphs
            // TODO: Render each glyph and pass data to gpu

            //glCreateVertexArrays(1, & vao);
            //glCreateBuffers(1, &vbo);
            //glCreateTextures(GL_TEXTURE_2D, 1, &texture);
        }
    private:
        FT_Error error;
        FT_Face face;
        GLuint texture;
        GLuint vao;
        GLuint vbo;
};

#endif