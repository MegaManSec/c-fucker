//Function Definition: rio_readinitb()  -->  main2(0)
//Function Definition: writen()  -->  main2(1)
//Function Definition: rio_read()  -->  main2(2)
//Function Definition: rio_readlineb()  -->  main2(3)
//Function Call: rio_read()  -->  main2(2)
//Function Definition: format_size()  -->  main2(4)
//Function Definition: handle_directory_request()  -->  main2(5)
//Function Call: writen()  -->  main2(1)
//Function Call: format_size()  -->  main2(4)
//Function Call: writen()  -->  main2(1)
//Function Call: writen()  -->  main2(1)
//Function Definition: get_mime_type()  -->  main2(6)
//Function Definition: open_listenfd()  -->  main2(7)
//Function Definition: url_decode()  -->  main2(8)
//Function Definition: parse_request()  -->  main2(9)
//Function Call: rio_readinitb()  -->  main2(0)
//Function Call: rio_readlineb()  -->  main2(3)
//Function Call: rio_readlineb()  -->  main2(3)
//Function Call: url_decode()  -->  main2(8)
//Function Definition: log_access()  -->  main2(10)
//Function Definition: client_error()  -->  main2(11)
//Function Call: writen()  -->  main2(1)
//Function Definition: serve_static()  -->  main2(12)
//Function Call: get_mime_type()  -->  main2(6)
//Function Call: writen()  -->  main2(1)
//Function Definition: process()  -->  main2(13)
//Function Call: parse_request()  -->  main2(9)
//Function Call: client_error()  -->  main2(11)
//Function Call: serve_static()  -->  main2(12)
//Function Call: handle_directory_request()  -->  main2(5)
//Function Call: client_error()  -->  main2(11)
//Function Call: log_access()  -->  main2(10)
//Function Definition: main()  -->  main2(-1)
//Function Call: open_listenfd()  -->  main2(7)
//Function Call: process()  -->  main2(13)
//Function Call: process()  -->  main2(13)




#include <arpa/inet.h>
#include <signal.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdarg.h>
typedef struct 
{
  int rio_fd;
  int rio_cnt;
  char *rio_bufptr;
  char rio_buf[1024];
} rio_t;
typedef struct sockaddr SA;
typedef struct 
{
  char filename[512];
  off_t offset;
  size_t end;
} http_request;
typedef struct 
{
  const char *extension;
  const char *mime_type;
} mime_map;
mime_map meme_types[] = {{".css", "text/css"}, {".gif", "image/gif"}, {".htm", "text/html"}, {".html", "text/html"}, {".jpeg", "image/jpeg"}, {".jpg", "image/jpeg"}, {".ico", "image/x-icon"}, {".js", "application/javascript"}, {".pdf", "application/pdf"}, {".mp4", "video/mp4"}, {".png", "image/png"}, {".svg", "image/svg+xml"}, {".xml", "text/xml"}, {0, 0}};
char *default_mime_type = "text/plain";

intmax_t main2(int fun_args, ...);

int main(int argc, char** argv) {
    main2(-1, argc, argv);
}

