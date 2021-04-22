#ifndef FILESYSTEM_H
#define FILESYSTEM_H

/* C++ INCLUDES */
#include <vector>
#include <string>
#include <ostream>
#include <fstream>

namespace wpp
{
    namespace file
    {
        static std::string get_file_contents(const std::string& path)
        {
            std::ifstream _ifs(path, std::ios::ios_base::binary);
            if (_ifs)
            {
                std::vector<char> buffer((
                                             std::istreambuf_iterator<char>(_ifs)),
                                         (std::istreambuf_iterator<char>()));
                _ifs.close();
                return std::string(buffer.data(), buffer.size());
            }
            else
            {
                return std::string();
            }
        }

        static bool put_file_contents(const std::string& path, const std::string& content)
        {
            std::ofstream _ofs(path, std::ios::ios_base::binary | std::ios::ios_base::trunc);
            if (_ofs)
            {
                _ofs.write(content.data(), content.size());
                _ofs.close();
                return true;
            }
            return false;
        }

        static bool append_file_contents(const std::string& path, const std::string& content)
        {
            std::ofstream _ofs(path, std::ios::ios_base::binary | std::ios::ios_base::app);
            if (_ofs)
            {
                _ofs.write(content.data(), content.size());
                _ofs.close();
                return true;
            }
            return false;
        }
    }
}
#endif // FILESYSTEM_H
