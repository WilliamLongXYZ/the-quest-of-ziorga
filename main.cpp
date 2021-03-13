#include <stdio.h>

bool run = true;
int damage;
int renown = 0;
int gold = 0;
int money_sack = 0;
int money_limit = 64;

class npc{
    public:
    int age;
} xerothusian, yovshornn, xarvveron;
class enemy{
    public:
    int strength;
    int current_health;
};
class goblin: public enemy{
    public:
    int strength = 1;
    int max_health = 5;
    int current_health = 5;
} goblin;
class weapon{
    public:
};
class sword: public weapon{
    public:
        int slash = 2;
} katana;
class bbeg: public enemy{
    public:
        int power = 2;
        int health = 20;
        int attack = power + katana.slash;
} shorvyyn;
class player{
    public:
    int experience = 0;
    int level = 1;
    short mh = level*5;
    short *max_health = &mh;
    short ch = mh;
    short *current_health = &ch;
}human;
int deposit_gold(int){
    if (gold+money_sack > money_limit){
        money_sack = money_limit;
        printf("You can not deposit at this time.");
    } else{
        money_sack += gold;
    }
    return money_sack;
};
int take_damage(int){
    *human.current_health -= damage;
    if (*human.current_health <= 0){
        run = false;
    }
    printf("%d\n", *human.current_health);
    return *human.current_health;
};
int health;
void shorvyyn_encounter(int){
    while (*human.current_health > 0 && shorvyyn.health >0 ){
        printf("Shorvyyn's health is: %d\n", shorvyyn.health);
        if (shorvyyn.health <= 0){
            printf("Shorvyyn has died.");
            renown += 5;
            printf("renown: %d\n", renown);
        }
        *human.current_health -= shorvyyn.attack;
        take_damage(shorvyyn.attack);
        printf("%d\n", *human.current_health);
        if (*human.current_health <= 0){
            printf("You were not well enough prepared to battle Shorvyyn.\n");
            renown -= 1;
            printf("renown: %d\n", renown);
        }
    }
};
void goblin_encounter(int){
    while (*human.current_health > 0 && goblin.current_health > 0){
        goblin.current_health -= 1.5;
        printf("The goblin's health is: %d\n", goblin.current_health);
        if (goblin.current_health <= 0){
            printf("The goblin has been killed.\n");
            renown += 1;
            printf("renown: %d\n", renown);
        }
        *human.current_health -= 1;
        printf("Your current health is: %d\n", *human.current_health);
        if (*human.current_health <= 0){
            printf("You have been killed.");
            renown -= 5;
            printf("renown: %d\n", renown);
        }
    }
};
int main(void) {
    char name[20];
    bool name_con = true;
    while (name_con){
        printf("Enter your name: ");
        scanf("%s", name);
        printf("The name you entered is: %s\n", name);
        name_con = false;
    }
    while (run){
        printf("Battle time\n");
        goblin_encounter(*human.current_health);
        break;
    }
    return 0;
}