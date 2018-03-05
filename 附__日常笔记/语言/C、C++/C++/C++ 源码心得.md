# CPP 源码心得记录

#### 01 初始化列表

```CPP
class Animal
{
public:
    Animal(int weight, int height):     // 初始化列表
        m_weight(weight),
        m_height(height)
      {
      }

    Animal(int weight, int height)      // 函数体内初始化
    {
        m_weight = weight;
        m_height = height;
    }

private:
    int m_weight;
    int m_height;
}
```
