#pragma once

// 地图类，用于显示地图并处理移动逻辑
class Map
{
public:
    // 显示地图，传入角色的当前位置标志
    void showmap(int placeflag);

    // 角色移动函数，传入移动的目标位置
    void move(int targetPlace);
};
