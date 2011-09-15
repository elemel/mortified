#include "default_style_parser.hpp"

#include "default_style_sheet.hpp"
#include "stream.hpp"
#include "style_parser.hpp"
#include "style_sheet.hpp"
#include "widget_style.hpp"

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace mortified {
    class DefaultStyleParser :
        public StyleParser
    {
    public:
        DefaultStyleParser() :
            names_(1),
            bases_(1),
            args_(1)
        { }

        std::auto_ptr<StyleSheet> parse(Stream *stream)
        {
            stream_ = stream;
            line_ = 0;
            nextChar_ = 0;
            nextToken_.clear();

            std::auto_ptr<StyleSheet> styleSheet = createStyleSheet();
            while (peekToken() != "") {
                readStyle();
                styleSheet->updateStyles(&names_[0], nameCount_,
                                         &bases_[0], baseCount_,
                                         &style_, mask_);
            }
            return styleSheet;
        }

    private:
        Stream *stream_;
        int line_;
        char nextChar_;
        std::string token_;
        std::string nextToken_;
        std::vector<std::string> names_;
        int nameCount_;
        std::vector<std::string> bases_;
        int baseCount_;
        std::string property_;
        std::vector<std::string> args_;
        int argCount_;
        WidgetStyle style_;
        StyleMask mask_;

        void readStyle()
        {
            nameCount_ = 0;
            baseCount_ = 0;
            mask_ = StyleMask();

            readNames();
            if (peekToken() == ":") {
                readToken();
                readBases();
            }
            if (peekToken() == "{") {
                readToken();
                readProperties();
                if (peekToken() != "}") {
                    throw std::runtime_error(std::string("Expected \"}\" token, found \"") + peekToken() + "\".");
                }
                readToken();
            } else if (peekToken() != ";") {
                throw std::runtime_error(std::string("Expected \"{\" or \";\" token, found \"") + peekToken() + "\".");
            }
        }

        void readNames()
        {
            for (;;) {
                if (!isWord(peekToken())) {
                    throw std::runtime_error(std::string("Expected word token, found \"") + peekToken() + "\".");
                }
                pushName(readToken());
                if (peekToken() == ",") {
                    readToken();
                } else {
                    break;
                }
            }
        }

        void readBases()
        {
            for (;;) {
                if (!isWord(peekToken())) {
                    throw std::runtime_error(std::string("Expected word token, found \"") + peekToken() + "\".");
                }
                pushBase(readToken());
                if (peekToken() == ",") {
                    readToken();
                } else {
                    break;
                }
            }
        }

        void readProperties()
        {
            for (;;) {
                if (peekToken() == "}") {
                    break;
                }
                splitProperty();
                parseProperty();
            }
        }

        void splitProperty()
        {
            argCount_ = 0;

            if (!isWord(peekToken())) {
                throw std::runtime_error(std::string("Expected word token, found \"") + peekToken() + "\".");
            }
            property_ = readToken();
            if (peekToken() != ":") {
                throw std::runtime_error(std::string("Expected \":\" token, found \"") + peekToken() + "\".");
            }
            readToken();
            for (;;) {
                if (!isWord(peekToken())) {
                    throw std::runtime_error(std::string("Expected word token, found \"") + peekToken() + "\".");
                }
                pushArg(readToken());
                if (peekToken() == ",") {
                    readToken();
                } else {
                    break;
                }
            }
            if (peekToken() != ";") {
                throw std::runtime_error(std::string("Expected \";\" token, found \"") + peekToken() + "\".");
            }
            readToken();
        }

        void parseProperty()
        {
            if (property_ == "weight") {
                parseWeightProperty();
            } else if (property_ == "stretch") {
                parseStretchProperty();
            } else if (property_ == "alignment") {
                parseAlignmentProperty();
            } else if (property_ == "padding") {
                parsePaddingProperty();
            } else if (property_ == "border") {
                parseBorderProperty();
            } else if (property_ == "spacing") {
                parseSpacingProperty();
            } else if (property_ == "color") {
                parseColorProperty();
            } else if (property_ == "background-color") {
                parseBackgroundColorProperty();
            } else if (property_ == "border-color") {
                parseBorderColorProperty();
            } else {
                throw std::runtime_error(std::string("Invalid property \"") + property_ + "\".");
            }
        }

        void parseWeightProperty()
        {
            if (argCount_ == 1) {
                style_.weight = WidgetWeight(parseFloat(args_[0]));
            } else if (argCount_ == 2) {
                style_.weight = WidgetWeight(parseFloat(args_[0]),
                                             parseFloat(args_[1]));
            } else {
                std::stringstream message;
                message << "Expected 1 or 2 arguments for " << property_
                        << " property, found " << argCount_ << ".";
                throw std::runtime_error(message.str());
            }
            mask_.weight = true;
        }

        void parseStretchProperty()
        {
            if (argCount_ == 1) {
                style_.stretch = WidgetStretch(parseFloat(args_[0]));
            } else if (argCount_ == 2) {
                style_.stretch = WidgetStretch(parseFloat(args_[0]),
                                               parseFloat(args_[1]));
            } else {
                std::stringstream message;
                message << "Expected 1 or 2 arguments for " << property_
                        << " property, found " << argCount_ << ".";
                throw std::runtime_error(message.str());
            }
            mask_.stretch = true;
        }

        void parseAlignmentProperty()
        {
            if (argCount_ == 1) {
                style_.alignment = WidgetAlignment(parseFloat(args_[0]));
            } else if (argCount_ == 2) {
                style_.alignment = WidgetAlignment(parseFloat(args_[0]),
                                                   parseFloat(args_[1]));
            } else {
                std::stringstream message;
                message << "Expected 1 or 2 arguments for " << property_
                        << " property, found " << argCount_ << ".";
                throw std::runtime_error(message.str());
            }
            mask_.alignment = true;
        }

        void parsePaddingProperty()
        {
            if (argCount_ == 1) {
                style_.padding = WidgetPadding(parseInt(args_[0]));
            } else if (argCount_ == 2) {
                style_.padding = WidgetPadding(parseInt(args_[0]),
                                               parseInt(args_[1]));
            } else if (argCount_ == 4) {
                style_.padding = WidgetPadding(parseInt(args_[0]),
                                               parseInt(args_[1]),
                                               parseInt(args_[2]),
                                               parseInt(args_[3]));
            } else {
                std::stringstream message;
                message << "Expected 1, 2, or 4 arguments for " << property_
                        << " property, found " << argCount_ << ".";
                throw std::runtime_error(message.str());
            }
            mask_.padding = true;
        }

        void parseBorderProperty()
        {
            if (argCount_ == 1) {
                style_.border = WidgetBorder(parseInt(args_[0]));
            } else if (argCount_ == 2) {
                style_.border = WidgetBorder(parseInt(args_[0]),
                                             parseInt(args_[1]));
            } else if (argCount_ == 4) {
                style_.border = WidgetBorder(parseInt(args_[0]),
                                             parseInt(args_[1]),
                                             parseInt(args_[2]),
                                             parseInt(args_[3]));
            } else {
                std::stringstream message;
                message << "Expected 1, 2, or 4 arguments for " << property_
                        << " property, found " << argCount_ << ".";
                throw std::runtime_error(message.str());
            }
            mask_.border = true;
        }

        void parseSpacingProperty()
        {
            if (argCount_ == 1) {
                style_.spacing = WidgetSpacing(parseInt(args_[0]));
            } else if (argCount_ == 2) {
                style_.spacing = WidgetSpacing(parseInt(args_[0]),
                                               parseInt(args_[1]));
            } else {
                std::stringstream message;
                message << "Expected 1 or 2 arguments for " << property_
                        << " property, found " << argCount_ << ".";
                throw std::runtime_error(message.str());
            }
            mask_.spacing = true;
        }

        void parseColorProperty()
        {
            if (argCount_ != 1) {
                std::stringstream message;
                message << "Expected 1 argument for " << property_
                        << " property, found " << argCount_ << ".";
                throw std::runtime_error(message.str());
            }
            style_.color = parseColor(args_[0]);
            mask_.color = true;
        }

        void parseBackgroundColorProperty()
        {
            if (argCount_ != 1) {
                std::stringstream message;
                message << "Expected 1 argument for " << property_
                        << " property, found " << argCount_ << ".";
                throw std::runtime_error(message.str());
            }
            style_.backgroundColor = parseColor(args_[0]);
            mask_.backgroundColor = true;
        }

        void parseBorderColorProperty()
        {
            if (argCount_ != 1) {
                std::stringstream message;
                message << "Expected 1 argument for " << property_
                        << " property, found " << argCount_ << ".";
                throw std::runtime_error(message.str());
            }
            style_.borderColor = parseColor(args_[0]);
            mask_.borderColor = true;
        }

        int parseInt(std::string const &arg)
        {
            return std::atoi(arg.c_str());
        }

        float parseFloat(std::string const &arg)
        {
            return float(std::atof(arg.c_str()));
        }

        WidgetColor parseColor(std::string const &arg)
        {
            if (arg.size() == 4 && arg[0] == '#') {
                return WidgetColor(parseComponent(arg[1]),
                                   parseComponent(arg[2]),
                                   parseComponent(arg[3]));
            }
            if (arg.size() == 5 && arg[0] == '#') {
                return WidgetColor(parseComponent(arg[1]),
                                   parseComponent(arg[2]),
                                   parseComponent(arg[3]),
                                   parseComponent(arg[4]));
            }
            if (arg.size() == 7 && arg[0] == '#') {
                return WidgetColor(parseComponent(arg[1], arg[2]),
                                   parseComponent(arg[3], arg[4]),
                                   parseComponent(arg[5], arg[6]));
            }
            if (arg.size() == 9 && arg[0] == '#') {
                return WidgetColor(parseComponent(arg[1], arg[2]),
                                   parseComponent(arg[3], arg[4]),
                                   parseComponent(arg[5], arg[6]),
                                   parseComponent(arg[7], arg[8]));
            }

            if (arg == "black") {
                return WidgetColor(0);
            } else if (arg == "blue") {
                return WidgetColor(0, 0, 255);
            } else if (arg == "cyan") {
                return WidgetColor(0, 255, 255);
            } else if (arg == "green") {
                return WidgetColor(0, 255, 0);
            } else if (arg == "magenta") {
                return WidgetColor(255, 0, 255);
            } else if (arg == "red") {
                return WidgetColor(255, 0, 0);
            } else if (arg == "white") {
                return WidgetColor(255);
            } else if (arg == "yellow") {
                return WidgetColor(255, 255, 0);
            }

            throw std::runtime_error(std::string("Expected color name or color in format \"#RGB\", \"#RGBA\", \"#RRGGBB\", or  \"#RRGGBBAA\"; found \"") + arg + "\".");
        }

        int parseHex(char c)
        {
            if ('0' <= c && c <= 9) {
                return int(c) - int('0');
            } else if ('a' <= c && c <= 'f') {
                return 10 + int(c) - int('a');
            } else if ('A' <= c && c <= 'F') {
                return 10 + int(c) - int('A');
            } else {
                return 0;
            }
        }

        int parseComponent(char c)
        {
            return 17 * parseHex(c);
        }

        int parseComponent(char high, char low)
        {
            return 16 * parseHex(high) + parseHex(low);
        }

        bool isWord(std::string const &token)
        {
            return !token.empty() && strchr(",:;{}", token[0]) == 0;
        }

        void pushName(std::string const &name)
        {
            if (int(names_.size()) <= nameCount_) {
                names_.resize(nameCount_ + 1);
            }
            names_[nameCount_] = name;
            ++nameCount_;
        }

        void pushBase(std::string const &base)
        {
            if (int(bases_.size()) <= baseCount_) {
                bases_.resize(baseCount_ + 1);
            }
            bases_[baseCount_] = base;
            ++baseCount_;
        }

        void pushArg(std::string const &arg)
        {
            if (int(args_.size()) <= argCount_) {
                args_.resize(argCount_ + 1);
            }
            args_[argCount_] = arg;
            ++argCount_;
        }

        std::string const &readToken()
        {
            token_ = peekToken();
            nextToken_.clear();
            return token_;
        }

        std::string const &peekToken()
        {
            if (nextToken_.empty()) {
                while (std::isspace(peekChar())) {
                    readChar();
                }
                while (peekChar() && !std::isspace(peekChar())) {
                    if (std::strchr(",:;{}", peekChar())) {
                        if (nextToken_.empty()) {
                            nextToken_.push_back(readChar());
                        }
                        break;
                    } else {
                        nextToken_.push_back(readChar());
                    }
                }
            }
            return nextToken_;
        }

        char readChar()
        {
            char c = peekChar();
            nextChar_ = 0;
            return c;
        }

        char peekChar()
        {
            if (nextChar_ == 0) {
                if (stream_->read(&nextChar_, 1) == 0) {
                    nextChar_ = 0;
                }
            }
            return nextChar_;
        }
    };

    std::auto_ptr<StyleParser> createStyleParser()
    {
        return std::auto_ptr<StyleParser>(new DefaultStyleParser);
    }
}
