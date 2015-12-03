#ifndef __FTW_MEM_H__
#define __FTW_MEM_H__

#if FTW_DEBUG
#define FTW_MEM_alloc(nSize)        _FTW_MEM_DEBUG_alloc(__func__, __LINE__, nSize)      
#define FTW_MEM_allocZero(nSize)    _FTW_MEM_DEBUG_allocZero(__func__, __LINE__, nSize)      
#define FTW_MEM_free(pMem);         _FTW_MEM_DEBUG_free(__func__, __LINE__, pMem)      
#else
#define FTW_MEM_alloc(nSize)        gsn_malloc(nSize)      
inline  void *FTW_MEM_allocZero(uint_32 nSize)    { void *pValue = gsn_malloc(nSize); if (pValue != NULL) { memset(pValue, 0, nSize); }; return pValue; }
#define FTW_MEM_free(pMem);         gsn_free(pMem)      
#endif

#define _mem_alloc_zero(x)          FTW_MEM_alloc((x))
#define _mem_alloc(x)               FTW_MEM_alloc((x))
#define _mem_free(x)                FTW_MEM_free((x))

void *  _FTW_MEM_DEBUG_alloc(const char *pFunc, int nLine, uint_32 nSize);
void *  _FTW_MEM_DEBUG_allocZero(const char *pFunc, int nLine, uint_32 nSize);
void    _FTW_MEM_DEBUG_free(const char *pFunc, int nLine, void *pMem);

int_32  FTW_MEM_SHELL_cmd(int_32 argc, char_ptr argv[]);
#endif
