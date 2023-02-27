#pragma once

#include <algorithm>
#include <string>
#include <vector>

class Mediator;

class ICharacter
{
protected:
    Mediator *mediator;

public:
    ICharacter(Mediator *m) : mediator(m) { }

    virtual void beNotified(const std::string &message, ICharacter const *const character) = 0;
    virtual void sendMessage(const std::string &message) = 0;

    virtual std::string getName() const = 0;

    void setMediator(Mediator *pMediator) { this->mediator = pMediator; }
};

class Mediator
{
private:
    std::vector<ICharacter *> v;

public:
    void AddColleague(ICharacter *ch) { v.push_back(ch); }

    void DelColleague(ICharacter *ch) {
        auto it = std::find(v.begin(), v.end(), ch);
        if (it != v.end()) {
            v.erase(it);
        }
    }

    void Notify(ICharacter *from, const std::string &message)
    {
        for (ICharacter *ch : v) {
            if (ch != from) {
                ch->beNotified(message, from);
            }
        }
    }
};
