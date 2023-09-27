#include <iostream>
#include <stdlib.h>
#include <cassert>
#include <ctime>
using namespace std;
/**
 * Rosalyn Navarrete
 * rdn0011
 * project_2.cpp
 * g++ project_2.cpp
 * ./a.out (to run)
 * press enter many times to see output
 */

// constants for shoot percent of aaron, bob
const static int runs = 10000;
const static int a_chance = 33;
const static int b_chance = 50;


// variables to be used during the main
int aaron_wins, bob_wins ,charlie_wins, aaron_wins_2,bob_wins_2,charlie_wins_2;
double aaron_wins_percent, bob_wins_percent, charlie_wins_percent, aaron_wins_percent_2, bob_wins_percent_2, charlie_wins_percent_2;
int better_strategy, worse_strategy;

//sets the chance of the players shot in th rand function
int chance;

// sets the players as alive
bool A_alive = true;
bool B_alive = true;
bool C_alive = true;

// flags for if the player is being shot at
bool is_shooting_a = false;
bool is_shooting_b = false;
bool is_shooting_c = false;

// flag to ensure one shot per player
bool shot_flag = false;



//pause command for Linux Terminal
void press_to_continue(){
    cout << "Press any key to continue... ";
    cin.ignore().get();
}

// function that clears each of the flags
void clear_flags(){
     is_shooting_a = false;
     is_shooting_b = false;
     is_shooting_c = false;
     shot_flag = false;
}

// function of case when two are alive
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive){
    if(A_alive && B_alive || A_alive && C_alive || B_alive && C_alive){
        return true;
    }
    return false;
}

// uses Call-By_references strat 1
void Aaron_shoots1(bool& B_alive, bool& C_alive){
    // clears the flags and sets the accuracy
clear_flags();
chance = rand()%100;
    // if C is alive and Aaron hasn't shot yet Aaron will attempt to shoot him
    if(C_alive){
        is_shooting_c = true;
        if(chance <= a_chance){
            C_alive = false;
            shot_flag = true;
        }
    }
    // if B is alive and Aaron hasn't shot yet Aaron will attempt to shoot him
    else if(B_alive){
        is_shooting_b = true;
        if(chance <= a_chance ){
            B_alive = false;
            shot_flag = true;
        }
    }

}

//Bob shoots function
void Bob_shoots(bool& A_alive, bool& C_alive) {
    // clears the flags and sets the accuracy
    clear_flags();
    chance = rand() % 100;
    // if C is alive and B hasn't shot then he will try to shoot C
    if(C_alive){
        is_shooting_c = true;
        if(chance <= b_chance){
            C_alive = false;
            shot_flag = true;
        }
    }
    // if A is alive and B hasn't shot then he will try to shoot A
    else if(A_alive){
        is_shooting_a = true;
        if(chance <= b_chance){
            A_alive = false;
            shot_flag = true;
        }
    }
}

// Function of charlie shooting
void Charlie_shoots(bool& A_alive, bool& B_alive){
    // no rand needed due to Charlie's accuracy
    clear_flags();
    // if B is alive and C hasn't shot then he will shoot B
    if(B_alive){
        is_shooting_b = true;
        B_alive = false;
        shot_flag = true;
    }
    // if A is alive and C hasn't shot then he will shoot A
     else if(A_alive){
        is_shooting_a = true;
        A_alive = false;
        shot_flag = true;
    }
}

// Aaron shoots 2 (Strategy 2)
void Aaron_shoots2(bool& B_alive, bool& C_alive) {
    clear_flags();
    chance = rand() % 100;
    // the rest similar to aaron_shoots_1
    // Aaron doesn't shoot first round
    if(B_alive && C_alive){
        is_shooting_b = false;
        is_shooting_c = false;
    }
    else if (C_alive && !B_alive) {
        is_shooting_c = true;
        if (chance <= a_chance) {
            C_alive = false;
            shot_flag = true;
        }
    }
     else if(B_alive && !C_alive) {
        is_shooting_b = true;
        if (chance <= a_chance) {
            B_alive = false;
            shot_flag = true;
        }
    }
}


// Duel using Strategy one
void duel_1(bool& A_alive,bool& B_alive, bool& C_alive) {
//while each still alive they will be shot at
    while (at_least_two_alive(A_alive, B_alive, C_alive)) {
        if (A_alive && at_least_two_alive(A_alive, B_alive, C_alive)) {
            Aaron_shoots1(B_alive, C_alive);
        }
        if (B_alive && at_least_two_alive(A_alive, B_alive, C_alive)) {
            Bob_shoots(A_alive, C_alive);
        }
        if (C_alive && at_least_two_alive(A_alive, B_alive, C_alive)) {
            Charlie_shoots(B_alive, A_alive);
        }
    }
    // whoever still living will be given a win
    if (A_alive) {
        aaron_wins++;
    }
    if (B_alive) {
        bob_wins++;
    }
    if (C_alive) {
        charlie_wins++;
    }
}

