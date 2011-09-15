#ifndef MORTIFIED_APPLICATION_HPP
#define MORTIFIED_APPLICATION_HPP

namespace mortified {
    class Application {
    public:
        virtual ~Application()
        { }

        virtual int main(int argc, char **argv) = 0;
    };
}

#endif
