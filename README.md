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
TODO

### Requirements
- Ruby 1.9 or above
- Ability to compile native extensions
