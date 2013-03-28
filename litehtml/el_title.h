#ifndef _EL_TITLE_H_
#define _EL_TITLE_H_

#include "element.h"

namespace litehtml {
  class el_title: public element {
  public:
    el_title(litehtml::document* doc);
    virtual ~el_title();

  protected:
    virtual void finish();
  };
}

#endif /** _EL_TITLE_H_ */
