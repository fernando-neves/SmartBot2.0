#ifndef DEFINES_H
#define DEFINES_H

/* C++ INCLUDES */
#include <cstdint>

#define PATH_DISTANCE_MAX 128
#define PATH_CENTER 128
#define USE_ON_OTSERVER  1
#define DELAY_REFRESH_THREAD 250

static constexpr int32_t NETWORKMESSAGE_MAXSIZE = 24590;
static constexpr int16_t MAP_WIDTH = 256;
static constexpr int16_t MAP_HEIGHT = 256;
static constexpr int16_t STARTING_X = MAP_WIDTH / 2;
static constexpr int16_t STARTING_Y = MAP_HEIGHT / 2;

#define WPP_SETTER(type, name) void set_##name (type _name) { name = _name; }
#define WPP_SETTER_MTX(type, name, mtx) void set_##name (type _name) { mtx.lock(); this->name = std::move(_name); mtx.unlock(); }

#define WPP_GETTER(type, name) type get_##name () { return name; }
#define WPP_GETTER_MTX(type, name, mtx) type get_##name () { mtx.lock(); type temp = std::move(this->name); mtx.unlock(); return std::move(temp); }

#define WPP_GET_SET(type, name) WPP_SETTER(type, name); WPP_GETTER(type, name);
#define WPP_GET_SET_MTX(type, name, mtx) WPP_SETTER_MTX(type, name, mtx); WPP_GETTER_MTX(type, name, mtx);

#define WPP_DECLARE(type, name) type name;

#define WPP_DECLARE_GET_SET(type, name, mtx) private: WPP_DECLARE(type, name) public: WPP_GET_SET_MTX(type, name, mtx) private:
#define DECLARE_GET_SET(type, name) private: WPP_DECLARE(type, name) public: WPP_GET_SET(type, name) private:

#endif // DEFINES_H
