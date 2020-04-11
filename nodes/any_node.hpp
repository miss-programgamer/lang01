#ifndef HEADER_NODES_ANY_NODE_DEFINED
#define HEADER_NODES_ANY_NODE_DEFINED


#include "../main.hpp"
#include "basic_node.hpp"
#include "no_op.hpp"
#include "program_decl.hpp"
#include "call_op.hpp"


// Comma-separated list of all valid node types
#define NODES_EVERY no_op, program_decl, call_op

// Comma-separated list of all nodes that can be matched
#define NODES_MATCHABLE program_decl, call_op


namespace nodes
{
	class any_node: protected variant<NODES_EVERY>
	{
	public:
		using variant::variant;
		
		using variant::operator=;
		
		using variant::emplace;
		
		~any_node();
		
		/**
		 * Checks if this holds any of the given node type.
		 */
		template<typename... T>
		constexpr bool holds() const
		{ return (holds_alternative<T>(self) || ...); }
		
		/**
		 * Applies the given visitor object to the held node.
		 */
		template<typename V>
		decltype(auto) visit(V&& visitor)
		{ return std::visit(visitor, (variant&)self); }
		
		/**
		 * Applies the given visitor object to the held node.
		 */
		template<typename V>
		decltype(auto) visit(V&& visitor) const
		{ return std::visit(visitor, (const variant&)self); }
		
		/**
		 * Constructs and inserts a node as the last child of this node.
		 */
		template<typename N, typename... A>
		any_node* emplace_child(A&&... args)
		{
			any_node* node = new any_node();
			node->emplace<N>(this, std::forward<A>(args)...);
			children_nodes().push_back(node);
			return node; // TODO: change this to return the emplaced type
		}
		
		/**
		 * Returns a pointer to the parent node if there is one.
		 */
		any_node* parent_node();
		
		/**
		 * Returns a reference to the vector of children nodes
		 */
		vector<any_node*>& children_nodes();
		
		/**
		 * Returns a reference to the vector of children nodes
		 */
		const vector<any_node*>& children_nodes() const;
		
		friend ostream& operator<<(ostream& os, const any_node& node);
	};
}


#else // HEADER_NODES_ANY_NODE_DEFINED


namespace nodes
{
	class any_node;
}


#endif // HEADER_NODES_ANY_NODE_DEFINED