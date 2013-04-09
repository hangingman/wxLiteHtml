#include "xh_scanner.h"
#include "string.h"
#include <ctype.h>
#include <wchar.h>

namespace litehtml {

// case sensitive string equality test
// s_lowcase shall be lowercase string
     inline bool equal(const wchar* s, const wchar* s1, size_t length) {
	  switch (length) {
	  case 8:
	       if (s1[7] != s[7])
		    return false;
	  case 7:
	       if (s1[6] != s[6])
		    return false;
	  case 6:
	       if (s1[5] != s[5])
		    return false;
	  case 5:
	       if (s1[4] != s[4])
		    return false;
	  case 4:
	       if (s1[3] != s[3])
		    return false;
	  case 3:
	       if (s1[2] != s[2])
		    return false;
	  case 2:
	       if (s1[1] != s[1])
		    return false;
	  case 1:
	       if (s1[0] != s[0])
		    return false;
	  case 0:
	       return true;
	  default:
	       return wcsncmp(s, s1, length) == 0;
	  }
     }

     const wchar* scanner::get_value() {
	  value[value_length] = 0;
	  return value;
     }

     const wchar* scanner::get_attr_name() {
	  attr_name[attr_name_length] = 0;
	  return attr_name;
     }

     const wchar* scanner::get_tag_name() {
	  tag_name[tag_name_length] = 0;
	  return tag_name;
     }

     scanner::token_type scanner::scan_body() {
	  wchar c = get_char();

	  value_length = 0;

	  bool ws = false;

	  if (c == 0)
	       return TT_EOF;
	  else if (c == '<')
	       return scan_tag();
	  else if (c == '&')
	       c = scan_entity();
	  else
	       ws = is_whitespace(c);

	  while (true) {
	       append_value(c);
	       c = input.get_char();
	       if (c == 0) {
		    push_back(c);
		    break;
	       }
	       if (c == '<') {
		    push_back(c);
		    break;
	       }
	       if (c == '&') {
		    push_back(c);
		    break;
	       }

	       if (is_whitespace(c) != ws) {
		    push_back(c);
		    break;
	       }

	  }
	  return ws ? TT_SPACE : TT_WORD;
     }

