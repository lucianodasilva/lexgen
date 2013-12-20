#ifndef _pvm_lexgen_context_h_
#define _pvm_lexgen_context_h_

#include <string>

namespace pvm {
	namespace lexgen {

		template < typename stream_t >
		struct context_base {

			typedef typename stream_t::value_type		value_type;
			typedef typename stream_t::const_iterator	iterator;

			iterator cursor;
			iterator it;
			iterator end;

			inline context_base (const stream_t & in) :
				cursor (in.begin ()),
				it (cursor),
				end (in.end ()) {}

			inline context_base & operator ++ () {
				++cursor;
				return *this;
			}

			inline value_type operator * () {
				return *cursor;
			}

			inline stream_t consume () {
				if (it == end)
					return stream_t ();

				stream_t v (it, cursor);
				it = cursor;

				return v;
			}

			inline void ignore () {
				it = cursor;
			}

			inline void terminate () {
				it = cursor = end;
			}

			inline bool is_end () {
				return cursor == end;
			}

		};

	}
}

#endif
