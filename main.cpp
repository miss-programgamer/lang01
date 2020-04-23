#include "libs.hpp"
#include "utils.hpp"
#include "tokens.hpp"
#include "nodes.hpp"


// TODO: Compile the AST into bytecode
// TODO: Create the VM for said bytecode


int main(int argc, char* argv[])
{
    // store program name
    const string program_name = argv[0];
    
    // store arguments here
    argsview args(argc - 1, &argv[1]);
    
    if (args.size() == 0)
    {
        cout << "Starting Lang01's interactive mode:\n";
        
        string_view source_name = "interactive mode";
        for (string source_text; source_text != "exit";)
        {
            // read lines from cin
            vector<string_view> source_lines;
            cout << "> ";
            slurp(cin, source_text, source_lines);
            
            // transform source text into node tree
            vector<any_token> tokens;
            any_node root = program(nullptr, source_name);
            lexer::lex(source_name, source_lines, tokens);
            parser::parse(source_name, tokens, &root);
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
            
            // transform source text into node tree
            vector<any_token> tokens;
            any_node root = program(nullptr, source_name);
            lexer::lex(source_name, source_lines, tokens);
            parser::parse(source_name, tokens, &root);
        }
    }
    
    return 0;
}