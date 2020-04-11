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
            // fill vector with tokens matched from console input
            slurp(cin, source_text);
            vector<any_token> tokens;
            tokenizer tokenizer(program_name, source_text);
            tokenizer.fill(tokens, token_flags::ONLY_SEMANTIC);
            
            // fill vector with nodes matched from tokens
            any_node program;
            parser parser(tokens, program_name);
            parser.fill(program);
            
            // print program nodes
            cout << tokens << "\n";
            cout << program;
        }
        
        cout << "Goodbye!\n";
    }
    else
    {
        string source_text;
        for (const auto source_name: args)
        {
            // fill vector of tokens created from a source file
            slurp(string(source_name), source_text);
            vector<any_token> tokens;
            tokenizer tokenizer(source_name, source_text);
            tokenizer.fill(tokens, token_flags::ONLY_SEMANTIC);
            
            // fill vector with nodes matched from tokens
            any_node program;
            parser parser(tokens, source_name);
            parser.fill(program);
            
            // print program nodes
            cout << tokens << "\n";
            cout << program;
        }
    }
    
    return 0;
}