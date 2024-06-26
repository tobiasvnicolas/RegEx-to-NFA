#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

const string ALLOWED = "0123456789qwertyuiopasdfghjklzxcvbnm*.+()$";
const unordered_set<char> OPS = {'*', '.', '+', '(', ')'};
const unordered_map<char, int> PRIORITY = {{'*', 2}, {'.', 1}, {'+', 0}};
const int INVALID_REGEX = -1;
const int VALID_REGEX = 0;

class State {
public:
    int id;
    string name;
    vector<pair<State*, char>> transitions;
    static int count;

    State() : id(count++), name("") {}

    void addTransition(State* node, char alph) {
        transitions.push_back({node, alph});
    }
};

int State::count = 0;

class NFA {
public:
    vector<State*> states;
    State* start;
    vector<State*> accept;
    unordered_set<char> alphabet;

    NFA() : start(nullptr) {}

    void getAlph(const string& regex) {
        for (char c : regex) {
            if (OPS.find(c) == OPS.end() && alphabet.find(c) == alphabet.end()) {
                alphabet.insert(c);
            }
        }
    }

    void addState(State* s) {
        states.push_back(s);
    }

    void addTransition(State* s1, State* s2, char a) {
        s1->addTransition(s2, a);
    }

    void makeStart(State* s) {
        start = s;
    }

    void makeAccept(State* s) {
        accept.push_back(s);
    }

    void removeAccept(State* s) {
        accept.erase(remove(accept.begin(), accept.end(), s), accept.end());
    }

    void names() {
        int c = 0;
        start->name = "q" + to_string(c++);
        vector<State*> states_queue = {start};
        while (!states_queue.empty()) {
            State* cur = states_queue.front();
            states_queue.erase(states_queue.begin());
            for (auto& transition : cur->transitions) {
                State* state = transition.first;
                if (state->name.empty()) {
                    state->name = "q" + to_string(c++);
                    states_queue.push_back(state);
                }
            }
        }
    }

    void printTuple(const string& path) {
        json js;
        for (auto state : states) {
            js["states"].push_back(state->name);
        }
        for (char c : alphabet) {
            js["letters"].push_back(string(1, c));
        }
        for (auto state : states) {
            for (auto& transition : state->transitions) {
                js["transition_function"].push_back({state->name, string(1, transition.second), transition.first->name});
            }
        }
        js["start_states"] = {start->name};
        for (auto state : accept) {
            js["final_states"].push_back(state->name);
        }

        ofstream file(path);
        file << setw(4) << js << endl;
    }
};

string addConcat(const string& regEx) {
    string res;
    for (size_t i = 0; i < regEx.size(); ++i) {
        res.push_back(regEx[i]);
        if (regEx[i] != '(' && regEx[i] != '.' && regEx[i] != '+') {
            if (i + 1 < regEx.size() && regEx[i + 1] != ')' && regEx[i + 1] != '*' && regEx[i + 1] != '+' && regEx[i + 1] != '.') {
                res.push_back('.');
            }
        }
    }
    return res;
}

int parseRegEx(const string& regEx, vector<char>& postfix) {
    if (regEx.empty()) return VALID_REGEX;

    for (char a : regEx) {
        if (ALLOWED.find(a) == string::npos) {
            return INVALID_REGEX;
        }
    }

    postfix.clear();
    stack<char> stack;
    for (char a : regEx) {
        if (OPS.find(a) == OPS.end()) {
            postfix.push_back(a);
        } else if (a == '(') {
            stack.push('(');
        } else if (a == ')') {
            while (!stack.empty() && stack.top() != '(') {
                postfix.push_back(stack.top());
                stack.pop();
            }
            stack.pop();
        } else {
            while (!stack.empty() && stack.top() != '(' && PRIORITY.at(a) <= PRIORITY.at(stack.top())) {
                postfix.push_back(stack.top());
                stack.pop();
            }
            stack.push(a);
        }
    }
    while (!stack.empty()) {
        postfix.push_back(stack.top());
        stack.pop();
    }
    return VALID_REGEX;
}

string readJSON(const string& path) {
    ifstream file(path);
    json data;
    file >> data;
    return data.value("regex", "");
}

void visualize_nfa(const json& nfa_json, const string& output_path) {
    ofstream dot(output_path + ".dot");
    dot << "digraph NFA {" << endl;
    for (const auto& state : nfa_json["states"]) {
        dot << "    " << state;
        if (find(nfa_json["final_states"].begin(), nfa_json["final_states"].end(), state) != nfa_json["final_states"].end()) {
            dot << " [shape=doublecircle]";
        }
        dot << ";" << endl;
    }
    for (const auto& transition : nfa_json["transition_function"]) {
        string label = (transition[1] == "$") ? "ε" : transition[1].get<string>();
        dot << "    " << transition[0] << " -> " << transition[2] << " [label=\"" << label << "\"];" << endl;
    }
    for (const auto& start_state : nfa_json["start_states"]) {
        dot << "    start [shape=point];" << endl;
        dot << "    start -> " << start_state << ";" << endl;
    }
    dot << "}" << endl;
    dot.close();
    string cmd = "dot -Tpng " + output_path + ".dot -o " + output_path + ".png";
    system(cmd.c_str());
    remove((output_path + ".dot").c_str());
}

