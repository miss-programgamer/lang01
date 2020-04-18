#include "context.hpp"


namespace nodes
{
	bool context::define(const string_view& def, role def_role)
	{
		if (def_role == role::UNDEFINED)
			return undefine(def);
		
		roles[string(def)] = def_role;
		return true;
	}
	
	bool context::define_op(const string_view& def, oprole op_role)
	{
		if (op_role == oprole::NONE)
			return false;
		
		roles[string(def)] = role::OPERATOR;
		oproles[string(def)] |= op_role;
		return true;
	}
	
	bool context::define_keyword(const string_view& def, keyrole key_role)
	{
		if (key_role == keyrole::NONE)
			return false;
		
		roles[string(def)] = role::KEYWORD;
		keyroles[string(def)] = key_role;
		return true;
	}
	
	bool context::undefine(const string_view& def)
	{
		if (auto it = roles.find(string(def)); it != roles.end())
		{
			oproles.erase(string(def));
			keyroles.erase(string(def));
			roles.erase(it);
			return true;
		}
		
		return false;
	}
	
	role context::get_role(const string_view& def) const
	{
		if (auto it = roles.find(string(def)); it != roles.end())
			return it->second;
		
		return role::UNDEFINED;
	}
	
	oprole context::get_oprole(const string_view& def) const
	{
		if (auto it = oproles.find(string(def)); it != oproles.end())
			return it->second;
		
		return oprole::NONE;
	}
	
	keyrole context::get_keyrole(const string_view& def) const
	{
		if (auto it = keyroles.find(string(def)); it != keyroles.end())
			return it->second;
		
		return keyrole::NONE;
	}
	
	bool context::holds_role(const any_token& token, role def_role) const
	{
		return token.holds<identifier, operator_t>() && get_role(token.content()) == def_role;
	}
	
	bool context::holds_any_role(const any_token& token, initializer_list<role> def_roles) const
	{
		if (!token.holds<identifier, operator_t>())
			return false;
		
		role token_role = get_role(token.content());
		for (auto def_role: def_roles)
			if (def_role == token_role)
				return true;
		
		return false;
	}
	
	bool context::holds_oprole(const any_token& token, oprole op_role) const
	{
		return token.holds<operator_t>() && (get_oprole(token.content()) && op_role);
	}
	
	bool context::holds_keyrole(const any_token& token, keyrole key_role) const
	{
		return token.holds<identifier>() && get_keyrole(token.content()) == key_role;
	}
}