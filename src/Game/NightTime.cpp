#include "NightTime.hpp"
#include "Global.hpp"
NightTime::NightTime(){

}

void NightTime::process(double delta){
    Global::showStats ^=1;
}