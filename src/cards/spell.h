#ifndef SPELL_H
#define SPELL_H

#include <memory>
#include "card.h"

class Game;

// Spell card
class Spell : public Card {
    std::string description;

    public:
        Spell();
        Spell(std::string name, int owner, int cost, std::string description);
        virtual void effect(std::shared_ptr<Game> game);
        virtual void effect(std::shared_ptr<Game> game, int player, int target);
        virtual void effect(std::shared_ptr<Game> game, int player);
        std::string getDescription() const;

        virtual ~Spell();
};

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
class Banish : public Spell{
    public:
        explicit Banish(int owner);
        void effect(std::shared_ptr<Game> game) override;
        void effect(std::shared_ptr<Game> game, int player, int target) override;
        void effect(std::shared_ptr<Game> game, int player) override;
};

class Unsummon : public Spell{
    public:
        explicit Unsummon(int owner);
        void effect(std::shared_ptr<Game> game) override;
        void effect(std::shared_ptr<Game> game, int player, int target) override;
        void effect(std::shared_ptr<Game> game, int player) override;
};

class Recharge : public Spell{
    public:
        explicit Recharge(int owner);
        void effect(std::shared_ptr<Game> game) override;
        void effect(std::shared_ptr<Game> game, int player, int target) override;
        void effect(std::shared_ptr<Game> game, int player) override;
};

class Disenchant : public Spell{
    public:
        explicit Disenchant(int owner);
        void effect(std::shared_ptr<Game> game) override;
        void effect(std::shared_ptr<Game> game, int player, int target) override;
        void effect(std::shared_ptr<Game> game, int player) override;
};

class RaiseDead : public Spell{
    public:
        explicit RaiseDead(int owner);
        void effect(std::shared_ptr<Game> game) override;
        void effect(std::shared_ptr<Game> game, int player, int target) override;
        void effect(std::shared_ptr<Game> game, int player) override;
};

class Blizzard : public Spell{
    public: 
        explicit Blizzard(int owner);
        void effect(std::shared_ptr<Game> game) override;
        void effect(std::shared_ptr<Game> game, int player, int target) override;
        void effect(std::shared_ptr<Game> game, int player) override;
};

#endif
