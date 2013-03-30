#ifndef _DOWNLOADER_H_
#define _DOWNLOADER_H_

class CRemotedFile
{
  WCHAR	m_tmpFile[MAX_PATH];
  HANDLE	m_hFile;
 public:
  CRemotedFile();
  ~CRemotedFile();

  HANDLE Open(LPCWSTR url);
};

LPWSTR load_text_file( LPCWSTR path, bool is_html = false );

#endif /** _DOWNLOADER_H_ */
