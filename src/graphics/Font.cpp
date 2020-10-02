#include "../../include/gum/graphics/Font.h"
#include <iostream>
#include <GL/glew.h>

namespace gum {

FT_Library Font::ft;
FT_Face Font::face;
int Font::num_fonts_created = 0;
bool Font::ft_initialized = false;;

Font::Font(std::string file_name, int size) {
    int error;
    if (!ft_initialized) {
        error = FT_Init_FreeType( &ft );
        if ( error )
        {
            std::cout << "Error initializing freetype" << std::endl;
        }
    }

    FT_Face face;      /* handle to face object */
    error = FT_New_Face( ft,
                         file_name.c_str(), 
                         0,
                         &face );

    if ( error == FT_Err_Unknown_File_Format )
    {
        std::cout << "The font file '" + file_name + "' could be opened and read, but it appears that its font format is unsupported" << std::endl;
    }
    else if ( error )
    {
        std::cout << "The font file '" + file_name + "' could not be opened or read, or it is broken. Error code: " + std::to_string(error) << std::endl;
    }

    error = FT_Set_Char_Size( face,    /* handle to face object           */
                      0,       /* char_width in 1/64th of points  */
                      size*64,   /* char_height in 1/64th of points */
                      300,     /* horizontal device resolution    */
                      300 );   /* vertical device resolution      */

    for (unsigned char c = 0; c < 128; c++)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction
        // load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture, 
            IVec2((int)face->glyph->bitmap.width, face->glyph->bitmap.rows),
            IVec2((int)face->glyph->bitmap_left, face->glyph->bitmap_top),
            (unsigned int) face->glyph->advance.x
        };
        characters.insert(std::pair<char, Character>(c, character));
    }

    error = FT_Done_Face(face);

    num_fonts_created++;
}

Font::~Font() {
    num_fonts_created--;
    if (num_fonts_created == 0) {
        FT_Done_FreeType(ft);
    }
}

}
