#include "physics_draw.hpp"

#include "geometry.hpp"

#include <iostream>
#include <vector>
#include <SDL/SDL_opengl.h>

namespace mortified {
    class PhysicsDraw :
    public b2Draw
    {
    public:
        PhysicsDraw()
        {
            transform_.SetIdentity();
            SetFlags(e_shapeBit);
            Polygon2 circlePolygon(Circle2(Vector2(0.0f, 0.0f), 1.0f), 32);
            for (int i = 0; i < circlePolygon.size(); ++i) {
                Vector2 vertex = circlePolygon.vertices[i];
                circleVertices_.push_back(b2Vec2(vertex.x, vertex.y));
            }
        }
        
        void DrawPolygon(b2Vec2 const *vertices, int32 vertexCount,
                         b2Color const &color)
        {
            (void) color;
            
            glBegin(GL_LINE_LOOP);
            for (int32 i = 0; i < vertexCount; ++i) {
                b2Vec2 transformedVertex = b2Mul(transform_, vertices[i]);
                glVertex2f(transformedVertex.x, transformedVertex.y);
            }
            glEnd();
        }
        
        void DrawSolidPolygon(b2Vec2 const *vertices, int32 vertexCount,
                              b2Color const &color)
        {
            DrawPolygon(vertices, vertexCount, color);
        }
        
        void DrawCircle(b2Vec2 const &center, float32 radius,
                        b2Color const &color)
        {
            (void) color;
            
            glBegin(GL_LINE_LOOP);
            for (std::size_t i = 0; i < circleVertices_.size(); ++i) {
                b2Vec2 vertex = center + radius * circleVertices_[i];
                b2Vec2 transformedVertex = b2Mul(transform_, vertex);
                glVertex2f(transformedVertex.x, transformedVertex.y);
            }
            glEnd();
        }
        
        void DrawSolidCircle(b2Vec2 const &center, float32 radius,
                             b2Vec2 const &axis, b2Color const &color)
        {
            DrawCircle(center, radius, color);
            DrawSegment(center, center + radius * axis, color);
        }
        
        void DrawSegment(b2Vec2 const &p1,
                         b2Vec2 const &p2, b2Color const &color)
        {
            (void) color;
            
            b2Vec2 transformedP1 = b2Mul(transform_, p1);
            b2Vec2 transformedP2 = b2Mul(transform_, p2);
            glBegin(GL_LINES);
            glVertex2f(transformedP1.x, transformedP1.y);
            glVertex2f(transformedP2.x, transformedP2.y);
            glEnd();
        }
        
        void DrawTransform(b2Transform const &transform)
        {
            transform_ = transform;
        }
        
    private:
        b2Transform transform_;
        std::vector<b2Vec2> circleVertices_;
    };

    std::auto_ptr<b2Draw> createPhysicsDraw()
    {
        return std::auto_ptr<b2Draw>(new PhysicsDraw);
    }
}
