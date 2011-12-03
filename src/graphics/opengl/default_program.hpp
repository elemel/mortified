#ifndef MORTIFIED_DEFAULT_PROGRAM_HPP
#define MORTIFIED_DEFAULT_PROGRAM_HPP

#include <boost/intrusive_ptr.hpp>

namespace mortified {
    class Context;
    class Program;
    
    boost::intrusive_ptr<Program>
    createProgram(boost::intrusive_ptr<Context> context);
}

#endif
