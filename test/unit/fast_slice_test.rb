require_relative "../test_helper.rb"

describe FastSlice do
  describe ".slice with no args" do
    it "returns an argument error" do
      assert_raises ArgumentError do
        FastSlice.slice
      end
    end
  end

  describe ".slice given something that isn't a Hash" do
    it "returns a type error" do
      assert_raises TypeError do
        FastSlice.slice(42)
      end
    end
  end

  describe ".slice a hash and no additional args" do
    it "returns a dup of the hash" do
      hash = {}
      result = FastSlice.slice(hash)
      assert_equal false, hash.object_id == FastSlice.slice(hash).object_id
      assert_equal hash, result
    end
  end

  describe ".slice a hash with elements and args that map to keys" do
    it "returns the appropriate hash" do
      hash = {x: 1, y: 2, z: 3}
      assert_equal({y: 2}, FastSlice.slice(hash, :y))
    end
  end

  describe ".slice a hash with elements and some args that map to keys and some that don't" do
    it "returns the the appropriate hash" do
      hash = {x: 1, y: 2, z: 3}
      assert_equal({x: 1}, FastSlice.slice(hash, :x, :i_don_t_exist))
    end
  end

  describe ".define_on_hash" do
    it "creates a #slice method on Hash" do
      FastSlice.define_on_hash
      hash = {x: 42, y: -42}
      assert_equal({y: -42}, hash.slice(:y))
    end
  end
end
