#include "../../include/gum/graphics/Font.h"
#include "../../include/gum/graphics/Shader.h"
#include <iostream>
#include <GL/glew.h>

namespace gum {

FT_Library Font::ft;
FT_Face Font::face;
int Font::num_fonts_created = 0;
bool Font::ft_initialized = false;;

unsigned int Font::shader_program = 0;
Mat4 Font::ortho_perspective;

unsigned int Font::vao = 0;
unsigned int Font::vbo = 0;


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
            (unsigned int) face->glyph->advance.x / 64
        };
        characters.insert(std::pair<char, Character>(c, character));
    }

    error = FT_Done_Face(face);

    num_fonts_created++;

    shader_program = LoadShadersByPath("shaders/font_vertex.glsl", "shaders/font_fragment.glsl");

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Font::~Font() {
    num_fonts_created--;
    if (num_fonts_created == 0) {
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
    }
}

void Font::draw(std::string s, float x, float y, float screen_w, float screen_h) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(vao);
    glUseProgram(shader_program);

    glUniformMatrix4fv(glGetUniformLocation(shader_program, "projection"), 1, false, ortho_perspective.data());

    ortho_perspective = Mat4::ortho(0.0f, screen_h, 0.0f, screen_w, 0.0f, 50.0f);

    float scale = 1.0f;

    for(int i = 0; i < (int) s.length(); i++) {
        Character c = characters.at(s[i]);

        float w = c.size.x * scale;
        float h = c.size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { x,    y+ h,    0.0f, 0.0f },            
            { x,    y,       0.0f, 1.0f },
            { x+ w, y,       1.0f, 1.0f },

            { x,    y+ h,    0.0f, 0.0f },
            { x+ w, y,       1.0f, 1.0f },
            { x+ w, y+ h,    1.0f, 0.0f }           
        };

        glBindTexture(GL_TEXTURE_2D, c.texture_id);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (c.advance) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
}

}