void duel_2(bool& A_alive,bool& B_alive, bool& C_alive) {
//while each still alive they will be shot at
    while (at_least_two_alive(A_alive, B_alive, C_alive)) {
        if (A_alive) {
            Aaron_shoots2(B_alive, C_alive);
        }
        if (B_alive) {
            Bob_shoots(A_alive, C_alive);
        }
        if (C_alive) {
            Charlie_shoots(B_alive, A_alive);
        }
    }
    // whoever still living will be given a win
    if (A_alive) {
        aaron_wins_2++;
    }
    if (B_alive) {
        bob_wins_2++;
    }
    if (C_alive) {
        charlie_wins_2++;
    }
}

//TEST VOIDS FOR 5 main fuctions
void test_at_least_two_alive(void);
void test_Aaron_shoots1(void);
void test_Bob_shoots(void);
void test_Charlie_shoots(void);
void test_Aaron_shoots2(void);

int main() {

    //random generator
    srand(time(0));
    cout << "***Welcome to Ro_main_Lettuce's Duel Simulator***" << endl;
    // tests the at_least_two_alive
    test_at_least_two_alive();
    press_to_continue();

    // tests Aaron_shoots_1
    test_Aaron_shoots1();
    press_to_continue();

    //tests Bob_shoots
    test_Bob_shoots();
    press_to_continue();

    //tests Charlie_shoots
    test_Charlie_shoots();
    press_to_continue();

    //tests Aaron_shoots_2
    test_Aaron_shoots2();
    press_to_continue();

    //Simulating duel 1
    cout<< "\nReady to test strategy 1 (run 10000 times):\n";
    press_to_continue();
    for(int i = 0; i < runs; i++){
        A_alive = true;
        B_alive = true;
        C_alive = true;
        duel_1(A_alive, B_alive, C_alive);
    }

    // duel one output values determined
    aaron_wins_percent = double(aaron_wins)/100;
    bob_wins_percent  = double(bob_wins)/100;
    charlie_wins_percent = double(charlie_wins)/100;
    cout << "\nAaron won " << aaron_wins<< "/10000" <<" duels or " << aaron_wins_percent << "%";
    cout << "\nBob won " << bob_wins << "/10000" <<" duels or " << bob_wins_percent << "%";
    cout << "\nCharlie won " << charlie_wins << "/10000" <<" duels or " << charlie_wins_percent << "%\n";

    //Simulating duel with Strategy 2
    cout<< "\nReady to test strategy 2 (run 10000 times):\n";
    press_to_continue();
    for(int i = 0; i < runs; i++){
        A_alive = true;
        B_alive = true;
        C_alive = true;
        duel_2(A_alive, B_alive, C_alive);
    }


    //output for duel 2
    aaron_wins_percent_2 = double(aaron_wins_2)/100;
    bob_wins_percent_2  = double(bob_wins_2)/100;
    charlie_wins_percent_2 = double(charlie_wins_2)/100;
    cout << "\nAaron won " << aaron_wins_2 << "/10000" <<" duels or " << aaron_wins_percent_2 << "%";
    cout << "\nBob won " << bob_wins_2 << "/10000"<<" duels or " << bob_wins_percent_2 << "%";
    cout << "\nCharlie won " << charlie_wins_2<< "/10000" << " duels or " << charlie_wins_percent_2 << "%\n";

// determines the worse strategy by comparing aaron2wins to arron1wins
if(aaron_wins > aaron_wins_2) {
    better_strategy = 1;
    worse_strategy = 2;
}
    else {
    better_strategy = 2;
    worse_strategy = 1;
}

    //Outputs better strategy
    cout << "\nStrategy " << better_strategy << " is better than strategy " << worse_strategy;


    return 0;
}

// test drivers for FUNCTIONS
//Test driver for at least two alive
// My shoot tests assert and see if the correct player is being shot at
void test_at_least_two_alive(void) {
    cout << "Unit Testing 1: Function - at_least_two_alive()\n";
    //case 1
    cout << "\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
    assert(at_least_two_alive(true, true, true));
    cout << "\tCase passed ...\n";

    //case 2
    cout << "\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
    assert(at_least_two_alive(false, true, true));
    cout << "\tCase passed ...\n";

    //case 3
    cout << "\tCase 3: Aaron alive, Bob dead, Charlie alive\n";
    assert(at_least_two_alive(true, false, true));
    cout << "\tCase passed ...\n";

    //case 4
    cout << "\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
    assert(at_least_two_alive(true, true, false));
    cout << "\tCase passed ...\n";

    //case 5
    cout << "\tCase 5: Aaron dead, Bob dead, Charlie alive\n";
    assert(!at_least_two_alive(false, false, true));
    cout << "\tCase passed ...\n";

    //case 6
    cout << "\tCase 6: Aaron dead, Bob alive, Charlie dead\n";
    assert(!at_least_two_alive(false, true, false));
    cout << "\tCase passed ...\n";

    //case 7
    cout << "\tCase 7: Aaron alive, Bob dead, Charlie dead\n";
    assert(!at_least_two_alive(true, false, false));
    cout << "\tCase passed ...\n";

    //case 8
    cout << "\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
    assert(!at_least_two_alive(false, false, false));
    cout << "\tCase passed ...\n";
}

