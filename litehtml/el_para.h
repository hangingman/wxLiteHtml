#ifndef _EL_PARA_H_
#define _EL_PARA_H_

#include "element.h"

namespace litehtml {
  class el_para: public element {
  public:
    el_para(litehtml::document* doc);
    virtual ~el_para();

    virtual void parse_styles(bool is_reparse = false);

  };
}

#endif /** _EL_PARA_H_ */
