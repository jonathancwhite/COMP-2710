/** project4_White_jcw0057.cpp
 * Jonathan White
 * JCW0057
 * Compile with g++ and run
 **/
#include <iostream>
#include <string>
#include <stdlib.h>
#include <assert.h>
#include <algorithm>
using namespace std;

//Creating linked list that holds a trivia question, answer, and point amount.
struct trivia_list_item {
    string question;
    string answer;
    int point;
    trivia_list_item *next;
};

//quiz - three questions input into list
void question_list(trivia_list_item &node_one, trivia_list_item &n2, trivia_list_item &n3) {
    node_one.question = "How long was the longest war on record? (Hint: how many minutes)";
    node_one.answer = "38";
    node_one.point = 100;
    node_one.next = &n2;

    n2.question = "What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)";
    n2.answer = "Bank of Italy";
    n2.point = 50;
    n2.next = &n3;

    n3.question = "What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)?";
    n3.answer = "Wii Sports";
    n3.point = 20;
    n3.next = NULL;
}

void add_user_question(trivia_list_item *head) {
        string cont;
        do {
            trivia_list_item *next = new trivia_list_item;
            while (next->question == "") {
                cout << "Enter a question: ";
                getline(cin, next->question);
            }
            while (next->answer == "") {
                cout << "Enter the answer: ";
                getline(cin, next->answer);
            }
            cout << "Enter award points: ";
            cin >> next->point;
            while (cin.fail()) {
                // clear input 
                cin.clear();
                cin.ignore();
                cout << "Please enter an integer value." << endl;
                cin >> next->point;
            }
            // ignore whitespace
            cin.ignore();
            // new last node
            next->next = NULL;

            if (head->question == "") {
                *head = *next;
            }
            else {
                // Temporary pointer
                trivia_list_item *temp = head;
                while (temp->next != NULL){
                    temp = temp->next;
                }
                temp->next = next;
            }
            cout << "Continue? (Yes/No): ";
            getline(cin, cont);
            transform(cont.begin(), cont.end(), cont.begin(), ::tolower);
            while (cont != "yes" && cont != "no") {
                cout << "Please enter \"Yes\" or \"No\"" << endl;
                getline(cin, cont);
                transform(cont.begin(), cont.end(), cont.begin(), ::tolower);
            }
        } while (cont == "yes");
}

//check num of questions - friend helped me with this one
int number_of_questions(trivia_list_item *head) {
    int length = 0;
    trivia_list_item *current = head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

int ask_question(trivia_list_item *head, int num_ask) {

    int player_points = 0;

    if (head == NULL)
        return 0;
    if (num_ask < 1) {
        cout << "Warning - the number of trivia questions to be asked must be equal to or be larger than 1.";
    }
    else if (number_of_questions(head) < num_ask) {
        cout << "Warning - There is only " << number_of_questions(head) << " trivia questions in the list.";
    }
    else {
        string user_answer;

        trivia_list_item *current_pointer = head;
        for (int i = 0; i < num_ask; i++) {
            cout << "Question: " << current_pointer->question << endl;
            cout << "Type Your Answer: ";
            getline(cin, user_answer);
            if (user_answer.compare(current_pointer->answer) == 0) {
                cout << "Correct! You are awarded " << current_pointer->point << " points." << endl;
                player_points += current_pointer->point;
            }
            else {
                cout << "That answer is wrong. The correct answer is " << current_pointer->answer << endl;
            }
            current_pointer = current_pointer->next;
            cout << "\nYour total points: " << player_points << endl;
        }
    }
    return player_points;
}

//Test cases.
void Unit_Test() {
    cout << "*** This is a debugging version ***\n";

    int total_points = 0;
    trivia_list_item node_one, n2, n3;
    question_list(node_one, n2, n3);

    cout << "Unit Test Case 1; Ask no question. The program should give a warning message." << endl;
    ask_question(&node_one, 0);
    cout << "\nCase 1 Passed\n\n";

    cout << "Unit Test Case 2.1: Ask 1 question in the linked list. The tester enters an incorrect answer." << endl;
    total_points = ask_question(&node_one, 1);
    assert(total_points == 0);
    cout << "\nCase 2.1 Passed\n\n";

    cout << "Unit Test Case 2.2: Ask 1 question in the linked list. The tester enters a correct answer." << endl;
    total_points = ask_question(&node_one, 1);
    assert(total_points != 0);
    cout << "\nCase 2.2 Passed\n\n";

    cout << "Unit Test Case 3: Ask all the questions in the linked list." << endl;
    total_points = ask_question(&node_one, 3);
    assert(total_points != 0);
    cout << "\nCase 3 Passed\n\n";

    cout << "Unit Test Case 4: Ask 5 questions in the linked list" << endl;
    total_points = ask_question(&node_one, 5);
    assert(total_points == 0);
    cout << "\nCase 4 Passed\n\n";

    cout << "\n\n*** End of the Debugging Version ***" << endl;
}

#define UNIT_TESTING

int main() {

#ifdef UNIT_TESTING
    Unit_Test();
    return 0;

#else
    int total_points = 0;
    string input;
    int number_of_questions;
    trivia_list_item node_one, n2, n3;
    question_list(node_one, n2, n3);

    cout << "*** Welcome to Jonathan's trivia quiz game ***\n";

    cout << "Would you like to add a question? (Yes/No)" << endl;
    getline(cin,input);

    if(input == "Yes" || "yes"){
         add_user_question(&node_one);
    }

    //This is the start of the Trivia quiz game.
    cout << "How many questions would you like to answer? " << endl;
    cin >> number_of_questions;
    cin.ignore();
    ask_question(&node_one, number_of_questions);
    cout << "\n*** Thank you for playing the trivia quiz game. Goodbye! ***" << endl;
    return 0;

#endif
}