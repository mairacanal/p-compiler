#pragma once

#include <map>

#include "state.hpp"

std::map<unsigned int, State> states = {
    {0,
     {
         "",
         {
             {' ', {0, false}}, {'\t', {0, false}}, {'\n', {0, false}},
             {'{', {7, false}}, {'0', 1},           {'1', 1},
             {'2', 1},          {'3', 1},           {'4', 1},
             {'5', 1},          {'6', 1},           {'7', 1},
             {'8', 1},          {'9', 1},           {'a', 19},
             {'b', 19},         {'c', 19},          {'d', 19},
             {'e', 19},         {'f', 19},          {'g', 19},
             {'h', 19},         {'i', 19},          {'j', 19},
             {'k', 19},         {'l', 19},          {'m', 19},
             {'n', 19},         {'o', 19},          {'p', 19},
             {'q', 19},         {'r', 19},          {'s', 19},
             {'t', 19},         {'u', 19},          {'v', 19},
             {'w', 19},         {'x', 19},          {'y', 19},
             {'z', 19},         {'A', 19},          {'B', 19},
             {'C', 19},         {'D', 19},          {'E', 19},
             {'F', 19},         {'G', 19},          {'H', 19},
             {'I', 19},         {'J', 19},          {'K', 19},
             {'L', 19},         {'M', 19},          {'N', 19},
             {'O', 19},         {'P', 19},          {'Q', 19},
             {'R', 19},         {'S', 19},          {'T', 19},
             {'U', 19},         {'V', 19},          {'W', 19},
             {'X', 19},         {'Y', 19},          {'Z', 19},
             {'+', 26},         {'-', 26},          {':', 9},
             {'>', 10},         {'<', 11},          {'/', 21},
             {'*', 22},         {';', 34},
         },
     }},

    {1,
     {"",
      {
          {'0', 1},  {'1', 1},   {'2', 1},   {'3', 1}, {'4', 1},  {'5', 1},
          {'6', 1},  {'7', 1},   {'8', 1},   {'9', 1}, {'a', 2},  {'b', 2},
          {'c', 2},  {'d', 2},   {'e', 2},   {'f', 2}, {'g', 2},  {'h', 2},
          {'i', 2},  {'j', 2},   {'k', 2},   {'l', 2}, {'m', 2},  {'n', 2},
          {'o', 2},  {'p', 2},   {'q', 2},   {'r', 2}, {'s', 2},  {'t', 2},
          {'u', 2},  {'v', 2},   {'w', 2},   {'x', 2}, {'y', 2},  {'z', 2},
          {'A', 2},  {'B', 2},   {'C', 2},   {'D', 2}, {'E', 2},  {'F', 2},
          {'G', 2},  {'H', 2},   {'I', 2},   {'J', 2}, {'K', 2},  {'L', 2},
          {'M', 2},  {'N', 2},   {'O', 2},   {'P', 2}, {'Q', 2},  {'R', 2},
          {'S', 2},  {'T', 2},   {'U', 2},   {'V', 2}, {'W', 2},  {'X', 2},
          {'Y', 2},  {'Z', 2},   {'\0', 4},  {'.', 4}, {'+', 23}, {'-', 23},
          {' ', 24}, {'\t', 24}, {'\n', 24},
      }}},

    {2, {true, false, "error_number", {}}},

    {3, {true, false, "integer_number", {}}},

    {4,
     {"",
      {
          {'0', 5},
          {'1', 5},
          {'2', 5},
          {'3', 5},
          {'4', 5},
          {'5', 5},
          {'6', 5},
          {'7', 5},
          {'8', 5},
          {'9', 5},
          {'\0', 2},
      }}},
    {5,
     {"",
      {
          {'0', 5},
          {'1', 5},
          {'2', 5},
          {'3', 5},
          {'4', 5},
          {'5', 5},
          {'6', 5},
          {'7', 5},
          {'8', 5},
          {'9', 5},
          {'\0', 6},
          {' ',{7, false}},
          {'\t',{7, false}},
          {'\n',{7, false}},

      }}},
    
    {6,
     {"real_number",
      {
        {'+', 29},
        {'-', 29},
      }}},


    {7,
     {"",
      {
          {'}', {0, false}},
          {'\n', {8, false}},
          {'\0', {7, false}},
      }}},

    {8, {"comment_error"{}}},

    {9
     {" ",
        {
          {'=', 17},
          {'\0', 18},

     }}},

    {10, 
     {" " 
        { 
            {'\0', 13},
            {'=', 14},

        }}},

    {11, 
     {" " 
        { 
            {'\0', 12},
            {'=', 15},
            {'>', 16},


        }}},

    {12, {"lesser", {}}},

    {13, {"greater", {}}},

    {14, {"greater_equal", {}}},

    {15, {"lesser_equal", {}}},

    {16, {"diff", {}}},

    {17, {"attribution", {}}},

    {18, {"type_attribution", {}}},

    {19,
     {"",
      {
          {'0', 1},  {'1', 1},  {'2', 1},  {'3', 1},   {'4', 1},  {'5', 1},
          {'6', 1},  {'7', 1},  {'8', 1},  {'9', 1},   {'a', 19}, {'b', 19},
          {'c', 19}, {'d', 19}, {'e', 19}, {'f', 19},  {'g', 19}, {'h', 19},
          {'i', 19}, {'j', 19}, {'k', 19}, {'l', 19},  {'m', 19}, {'n', 19},
          {'o', 19}, {'p', 19}, {'q', 19}, {'r', 19},  {'s', 19}, {'t', 19},
          {'u', 19}, {'v', 19}, {'w', 19}, {'x', 19},  {'y', 19}, {'z', 19},
          {'A', 19}, {'B', 19}, {'C', 19}, {'D', 19},  {'E', 19}, {'F', 19},
          {'G', 19}, {'H', 19}, {'I', 19}, {'J', 19},  {'K', 19}, {'L', 19},
          {'M', 19}, {'N', 19}, {'O', 19}, {'P', 19},  {'Q', 19}, {'R', 19},
          {'S', 19}, {'T', 19}, {'U', 19}, {'V', 19},  {'W', 19}, {'X', 19},
          {'Y', 19}, {'Z', 19}, {'_', 19}, {'\0', 20},
      }}},
    {20, {true, true, "id", {}}},
    
    {21, {"divide", {}}},

    {22, {"multiply", {}}},

    {23, 
     {"integer_number", 
      {
        {'\0', 28}
    }}},

    {24, 
     {"integer_number", 
      { {' ', 25},
        {'\t', 25}
        {'\n', 25}
        {'-', 28},
        {'+', 28}
    }}},

    {25, 
     {" ", 
      { {' ', 25},
        {'\t', 25}
        {'\n', 25}
        {'-', 28},
        {'+', 28}
    }}},
    
    {26, {"signal", {}}},

    {27, 
     {"real_number", 
      { {' ', 25},
        {'\t', 25}
        {'\n', 25}
        {'-', 28},
        {'+', 28}
    }}},

    {28, {"plus_minus_operation", {}}},

    {29, {"signal", {}}},    
    


    {34, {true, false, "simb_pv", {}}},
};
