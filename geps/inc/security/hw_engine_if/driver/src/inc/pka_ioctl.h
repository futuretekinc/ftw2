#ifndef _PKA_IOCTL_H
#define _PKA_IOCTL_H

#include <linux/ioctl.h>
#include <linux/types.h>

struct pka_param {
   __u8  func[32];
   __u8  name[30];
   __u16 size;
   __u8  value[512];
};

enum {
   PKA_MIN_NUM = 0x10,
   PKA_SETPARAM_NUM = PKA_MIN_NUM,
   PKA_GETPARAM_NUM,
   PKA_CALL_NUM,
   PKA_WAIT_NUM,
   PKA_IDENT_NUM,
   PKA_ABORT_NUM,
   PKA_TESTF_NUM,
   PKA_SETF_NUM,
   PKA_MAX_NUM
};

#define PKA_IOC_SETPARAM   _IOW ('k', PKA_SETPARAM_NUM, struct pka_param)
#define PKA_IOC_GETPARAM   _IOWR('k', PKA_SETPARAM_NUM, struct pka_param)
#define PKA_IOC_CALL       _IOW ('k', PKA_CALL_NUM,     struct pka_param)
#define PKA_IOC_WAIT       _IO  ('k', PKA_WAIT_NUM)
#define PKA_IOC_ABORT      _IO  ('k', PKA_ABORT_NUM)
#define PKA_IOC_TESTF      _IOW ('k', PKA_TESTF_NUM,    struct pka_param)
#define PKA_IOC_SETF       _IOW ('k', PKA_SETF_NUM,     struct pka_param)

#define PKA_IOC_IDENT(len) _IOC (_IOC_READ, 'k', PKA_IDENT_NUM, len)

#endif
