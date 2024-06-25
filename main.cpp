#include <iostream>
#include <stack>
#include <string>
#include <fstream>
#include <vector>

struct State {
    int id;
    std::string label;
    State(int id, const std::string& label) : id(id), label(label) {}
};

struct Transition {
    int from;
    int to;
    std::string symbol;
    Transition(int from, int to, const std::string& symbol) : from(from), to(to), symbol(symbol) {}
};

class NFA {
public:
    std::vector<State> states;
    std::vector<Transition> transitions;
    int start;
    int accept;

    NFA() : start(-1), accept(-1) {}

    NFA(char symbol, int& idCounter) {
        start = idCounter++;
        accept = idCounter++;
        int mid = idCounter++;
        states.push_back(State(start, "start"));
        states.push_back(State(mid, std::string(1, symbol)));
        states.push_back(State(accept, "accept"));
        transitions.push_back(Transition(start, mid, std::string(1, symbol)));
        transitions.push_back(Transition(mid, accept, ""));
    }

    static NFA concatenate(NFA nfa1, NFA nfa2, int& idCounter) {
        NFA result;
        result.start = nfa1.start;
        result.accept = nfa2.accept;
        result.states = nfa1.states;
        result.states.insert(result.states.end(), nfa2.states.begin(), nfa2.states.end());
        result.transitions = nfa1.transitions;
        result.transitions.insert(result.transitions.end(), nfa2.transitions.begin(), nfa2.transitions.end());
        result.transitions.push_back(Transition(nfa1.accept, nfa2.start, ""));
        idCounter = result.add_states_ids(idCounter);
        return result;
    }

    static NFA unite(NFA nfa1, NFA nfa2, int& idCounter) {
        NFA result;
        result.start = idCounter++;
        result.accept = idCounter++;
        result.states.push_back(State(result.start, "start"));
        result.states.push_back(State(result.accept, "accept"));
        result.states.insert(result.states.end(), nfa1.states.begin(), nfa1.states.end());
        result.states.insert(result.states.end(), nfa2.states.begin(), nfa2.states.end());
        result.transitions.push_back(Transition(result.start, nfa1.start, ""));
        result.transitions.push_back(Transition(result.start, nfa2.start, ""));
        result.transitions.insert(result.transitions.end(), nfa1.transitions.begin(), nfa1.transitions.end());
        result.transitions.insert(result.transitions.end(), nfa2.transitions.begin(), nfa2.transitions.end());
        result.transitions.push_back(Transition(nfa1.accept, result.accept, ""));
        result.transitions.push_back(Transition(nfa2.accept, result.accept, ""));
        idCounter = result.add_states_ids(idCounter);
        return result;
    }

    static NFA kleene_star(NFA nfa, int& idCounter) {
        NFA result;
        result.start = idCounter++;
        result.accept = idCounter++;
        result.states.push_back(State(result.start, "start"));
        result.states.push_back(State(result.accept, "accept"));
        result.states.insert(result.states.end(), nfa.states.begin(), nfa.states.end());
        result.transitions.push_back(Transition(result.start, nfa.start, ""));
        result.transitions.push_back(Transition(nfa.accept, nfa.start, ""));
        result.transitions.push_back(Transition(nfa.accept, result.accept, ""));
        result.transitions.push_back(Transition(result.start, result.accept, ""));
        result.transitions.insert(result.transitions.end(), nfa.transitions.begin(), nfa.transitions.end());
        idCounter = result.add_states_ids(idCounter);
        return result;
    }

    int add_states_ids(int start_id) {
        for (auto& state : states) {
            state.id = start_id++;
        }
        return start_id;
    }

    void write_to_dot(const std::string& filename) {
        std::ofstream dot_file(filename);
        dot_file << "digraph NFA {" << std::endl;
        for (const auto& state : states) {
            dot_file << "  " << state.id << " [label=\"" << state.label << "\"];" << std::endl;
        }
        for (const auto& transition : transitions) {
            dot_file << "  " << transition.from << " -> " << transition.to << " [label=\"" << transition.symbol << "\"];" << std::endl;
        }
        dot_file << "}" << std::endl;
        dot_file.close();
    }
};

NFA regex_to_nfa(const std::string& regex) {
    std::stack<NFA> stack;
    int idCounter = 0;

    for (char c : regex) {
        if (c == '*') {
            NFA nfa = stack.top(); stack.pop();
            stack.push(NFA::kleene_star(nfa, idCounter));
        } else if (c == '|') {
            NFA nfa2 = stack.top(); stack.pop();
            NFA nfa1 = stack.top(); stack.pop();
            stack.push(NFA::unite(nfa1, nfa2, idCounter));
        } else if (c == '.') {
            NFA nfa2 = stack.top(); stack.pop();
            NFA nfa1 = stack.top(); stack.pop();
            stack.push(NFA::concatenate(nfa1, nfa2, idCounter));
        } else {
            stack.push(NFA(c, idCounter));
        }
    }

    return stack.top();
}

int main() {
    std::string regex = "a.b|c*";
    NFA nfa = regex_to_nfa(regex);
    std::cout << "Generando archivo nfa.dot..." << std::endl;
    nfa.write_to_dot("nfa.dot");
    std::cout << "El archivo nfa.dot ha sido creado. Usa Graphviz para visualizarlo." << std::endl;

    return 0;
}