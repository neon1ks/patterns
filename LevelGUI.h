#pragma once

#include <stdint.h>

#include "GameObject.h"
#include "ICharacter.h"

#include <string>
#include <vector>
#include <queue>

class LevelGUI : public GameObject, public ICharacter
{
public:
    LevelGUI(Mediator *m, const std::string &n)
        : ICharacter(m), name(n), bombsNumber(0), score(0), passedTime(0), fps(0), height(0)
    {
    }

    void __fastcall SetParam(uint64_t passedTimeNew, uint64_t fpsNew, uint16_t bombsNumberNew,
                             int16_t scoreNew);

    void __fastcall SetHeight(uint16_t heightN) { height = heightN; };

    inline uint16_t GetFinishX() const { return finishX; }
    inline void SetFinishX(uint16_t finishXN) { finishX = finishXN; }

    void Draw() const override;

    void beNotified(const std::string &message, ICharacter const *const character) override;
    void sendMessage(const std::string &message) override { } // Empty

    std::string getName() const override { return name; }

private:
    std::string name;

    uint16_t bombsNumber;
    int16_t score;
    uint64_t passedTime;
    uint64_t fps;
    uint16_t height;

    uint16_t finishX = 109;
    uint64_t next = 0;
    std::string currentMessage;
    std::queue<std::string> messages;
};
