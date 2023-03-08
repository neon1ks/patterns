
#include <conio.h>
#include <windows.h>

#include "Logger.h"
#include "ScreenSingleton.h"
#include "SBomber.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"
#include "House.h"

#include <thread>

using namespace std;

SBomber::SBomber()
{
    Logger::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

    auto *p = new Plane;
    p->SetDirection(1, 0.1);
    p->SetSpeed(4);
    p->SetPos(5, 10);
    vecDynamicObj.push_back(p);

    auto *pGUI = new LevelGUI;
    pGUI->SetParam(passedTime, fps, bombsNumber, score);
    const uint16_t maxX = ScreenSingleton::getInstance().GetMaxX();
    const uint16_t maxY = ScreenSingleton::getInstance().GetMaxY();
    const uint16_t offset = 3;
    const uint16_t width = maxX - 7;
    pGUI->SetPos(offset, offset);
    pGUI->SetWidth(width);
    pGUI->SetHeight(maxY - 4);
    pGUI->SetFinishX(offset + width - 4);
    vecStaticObj.push_back(pGUI);

    auto *pGr = new Ground;
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

    auto *pHouse = new House;
    pHouse->SetWidth(13);
    pHouse->SetPos(80, groundY - 1);
    vecStaticObj.push_back(pHouse);

    /*
    Bomb* pBomb = new Bomb;
    pBomb->SetDirection(0.3, 1);
    pBomb->SetSpeed(2);
    pBomb->SetPos(51, 5);
    pBomb->SetSize(SMALL_CRATER_SIZE);
    vecDynamicObj.push_back(pBomb);
    */
}

SBomber::~SBomber()
{
    for (auto &it : vecDynamicObj) {
        delete it;
    }

    for (auto &it : vecStaticObj) {
        delete it;
    }
}

void SBomber::MoveObjects()
{
    Logger::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

    for (auto &it : vecDynamicObj) {
        if (it != nullptr) {
            it->Move(deltaTime);
        }
    }
};

void SBomber::CheckObjects()
{
    Logger::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

    CheckPlaneAndLevelGUI();
    CheckBombsAndGround();
};

void SBomber::CheckPlaneAndLevelGUI()
{
    if (FindPlane()->GetX() > FindLevelGUI()->GetFinishX()) {
        exitFlag = true;
    }
}

void SBomber::CheckBombsAndGround()
{
    vector<Bomb *> vecBombs = FindAllBombs();
    Ground *pGround = FindGround();
    const double y = pGround->GetY();
    for (auto &vecBomb : vecBombs) {
        if (vecBomb->GetY() >= y) // Пересечение бомбы с землей
        {
            pGround->AddCrater(vecBomb->GetX());
            CheckDestoyableObjects(vecBomb);
            DeleteDynamicObj(vecBomb);
        }
    }
}

void SBomber::CheckDestoyableObjects(Bomb *pBomb)
{
    vector<DestroyableGroundObject *> vecDestoyableObjects = FindDestoyableGroundObjects();
    const double size = pBomb->GetWidth();
    const double size_2 = size / 2;
    for (auto &vecDestoyableObject : vecDestoyableObjects) {
        const double x1 = pBomb->GetX() - size_2;
        const double x2 = x1 + size;
        if (vecDestoyableObject->isInside(x1, x2)) {
            score = score + vecDestoyableObject->GetScore();
            DeleteStaticObj(vecDestoyableObject);
        }
    }
}

void SBomber::DeleteDynamicObj(DynamicObject *pObj)
{
    auto it = vecDynamicObj.begin();
    for (; it != vecDynamicObj.end(); it++) {
        if (*it == pObj) {
            vecDynamicObj.erase(it);
            break;
        }
    }
}

void SBomber::DeleteStaticObj(GameObject *pObj)
{
    auto it = vecStaticObj.begin();
    for (; it != vecStaticObj.end(); it++) {
        if (*it == pObj) {
            vecStaticObj.erase(it);
            break;
        }
    }
}

vector<DestroyableGroundObject *> SBomber::FindDestoyableGroundObjects() const
{
    vector<DestroyableGroundObject *> vec;
    Tank *pTank = nullptr;
    House *pHouse = nullptr;
    for (auto *it : vecStaticObj) {
        pTank = dynamic_cast<Tank *>(it);
        if (pTank != nullptr) {
            vec.push_back(pTank);
            continue;
        }

        pHouse = dynamic_cast<House *>(it);
        if (pHouse != nullptr) {
            vec.push_back(pHouse);
            continue;
        }
    }

    return vec;
}

Ground *SBomber::FindGround() const
{
    Ground *pGround = nullptr;

    for (auto *it : vecStaticObj) {
        pGround = dynamic_cast<Ground *>(it);
        if (pGround != nullptr) {
            return pGround;
        }
    }

    return nullptr;
}

vector<Bomb *> SBomber::FindAllBombs() const
{
    vector<Bomb *> vecBombs;

    for (auto *it : vecDynamicObj) {
        auto *pBomb = dynamic_cast<Bomb *>(it);
        if (pBomb != nullptr) {
            vecBombs.push_back(pBomb);
        }
    }

    return vecBombs;
}

Plane *SBomber::FindPlane() const
{
    for (auto *it : vecDynamicObj) {
        auto *p = dynamic_cast<Plane *>(it);
        if (p != nullptr) {
            return p;
        }
    }

    return nullptr;
}

LevelGUI *SBomber::FindLevelGUI() const
{
    for (auto *it : vecStaticObj) {
        auto *p = dynamic_cast<LevelGUI *>(it);
        if (p != nullptr) {
            return p;
        }
    }

    return nullptr;
}

void SBomber::ProcessKBHit()
{
    int c = _getch();

    if (c == 224) {
        c = _getch();
    }

    Logger::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked. key = ", c);

    switch (c) {

    case 27: // esc
        exitFlag = true;
        break;

    case 72: // up
        FindPlane()->ChangePlaneY(-0.25);
        break;

    case 80: // down
        FindPlane()->ChangePlaneY(0.25);
        break;

    case 'b':
    case 'B':
        DropBomb();
        break;

    default:
        break;
    }
}

void SBomber::DrawFrame()
{
    Logger::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

    for (auto *it : vecDynamicObj) {
        if (it != nullptr) {
            it->Draw();
        }
    }

    for (auto *it : vecStaticObj) {
        if (it != nullptr) {
            it->Draw();
        }
    }

    ScreenSingleton::getInstance().GotoXY(0, 0);
    fps++;

    FindLevelGUI()->SetParam(passedTime, fps, bombsNumber, score);
}

void SBomber::TimeStart()
{
    Logger::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");
    startTime = GetTickCount64();
}

void SBomber::TimeFinish()
{
    finishTime = GetTickCount64();
    deltaTime = uint16_t(finishTime - startTime);
    passedTime += deltaTime;

    Logger::getInstance().WriteToLog(string(__FUNCTION__) + " deltaTime = ", (int)deltaTime);

    std::this_thread::sleep_for(20ms);
}

void SBomber::DropBomb()
{
    if (bombsNumber > 0) {
        Logger::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

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