     scanner::token_type scanner::scan_head() {
	  wchar c = skip_whitespace();

	  if (c == '>') {
	       if (tag_name_length == 6
		   && !wcsncasecmp(tag_name, L"script", tag_name_length)) {
		    c_scan = &scanner::scan_raw_body;
		    return scan_raw_body();
	       } else {
		    c_scan = &scanner::scan_body;
		    return scan_body();
	       }
	  }

	  if (c == '/') {
	       wchar t = get_char();
	       if (t == '>') {
		    c_scan = &scanner::scan_body;
		    return TT_TAG_END;
	       } else {
		    push_back(t);
		    return TT_ERROR;
	       } // erroneous situtation - standalone '/'
	  }

	  attr_name_length = 0;
	  value_length = 0;

	  // attribute name...
	  while (c != '=') {
	       if (c == 0)
		    return TT_EOF;
	       if (c == '>') {
		    push_back(c);
		    return TT_ATTR;
	       } // attribute without value (HTML style)
	       if (is_whitespace(c)) {
		    c = skip_whitespace();
		    if (c != '=') {
			 push_back(c);
			 return TT_ATTR;
		    } // attribute without value (HTML style)
		    else
			 break;
	       }
	       if (c == '<')
		    return TT_ERROR;
	       append_attr_name(c);
	       c = get_char();
	  }

	  c = skip_whitespace();
	  // attribute value...

	  if (c == '\"')
	       while (c = get_char()) {
		    if (c == '\"')
			 return TT_ATTR;
		    if (c == '&')
			 c = scan_entity();
		    append_value(c);
	       }
	  else if (c == '\'') // allowed in html
	       while (c = get_char()) {
		    if (c == '\'')
			 return TT_ATTR;
		    if (c == '&')
			 c = scan_entity();
		    append_value(c);
	       }
	  else
	       // scan token, allowed in html: e.g. align=center
	       do {
		    if (is_whitespace(c))
			 return TT_ATTR;
		    /* these two removed in favour of better html support:
		       if( c == '/' || c == '>' ) { push_back(c); return TT_ATTR; }
		       if( c == '&' ) c = scan_entity();*/
		    if (c == '>') {
			 push_back(c);
			 return TT_ATTR;
		    }
		    append_value(c);
	       } while (c = get_char());

	  return TT_ERROR;
     }

// caller already consumed '<'
// scan header start or tag tail
     scanner::token_type scanner::scan_tag() {
	  tag_name_length = 0;

	  wchar c = get_char();

	  bool is_tail = c == '/';
	  if (is_tail)
	       c = get_char();

	  while (c) {
	       if (is_whitespace(c)) {
		    c = skip_whitespace();
		    break;
	       }
	       if (c == '/' || c == '>')
		    break;
	       append_tag_name(c);

	       switch (tag_name_length) {
	       case 3:
		    if (equal(tag_name, L"!--", 3)) {
			 c_scan = &scanner::scan_comment;
			 return TT_COMMENT_START;
		    }
		    break;
	       case 8:
		    if (equal(tag_name, L"![CDATA[", 8)) {
			 c_scan = &scanner::scan_cdata;
			 return TT_CDATA_START;
		    }
		    if (equal(tag_name, L"!DOCTYPE", 8)) {
			 c_scan = &scanner::scan_entity_decl;
			 return TT_DOCTYPE_START;
		    }
		    break;
	       case 7:
		    if (equal(tag_name, L"!ENTITY", 8)) {
			 c_scan = &scanner::scan_entity_decl;
			 return TT_ENTITY_START;
		    }
		    break;
	       }

	       c = get_char();
	  }

	  if (c == 0)
	       return TT_ERROR;

	  if (is_tail) {
	       if (c == '>')
		    return TT_TAG_END;
	       return TT_ERROR;
	  } else
	       push_back(c);

	  c_scan = &scanner::scan_head;
	  return TT_TAG_START;
     }

// skip whitespaces.
// returns first non-whitespace char
     wchar scanner::skip_whitespace() {
	  while (wchar c = get_char()) {
	       if (!is_whitespace(c))
		    return c;
	  }
	  return 0;
     }

     void scanner::push_back(wchar c) {
	  input_char = c;
     }

     wchar scanner::get_char() {
	  if (input_char) {
	       wchar t(input_char);
	       input_char = 0;
	       return t;
	  }
	  return input.get_char();
     }

// caller consumed '&'
     wchar scanner::scan_entity() {
	  wchar buf[32];
	  int i = 0;
	  wchar t;
	  for (; i < 31; ++i) {
	       t = get_char();

	       if (t == ';')
		    break;

	       if (t == 0)
		    return TT_EOF;
	       if (!isalnum(t) && t != '#') {
		    push_back(t);
		    break; // appears a erroneous entity token.
		    // but we try to use it.
	       }
	       buf[i] = char(t);
	  }
	  buf[i] = 0;
	  if (i == 2) {
	       if (equal(buf, L"gt", 2))
		    return '>';
	       if (equal(buf, L"lt", 2))
		    return '<';
	  } else if (i == 3 && equal(buf, L"amp", 3))
	       return '&';
	  else if (i == 4) {
	       if (equal(buf, L"apos", 4))
		    return '\'';
	       if (equal(buf, L"quot", 4))
		    return '\"';
	  }
	  t = resolve_entity(buf, i);
	  if (t)
	       return t;
	  // no luck ...
	  append_value('&');
	  for (int n = 0; n < i; ++n)
	       append_value(buf[n]);
	  return ';';
     }

