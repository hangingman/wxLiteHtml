#ifndef WX_CONTAINER_H_
#define WX_CONTAINER_H_

#include <wx/wx.h>

/**
 * stub class for document_container by wxWidgets
 */
namespace litehtml
{
  class wx_container : public document_container
  {
  public:
    typedef std::map<std::wstring, litehtml::uint_ptr>	images_map;
	
  protected:
		
    images_map			m_images;
    litehtml::position::vector	m_clips;

  public:
    wx_container();
    virtual ~wx_container();

    // litehtml::document_container members
  };
}

#endif /** WX_CONTAINER_H_ */
