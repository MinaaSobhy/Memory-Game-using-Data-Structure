#include <iostream>
#include <cstdlib>
#include<time.h>
#include <cstring>
#include <bits/stdc++.h>
#include <cmath>
#include <unistd.h>
using namespace std;

// array of the letters which will be shuffled to play the game

string staff[32] = {"a ", "a ", "a ", "a ", "b ", "b ", "b ", "b ", "c ", "c ", "c ", "c ", "d ", "d ", "d ", "d ", "e ", "e ", "e ", "e ", "f ", "f ", "f ", "f ", "g ", "g ", "g ", "g ", "h ", "h ", "h ", "h "};

// array of IDs which gets printed to the terminal

string usedIds[32] = {"01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32"};

//array which determines which squares were matched then removed from the game

int flagged[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

//arrays which the computer uses to store the data of opened squares

int com[32] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
string tiles[32] = {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "};

//Scores of player and computer
int playerScore = 0;
int comScore = 0;

//the flag that decides if the game ended or not
bool work = true;

// node construction

struct Node {
    string data;
    int id;
    Node *left;
    Node *right;
    int height;
};

//function returns the height of the node
int height(Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

// A utility function to get maximum
// of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}

/* Helper function that allocates a
   new node with the given key and
   NULL left and right pointers. */
Node* newNode(int key, string data)
{
    Node* node = new Node();
    node->id = key;
    node->left = NULL;
    node->right = NULL;
    node->data = data;
    node->height = 1; // new node is initially
                      // added at leaf
    return(node);
}

// A utility function to right
// rotate subtree rooted with y
// See the diagram given above.
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;

    // Return new root
    return x;
}

// A utility function to left
// rotate subtree rooted with x
// See the diagram given above.
Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left),
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Recursive function to insert a key
// in the subtree rooted with node and
// returns the new root of the subtree.
Node* insert(Node* node, int key, string data)
{
    /* 1. Perform the normal BST insertion */
    if (node == NULL)
        return(newNode(key, data));

    if (key < node->id)
        node->left = insert(node->left, key, data);
    else if (key > node->id)
        node->right = insert(node->right, key, data);
    else // Equal keys are not allowed in BST
        return node;

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
                        height(node->right));

    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->id)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->id)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->id)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->id)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

//the function that used to search the IDs
string search_tree (Node* root, int key)
    {
        if (root->id == key)
            return root->data;
        if (key > root->id)
            return search_tree(root->right, key);
        else
            return search_tree(root->left, key);
    }

Node* root = NULL;
void shuffle_array(string arr[], int n)
{
    // shuffle the letters array randomly
    random_shuffle(arr, arr + n);

    // creates nodes and puts them in their place in the AVL tree
    // The node takes the random values of letters after being shuffled
    for(int i = 1; i<= 32; i++) {
        root = insert(root, i, arr[i-1]);
    }
}

// prints the data in usedIds array into the terminal

void printBoard() {
    cout << "\n";
    cout << "  | " << usedIds[0] << " | " << usedIds[1] << " | " << usedIds[2] << " | " << usedIds[3] << " | "  << usedIds[4] << " | " << usedIds[5] << " | " << usedIds[6] << " | " << usedIds[7] << " |             Your-score: " << playerScore << "\n";
    cout << "  |----|----|----|----|----|----|----|----|             " << "Com-score: " << comScore << "\n";
    cout << "  | " << usedIds[8] << " | " << usedIds[9] << " | " << usedIds[10] << " | " << usedIds[11] << " | " << usedIds[12] << " | " << usedIds[13] << " | " << usedIds[14] << " | " << usedIds[15] << " | \n";
    cout << "  |----|----|----|----|----|----|----|----|\n";
    cout << "  | " << usedIds[16] << " | " << usedIds[17] << " | " << usedIds[18] << " | " << usedIds[19] << " | " << usedIds[20] << " | " << usedIds[21] << " | " << usedIds[22] << " | " << usedIds[23] << " | \n";
    cout << "  |----|----|----|----|----|----|----|----|\n";
    cout << "  | " << usedIds[24] << " | " << usedIds[25] << " | " << usedIds[26] << " | " << usedIds[27] << " | " << usedIds[28] << " | " << usedIds[29] << " | " << usedIds[30] << " | " << usedIds[31] << " | \n";
    cout << "\n";
}

// Checks if the game has ended and determines the winner

void checkWinner() {
    bool finished = true;
    for(int i=0; i<32; i++) {
        if(com[i] != 0) {
            finished = false;
        }
    }
    if(finished == true) {
         cout << "\n";
         cout << "  Your-score: " << playerScore << "    Com-score: " << comScore << "\n";
        if(playerScore > comScore) {
            cout << "  You Won!\n";
        } else if(playerScore < comScore) {
            cout << "  You Lost!\n";
        } else {
            cout << "  Draw!\n";
        }
        work = false;
    }
}

//function handles the computer's turn

