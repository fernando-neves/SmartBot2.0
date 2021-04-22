#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

/* THIS PROJECT INCLUDES */
#include <memory_manager.h>
#include <helper/includes.h>

/* QT INCLUDES */
#include <qprocess.h>

/* WPP INCLUDES */
#include <wpp/process.hpp>

class process_manager : public utils::singleton<process_manager>
{
public:
    process_manager()
    {
        std::cout << __FUNCTION__ << "[" << __LINE__ << "] - " << "CALL_ME" << std::endl;
        this->scheduler_refresh_tibia_clients();
    }

    void refresher_tibia_clients()
    {
        const auto process_id = wpp::process::get_process_id("Tibia.exe");
        const auto process_handle = wpp::process::get_process_handle(process_id);
        const auto process_base_address = wpp::process::get_module_base("Tibia.exe", process_id);

        if(process_id == UINT32_MAX || process_handle == NULL)
        {
            m_load_success = false;
            return;
        }

        memory_manager::instance()->initialize(
            process_handle,
            process_base_address);

        m_load_success = true;
    }

private:
    void scheduler_refresh_tibia_clients()
    {
        const auto bounded_function = [=]()
        {
            while(true)
            {
                this->refresher_tibia_clients();

                std::this_thread::sleep_for(std::chrono::milliseconds(10 * 1000));
            }
        };

        std::thread(bounded_function).detach();
    }

private:
    std::atomic_bool m_load_success{ false };

};

#endif // PROCESS_MANAGER_H
