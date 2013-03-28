#ifndef _EL_BASE_H_
#define _EL_BASE_H_

#include "element.h"

namespace litehtml {
  class el_base: public element {
  public:
    el_base(litehtml::document* doc);
    virtual ~el_base();
    virtual void finish();
  };
}

#endif /** _EL_BASE_H_ */
