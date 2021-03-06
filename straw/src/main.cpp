#include <iostream>
#include <fstream>
#include <exception>
#include <optional>
#include <string>
#include <vector>
#include <map>
#include <array>
#include <numeric>
#include <string_view>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

#include "logging.h"
#include "util.h"
//#include "parse_context.h"
#include "ast.h"
#include "parsing.h"
#include "heapsort.h"
#include "eval.h"

void execute(const string& source) {
    auto ptr = (char*)source.c_str();
    auto program = ast();
    
    if (parse_program(ptr, program)) {
        cout << "Parse succeeded" << endl;
        cout << program << endl;
    } else {
        cout << "Parse errors: " << endl;
    }

    try {
        cout << "Evaluating: " << eval(program) << endl;
    } catch (...) {
        cout << "Runtime errors" << endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        // repl mode
        // not very good, can't handle multi lines yet
        auto line = string();
        while (true) {
            if (cin.eof()) {
                break;
            }
            
            cout << "> " << flush;
            getline(cin, line);
            if (!line.length()) {
                continue;
            }
            if (line == "exit") {
                break;
            }
            execute(line);
        }
    } else {
        // source file mode
        auto fname = argv[1];
        cout << "Loading: " << fname << endl;
        auto data = read_text_file(fname);
        cout << "Data: {" << data << "}" << endl;
        execute(data);
    }
    
    return 0;
}