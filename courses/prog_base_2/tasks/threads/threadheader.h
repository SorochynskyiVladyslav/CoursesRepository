#ifndef THREADHEADER_H_INCLUDED
#define THREADHEADER_H_INCLUDED

typedef struct stack_s * stack_t;
typedef enum status{
    STACK_OK,
    STACK_OVERFLOW,
} status;

//DWORD Producer(LPVOID);
//DWORD Consumer(LPVOID);
//HANDLE newThread(LPTHREAD_START_ROUTINE routine, struct Context * ctx);
stack_t stack_new (void);
void stack_free (stack_t s);
void stack_push (stack_t p, int element);
int stack_pop (stack_t p);


typedef struct mutex_s mutex_t;

mutex_t * mutex_new(void);
void mutex_free(mutex_t * self);

void mutex_lock(mutex_t * self);
void mutex_unlock(mutex_t * self);


typedef struct thread_s thread_t;
typedef void * (*thread_func_t)(void *);

// helper functions
thread_t * thread_getCurrentThread(void);
void thread_exit(void * retval);

// constructors
thread_t * thread_create(thread_func_t func);
thread_t * thread_create_args(thread_func_t func, void * args);
// destructor
void thread_free(thread_t * self);

// methods
int thread_join(const thread_t * self);
int thread_join_result(const thread_t * self, void ** result);
int thread_terminate(const thread_t * self);
int thread_equals(const thread_t * self, const thread_t * obj);

#endif // THREADHEADER_H_INCLUDED
