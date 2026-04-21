#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <numeric>

using namespace std;

struct Student {
    string name;
    string gender;
    int className;
    int scores[9];
    int avg;
    int rank;

    void updateAvg() {
        int sum = 0;
        for (int i = 0; i < 9; ++i) sum += scores[i];
        avg = sum / 9;
    }
};

bool compareStudents(const Student* a, const Student* b) {
    if (a->avg != b->avg) return a->avg > b->avg;
    for (int i = 0; i < 9; ++i) {
        if (a->scores[i] != b->scores[i]) return a->scores[i] > b->scores[i];
    }
    return a->name < b->name;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unordered_map<string, Student*> nameToStudent;
    vector<Student*> students;
    bool started = false;
    string cmd;

    while (cin >> cmd) {
        if (cmd == "ADD") {
            string name, gender_in;
            int className;
            int scores[9];
            cin >> name >> gender_in >> className;
            for (int i = 0; i < 9; ++i) cin >> scores[i];

            if (started) {
                cout << "[Error]Cannot add student now.\n";
                continue;
            }
            if (nameToStudent.count(name)) {
                cout << "[Error]Add failed.\n";
                continue;
            }

            string gender = (gender_in == "M" ? "male" : "female");
            Student* s = new Student{name, gender, className};
            for (int i = 0; i < 9; ++i) s->scores[i] = scores[i];
            s->updateAvg();
            nameToStudent[name] = s;
            students.push_back(s);

        } else if (cmd == "START") {
            started = true;
            sort(students.begin(), students.end(), compareStudents);
            for (int i = 0; i < students.size(); ++i) {
                students[i]->rank = i + 1;
            }

        } else if (cmd == "UPDATE") {
            string name;
            int code, score;
            cin >> name >> code >> score;
            if (!nameToStudent.count(name)) {
                cout << "[Error]Update failed.\n";
                continue;
            }
            Student* s = nameToStudent[name];
            s->scores[code] = score;
            s->updateAvg();

        } else if (cmd == "FLUSH") {
            sort(students.begin(), students.end(), compareStudents);
            for (int i = 0; i < students.size(); ++i) {
                students[i]->rank = i + 1;
            }

        } else if (cmd == "PRINTLIST") {
            for (auto s : students) {
                cout << s->rank << " " << s->name << " " << s->gender << " " << s->className << " " << s->avg << "\n";
            }

        } else if (cmd == "QUERY") {
            string name;
            cin >> name;
            if (!nameToStudent.count(name)) {
                cout << "[Error]Query failed.\n";
                continue;
            }
            cout << "STUDENT " << name << " NOW AT RANKING " << nameToStudent[name]->rank << "\n";

        } else if (cmd == "END") {
            break;
        }
    }

    for (auto s : students) delete s;

    return 0;
}
