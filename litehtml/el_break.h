#ifndef _EL_BREAK_H_
#define _EL_BREAK_H_

#include "element.h"

namespace litehtml {
  class el_break: public element {
  public:
    el_break(litehtml::document* doc);
    virtual ~el_break();
    virtual bool is_break() const;
  };
}

#endif /** _EL_BREAK_H_ */
