#ifndef _SPRITESHEET_H_
#define _SPRITESHEET_H_
#include "drawable.h"

class SpriteSheet : public Drawable
{
public:
    DECLARE_RTTI_SUB(SpriteSheet, Drawable);
    static SharedPtr<SpriteSheet> create(uint16_t width, uint16_t height, const uint16_t* data, uint16_t col, uint16_t row, bool hasMask,
     uint16_t maskColor = 0, const uint16_t* palette = nullptr, uint8_t bpp = 16) {
        return SharedPtr<SpriteSheet>(NEW SpriteSheet(width, height, data, col, row, hasMask, maskColor, palette, bpp));
     }
    const uint16_t* getDrawData() override;
    void setFrame(int nth);
    // Todo:设置使用外部的帧数据. 针对于一个动画使用多张序列图片的情况，后期可能会修改使用更统一的机制
    void setFrameData(const uint16_t* data, uint16_t width, uint16_t height, uint16_t maskColor);
private:
    SpriteSheet(uint16_t width, uint16_t height, const uint16_t* data, uint16_t col, uint16_t row, bool hasMask, uint16_t maskColor = 0, 
    const uint16_t* palette = nullptr, uint8_t bpp = 16);
    const uint16_t*     m_data;
    const uint16_t*     m_frameDataPtr;
    unsigned int        m_col : 8;   
    unsigned int        m_row : 8;     
    unsigned int        m_currentFrame : 8;
    Vector2             m_originSize;
    uint16_t            m_originMaskColor;
};
typedef SharedPtr<SpriteSheet>       SpriteSheetPtr;
inline const uint16_t* SpriteSheet::getDrawData() {
    return m_frameDataPtr;
}
#endif