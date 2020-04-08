#include "main.hpp"
#include "utils.hpp"
#include "tokens.hpp"


void main(int argc, char* argv[])
{
    // store program name
    const string program_name = argv[0];
    
    // store arguments here
    argsview args(argc - 1, &argv[1]);
    
    if (args.size() == 0)
    {
        // signal repl mode
        cout << "Starting Lang01 in REPL mode:" << endl;
        
        // TODO: implement repl mode
        string source_text;
        
        do
        {
            // fill source text with console input
            slurp(cin, source_text);
            
            // create token stream from source name and text
            tokenizer tokenizer(program_name, source_text);
            
            // create array of tokens
            vector<any_token> tokens;
            for (any_token token; tokenizer.next(token, token_flags::ONLY_SEMANTIC);)
                tokens.push_back(token);
            
            // print tokens
            for (auto token: tokens) {
                cout << token << endl;
            }
        }
        while (source_text != ".exit");
        
        cout << "Goodbye!" << endl;
    }
    else if (args.size() == 1)
    {
        // use the given argument as a filename for finding the source text
        const auto source_name = string(args[0]);
        
        // create and fill source text string
        string source_text;
        slurp(source_name, source_text);
        
        // create token stream from source name and text
        tokenizer tokenizer(source_name, source_text);
        
        // create array of tokens
        vector<any_token> tokens;
        any_token token;
        while (tokenizer.next(token, token_flags::ONLY_SEMANTIC))
            tokens.push_back(token);
        
        // print tokens
        for (auto token: tokens) {
            cout << token << endl;
        }
        
        cout << "done" << endl;
    }
    else
    {
        // we can only run a program when we have a single argument
        cout << "Lang01 takes exactly one argument; the name of a file to run." << endl;
    }
}