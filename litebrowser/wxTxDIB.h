/**
 * wxTxDIB.h - stub implement class of TxDIB
 *
 * Copyright (c) 2013 Hiroyuki Nagata <newserver002@gmail.com>
 * 
 *
 */
#ifndef WXTXDIB_H_
#define WXTXDIB_H_

#include <math.h>
#include <vector>
#include <memory>
#include <wx/wx.h>

#define JPEG_QUALITY_SUPER		0
#define JPEG_QUALITY_GOOD		1
#define JPEG_QUALITY_NORMAL		2
#define JPEG_QUALITY_AVERAGE	        3
#define JPEG_QUALITY_BAD		4

class wxCTxDIB {
  LPRGBQUAD	m_bits;
  int		m_width;
  int		m_height;
  BYTE		m_maxAlpha;
 public:
  wxCTxDIB(void);
  wxCTxDIB(LPCWSTR fileName);
  wxCTxDIB(wxCTxDIB& val);
  virtual ~wxCTxDIB(void);

  void operator=(wxCTxDIB& val);

  BOOL	load(LPCWSTR fileName);
  BOOL	load(HRSRC hRes, HMODULE hModule = NULL);
  BOOL	load(LPBYTE data, DWORD size);
  BOOL	savePNG(LPCWSTR fileName);
  BOOL	saveJPG(LPCWSTR fileName, int quality = JPEG_QUALITY_GOOD);
  BOOL	saveBMP(LPCWSTR fileName);

  BOOL	destroy();
  BOOL	draw(HDC hdc, int x, int y, int cx = -1, long cy = -1);
  BOOL	draw(HDC hdc, LPCRECT rcDraw);
  BOOL	createFromHBITMAP(HBITMAP bmp);
  BOOL	createFromHICON(HICON ico);

  HBITMAP createBitmap( HDC hdc = NULL );
  void	setTransColor(COLORREF clr);
  void	resample( int newWidth, int newHeight, wxCTxDIB* dst = NULL );
  void	tile(HDC hdc, LPRECT rcDraw, LPRECT rcClip = NULL);
  int		getWidth();
  int		getHeight();
  void	crop(int left, int top, int right, int bottom, wxCTxDIB* dst = NULL);
  void	crop(LPCRECT rcCrop, wxCTxDIB* dst = NULL);
  BOOL	isValid();
  void	setMaxAlpha(BYTE alpha);
  BYTE	getMaxAlpha();
  void	colorize(COLORREF clr);
  BOOL	calcAlpha(wxCTxDIB* imgWhite, wxCTxDIB* imgBlack);
  LPRGBQUAD	getBits() { return m_bits; }
  void	PreMulRGBA(RGBQUAD& color);
  void	rotateLeft(wxCTxDIB* dst = NULL);
  void	rotateRight(wxCTxDIB* dst = NULL);
 private:
  void	OverflowCoordinates(float &x, float &y);
  RGBQUAD GetPixelColorWithOverflow(long x, long y);
  RGBQUAD GetAreaColorInterpolated(float const xc, float const yc, float const w, float const h);
  void	AddAveragingCont(RGBQUAD const &color, float const surf, float &rr, float &gg, float &bb, float &aa);
  RGBQUAD GetPixelColorInterpolated(float x,float y);
  void	resample2( int newWidth, int newHeight, wxCTxDIB* dst = NULL );
  bool	QIShrink( int newWidth, int newHeight, wxCTxDIB* dst = NULL );

  void	PreMultiplyWithAlpha();
  void	_copy( wxCTxDIB& val );
  void	_copy( LPRGBQUAD newBits, int newWidth, int newHeight, BOOL copyBits = FALSE );
  BOOL	attach( LPVOID dib );
};

class wxCTxDibSet {
  typedef std::vector<wxCTxDIB*>	imgCols;
  
