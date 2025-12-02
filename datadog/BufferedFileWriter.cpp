// BufferedFileWriter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class FileOut {
private:
    ofstream m_outFile;
public:
    FileOut(const string& path)
        : m_outFile(path, ios::app | ios::binary) {
        if (!m_outFile) {
            cerr << "Failed to open file!" << endl;
        }
    }
    // Writes the whole buffer to file
    int write(vector<char>& buf) {
        //std::vector<char> data = { 'H', 'e', 'l', 'l', 'o', '\n' };

        

        if (!m_outFile) {
            cerr << "Failed to open file!" << endl;
            return 1;
        }

        // Write vector to file
        m_outFile.write(buf.data(), buf.size()); // data.data() gives pointer to first element

        //m_outFile.close(); // always close the file
        cout << "Data written successfully." << endl;

        return 0;
    }
private:
    string m_path;
};

class BufferedFileWriter {
public:
    /*
    *  we want to hold reference to FileOut to avoid copying.
    *  because of that we MUST do the initialization of m_file in the 
    *  ctor initializion list and NOT inside the ctor body
    */
    BufferedFileWriter(FileOut& file, int buffer_size)
        : m_file(file), m_buffer_size(buffer_size) {

    }

    /*
        We need to flush the data in the dctor.
        Otherwise, when we exit the program the data in the buffer 
        will NOT be written to the disk
    */
    ~BufferedFileWriter() {
        flush();
    }
    void write(const vector<char>& bytes) {

        size_t bytes_p = 0;

        while (true) {

            size_t bytes_to_write;
            if (bytes.size()-bytes_p > m_buffer_size - m_buffer.size()) {
                bytes_to_write = m_buffer_size - m_buffer.size();
            }
            else {
                bytes_to_write = bytes.size() - bytes_p;
            }

            if (!bytes_to_write) {
                break;
            }

            m_buffer.insert(m_buffer.end(), bytes.begin() + bytes_p, bytes.begin() + bytes_p + bytes_to_write);


            //for (int i = 0; i < bytes_to_write; i++) {
            //    m_buffer.push_back(bytes[bytes_p+i]);
            //}

            if (m_buffer.size() == m_buffer_size) {
                flush();
            }
            bytes_p = bytes_p + bytes_to_write;
        }

    }


    void flush() {

        if (m_buffer.size() > 0) {
            m_file.write(m_buffer);
            m_buffer.resize(0);
        }
    }
private:
    FileOut& m_file;
    int m_buffer_size;
    vector<char> m_buffer;
};

int main()
{
    std::cout << "Hello World!\n";
    FileOut fo("test.log");

    BufferedFileWriter bfw(fo, 4);
    string str = "0123456789abcde";
    vector<char> data(str.begin(), str.end());
    bfw.write(data);
    //bfw.flush();
}


