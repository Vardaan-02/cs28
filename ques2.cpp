
#include <bits/stdc++.h>
using namespace std;

struct Rule {
    vector<string> premises;
    string conclusion;
};

int main() {

    // Initial Knowledge Base
    set<string> facts = {
        "Student(Ravi)",
        "Student(Anu)",

        "Course(AI)",
        "Course(ML)",

        "Studies(Ravi,AI)",
        "Passed(Ravi,AI)",

        "Studies(Anu,ML)",

        "Professor(DrSharma)",
        "Supervises(DrSharma,Ravi)"
    };

    vector<string> students = {"Ravi", "Anu"};
    vector<string> courses = {"AI", "ML"};
    vector<string> professors = {"DrSharma"};

    vector<Rule> rules;

    // Policy 1:
    // Every student studies at least one course.
    // FOL:
    // forall x (Student(x) ->
    //     exists y (Course(y) AND Studies(x,y)))

    cout << "POLICY 1: Checking student-course relationships\n";

    for (string s : students) {
        bool found = false;

        for (string c : courses) {
            if (facts.count("Course(" + c + ")") &&
                facts.count("Studies(" + s + "," + c + ")")) {
                found = true;
                break;
            }
        }

        if (found)
            cout << s << " studies at least one course.\n";
        else
            cout << s << " does not have a recorded course.\n";
    }

    // Policy 2:
    // Student studies and passes same course -> Qualified
    //
    // FOL:
    // forall x,y (
    //   Student(x) AND Course(y) AND
    //   Studies(x,y) AND Passed(x,y)
    //   -> Qualified(x)
    // )

    for (string s : students) {
        for (string c : courses) {

            rules.push_back({
                {
                    "Student(" + s + ")",
                    "Course(" + c + ")",
                    "Studies(" + s + "," + c + ")",
                    "Passed(" + s + "," + c + ")"
                },
                "Qualified(" + s + ")"
            });

        }
    }

    // Policy 3:
    // Qualified student supervised by professor
    // -> Researcher
    //
    // FOL:
    // forall x,y (
    //   Qualified(x) AND Professor(y) AND
    //   Supervises(y,x)
    //   -> Researcher(x)
    // )

    for (string s : students) {
        for (string p : professors) {

            rules.push_back({
                {
                    "Qualified(" + s + ")",
                    "Professor(" + p + ")",
                    "Supervises(" + p + "," + s + ")"
                },
                "Researcher(" + s + ")"
            });

        }
    }

    // Policy 4:
    // Researcher -> Eligible
    //
    // FOL:
    // forall x (Researcher(x) -> Eligible(x))

    for (string s : students) {

        rules.push_back({
            {"Researcher(" + s + ")"},
            "Eligible(" + s + ")"
        });

    }

    // Forward Chaining Algorithm

    cout << "\nFORWARD CHAINING:\n";

    bool changed = true;
    int step = 1;

    while (changed) {

        changed = false;

        for (const Rule &rule : rules) {

            bool allTrue = true;

            // Check whether all premises are satisfied
            for (const string &premise : rule.premises) {
                if (!facts.count(premise)) {
                    allTrue = false;
                    break;
                }
            }

            // Generate a new fact
            if (allTrue && !facts.count(rule.conclusion)) {

                facts.insert(rule.conclusion);

                cout << "Step " << step++ << ": "
                     << rule.conclusion << endl;

                changed = true;
            }
        }
    }

    // Final Result

    cout << "\nFINAL KNOWLEDGE BASE:\n";

    for (const string &fact : facts)
        cout << fact << endl;

    cout << "\nRESULT:\n";

    if (facts.count("Eligible(Ravi)"))
        cout << "Ravi IS eligible for research fellowship.\n";
    else
        cout << "Ravi is NOT eligible for research fellowship.\n";

    if (facts.count("Eligible(Anu)"))
        cout << "Anu IS eligible for research fellowship.\n";
    else
        cout << "Anu is NOT eligible for research fellowship.\n";

    return 0;
}
