#include <ruby.h>

static VALUE FastSlice = Qnil;

// Effectively a copy and paste from hash.c
// but replacing RHASH(hash)->tbl with RHASH_TBL (RHASH is not public)
static VALUE
rb_hash_has_key(VALUE hash, VALUE key)
{
  if (!RHASH_TBL(hash))
    return Qfalse;
  if (st_lookup(RHASH_TBL(hash), key, 0)) {
    return Qtrue;
  }
  return Qfalse;
}

static VALUE
fast_slice(VALUE hash, VALUE keys)
{
  if (TYPE(hash) != T_HASH) {
    rb_raise(rb_eTypeError, "expected a Hash");
    return Qfalse;
  }

  if (!RHASH_EMPTY_P(hash)) {
    VALUE result;
    result = rb_hash_new();

    int i;
    for (i=0; i < RARRAY_LEN(keys); i++) {
      VALUE key;
      key = rb_ary_entry(keys, i);
      if(rb_hash_has_key(hash, key) == Qtrue) {
        rb_hash_aset(result, key, rb_hash_aref(hash, key));
      }
    }

    return result;
  }

  return rb_hash_dup(hash);
}

VALUE
rb_fast_slice_m(int argc, VALUE *argv, VALUE self)
{
  VALUE hash, args;
  rb_scan_args(argc, argv, "1*", &hash, &args);
  return fast_slice(hash, args);
}

VALUE
rb_fast_slice(int argc, VALUE *argv, VALUE self)
{
  VALUE args;
  rb_scan_args(argc, argv, "0*", &args);
  return fast_slice(self, args);
}

static VALUE
rb_define_hash_slice_m(void)
{
  rb_define_method(rb_cHash, "slice", rb_fast_slice, -1);
  return Qtrue;
}

void Init_fast_slice( void )
{
  FastSlice = rb_define_module_under(rb_cObject, "FastSlice");
  rb_define_singleton_method(FastSlice, "slice", rb_fast_slice_m, -1);
  rb_define_method(FastSlice, "slice", rb_fast_slice, -1);
  rb_define_singleton_method(FastSlice, "define_on_hash", rb_define_hash_slice_m, 0);
}
