#ifndef _pvm_lexgen_scan_string_h_
#define _pvm_lexgen_scan_string_h_

#include "pvm.lexgen.base.h"
#include "pvm.lexgen.scan.h"

#include <locale>
#include <string>

namespace pvm {
	namespace lexgen {

		namespace text {

			using context = lexgen::context_base < std::string >;

			inline bool _is_alpha (context & cxt) {
				return std::isalpha (*cxt, std::locale ());
			}

			inline bool _is_alpha_num (context & cxt) {
				return std::isalnum (*cxt, std::locale ());
			}

			inline bool _is_digit (context & cxt) {
				return std::isdigit (*cxt, std::locale ());
			}

			inline bool _is_graph (context & cxt) {
				return std::isgraph (*cxt, std::locale ());
			}

			inline bool _is_not_graph (context & cxt) {
				return !std::isgraph (*cxt, std::locale ());
			}

			const unit_scanner < context, _is_alpha >		alpha;
			const unit_scanner < context, _is_alpha_num >	alnum;
			const unit_scanner < context, _is_digit >		digit;
			const unit_scanner < context, _is_graph >		graph;
			const unit_scanner < context, _is_not_graph >	n_graph;

			const unit_cmp_definition < char >				is_char;
			const sequence_cmp_definition < std::string >	is_str;

		}

	}
}

#endif