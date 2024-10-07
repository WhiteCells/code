### 抽象工厂模式

#### UML

```mermaid
classDiagram

class Factory {
    <<abstract>>
    ...
    +~~createProductA~~() ProductA
    +~~createProductB~~() ProductB
}

class Factory1 {
    ...
    +createProductA() ProductA
    +createProductB() ProductB
}

class Factory2 {
    ...
    +createProductA() ProductA
    +createProductB() ProductB
}

Factory1 ..|> Factory
Factory2 ..|> Factory

class ProductA {
    <<abstract>>
    ...
}

class ProductA1 {
    ...
}

class ProductA2 {
    ...
}

ProductA1 ..|> ProductA
ProductA2 ..|> ProductA

class ProductB {
    <<abstract>>
    ...
}

class ProductB1 {
    ...
}

class ProductB2 {
    ...
}

ProductB1 ..|> ProductB
ProductB2 ..|> ProductB

Factory1 ..> ProductA1
Factory1 ..> ProductB1
Factory2 ..> ProductA2
Factory2 ..> ProductB2
```

#### 优点

- 确保同一工厂生产的产品相互匹配
- 可以避免客户端和具体代码的耦合
- 符合单一职责原则，产品生成代码位于同一位置
- 符合开闭原则，程序引入新产品时无需修改客户端代码

#### 缺点

- 复杂性增加，抽象工厂引入的多个新的接口和类，增加了系统的复杂性
- 难以增加新种类的产品，如需增加新的产品种类，则可能需要修改抽象工厂的接口，这导致所有实现这个接口的具体工厂都要修改