  std::vector<imgCols>	m_items;
  int						m_width;
  int						m_height;
  int						m_cols;
  int						m_rows;
 public:
  wxCTxDibSet(wxCTxDIB* img, int rows, int cols);
  ~wxCTxDibSet();
  wxCTxDIB* get(int col, int row) { return m_items[row][col]; }


  int width()		{ return m_width;	}
  int height()	        { return m_height;	}
  int rows()		{ return m_rows;	}
  int cols()		{ return m_cols;	}
};

class wxCTxSkinDIB {
  wxCTxDIB	m_dibLeftTop;
  wxCTxDIB	m_dibTop;
  wxCTxDIB	m_dibRightTop;

  wxCTxDIB	m_dibLeftCenter;
  wxCTxDIB	m_dibCenter;
  wxCTxDIB	m_dibRightCenter;

  wxCTxDIB	m_dibLeftBottom;
  wxCTxDIB	m_dibBottom;
  wxCTxDIB	m_dibRightBottom;

  //MARGINS	m_margins;
  BOOL	        m_tileX;
  BOOL	        m_tileY;

 public:
  wxCTxSkinDIB();
  virtual ~wxCTxSkinDIB();

  //BOOL load(LPCWSTR fileName, MARGINS* mg, BOOL tileX, BOOL tileY);
  //BOOL load(wxCTxDIB* dib, MARGINS* mg, BOOL tileX, BOOL tileY);

  void draw(HDC hdc, LPRECT rcDraw, LPRECT rcClip);
};

//***bd*** simple floating point point
class wxCTxDibPoint2 {
 public:
  wxCTxDibPoint2();
  wxCTxDibPoint2(float const x_, float const y_);
  wxCTxDibPoint2(wxCTxDibPoint2 const &p);

  float Distance(wxCTxDibPoint2 const p2);
  float Distance(float const x_, float const y_);

  float x,y;
};

//and simple rectangle
class wxCTxDibRect2 {
 public:
  wxCTxDibRect2();
  wxCTxDibRect2(float const x1_, float const y1_, float const x2_, float const y2_);
  wxCTxDibRect2(wxCTxDibPoint2 const &bl, wxCTxDibPoint2 const &tr);
  wxCTxDibRect2(wxCTxDibRect2 const &p);

  float Surface() const;
  wxCTxDibRect2 CrossSection(wxCTxDibRect2 const &r2);
  wxCTxDibPoint2 Center();
  float Width();
  float Height();

  wxCTxDibPoint2 botLeft;
  wxCTxDibPoint2 topRight;
};


inline RGBQUAD wxCTxDIB::GetPixelColorWithOverflow(long x, long y) {
  
  if (!(0 <= y && y < m_height && 0 <= x &&  x < m_width)) {
    x = std::max(x, static_cast<long>(0)); 
    x = std::min(x, static_cast<long>(m_width - 1));
    y = std::max(y, static_cast<long>(0)); 
    y = std::min(y, static_cast<long>(m_height - 1));
  }
  return m_bits[y * m_width + x];
}

inline void wxCTxDIB::OverflowCoordinates( float &x, float &y ) {
  if (x >= 0 && x < m_width && y >= 0 && y < m_height) 
    {
      return;
    }
  x = std::max(x, static_cast<float>(0)); 
  x = std::min(x, static_cast<float>(m_width - 1));
  y = std::max(y, static_cast<float>(0)); 
  y = std::min(y, static_cast<float>(m_height - 1));
}

inline void wxCTxDIB::AddAveragingCont(RGBQUAD const &color, float const surf, float &rr, float &gg, float &bb, float &aa) {
  rr += color.rgbRed		* surf;
  gg += color.rgbGreen	* surf;
  bb += color.rgbBlue		* surf;
  aa += color.rgbReserved	* surf;
}


