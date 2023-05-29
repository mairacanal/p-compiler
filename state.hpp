#pragma once

#include <map>
#include <string>

class Transition {
private:
    unsigned int state;
    bool to_stack;

public:
    Transition()
        : state { 0 }
        , to_stack { true }
    {
    }

    Transition(unsigned int state)
        : state { state }
        , to_stack { true }
    {
    }

    Transition(unsigned int state, bool to_stack)
        : state { state }
        , to_stack { to_stack }
    {
    }

    auto get_state() -> unsigned int
    {
        return state;
    }

    auto add_to_stack() -> bool
    {
        return to_stack;
    }
};

class State {
private:
    bool is_final;
    bool go_back;
    std::string output;
    std::map<char, Transition> transitions;

public:
    State()
    {
        is_final = false;
        is_final = false;
        output = "";
        transitions = std::map<char, Transition> {};
    }

    State(bool is_final, bool go_back, std::string output, std::map<char, Transition> transitions)
        : is_final { is_final }
        , go_back { go_back }
        , output { output }
        , transitions { transitions }
    {
    }

    State(std::string output, std::map<char, Transition> transitions)
        : is_final { false }
        , go_back { false }
        , output { output }
        , transitions { transitions }
    {
    }

    auto get_output() -> std::string
    {
        return output;
    }

    auto is_final_state() -> bool
    {
        return is_final;
    }

    auto should_go_back() -> bool
    {
        return go_back;
    }

    auto add_to_stack(const char& c) -> bool
    {
        return transitions.count(c) ? transitions[c].add_to_stack() : transitions['\0'].add_to_stack();
    }

    auto operator[](const char& c) -> unsigned int
    {
        return transitions.count(c) ? transitions[c].get_state() : transitions['\0'].get_state();
    }
};
