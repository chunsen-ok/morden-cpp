#include "htmlwidget.h"
#include <QFile>
#include <QPainter>
#include <QTextStream>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QApplication>

#include <litehtml/el_body.h>
#include "master_css.inc"

using namespace litehtml;

HtmlWidget::HtmlWidget(QWidget* parent)
	: QWidget(parent)
{
	mCtx.load_master_stylesheet(master_css);
}

HtmlWidget::~HtmlWidget()
{
}

void HtmlWidget::loadDocument(const QString &html)
{
	const auto docStr = html.toUtf8();
	mDoc = litehtml::document::createFromUTF8(docStr.data(), std::addressof(mContainer), std::addressof(mCtx));
	updateGeometry();
}

void HtmlWidget::resizeEvent(QResizeEvent* ev)
{
	QWidget::resizeEvent(ev);

	if (mDoc) {
		mIdealWidth = mDoc->render(ev->size().width());
	}
}

void HtmlWidget::paintEvent(QPaintEvent* ev)
{
	QPainter painter(this);

	if (mDoc) {
		const auto r = ev->rect();
		const litehtml::position pos{r.x(), r.y(), r.width(), r.height()};
		mDoc->draw(reinterpret_cast<litehtml::uint_ptr>(std::addressof(painter)), 0, 0, &pos);
	}
}

DocumentContainer::DocumentContainer()
	: litehtml::document_container()
	, mFont(qApp->font())
{
}

DocumentContainer::~DocumentContainer()
{
}

litehtml::uint_ptr DocumentContainer::create_font(const litehtml::tchar_t* faceName, int size, int weight, litehtml::font_style italic, unsigned int decoration, litehtml::font_metrics* fm)
{
	return reinterpret_cast<litehtml::uint_ptr>(std::addressof(mFont));
}

void DocumentContainer::delete_font(litehtml::uint_ptr hFont)
{
}

int DocumentContainer::text_width(const litehtml::tchar_t* text, litehtml::uint_ptr hFont)
{
	const auto f = reinterpret_cast<QFont*>(hFont);
	const QFontMetrics metrics(*f);
	const auto s =  metrics.size(Qt::TextSingleLine, QString::fromStdWString(std::wstring(text)));
	return s.width();
}

void DocumentContainer::draw_text(litehtml::uint_ptr hdc, const litehtml::tchar_t* text, litehtml::uint_ptr hFont, litehtml::web_color color, const litehtml::position& pos)
{
	QPainter* painter = reinterpret_cast<QPainter*>(hdc);
	painter->drawRect(QRect(pos.x, pos.y, pos.width, pos.height));
}

int DocumentContainer::pt_to_px(int pt) const
{
	return 1;
}

int DocumentContainer::get_default_font_size() const
{
	return mFont.pixelSize();
}

const litehtml::tchar_t* DocumentContainer::get_default_font_name() const
{
	return L"Microsoft YaHei";
}

void DocumentContainer::draw_list_marker(litehtml::uint_ptr hdc, const litehtml::list_marker& marker)
{
}

void DocumentContainer::load_image(const litehtml::tchar_t* src, const litehtml::tchar_t* baseurl, bool redraw_on_ready)
{
}

void DocumentContainer::get_image_size(const litehtml::tchar_t* src, const litehtml::tchar_t* baseurl, litehtml::size& sz)
{
}

void DocumentContainer::draw_background(litehtml::uint_ptr hdc, const litehtml::background_paint& bg)
{
}

void DocumentContainer::draw_borders(litehtml::uint_ptr hdc, const litehtml::borders& borders, const litehtml::position& draw_pos, bool root)
{
}

void DocumentContainer::set_caption(const litehtml::tchar_t* caption)
{
}

void DocumentContainer::set_base_url(const litehtml::tchar_t* base_url)
{
}

void DocumentContainer::link(const std::shared_ptr<litehtml::document>& doc, const litehtml::element::ptr& el)
{
}

void DocumentContainer::on_anchor_click(const litehtml::tchar_t* url, const litehtml::element::ptr& el)
{
}

void DocumentContainer::set_cursor(const litehtml::tchar_t* cursor)
{
}

void DocumentContainer::transform_text(litehtml::tstring& text, litehtml::text_transform tt)
{
}

void DocumentContainer::import_css(litehtml::tstring& text, const litehtml::tstring& url, litehtml::tstring& baseurl)
{
}

void DocumentContainer::set_clip(const litehtml::position& pos, const litehtml::border_radiuses& bdr_radius, bool valid_x, bool valid_y)
{
}

void DocumentContainer::del_clip()
{
}

void DocumentContainer::get_client_rect(litehtml::position& client) const
{
}

std::shared_ptr<litehtml::element> DocumentContainer::create_element(const litehtml::tchar_t* tag_name, const litehtml::string_map& attributes, const std::shared_ptr<litehtml::document>& doc)
{
	fwprintf_s(stdout, L"%s\n", tag_name);
	if (std::wcscmp(tag_name, L"html") == 0) {
		return element::ptr{ new html_tag{doc} };
	}
	else if (std::wcscmp(tag_name, L"head") == 0) {
		return element::ptr{ new element{doc} };
	}
	else if (std::wcscmp(tag_name, L"body") == 0) {
		return element::ptr{ new el_body{doc} };
	}
	else if (std::wcscmp(tag_name, L"h1") == 0) {
		return element::ptr{ new html_tag{doc} };
	} 
	else if (std::wcscmp(tag_name, L"p") == 0) {
		return element::ptr{ new html_tag{doc} };
	}

	return std::shared_ptr<element>{};
}

void DocumentContainer::get_media_features(litehtml::media_features& media) const
{
}

void DocumentContainer::get_language(litehtml::tstring& language, litehtml::tstring& culture) const
{
}

litehtml::tstring DocumentContainer::resolve_color(const litehtml::tstring&) const
{
	return litehtml::tstring();
}

void DocumentContainer::split_text(const char* text, const std::function<void(const litehtml::tchar_t*)>& on_word, const std::function<void(const litehtml::tchar_t*)>& on_space)
{
}
