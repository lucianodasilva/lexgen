#ifndef _pvm_lexgen_scan_h_
#define _pvm_lexgen_scan_h_

#include "pvm.lexgen.base.h"

namespace pvm {
	namespace lexgen {

		template < class cxt_type, bool eval_method (cxt_type &)>
		struct unit_scanner {

			typedef unit_scanner < cxt_type, eval_method > this_type;

			inline unit_scanner () {}

			template < class trn_type >
			inline bool parse (cxt_type & cxt, trn_type & transport) const {
				if (cxt.is_end ())
					return false;

				if (eval_method (cxt)) {
					++cxt;
					return true;
				} else
					return false;
			}

			template < class callback_type >
			inline action < this_type, callback_type > operator [] (callback_type callback) const {
				return action < this_type, callback_type > (*this, callback);
			}

		};

		template < class value_type >
		inline bool unit_cmp_default (const value_type & v1, const value_type & v2) {
			return v1 == v2;
		}

		template < class value_type, bool cmp_method (const value_type &, const value_type &) >
		struct unit_cmp_scanner {

			typedef unit_cmp_scanner < value_type, cmp_method > this_type;

			value_type value;

			inline unit_cmp_scanner (const value_type & v) : value (v) {}

			template < class cxt_type, class trn_type >
			inline bool parse (cxt_type & cxt, trn_type & transport) const {
				if (cxt.is_end ())
					return false;

				if (cmp_method (*cxt, value)) {
					++cxt;
					return true;
				} else
					return false;
			}

			template < class callback_type >
			inline action < this_type, callback_type > operator [] (callback_type callback) const {
				return action < this_type, callback_type > (*this, callback);
			}

		};

		template < typename value_type, bool cmp_method (const value_type &, const value_type &) = unit_cmp_default < value_type > >
		struct unit_cmp_definition {

			inline unit_cmp_definition () {};

			inline unit_cmp_scanner < value_type, cmp_method > operator () (const value_type & v) const {
				return unit_cmp_scanner < value_type, cmp_method > (v);
			}
		};

		template < class stream_t >
		struct sequence_cmp_scanner {

			typedef sequence_cmp_scanner < stream_t > this_type;

			stream_t stream;

			inline sequence_cmp_scanner (const stream_t & s) : stream (s) {}

			template < class context_type, class attribute_type >
			inline bool parse (context_type & cxt, attribute_type & att) const {
				if (cxt.is_end ())
					return false;

				context_type nc = cxt;

				typename stream_t::const_iterator
					it = stream.begin (),
					end = stream.end ();

				while (it != end) {
					if (nc.is_end () || *it != *nc)
						return false;

					++it;
					++nc;
				}

				cxt = nc;

				return true;
			}

			template < class callback_type >
			inline action < this_type, callback_type > operator [] (callback_type callback) const {
				return action < this_type, callback_type > (callback, *this);
			}

		};

		template < typename stream_t >
		struct sequence_cmp_definition {

			inline sequence_cmp_definition () {}

			inline sequence_cmp_scanner < stream_t > operator () (const stream_t & s) const {
				return sequence_cmp_scanner < stream_t > (s);
			}
		};

	}
}


#endif