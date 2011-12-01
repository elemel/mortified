#ifndef MORTIFIED_APPLICATION_HPP
#define MORTIFIED_APPLICATION_HPP

#include <list>
#include <memory>

namespace mortified {
    class Screen;
    class Window;

    class Application {
    public:
        typedef std::list<Screen *> ScreenList;
        typedef ScreenList::iterator ScreenIterator;
        typedef ScreenList::const_iterator ConstScreenIterator;

        virtual ~Application()
        { }

        virtual int main(int argc, char **argv) = 0;

        virtual void addScreen(std::auto_ptr<Screen> screen) = 0;
        virtual std::auto_ptr<Screen> removeScreen(Screen *screen) = 0;
        virtual Screen *getCurrentScreen() = 0;        

        virtual Window *getWindow() = 0;
        virtual Window const *getWindow() const = 0;
    };
}

#endif