void comPlay() {

    // shuffle the com array and select two numbers which are not similar or removed before
    if(work) {
        random_shuffle(com, com + sizeof(com) / sizeof(com[0]));
        int num1 = 0;
        int num2 = 0;
        bool foundSame = false;
        if(rand() % 10 > 4) {
            for(int i=0; i<31; i++) {
                for(int j=i+1; j<32; j++) {
                    if(tiles[i] != " " && tiles[j] != " " && tiles[i] == tiles[j]) {
                        num1 = i;
                        num2 = j;
                        foundSame = true;
                        break;
                    }
                }
                if(foundSame == true) break;
            }
        }
        if(foundSame == false) {
            for(int i = 0; i<32; i++) {
                if(com[i] > 0) {
                    if(num1 == 0) num1 = com[i] - 1;
                    else {
                        num2 = com[i] - 1;
                        break;
                    }
                }
            }
        }
        string val1 = usedIds[num1];
        string letter1 = search_tree(root, num1 + 1);
        usedIds[num1] = letter1;
        cout << "  Com chose: " << to_string(num1 + 1) << endl;
        printBoard();
        sleep(5);
        string val2 = usedIds[num2];
        string letter2 = search_tree(root, num2 + 1);
        usedIds[num2] = letter2;
        cout << "  Com chose: " << to_string(num2 + 1) << endl;
        printBoard();

        // compares both of the letters if they are similar com gets a point and then removes them from the possible plays

        if(letter1 == letter2) {
            tiles[num1] = " ";
            tiles[num2] = " ";
            comScore++;
            val1 = "  ";
            val2 = "  ";
            for(int i=0; i<32; i++) {
                if(flagged[i] == 0) {
                    flagged[i] = num1 + 1;
                    flagged[i + 1] = num2 + 1;
                    break;
                }
            }
            for(int i=0; i<32; i++) {
                if(com[i] == num1+1 || com[i] == num2 + 1) com[i] = 0;
            }
        } else {
            tiles[num1] = letter1;
            tiles[num2] = letter2;
        }
        usedIds[num1] = val1;
        usedIds[num2] = val2;
        sleep(5);
        system("cls");
        checkWinner();

        if(work)
        {
            printBoard();
        }

    }
}

bool isNumber(const string& str)
{
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

//function handles the player's turn

void play() {
    if(work) {
        int num1;
        int num2;

        // takes the player's first number and processes it
        string in1;
        cout << "  Type a number: ";
        cin >> in1;
        in1.erase(std::remove(in1.begin(), in1.end(), ' '), in1.end());
        if(isNumber(in1) == false || in1.empty()) {
            cout << "  Enter a valid integer between 1 and 32.\n";
            play();
        } else num1 = stoi(in1);
        if(num1 > 32 || num1 < 1) {
            cout << "  Enter a valid integer between 1 and 32.\n";
            play();
        }
        for(int i=0; i<32; i++) {
            if(flagged[i] == num1) {
                cout << "  Type a number that is not selected before.\n";
                play();
            }
        }
        num1--;
        string val1 = usedIds[num1];
        string letter1 = search_tree(root, num1 + 1);
        usedIds[num1] = letter1;
        printBoard();

        // takes the player's second number and processes it

        while(true) {
            bool can = true;
            string in2;
            cout << "  Type another number: ";
            cin >> in2;
            in2.erase(std::remove(in2.begin(), in2.end(), ' '), in2.end());
            if(isNumber(in2) == false || in2.empty()) {
                cout << "  Enter a valid integer between 1 and 32.\n";
                can = false;
            } else num2 = stoi(in2);
            if(num2 > 32 && can == true || num2 < 1 && can == true) {
                cout << "  Enter a valid integer between 1 and 32.\n";
                can = false;
            }
            if(num1 + 1 == num2 && can == true) {
                cout << "  You can't type the same number twice.\n";
                can = false;
            }
            for(int i = 0; i<32; i++) {
                if(flagged[i] == num2 && can == true) {
                    cout << "  Type a number that is not selected before.\n";
                    can = false;
                }
            }
            if(can == true) break;
        }
        num2--;
        string val2 = usedIds[num2];
        string letter2 = search_tree(root, num2 + 1);
        usedIds[num2] = letter2;
        printBoard();

        // compares both of the letters if they are similar the player gets a point and then removes them from the possible plays
        if(letter1 == letter2) {
            tiles[num1] = " ";
            tiles[num2] = " ";
            playerScore++;
            val1 = "  ";
            val2 = "  ";
            for(int i=0; i<32; i++) {
                if(flagged[i] == 0) {
                    flagged[i] = num1 + 1;
                    flagged[i + 1] = num2 + 1;
                    break;
                }
            }
            for(int i=0; i<32; i++) {
                if(com[i] == num1+1 || com[i] == num2 + 1) com[i] = 0;
            }
        } else {
            tiles[num1] = letter1;
            tiles[num2] = letter2;
        }
        usedIds[num1] = val1;
        usedIds[num2] = val2;
        sleep(5);
        system("cls");
        checkWinner();
        if(work) {

        // recurrsive loop to continue the game
            comPlay();
            play();
        }
    }
};

int main() {
    srand(time(0));

    // TO display instructions

     cout << "You will have a board with 32 squares, each square has a number. \nWhen you write its number it will show you the letter it hides. You must get 2 similar letters to score a point. \nYou also should beat the COM. Good Luck." << endl;
     sleep(20);
     system("cls");

    printBoard();

    // start the game

    shuffle_array(staff, sizeof(staff) / sizeof(staff[0]));
    play();
    return 0;
}
