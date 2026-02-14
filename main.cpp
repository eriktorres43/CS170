#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <ctime>

using namespace std;

vector<int> depth_0_puzzle = {1, 2, 3, 4, 5, 6, 7, 8, 0}; vector<int> depth_2_puzzle = {1, 2, 3, 4, 5, 6, 0, 7, 8};
vector<int> depth_4_puzzle = {1, 2, 3, 5, 0, 6, 4, 7, 8}; vector<int> depth_8_puzzle = {1, 3, 6, 5, 0, 2, 4, 7, 8};
vector<int> depth_12_puzzle = {1, 3, 6, 5, 0, 7, 4, 8, 2}; vector<int> depth_16_puzzle = {1, 6, 7, 5, 0, 3, 4, 8, 2};
vector<int> depth_20_puzzle = {7, 1, 2, 4, 8, 5, 6, 3, 0}; vector<int> depth_24_puzzle = {0, 7, 2, 4, 6, 1, 3, 5, 8};

vector<vector<int>> Puzzles = {depth_0_puzzle, depth_2_puzzle, depth_4_puzzle, depth_8_puzzle, depth_12_puzzle, depth_16_puzzle, depth_20_puzzle, depth_24_puzzle};

class TreeNode {
    public:
    vector<int> puzzle;
    TreeNode* child_1 = nullptr;
    TreeNode* child_2 = nullptr; 
    TreeNode* child_3 = nullptr;
    TreeNode* child_4 = nullptr;

    int path_cost, heuristic, depth; // This is our g(n), h(n) and current depth

    TreeNode(vector<int> puzzle, int path_cost, int heuristic, int depth) : puzzle(puzzle), path_cost(path_cost), heuristic(heuristic), depth(depth)  {}
};

// Used CPlusPlus/Compilier for help with this part, setting up the priority queue

class Priority_Queue_Sorting {
    public: 
    bool operator() (TreeNode* puzzle_1, TreeNode* puzzle_2) {
        int heuristic_puzzle_1 = puzzle_1->path_cost + puzzle_1->heuristic; // This is f(n) = g(n) + h(n) which is the cheapest node and if it is, it goes to the top
        int heuristic_puzzle_2 = puzzle_2->path_cost + puzzle_2->heuristic; // of the priority queue (in if statement)
        if(heuristic_puzzle_1 > heuristic_puzzle_2) {
            return true;
        }
        return false;
    }
};

bool goalfunction(const vector<int>& puzzle);
int Misplaced_Tiles(const vector<int>& puzzle); 
int Manhattan_Distance(const vector<int>& puzzle);
int Expand(vector<int>& puzzle, TreeNode* current, int algorithm, priority_queue<TreeNode*, vector<TreeNode*>, Priority_Queue_Sorting>& working_queue);
TreeNode* general_search(const vector<int>&, int, TreeNode*); 

int main() {
    vector<int> choice;
    int userchoice;
    bool valid = false;
    cout << "Choose one of the following choices: " << endl << "1. If you want to be given an initial state" << endl << "2. If you want to input an initial state" << endl;
    cin >> userchoice;
    while(userchoice < 1 || userchoice > 2) { 
        cin.ignore(); cout << "Not a valid input, try again." << endl; 
        cin >> userchoice;
    }

    if(userchoice == 1) {
        cout << "Choose a case by giving a number 1-8: " << endl;
        cin.ignore();
        cin >> userchoice;

        while(userchoice < 1 || userchoice > 8) { 
            cin.ignore(); 
            cout << "Not a valid input, try again." << endl; 
            cin >> userchoice; 
        }
        
        for(int i = 0; i < Puzzles.size(); ++i) {
            if(i + 1 == userchoice) { 
                choice = Puzzles.at(i); 
            }
        }
    } else {
        cout << "Enter the 9 values (0-8), where 0 represents the blank tile, below: " << endl;

        for(int i = 0; i < choice.size(); ++i) {
            cin.ignore();
            cin >> userchoice;
            choice.push_back(userchoice);
        }
    } 
    int Choice = 0;
    for(int i = 0; i < choice.size(); ++i) {
        cout << choice.at(i);
        ++Choice;
        if(Choice != 0 && Choice % 3 == 0) { 
            cout << endl; 
        } else { 
            cout << " "; 
        }
    }

    cout << "Choose one of the following algorithms below: " << endl << "1. Uniform Cost Search" << endl << "2. A* with the Misplaced Tile heuristic " << endl; 
    cout << "3. A* with the Manhattan Distance heuristic" << endl;
    int option;
    cin >> option;
    while(option < 1 || option > 3) { 
        cin.ignore(); 
        cout << "Not a valid input, try again." << endl; 
        cin >> option; 
    }

    TreeNode* current = general_search(choice, option, nullptr);
    
    if(current == nullptr) {
        cout << "Failure, no solution." << endl;
    }
    
    return 0;
}

