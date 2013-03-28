#ifndef _EL_STYLE_H_
#define _EL_STYLE_H_

#include "element.h"

namespace litehtml {
  class el_style: public element {
  public:
    el_style(litehtml::document* doc);
    virtual ~el_style();

    virtual void finish();
  };
}

#endif /** _EL_STYLE_H_ */
