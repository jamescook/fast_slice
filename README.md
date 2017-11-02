## fast_slice

Hash#slice implemented in C.

### Usage
```ruby
require 'fast_slice'

FastSlice.slice(my_hash, :a, :b, :c)
```

Alternatively, you can call `FastSlice.define_on_hash` to create a `slice`
instance method on Hash.

```ruby
FastSlice.define_on_hash
hash = {a: 1, b: 2, c: 3}
hash.slice(:c)
```

### Benchmarks

From `rake benchmark` using Ruby 2.4 on an i7 Macbook:
```
Warming up --------------------------------------
     FastSlice.slice    73.127k i/100ms
Calculating -------------------------------------
     FastSlice.slice    961.308k (± 3.2%) i/s -     19.232M in  20.030666s

Warming up --------------------------------------
ActiveSupport's Hash#slice
                        41.469k i/100ms
Calculating -------------------------------------
ActiveSupport's Hash#slice
                        474.034k (± 1.3%) i/s -      9.496M in  20.036614s

Comparison:
           FastSlice.slice:   961307.9 i/s
ActiveSupport's Hash#slice:   474033.8 i/s - 2.03x  slower
```

### Requirements
- Ruby 1.9 or above
- Ability to compile native extensions
