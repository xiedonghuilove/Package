/***************************************************************************

 ***************************************************************************/

#include <QtGui>
#include "widgetwithbackground.h"

WidgetWithBackground::WidgetWithBackground(QWidget * parent) : QWidget(parent)
{
  m_pixmap = new QPixmap(size());
  m_modified = false;
}

WidgetWithBackground::~WidgetWithBackground()
{
   if (m_pixmap)
     {
	delete m_pixmap;
	m_pixmap = NULL;
     }
}

void WidgetWithBackground::drawBackground()
{
  if (m_pixmap->size() != size() || m_modified )
    {
	delete m_pixmap;
	m_pixmap = new QPixmap(size());
    m_modified=true; // ???????????
	repaintBackground();
	m_modified=false;
    }
    QPainter painter(this);
    painter.drawPixmap(0,0,*m_pixmap);
}

void WidgetWithBackground::updateWithBackground()
{
  m_modified=true;
  update();
}

bool WidgetWithBackground::doRepaintBackground()
{
  return m_modified;
}

void WidgetWithBackground::repaintBackground()
{
  m_pixmap->fill(QColor(0,0,0,0));
  QPainter painter(m_pixmap);
  paintBackground(painter);
}
