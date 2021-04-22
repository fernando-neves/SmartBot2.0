#ifndef ADDRESS_MANAGER_H
#define ADDRESS_MANAGER_H

/* THIS PROJECT INCLUDES */
#include <helper/includes.h>
#include <memory_manager.h>

/* C++ INCLUDES */
#include <stdlib.h>
#include <stdio.h>

enum ADDRESS_TYPE : uint32_t
{
    ADDRESS_PLAYER_ID,
    ADDRESS_BATTLE_LIST,
    ADDRESS_HEALTH_TOTAL,
    ADDRESS_HEALTH_CURRENT,
    ADDRESS_MANA_TOTAL,
    ADDRESS_MANA_CURRENT,
    ADDRESS_BASE_TABS,
    ADDRESS_XOR,
    ADDRESS_LEVEL,
    ADDRESS_EXP
};

static std::unordered_map<uint8_t /* address_name */,
    std::pair<uint32_t /* address_memory */,
    std::vector<uint32_t> /* address_offset */>
> address_memory =
{
    { ADDRESS_PLAYER_ID,		{0x70F050, {}}},
    { ADDRESS_BATTLE_LIST,		{0x76A48C, {}}},
    { ADDRESS_HEALTH_TOTAL,     {0x70E048, {}}},
    { ADDRESS_HEALTH_CURRENT,   {0x70E000, {}}},
    { ADDRESS_MANA_TOTAL,		{0x57045C, {}}},
    { ADDRESS_MANA_CURRENT,     {0x57048C, {}}},
    { ADDRESS_BASE_TABS,        {0x570744, {}}},
    { ADDRESS_XOR,              {0x570458, {}}},
    { ADDRESS_LEVEL,            {0x570470, {}}},
    { ADDRESS_EXP,              {0x570460, {}}},
};

struct my_player_info
{
    uint8_t get_health_percent()
    {
        if (m_current_health == 0 || m_current_health == UINT32_MAX)
        {
            return UINT8_MAX;
        }

        if (m_total_health == 0 || m_total_health == UINT32_MAX)
        {
            return UINT8_MAX;
        }

        return static_cast<int>(static_cast<double>(m_current_health) / (static_cast<double>(m_total_health) /
            static_cast<double>(100)));
    }
    uint8_t get_mana_percent()
    {
        if (m_current_mana == 0 || m_current_mana == UINT32_MAX)
        {
            return UINT8_MAX;
        }

        if (m_total_mana == 0 || m_total_mana == UINT32_MAX)
        {
            return UINT8_MAX;
        }

        return static_cast<int>(static_cast<double>(m_current_mana) / (static_cast<double>(m_total_mana) / static_cast<
            double>(100)));
    }

    std::atomic_uint32_t m_current_health{ UINT32_MAX };
    std::atomic_uint32_t m_total_health{ UINT32_MAX };
    std::atomic_uint32_t m_current_mana{ UINT32_MAX };
    std::atomic_uint32_t m_total_mana{ UINT32_MAX };

public:
private:
};

class address_manager : public utils::singleton<address_manager>
{
public:
    address_manager()
    {
        m_current_player_info = std::make_shared<my_player_info>();

        this->scheduler_refresh_infos();
    }

private:
    void refresh_player_info()
    {
        const auto& address_health_total = address_memory[ADDRESS_HEALTH_TOTAL];
        const auto& address_health_current = address_memory[ADDRESS_HEALTH_CURRENT];
        const auto& address_mana_total= address_memory[ADDRESS_MANA_TOTAL];
        const auto& address_mana_current = address_memory[ADDRESS_MANA_CURRENT];
        const auto& address_xor = address_memory[ADDRESS_XOR];

        const auto xor_health_total = memory_manager::instance()->read_memory_block<uint32_t>(address_health_total.first);
        const auto xor_health_current = memory_manager::instance()->read_memory_block<uint32_t>(address_health_current.first);
        const auto xor_mana_total = memory_manager::instance()->read_memory_block<uint32_t>(address_mana_total.first);
        const auto xor_mana_current = memory_manager::instance()->read_memory_block<uint32_t>(address_mana_current.first);
        const auto current_xor = memory_manager::instance()->read_memory_block<uint32_t>(address_xor.first);

        const uint32_t health_total = xor_health_total ^ current_xor;
        const uint32_t health_current = xor_health_current ^ current_xor;

        const uint32_t mana_total = xor_mana_total ^ current_xor;
        const uint32_t mana_current = xor_mana_current ^ current_xor;

        m_current_player_info->m_total_health = health_total;
        m_current_player_info->m_current_health = health_current;

        m_current_player_info->m_total_mana= mana_total;
        m_current_player_info->m_current_mana = mana_current;
    }

    void refresh_infos()
    {

    }

    void scheduler_refresh_infos()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10 * 1000));

        auto bounded_function = [=]()
        {
            wpp::time_ns::timer_chronometer chronometer;
            while (true)
            {
                chronometer.reset();

                refresh_infos();
                //std::cout << "passed: " << chronometer.elapsed_milliseconds() << " (mili)" << std::endl;

                std::this_thread::sleep_for(std::chrono::milliseconds(DELAY_REFRESH_THREAD));
            }
        };

        auto bounded_function2 = [=]() {
            while (true)
            {
                refresh_player_info();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        };

        std::thread(bounded_function).detach();
        std::thread(bounded_function2).detach();
    }

private:
    std::shared_ptr<my_player_info> m_current_player_info{ nullptr };
};

#endif // ADDRESS_MANAGER_H
