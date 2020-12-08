#ifndef SUBJECT_H
#define SUBJECT_H
#include <memory>
#include <vector>

class Observer;

class Subject {
    std::vector<std::shared_ptr<Observer>> observers;

    protected:
        void notify() const;

    public:
        void attach(Observer &o);
        void detach(Observer &o);
};

#endif
