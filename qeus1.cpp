
#include <bits/stdc++.h>
using namespace std;

class BlocksWorld {
private:
    set<string> onTable;
    set<string> clear;
    map<string, string> on;
    string holding = "";
    bool handEmpty = true;

public:
    BlocksWorld() {
        onTable = {"A", "B", "C", "D"};
        clear = {"A", "B", "C", "D"};
    }

    void pickup(string x) {
        if (!handEmpty || !onTable.count(x) || !clear.count(x)) {
            cout << "PICKUP(" << x << ") failed!\n";
            return;
        }

        onTable.erase(x);
        clear.erase(x);
        holding = x;
        handEmpty = false;

        cout << "PICKUP(" << x << ") executed\n";
    }

    void putdown(string x) {
        if (handEmpty || holding != x) {
            cout << "PUTDOWN(" << x << ") failed!\n";
            return;
        }

        onTable.insert(x);
        clear.insert(x);
        holding = "";
        handEmpty = true;

        cout << "PUTDOWN(" << x << ") executed\n";
    }

    void stack(string x, string y) {
        if (handEmpty || holding != x || !clear.count(y)) {
            cout << "STACK(" << x << "," << y << ") failed!\n";
            return;
        }

        on[x] = y;
        clear.insert(x);
        clear.erase(y);

        holding = "";
        handEmpty = true;

        cout << "STACK(" << x << "," << y << ") executed\n";
    }

    void unstack(string x, string y) {
        if (!handEmpty || !on.count(x) ||
            on[x] != y || !clear.count(x)) {
            cout << "UNSTACK(" << x << "," << y << ") failed!\n";
            return;
        }

        on.erase(x);
        clear.erase(x);
        clear.insert(y);

        holding = x;
        handEmpty = false;

        cout << "UNSTACK(" << x << "," << y << ") executed\n";
    }

    void displayState() {
        cout << "\nCurrent State:\n";

        for (auto x : onTable)
            cout << "OnTable(" << x << ")\n";

        for (auto [x, y] : on)
            cout << "On(" << x << "," << y << ")\n";

        for (auto x : clear)
            cout << "Clear(" << x << ")\n";

        if (handEmpty)
            cout << "HandEmpty\n";
        else
            cout << "Holding(" << holding << ")\n";
    }

    bool goalAchieved() {
        return on.count("A") && on.at("A") == "C" &&
               on.count("D") && on.at("D") == "B";
    }
};

int main() {
    BlocksWorld bw;

    cout << "INITIAL STATE:\n";
    bw.displayState();

    cout << "\nExecuting Goal Stack Plan:\n";

    // Goal 1: On(A, C)
    bw.pickup("A");
    bw.stack("A", "C");

    // Goal 2: On(D, B)
    bw.pickup("D");
    bw.stack("D", "B");

    cout << "\nFINAL STATE:\n";
    bw.displayState();

    cout << "\nGoal Verification:\n";

    if (bw.goalAchieved())
        cout << "SUCCESS: Both goals achieved!\n";
    else
        cout << "FAILURE: Goal not achieved!\n";

    return 0;
}
