/* Author: Jonathan White (jcw0057)
 * File: project2_White_jcw0057.cpp
 * Compile project2_White_jcw0057.cpp and then run.
 * Used "murach's C++ programming" book and lectures for help; Also used project hints for press any key implementation
 */

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <iomanip>

using namespace std;

// Global Variables
int a_wins = 0;
int b_wins = 0;
int c_wins = 0;


bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive);
/* Params: A_alive -> Aaron is alive or not
 *         B_alive -> Bob is alive or not
 *         C_alive -> Charlie is alive or not
 *
 * Return: Changes B_alive to false if Bob is killed.
 *         Changes C_alive to false if Charlie is killed.
 */

 void Aaron_shoots1(bool& B_alive, bool& C_alive);

 void Bob_shoots(bool& A_alive, bool& C_alive);

 void Charlie_shoots(bool& A_alive, bool& B_alive);

 void Aaron_shoots2(bool& B_alive, bool& C_alive);

 void strategy1(void);
 void strategy2(void);

 /**** TEST PROTOTYPES ****/
 // Test Drivers for methods
 void test_atleast_two_alive(void);

 void test_Aaron_shoots1(void);

 void test_Bob_shoots(void);

 void test_Charlie_shoots(void);

 void test_Aaron_shoots2(void);

 int main() {
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    const int NUM_OF_DUELS = 10000;
    srand(time(0));
    cout << "*** Welcome to Jonathan's Duel Simulator ***\n";

    // Tests
    test_atleast_two_alive();
    cout << "Press any key to continue...";
    cin.ignore().get();

    test_Aaron_shoots1();
    cout << "Press any key to continue...";
    cin.ignore().get();

    test_Bob_shoots();
    cout << "Press any key to continue...";
    cin.ignore().get();

    test_Charlie_shoots();
    cout << "Press any key to continue...";
    cin.ignore().get();

    test_Aaron_shoots2();
    cout << "Press any key to continue...";
    cin.ignore().get();

    // 1000 duels for strategy1
    cout << "Ready to test Strategy 1 (10000 duels):\n";
    cout << "Press any key to continue...";
    cin.ignore().get();
    cout << "...\n...\n...\n";
    int duels = 0;
    while (duels < NUM_OF_DUELS) {
        strategy1();
        duels++;
    }

    // Calculating percentages
    double a_perc = (double) a_wins / (double) NUM_OF_DUELS;
    double b_perc = (double) b_wins / (double) NUM_OF_DUELS;
    double c_perc = (double) c_wins / (double) NUM_OF_DUELS;

    // Assigning wins to compare to strategy 2
    int a_wins_strategy1 = a_wins;
    cout << "Aaron won " << a_wins << "/" << NUM_OF_DUELS << " duels or " << setprecision(2) << a_perc * 100 << "%\n";
    cout << "Bob won " << b_wins << "/" << NUM_OF_DUELS << " duels or " << setprecision(2) << b_perc * 100 << "%\n";
    cout << "Charlie won " << c_wins << "/" << NUM_OF_DUELS << " duels or " << setprecision(2) << c_perc * 100 << "%\n\n";

    // 1000 duels for strategy2
    cout << "Ready to test Strategy 1 (10000 duels):\n";
    cout << "Press any key to continue...";
    cin.ignore().get();
    cout << "...\n...\n...\n";
    // Reset var values
    duels = 0;
    a_wins = 0;
    b_wins = 0;
    c_wins = 0;

    while (duels < NUM_OF_DUELS) {
        strategy2();
        duels++;
    }

    a_perc = (double) a_wins / (double) NUM_OF_DUELS;
    b_perc = (double) b_wins / (double) NUM_OF_DUELS;
    c_perc = (double) c_wins / (double) NUM_OF_DUELS;

    //Output
    cout << "Aaron won " << a_wins << "/" << NUM_OF_DUELS << " duels or " << setprecision(2) << a_perc * 100 << "%\n";
    cout << "Bob won " << b_wins << "/" << NUM_OF_DUELS << " duels or " << setprecision(2) << b_perc * 100 << "%\n";
    cout << "Charlie won " << c_wins << "/" << NUM_OF_DUELS << " duels or " << setprecision(2) << c_perc * 100 << "%\n\n";

    if (a_wins > a_wins_strategy1) {
        cout << "Strategy 2 is better than strategy 1\n";
    } else if (a_wins < a_wins_strategy1) {
        cout << "Strategy 1 is better than strategy 2\n";
    } else {
        cout << "The strategies have the same outcome\n";
    }
 }

 /* Implementations */
 bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive) {
    if(A_alive) {
        if (B_alive || C_alive) {
            return true;
        }
    } else if (B_alive) {
        if (C_alive) {
            return true;
        }
    } else {
        return false;
    }
 }

 void Aaron_shoots1(bool& B_alive, bool& C_alive) {
    const int A_PROBABILITY = 33;
    int target_result;
    target_result = rand()%100;
    if(target_result <= 33) {
        if (C_alive) {
            C_alive = false;
        } else {
            B_alive = false;
        }
    }
 }

 void Bob_shoots(bool& A_alive, bool& C_alive) {
    const int B_PROBABILITY = 50;
    int target_result;
    target_result = rand()%100;
    if(target_result <= 50) {
        if (C_alive) {
            C_alive = false;
        } else {
            A_alive = false;
        }
    }
 }

 void Charlie_shoots(bool& A_alive, bool& B_alive) {
    if(B_alive) {
        B_alive = false;
    } else {
        A_alive = false;
    }
 }

 void Aaron_shoots2(bool& B_alive, bool& C_alive) {
    // Misses first shot -> Charlie never misses, so either B_alive or C_alive will be false -> if both true - miss
    const int A_PROBABILITY = 33;
    int target_result;
    if(!B_alive || !C_alive) {
        target_result = rand()%100;
        if(target_result <= 33) {
            if (C_alive) {
                C_alive = false;
            } else {
                B_alive = false;
            }
        }
    }
 }

 void strategy1(void) {
	bool a_alive = true;
	bool b_alive = true;
	bool c_alive = true;
	while (at_least_two_alive(a_alive, b_alive, c_alive)) {
		if (a_alive) {
			Aaron_shoots1(b_alive, c_alive);
		}
		if (b_alive) {
			Bob_shoots(a_alive, c_alive);
		}
		if (c_alive) {
			Charlie_shoots(a_alive, b_alive);
		}
	}
	//Only one alive after loop, whoever alive is winner.
	if (a_alive) {
		a_wins++;
	}
	else if (b_alive) {
		b_wins++;
	}
	else {
		c_wins++;
	}
}

 // Implementing Strategy 2
 void strategy2(void) {
    bool A_alive = true;
    bool B_alive = true;
    bool C_alive = true;
    while(at_least_two_alive(A_alive, B_alive, C_alive)) {
        if (A_alive) {
            Aaron_shoots2(B_alive, C_alive);
        } if (B_alive) {
            Bob_shoots(A_alive, C_alive);
        } if (C_alive) {
            Charlie_shoots(A_alive, B_alive);
        }
    }

    // Declare winner
    if(A_alive) {
        a_wins++;
    } else if(B_alive) {
        b_wins++;
    } else {
        c_wins++;
    }

 }

 /* Implementation test for at_least_two_alive() */
