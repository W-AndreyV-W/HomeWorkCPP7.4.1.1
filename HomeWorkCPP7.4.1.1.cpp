#include <iostream>
#include <fstream>

class PrintableAsText {

public:

    virtual std::string printable(const std::string& data) const {

        return data;
    }
};

class Data : public PrintableAsText {

public:

    explicit Data(PrintableAsText* _printableastext) : printableastext(_printableastext) {}

    PrintableAsText* printableastext;
};

class PrintableAsHTML : public Data {

public:

    explicit PrintableAsHTML(PrintableAsText* _printableastext) :Data(_printableastext) {}

    virtual std::string printable(const std::string& data) const {

        return "<html>" + printableastext->printable(data) + "<html/>";
    }
};

class PrintableAsJSON : public Data {

public:

    explicit PrintableAsJSON(PrintableAsText* _printableastext) :Data(_printableastext) {}

    virtual std::string printable(const std::string& data) const {

        return "{ \"data\": \"" + printableastext->printable(data) + "\"}";
    }
};



void saveTo(std::ofstream& out, const std::string data, PrintableAsText* printableastext) {

    out << printableastext->printable(data);
}



void saveToAsHTML(std::ofstream& out, const std::string& data) {

    auto text_format = new PrintableAsHTML(new PrintableAsText());
    saveTo(out, data, text_format);
}

void saveToAsJSON(std::ofstream& out, const std::string& data) {

    auto text_format = new PrintableAsJSON(new PrintableAsText());
    saveTo(out, data, text_format);
}

void saveToAsText(std::ofstream& out, const std::string& data) {

    auto text_format = new PrintableAsText();
    saveTo(out, data, text_format);
}



int main() {

    std::ofstream file("out.txt", std::ios::app);
    std::string messing("Hello World!");

    saveToAsHTML(file, messing);
    saveToAsJSON(file, messing);
    saveToAsText(file, messing);
}