#ifndef _pvm_lexgen_op_alternation_h_
#define _pvm_lexgen_op_alternation_h_

#include "pvm.lexgen.base.h"

namespace pvm {
	namespace lexgen {

		struct alternation_parser {

			template <
				class this_type,
				class cxt_type,
				class trn_type
			>
			inline static bool parse (this_type & this_inst, cxt_type & cxt, trn_type & transport) {
				cxt_type nc = cxt;

				bool valid = this_inst.left.parse (nc, transport);

				if (valid)
					cxt = nc;
				else {
					valid = this_inst.right.parse (nc, transport);
					if (valid)
						cxt = nc;
				}

				return valid;
			}

		};

		template < class lhe_type, class rhe_type >
		using alternation = binary_oper <
			lhe_type,
			rhe_type,
			alternation_parser
		>;

		template < class lhe_type, class rhe_type >
		inline alternation < lhe_type, rhe_type > operator | (const lhe_type & l, const rhe_type & r) {
			return alternation < lhe_type, rhe_type > (l, r);
		}

	}
}


#endif
