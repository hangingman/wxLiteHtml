#ifndef _EL_ANCHOR_H_
#define _EL_ANCHOR_H_

#include "element.h"

namespace litehtml {
  class el_anchor: public element {
  public:
    el_anchor(litehtml::document* doc);
    virtual ~el_anchor();
    virtual void on_click(int x, int y);
  };
}

#endif /** _EL_ANCHOR_H_ */
