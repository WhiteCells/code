### 设计模式

the purpose is to use simple cases to embody the ideas of design patterns.

用简单的案例来体现设计模式的思想

### 目录

- creative
  - [factory](./creative/factory_method/README.md)
  - [abstract factory](./creative/abstract_factory/README.md)
  - [builder](./creative/builder/README.md)
  - [prototype](./creative/prototype/README.md)
  - [singleton](./creative/singleton/README.md)

- structural
  - [adapter](./structural/adapter/README.md)
  - [bridge](./structural/bridge/README.md)
  - [composite](./structural/composite/README.md)
  - [decorator](./structural/decorator/README.md)
  - [facade](./structural/facade/README.md)
  - [flyweight](./structural/flyweight/README.md)
  - [proxy](./structural/proxy/README.md)

- behaviour
  - [chain of responsibility](./behaviour/chain_of_responsibility/README.md)
  - [command](./behaviour/command/README.md)
  - [interpreter](./behaviour/interpreter/README.md)
  - [iterator](./behaviour/iterator/README.md)
  - [mediator](./behaviour/mediator/README.md)
  - [memento](./behaviour/memento/README.md)
  - [observer](./behaviour/observer/README.md)
  - [state](./behaviour/state/README.md)
  - [strategy](./behaviour/strategy/README.md)
  - [template](./behaviour/template/README.md)
  - [vistor](./behaviour/vistor/README.md)

### 运行

环境

- OS: Linux / Windows
- Compiler: g++ (GCC) 13.2.1 20230801
- Build Tools: cmake version 3.28.3

```sh
# factor
cd ./creative/factory
cmake -B build
cmake --build build
./build/factory

# ...
```
