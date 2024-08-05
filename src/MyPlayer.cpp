/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"

enum MyPlayerAcoreString
{
    HELLO_WORLD = 35410
};

// Add player scripts
class MyPlayer : public PlayerScript
{
public:
    MyPlayer() : PlayerScript("MyPlayer") {}

    void OnLogin(Player *player) override
    {
        ChatHandler(player->GetSession()).PSendSysMessage("OnLogin called");

        if (sConfigMgr->GetOption<bool>("MyModule.Enable", false))
        {
            ChatHandler(player->GetSession()).PSendSysMessage("Hello, world!");
        }
        else
        {
            ChatHandler(player->GetSession()).PSendSysMessage("<error> MyModule.Enable is false or not set");
        }
    }
};

// Add all scripts in one
void AddMyPlayerScripts()
{
    new MyPlayer();
}