inline void wxCTxDIB::PreMulRGBA(RGBQUAD& color) {
  color.rgbRed		= (color.rgbRed		* color.rgbReserved) / 255;
  color.rgbGreen	= (color.rgbGreen	* color.rgbReserved) / 255;
  color.rgbBlue		= (color.rgbBlue	* color.rgbReserved) / 255;
}

inline int wxCTxDIB::getWidth()	{ 
  return m_width;  
}

inline int wxCTxDIB::getHeight() { 
  return m_height; 
}

inline void wxCTxDIB::crop(LPCRECT rcCrop, wxCTxDIB* dst /*= NULL*/) 
{ 
  crop(rcCrop->left, rcCrop->top, rcCrop->right, rcCrop->bottom, dst); 
}

inline BOOL wxCTxDIB::isValid()	{ 
  return m_bits ? TRUE : FALSE; 
}

inline void wxCTxDIB::setMaxAlpha(BYTE alpha) { 
  m_maxAlpha = alpha; 
}

inline BYTE wxCTxDIB::getMaxAlpha() { 
  return m_maxAlpha;
}

inline BOOL wxCTxDIB::draw(HDC hdc, LPCRECT rcDraw) { 
  return draw(hdc, rcDraw->left, rcDraw->top, rcDraw->right - rcDraw->left, rcDraw->bottom - rcDraw->top); 
}

inline void wxCTxDIB::operator=(wxCTxDIB& val) { 
  _copy(val); 
}


inline wxCTxDibPoint2::wxCTxDibPoint2() {
  x=y=0.0f;
}

inline wxCTxDibPoint2::wxCTxDibPoint2(float const x_, float const y_) {
  x=x_;
  y=y_;
}

inline wxCTxDibPoint2::wxCTxDibPoint2(wxCTxDibPoint2 const &p) {
  x=p.x;
  y=p.y;
}

inline float wxCTxDibPoint2::Distance(wxCTxDibPoint2 const p2) {
  return (float)sqrt((x-p2.x)*(x-p2.x)+(y-p2.y)*(y-p2.y));
}

inline float wxCTxDibPoint2::Distance(float const x_, float const y_) {
  return (float)sqrt((x-x_)*(x-x_)+(y-y_)*(y-y_));
}

inline wxCTxDibRect2::wxCTxDibRect2() {
}

inline wxCTxDibRect2::wxCTxDibRect2(float const x1_, float const y1_, float const x2_, float const y2_) {
  botLeft.x=x1_;
  botLeft.y=y1_;
  topRight.x=x2_;
  topRight.y=y2_;
}

inline wxCTxDibRect2::wxCTxDibRect2(wxCTxDibRect2 const &p) {
  botLeft=p.botLeft;
  topRight=p.topRight;
}

inline float wxCTxDibRect2::Surface() const {
  return (topRight.x-botLeft.x)*(topRight.y-botLeft.y);
}

inline wxCTxDibRect2 wxCTxDibRect2::CrossSection(wxCTxDibRect2 const &r2) {
  wxCTxDibRect2 cs;
  cs.botLeft.x=std::max(botLeft.x, r2.botLeft.x);
  cs.botLeft.y=std::max(botLeft.y, r2.botLeft.y);
  cs.topRight.x=std::min(topRight.x, r2.topRight.x);
  cs.topRight.y=std::min(topRight.y, r2.topRight.y);
  if (cs.botLeft.x<=cs.topRight.x && cs.botLeft.y<=cs.topRight.y) {
    return cs;
  } else {
    return wxCTxDibRect2(0,0,0,0);
  }//if
}

inline wxCTxDibPoint2 wxCTxDibRect2::Center() {
  return wxCTxDibPoint2((topRight.x+botLeft.x)/2.0f, (topRight.y+botLeft.y)/2.0f);
}

inline float wxCTxDibRect2::Width() {
  return topRight.x-botLeft.x;
}

inline float wxCTxDibRect2::Height() {
  return topRight.y-botLeft.y;
}

#endif /* WXTXDIB_H_ */
