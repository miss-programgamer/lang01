#include "any_node.hpp"


namespace nodes
{
	any_node::any_node(any_node&& other)
	{
		self = (variant&)other;
		other.children_nodes().clear();
	}
	
	any_node& any_node::operator=(any_node&& other)
	{
		self = (variant&)other;
		other.children_nodes().clear();
		return self;
	}
	
	any_node::~any_node()
	{
		for (auto child_node: children_nodes())
			delete child_node;
	}
	
	any_node* any_node::parent_node()
	{
		return visit([](auto&& node) {
			return node.parent_node;
		});
	}
	
	vector<any_node*>& any_node::children_nodes()
	{
		return *visit([](auto&& node) {
			return &node.children_nodes;
		});
	}
	
	const vector<any_node*>& any_node::children_nodes() const
	{
		return *visit([](auto&& node) {
			return &node.children_nodes;
		});
	}
	
	context& any_node::parent_context()
	{
		return *visit([](auto&& node) -> context* {
			return &node.parent_context();
		});
	}
	
	const context& any_node::parent_context() const
	{
		return *visit([](auto&& node) -> const context* {
			return &node.parent_context();
		});
	}
	
	
	static inline int nodes_index()
	{ static int index = ios_base::xalloc(); return index; }
	
	static inline long nodes_indent(ostream& os)
	{ return os.iword(nodes_index()); }
	
	static inline ostream& nodes_indent_up(ostream& os)
	{ ++os.iword(nodes_index()); return os; }
	
	static inline ostream& nodes_indent_down(ostream& os)
	{ --os.iword(nodes_index()); return os; }
	
	static inline void nodes_write_indent(ostream& os)
	{ repeat (nodes_indent(os)) { os << "  "; } }
	
	ostream& operator<<(ostream& os, const any_node& node)
	{
		node.visit([&os](auto&& node) {
			nodes_write_indent(os);
			os << node << "\n";
		});
		
		os << nodes_indent_up;
		for (auto child: node.children_nodes())
			os << *child;
		os << nodes_indent_down;
		
		return os;
	}
}