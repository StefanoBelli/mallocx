#ifndef DEBUG_FACILITY_H
#define DEBUG_FACILITY_H

#define __VALUE_HELPER(xval) #xval
#define any_to_string(orig) __VALUE_HELPER(orig)

#if defined(__GNUC_MINOR__) || defined(__clang__)
#define __PREFIX_FMT__ "[DEBUG][" __FILE__ ":" any_to_string(__LINE__) "][%s] "
#endif

#if defined(ENABLE_DEBUG_PRINTFS) && (defined(__GNUC_MINOR__) || defined(__clang__))
#define dfenter() \
  printf(__PREFIX_FMT__ "entering function\n", __PRETTY_FUNCTION__)

#define dfleave() \
  printf(__PREFIX_FMT__ "leaving function\n", __PRETTY_FUNCTION__)

#define dvalue(xv)                                                             \
  printf(__PREFIX_FMT__ "value for: %s is 0x%llx\n", __PRETTY_FUNCTION__, #xv, \
         (long long)xv)

#define dstring(xv) \
  printf(__PREFIX_FMT__ "value for: %s is %s\n", __PRETTY_FUNCTION__, #xv, xv)

#define dmessage(xstring) \
  printf(__PREFIX_FMT__ "message: %s\n", __PRETTY_FUNCTION__, xstring)

#else
#define dfenter()
#define dfleave()
#define dvalue(__p_unused)
#define dstring(__p_unused)
#define dmessage(__p_unused)

#endif

#endif
