/*
 * Sux: Succinct data structures
 *
 * Copyright (C) 2019 Stefano Marchini
 *
 *  This library is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU Lesser General Public License as published by the Free
 *  Software Foundation; either version 3 of the License, or (at your option)
 *  any later version.
 *
 *  This library is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include "../../Rank.hpp"
#include "../../Select.hpp"
#include "../../SelectZero.hpp"
#include "../../common.hpp"
#include "../DArray.hpp"

namespace sux::ranking {

/** An interface for all classes implementating dynamic bitvectors.
 *
 * Each RankSelect is serializable and deserializable with:
 * - friend std::ostream &operator<<(std::ostream &os, const FenwickTree &ft);
 * - friend std::istream &operator>>(std::istream &is, FenwickTree &ft);
 *
 * The data is stored and loaded in little-endian byte order to guarantee
 * compatibility on different architectures.
 *
 * The serialized data follows the compression and node ordering of the specific Fenwick tree
 * without any compatibility layer (e.g., if you serialize a FixedF, you cannot deserialize the
 * very same data with a ByteL).
 */
class RankSelect : public Rank, public Select, public SelectZero {
  public:
	virtual ~RankSelect() = default;

	/** Returns the bit vector. */
	virtual const uint64_t *bitvector() const = 0;

	/** Replace a given word in the bitvector.
	 * @param index index (in words) in the bitvector.
	 * @param word new value for `bitvector[index]`
	 * @return the replaced word
	 *
	 */
	virtual uint64_t update(size_t index, uint64_t word) = 0;

	/** Set (set to 1) a given bit in the bitvector.
	 * @param index index (in bits) in the bitvector.
	 * @return the previous value of such a bit.
	 *
	 */
	virtual bool set(size_t index) = 0;

	/** Clear (set to 0) a given bit in the bitvector.
	 * @param index index (in bits) in the bitvector.
	 * @return: the previous value of such a bit.
	 *
	 */
	virtual bool clear(size_t index) = 0;

	/** Change the value of a given bit in the bitvector.
	 * @param index index (in bits) in the bitvector.
	 * @return: the previous value of such a bit.
	 *
	 */
	virtual bool toggle(size_t index) = 0;

	/** Returns an estimate of the size (in bits) of this structure. */
	virtual size_t bitCount() const = 0;

};

} // namespace sux::ranking
