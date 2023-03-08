#include <conio.h>
#include <windows.h>

#include <thread>
#include <vector>

#include "Bomb.h"
#include "DestroyableGroundObject.h"
#include "Ground.h"
#include "House.h"
#include "LevelGUI.h"
#include "MyTools.h"
#include "Plane.h"
#include "Tank.h"

#include "SBomber.h"

using namespace std;
using namespace MyTools;

/*
 *
 * SBomberImpl
 *
 */

class SBomberImpl
{
public:
    SBomberImpl()
    {
        logger.WriteToLog(string(__FUNCTION__) + " was invoked");

        Plane *p = new Plane;
        p->SetDirection(1, 0.1);
        p->SetSpeed(4);
        p->SetPos(5, 10);
        vecDynamicObj.push_back(p);

        LevelGUI *pGUI = new LevelGUI;
        pGUI->SetParam(passedTime, fps, bombsNumber, score);
        const uint16_t maxX = GetMaxX();
        const uint16_t maxY = GetMaxY();
        const uint16_t offset = 3;
        const uint16_t width = maxX - 7;
        pGUI->SetPos(offset, offset);
        pGUI->SetWidth(width);
        pGUI->SetHeight(maxY - 4);
        pGUI->SetFinishX(offset + width - 4);
        vecStaticObj.push_back(pGUI);

        Ground *pGr = new Ground;
        const uint16_t groundY = maxY - 5;
        pGr->SetPos(offset + 1, groundY);
        pGr->SetWidth(width - 2);
        vecStaticObj.push_back(pGr);

        Tank *pTank = new Tank;
        pTank->SetWidth(13);
        pTank->SetPos(30, groundY - 1);
        vecStaticObj.push_back(pTank);

        pTank = new Tank;
        pTank->SetWidth(13);
        pTank->SetPos(50, groundY - 1);
        vecStaticObj.push_back(pTank);

        House *pHouse = new House;
        pHouse->SetWidth(13);
        pHouse->SetPos(80, groundY - 1);
        vecStaticObj.push_back(pHouse);
    };

    ~SBomberImpl()
    {
        for (auto *it : vecDynamicObj) {
            delete it;
        }
        for (auto *it : vecStaticObj) {
            delete it;
        }
    }

protected:
    void CheckPlaneAndLevelGUI()
    {
        if (FindPlane()->GetX() > FindLevelGUI()->GetFinishX()) {
            exitFlag = true;
        }
    }

    void CheckBombsAndGround()
    {
        vector<Bomb *> vecBombs = FindAllBombs();
        Ground *pGround = FindGround();
        const double y = pGround->GetY();
        for (size_t i = 0; i < vecBombs.size(); i++) {
            if (vecBombs[i]->GetY() >= y) // Пересечение бомбы с землей
            {
                pGround->AddCrater(vecBombs[i]->GetX());
                CheckDestoyableObjects(vecBombs[i]);
                DeleteDynamicObj(vecBombs[i]);
            }
        }
    }

    void CheckDestoyableObjects(Bomb *pBomb)
    {
        vector<DestroyableGroundObject *> vecDestoyableObjects = FindDestoyableGroundObjects();
        const double size = pBomb->GetWidth();
        const double size_2 = size / 2;
        for (size_t i = 0; i < vecDestoyableObjects.size(); i++) {
            const double x1 = pBomb->GetX() - size_2;
            const double x2 = x1 + size;
            if (vecDestoyableObjects[i]->isInside(x1, x2)) {
                score += vecDestoyableObjects[i]->GetScore();
                DeleteStaticObj(vecDestoyableObjects[i]);
            }
        }
    }

    void DeleteDynamicObj(DynamicObject *pObj)
    {
        auto it = vecDynamicObj.begin();
        for (; it != vecDynamicObj.end(); it++) {
            if (*it == pObj) {
                vecDynamicObj.erase(it);
                break;
            }
        }
    }

    void DeleteStaticObj(GameObject *pObj)
    {
        auto it = vecStaticObj.begin();
        for (; it != vecStaticObj.end(); it++) {
            if (*it == pObj) {
                vecStaticObj.erase(it);
                break;
            }
        }
    }

    std::vector<DestroyableGroundObject *> FindDestoyableGroundObjects() const
    {
        vector<DestroyableGroundObject *> vec;
        Tank *pTank;
        House *pHouse;
        for (size_t i = 0; i < vecStaticObj.size(); i++) {
            pTank = dynamic_cast<Tank *>(vecStaticObj[i]);
            if (pTank != nullptr) {
                vec.push_back(pTank);
                continue;
            }

            pHouse = dynamic_cast<House *>(vecStaticObj[i]);
            if (pHouse != nullptr) {
                vec.push_back(pHouse);
                continue;
            }
        }

        return vec;
    }

    Ground *FindGround() const
    {
        Ground *pGround;

        for (size_t i = 0; i < vecStaticObj.size(); i++) {
            pGround = dynamic_cast<Ground *>(vecStaticObj[i]);
            if (pGround != nullptr) {
                return pGround;
            }
        }

        return nullptr;
    }

