#ifndef _pvm_lexgen_op_zero_or_n_h_
#define _pvm_lexgen_op_zero_or_n_h_

#include "pvm.lexgen.base.h"

namespace pvm {
	namespace lexgen {

		struct zero_or_n_parser {

			template <
				class this_type,
				class cxt_type,
				class trn_type
			>
			inline static bool parse (this_type & this_inst, cxt_type & cxt, trn_type & transport) {
				cxt_type nc = cxt;
				while (this_inst.exp.parse (nc, transport)) { cxt = nc; }

				return true;
			}

		};

		template < class exp_type >
		using zero_or_n = unary_oper <
			exp_type,
			zero_or_n_parser
		>;

		template < class exp_type >
		inline zero_or_n < exp_type > operator * (const exp_type & r) {
			return zero_or_n < exp_type > (r);
		}

	}
}

#endif
