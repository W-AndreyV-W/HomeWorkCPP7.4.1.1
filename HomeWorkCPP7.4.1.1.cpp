#include <iostream>
#include <fstream>

class Printable {

public:

    virtual std::string printable(const std::string& data) const = 0;
};

class PrintableAsText : public Printable {

public:

    std::string printable(const std::string& data) const override {

        return data;
    }
};

class PrintableAsHTML : public Printable {

public:

    std::string printable(const std::string& data) const override{

        return "<html>" + data + "<html/>";
    }
};

class PrintableAsJSON : public Printable {

public:

    std::string printable(const std::string& data) const override{

        return "{ \"data\": \"" + data + "\"}";
    }
};



void saveTo(std::ofstream& out, const std::string data, const Printable& printable) {

    out << printable.printable(data) << std::endl;
}

int main() {

    std::ofstream file("out.txt", std::ios::app);
    std::string messing("Hello World!");

    PrintableAsText printableAsText;
    PrintableAsHTML printableAsHTML;
    PrintableAsJSON printableAsJSON;

    saveTo(file, messing, printableAsText);
    saveTo(file, messing, printableAsHTML);
    saveTo(file, messing, printableAsJSON);

    file.close();
}