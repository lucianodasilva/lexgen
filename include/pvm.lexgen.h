#ifndef _pvm_lexgen_h_
#define _pvm_lexgen_h_

#include "pvm.lexgen.base.h"
#include "pvm.lexgen.context.h"
#include "pvm.lexgen.op_alternation.h"
#include "pvm.lexgen.op_one_or_n.h"
#include "pvm.lexgen.op_sequence.h"
#include "pvm.lexgen.op_zero_or_n.h"
#include "pvm.lexgen.op_zero_or_one.h"
#include "pvm.lexgen.scan.h"
#include "pvm.lexgen.scan.text.h"

namespace pvm {
	namespace lexgen {

		template < class exp_type, class stream_type, class trn_type >
		inline bool parse (exp_type & exp, stream_type & source, trn_type & transport) {
			context_base < stream_type > cxt (source);
			return exp.parse (cxt, transport);
		}

		template < class exp_type, class trn_type >
		inline bool parse (exp_type & exp, std::string & source, trn_type & transport) {
			text::context cxt (source);
			return exp.parse (cxt, transport);
		}

	}
}

#endif