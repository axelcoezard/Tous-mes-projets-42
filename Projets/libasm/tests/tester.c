#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

size_t	ft_write(int fd, const char* buffer, size_t size);
size_t	ft_read(int fd, char* buffer, size_t size);
size_t	ft_strlen(char* str);
int		ft_strcmp(const char* s1, const char* s2);
char*	ft_strcpy(char* dest, char* src);
char*	ft_strdup(char* src);

#define __RED		"\033[1;31m"
#define __GREEN		"\033[1;32m"
#define __YELLOW	"\033[1;33m"
#define __BLUE		"\033[1;36m"
#define __WHITE		"\033[1;37m"
#define __EOC		"\033[0;0m"

static void	log(char* text, char* color)
{
	printf("==== %s%s%s ====\n", color, text, __EOC);
}

static void sub_log(char* text, char* color)
{
	printf("%s=> %s%s%s\n", __WHITE, color, text, __EOC);
}

static void test_ft_strlen(void)
{
	log("TEST DE FT_STRLEN", __BLUE);
	printf("ft_strlen('%s')=%d\n", "test", (int) ft_strlen("test"));
	printf("strlen('%s')=%d", "test", (int) strlen("test"));
	puts("\n");

	printf("ft_strlen('%s')=%d\n", "salut toi", (int) ft_strlen("salut toi"));
	printf("strlen('%s')=%d", "salut toi", (int) strlen("salut toi"));
	puts("\n");

	printf("ft_strlen('%s')=%d\n", "djshxgiuhdsouxgouhjdxcg", (int) ft_strlen("djshxgiuhdsouxgouhjdxcg"));
	printf("strlen('%s')=%d", "djshxgiuhdsouxgouhjdxcg", (int) strlen("djshxgiuhdsouxgouhjdxcg"));
	puts("\n");
}

void test_ft_strcpy(void)
{
	log("TEST DE FT_STRCPY", __BLUE);
	char* src = strdup("test\0");
	char* dest = strdup("hello\0");

	printf("ft_strcpy(dest, '%s')=%s\n", src, ft_strcpy(dest, src));
	printf("strcpy(dest, '%s')=%s", src, strcpy(dest, src));
	puts("\n");

	if (src)	free(src);
	if (dest)	free(dest);
}

static void test_ft_strcmp(void)
{
	log("TEST DE FT_STRCMP", __BLUE);
	char* src = strdup("test\0");
	char* dest = strdup("hello\0");
	printf("ft_strcmp('%s', '%s')=%d\n", dest, src, ft_strcmp(dest, src));
	printf("strcmp('%s', '%s')=%d\n", dest, src, strcmp(dest, src));
	puts("");

	if (src)	free(src);
	if (dest)	free(dest);
}

static void test_ft_strdup(void)
{
	log("TEST DE FT_STRDUP", __BLUE);
	char* test = "test";
	char* a = strdup(test);
	char* b = ft_strdup(test);

	printf("strdup('%s')=%s\n", test, a);
	printf("ft_strdup('%s')=%s\n", test, b);
	puts("");

	if (a < 0 || b < 0 || strcmp(a, b) != 0)
		printf("strdup() === ft_strdup() %s%s%s\n", __RED, "ERROR", __EOC);
	else
		printf("strdup() === ft_strdup() %s%s%s\n", __GREEN, "SUCCESS", __EOC);
	puts("");

	if (a)	free(a);
	if (b)	free(b);
}

static void test_ft_write(void)
{
	char* msg;
	log("TEST DE FT_WRITE", __BLUE);
	sub_log("standards: ", __BLUE);

	msg = "test\n\n";
	puts("write()=");
	write(1, msg, strlen(msg));
	puts("ft_write()=");
	ft_write(1, msg, strlen(msg));

	msg = "dsjgjdsgj\n\n";
	puts("write()=");
	write(1, msg, strlen(msg));
	puts("ft_write()=");
	ft_write(1, msg, strlen(msg));

	sub_log("errors: ", __BLUE);
	errno = 100; write(FOPEN_MAX + 1, "abcdefghijklmnopqrstuvwxyz\n", 27);
	perror("write errno");
	errno = 100; ft_write(FOPEN_MAX + 1, "abcdefghijklmnopqrstuvwxyz\n", 27);
	perror("ft_write errno");
	puts("");
}

static void test_ft_read(void)
{
	log("TEST DE FT_READ", __BLUE);

	char* buffer;
	char* ft_buffer;
	int fd = open("tests/test.txt", O_RDONLY);
	int fs = lseek(fd, 0, SEEK_END);
	sub_log("standards: ", __BLUE);
	buffer = malloc(sizeof(char) * (fs * 2));
	ft_buffer = malloc(sizeof(char) * (fs * 2));

	lseek(fd, 0, SEEK_SET);
	int a = read(fd, buffer, fs);

	lseek(fd, 0, SEEK_SET);
	int b = ft_read(fd, ft_buffer, fs);

	if (a < 0 || b < 0 || strcmp(buffer, ft_buffer) != 0)
		printf("ft_read() === read() %s%s%s\n", __RED, "ERROR", __EOC);
	else
		printf("ft_read() === read() %s%s%s\n", __GREEN, "SUCCESS", __EOC);
	puts("");

	sub_log("errors: ", __BLUE);
	errno = 100; read(fd, buffer, 1);
	perror("read errno");
	errno = 100; ft_read(fd, ft_buffer, 1);
	perror("ft_read errno");
	puts("");

	if (fd)			close(fd);
	if (buffer)		free(buffer);
	if (ft_buffer)	free(ft_buffer);
}

int main(int ac, char **av)
{
	(void) ac;
	(void) av;

	test_ft_strlen();
	test_ft_strcmp();
	test_ft_strcpy();
	test_ft_strdup();
	test_ft_write();
	test_ft_read();

	return 0;
}
