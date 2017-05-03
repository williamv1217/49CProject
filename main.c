//
//  main.c
//  49CProject
//
//  Created by Casper Juul Lindinger, Jamahl Reynolds, Philip West Christiansen, William Vagharfard
//
//

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

struct enemy {
    char *type;
    int attackPower;
    int health;
    int coins;
};

struct player {
    char *name;
    char *type;
    int attackPower;
    int health;
    int coins;
    int potions;
};

typedef struct player * Player;
typedef struct enemy * Enemy;
int potionPower = 30;

void playerType(Player p, int type);
void shop(Player p);
void showStats(Player p);
void playerAttack(Player p, Enemy e);
void enemyAttack(Player p, Enemy e);
void battle(Player p, Enemy e);
void roomType(Enemy e, int x);

int main(void) {
    struct player p1;
    struct enemy e1;
    Player p1ptr = &p1;
    Enemy e1ptr = &e1;
    char arr[80];
    srand((unsigned int) time(NULL));
    int chartype = 0;
    int exit =  1;
    
    //creating the initial values for the player
    p1.attackPower = 20;
    p1.health = 100;
    p1.coins = 150;
    p1.potions = 1;
    
    e1.attackPower = 20;

    
    printf("Welcome to Nameless Village traveler...");
    
    printf("What is your name?: ");
    scanf("%s", arr);
    p1.name = arr;
    printf("\nHello, %s\n", p1.name);
    
    puts("What kind of character are you?\n");
    puts("1. Wizard \t(higher attack, lower defense)\n2. Fighter \t(same attack and defense)\n3. Knight \t(lower attack, higher defense)");
    
    scanf("%d", &chartype);
    playerType(p1ptr, chartype);
    
    printf("\nHello there %s! \n", p1.type);
    while (exit > 0){
        puts("What will you like to do? (enter a number)\n");
        puts("0. Go to sleep, Goodbye!");
        puts("1. Enter the dungeon");
        puts("2. Go shopping");
        puts("3. See my stats");
        scanf("%d", &exit);
        switch (exit) {
            case 1 :
                e1.health = 100;
                roomType(e1ptr, rand() % 2 + 1);
                battle(p1ptr, e1ptr);
                break;
            case 2 :
                shop(p1ptr);
                break;
            case 3 :
                showStats(p1ptr);
                break;
        }
    }

    return 0;
}

void playerType(Player p, int type) {
    switch(type) {
        case 1 :
            p -> type = "Wizard";
            p -> attackPower *= 1.20;
            p -> health *= 0.80;
            break;
        case 2 :
            p -> type = "Fighter";
            break;
        case 3 :
            p -> type = "Knight";
            p -> attackPower *= 0.80;
            p -> health *= 1.20;
            break;
    }
}

void roomType(Enemy e, int x) {
    switch(x) {
        case 1 :
            e -> type = "Thief";
            e -> attackPower *= 0.80;
            e -> health *= 1.20;
            e -> coins = 100;
            break;
        case 2 :
            e -> type = "Sorcerer";
            e -> attackPower *= 1.10;
            e -> health *= 0.80;
            e -> coins = 100;
            break;
//        case 3 :
//            e -> type = "Dragon";
//            e -> attackPower *= 1.20;
//            e -> coins = 250;
//        case 4 :
//            e -> type = "Treasure Chest";
//            e -> coins = 50;

    }
}

void showStats(Player p) {
    printf("\nAttack Power: %d\n", p -> attackPower);
    printf("Health: %d\n", p -> health);
    printf("Potions: %d\n", p -> potions);
    printf("Coins: %d\n\n", p -> coins);
}

