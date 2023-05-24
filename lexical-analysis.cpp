#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>
#include <sstream>
using namespace std;
 
 
class Atomation {
private:
    string tokens;  // recognized characters
    bool endsWith[3] = { false, false, false };
    set<string> s = { "+", "-", "*", "/", ";", ",", "(", ")", "{", "}" };
 
    unordered_map<string, int> symbolTable = {
        {"main", 0}, {"int", 1}, {"if", 2}, {"else", 3}, {"while", 4}, {"do", 5},
        {"for", 6}, {"long", 7}, {"bool", 8}, {"<", 9}, {">", 10}, {"=", 11},
        {";", 12}, {",", 13}, {"<=", 14}, {">=", 15}, {"==", 16}, {"!=", 17},
        {"+", 18}, {"-", 19}, {"*", 20}, {"/", 21}, {"(", 22}, {")", 23}, {"{", 24},
        {"}", 25}, {"digit", 26}, {"string", 27}, {"return", 28}, {"false", 29}, {"true", 30},
    };
 
    unordered_map<string, vector<string> > table  = {
        { "start", { "start", "end", "in_letter", "in_digit", "<", ">", "=", "!", "error" } },
        { "in_letter", { "in_letter", "end" } },
        { "in_digit", { "in_digit", "end" } },
        { "<", { "end", "error" } },
        { ">", { "end", "error" } },
        { "=", { "end", "error" } },
        { "!", { "end", "error" } },
    };
 
    unordered_map<string, int> ends = {
        { ";", 0 }, { ")", 1 }, { ",", 2 }
    };
 
 
    bool inSet(const string c) {
        set<string>::iterator it;
        it = find(s.begin(), s.end(), c);
        return it != s.end();
    }
 
    int getNextState(const string state, string c) {
        if (state == "start") {
            if (c == " ") return 0;
            if (inSet(c)) return 1;
            if (isalpha((int)c.front())) return 2;
            if (isdigit((int)c.front())) return 3;
            if (c == "<") return 4;
            if (c == ">") return 5;
            if (c == "=") return 6;
            if (c == "!") return 7;
            return 8;
        } else if (state == "in_letter") {
            if (isalnum((int)c.front())) return 0;
            return 1;
        } else if (state == "in_digit") {
            if (isnumber((int)c.front())) return 0;
            return 1;
        } else if (state == "<" or ">" or "=" or "!") {
            if (inSet(c)) return 1;
            return 0;
        }
    }
 
    inline void next(FILE *stdin, char *buff, string &str) {
        string next[3] = { ";", ")", "," };
        for (int i = 0; i < 3; ++i) {   // split next character {';', ',', ')'}
            if (endsWith[i]) {
                endsWith[i] = false;
                str = next[i] + " ";
                return;
            }
        }
        fscanf(stdin, "%s", buff);
        str = buff;
        string endChar(1, str.back());
        if (endChar == ";" or endChar == "," or endChar == ")") {
            endsWith[ends[endChar]] = true;
            str.pop_back();
        }
        str.append(" ");    // add a endding character
    }

public:
    void run(FILE *stdin, FILE *stdout) {
        string state = "start";
        char buff[256];
        string str;
        next(stdin, buff, str);
        while (str != "# ") {
            for (char s : str) {
                string c(1, s);
 
                if (c != " ") tokens.append(c);
                state = table[state][getNextState(state, c)];
 
                if (state == "error") {
                    printf("Error occurs at %s\n", tokens.c_str());
                    fprintf(stdout, "Error occurs at %s\n", tokens.c_str());
                    exit(1);
                }
 
                if (state == "end") {
                    int id = symbolTable[tokens];
                    if (!id and tokens != "main") {  // digit or letter
                        stringstream ss;
                        ss << tokens;
                        int d;
                        id = (ss >> d) ? 26 : 27;   // test whether id is a number
                    }
                    string output = "( '" + tokens + "', " + to_string(id) + " )";
                    fprintf(stdout, "%s\n", output.c_str());
                    tokens.clear();
                    state = "start";
                }
            }
            next(stdin, buff, str);
        }
    }
};
 
 
void document() {
    printf("\n======================= Lexical analysis ========================\n");
    printf("➤ Author: AaronComo\n");
    printf("➤ NOTE: Please type a SPACE after function name in your testcase.\n");
    printf("        e.g. int main () { ... }\n");
    printf("➤ Compile: g++ -g -std=c++11 lexical-analysis.cpp\n");
    printf("➤ Input format: ./a.out <inputfile> <outputfile>\n");
    printf("==================================================================\n\n");
}
 
 
int main(int argc, char *argv[]) {
    if (argc < 3) {
        document();
        return 0;
    }
    printf("Input  file:\t%s\n", argv[1]);
    printf("Output file:\t%s\n", argv[2]);
    FILE *stdin = fopen(argv[1], "r");
    FILE *stdout = fopen(argv[2], "w");
    Atomation *atom = new Atomation();
    atom->run(stdin, stdout);
    fclose(stdin);
    fclose(stdout);
    delete atom;
    printf("Done! See %s for details.\n", argv[2]);
    return 0;
}
 
