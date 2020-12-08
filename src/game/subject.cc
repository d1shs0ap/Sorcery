#include "subject.h"
#include "../view/observer.h"

void Subject::notify(){
    for (auto &ob : observers) ob->update( *this );
}
