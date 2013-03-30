#ifndef _MEMDC_H_
#define _MEMDC_H_

class CMemDC
{
  RECT	        m_rcTarget;
  HBITMAP	m_hBmp;
  HBITMAP	m_hOldBmp;
  HDC		m_hMemDC;
  HDC		m_hTargetDC;
  BYTE	        m_alpha;
  POINT	        m_oldViewPort;

 public:
  CMemDC();
  virtual ~CMemDC();
  virtual HDC	beginPaint(HDC targetDC, LPRECT rcDraw);
  virtual void	endPaint();
  virtual void	setAlpha(BYTE alpha, LPRECT rcAlpha);
};

#endif /** _MEMDC_H_ */