intmax_t main2(int fun_args, ...) {
    va_list args;
    va_start(args, fun_args);

    if (fun_args == 0) { // rio_readinitb(rio_t *rp, int fd)
        rio_t *rp = va_arg(args, rio_t *);
        int fd = va_arg(args, int);
      
        rp->rio_fd = fd;
        rp->rio_cnt = 0;
        rp->rio_bufptr = rp->rio_buf;
    
    }
    
    if (fun_args == 1) { // writen(int fd, void *usrbuf, size_t n)
        int fd = va_arg(args, int);
        void *usrbuf = va_arg(args, void *);
        size_t n = va_arg(args, size_t);
      
        size_t nleft = n;
        ssize_t nwritten;
        char *bufp = usrbuf;
        while (nleft > 0)
        {
          if ((nwritten = write(fd, bufp, nleft)) <= 0)
          {
            if (errno == EINTR)
              nwritten = 0;
            else
              return -1;
          }
          nleft -= nwritten;
          bufp += nwritten;
        }
      
        return n;
    
    }
    
    if (fun_args == 2) { // rio_read(rio_t *rp, char *usrbuf, size_t n)
        rio_t *rp = va_arg(args, rio_t *);
        char *usrbuf = va_arg(args, char *);
        size_t n = va_arg(args, size_t);
      
        int cnt;
        while (rp->rio_cnt <= 0)
        {
          rp->rio_cnt = read(rp->rio_fd, rp->rio_buf, sizeof(rp->rio_buf));
          if (rp->rio_cnt < 0)
          {
            if (errno != EINTR)
              return -1;
          }
          else
            if (rp->rio_cnt == 0)
            return 0;
          else
            rp->rio_bufptr = rp->rio_buf;
        }
      
        cnt = n;
        if (rp->rio_cnt < n)
          cnt = rp->rio_cnt;
        memcpy(usrbuf, rp->rio_bufptr, cnt);
        rp->rio_bufptr += cnt;
        rp->rio_cnt -= cnt;
        return cnt;
    
    }
    
    if (fun_args == 3) { // rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen)
        rio_t *rp = va_arg(args, rio_t *);
        void *usrbuf = va_arg(args, void *);
        size_t maxlen = va_arg(args, size_t);
      
        int n;
        int rc;
        char c;
        char *bufp = usrbuf;
        for (n = 1; n < maxlen; n++)
        {
          if ((rc = main2(2, rp, &c, 1)) == 1)
          {
            *(bufp++) = c;
            if (c == '\n')
              break;
          }
          else
            if (rc == 0)
          {
            if (n == 1)
              return 0;
            else
              break;
          }
          else
            return -1;
        }
      
        *bufp = 0;
        return n;
    
    }
    
    if (fun_args == 4) { // format_size(char *buf, struct stat *stat)
        char *buf = va_arg(args, char *);
        struct stat *stat = va_arg(args, struct stat *);
      
        if (S_ISDIR(stat->st_mode))
        {
          sprintf(buf, "%s", "[DIR]");
        }
        else
        {
          off_t size = stat->st_size;
          if (size < 1024)
          {
            sprintf(buf, "%lu", size);
          }
          else
            if (size < (1024 * 1024))
          {
            sprintf(buf, "%.1fK", ((double) size) / 1024);
          }
          else
            if (size < ((1024 * 1024) * 1024))
          {
            sprintf(buf, "%.1fM", (((double) size) / 1024) / 1024);
          }
          else
          {
            sprintf(buf, "%.1fG", ((((double) size) / 1024) / 1024) / 1024);
          }
        }
    
    }
    
    if (fun_args == 5) { // handle_directory_request(int out_fd, int dir_fd, char *filename)
        int out_fd = va_arg(args, int);
        int dir_fd = va_arg(args, int);
        char *filename = va_arg(args, char *);
      
        char buf[1024];
        char m_time[32];
        char size[16];
        struct stat statbuf;
        sprintf(buf, "HTTP/1.1 200 OK\r\n%s%s%s%s%s", "Content-Type: text/html\r\n\r\n", "<html><head><style>", "body{font-family: monospace; font-size: 13px;}", "td {padding: 1.5px 6px;}", "</style></head><body><table>\n");
        main2(1, out_fd, buf, strlen(buf));
        DIR *d = fdopendir(dir_fd);
        struct dirent *dp;
        int ffd;
        while ((dp = readdir(d)) != 0)
        {
          if ((!strcmp(dp->d_name, ".")) || (!strcmp(dp->d_name, "..")))
          {
            continue;
          }
          if ((ffd = openat(dir_fd, dp->d_name, O_RDONLY)) == (-1))
          {
            perror(dp->d_name);
            continue;
          }
          fstat(ffd, &statbuf);
          strftime(m_time, sizeof(m_time), "%Y-%m-%d %H:%M", localtime(&statbuf.st_mtime));
          main2(4, size, &statbuf);
          if (S_ISREG(statbuf.st_mode) || S_ISDIR(statbuf.st_mode))
          {
            char *d = (S_ISDIR(statbuf.st_mode)) ? ("/") : ("");
            sprintf(buf, "<tr><td><a href=\"%s%s\">%s%s</a></td><td>%s</td><td>%s</td></tr>\n", dp->d_name, d, dp->d_name, d, m_time, size);
            main2(1, out_fd, buf, strlen(buf));
          }
          close(ffd);
        }
      
        sprintf(buf, "</table></body></html>");
        main2(1, out_fd, buf, strlen(buf));
        closedir(d);
    
    }
    
    if (fun_args == 6) { // get_mime_type(char *filename)
        char *filename = va_arg(args, char *);
      
        char *dot = strrchr(filename, '.');
        if (dot)
        {
          mime_map *map = meme_types;
          while (map->extension)
          {
            if (strcmp(map->extension, dot) == 0)
            {
              return (intmax_t)map->mime_type;
            }
            map++;
          }
      
        }
        return (intmax_t)default_mime_type;
    
    }
    
    if (fun_args == 7) { // open_listenfd(int port)
        int port = va_arg(args, int);
      
        int listenfd;
        int optval = 1;
        struct sockaddr_in serveraddr;
        if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
          return -1;
        if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void *) (&optval), sizeof(int)) < 0)
          return -1;
        memset(&serveraddr, 0, sizeof(serveraddr));
        serveraddr.sin_family = AF_INET;
        serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
        serveraddr.sin_port = htons((unsigned short) port);
        if (bind(listenfd, (SA *) (&serveraddr), sizeof(serveraddr)) < 0)
          return -1;
        if (listen(listenfd, 1024) < 0)
          return -1;
        return listenfd;
    
    }
    
    if (fun_args == 8) { // url_decode(char *src, char *dest, int max)
        char *src = va_arg(args, char *);
        char *dest = va_arg(args, char *);
        int max = va_arg(args, int);
      
        char *p = src;
        char code[3] = {0};
        while ((*p) && (--max))
        {
          if ((*p) == '%')
          {
            memcpy(code, ++p, 2);
            *(dest++) = (char) strtoul(code, 0, 16);
            p += 2;
          }
          else
          {
            *(dest++) = *(p++);
          }
        }
      
        *dest = '\0';
    
    }
    
    if (fun_args == 9) { // parse_request(int fd, http_request *req)
        int fd = va_arg(args, int);
        http_request *req = va_arg(args, http_request *);
      
        rio_t rio;
        char buf[1024];
        char method[1024];
        char uri[1024];
        req->offset = 0;
        req->end = 0;
        main2(0, &rio, fd);
        main2(3, &rio, buf, 1024);
        sscanf(buf, "%s %s", method, uri);
        while ((buf[0] != '\n') && (buf[1] != '\n'))
        {
          main2(3, &rio, buf, 1024);
          if (((buf[0] == 'R') && (buf[1] == 'a')) && (buf[2] == 'n'))
          {
            sscanf(buf, "Range: bytes=%lu-%lu", &req->offset, &req->end);
            if (req->end != 0)
              req->end++;
          }
        }
      
        char *filename = uri;
        if (uri[0] == '/')
        {
          filename = uri + 1;
          int length = strlen(filename);
          if (length == 0)
          {
            filename = ".";
          }
          else
          {
            for (int i = 0; i < length; ++i)
            {
              if (filename[i] == '?')
              {
                filename[i] = '\0';
                break;
              }
            }
      
          }
        }
        main2(8, filename, req->filename, 1024);
    
    }
    
    if (fun_args == 10) { // log_access(int status, struct sockaddr_in *c_addr, http_request *req)
        int status = va_arg(args, int);
        struct sockaddr_in *c_addr = va_arg(args, struct sockaddr_in *);
        http_request *req = va_arg(args, http_request *);
      
        printf("%s:%d %d - %s\n", inet_ntoa(c_addr->sin_addr), ntohs(c_addr->sin_port), status, req->filename);
    
    }
    
    if (fun_args == 11) { // client_error(int fd, int status, char *msg, char *longmsg)
        int fd = va_arg(args, int);
        int status = va_arg(args, int);
        char *msg = va_arg(args, char *);
        char *longmsg = va_arg(args, char *);
      
        char buf[1024];
        sprintf(buf, "HTTP/1.1 %d %s\r\n", status, msg);
        sprintf(buf + strlen(buf), "Content-length: %lu\r\n\r\n", strlen(longmsg));
        sprintf(buf + strlen(buf), "%s", longmsg);
        main2(1, fd, buf, strlen(buf));
    
    }
    
    if (fun_args == 12) { // serve_static(int out_fd, int in_fd, http_request *req, size_t total_size)
        int out_fd = va_arg(args, int);
        int in_fd = va_arg(args, int);
        http_request *req = va_arg(args, http_request *);
        size_t total_size = va_arg(args, size_t);
      
        char buf[256];
        if (req->offset > 0)
        {
          sprintf(buf, "HTTP/1.1 206 Partial\r\n");
          sprintf(buf + strlen(buf), "Content-Range: bytes %lu-%lu/%lu\r\n", req->offset, req->end, total_size);
        }
        else
        {
          sprintf(buf, "HTTP/1.1 200 OK\r\nAccept-Ranges: bytes\r\n");
        }
        sprintf(buf + strlen(buf), "Cache-Control: no-cache\r\n");
        sprintf(buf + strlen(buf), "Content-length: %lu\r\n", req->end - req->offset);
        sprintf(buf + strlen(buf), "Content-type: %s\r\n\r\n", main2(6, req->filename));
        main2(1, out_fd, buf, strlen(buf));
        off_t offset = req->offset;
        off_t sbytes = 0;
        while (offset < req->end)
        {
          if (sendfile(out_fd, in_fd, offset, req->end - req->offset, 0, &sbytes, 0) <= 0)
          {
            break;
          }
          close(out_fd);
          break;
        }
      
    
    }
    
    if (fun_args == 13) { // process(int fd, struct sockaddr_in *clientaddr)
        int fd = va_arg(args, int);
        struct sockaddr_in *clientaddr = va_arg(args, struct sockaddr_in *);
      
        printf("accept request, fd is %d, pid is %d\n", fd, getpid());
        http_request req;
        main2(9, fd, &req);
        struct stat sbuf;
        int status = 200;
        int ffd = open(req.filename, O_RDONLY, 0);
        if (ffd <= 0)
        {
          status = 404;
          char *msg = "File not found";
          main2(11, fd, status, "Not found", msg);
        }
        else
        {
          fstat(ffd, &sbuf);
          if (S_ISREG(sbuf.st_mode))
          {
            if (req.end == 0)
            {
              req.end = sbuf.st_size;
            }
            if (req.offset > 0)
            {
              status = 206;
            }
            main2(12, fd, ffd, &req, sbuf.st_size);
          }
          else
            if (S_ISDIR(sbuf.st_mode))
          {
            status = 200;
            main2(5, fd, ffd, req.filename);
          }
          else
          {
            status = 400;
            char *msg = "Unknow Error";
            main2(11, fd, status, "Error", msg);
          }
          close(ffd);
        }
        main2(10, status, clientaddr, &req);
    
    }
    
    if (fun_args == -1) { // main(int argc, char **argv)
        int argc = va_arg(args, int);
        char **argv = va_arg(args, char **);
      
        struct sockaddr_in clientaddr;
        int default_port = 9999;
        int listenfd;
        int connfd;
        char buf[256];
        char *path = getcwd(buf, 256);
        socklen_t clientlen = sizeof(clientaddr);
        if (argc == 2)
        {
          if ((argv[1][0] >= '0') && (argv[1][0] <= '9'))
          {
            default_port = atoi(argv[1]);
          }
          else
          {
            path = argv[1];
            if (chdir(argv[1]) != 0)
            {
              perror(argv[1]);
              exit(1);
            }
          }
        }
        else
          if (argc == 3)
        {
          default_port = atoi(argv[2]);
          path = argv[1];
          if (chdir(argv[1]) != 0)
          {
            perror(argv[1]);
            exit(1);
          }
        }
        listenfd = main2(7, default_port);
        if (listenfd > 0)
        {
          printf("listen on port %d, fd is %d\n", default_port, listenfd);
        }
        else
        {
          perror("ERROR");
          exit(listenfd);
        }
        signal(SIGPIPE, SIG_IGN);
        for (int i = 0; i < 10; i++)
        {
          int pid = fork();
          if (pid == 0)
          {
            while (1)
            {
              connfd = accept(listenfd, (SA *) (&clientaddr), &clientlen);
              main2(13, connfd, &clientaddr);
              close(connfd);
            }
      
          }
          else
            if (pid > 0)
          {
            printf("child pid is %d\n", pid);
          }
          else
          {
            perror("fork");
          }
        }
      
        while (1)
        {
          connfd = accept(listenfd, (SA *) (&clientaddr), &clientlen);
          main2(13, connfd, &clientaddr);
          close(connfd);
        }
      
        return 0;
    
    }
}

