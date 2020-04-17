#ifndef HEADER_NODES_CONTEXT_DEFINED
#define HEADER_NODES_CONTEXT_DEFINED


#include "../main.hpp"
#include "../tokens.hpp"


namespace nodes
{
	// The set of roles that a keyword or operator can have.
	enum class role
	{
		UNDEFINED, // An identifier or operator that has not been defined.
		KEYWORD,   // An identifier that refers to a keyword.
		VARIABLE,  // An identifier that refers to a variable.
		FUNCTION,  // An identifier that refers to a function.
		OPERATOR,  // An operator that has been defined and given an oprole.
		TYPE,      // An identifier that refers to a type.
	};
	
	// The set of subroles that an operator can have.
	enum class oprole: unsigned
	{
		NONE   = 0, // The operator has no assigned role.
		PREFIX = 1, // The operator can be matched in unary prefix expressions.
		SUFFIX = 2, // The operator can be matched in unary suffix expressions.
		BINARY = 4  // The operator can be matched in binary expressions.
	};
	
	// Combines two oproles into one value.
	inline oprole operator|(oprole lhs, oprole rhs)
	{ return oprole(unsigned(lhs) | unsigned(rhs)); }
	
	// Combines two oproles into the left hand variable.
	inline oprole operator|=(oprole& lhs, oprole rhs)
	{ lhs = oprole(unsigned(lhs) | unsigned(rhs)); return lhs; }
	
	// Checks if the two set of optoles intersect.
	inline bool operator&&(oprole lhs, oprole rhs)
	{ return (unsigned(lhs) & unsigned(rhs)) != 0u; }
	
	// The set of subroles that a keyword can have.
	enum class keyrole
	{
		NONE,  // The keyword either has no assigned role.
		CONST, // A keyword that represents a constant value.
		TRIP,  // A keyword that merely supports the syntax of the language.
		FLOW,  // For matching expressions that change the flow of the program.
		DEFINE // For matching expressions that extend the current context.
	};
	
	// Holds contextual data used to determine which identifiers
	// and operators are defined and what roles they have.
	class context
	{
	protected:
		map<string, role> roles;
		
		map<string, oprole> oproles;
		
		map<string, keyrole> keyroles;
		
	public:
		// Define an identifier or operator with the given role.
		bool define(const string_view& definition, role def_role);
		
		// Define an operator with the given oprole.
		bool define_op(const string_view& definition, oprole op_role);
		
		// Define a keyword with the given keyrole.
		bool define_keyword(const string_view& definition, keyrole key_role);
		
		// Undefine an identifier or operator.
		bool undefine(const string_view& definition);
		
		
		// Returns the role of the given identifier or operator.
		role get_role(const string_view& definition) const;
		
		// Returns the oprole of the given operator.
		oprole get_oprole(const string_view& definition) const;
		
		// Returns the keyrole of the given keyword.
		keyrole get_keyrole(const string_view& definition) const;
		
		
		// Checks if the given identifier or operator has the given role.
		bool holds_role(const any_token& token, role def_role) const;
		
		// Checks if the given identifier or operator has the given role.
		bool holds_any_role(const any_token& token, initializer_list<role> def_roles) const;
		
		// Checks if the given identifier intersects the given set oprole.
		bool holds_oprole(const any_token& token, oprole op_role) const;
		
		// Checks if the given identifier has the given keyrole.
		bool holds_keyrole(const any_token& token, keyrole keyrole) const;
	};
}


#else // HEADER_NODES_CONTEXT_DEFINED


namespace nodes
{
	class context;
}


#endif // HEADER_NODES_CONTEXT_DEFINED