NFA kleene_base_cases(char symbol) {
    NFA nfa;
    if (symbol == '$') {
        State* start_state = new State();
        nfa.addState(start_state);
        nfa.makeStart(start_state);
        nfa.makeAccept(start_state);
        return nfa;
    }
    if (symbol == '\0' || symbol == ' ') {
        State* start_state = new State();
        nfa.addState(start_state);
        nfa.makeStart(start_state);
        return nfa;
    } else {
        State* q0 = new State();
        nfa.addState(q0);
        nfa.makeStart(q0);
        State* q1 = new State();
        nfa.addState(q1);
        nfa.makeAccept(q1);
        nfa.addTransition(q0, q1, symbol);
        return nfa;
    }
}

NFA kleene_union(NFA& nfa1, NFA& nfa2) {
    NFA nfa;
    State* start = new State();
    nfa.addState(start);
    nfa.makeStart(start);
    nfa.addTransition(start, nfa1.start, '$');
    nfa.addTransition(start, nfa2.start, '$');
    nfa.states.insert(nfa.states.end(), nfa1.states.begin(), nfa1.states.end());
    nfa.states.insert(nfa.states.end(), nfa2.states.begin(), nfa2.states.end());
    nfa.accept.insert(nfa.accept.end(), nfa1.accept.begin(), nfa1.accept.end());
    nfa.accept.insert(nfa.accept.end(), nfa2.accept.begin(), nfa2.accept.end());
    return nfa;
}

NFA kleene_concat(NFA& nfa1, NFA& nfa2) {
    NFA nfa;
    nfa.states.insert(nfa.states.end(), nfa1.states.begin(), nfa1.states.end());
    nfa.states.insert(nfa.states.end(), nfa2.states.begin(), nfa2.states.end());
    nfa.start = nfa1.start;
    nfa.accept = nfa2.accept;
    for (auto accept_state : nfa1.accept) {
        accept_state->addTransition(nfa2.start, '$');
    }
    return nfa;
}

NFA kleene_star(NFA& nfa1) {
    NFA nfa;
    State* start = new State();
    nfa.addState(start);
    nfa.makeStart(start);
    nfa.addTransition(start, nfa1.start, '$');
    for (auto accept_state : nfa1.accept) {
        nfa.addTransition(accept_state, nfa1.start, '$');
        nfa.addTransition(accept_state, start, '$');
    }
    nfa.states.insert(nfa.states.end(), nfa1.states.begin(), nfa1.states.end());
    nfa.makeAccept(start);
    return nfa;
}

NFA thompson(const string& regEx) {
    vector<char> postfix;
    if (parseRegEx(addConcat(regEx), postfix) == INVALID_REGEX) {
        throw invalid_argument("Invalid regular expression");
    }

    if (postfix.empty()) {
        NFA nfa;
        State* start_state = new State();
        nfa.addState(start_state);
        nfa.makeStart(start_state);
        return nfa;
    }

    stack<NFA> stackNFA;
    for (char symbol : postfix) {
        if (OPS.find(symbol) == OPS.end()) {
            stackNFA.push(kleene_base_cases(symbol));
        } else if (symbol == '+') {
            NFA N2 = stackNFA.top(); stackNFA.pop();
            NFA N1 = stackNFA.top(); stackNFA.pop();
            stackNFA.push(kleene_union(N1, N2));
        } else if (symbol == '.') {
            NFA N2 = stackNFA.top(); stackNFA.pop();
            NFA N1 = stackNFA.top(); stackNFA.pop();
            stackNFA.push(kleene_concat(N1, N2));
        } else if (symbol == '*') {
            NFA N = stackNFA.top(); stackNFA.pop();
            stackNFA.push(kleene_star(N));
        }
    }

    if (stackNFA.empty()) {
        throw invalid_argument("Invalid regular expression");
    }

    return stackNFA.top();
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: regex-NFA <input_json> <output_json>" << endl;
        return 1;
    }

    string regEx = readJSON(argv[1]);
    if (regEx.empty()) {
        regEx = "";
    }

    NFA nfa = thompson(regEx);
    nfa.getAlph(regEx);
    nfa.names();
    string output_path = argv[2];
    nfa.printTuple(output_path);

    ifstream file(output_path);
    json nfa_json;
    file >> nfa_json;
    visualize_nfa(nfa_json, output_path.substr(0, output_path.find_last_of('.')));

    return 0;
}