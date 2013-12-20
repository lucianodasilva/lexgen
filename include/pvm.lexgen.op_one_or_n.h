#ifndef _pvm_lexgen_op_one_or_n_h_
#define _pvm_lexgen_op_one_or_n_h_

#include "pvm.lexgen.base.h"

namespace pvm {
	namespace lexgen {

		struct one_or_n_parser {

			template <
				class this_type,
				class cxt_type,
				class trn_type
			>
			inline static bool parse (this_type & this_inst, cxt_type & cxt, trn_type & transport) {
				cxt_type nc = cxt;

				bool one_valid = this_inst.exp.parse (nc, transport);

				if (one_valid) {
					cxt = nc;
					while (this_inst.exp.parse (nc, transport)) { cxt = nc; }
				}

				return one_valid;
			}

		};

		template < class exp_type >
		using one_or_n = unary_oper <
			exp_type,
			one_or_n_parser
		>;

		template < class rh_t >
		inline one_or_n < rh_t > operator + (const rh_t & r) {
			return one_or_n < rh_t > (r);
		}

	}
}

#endif
