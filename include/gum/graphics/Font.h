#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

#include "../math/IVec2.h"
#include <map>

namespace gum {
    
class Font {
public:
    Font(std::string file_name, int size);
    ~Font();
private:
    struct Character {
        unsigned int texture_id;
        IVec2 size;
        IVec2 bearing;
        unsigned int advance;
    };

    std::map<char, Character> characters;

    static FT_Library ft;
    static FT_Face face;
    static int num_fonts_created;
    static bool ft_initialized;
};

}
