# build libwxlitehtml
ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libwxlitehtml.la
libwxlitehtml_la_SOURCES = \
css_position.h  el_body.h         el_para.h       el_text.h     line.cpp       tokenizer.cpp                   \
attributes.h    css_selector.cpp  el_break.cpp    el_space.cpp  el_title.cpp   line.h           tokenizer.h    \
background.cpp  css_selector.h    el_break.h      el_space.h    el_title.h     litehtml.vcproj  types.h        \
background.h    document.cpp      el_comment.cpp  el_style.cpp  element.cpp    object.h         web_color.cpp  \
borders.h       document.h        el_comment.h    el_style.h    element.h      style.cpp        web_color.h    \
context.cpp     el_anchor.cpp     el_image.cpp    el_table.cpp  elements.h     style.h          xh_scanner.cpp \
context.h       el_anchor.h       el_image.h      el_table.h    html.cpp       stylesheet.cpp   xh_scanner.h   \
css_length.cpp  el_base.cpp       el_link.cpp     el_td.cpp     html.h         stylesheet.h                    \
css_length.h    el_base.h         el_link.h       el_td.h       iterators.cpp  table.cpp                       \
css_margins.h   el_body.cpp       el_para.cpp     el_text.cpp   iterators.h    table.h

libwxlitehtml_la_LDFLAGS = -no-undefined -version-info 1:0:0