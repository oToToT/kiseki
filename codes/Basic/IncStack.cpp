//stack resize(change esp to rsp if 64-bit system)
asm( "mov %0,%%esp\n" ::"g"(mem+10000000) );
// craziest way
static void run_with_stack_size(void(*func)(),size_t stsize){
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