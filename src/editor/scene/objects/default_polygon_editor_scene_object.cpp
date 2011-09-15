#include "default_polygon_editor_scene_object.hpp"

#include "editor_scene_object_base.hpp"
#include "geometry.hpp"
#include "polygon_editor_scene_object.hpp"

#include <SDL/SDL_opengl.h>

namespace mortified {
    class DefaultPolygonEditorSceneObject :
        public virtual PolygonEditorSceneObject,
        private virtual EditorSceneObjectBase
    {
    public:
        Polygon2 *polygon()
        {
            return &polygon_;
        }

        Polygon2 const *polygon() const
        {
            return &polygon_;
        }

        void draw()
        {
            glBegin(GL_LINE_LOOP);
            for (std::size_t i = 0; i < polygon_.vertices.size(); ++i) {
                glVertex2f(polygon_.vertices[i].x, polygon_.vertices[i].y);
            }
            glEnd();
        }

    private:
        Polygon2 polygon_;
    };

    std::auto_ptr<EditorSceneObject> createPolygonEditorSceneObject()
    {
        return std::auto_ptr<EditorSceneObject>
            (new DefaultPolygonEditorSceneObject);
    }
}
