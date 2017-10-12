#include <ruby.h>

// Effectively a copy and paste from hash.c
// but replacing RHASH(hash)->tbl with RHASH_TBL (RHASH is not public)
VALUE
__rb_hash_has_key(VALUE hash, VALUE key)
{
  if (!RHASH_TBL(hash))
    return Qfalse;
  if (st_lookup(RHASH_TBL(hash), key, 0)) {
    return Qtrue;
  }
  return Qfalse;
}

VALUE
rb_fast_slice(int argc, VALUE *argv, VALUE self)
{
  VALUE hash, args;
  rb_scan_args(argc, argv, "1*", &hash, &args);

  if (TYPE(hash) != T_HASH) {
    rb_raise(rb_eTypeError, "expected a Hash");
    return Qfalse;
  }

  if (NIL_P(args)) {
    return hash;
  }

  if (!RHASH_EMPTY_P(hash)) {
    VALUE result;
    result = rb_hash_new();

    int i;
    for (i=0; i < RARRAY_LEN(args); i++) {
      VALUE arg;
      arg = rb_ary_entry(args, i);
      if(__rb_hash_has_key(hash, arg) == Qtrue) {
        rb_hash_aset(result, arg, rb_hash_aref(hash, arg));
      }
    }

    return result;
  }

  return hash;
}

// Add the `slice` instance method to Hash
// TODO figure out how to do this
VALUE rb_define_hash_slice(int argc, VALUE *argv, VALUE self)
{
  rb_define_method(rb_cHash, "slice", rb_fast_slice, -1);

  return Qtrue;
}

void Init_fast_slice( void )
{
  VALUE FastSlice = Qnil;
  FastSlice = rb_define_class_under(rb_cObject, "FastSlice", rb_cObject);
      
  rb_define_singleton_method(FastSlice, "slice", rb_fast_slice, -1);
  // rb_define_singleton_method(FastSlice, "define_on_hash", rb_define_hash_slice, 0);
}
