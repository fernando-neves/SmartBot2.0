#ifndef ENUMS_H
#define ENUMS_H

/* WINDOWS INCLUDES */
#include <WinUser.h>

/* C++ INCLUDES */
#include <stdint.h>

enum waypoint_type : uint16_t
{
    waypoint_t_none = 0,
    waypoint_t_walk = 1,
    waypoint_t_action = 2
};

enum map_type : uint8_t
{
    map_back_t = 0,
    map_back_t_mini,
    map_front_t,
    map_front_t_mini,
    map_front_t_special_area,
    map_front_t_advanced,
    map_front_t_clear,
    map_front_t_clear_minimap,
    map_front_t_advanced_mini,
    map_front_t_cached,
    map_front_t_cached_editable,
    map_front_t_cached_advanced,
    map_total_t,
    map_none_t = map_total_t
};

enum pathfind_walkability_type : uint8_t
{
    pathind_walkability_not_walkable,
    pathind_walkability_walkable,
    pathind_walkability_player,
    pathind_walkability_monster,
    pathind_walkability_summon,
    pathind_walkability_npc,
    pathind_walkability_furniture,
    pathind_walkability_rune_field,
    pathind_walkability_timed_not_walkable,
    pathind_walkability_near_depot_walkable,
    pathind_walkability_near_depot_unwalkable,
    pathind_walkability_undefined = 255
};

enum pathfind_walk_type : uint8_t
{
    pathfind_walk_none,
    pathfind_walk_request_start,
    pathfind_walk_going,
    pathfind_walk_not_reachable,
    pathfind_walk_overriden,
    pathfind_walk_canceled,
    pathfind_walk_reached,
    pathfind_walk_condition_has_to_stop,
    pathfind_walk_killed,
    pathfind_walk_params_null,
    pathfind_walk_state_none
};

enum side_type : uint8_t
{
    side_north,
    side_north_east,
    side_east,
    side_south_east,
    side_south,
    side_south_west,
    side_west,
    side_north_west,
    side_center
};

enum health_type : uint8_t
{
    health_t_none,
    health_t_mana,
    health_t_health,
    health_t_attack,
    health_t_attack_area,
};

enum spell_type : uint8_t
{
    spell_t_none,
    spell_t_healing,
    spell_t_on_target,
    spell_t_area,
    spell_t_rune_on_target,
    spell_t_rune_area,
};

enum spell_category_type : uint8_t
{
    spell_t_category_none,
    spell_t_category_attack,
    spell_t_category_recover,
    spell_t_category_support,
    spell_t_category_item,
    spell_t_category_total
};

enum hotkey_type : uint32_t
{
    hotkey_t_none = 0x0,
    hotkey_t_f1 = VK_F1,
    hotkey_t_f2 = VK_F2,
    hotkey_t_f3 = VK_F3,
    hotkey_t_f4 = VK_F4,
    hotkey_t_f5 = VK_F5,
    hotkey_t_f6 = VK_F6,
    hotkey_t_f7 = VK_F7,
    hotkey_t_f8 = VK_F8,
    hotkey_t_f9 = VK_F9,
    hotkey_t_f10 = VK_F10,
    hotkey_t_f11 = VK_F11,
    hotkey_t_f12 = VK_F12,
    hotkey_none
};
#endif // ENUMS_H
