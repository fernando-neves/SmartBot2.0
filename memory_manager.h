#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

/* THIS PROJECT INCLUDES */
#include <helper/includes.h>

#undef max

class memory_manager : public utils::singleton<memory_manager>
{
public:
    void initialize(
        const HANDLE process_handle,
        const uint32_t process_base_address)
    {
        m_process_handle = process_handle;
        m_process_base_address = process_base_address;
    }

    template <class T>
    T read_memory_block(
        const uint32_t read_address,
        const std::vector<uint32_t>& offset_list = std::vector<uint32_t>(),
        const bool use_base_address = true)
    {
        if (read_address == UINT32_MAX)
        {
            return T();
        }

        if (m_process_handle == nullptr || m_process_base_address == std::numeric_limits<uint32_t>::max())
        {
            return T();
        }

        const auto bytes_to_read = sizeof(T);
        auto buffer_read_address = std::string("", bytes_to_read);
        const auto current_address = use_base_address ? (read_address + m_process_base_address) : read_address;
        if (offset_list.empty())
        {
            ReadProcessMemory(m_process_handle, reinterpret_cast<LPCVOID>(current_address), (void*)buffer_read_address.data(),
                              bytes_to_read, nullptr);

            return *reinterpret_cast<T*>((void*)buffer_read_address.data());
        }

        uint32_t result_address = 0U;
        ReadProcessMemory(m_process_handle, reinterpret_cast<LPCVOID>(current_address), &result_address, 4, nullptr);

        for (auto i = 0; i < offset_list.size(); ++i)
        {
            const auto address_to_read = result_address + offset_list[i];

            if ((i + 1) >= offset_list.size())
            {
                ReadProcessMemory(m_process_handle, reinterpret_cast<LPCVOID>(address_to_read), (void*)buffer_read_address.data(),
                                  bytes_to_read, nullptr);

                int x = 0;
                return *(T*)(void*)buffer_read_address.data();
            }

            ReadProcessMemory(m_process_handle, reinterpret_cast<LPCVOID>(address_to_read), &result_address, 4,
                              nullptr);
        }

        ReadProcessMemory(m_process_handle, reinterpret_cast<LPCVOID>(read_address), (void*)buffer_read_address.data(),
                          bytes_to_read, nullptr);

        int x = 0;
        return  *(T*)(void*)buffer_read_address.data();
    }

private:
private:
    HANDLE m_process_handle{nullptr};
    uint32_t m_process_base_address{std::numeric_limits<uint32_t>::max()};
};

#endif // MEMORY_MANAGER_H