bool goalfunction(const vector<int>& puzzle) {
    for(int i = 0; i < puzzle.size(); ++i) {
        if(puzzle.at(i) != depth_0_puzzle.at(i)) {
            return false;
        }
    }
    return true;
}

int Misplaced_Tiles(const vector<int>& puzzle) {
    int count = 0;
    for(int i = 0; i < puzzle.size(); ++i) {
        if(puzzle.at(i) != 0 && depth_0_puzzle.at(i) != puzzle.at(i)) {
            ++count;
        }
    }
    return count;
}

int Manhattan_Distance(const vector<int>& puzzle) {
    int count, copy_i;
    for(int i = 0; i < puzzle.size(); ++i) {
       copy_i = i;
       while(puzzle.at(i) != 0 && (puzzle.at(i) != depth_0_puzzle.at(copy_i))) {
            if(copy_i - 3 >= 0 && puzzle.at(i) <= depth_0_puzzle.at(copy_i - 3)) { 
                copy_i = copy_i - 3; 
            }
            else if (copy_i + 3 <= puzzle.size()-1 && puzzle.at(i) >= depth_0_puzzle.at(copy_i + 3) && depth_0_puzzle.at(copy_i + 3) != 0) { 
                copy_i = copy_i + 3; 
            } 
            else if (copy_i + 1 > puzzle.size() - 1 || copy_i - 1 >= 0 && i % 3 != 0 && (depth_0_puzzle.at(i) % 3 == 0 || puzzle.at(i) != depth_0_puzzle.at(copy_i + 1))) { 
                copy_i = copy_i - 1; 
            } 
            else if (copy_i + 1 <= puzzle.size()-1 && depth_0_puzzle.at(i) % 3 != 0) { 
                copy_i = copy_i + 1;
            }
            ++count;
        }
    }
    return count;
}

