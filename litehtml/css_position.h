#ifndef _CSS_POSITION_H_
#define _CSS_POSITION_H_

#include "css_length.h"

namespace litehtml {
  struct css_position {
    css_length x;
    css_length y;
    css_length width;
    css_length height;

    css_position() {

    }

    css_position(const css_position& val) {
      x = val.x;
      y = val.y;
      width = val.width;
      height = val.height;
    }

    void operator=(const css_position& val) {
      x = val.x;
      y = val.y;
      width = val.width;
      height = val.height;
    }
  };
}

#endif /** _CSS_POSITION_H_ */
