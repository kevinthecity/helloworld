/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"

// Define the LLaMATokenizer type
typedef std::unique_ptr<LLaMATokenizer> LLaMATokenizerPtr;

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

        // Initialize the LLaMATokenizer model
        std::string modelPath = "/root/llama-models/models/llama3_1/Meta-Llama-3.1-8B/consolidated.00.pth";
        LLaMATokenizerPtr tokenizer(new LLaMATokenizer(modelPath));

        // Use the tokenizer to process user input
        if (sConfigMgr->GetOption<bool>("MyModule.Enable", false))
        {
            ChatHandler(player->GetSession()).PSendSysMessage("Hello, world!");

            // Process user input using the LLaMATokenizer
            std::string userInput = "What's your name?";
            auto response = tokenizer->processInput(userInput);
            ChatHandler(player->GetSession()).PSendSysMessage(response.data());
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