
#include <sstream>
#include "File.h"

File::File(const string &path, ios_base::openmode openmode) {
    this->path = path;
    this->openmode = openmode;
    this->file.open(path.c_str(), openmode);
}

File::~File() {
}

void File::write(const string &content) {
    this->file << content << endl;
}

vector<string> File::read() {
    std::string line;
    vector<string> lines;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}


long File::getSize() {
    long size = 0;
    if (file.is_open() && file.good()) {
        long currentPosition = this->file.tellp();
        this->file.seekp(0, std::ios::end);
        size = this->file.tellp();
        this->file.seekp(currentPosition);
    }

    return size;
}

string File::getPath() {
    return this->path;
}

void File::close() {
    if (this->file.is_open()) {
        this->file.close();
    }
}

void File::setOpenmode(ios_base::openmode openmode) {
    this->openmode = openmode;
}
