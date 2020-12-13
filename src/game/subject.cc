#include "subject.h"

void Subject::notify(){
    for (auto &ob : observers) ob->update( *this );
}
