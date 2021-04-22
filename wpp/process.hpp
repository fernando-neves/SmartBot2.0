#ifndef PROCESS_HPP
#define PROCESS_HPP

/* C++ INCLUDES */
#include <unordered_map>
#include <cstdio>
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <codecvt>
#include <locale>
#include <xutility>

#undef max

namespace wpp
{
    namespace _private
    {
        using convert_t = std::codecvt_utf8<wchar_t>;
        static std::wstring_convert<convert_t, wchar_t> strconverter;

        static bool icompare_pred(uint8_t a, uint8_t b){
            return ::tolower(a) == ::tolower(b);
        }
        static std::string to_string(std::wstring wstr)
        {
            return strconverter.to_bytes(wstr);
        }
        static std::wstring to_wstring(std::string str)
        {
            return strconverter.from_bytes(str);
        }
        static bool icompare(std::string a, std::string b){
            if (a.length() == b.length())
                return std::equal(b.begin(), b.end(), a.begin(), icompare_pred);
            else
                return false;
        }
    }

    namespace process
    {
        static uint32_t get_current_id() {
           return GetCurrentProcessId();
        }

        static HANDLE get_process_handle(uint32_t process_id = std::numeric_limits<uint32_t>::max())
        {
            if(process_id == std::numeric_limits<uint32_t>::max())
            {
                process_id = get_current_id();
            }

            if(process_id == std::numeric_limits<uint32_t>::max())
            {
                return NULL;
            }

            return  OpenProcess(PROCESS_VM_READ, FALSE, process_id);
        }

        static uintptr_t get_module_base(const std::string module_name, uint32_t process_id = std::numeric_limits<uint32_t>::max())
        {
            if (process_id == std::numeric_limits<uint32_t>::max())
            {
                process_id = get_current_id();
            }

            if (process_id == std::numeric_limits<uint32_t>::max())
            {
                return std::numeric_limits<uintptr_t>::max();
            }

            MODULEENTRY32 lp_module_entry = { 0 };
            const auto h_snap_shot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, process_id);
            if (!h_snap_shot)
            {
                return std::numeric_limits<uintptr_t>::max();
            }

            lp_module_entry.dwSize = sizeof(lp_module_entry);
            auto b_module = Module32First(h_snap_shot, &lp_module_entry);
            while (b_module)
            {
                const std::wstring w_module_name = std::wstring(lp_module_entry.szModule);
                const std::string current_module_name = _private::to_string(w_module_name);

                if (_private::icompare(current_module_name, module_name))
                {
                    CloseHandle(h_snap_shot);
                    return reinterpret_cast<uintptr_t>(lp_module_entry.modBaseAddr);
                }
                b_module = Module32Next(h_snap_shot, &lp_module_entry);
            }
            CloseHandle(h_snap_shot);

            return std::numeric_limits<uintptr_t>::max();
        }

        static std::unordered_map<uint32_t, std::string> get_all_process_name()
        {
            std::unordered_map<uint32_t, std::string> retval;

            PROCESSENTRY32 entry;
            entry.dwSize = sizeof(PROCESSENTRY32);

            HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
            if (Process32First(snapshot, &entry) == TRUE)
            {
                while (Process32Next(snapshot, &entry) == TRUE)
                {
                    const std::wstring w_process_name = std::wstring(entry.szExeFile);
                    const std::string process_name = _private::to_string(w_process_name);
                    const uint32_t process_id = entry.th32ProcessID;

                    retval.insert({process_id, process_name});
               }
           }

            return retval;
        }

        static uint32_t get_process_id(const std::string process_name)
        {
            const auto process_list = get_all_process_name();
            for(auto current_process : process_list)
            {
                if (_private::icompare(process_name, current_process.second))
                {
                    return current_process.first;
                }
            }
            return std::numeric_limits<uint32_t>::max();
        }
    }
}
#endif // PROCESS_HPP
