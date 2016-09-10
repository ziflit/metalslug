
#ifndef METALSLUG_FILEUTIL_H
#define METALSLUG_FILEUTIL_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class File {
private:
    fstream file;
    string path;
    ios_base::openmode openmode;
public:
    /*
     * Pre: path valido.
     * Pos: Crea una nueva instancia.
     * Params:
     *      path direccion file
     *      mode: mode en que va a ser usado el archivo fstream::in o fstream::out
     */
    File(const string &path, ios_base::openmode mode);

    virtual ~File();

    /*
     * Pre: archivo abierto
     * Pos: escribe en el archivo el string pasado por argumento.
     */
    virtual void write(const string &);

    /*
     * Pre: archivo abierto
     * Pos:
     */
    virtual vector<string> read();

    /*
     * Pre: -
     * Pos: devuelve el path del archivo.
     */
    string getPath();

    /*
     * Pre: -
     * Pos: devuelve el tamanio en bytes del archivo.
     */
    long getSize();

    void setOpenmode(ios_base::openmode openmode);


    virtual void close();

    bool isOpen() { return file.is_open(); }

};


#endif //METALSLUG_FILEUTIL_H