//Test driver for Aaron shoots (strat 1)
void test_Aaron_shoots1(void) {
    cout << "\nUnit Testing 2: Function Aaron_shoots1(Bob_alive,Charlie_alive)\n";
    // case 1
    cout << "\tCase 1: Bob alive, Charlie alive\n";
    B_alive = true;
    C_alive = true;
    Aaron_shoots1(B_alive, C_alive);
    assert(is_shooting_c);
    cout << "\t\tAaron is shooting at Charlie\n";

    //case2
    cout << "\tCase 2: Bob dead, Charlie alive\n";
    B_alive = false;
    C_alive = true;
    Aaron_shoots1(B_alive , C_alive);
    assert(is_shooting_c);
    cout << "\t\tAaron is shooting at Charlie\n";

    //case 3
    cout << "\tCase 3: Bob alive, Charlie dead\n";
    B_alive = true;
    C_alive = false;
    Aaron_shoots1(B_alive , C_alive);
    assert(is_shooting_b);
    cout << "\t\tAaron is shooting at Bob\n";
}

//Test driver for Bob shooting
void test_Bob_shoots(void){
    cout << "\nUnit Testing 3: Function Bob_shoots1(Aaron_alive,Charlie_alive)\n";

    //case1
    cout << "\tCase 1: Aaron alive, Charlie alive\n";
    A_alive = true;
    C_alive = true;
    Bob_shoots(A_alive, C_alive);
    assert(is_shooting_c);
    cout << "\t\tBob is shooting at Charlie\n";

    //case 2
    cout << "\tCase 2: Aaron dead, Charlie alive\n";
    A_alive = false;
    C_alive = true;
    Bob_shoots(A_alive, C_alive);
    assert(is_shooting_c);
    cout << "\t\tBob is shooting at Charlie\n";

    //case 3
    cout << "\tCase 3: Aaron alive, Charlie dead\n";
    A_alive = true;
    C_alive = false;
    Bob_shoots(A_alive, C_alive);
    assert(is_shooting_a);
    cout << "\t\tBob is shooting at Aaron\n";
}

//Test driver for Charlie shooting
void test_Charlie_shoots(void) {
    cout << "\nUnit Testing 4: Function Charlie_shoots(Aaron_alive,Bob_alive)\n";
    //case 1
    cout << "\tCase 1: Aaron alive, Bob alive\n";
    A_alive = true;
    B_alive = true;
    Charlie_shoots(A_alive, B_alive);
    assert(is_shooting_b);
    assert(!is_shooting_a);
    cout << "\t\tCharlie is shooting at Bob\n";

    //case 2
    cout << "\tCase 2: Aaron dead, Bob alive\n";
    A_alive = false;
    B_alive = true;
    Charlie_shoots(A_alive, B_alive);
    assert(is_shooting_b);
    cout << "\t\tCharlie is shooting at Bob\n";

    //case3
    cout << "\tCase 3: Aaron alive, Bob dead\n";
    A_alive = true;
    B_alive = false;
    Charlie_shoots(A_alive, B_alive);
    assert(is_shooting_a);
    cout<< "\t\tCharlie is shooting at Aaron\n";
}

//Test driver for Aaron shooting (Strategy 2)
void test_Aaron_shoots2(void){
    cout << "\nUnit Testing 5: Function Aaron_shoots2(Bob_alive,Charlie_alive)\n";
    //case 1
    cout << "\tCase 1: Bob alive, Charlie alive\n";
    cout << "\t\tAaron intentionally misses his first shot\n";
    cout << "\t\tBoth Bob and Charlie are alive.\n";
    B_alive = true;
    C_alive = true;
    Aaron_shoots2(B_alive, C_alive);
    assert(!is_shooting_b);
    assert(!is_shooting_c);
    //case 2
    cout << "\tCase 2: Bob dead, Charlie alive\n";
    B_alive = false;
    C_alive = true;
    Aaron_shoots2(B_alive, C_alive);
    assert(is_shooting_c);
    cout << "\t\tAaron is shooting at Charlie\n";

    //case3
    cout << "\tCase 3: Bob alive, Charlie dead\n";
    B_alive = true;
    C_alive = false;
    Aaron_shoots2(B_alive, C_alive);
    assert(is_shooting_b);
    cout<< "\t\tAaron is shooting at Bob\n";
}