int Expand(vector<int>& puzzle, TreeNode* current, int algorithm, priority_queue<TreeNode*, vector<TreeNode*>, Priority_Queue_Sorting>& working_queue) {
    int heuristic, count = 0;
    for(int i = 0; i < puzzle.size(); ++i) {
        if(puzzle.at(i) == 0) {
            if(i - 1 >= 0) { 
                swap(puzzle.at(i), puzzle.at(i-1));
                if(algorithm == 1) {
                    heuristic = 0;
                } else if (algorithm == 2) {
                    heuristic = Misplaced_Tiles(puzzle);
                } else {
                    heuristic = Manhattan_Distance(puzzle);
                }

                if(i % 3 != 0) {
                    current->child_1 = new TreeNode(puzzle, current->path_cost+1, heuristic, current->depth+1);
                }
                swap(puzzle.at(i), puzzle.at(i-1));
            } 
            if(i + 1 < puzzle.size()) { 
                swap(puzzle.at(i), puzzle.at(i+1));
                if(algorithm == 1) {
                    heuristic = 0;
                } else if (algorithm == 2) {
                    heuristic = Misplaced_Tiles(puzzle);
                } else {
                    heuristic = Manhattan_Distance(puzzle);
                }

                if(depth_0_puzzle.at(i) % 3 != 0) {
                    if(current->child_1 == nullptr) {
                        current->child_1 = new TreeNode(puzzle, current->path_cost+1, heuristic, current->depth+1);
                    } else {
                        current->child_2 = new TreeNode(puzzle, current->path_cost+1, heuristic, current->depth+1);
                    }
                }
                swap(puzzle.at(i), puzzle.at(i+1));
            } 
            if(i + 3 < puzzle.size()) { 
                swap(puzzle.at(i), puzzle.at(i+3));
                if(algorithm == 1) {
                    heuristic = 0;
                } else if (algorithm == 2) {
                    heuristic = Misplaced_Tiles(puzzle);
                } else {
                    heuristic = Manhattan_Distance(puzzle);
                }

                if(i <= 5) {
                    if(current->child_2 == nullptr) {
                        current->child_2 = new TreeNode(puzzle, current->path_cost+1, heuristic, current->depth+1);
                    } else {
                        current->child_3 = new TreeNode(puzzle, current->path_cost+1, heuristic, current->depth+1);
                    }
                }
                swap(puzzle.at(i), puzzle.at(i+3));
            } 
            if(i - 3 >= 0) { 
                swap(puzzle.at(i), puzzle.at(i-3));
                if(algorithm == 1) {
                    heuristic = 0;
                } else if (algorithm == 2) {
                    heuristic = Misplaced_Tiles(puzzle);
                } else {
                    heuristic = Manhattan_Distance(puzzle);
                }

                if(i > 2) {
                    if(current->child_2 == nullptr) {
                        current->child_2 = new TreeNode(puzzle, current->path_cost+1, heuristic, current->depth+1);
                    } else if(current->child_3 == nullptr) {
                        current->child_3 = new TreeNode(puzzle, current->path_cost+1, heuristic, current->depth+1);
                    } else {
                        current->child_4 = new TreeNode(puzzle, current->path_cost+1, heuristic, current->depth+1);
                    }
                }
                swap(puzzle.at(i), puzzle.at(i-3));
            }
            break;
        }
    }

    working_queue.push(current->child_1);
    working_queue.push(current->child_2);
    count += 2;
    if(current->child_3 != nullptr) {
        working_queue.push(current->child_3);
        ++count;
    }
    if(current->child_4 != nullptr) {
        working_queue.push(current->child_4);
        ++count;
    }
    return count;
}

bool Repeat_State(vector<vector<int>>& repeat, TreeNode* current) {
    for(int i = 0; i < repeat.size(); ++i) {
        if(repeat.at(i) == current->puzzle) {
            return true;
        }
    }
    return false;
}

TreeNode* general_search(const vector<int>& puzzle, int algorithm, TreeNode* current) { 
    priority_queue<TreeNode*, vector<TreeNode*>, Priority_Queue_Sorting> working_queue; // Used CPlusPlus/Compilier for help with this part, setting up the priority queue
    int heuristic, nodes_expanded = 0, max_queue_size = 0;
    vector<vector<int>> repeat;
    
    if(algorithm == 1) { 
        heuristic = 0; 
    } else if (algorithm == 2) { 
        heuristic = Misplaced_Tiles(puzzle); 
    } else { 
        heuristic = Manhattan_Distance(puzzle); 
    }

    if(current == nullptr) {
        current = new TreeNode(puzzle, 0, heuristic, 0);
        working_queue.push(current);
    }
    
    while(working_queue.empty() != true) {
        max_queue_size = max(max_queue_size, static_cast<int>(working_queue.size()));
        current = working_queue.top();
        working_queue.pop();

        if(working_queue.size() != 0) {
            cout << "The best state to expand with a g(n) = " << current->path_cost << " and h(n) = "
            << current->heuristic << " is:" << endl;
            int Choice = 0;
            for(int i = 0; i < puzzle.size(); ++i) {
                cout << current->puzzle.at(i);
                ++Choice;
                if(Choice != 0 && Choice % 3 == 0) { 
                    cout << endl; 
                } else { 
                    cout << " ";
                }
            }
        }

        if(goalfunction(current->puzzle) == true) {
            cout << "Goal State!!!" << endl << endl;
            cout << "Solution depth: " << current->depth << endl;
            cout << "Number of nodes expanded: " << nodes_expanded << endl;
            cout << "Max queue size: " << max_queue_size << endl;
            cout << "Time took is: " << clock()/(1.0 * CLOCKS_PER_SEC) << endl; // Used CPlusPlus time/clock review with its constants and functions
            return current;
        }

        if(Repeat_State(repeat, current) == false) {
            repeat.push_back(current->puzzle);
            nodes_expanded += Expand(current->puzzle, current, algorithm, working_queue);
        }
    }

    return nullptr;
}
