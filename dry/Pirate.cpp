
#include "Pirate.h"


/*Pirate::Pirate(const string& name, int bounty){
    this-> name = name;
    this-> bounty = bounty;
}*/
//Pirate::Pirate(const string& name): name(name){}

//Pirate::Pirate(const string& name, DEVIL_FRUIT devilFruit): name(name), devilFruit(devilFruit) {}

Pirate::Pirate(const string& name,int bounty, DEVIL_FRUIT devilFruit) : name(name),bounty(bounty), devilFruit
(devilFruit){}


Pirate ::Pirate() {}

void Pirate::setName(const string& name){
    this->name = name;
}


std::string Pirate::getName(){
    return name;
}
const char* const devilFruitNames[] = {
        "Gum Gum",
        "Smoke Smoke",
        "Flame Flame",
        "Rumble Rumble",
        "String String",
        "Ice Ice",
        "None"
};

std::ostream &operator<<(std::ostream &os, const Pirate &pirate){
    os << pirate.name <<" "<< pirate.bounty<< " (Devil Fruit: " << devilFruitNames[pirate.devilFruit] << ")";
    return os;
}

void Pirate::setBounty(int bounty){
    this-> bounty = bounty;
}

int Pirate::getBounty(){
    return this-> bounty;
}

void Pirate::setDevilFruit(DEVIL_FRUIT devilFruit){
    this->devilFruit = devilFruit;
}
DEVIL_FRUIT Pirate::getDevilFruit(){
    return devilFruit;
}
