#ifndef HTMLWIDGET_H
#define HTMLWIDGET_H

#include <QWidget>
#include <litehtml/litehtml.h>

class DocumentContainer : public litehtml::document_container
{
public:
	DocumentContainer();
	~DocumentContainer();

	litehtml::uint_ptr	create_font(const litehtml::tchar_t* faceName, int size, int weight, litehtml::font_style italic, unsigned int decoration, litehtml::font_metrics* fm) override;
	void				delete_font(litehtml::uint_ptr hFont) override;
	int					text_width(const litehtml::tchar_t* text, litehtml::uint_ptr hFont) override;
	void				draw_text(litehtml::uint_ptr hdc, const litehtml::tchar_t* text, litehtml::uint_ptr hFont, litehtml::web_color color, const litehtml::position& pos) override;
	int					pt_to_px(int pt) const override;
	int					get_default_font_size() const override;
	const litehtml::tchar_t* get_default_font_name() const override;
	void				draw_list_marker(litehtml::uint_ptr hdc, const litehtml::list_marker& marker) override;
	void				load_image(const litehtml::tchar_t* src, const litehtml::tchar_t* baseurl, bool redraw_on_ready) override;
	void				get_image_size(const litehtml::tchar_t* src, const litehtml::tchar_t* baseurl, litehtml::size& sz) override;
	void				draw_background(litehtml::uint_ptr hdc, const litehtml::background_paint& bg) override;
	void				draw_borders(litehtml::uint_ptr hdc, const litehtml::borders& borders, const litehtml::position& draw_pos, bool root) override;
	void				set_caption(const litehtml::tchar_t* caption) override;
	void				set_base_url(const litehtml::tchar_t* base_url) override;
	void				link(const std::shared_ptr<litehtml::document>& doc, const litehtml::element::ptr& el) override;
	void				on_anchor_click(const litehtml::tchar_t* url, const litehtml::element::ptr& el) override;
	void				set_cursor(const litehtml::tchar_t* cursor) override;
	void				transform_text(litehtml::tstring& text, litehtml::text_transform tt) override;
	void				import_css(litehtml::tstring& text, const litehtml::tstring& url, litehtml::tstring& baseurl) override;
	void				set_clip(const litehtml::position& pos, const litehtml::border_radiuses& bdr_radius, bool valid_x, bool valid_y) override;
	void				del_clip() override;
	void				get_client_rect(litehtml::position& client) const override;
	std::shared_ptr<litehtml::element> create_element(const litehtml::tchar_t* tag_name, const litehtml::string_map& attributes, const std::shared_ptr<litehtml::document>& doc) override;

	void				get_media_features(litehtml::media_features& media) const override;
	void				get_language(litehtml::tstring& language, litehtml::tstring& culture) const override;
	litehtml::tstring   resolve_color(const litehtml::tstring& /*color*/) const override;
	void				split_text(const char* text, const std::function<void(const litehtml::tchar_t*)>& on_word, const std::function<void(const litehtml::tchar_t*)>& on_space);

private:
	QFont mFont;
};

class HtmlWidget : public QWidget
{
	Q_OBJECT
public:
	explicit HtmlWidget(QWidget* parent = nullptr);
	~HtmlWidget();

	void loadDocument(const QString &thml);

protected:
	void resizeEvent(QResizeEvent* ev) override;
	void paintEvent(QPaintEvent* ev) override;

private:
	litehtml::context mCtx;
	DocumentContainer mContainer;
	litehtml::document::ptr mDoc;
	int mIdealWidth{ 0 };
};

#endif
