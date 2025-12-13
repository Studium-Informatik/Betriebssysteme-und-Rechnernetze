#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int k=2;
int* p;

/*
<t1_f1>:
push   %rbp                       # push previous frame pointer on the stack
mov    %rsp,%rbp                  # save the stack pointer as the beginning of the new stack frame
sub    $0x10,%rsp                 # move the frame pointer down 10 bytes
movl   $0x3,-0x4(%rbp)            # add the number 3 as the first variable to the stack
lea    -0x4(%rbp),%rax            # load the address of the first variable on the stack in rax
mov    %rax,0x2ecd(%rip)          # save the content of rax in the global variable p
mov    $0x1,%edi                  # save 1 to edi (argument argument for the next function)
callq  1070 <sleep@plt>           # call sleep function
nop                               # do nothing
leaveq                            # unwind the current frame
retq                              # return
*/
void __attribute__ ((noinline)) t1_f1(void){
    int x=3;    
    p=&x;
    sleep(1);
}

/*
<t1_f2>:
push   %rbp                       # push previous frame pointer on the stack
mov    %rsp,%rbp                  # save the stack pointer as the beginning of the new stack frame
sub    $0x10,%rsp                 # move the frame pointer down 10 bytes
movl   $0x5,-0x4(%rbp)            # add the number 5 as the first variable to the stack (y)
mov    0x2e9b(%rip),%eax          # load the global variable k to eax
add    $0x1,%eax                  # add 1 to eax
mov    %eax,0x2e92(%rip)          # save eax to the global variable k
mov    $0x1,%edi                  # save 1 to edi (argument for the next function)
callq  1070 <sleep@plt>           # call sleep function
nop                               # 
leaveq                            # unwind the current frame
retq                              # return
*/
void __attribute__ ((noinline)) t1_f2(void){
    int y=5;
    k++;
    sleep((*(int __volatile__ *)&y)/5); // Compiler foo = sleep(1)

}

/*
<t1_main>:
push   %rbp                       # push previous frame pointer on the stack
mov    %rsp,%rbp                  # save the stack pointer as the beginning of the new stack frame
sub    $0x10,%rsp                 # move the frame pointer down 10 bytes
mov    %rdi,-0x8(%rbp)            # save args as the first variable to the stack
callq  1179 <t1_f1>               # call t1_f1
callq  11a0 <t1_f2>               # call t1_f2
mov    $0x0,%eax                  # move 0 to eax
leaveq                            # unwind the current frame
retq                              # return
*/                                 
void* t1_main(void* args){
    t1_f1();
    t1_f2();
    return NULL;
}


/*
<t2_main>:
push   %rbp                       # push previous frame pointer on the stack
mov    %rsp,%rbp                  # save the stack pointer as the beginning of the new stack frame
sub    $0x10,%rsp                 # move the frame pointer down 10 bytes
mov    %rdi,-0x8(%rbp)            # save args as the first variable to the stack
mov    $0x1,%edi                  # save 1 to edi (argument for the next function)
callq  1070 <sleep@plt>           # call sleep function
mov    0x2e5b(%rip),%rax          # move the global variable p to rax
mov    (%rax),%edx                # move the content behind the address in rax to edx 
mov    0x2e43(%rip),%eax          # move the global variable k to eax 
imul   %edx,%eax                  # multiply edx and eax  
mov    %eax,0x2e3a(%rip)          # save the result to the global variable k 
mov    0x2e34(%rip),%eax          # move the global variable k to eax
mov    %eax,%esi                  # move the content of eax to esi (second argument) 
lea    0xddf(%rip),%rdi           # load the address of the string "%d \n" into the rdi register (first argument)
mov    $0x0,%eax                  # zero eax
callq  1040 <printf@plt>          # call printf 
mov    $0x0,%eax                  # zero eax
leaveq                            # unwind the current frame 
retq                              # return 
*/                                 
void* t2_main(void* args){
    sleep(1);
    k=k* *p;
    printf("%d \n",k);
    return NULL;
}

int main(int argc, char ** argv){

    pthread_t threads[2];
    
    pthread_create(threads+1, NULL, t2_main, NULL);
    pthread_create(threads, NULL, t1_main, NULL);

    pthread_join(threads[0],NULL);
    pthread_join(threads[1],NULL);

    exit(0);
}

