#include <stdio.h>

bool run = true;
int damage;
int renown = 0;
int gold = 0;
int money_sack = 0;
int money_limit = 64;
char inventory[20][20];

class Inventory{
    private:
    int itemNumber;
    int quantity;
    double cost;
    double totalCost;
    public:
    Inventory(){
        itemNumber = 0;
        quantity = 0;
        cost = 0;
        totalCost = 0;
    }
    Inventory(int newItemNumber, int newQuantity, double newCost){
        itemNumber = newItemNumber;
        quantity = newQuantity;
        cost = newCost;
        setTotalCost(quantity, cost);
    }/*
    void setItemNumber(int){
        itemNumber = itemNumber;
    }
    void setQuantity(int){
        quantity = quantity;
    }
    void setCost(double){
        cost = cost;
    }*/
    int getItemNumber(){
        return itemNumber;
    }
    int getQuantity(){
        return quantity;
    }
    double getCost(){
        return cost;
    }
    double getTotalCost(){
        return totalCost;
    }
    void setTotalCost(int, double){
        totalCost = quantity * cost;
    }
};
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
        take_damage(damage = shorvyyn.attack);
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
        take_damage(damage = 1);
        printf("Your current health is: %d\n", *human.current_health);
        if (*human.current_health <= 0){
            printf("You have been killed.\n");
            renown -= 5;
            printf("renown: %d\n", renown);
        }
    }
};
class treasure{
    public:
    int price;
    int value;
} ruby, emerald, saphire, onyx_sculpture, crucifix;
class key_relic{
    public:
} olive_branch, blood_of_lamb, nail, wood;
void sell(int value, char item){
    inventory[10][10] -= item;
    deposit_gold(value);
}
int main(){
    int itemNumber;
    int quantity;
    double cost;
    double totalCost;
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
        shorvyyn_encounter(*human.current_health);
        break;
    }
    Inventory();
    {
        itemNumber = 0;
        quantity = 0;
        cost = 0;
        totalCost = 0;
    }
    printf("\nEnter an item number. ");
    scanf("%d", &itemNumber);
    while (itemNumber < 0){
        printf("Please enter a positive integer value.");
        scanf("%d", &itemNumber);
    }
    printf("\nEnter a quantity. ");
    scanf("%d", &quantity);
    while (quantity < 0){
        printf("Please enter a positive integer value.");
        scanf("%d", &quantity);
    }
    printf("\nEnter a cost. ");
    scanf("%lf", &cost);
    while (cost < 0){
        printf("Please enter a positive value, with no further precision than the hundredths place. ");
        scanf("%lf", &cost);
    }
    Inventory information(itemNumber, quantity, cost);
    totalCost = information.getTotalCost();
    itemNumber = information.getItemNumber();
    quantity = information.getQuantity();
    cost = information.getCost();
    printf("\nItem number: %d\n", itemNumber);
    printf("Item quantity: %d\n", quantity);
    printf("Item cost: %lf\n", cost);
    printf("---------------------------\n");
    printf("Total cost: %lf\n", totalCost);    
    return 0;
}