     bool scanner::is_whitespace(wchar c) {
	  return c <= ' '
	       && (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f');
     }

     void scanner::append_value(wchar c) {
	  if (value_length < (MAX_TOKEN_SIZE - 1))
	       value[value_length++] = c;
     }

     void scanner::append_attr_name(wchar c) {
	  if (attr_name_length < (MAX_NAME_SIZE - 1))
	       attr_name[attr_name_length++] = c;
     }

     void scanner::append_tag_name(wchar c) {
	  if (tag_name_length < (MAX_NAME_SIZE - 1))
	       tag_name[tag_name_length++] = c;
     }

     scanner::token_type scanner::scan_comment() {
	  if (got_tail) {
	       c_scan = &scanner::scan_body;
	       got_tail = false;
	       return TT_COMMENT_END;
	  }
	  for (value_length = 0; value_length < (MAX_TOKEN_SIZE - 1);
	       ++value_length) {
	       wchar c = get_char();
	       if (c == 0)
		    return TT_EOF;
	       value[value_length] = c;

	       if (value_length >= 2 && value[value_length] == '>'
		   && value[value_length - 1] == '-'
		   && value[value_length - 2] == '-') {
		    got_tail = true;
		    value_length -= 2;
		    break;
	       }
	  }
	  return TT_DATA;
     }

     scanner::token_type scanner::scan_cdata() {
	  if (got_tail) {
	       c_scan = &scanner::scan_body;
	       got_tail = false;
	       return TT_CDATA_END;
	  }
	  for (value_length = 0; value_length < (MAX_TOKEN_SIZE - 1);
	       ++value_length) {
	       wchar c = get_char();
	       if (c == 0)
		    return TT_EOF;
	       value[value_length] = c;

	       if (value_length >= 2 && value[value_length] == '>'
		   && value[value_length - 1] == ']'
		   && value[value_length - 2] == ']') {
		    got_tail = true;
		    value_length -= 2;
		    break;
	       }
	  }
	  return TT_DATA;
     }

     scanner::token_type scanner::scan_pi() {
	  if (got_tail) {
	       c_scan = &scanner::scan_body;
	       got_tail = false;
	       return TT_PI_END;
	  }
	  for (value_length = 0; value_length < (MAX_TOKEN_SIZE - 1);
	       ++value_length) {
	       wchar c = get_char();
	       if (c == 0)
		    return TT_EOF;
	       value[value_length] = c;

	       if (value_length >= 1 && value[value_length] == '>'
		   && value[value_length - 1] == '?') {
		    got_tail = true;
		    value_length -= 1;
		    break;
	       }
	  }
	  return TT_DATA;
     }

     scanner::token_type scanner::scan_entity_decl() {
	  if (got_tail) {
	       c_scan = &scanner::scan_body;
	       got_tail = false;
	       return TT_ENTITY_END;
	  }
	  wchar t;
	  unsigned int tc = 0;
	  for (value_length = 0; value_length < (MAX_TOKEN_SIZE - 1);
	       ++value_length) {
	       t = get_char();
	       if (t == 0)
		    return TT_EOF;
	       value[value_length] = t;
	       if (t == '\"')
		    tc++;
	       else if (t == '>' && (tc & 1) == 0) {
		    got_tail = true;
		    break;
	       }
	  }
	  return TT_DATA;
     }

     scanner::token_type scanner::scan_doctype_decl() {
	  if (got_tail) {
	       c_scan = &scanner::scan_body;
	       got_tail = false;
	       return TT_DOCTYPE_END;
	  }
	  wchar t;
	  unsigned int tc = 0;
	  for (value_length = 0; value_length < (MAX_TOKEN_SIZE - 1);
	       ++value_length) {
	       t = get_char();
	       if (t == 0)
		    return TT_EOF;
	       value[value_length] = t;
	       if (t == '\"')
		    tc++;
	       else if (t == '>' && (tc & 1) == 0) {
		    got_tail = true;
		    break;
	       }
	  }
	  return TT_DATA;
     }

     struct {
	  wchar szCode[10];
	  wchar Code;
     } g_HTMLCodes[] = {

	  {L"&quot;",L'"'},
	  {L"&amp;",L'&'},
	  {L"&lt;",L'<'},
	  {L"&gt;",L'>'},
	  {L"&nbsp;",L'\u00A0'},
	  {L"&iexcl;",L'\u00A1'},
	  {L"&cent;",L'\u00A2'},
	  {L"&pound;",L'u00A3'},
	  {L"&curren;",L'\u00A4'},
	  {L"&yen;",L'\u00A5'},
	  {L"&brvbar;",L'\u00A6'},
	  {L"&sect;",L'\u00A7'},
	  {L"&uml;",L'\u00A8'},
	  {L"&copy;",L'\u00A9'},
	  {L"&ordf;",L'\u00AA'},
	  {L"&laquo;",L'\u00AB'},
	  {L"&not;",L'\u00AC'},
	  {L"&shy;",L'\u00AD'},
	  {L"&reg;",L'\u00AE'},
	  {L"&macr;",L'\u00AF'},
	  {L"&deg;",L'\u00B0'},
	  {L"&plusmn;",L'\u00B1'},
	  {L"&sup2;",L'\u00B2'},
	  {L"&sup3;",L'\u00B3'},
	  {L"&acute;",L'\u00B4'},
	  {L"&micro;",L'\u00B5'},
	  {L"&para;",L'\u00B6'},
	  {L"&middot;",L'\u00B7'},
	  {L"&cedil;",L'\u00B8'},
	  {L"&sup1;",L'\u00B9'},
	  {L"&ordm;",L'\u00BA'},
	  {L"&raquo;",L'\u00BB'},
	  {L"&frac14;",L'\u00BC'},
	  {L"&frac12;",L'\u00BD'},
	  {L"&frac34;",L'\u00BE'},
	  {L"&iquest;",L'\u00BF'},
	  {L"&Agrave;",L'\u00C0'},
	  {L"&Aacute;",L'\u00C1'},
	  {L"&Acirc;",L'\u00C2'},
	  {L"&Atilde;",L'\u00C3'},
	  {L"&Auml;",L'\u00C4'},
	  {L"&Aring;",L'\u00C5'},
	  {L"&AElig;",L'\u00C6'},
	  {L"&Ccedil;",L'\u00C7'},
	  {L"&Egrave;",L'\u00C8'},
	  {L"&Eacute;",L'\u00C9'},
	  {L"&Ecirc;",L'\u00CA'},
	  {L"&Euml;",L'\u00CB'},
	  {L"&Igrave;",L'\u00CC'},
	  {L"&Iacute;",L'\u00CD'},
	  {L"&Icirc;",L'\u00CE'},
	  {L"&Iuml;",L'\u00CF'},
	  {L"&ETH;",L'\u00D0'},
	  {L"&Ntilde;",L'\u00D1'},
	  {L"&Ograve;",L'\u00D2'},
	  {L"&Oacute;",L'\u00D3'},
	  {L"&Ocirc;",L'\u00D4'},
	  {L"&Otilde;",L'\u00D5'},
	  {L"&Ouml;",L'\u00D6'},
	  {L"&times;",L'\u00D7'},
	  {L"&Oslash;",L'\u00D8'},
	  {L"&Ugrave;",L'\u00D9'},
	  {L"&Uacute;",L'\u00DA'},
	  {L"&Ucirc;",L'\u00DB'},
	  {L"&Uuml;",L'\u00DC'},
	  {L"&Yacute;",L'\u00DD'},
	  {L"&THORN;",L'\u00DE'},
	  {L"&szlig;",L'\u00DF'},
	  {L"&agrave;",L'\u00E0'},
	  {L"&aacute;",L'\u00E1'},
	  {L"&acirc;",L'\u00E2'},
	  {L"&atilde;",L'\u00E3'},
	  {L"&auml;",L'\u00E4'},
	  {L"&aring;",L'\u00E5'},
	  {L"&aelig;",L'\u00E6'},
	  {L"&ccedil;",L'\u00E7'},
	  {L"&egrave;",L'\u00E8'},
	  {L"&eacute;",L'\u00E9'},
	  {L"&ecirc;",L'\u00EA'},
	  {L"&euml;",L'\u00EB'},
	  {L"&igrave;",L'\u00E0C'},
	  {L"&iacute;",L'\u00ED'},
	  {L"&icirc;",L'\u00EE'},
	  {L"&iuml;",L'\u00EF'},
	  {L"&eth;",L'\u00F0'},
	  {L"&ntilde;",L'\u00F1'},
	  {L"&ograve;",L'\u00F2'},
	  {L"&oacute;",L'\u00F3'},
	  {L"&ocirc;",L'\u00F4'},
	  {L"&otilde;",L'\u00F5'},
	  {L"&ouml;",L'\u00F6'},
	  {L"&divide;",L'\u00F7'},
	  {L"&oslash;",L'\u00F8'},
	  {L"&ugrave;",L'\u00F9'},
	  {L"&uacute;",L'\u00FA'},
	  {L"&ucirc;",L'\u00FB'},
	  {L"&uuml;",L'\u00FC'},
	  {L"&yacute;",L'\u00FD'},
	  {L"&thorn;",L'\u00FE'},
	  {L"&yuml;",L'\u00FF'},
	  {L"&OElig;",L'E'},
	  {L"&oelig;",L'e'},
	  {L"&Scaron;",L'S'},
	  {L"&scaron;",L's'},
	  {L"&Yuml;",L'\u0178'},
	  {L"&fnof;",L'f'},
	  {L"&circ;",L'^'},
	  {L"&tilde;",L'~'},
	  {L"&ndash;",L'-'},
	  {L"&mdash;",L'-'},
	  {L"&lsquo;",L'\u2018'},
	  {L"&rsquo;",L'\u2019'},
	  {L"&sbquo;",L','},
	  {L"&ldquo;",L'\"'},
	  {L"&rdquo;",L'\"'},
	  {L"&bdquo;",L'\u201E'},
	  {L"&dagger;",L'\u2020'},
	  {L"&Dagger;",L'\u2021'},
	  {L"&bull;",L'\u2022'},
	  {L"&hellip;",L'\u2026'},
	  {L"&permil;",L'\u2030'},
	  {L"&lsaquo;",L'\u2039'},
	  {L"&rsaquo;",L'\u2019'},
	  {L"&euro;",L'\u20AC'},
	  {L"&trade;",L'\u2122'},
	  {{(char)0x97,(char)0x00},L'-'},
	  {{(char)0xA0,(char)0x00},L' '},
	  {L"",0}
     };

     litehtml::wchar scanner::resolve_entity( const wchar* buf, int buf_size )
     {
	  if(buf[0] == '#')
	  {
	       if(buf[1] == 'x' || buf[1] == 'X')
	       {
		    wchar* end = 0;
		    return (wchar) wcstol(buf + 2, &end, 16);
	       } else
	       {
		    return (wchar) wcstol(buf + 1, NULL, 10);
	       }
	  } else
	  {
	       for(int i=0; g_HTMLCodes[i].szCode[0]; i++)
	       {
		    if(!wcsncasecmp(g_HTMLCodes[i].szCode + 1, buf, buf_size))
		    {
			 return g_HTMLCodes[i].Code;
		    }
	       }
	  }
	  return 0;
     }

     scanner::token_type scanner::scan_raw_body()
     {
	  if(got_tail)
	  {
	       c_scan = &scanner::scan_body;
	       got_tail = false;
	       return TT_TAG_END;
	  }
	  for(value_length = 0; value_length < (MAX_TOKEN_SIZE - 1); ++value_length)
	  {
	       wchar c = get_char();
	       if( c == 0) return TT_EOF;
	       value[value_length] = c;

	       if(value_length >= 8 && !wcsncasecmp(value + value_length - 8, L"</script>", 9))
	       {
		    got_tail = true;
		    value_length -= 8;
		    break;
	       }
	  }
	  value[value_length] = 0;
	  return TT_DATA;
     }

}