void test_atleast_two_alive(void) {
	cout << "Unit Testing 1: Function - at_least_two_alive()\n";

	cout<< "\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
	assert(true == at_least_two_alive(true, true, true));
	cout << "\tCase passed...\n";

	cout<< "\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
	assert(true == at_least_two_alive(false, true, true));
	cout << "\tCase passed...\n";

	cout<< "\tCase 3: Aaron alive, Bob dead, Charlie alive\n";
	assert(true == at_least_two_alive(true, false, true));
	cout << "\tCase passed...\n";

	cout<< "\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
	assert(true == at_least_two_alive(true, true, false));
	cout << "\tCase passed...\n";

	cout<< "\tCase 5: Aaron dead, Bob dead, Charlie alive\n";
	assert(false == at_least_two_alive(false, false, true));
	cout << "\tCase passed...\n";

	cout<< "\tCase 6: Aaron dead, Bob alive, Charlie dead\n";
	assert(false == at_least_two_alive(false, true, false));
	cout << "\tCase passed...\n";

	cout<< "\tCase 7: Aaron alive, Bob dead, Charlie dead\n";
	assert(false == at_least_two_alive(true, false, false));
	cout << "\tCase passed...\n";

	cout<< "\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
	assert(false == at_least_two_alive(false, false, false));
	cout << "\tCase passed...\n";
}

/* Implementation test for Aaron_shoots1() */
void test_Aaron_shoots1(void) {
	cout << "Unit Test 2: Function Aaron_shoots1(Bob_alive, Charlie_alive)\n";
	bool bob_alive;
	bool charlie_alive;

	cout << "\tCase 1: Bob alive, Charlie alive\n";
	cout << "\t\tAaron is shooting at Charlie\n";
	bob_alive = true;
	charlie_alive = true;
	Aaron_shoots1(bob_alive, charlie_alive);


	assert(true == bob_alive);
	if (charlie_alive) {
		cout << "\t\tAaron misses.\n";
	}
	else {
		cout << "\t\tCharlie is dead.\n";
	}

	cout << "\tCase 2: Bob dead, Charlie alive\n";
	cout << "\t\tAaron is shooting at Charlie\n";
	bob_alive = false;
	charlie_alive = true;
	Aaron_shoots1(bob_alive, charlie_alive);

	assert(false == bob_alive);
	if (charlie_alive) {
		cout << "\t\tAaron misses.\n";
	}
	else {
		cout << "\t\tCharlie is dead.\n";
	}

	cout << "\tCase 3: Bob alive, Charlie dead\n";
	cout << "\t\tAaron is shooting at Bob\n";
	bob_alive = true;
	charlie_alive = false;
	Aaron_shoots1(bob_alive, charlie_alive);


	assert(false == charlie_alive);
	if (bob_alive) {
		cout << "\t\tAaron misses.\n";
	}
	else {
		cout << "\t\tBob is dead.\n";
	}

}

