/**
 * Non-metric Space Library
 *
 * Main developers: Bilegsaikhan Naidan, Leonid Boytsov, Yury Malkov, Ben Frederickson, David Novak
 *
 * For the complete list of contributors and further details see:
 * https://github.com/searchivarius/NonMetricSpaceLib
 *
 * Copyright (c) 2013-2018
 *
 * This code is released under the
 * Apache License Version 2.0 http://www.apache.org/licenses/.
 *
 */
#ifndef _SPACE_BIT_JACCARD_H_
#define _SPACE_BIT_JACCARD_H_

#include <string>
#include <map>
#include <stdexcept>

#include <string.h>
#include "global.h"
#include "object.h"
#include "utils.h"
#include "space.h"
#include "distcomp.h"
#include "space_bit_vector.h"

#define SPACE_BIT_JACCARD "bit_jaccard"

namespace similarity {

template <typename dist_t, typename dist_uint_t>
class SpaceBitJaccard : public SpaceBitVector<dist_t,dist_uint_t> {
 public:
  explicit SpaceBitJaccard() {}
  virtual ~SpaceBitJaccard() {}

  virtual std::string StrDesc() const { return "Jaccard (bit-storage) space"; }

 protected:
  virtual dist_t HiddenDistance(const Object* obj1, const Object* obj2) const {
    CHECK(obj1->datalength() > 0);
    CHECK(obj1->datalength() == obj2->datalength());
    const dist_uint_t* x = reinterpret_cast<const dist_uint_t*>(obj1->data());
    const dist_uint_t* y = reinterpret_cast<const dist_uint_t*>(obj2->data());
    const size_t length = obj1->datalength() / sizeof(dist_uint_t)
                          - 1; // the last integer is an original number of elements

    return BitJaccard(x, y, length);
  }

  DISABLE_COPY_AND_ASSIGN(SpaceBitJaccard);
};

}  // namespace similarity

#endif
