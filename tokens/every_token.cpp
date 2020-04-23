#include "every_token.hpp"
#include "../utils.hpp"


static constexpr style type_styl("36");
static constexpr style content_styl("33");


namespace tokens
{
	empty::empty() noexcept:
		basic_token("", 0, -1, 0)
	{}
	
	ostream& operator<<(ostream& os, const empty& token)
	{
		os << "[" << type_styl << token.type << style::reset
			<< " Ln " << token.lineno << ", Lvl " << token.lineindent << ", Ld " << token.leading_space << "]";
		return os;
	}
	
	ostream& operator<<(ostream& os, const upline& token)
	{
		os << "[" << type_styl << token.type << style::reset << " - " << content_styl;
		
		size_t tab_count = 0;
		while (token.content()[tab_count] == '\t') {
			tab_count++;
			cout << "\\t";
		}
		
		if (token.has_linefeed()) {
			cout << token.content().substr(tab_count).substr(0, token.content().size() - 1) << "\\n" << style::reset
				<< " Ln " << token.lineno << ", Lvl " << token.lineindent << ", Ld " << token.leading_space << "]";
		} else {
			cout << token.content().substr(tab_count) << style::reset
				<< " Ln " << token.lineno << ", Lvl " << token.lineindent << ", Ld " << token.leading_space << "]";
		}
		return os;
	}
	
	ostream& operator<<(ostream& os, const newline& token)
	{
		if (token.has_comment()) {
			if (token.has_linefeed()) {
				os << "[" << type_styl << "comment" << style::reset << " - " << content_styl << token.content().substr(0, token.content().size() - 1) << "\\n" << style::reset
					<< " Ln " << token.lineno << ", Lvl " << token.lineindent << ", Ld " << token.leading_space << "]";
			} else {
				os << "[" << type_styl << "comment" << style::reset << " - " << content_styl << token.content() << style::reset
					<< " Ln " << token.lineno << ", Lvl " << token.lineindent << ", Ld " << token.leading_space << "]";
			}
		} else {
			os << "[" << type_styl << token.type << style::reset
				<< " Ln " << token.lineno << ", Lvl " << token.lineindent << ", Ld " << token.leading_space << "]";
		}
		return os;
	}
	
	ostream& operator<<(ostream& os, const identifier& token)
	{
		os << "[" << type_styl << token.type << style::reset << " - " << content_styl << token.content() << style::reset
			<< " Ln " << token.lineno << ", Lvl " << token.lineindent << ", Ld " << token.leading_space << "]";
		return os;
	}
	
	ostream& operator<<(ostream& os, const numeric& token)
	{
		os << "[" << type_styl << token.type << style::reset << " - " << content_styl << token.content() << style::reset
			<< " Ln " << token.lineno << ", Lvl " << token.lineindent << ", Ld " << token.leading_space << "]";
		return os;
	}
	
	ostream& operator<<(ostream& os, const quoted_string& token)
	{
		os << "[" << type_styl << token.type << style::reset << " - " << content_styl << token.content() << style::reset
			<< " Ln " << token.lineno << ", Lvl " << token.lineindent << ", Ld " << token.leading_space << "]";
		return os;
	}
	
	ostream& operator<<(ostream& os, const short_string& token)
	{
		os << "[" << type_styl << token.type << style::reset << " - " << content_styl << token.content() << style::reset
			<< " Ln " << token.lineno << ", Lvl " << token.lineindent << ", Ld " << token.leading_space << "]";
		return os;
	}
	
	ostream& operator<<(ostream& os, const delimiter& token)
	{
		os << "[" << type_styl << token.type << style::reset << " - " << content_styl << token.content() << style::reset
			<< " Ln " << token.lineno << ", Lvl " << token.lineindent << ", Ld " << token.leading_space << "]";
		return os;
	}
	
	ostream& operator<<(ostream& os, const operator_t& token)
	{
		os << "[" << type_styl << token.type << style::reset << " - " << content_styl << token.content() << style::reset
			<< " Ln " << token.lineno << ", Lvl " << token.lineindent << ", Ld " << token.leading_space << "]";
		return os;
	}
	
	ostream& operator<<(ostream& os, const invalid& token)
	{
		os << "[" << type_styl << token.type << style::reset << " - " << content_styl << token.content() << style::reset
			<< " Ln " << token.lineno << ", Lvl " << token.lineindent << ", Ld " << token.leading_space << "]";
		return os;
	}
}