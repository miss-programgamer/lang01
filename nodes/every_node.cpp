#include "every_node.hpp"
#include "parser.hpp"


namespace nodes
{
	//========================================
	// class nop;
	//========================================
	
	ostream& operator<<(ostream& os, const nop& node)
	{
		os << "{ " << node.type << " }";
		return os;
	}
	
	//========================================
	// class program;
	//========================================
	
	program::program(any_node* parent_node, const string_view& program_name):
		basic_node(parent_node),
		program_name(program_name)
	{}
	
	context& program::parent_context()
	{ return self; }
	
	const context& program::parent_context() const
	{ return self; }
	
	ostream& operator<<(ostream& os, const program& node)
	{
		os << "{ " << node.type << ": " << node.program_name << " }";
		return os;
	}
	
	//========================================
	// class call;
	//========================================
	
	call::call(any_node* parent_node, const string_view& action_name):
		basic_node(parent_node),
		action_name(action_name)
	{}
	
	ostream& operator<<(ostream& os, const call& node)
	{
		os << "{ " << node.type << ": " << node.action_name << " }";
		return os;
	}
	
	//========================================
	// class literal;
	//========================================
	
	literal::literal(any_node* parent_node, const any_token& value):
		basic_node(parent_node),
		value(&value)
	{}
	
	ostream& operator<<(ostream& os, const literal& node)
	{
		os << "{ " << node.type << ": " << *node.value << " }";
		return os;
	}
	
	//========================================
	// class variable;
	//========================================
	
	variable::variable(any_node* parent_node, const string_view& variable_name):
		basic_node(parent_node),
		variable_name(variable_name)
	{}
	
	ostream& operator<<(ostream& os, const variable& node)
	{
		os << "{ " << node.type << ": " << node.variable_name << " }";
		return os;
	}
	
	//========================================
	// class tuple;
	//========================================
	
	ostream& operator<<(ostream& os, const tuple& node)
	{
		os << "{ " << node.type << " }";
		return os;
	}
	
	//========================================
	// class branch;
	//========================================
	
	branch::branch(any_node* parent_node, const any_token& kind):
		basic_node(parent_node),
		kind(&kind)
	{}
	
	ostream& operator<<(ostream& os, const branch& node)
	{
		os << "{ " << node.type << ": " << node.kind->content() << " }";
		return os;
	}
	
	//========================================
	// class scope;
	//========================================
	
	scope::scope(any_node* parent_node, const string_view& source_name, const vector<string_view>& source_lines):
		basic_node(parent_node),
		source_name(&source_name),
		source_lines(&source_lines)
	{}
	
	context& scope::parent_context()
	{ return self; }
	
	const context& scope::parent_context() const
	{ return self; }
	
	bool scope::fill()
	{
		return lexer::lex(*source_name, *source_lines, tokens) && parser::parse(*source_name, tokens, parent_last_child());
	}
	
	any_node* scope::parent_last_child()
	{ return parent_node->children_nodes()[parent_node->children_nodes().size() - 1]; }
	
	ostream& operator<<(ostream& os, const scope& node)
	{
		os << "{ " << node.type << " }";
		return os;
	}
}