#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <linux/kexec.h>
#include <sys/syscall.h>

#include <errno.h>

int main(int argc, char **argv) {
	if (argc != 2) {
		puts("invalid usage");
		return -1;
	}

	char *kernel_fname = argv[1];

	printf("kernel: %s\n", kernel_fname);

	FILE *kernel = fopen(kernel_fname, "r");

	if (kernel == NULL) {
		puts("can't open kernel file");
		return -1;
	}

	puts("kexecing\n");

	long r = syscall(
		SYS_kexec_file_load,
		fileno(kernel),
		-1,
		1,
		"\0",
		KEXEC_FILE_NO_INITRAMFS
	);


	fclose(kernel);

	printf("return value: %ld\n", r);

	if (r < 0) {
		printf("%d\n", errno);
	}

	return r;
}
