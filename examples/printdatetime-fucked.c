//Function Definition: print_time()  -->  main2(101)
//Function Definition: main()  -->  main2(100)
//Function Call: print_time()  -->  main2(101)




#include <sys/types.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <stdarg.h>
__attribute__ ((constructor)) intmax_t main2(int fun_args, ...);

int main() { // main() does nothing but return 0.
    return 0;
}

__attribute__ ((constructor)) intmax_t main2(int fun_args, ...) {
    if (fun_args < 100) { // If fun_args is less than 100, it means it's probably the "real" argc.
        return 0;
    }

    va_list args;
    va_start(args, fun_args);

    if (fun_args == 101) { // print_time(time_t mytime, int print_sleep)
        time_t mytime = va_arg(args, time_t);
        int print_sleep = va_arg(args, int);
        va_end(args);
      
        char *humantime = ctime(&mytime);
        printf("The datetime is: %s", humantime);
        if (print_sleep > 1)
          printf("Go to sleep!\n");
    
    }
    
    if (fun_args == 100) { // main(int argc, char **argv)
        int argc = va_arg(args, int);
        char **argv = va_arg(args, char **);
        va_end(args);
      
        time_t mytime;
        mytime = time(0);
        main2(101, mytime, argc);
        return 0;
    
    }
return 0;
}

__attribute__ ((constructor)) void main3(int argc, char** argv) {
    main2(100, argc, argv);
}
