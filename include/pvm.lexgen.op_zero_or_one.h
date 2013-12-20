#ifndef _pvm_lexgen_op_zero_or_one_h_
#define _pvm_lexgen_op_zero_or_one_h_

#include "pvm.lexgen.base.h"

namespace pvm {
	namespace lexgen {

		struct zero_or_one_parser {

			template <
				class this_type,
				class cxt_type,
				class trn_type
			>
			inline static bool parse (this_type & this_inst, cxt_type & cxt, trn_type & transport) {
				cxt_type nc = cxt;

				bool one_valid = this_inst.exp.parse (nc, transport);

				if (one_valid) {
					if (this_inst.exp.parse (nc, transport))
						return false;
					else
						cxt = nc;
				}

				return true;
			}

		};

		template < class exp_type >
		using zero_or_one = unary_oper <
			exp_type,
			zero_or_one_parser
		>;

		template < typename exp_type >
		inline zero_or_one < exp_type > operator - (const exp_type & e) {
			return zero_or_one < exp_type > (e);
		}

	}
}
	
#endif
