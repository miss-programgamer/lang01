#include "main.hpp"
#include "utils.hpp"
#include "tokens.hpp"
#include "nodes.hpp"


// TODO: Parse tokens into AST nodes
// TODO: Compile the AST into bytecode
// TODO: Create the VM for said bytecode


ostream& operator<<(ostream& os, const vector<any_token>& tokens)
{
    for (auto token: tokens)
    {
        cout << token << "\n";
    }
    return os;
}


int main(int argc, char* argv[])
{
    // store program name
    const string program_name = argv[0];
    
    // store arguments here
    argsview args(argc - 1, &argv[1]);
    
    if (args.size() == 0)
    {
        cout << "Starting Lang01 in REPL mode:" << endl;
        
        for (string source_text; source_text != ".exit";)
        {
            // read lines from cin
            vector<string_view> source_lines;
            cout << "> ";
            slurp(cin, source_text, source_lines);
            
            // fill vector of tokens created from cin
            vector<any_token> tokens;
            lexer lexer(program_name, source_lines);
            lexer.fill(tokens);
            
            // fill vector with nodes matched from tokens
            any_node program;
            parser parser(tokens, program_name);
            parser.fill(program);
            
            // print program nodes
            cout << tokens << "===\n";
            cout << program;
        }
        
        cout << "Goodbye!\n";
    }
    else
    {
        for (const auto source_name: args)
        {
            // read lines from a source file
            string source_text;
            vector<string_view> source_lines;
            slurp(string(source_name), source_text, source_lines);
            
            // fill vector of tokens created from that source file
            vector<any_token> tokens;
            lexer lexer(source_name, source_lines);
            lexer.fill(tokens);
            
            // fill vector with nodes matched from tokens
            any_node program;
            parser parser(tokens, source_name);
            parser.fill(program);
            
            // print program nodes
            cout << tokens << "===\n";
            cout << program;
        }
    }
    
    return 0;
}