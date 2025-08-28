#include <iostream>

// 数据类：只管理坐标
class Point2D {
    public:
        int x, y;
        void move(int dx, int dy) { x += dx; y += dy; }
        double distanceTo(const Point2D& other) { /* ... */ }
    };
    
// 数据类：只管理血量
class Health {
public:
    int current, max;
    void takeDamage(int dmg) { current -= dmg; }
};

// 协调类：组合成员完成任务
class Creature {
private:
    Point2D location;    // 使用 Point2D 管理位置
    Health health;       // 使用 Health 管理血量
public:
    void move(int dx, int dy) { location.move(dx, dy); } // 委托给 Point2D
    void takeDamage(int dmg) { health.takeDamage(dmg); } // 委托给 Health
};