void shop(Player p) {
    int leaveShop = 1;
    puts("\nWelcome to the shop!");
    puts("What can I get for you today?\n");
    while(leaveShop > 0){
        puts("0. Nevermind, I'm leaving");
        puts("1. Weapon       (100 coins)");
        puts("2. Armor        (100 coins)");
        puts("3. Heal Potion  (40 coins)");
        scanf("%d", &leaveShop);
        
        switch(leaveShop) {
            case 1 :
                if (p -> coins >= 100) {
                    p -> attackPower *= 1.15; //increase attack by 15%
                    p -> coins -= 100; //reduce coins by 100
                    printf("\nYou have %d coins left\n", p -> coins);
                } else {
                    puts("\nSorry, you don't have enough coins to purchase a new weapon");
                }
                break;
            case 2 :
                if (p -> coins >= 100) {
                    p -> health *= 1.15; //increase defense by 15%
                    p -> coins -= 100; //reduce coins by 100
                    printf("\nYou have %d coins left\n", p -> coins);
                } else {
                    puts("\nSorry, you don't have enough coins to purchase new armor");
                }
                break;
            case 3 :
                if (p -> coins >= 40) {
                    p -> potions++; //increase number of potions by one
                    p -> coins -= 40; //reduce coins by 40
                    printf("\nYou have %d coins left\n", p -> coins);
                } else {
                    puts("\nSorry, you don't have enough coins to purchase a healing potion");
                }
                break;
        }
        if (leaveShop != 0) {
            printf("Would you like anything else, %s?\n\n", p -> name);
        }
    }
    printf("Thank you %s!\n\n", p -> name);
}

void playerAttack(Player p, Enemy e) {
    int r = 1 + rand() % 100;
    if (r <= 65) {
        e -> health -= p -> attackPower;
        if (e -> health > 0) {
            
            printf("You attacked %s for %d power. %s now has %d health left!\n", e -> type, p -> attackPower, e -> type, e -> health);
        } else {
            e -> health = 0;
            printf("You attacked %s for %d power. %s now has died!!!\n", e -> type, p -> attackPower, e -> type);
        }
    } else {
        puts("Your attack missed!");
    }
}

void enemyAttack(Player p, Enemy e) {
    int r = 1 + rand() % 100;
    if (r <= 65) {
        p -> health -= e -> attackPower;
        if (p -> health > 0) {
            printf("%s attacked you for %d power. You now have %d health left!\n", e -> type, e -> attackPower, p -> health);
        } else {
            p -> health = 0;
            printf("%s attacked you for %d power. You have died!!!\n", e -> type, e -> attackPower);
        }
    } else {
        printf("%s's attack missed!\n", e -> type);
    }
}

void battle(Player p, Enemy e) {
    int leaveBattle = 1;
    printf("You see a %s in the room!\n", e -> type);
    
    if (strcmp(e -> type, "Treasure Chest") == 0) {
        p -> coins += e -> coins;
        printf("You have gained %d coins!\n", e -> coins);
        
    } else {
        while(leaveBattle > 0){
            puts("\nWhat will you do?");
            puts("0. Tactical Retreat");
            puts("1. Attack with weapon");
            puts("2. Heal");
            puts("3. See my stats");
            scanf("%d", &leaveBattle);
            
            switch(leaveBattle) {
                case 0 :
                    break;
                case 1 :
                    puts("--------------------------------------------------------");
                    if (p -> health > 0) {
                        playerAttack(p, e);
                        if (e -> health == 0) {
                            p -> coins += e -> coins;
                            printf("You gained %d coins from killing the %s\n", e -> coins, e -> type);
                            leaveBattle = 0;
                        }
                    }
                    if (e -> health > 0){
                        enemyAttack(p, e);
                        if (p -> health == 0) {
                            leaveBattle = 0;
                        }
                    }
                    puts("--------------------------------------------------------");
                    break;
                case 2 :
                    puts("--------------------------------------------------------");
                    if (p -> potions > 0) {
                        p -> potions--;
                        p -> health += potionPower;
                        printf("You increased your health by %d points, you have %d potions left\n", potionPower, p -> potions);
                        enemyAttack(p, e);
                    } else {
                        printf("You have no potions left!\n");
                    }
                    puts("--------------------------------------------------------");
                    break;
                case 3 :
                    showStats(p);
                    break;
            }
            
        }
    }
}
