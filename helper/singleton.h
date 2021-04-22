#ifndef SINGLETON_H
#define SINGLETON_H

namespace utils
{
    /**
     * @class singleton
     * @tparam same as class designed for single instance
     * @brief derive custom class from this template
     */
    template <typename T>
    class singleton
    {
    public:
        /**
         * @brief instance
         * @return the only instance of class
         */
        static T* instance()
        {
            static T instance;
            return &instance;
        }
        singleton() = default;
        /**
         * @brief singleton  Copy constructor
         */
        singleton(singleton const&) = delete;
        /**
         * @brief singleton move constructor
         */
        singleton(singleton&&) = delete;
        /**
         * @brief operator = assign operator
         * @return
         */
        singleton& operator=(singleton const&) = delete;
        /**
         * @brief operator = Move assignment operator
         * @return
         */
        singleton& operator=(singleton&&) = delete;
    };
}

#endif // SINGLETON_H
