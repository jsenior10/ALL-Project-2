#include "entity.h"
#include <iostream>
using namespace std;
void Entity::hasInteracted(int hasInteracted){
    currentHealth -= hasInteracted;
    if(currentHealth <= 0){
        
        isDead = true;
    }
}