/* Implementation test for Bob_shoots() */
void test_Bob_shoots(void) {
	cout << "Unit Testing 3: Function Bob_shoots(Aaron_alive, Charlie_alive)\n";
	bool a_alive;
	bool c_alive;

	cout << "\tCase 1: Aaron alive, Charlie alive\n";
	cout << "\t\tBob is shooting at Charlie\n";
	a_alive = true;
	c_alive - true;
	Bob_shoots(a_alive, c_alive);

	assert(true == a_alive);
	if (c_alive) {
		cout << "\t\tBob missed\n";
	}
	else {
		cout << "\t\tCharlie is dead.\n";
	}

	cout << "\tCase 2: Aaron dead, Charlie alive\n";
	cout << "\t\tBob is shooting at Charlie\n";
	a_alive = false;
	c_alive = true;
	Bob_shoots(a_alive, c_alive);

	if (c_alive) {
		cout << "\t\tBob missed\n";
	}
	else {
		cout << "\t\tCharlie is dead.\n";
	}

	cout << "\tCase 3: Aaron alive, Charlie dead\n";
	cout << "\t\tBob is shooting at Charlie\n";
	a_alive = true;
	c_alive = false;
	Bob_shoots(a_alive, c_alive);

	assert(false == c_alive);
	if (a_alive) {
		cout << "\t\tBob missed\n";
	}
	else {
		cout << "\t\tAaron is dead.\n";
	}
}

/* Implementation test for Charlie_shoots() */
void test_Charlie_shoots(void) {
	cout << "Unit Testing 4: Function Charlie_shoots(Aaron_alive, Bob_alive)\n";
	bool a_alive;
	bool b_alive;

	cout << "\tCase 1: Aaron alive, Bob alive\n";
	cout << "\t\tCharlie is shooting at Bob\n";
	a_alive = true;
	b_alive = true;
	Charlie_shoots(a_alive, b_alive);

	assert(true == a_alive);

	assert(false == b_alive);
	cout << "\t\tBob is dead.\n";

	cout << "\tCase 2: Aaron dead, Bob alive\n";
	cout << "\t\tCharlie is shooting at Bob\n";
	a_alive = false;
	b_alive = true;
	Charlie_shoots(a_alive, b_alive);

	assert(false == a_alive);

	assert(false == b_alive);
	cout << "\t\tBob is dead.\n";

	cout << "\tCase 3: Aaron alive, Bob dead\n";
	cout << "\t\tCharlie is shooting at Aaron\n";
	a_alive = true;
	b_alive = false;
	Charlie_shoots(a_alive, b_alive);

	assert(false == b_alive);

	assert(false == a_alive);
	cout << "\t\tAaron is dead.\n";
}

/* Implementation test for Aaron_shoots2() */
void test_Aaron_shoots2(void) {
	cout << "Unit Testing 5: Function Aaron_shoots2(Bob_alive, Charlie_alive)\n";
	bool b_alive;
	bool c_alive;

	cout << "\tCase 1: Bob alive, Charlie alive\n";
	cout << "\t\tAaron intentionally misses his first shot\n";
	b_alive = true;
	c_alive = true;
	Aaron_shoots2(b_alive, c_alive);
	assert(true == b_alive);
	assert(true == c_alive);
	cout << "\t\tBoth Bob and Charlie are alive\n";

	cout << "\tCase 2: Bob dead, Charlie alive\n";
	cout << "\t\tAaron is shooting at Charlie\n";
	b_alive = false;
	c_alive = true;
	Aaron_shoots2(b_alive, c_alive);

	assert(false == b_alive);
	if (c_alive) {
		cout << "\t\tAaron misses\n";
	}
	else {
		cout << "\t\tCharlie is dead\n";
	}

	cout << "\tCase 3: Bob alive, Charlie dead\n";
	cout << "\t\tAaron is shooting at Bob\n";
	b_alive = true;
	c_alive = false;
	Aaron_shoots2(b_alive, c_alive);

	assert(false == c_alive);
	if (b_alive) {
		cout << "\t\tAaron misses\n";
	}
	else {
		cout << "\t\tBob is dead\n";
	}
}