    Plane *FindPlane() const
    {
        for (size_t i = 0; i < vecDynamicObj.size(); i++) {
            Plane *p = dynamic_cast<Plane *>(vecDynamicObj[i]);
            if (p != nullptr) {
                return p;
            }
        }

        return nullptr;
    }

    LevelGUI *FindLevelGUI() const
    {
        for (size_t i = 0; i < vecStaticObj.size(); i++) {
            LevelGUI *p = dynamic_cast<LevelGUI *>(vecStaticObj[i]);
            if (p != nullptr) {
                return p;
            }
        }

        return nullptr;
    }

    std::vector<Bomb *> FindAllBombs() const
    {
        vector<Bomb *> vecBombs;

        for (size_t i = 0; i < vecDynamicObj.size(); i++) {
            Bomb *pBomb = dynamic_cast<Bomb *>(vecDynamicObj[i]);
            if (pBomb != nullptr) {
                vecBombs.push_back(pBomb);
            }
        }

        return vecBombs;
    }

    void DropBomb()
    {
        if (bombsNumber > 0) {
            logger.WriteToLog(string(__FUNCTION__) + " was invoked");

            Plane *pPlane = FindPlane();
            double x = pPlane->GetX() + 4;
            double y = pPlane->GetY() + 2;

            Bomb *pBomb = new Bomb;
            pBomb->SetDirection(0.3, 1);
            pBomb->SetSpeed(2);
            pBomb->SetPos(x, y);
            pBomb->SetWidth(SMALL_CRATER_SIZE);

            vecDynamicObj.push_back(pBomb);
            bombsNumber--;
            score -= Bomb::BombCost;
        }
    }

    std::vector<DynamicObject *> vecDynamicObj;
    std::vector<GameObject *> vecStaticObj;

    bool exitFlag = false;

    uint64_t startTime = 0;
    uint64_t finishTime = 0;
    uint64_t passedTime = 0;
    uint16_t bombsNumber = 10;
    uint16_t deltaTime = 0;
    uint16_t fps = 0;
    int16_t score = 0;

    friend class SBomber;
};

/*
 *
 * SBomber
 *
 */

SBomber::SBomber() : impl(make_unique<SBomberImpl>()) { }
SBomber::~SBomber() = default;

bool SBomber::GetExitFlag() const
{
    return impl->exitFlag;
}

void SBomber::ProcessKBHit()
{
    int c = _getch();

    if (c == 224) {
        c = _getch();
    }

    logger.WriteToLog(string(__FUNCTION__) + " was invoked. key = ", c);

    switch (c) {

    case 27: // esc
        impl->exitFlag = true;
        break;

    case 72: // up
        impl->FindPlane()->ChangePlaneY(-0.25);
        break;

    case 80: // down
        impl->FindPlane()->ChangePlaneY(0.25);
        break;

    case 'b':
        impl->DropBomb();
        break;

    case 'B':
        impl->DropBomb();
        break;

    default:
        break;
    }
}

void SBomber::TimeStart()
{
    logger.WriteToLog(string(__FUNCTION__) + " was invoked");
    impl->startTime = GetTickCount64();
}

void SBomber::TimeFinish()
{
    impl->finishTime = GetTickCount64();
    impl->deltaTime = uint16_t(impl->finishTime - impl->startTime);
    impl->passedTime += impl->deltaTime;

    logger.WriteToLog(string(__FUNCTION__) + " deltaTime = ", (int)impl->deltaTime);

    std::this_thread::sleep_for(20ms);
}

void SBomber::DrawFrame()
{
    logger.WriteToLog(string(__FUNCTION__) + " was invoked");

    for (size_t i = 0; i < impl->vecDynamicObj.size(); i++) {
        if (impl->vecDynamicObj[i] != nullptr) {
            impl->vecDynamicObj[i]->Draw();
        }
    }

    for (size_t i = 0; i < impl->vecStaticObj.size(); i++) {
        if (impl->vecStaticObj[i] != nullptr) {
            impl->vecStaticObj[i]->Draw();
        }
    }

    GotoXY(0, 0);
    impl->fps++;

    impl->FindLevelGUI()->SetParam(impl->passedTime, impl->fps, impl->bombsNumber, impl->score);
}

void SBomber::MoveObjects()
{
    logger.WriteToLog(string(__FUNCTION__) + " was invoked");

    for (size_t i = 0; i < impl->vecDynamicObj.size(); i++) {
        if (impl->vecDynamicObj[i] != nullptr) {
            impl->vecDynamicObj[i]->Move(impl->deltaTime);
        }
    }
};

void SBomber::CheckObjects()
{
    logger.WriteToLog(string(__FUNCTION__) + " was invoked");

    impl->CheckPlaneAndLevelGUI();
    impl->CheckBombsAndGround();
};
