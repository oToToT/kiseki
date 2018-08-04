//stack resize
asm( "mov %0,%%esp\n" ::"g"(mem+10000000) );
//change esp to rsp if 64-bit system

//stack resize (linux)
#include <sys/resource.h>
void increase_stack_size() {
    const rlim_t ks = 64*1024*1024;
    struct rlimit rl;
    int res=getrlimit(RLIMIT_STACK, &rl);
    if(res==0){
        if(rl.rlim_cur<ks){
            rl.rlim_cur=ks;
            res=setrlimit(RLIMIT_STACK, &rl);
        }
    }
}

// craziest way
static void run_with_stack_size(void (*func)(), size_t stsize) {
    char *stack, *send;
    stack=(char *)malloc(stsize);
    send=stack+stsize-16;
    send=(char *)((uintptr_t)send/16*16);
    asm volatile(
      "mov %%rsp, (%0)\n"
      "mov %0, %%rsp\n"
      :
      : "r" (send));
    func();
    asm volatile(
      "mov (%0), %%rsp\n"
      :
      : "r" (send));
    free(stack);
}