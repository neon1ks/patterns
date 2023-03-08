#pragma once

#include <vector>

#include "LevelGUI.h"
#include "Plane.h"
#include "Bomb.h"
#include "Ground.h"
#include "DestroyableGroundObject.h"

class SBomber
{
public:
    SBomber();

    SBomber(const SBomber &root) = delete;
    SBomber &operator=(const SBomber &) = delete;

    SBomber(SBomber &&root) = delete;
    SBomber &operator=(SBomber &&) = delete;

    ~SBomber();

    [[nodiscard]] inline bool GetExitFlag() const { return exitFlag; }

    void ProcessKBHit();
    void TimeStart();
    void TimeFinish();

    void DrawFrame();
    void MoveObjects();
    void CheckObjects();

private:
    void CheckPlaneAndLevelGUI();
    void CheckBombsAndGround();
    void __fastcall CheckDestoyableObjects(Bomb *pBomb);

    void __fastcall DeleteDynamicObj(DynamicObject *pBomb);
    void __fastcall DeleteStaticObj(GameObject *pObj);

    [[nodiscard]] Ground *FindGround() const;
    [[nodiscard]] Plane *FindPlane() const;
    [[nodiscard]] LevelGUI *FindLevelGUI() const;
    [[nodiscard]] std::vector<DestroyableGroundObject *> FindDestoyableGroundObjects() const;
    [[nodiscard]] std::vector<Bomb *> FindAllBombs() const;

    void DropBomb();

    std::vector<DynamicObject *> vecDynamicObj;
    std::vector<GameObject *> vecStaticObj;

    bool exitFlag = false;

    uint64_t startTime = 0;
    uint64_t finishTime = 0;
    uint64_t passedTime = 0;
    uint16_t bombsNumber = 10;
    uint16_t deltaTime = 0;
    uint16_t fps = 0;
    int score = 0;
};
