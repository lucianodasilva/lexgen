#ifndef _pvm_lexgen_base_h_
#define _pvm_lexgen_base_h_

#include "pvm.lexgen.context.h"

// decorated name blah blah blah
#pragma warning(disable : 4503)

namespace pvm {
	namespace lexgen {

		template < typename exp_type, typename callback_type >
		struct action {

			typedef action < exp_type, callback_type > this_type;

			exp_type		exp;
			callback_type	callback;

			inline action (const exp_type & e, callback_type call) : exp (e), callback (call) {}

			template <
				class cxt_type,
				class trn_type
			>
			inline bool parse (cxt_type & cxt, trn_type & transport) const {
				if (exp.parse (cxt, transport)) {
					callback (cxt, transport);
					return true;
				} else
					return false;
			}

				inline action < this_type, callback_type > operator [] (callback_type callback) const {
					return action < this_type, callback_type > (*this, callback);
				}

		};

		template <
			class exp_type,
			class prs_type
		>
		struct unary_oper {

			using this_type = unary_oper < exp_type, prs_type>;

			template < class callback_type >
			using unary_action = action < this_type, callback_type >;

			exp_type exp;

			inline unary_oper (const exp_type & e) : exp (e) {}

			template < class callback_type >
			inline unary_action < callback_type > operator [] (callback_type callback) const {
				return unary_action < callback_type > (*this, callback);
			}

			template < class cxt_type, class trn_type>
			inline bool parse (cxt_type & cxt, trn_type & transport) const {
				return prs_type::parse (*this, cxt, transport);
			}

		};

		template <
			class lhe_type,	// left hand expression
			class rhe_type, // right hand expression
			class prs_type
		>
		struct binary_oper {

			using this_type = binary_oper < lhe_type, rhe_type, prs_type>;

			template < class callback_type >
			using binary_action = action < this_type, callback_type >;

			lhe_type left;
			rhe_type right;

			inline binary_oper (const lhe_type & l, const rhe_type & r) : left (l), right (r) {}

			template < class callback_type >
			inline binary_action < callback_type > operator [] (callback_type callback) const {
				return binary_action < callback_type > (*this, callback);
			}

			template < class cxt_type, class trn_type>
			inline bool parse (cxt_type & cxt, trn_type & transport) const {
				return prs_type::parse (*this, cxt, transport);
			}

		};

	}
}
	

#endif