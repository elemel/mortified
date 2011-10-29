#ifndef MORTIFIED_DEFAULT_STYLE_SHEET_HPP
#define MORTIFIED_DEFAULT_STYLE_SHEET_HPP

#include <memory>

namespace mortified {
    class StyleSheet;

    std::auto_ptr<StyleSheet> createStyleSheet();
}

#endif
