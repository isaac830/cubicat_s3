/*
* @author       Isaac
* @date         2024-08-20
* @license      MIT License
* @copyright    Copyright (c) 2024 Deer Valley
*/
#ifndef _EMBED_GAME_ENGINE_H_
#define _EMBED_GAME_ENGINE_H_
#include "scene_manager.h"
#include "tick_manager/ticke_manager.h"
#include "input_manager.h"
#include "component/sheet_animation_component.h"
#include "component/rigidbody_component.h"
#include "core/message/message_tube.h"
#include "schedule_manager.h"
#include "resource_manager.h"

class EmbedGameEngine
{
public:
    EmbedGameEngine();
    ~EmbedGameEngine();
    SceneManager* createSceneManager();
    TickManager* createTickManager();
    ScheduleManager* createScheduleManager();
    ResourceManager* createResourceManager();
    // scene graph renderer
    // @param displayInterface draw interface
    Renderer* createRenderer(DisplayInterface* backBuffer);
    void update();
    void setFPS(uint16_t fps) {m_FPS = fps;}
    float getFPS();
    SceneManager* getSceneManager() {return m_pSceneMgr;}
    TickManager* getTickManager() {return m_pTickMgr;}
    ScheduleManager* getScheduleManager() {return m_pScheduleMgr;}
    Renderer* getRenderer() {return m_pRenderer;}
    ResourceManager* getResourceManager() {return m_pResourceManager;}
private:
    SceneManager*                   m_pSceneMgr = nullptr;
    ResourceManager*                m_pResourceManager = nullptr;
    TickManager*                    m_pTickMgr = nullptr;
    ScheduleManager*                m_pScheduleMgr = nullptr;
    Renderer*                       m_pRenderer = nullptr;
    uint16_t                        m_FPS = 60;
};

#endif