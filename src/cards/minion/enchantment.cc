#include "enchantment.h"
#include "../../util.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
Enchantment::Enchantment() {}

void Enchantment::attach(std::shared_ptr<Minion> minion) { component = minion; }

///////////////////////////////////////////////////////////////////////////////////////////////////
// GiantStrength //////////////////////////////////////////////////////////////////////////////////
int GiantStrength::computeAtk() const { return component->computeAtk() + atkBoost + getAtk(); }
int GiantStrength::computeDef() const { return component->computeDef() + defBoost + getDef(); }
std::vector<std::string> GiantStrength::getDisplay() const
{
    std::string line0{"|                               |"};
    std::string line1{"|------                   ------|"};
    std::string line2{"| +2  |                   |  +2 |"};
    std::vector<std::string> result{line0, line0, line0,
                                    line1, line2};
    // should not have used constants but good enough for now. (Dec.12)
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Enrage /////////////////////////////////////////////////////////////////////////////////////////
int Enrage::computeAtk() const { return component->computeAtk() * atkScale + getAtk(); }
int Enrage::computeDef() const { return component->computeDef() - defWound + getDef(); }
std::vector<std::string> Enrage::getDisplay() const
{
    std::string line0{"|                               |"};
    std::string line1{"|------                   ------|"};
    std::string line2{"| *2  |                   |  -2 |"};
    std::vector<std::string> result{line0, line0, line0,
                                    line1, line2};
    // should not have used constants but good enough for now. (Dec.12)
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Delay //////////////////////////////////////////////////////////////////////////////////////////
std::vector<std::string> Delay::getDisplay() const
{
    std::string line1{"| Enchanted minion does not gai |"};
    std::string line2{"| n an action on their next tur |"};
    std::string line3{"| n. This enchantement is autom |"};
    std::string line4{"| atically destroyed after 1 tu |"};
    std::string line5{"| rn                            |"};
    std::vector<std::string> result{line1, line2, line3, line4, line5};
}
