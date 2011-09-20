#ifndef MORTIFIED_GRAPHICS_RESOURCE_HPP
#define MORTIFIED_GRAPHICS_RESOURCE_HPP

namespace mortified {
    class GraphicsResource {
    public:
        virtual ~GraphicsResource()
        { }

        /// Does the resource exist in the graphics context?
        virtual bool valid() const = 0;

        /// Create the resource in the graphics context.
        virtual void create() = 0;

        /// Destroy the resource in the graphics context.
        virtual void destroy() = 0;

        /// Called when the graphics context has been lost.
        virtual void invalidate() = 0;
    };
}

#endif
