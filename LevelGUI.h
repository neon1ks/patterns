#pragma once

#include <cstdint>

#include "GameObject.h"

class LevelGUI : public GameObject
{
public:
    LevelGUI() = default;

    void __fastcall SetParam(uint64_t passedTimeNew, uint64_t fpsNew, uint16_t bombsNumberNew,
                             int scoreNew);

    void __fastcall SetHeight(uint16_t heightN) { height = heightN; };

    [[nodiscard]] inline uint16_t GetFinishX() const { return finishX; }
    inline void SetFinishX(uint16_t finishXN) { finishX = finishXN; }

    void Draw() const override;

private:
    uint16_t height = 0;
    uint16_t finishX = 109;

    uint64_t passedTime = 0;
    uint64_t fps = 0;
    uint16_t bombsNumber = 0;
    int score = 0;
};
