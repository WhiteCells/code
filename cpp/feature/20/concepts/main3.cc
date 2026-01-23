#include <concepts>
#include <string>

// 定义可渲染对象的概念
template <typename T>
concept Renderable = requires(T obj, int x, int y) {
    { obj.render(x, y) } -> std::same_as<void>;
    { obj.get_width() } -> std::convertible_to<int>;
    { obj.get_height() } -> std::convertible_to<int>;
};

// 定义可序列化的概念
template <typename T>
concept Serializable = requires(T obj, const std::string &filename) {
    { obj.serialize(filename) } -> std::same_as<bool>;
    { T::deserialize(filename) } -> std::same_as<T &>;
};

// 游戏引擎中的渲染系统
template <Renderable T>
void render_object(T &obj)
{
    obj.render(obj.get_width(), obj.get_height());
}

// 数据持久化系统
template <Serializable T>
bool save_object(T &obj, const std::string &filename)
{
    return obj.serialize(filename);
}

// 使用示例
class Sprite
{
public:
    void render(int, int) {}
    int get_width() const
    {
        return 64;
    }
    int get_height() const { return 64; }
};

class Config
{
public:
    bool serialize(const std::string &) { return true; }
    static Config &deserialize(const std::string &)
    {
        static Config cfg;
        return cfg;
    }
};

int main()
{
    Sprite sprite;
    render_object(sprite);
    // OK，Sprite满足Renderable

    Config config;
    save_object(config, "config.json");
    // OK，Config满足Serializable
}