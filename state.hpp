#pragma once

#include <map>
#include <string>

class State {
private:
    unsigned int state;
    bool is_final;
    bool go_back;
    std::string output;
    std::map<char, unsigned int> transitions;

public:
    State()
    {
        state = 0;
        is_final = false;
        is_final = false;
        output = "";
        transitions = std::map<char, unsigned int> {};
    }

    State(unsigned int state, bool is_final, bool go_back, std::string output, std::map<char, unsigned int> transitions)
        : state { state }
        , is_final { is_final }
        , go_back { go_back }
        , output { output }
        , transitions { transitions }
    {
    }

    auto get_state() -> unsigned int
    {
        return state;
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

    auto operator[](const char& c) -> unsigned int
    {
        return transitions.count(c) ? transitions[c] : transitions['\0'];
    }
};
