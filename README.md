# vtable

use kv engine to simulate column database

```
name                birth               age                 occupation          country
Alexander           BC 356.7.20         33                  emperor             Macedonia
Caesar              BC 100.7.3          56                  dictator            Rome
Hannibal            BC 247              64                  administrator       Carthage
Napoleon            AD 1769.8.5         52                  emperor             France

test Get:
Napoleon birth: AD 1769.8.5

test Get:
Napoleon: Napoleon, AD 1769.8.5, 52, emperor, France,

test GetColumn:
age: 33, 56, 64, 52,
```
