#include "editor_screen.hpp"

#include "canvas_widget.hpp"
#include "default_editor_scene.hpp"
#include "default_font.hpp"
#include "default_layout_parser.hpp"
#include "default_polygon_editor_scene_object.hpp"
#include "default_stream.hpp"
#include "default_style_parser.hpp"
#include "editor_scene.hpp"
#include "editor_scene_object.hpp"
#include "font.hpp"
#include "geometry.hpp"
#include "layout_parser.hpp"
#include "polygon_editor_scene_object.hpp"
#include "screen.hpp"
#include "stream.hpp"
#include "style_parser.hpp"
#include "style_sheet.hpp"
#include "text_widget.hpp"
#include "widget.hpp"
#include "window.hpp"

#include <iostream>
#include <vector>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <SDL/SDL_opengl.h>

namespace mortified {
    class EditorScreen :
        public virtual Screen
    {
    public:
        explicit EditorScreen(Window *window) :
            window_(window),
            resize_(false),
            width_(0),
            height_(0)
        { }

        void create()
        {
            scene_ = createEditorScene();
            std::auto_ptr<EditorSceneObject> object =
                createPolygonEditorSceneObject();
            EditorScene::ObjectIterator iterator = scene_->addObject(object);
            if (PolygonEditorSceneObject *polygonObject =
                dynamic_cast<PolygonEditorSceneObject *>(*iterator))
            {
                Polygon2 *polygon = polygonObject->polygon();
                polygon->vertices.push_back(Vector2(0.0f, 0.0f));
                polygon->vertices.push_back(Vector2(20.0f, 0.0f));
                polygon->vertices.push_back(Vector2(20.0f, 20.0f));
                polygon->vertices.push_back(Vector2(0.0f, 20.0f));
            }

            createWidgets();
            createHandlers();

            resize_ = true;
            width_ = window_->width();
            height_ = window_->height();
        }

        void destroy()
        {
            rootWidget_.reset();
            scene_.reset();
        }

        bool handleEvent(SDL_Event const *event)
        {
            if (event->type == SDL_KEYDOWN &&
                event->key.keysym.sym == SDLK_BACKSPACE)
            {
                destroy();
                create();
                return true;
            }

            if (rootWidget_.get()) {
                return rootWidget_->handleEvent(event);
            }

            return false;
        }

        void update()
        {
            if (resize_) {
                resize_ = false;
                if (rootWidget_.get()) {
                    rootWidget_->size(WidgetSize(width_, height_));
                    rootWidget_->measure();
                    rootWidget_->arrange();
                }

                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                glOrtho(0.0, double(width_), double(height_), 0.0, -1.0, 1.0);
                glMatrixMode(GL_MODELVIEW);
            }
        }

        void draw()
        {
            if (rootWidget_.get()) {
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glEnable(GL_TEXTURE_2D);
                rootWidget_->draw();
                glDisable(GL_TEXTURE_2D);
                glDisable(GL_BLEND);
            }
        }

        void resize(int width, int height)
        {
            resize_ = true;
            width_ = width;
            height_ = height;
        }

    private:
        Window *window_;
        bool resize_;
        int width_;
        int height_;
        std::auto_ptr<EditorScene> scene_;
        std::auto_ptr<Widget> rootWidget_;
        boost::shared_ptr<Font> font_;

        void createWidgets()
        {
            std::auto_ptr<Stream> layoutStream =
                createStreamFromFile("../assets/layouts/editor.xml", "rb");
            std::auto_ptr<LayoutParser> layoutParser = createLayoutParser();
            rootWidget_ = layoutParser->parse(layoutStream.get());

            std::auto_ptr<Stream> styleStream =
                createStreamFromFile("../assets/styles/editor.txt", "rb");
            std::auto_ptr<StyleParser> styleParser = createStyleParser();
            std::auto_ptr<StyleSheet> styleSheet =
                styleParser->parse(styleStream.get());
            applyStyles(styleSheet.get(), rootWidget_.get());

            std::auto_ptr<Stream> fontStream =
                createStreamFromFile("../assets/fonts/teen/teen.ttf", "rb");
            font_ = createFont(fontStream.get(), 15);
            updateFonts(rootWidget_.get());
        }

        void createHandlers()
        {
            if (Widget *menuBarWidget =
                findWidget(rootWidget_.get(), "menu-bar"))
            {
                menuBarWidget->addEventHandler(boost::bind(&EditorScreen::handleWidgetEvent, this, menuBarWidget, _1));
            }
            if (Widget *statusBarWidget =
                findWidget(rootWidget_.get(), "status-bar"))
            {
                statusBarWidget->addEventHandler(boost::bind(&EditorScreen::handleWidgetEvent, this, statusBarWidget, _1));
            }
            if (Widget *sceneWidget = findWidget(rootWidget_.get(), "scene")) {
                if (CanvasWidget *sceneCanvasWidget = sceneWidget->asCanvasWidget()) {
                    sceneCanvasWidget->addDrawHandler(boost::bind(&EditorScreen::drawSceneWidget, this, sceneWidget));
                }
            }
        }

        void applyStyles(StyleSheet *sheet, Widget *widget)
        {
            std::vector<std::string> names;
            names.push_back("default");
            names.push_back(widget->type());
            names.push_back(widget->name());
            std::auto_ptr<WidgetStyle> style =
                sheet->applyStyles(&names[0], int(names.size()));
            widget->style(style.get());

            for (int i = 0; i < widget->childCount(); ++i) {
                applyStyles(sheet, widget->child(i));
            }
        }

        void updateFonts(Widget *widget)
        {
            if (TextWidget *textWidget = widget->asTextWidget()) {
                textWidget->font(font_);
            }

            for (int i = 0; i < widget->childCount(); ++i) {
                updateFonts(widget->child(i));
            }
        }

        Widget *findWidget(Widget *ancestor, char const *name)
        {
            if (std::strcmp(ancestor->name(), name) == 0) {
                return ancestor;
            }

            for (int i = 0; i < ancestor->childCount(); ++i) {
                if (Widget *descendant = findWidget(ancestor->child(i), name))
                {
                    return descendant;
                }
            }

            return false;
        }

        bool handleWidgetEvent(Widget *widget, SDL_Event const *event)
        {
            switch (event->type) {
            case SDL_MOUSEBUTTONDOWN:
                std::cerr << "mouse-button-down event on " << widget->name()
                          << " widget" << std::endl;
                return true;

            case SDL_MOUSEBUTTONUP:
                std::cerr << "mouse-button-up event on " << widget->name()
                          << " widget" << std::endl;
                return true;

            case SDL_MOUSEMOTION:
                std::cerr << "mouse-motion event on " << widget->name()
                          << " widget" << std::endl;
                return true;
            }

            return false;
        }

        void drawSceneWidget(Widget *widget)
        {
            (void) widget;
#if 0
            WidgetPosition position = widget->position();
            WidgetPosition absolutePosition =
                widget->toAbsolutePosition(position);
            WidgetSize size = widget->size();

            glViewport(absolutePosition.x, absolutePosition.y, size.width, size.height);

            glColor3ub(255, 127, 127);
            glBegin(GL_POLYGON);
            glVertex2i(position.x, position.y);
            glVertex2i(position.x + size.width, position.y);
            glVertex2i(position.x + size.width, position.y + size.height);
            glVertex2i(position.x, position.y + size.height);
            glEnd();

            scene_->draw();

            glViewport(0, 0, width_, height_);
#endif
        }
    };

    std::auto_ptr<Screen>
        createEditorScreen(Window *window)
    {
        return std::auto_ptr<Screen>(new EditorScreen(window));
    }
}