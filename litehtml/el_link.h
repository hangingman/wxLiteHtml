#ifndef _EL_LINK_H_
#define _EL_LINK_H_

#include "element.h"

namespace litehtml {
  class el_link: public element {
  public:
    el_link(litehtml::document* doc);
    virtual ~el_link();

  protected:
    virtual void finish();
  };
}

#endif /** _EL_LINK_H_ */
