#include <pvm.lexgen.h>

#include <cinttypes>
#include <string>
#include <vector>

enum token_type : unsigned int {
	
	token_none				= 0x0,

	token_literal			= 0x1000,

	token_op				= 0x2000,

	token_math_op			= token_op | 0x2,
	token_op_add			= token_math_op | 0x4,
	token_op_sub			= token_math_op | 0x8,
	token_op_mlt			= token_math_op | 0x10,
	token_op_div			= token_math_op | 0x20,

	token_op_bracket_open	= token_op | 0x40,
	token_op_bracket_close	= token_op | 0x80,
};

struct token {

	token_type		type;
	std::string		text;

	inline token () : type (token_none) {}

	inline token (token_type t) :  type (t) {}
	inline token (token_type t, const std::string & s) : type (t), text (s) {}

	inline bool operator == (token & v) {
		return type == v.type;
	}

	inline operator token_type () {
		return type;
	}
};

typedef std::vector < token > token_transport;

namespace tokenizer {

	using namespace pvm::lexgen::text;

	inline void ignore (context & cxt, token_transport & transport) { cxt.ignore (); };

	inline void add_literal (context & cxt, token_transport & transport) {
		transport.push_back (token (token_literal, cxt.consume ()));
	};

	inline void add_math_op (context & cxt, token_transport & transport) {

		std::string c_val = cxt.consume ();
		token_type t;

		if (c_val == "+")
			t = token_op_add;
		else if (c_val == "-")
			t = token_op_sub;
		else if (c_val == "/")
			t = token_op_div;
		else if (c_val == "*")
			t = token_op_mlt;
		else
			throw "invalid stuffs";

		transport.push_back (token (t));
	};

	inline void add_open_bracket (context & cxt, token_transport & transport) {
		cxt.consume ();
		transport.push_back (token (token_op_bracket_open));
	};

	inline void add_close_bracket (context & cxt, token_transport & transport) {
		cxt.consume ();
		transport.push_back (token (token_op_bracket_close));
	};

	const auto e_literal = -is_char ('-') >> (
		(+digit >> -is_char ('.') >> *digit) |	// [0..9]+ '.'? [0..9]*
		(-is_char ('.') >> +digit)				// '.' [0..9]+
		);

	const auto e_identifier =
		is_char ('_') >>
		+(alnum | is_char ('_')) |
		(alpha >> *(alnum | is_char ('_')))
		;

	const auto e_math_op =
		is_char ('+') | is_char ('-') | is_char ('*') | is_char ('/');

	const auto e_open_braket =
		is_char ('(');

	const auto e_close_braket =
		is_char (')');

	const auto e_token =
	(
		e_literal			[add_literal] |
		e_math_op			[add_math_op] |
		e_open_braket		[add_open_bracket] |
		e_close_braket		[add_close_bracket]
	);

	const auto e_null_char =
		(*n_graph) [ignore];

	const auto expression =
		*(e_null_char >> e_token);
}

int main (int arg_c, char **arg_v) {

	std::string source = "1 + 2 * 3";

	token_transport output;

	pvm::lexgen::parse (tokenizer::expression, source, output);

}