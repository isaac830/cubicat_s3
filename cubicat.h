#ifndef _CUBICAT_H_
#define _CUBICAT_H_
#include "core/singleton.h"
#include "devices/devices.h"
#include "graphic_engine/embed_game_engine.h"
#include "utils/logger.h"

class RendererDisplay : public Display , public DisplayInterface, public DrawStageListener {
    friend class Cubicat;
public:
    // prevent assignment
    RendererDisplay& operator=(const RendererDisplay&) = delete;
    RendererDisplay(const RendererDisplay&) = delete;
    // display interface implementation
    RenderBuffer getRenderBuffer() override;
    uint16_t getBackgroundColor() override {return m_backgroundColor;}
    // draw stage listener implementation
    virtual void onDrawStart(const Region& dirtyRegion) override {};
    virtual void onDrawFinish(const Region& dirtyRegion) override;
private:
    RendererDisplay() = default;
};

class Cubicat : public Singleton<Cubicat>
{
    friend class Singleton<Cubicat>;
public:
    void begin(bool wifiEnable, bool speakerEnable, bool micEnable, bool sdEnable);
    // @param swap the buffer automatically if true, otherwise, let the user handle it
    void loop(bool present = true);
public:
    RendererDisplay lcd;
    Speaker         speaker;
    Microphone      mic;
    Wifi            wifi;
    UnifiedStorage  storage;
#ifdef CONFIG_BT_ENABLED
    BLEClient& bluetooth = *BLEClient::getInstance();
#endif
#if !CONFIG_REMOVE_GRAPHIC_ENGINE
    EmbedGameEngine engine;
#endif
private:
    Cubicat() = default;
    ~Cubicat() = default;
};

#define CUBICAT Cubicat::getInstance()
#endif