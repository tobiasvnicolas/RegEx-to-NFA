#include <iostream>
#include <stack>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>

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
    std::vector<int> accept;

    NFA() : start(-1) {}

    NFA(char symbol, int& idCounter) {
        start = idCounter++;
        int acceptState = idCounter++;
        states.push_back(State(start, "start"));
        states.push_back(State(acceptState, "accept"));
        transitions.push_back(Transition(start, acceptState, std::string(1, symbol)));
        accept.push_back(acceptState);
    }

    static NFA concatenate(NFA nfa1, NFA nfa2, int& idCounter) {
        NFA result;
        result.start = nfa1.start;

        // Copiar estados de nfa1
        result.states = nfa1.states;
        result.transitions = nfa1.transitions;

        // Crear un mapa para actualizar los IDs de nfa2
        std::unordered_map<int, int> idMap;
        for (const auto& state : nfa2.states) {
            idMap[state.id] = idCounter++;
        }

        // Añadir los estados de nfa2 con los nuevos IDs
        for (const auto& state : nfa2.states) {
            result.states.push_back(State(idMap[state.id], state.label));
        }

        // Añadir las transiciones de nfa2 con los nuevos IDs
        for (const auto& transition : nfa2.transitions) {
            result.transitions.push_back(Transition(idMap[transition.from], idMap[transition.to], transition.symbol));
        }

        // Añadir transiciones epsilon desde los estados de aceptación de nfa1 a nfa2.start
        for (int acceptState : nfa1.accept) {
            result.transitions.push_back(Transition(acceptState, idMap[nfa2.start], ""));
        }

        // Actualizar los estados de aceptación
        for (int acceptState : nfa2.accept) {
            result.accept.push_back(idMap[acceptState]);
        }

        return result;
    }

    static NFA unite(NFA nfa1, NFA nfa2, int& idCounter) {
        NFA result;
        result.start = idCounter++;
        int newAccept = idCounter++;
        result.states.push_back(State(result.start, "start"));
        result.states.push_back(State(newAccept, "accept"));

        std::unordered_map<int, int> idMap1;
        for (const auto& state : nfa1.states) {
            idMap1[state.id] = idCounter++;
        }
        for (const auto& state : nfa1.states) {
            result.states.push_back(State(idMap1[state.id], state.label));
        }

        std::unordered_map<int, int> idMap2;
        for (const auto& state : nfa2.states) {
            idMap2[state.id] = idCounter++;
        }
        for (const auto& state : nfa2.states) {
            result.states.push_back(State(idMap2[state.id], state.label));
        }

        result.transitions.push_back(Transition(result.start, idMap1[nfa1.start], ""));
        result.transitions.push_back(Transition(result.start, idMap2[nfa2.start], ""));

        for (const auto& transition : nfa1.transitions) {
            result.transitions.push_back(Transition(idMap1[transition.from], idMap1[transition.to], transition.symbol));
        }
        for (const auto& transition : nfa2.transitions) {
            result.transitions.push_back(Transition(idMap2[transition.from], idMap2[transition.to], transition.symbol));
        }

        for (int acceptState : nfa1.accept) {
            result.transitions.push_back(Transition(idMap1[acceptState], newAccept, ""));
        }
        for (int acceptState : nfa2.accept) {
            result.transitions.push_back(Transition(idMap2[acceptState], newAccept, ""));
        }

        result.accept.push_back(newAccept);
        return result;
    }

    static NFA kleene_star(NFA nfa, int& idCounter) {
        NFA result;
        result.start = idCounter++;
        int newAccept = idCounter++;
        result.states.push_back(State(result.start, "start"));
        result.states.push_back(State(newAccept, "accept"));

        std::unordered_map<int, int> idMap;
        for (const auto& state : nfa.states) {
            idMap[state.id] = idCounter++;
        }
        for (const auto& state : nfa.states) {
            result.states.push_back(State(idMap[state.id], state.label));
        }

        result.transitions.push_back(Transition(result.start, idMap[nfa.start], ""));
        result.transitions.push_back(Transition(result.start, newAccept, ""));
        for (int acceptState : nfa.accept) {
            result.transitions.push_back(Transition(idMap[acceptState], idMap[nfa.start], ""));
            result.transitions.push_back(Transition(idMap[acceptState], newAccept, ""));
        }

        for (const auto& transition : nfa.transitions) {
            result.transitions.push_back(Transition(idMap[transition.from], idMap[transition.to], transition.symbol));
        }

        result.accept.push_back(newAccept);
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
