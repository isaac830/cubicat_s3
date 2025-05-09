#include "font.h"
#include <string>
#include "gb2312font_20.h"
#include "utils/helper.h"
#include <algorithm>
#include <cmath>

FontData DefaultFontData = {
    .glyphData = GB2312_GlyphData_20,
    .fontSize = GB2312_FontSize_20,
    .charCount = GB2312_CharCount_20,
    .charSet = GB2312_CharSet_20
};

int getCharIndex(const char* str, const char* target) {
    int char_count = 0;
    while (*str) {
        // count current char
        if ((*str & 0x80) == 0) {
            // ASCII char, 1 byte
            str++;
        } else if ((*str & 0xE0) == 0xC0) {
            // 2 bytes char
            str += 2;
        } else if ((*str & 0xF0) == 0xE0) {
            // 3 bytes char
            str += 3;
        } else {
            // 4 bytes char
            str += 4;
        }
        // compare current char to target char
        if (strncmp(str - strlen(target), target, strlen(target)) == 0) {
            return char_count;
        }
        char_count++;
    }
    return -1; 
}

std::vector<std::string> splitUTF8(const char* s) {
    std::vector<std::string> characters;
    while (*s) {
        std::string current_char;

        if ((*s & 0x80) == 0) {
            // 1 byte char（ASCII）
            current_char += *s;
            s++;
        } else if ((*s & 0xE0) == 0xC0) {
            // 2 bytes char
            current_char += s[0];
            current_char += s[1];
            s += 2;
        } else if ((*s & 0xF0) == 0xE0) {
            // 3 bytes char
            current_char += s[0];
            current_char += s[1];
            current_char += s[2];
            s += 3;
        } else if ((*s & 0xF8) == 0xF0) {
            // 4 bytes char
            current_char += s[0];
            current_char += s[1];
            current_char += s[2];
            current_char += s[3];
            s += 4;
        }

        characters.push_back(current_char);
    }

    return characters;
}
void calculateUTFStringSize(const char* text, uint16_t* width, uint16_t* height) {
    const uint16_t SingleGlyphDataLen = 4 + ceil(DefaultFontData.fontSize * DefaultFontData.fontSize / 8.0f);
    auto lines = splitString(text, "\n");
    *height = (DefaultFontData.fontSize * 1.5) * lines.size();//加半个字模高度，为了不同字符的高低对齐
    *width = 0;
    for (auto& line : lines) {
        auto characters = splitUTF8(line.c_str());
        uint16_t lineWidth = 0;
        for (auto& character : characters) {
            int index = getCharIndex((const char*)DefaultFontData.charSet, character.c_str());
            if (index >= 0) {
                auto ptr = DefaultFontData.glyphData + index * SingleGlyphDataLen;
                // 字模数据前4字节为字模bbox数据
                uint8_t data[4] = { 0 };
                memcpy(data, (uint8_t*)ptr, 4);
                auto glyphWidth = data[2] - data[0];
                lineWidth += glyphWidth;
            }
        }
        *width = std::max(*width, lineWidth);
    }
}